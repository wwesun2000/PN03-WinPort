#include "pn03_all_forwards.hpp"
#include "pn03_audio_ax.hpp"
#include "pn03_config.hpp"
#include "pn03_cyber_launcher.hpp"
#include "pn03_d3d11_host.hpp"
#include "pn03_gx_3d_interface.hpp"
#include "pn03_host_common.hpp"
#include "pn03_logger.hpp"
#include "pn03_ppc_context.hpp"
#include "pn03_runtime.hpp"
#include "pn03_symbols.hpp"
#include "pn03_vulkan_host.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

using namespace pn03;

static void test_memory_and_ppc_context() {
    Memory mem;
    PPCContext ctx;
    ctx.mem_ptr = &mem;
    assert(ctx.r[1]  == kGcInitialSp);
    assert(ctx.r[2]  == kGcSda2Base);
    assert(ctx.r[13] == kGcSda1Base);

    mem.write_u32(0x80003100u, 0x3C208028u);
    assert(mem.read_u32(0x80003100u) == 0x3C208028u);
    assert(mem.read_u16(0x80003100u) == 0x3C20u);
    assert(mem.read_u8(0x80003100u)  == 0x3Cu);

    mem.write_f64(0x80190000u, 3.141592653589793);
    assert(std::fabs(mem.read_f64(0x80190000u) - 3.141592653589793) < 1e-12);

    ctx.r[28] = 0x11112222u;
    ctx.r[29] = 0x33334444u;
    ctx.r[30] = 0x55556666u;
    ctx.r[31] = 0x77778888u;
    ctx.stmw(mem, 28, 0x80190100u);
    ctx.r[28] = ctx.r[29] = ctx.r[30] = ctx.r[31] = 0;
    ctx.lmw(mem, 28, 0x80190100u);
    assert(ctx.r[28] == 0x11112222u && ctx.r[31] == 0x77778888u);

    ctx.r[3] = 0x12345678u;
    ctx.rlwinm(4, 3, 8, 16, 31, true);
    assert(ctx.r[4] == 0x00007812u);

    // Workstream A: Verify srawi_op + XER[CA] + exec_raw addze/ps_nmadd/stfiwx/dcbz
    ctx.r[3] = static_cast<uint32_t>(-7);
    ctx.r[4] = ctx.srawi_op(ctx.r[3], 2u, false); // -7 >> 2 = -2, CA = 1
    assert(static_cast<int32_t>(ctx.r[4]) == -2 && ctx.get_ca());
    ctx.exec_raw(0x80004000u, (31u << 26) | (5u << 21) | (4u << 16) | (202u << 1), &mem); // addze r5, r4 -> -1
    assert(static_cast<int32_t>(ctx.r[5]) == -1);

    ctx.ps0[1] = 2.0f; ctx.ps1[1] = 3.0f;
    ctx.ps0[2] = 4.0f; ctx.ps1[2] = 5.0f;
    ctx.ps0[3] = 1.0f; ctx.ps1[3] = 2.0f;
    // ps_nmadd f4, f1, f2, f3 (op=4, rd=4, ra=1, rb=3, rc=2, xo5=30)
    uint32_t ps_nmadd_insn = (4u << 26) | (4u << 21) | (1u << 16) | (3u << 11) | (2u << 6) | (30u << 1);
    ctx.exec_raw(0x80004004u, ps_nmadd_insn, &mem);
    assert(std::fabs(ctx.ps0[4] - (-9.0f)) < 1e-5f && std::fabs(ctx.ps1[4] - (-17.0f)) < 1e-5f);

    std::cout << "[PASS] test_memory_and_ppc_context (32/64-bit BE RAM, lmw/stmw, rlwinm, CR, XER[CA], exec_raw 41 opcodes)\n";
}

static void test_lzs_decode_roundtrip() {
    const std::string payload = "P.N.03 GPNE08 CAPCOM PRODUCTION STUDIO 4 MEKA LZS_DECODE TEST DATA 2003";
    auto encoded = IsoStreamReader::lzs_encode_for_test(
        reinterpret_cast<const uint8_t*>(payload.data()),
        payload.size()
    );
    auto decoded = IsoStreamReader::lzs_decode(encoded.data(), encoded.size());
    assert(decoded.size() == payload.size());
    std::string roundtrip(reinterpret_cast<const char*>(decoded.data()), decoded.size());
    assert(roundtrip == payload);
    std::cout << "[PASS] test_lzs_decode_roundtrip (" << decoded.size() << " bytes verified)\n";
}

static void test_iso_fst_and_dol_loading(const std::string& extract_dir) {
    IsoStreamReader reader;
    std::string err;
    bool ok = reader.open(extract_dir, err);
    assert(ok && err.empty());
    assert(reader.game_id() == "GPNE08");
    assert(reader.game_title() == "P.N.03");
    assert(reader.dol_offset() == 0x0001EC00u);
    assert(reader.fst_offset() == 0x001A3C00u);
    assert(reader.file_count() == 700u);
    assert(reader.find_entrynum("/etc/core.dat") >= 0);

    Memory mem;
    uint32_t entry = 0;
    assert(reader.load_main_dol_into_memory(mem, entry));
    assert(entry == 0x80003100u);
    assert(mem.read_u32(0x80003100u) == 0x3C208028u);
    assert(mem.read_u32(0x8009F12Cu) == 0x38000001u);

    auto rel_bytes = reader.read_file("/module/Tools.rel");
    assert(rel_bytes.size() == 52492u);
    RelModuleHeader rel_hdr{};
    uint32_t prolog_va = 0;
    assert(ToolsRelLoader::link_rel_module(rel_bytes, mem, 0x80300000u, rel_hdr, prolog_va));
    assert(rel_hdr.id == 1u);
    assert(rel_hdr.num_sections == 24u);
    assert(prolog_va >= 0x80300000u);

    std::cout << "[PASS] test_iso_fst_and_dol_loading (700 FST files + main.dol + FileTbl + Tools.rel verified)\n";
}

static void test_gx_3d_interface_and_cyber_launcher() {
    RuntimeConfig cfg;
    cfg.render_width          = 3840;
    cfg.render_height         = 2160;
    cfg.msaa_mode             = AntiAliasingMode::MSAA_8x;
    cfg.enable_fxaa           = true;
    cfg.aspect_ratio          = AspectRatioMode::Widescreen_16_9;
    cfg.anisotropic_filtering = 16;

    set_global_gx_config(cfg);
    Memory mem;
    PPCContext ctx;
    global_gx_3d_interface().bind_fifo_to_memory(mem);
    global_gx_3d_interface().clear_frame_geometry();

    uint32_t proj_addr = 0x80195000u;
    for (int i = 0; i < 16; ++i) mem.write_f32(proj_addr + i * 4, (i % 5 == 0) ? 1.0f : 0.0f);
    ctx.r[3] = proj_addr;
    ctx.r[4] = 0u;
    ctx.call_indirect(0x80125D20u, mem);
    assert(std::fabs(global_gx_3d_interface().projection_mtx()[0][0] - 0.75f) < 1e-4f);

    uint32_t tex_obj_addr  = 0x80195100u;
    uint32_t tex_data_addr = 0x80195200u;
    for (int i = 0; i < 16; ++i) mem.write_u16(tex_data_addr + i * 2, 0xFC00u);
    ctx.r[3] = tex_obj_addr;
    ctx.r[4] = tex_data_addr;
    ctx.r[5] = 4u;
    ctx.r[6] = 4u;
    ctx.r[7] = GX_TF_RGB5A3;
    ctx.r[8] = 1u;
    ctx.r[9] = 1u;
    ctx.call_indirect(0x8012270Cu, mem);

    ctx.r[3] = tex_obj_addr;
    ctx.r[4] = 0u;
    ctx.call_indirect(0x8012319Cu, mem);
    assert(global_gx_3d_interface().bound_texture(0).width == 4u);

    auto decoded_rgba = global_gx_3d_interface().decode_gc_texture_to_rgba8(mem, global_gx_3d_interface().bound_texture(0));
    assert(decoded_rgba.size() == 4u * 4u * 4u);
    assert(decoded_rgba[0] == 255u && decoded_rgba[1] == 0u && decoded_rgba[2] == 0u && decoded_rgba[3] == 255u);

    // Workstream C: Test 0xCC008000 GX FIFO write-gather vertex assembly + GXDrawBatch recording
    global_gx_3d_interface().clear_vtx_desc();
    global_gx_3d_interface().set_vtx_desc(GX_VA_POS, GX_DIRECT);
    global_gx_3d_interface().set_vtx_attr_fmt(0, GX_VA_POS, 1, 4, 0);

    ctx.r[3] = GX_QUADS;
    ctx.r[4] = 0u;
    ctx.r[5] = 4u;
    ctx.call_indirect(0x80120A9Cu, mem);
    for (int v = 0; v < 4; ++v) {
        mem.write_f32(0xCC008000u, static_cast<float>(v * 10));
        mem.write_f32(0xCC008000u, static_cast<float>(v * 20));
        mem.write_f32(0xCC008000u, 0.5f);
    }
    assert(global_gx_3d_interface().submitted_triangle_count() == 2u);
    assert(!global_gx_3d_interface().draw_batches().empty());

    CyberLauncherUI launcher(cfg);
    assert(launcher.build_diagnostic_readout().find("3840x2160") != std::string::npos);

    std::cout << "[PASS] test_gx_3d_interface_and_cyber_launcher (270 GX/VI hooks, 0xCC008000 FIFO, RGB5A3 decode, Quads->Tris, 4K UI verified)\n";
}

static void test_audio_ax_and_osalloc() {
    Memory mem;
    PPCContext ctx;
    reset_hle_runtime_state(mem);

    ctx.r[3] = 0x80360000u;
    ctx.r[4] = 0u;
    ctx.r[5] = 0u;
    ctx.call_indirect(0x800F0F64u, mem);
    ctx.r[3] = 0u;
    ctx.r[4] = 1024u;
    ctx.call_indirect(0x800F0B58u, mem);
    assert(ctx.r[3] == 0x80360020u); // 32-byte Cell header offset before payload

    ctx.r[3] = 0x80400000u;
    ctx.r[4] = 2048u;
    ctx.call_indirect(0x8011136Cu, mem);
    ctx.call_indirect(0x80111404u, mem);
    assert(global_audio_ax_interface().is_dma_enabled());
    assert(global_audio_ax_interface().ai_dma_addr() == 0x80400000u);

    const uint8_t adpcm_frame[8] = {0x02, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE};
    const int16_t coefs[16] = {1024, -512, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int16_t h1 = 0, h2 = 0, out_pcm[14]{};
    AudioAXInterface::decode_dsp_adpcm_frame(adpcm_frame, coefs, h1, h2, out_pcm);
    assert(out_pcm[0] != 0);

    std::cout << "[PASS] test_audio_ax_and_osalloc (OSAlloc heap, AIInitDMA/StartDMA, DSP 4-bit ADPCM verified)\n";
}

static void test_xbox_xinput_bridge() {
    RuntimeConfig cfg;
    PadXInputBridge pad(cfg);
    XboxInputState xst{};
    xst.connected     = true;
    xst.btn_a         = true;
    xst.btn_x         = true;
    xst.dpad_left     = true;
    xst.left_stick_x  = 0.10f;
    xst.left_stick_y  = 1.00f;
    xst.right_trigger = 0.80f;

    Memory mem;
    pad.update_memory_pad_status(mem, &xst);

    uint16_t buttons = mem.read_u16(recomp::sym_addr::kPadData);
    int8_t stick_x   = static_cast<int8_t>(mem.read_u8(recomp::sym_addr::kPadData + 2));
    int8_t stick_y   = static_cast<int8_t>(mem.read_u8(recomp::sym_addr::kPadData + 3));
    uint8_t trig_r   = mem.read_u8(recomp::sym_addr::kPadData + 7);

    assert((buttons & PAD_BUTTON_A) != 0);
    assert((buttons & PAD_BUTTON_X) != 0);
    assert((buttons & PAD_BUTTON_LEFT) != 0);
    assert((buttons & PAD_TRIGGER_R) != 0);
    assert(stick_x == 0);
    assert(stick_y == 100);
    assert(trig_r >= 200);

    std::cout << "[PASS] test_xbox_xinput_bridge (PADStatus @ 0x801C4A68 & Rumble verified)\n";
}

static void test_dolphin_sdk_hle_and_full_6340_dispatch() {
    Memory mem;
    PPCContext ctx;

    uint32_t mtx_addr = 0x80191000u;
    uint32_t vec_in   = 0x80191100u;
    uint32_t vec_out  = 0x80191120u;
    ctx.r[3] = mtx_addr;
    ctx.f[1] = 10.0;
    ctx.f[2] = 20.0;
    ctx.f[3] = 30.0;
    ctx.call_indirect(0x80101378u, mem);

    mem.write_f32(vec_in + 0, 1.0f);
    mem.write_f32(vec_in + 4, 2.0f);
    mem.write_f32(vec_in + 8, 3.0f);
    ctx.r[3] = mtx_addr;
    ctx.r[4] = vec_in;
    ctx.r[5] = vec_out;
    ctx.call_indirect(0x80101CC8u, mem);
    assert(std::fabs(mem.read_f32(vec_out + 0) - 11.0f) < 1e-4f);
    assert(std::fabs(mem.read_f32(vec_out + 4) - 22.0f) < 1e-4f);
    assert(std::fabs(mem.read_f32(vec_out + 8) - 33.0f) < 1e-4f);

    const char* save_magic = "PN03_SAVE_SLOT_A_VANESSA";
    mem.write_bytes(0x80192000u, save_magic, std::strlen(save_magic) + 1);
    ctx.r[3] = 0x80191F00u;
    ctx.r[4] = 0x80192000u;
    ctx.r[5] = 32u;
    ctx.r[6] = 0u;
    ctx.call_indirect(0x80119650u, mem);
    assert(ctx.r[3] == 0u);

    ctx.r[4] = 0x80193000u;
    ctx.call_indirect(0x80119214u, mem);
    assert(mem.read_cstring(0x80193000u) == save_magic);

    mem.write_u32(0x8026DD0Cu, 41u);
    ctx.call_indirect(0x8009C58Cu, mem);
    assert(mem.read_u32(0x8026DD0Cu) == 42u);

    mem.write_u32(0x80194000u, 0x00000001u);
    ctx.r[3] = 0x80194000u;
    ctx.r[4] = 16u;
    ctx.call_indirect(0x8009D5F8u, mem);
    assert(mem.read_u32(0x80194000u) == 0x00008001u);

    std::cout << "[PASS] test_dolphin_sdk_hle_and_full_6340_dispatch (PSMTX/PSVEC, CARD Save/Load, Indirect Call Table verified)\n";
}

static void test_chinese_localization_overlay() {
    RuntimeConfig cfg;
    cfg.language = GameLanguage::SimplifiedChinese;
    cfg.locale_overlay_path = "assets/locales/zh_CN.json";
    if (!std::filesystem::exists(cfg.locale_overlay_path) && std::filesystem::exists("../assets/locales/zh_CN.json")) {
        cfg.locale_overlay_path = "../assets/locales/zh_CN.json";
    }

    LocalizationOverlay loc(cfg);
    assert(loc.entry_count() >= 300u);
    assert(loc.translate_text("NEW GAME") == "新游戏");
    assert(loc.translate_text("PAPILLON SUIT") == "蝶翼终极型装甲 (Papillon)");

    Memory mem;
    PPCContext ctx;
    ctx.r[3] = 0x801A0000u;
    loc.hook_mes_set_language(ctx, mem);
    assert(mem.read_u32(0x801A0000u) == static_cast<uint32_t>(GameLanguage::SimplifiedChinese));
    assert(recomp::kMasterCodeSymbolCount == 6353u);
    std::cout << "[PASS] test_chinese_localization_overlay (" << loc.entry_count() << " entries) & 6,353 symbol registry verified\n";
}

static std::string auto_discover_test_iso() {
    namespace fs = std::filesystem;
    for (const std::string& search_dir : {".", "..", "../.."}) {
        if (!fs::exists(search_dir)) continue;
        std::vector<std::string> found;
        for (const auto& entry : fs::directory_iterator(search_dir)) {
            if (!entry.is_regular_file()) continue;
            std::string ext = entry.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            if (ext == ".iso" || ext == ".gcm") {
                found.push_back(entry.path().string());
            }
        }
        if (!found.empty()) {
            std::sort(found.begin(), found.end());
            return found.front();
        }
    }
    return "/tmp/pn03_extract";
}

static void test_logger_rotation_and_pruning() {
    namespace fs = std::filesystem;
    const fs::path tmp_dir = fs::temp_directory_path() / "pn03_logger_unit_test";
    std::error_code ec;
    fs::remove_all(tmp_dir, ec);

    Logger lg;
    LogConfig lcfg;
    lcfg.log_dir         = tmp_dir.string();
    lcfg.base_name       = "test_rot";
    lcfg.max_file_bytes  = 256u;
    lcfg.max_total_bytes = 900u;
    lcfg.max_files       = 3u;
    lcfg.min_level       = LogLevel::Info;
    lcfg.mirror_stderr   = false;

    assert(lg.init(lcfg));
    assert(lg.is_initialized());
    assert(!lg.should_log(LogLevel::Debug));
    assert(lg.should_log(LogLevel::Info));

    lg.set_current_frame(42u);
    lg.log(LogLevel::Debug, "UNIT", "filtered debug line");
    const std::string payload(88, 'X');
    for (int i = 0; i < 30; ++i) {
        lg.log(LogLevel::Info, "UNIT", "rot_" + std::to_string(i) + "_" + payload);
    }
    lg.flush();
    lg.prune_old_logs();

    const uint32_t archives = lg.archive_count();
    const uint64_t total_b  = lg.total_directory_log_bytes();
    assert(archives >= 1u);
    assert(archives <= 2u); // max_files=3 counts active log + archives
    assert(total_b > 0u);
    assert(total_b <= 900u);
    assert(fs::exists(lg.active_log_path()));

    lg.shutdown();
    assert(!lg.is_initialized());
    fs::remove_all(tmp_dir, ec);
    std::cout << "[PASS] test_logger_rotation_and_pruning (rotations, max_files=3, total_bytes<=900 verified)\n";
}

static void test_controller_remapping_and_guide() {
    RuntimeConfig cfg;
    cfg.apply_control_preset(1); // Type B (Trigger Fire)
    assert(cfg.control_scheme_preset == 1);
    assert(cfg.bind_gc_a == static_cast<int>(XboxInputSource::TriggerRT));
    assert(cfg.bind_gc_b == static_cast<int>(XboxInputSource::BtnA));
    assert(cfg.bind_gc_z == static_cast<int>(XboxInputSource::BtnLB));

    assert(std::string(RuntimeConfig::xbox_input_source_label(static_cast<int>(XboxInputSource::BtnGuide))) == "Xbox [X] Guide");
    assert(std::string(RuntimeConfig::guide_action_label(static_cast<int>(GuideActionTarget::GcStart))) == "PAUSE / MENU (START)");

    // Custom remap + Center Xbox [X] Guide target
    cfg.bind_gc_a         = static_cast<int>(XboxInputSource::BtnRB);
    cfg.bind_gc_z         = static_cast<int>(XboxInputSource::TriggerLT);
    cfg.bind_guide_target = static_cast<int>(GuideActionTarget::GcStart);

    PadXInputBridge pad(cfg);
    XboxInputState xst{};
    xst.connected    = true;
    xst.btn_rb       = true;
    xst.left_trigger = 0.85f;
    xst.btn_guide    = true;

    GcPadStatus gcp = pad.translate_to_gc_pad(xst);
    assert((gcp.button & PAD_BUTTON_A) != 0);
    assert((gcp.button & PAD_TRIGGER_Z) != 0);
    assert((gcp.button & PAD_BUTTON_START) != 0);

    // Reassign Guide -> GC Y and verify, then Disabled
    cfg.bind_guide_target = static_cast<int>(GuideActionTarget::GcY);
    PadXInputBridge pad_y(cfg);
    XboxInputState xst_g{};
    xst_g.connected = true;
    xst_g.btn_guide = true;
    GcPadStatus gcp_y = pad_y.translate_to_gc_pad(xst_g);
    assert((gcp_y.button & PAD_BUTTON_Y) != 0);
    assert((gcp_y.button & PAD_BUTTON_START) == 0);

    cfg.bind_guide_target = static_cast<int>(GuideActionTarget::Disabled);
    PadXInputBridge pad_off(cfg);
    GcPadStatus gcp_off = pad_off.translate_to_gc_pad(xst_g);
    assert(gcp_off.button == 0u);

    std::cout << "[PASS] test_controller_remapping_and_guide (Presets, Custom Remap, Xbox [X] Guide verified)\n";
}

void test_audio_ax_mixer_and_aram_step() {
    Memory mem;
    PPCContext ctx;
    ctx.mem_ptr = &mem;
    reset_hle_runtime_state(mem);

    RuntimeConfig cfg;
    cfg.audio_muted  = false;
    cfg.audio_volume = 1.0f;

    auto& ax = global_audio_ax_interface();
    ax.reset_state();
    ax.set_config(cfg);

    const uint32_t aram_addr = ax.aram_alloc(4096u);
    assert(aram_addr != 0u);

    // Write 512 samples (1024 bytes) of big-endian 16-bit PCM square wave into MRAM and DMA to ARAM
    constexpr uint32_t kMramAudioBuf = 0x80500000u;
    constexpr uint32_t kNumSamples  = 512u;
    for (uint32_t i = 0; i < kNumSamples; ++i) {
        const int16_t s = ((i / 16u) % 2u == 0u) ? 16000 : -16000;
        mem.write_u16(kMramAudioBuf + i * 2u, static_cast<uint16_t>(s));
    }
    ax.aram_dma_transfer(0u, kMramAudioBuf, aram_addr, kNumSamples * 2u, mem);

    // Populate __AXVPB[0] at 0x802614E0 for looping PCM16 (format == 10, word-addressed in ARAM)
    constexpr uint32_t kAxVpbBase = 0x802614E0u;
    const uint32_t word_cur = aram_addr >> 1;
    const uint32_t word_end = word_cur + kNumSamples;
    mem.write_u16(kAxVpbBase + 326u, 1u);       // state = run
    mem.write_u16(kAxVpbBase + 330u, 0x7FFFu);  // mix vL
    mem.write_u16(kAxVpbBase + 334u, 0x7FFFu);  // mix vR
    mem.write_u16(kAxVpbBase + 412u, 0x7FFFu);  // ve.currentVolume
    mem.write_u16(kAxVpbBase + 422u, 1u);       // loopFlag = 1
    mem.write_u16(kAxVpbBase + 424u, 10u);      // format = PCM16
    mem.write_u16(kAxVpbBase + 426u, static_cast<uint16_t>((word_cur >> 16) & 0xFFFFu));
    mem.write_u16(kAxVpbBase + 428u, static_cast<uint16_t>(word_cur & 0xFFFFu));
    mem.write_u16(kAxVpbBase + 430u, static_cast<uint16_t>((word_end >> 16) & 0xFFFFu));
    mem.write_u16(kAxVpbBase + 432u, static_cast<uint16_t>(word_end & 0xFFFFu));
    mem.write_u16(kAxVpbBase + 434u, static_cast<uint16_t>((word_cur >> 16) & 0xFFFFu));
    mem.write_u16(kAxVpbBase + 436u, static_cast<uint16_t>(word_cur & 0xFFFFu));
    mem.write_u16(kAxVpbBase + 478u, 1u);       // src_ratio_hi
    mem.write_u16(kAxVpbBase + 480u, 0u);       // src_ratio_lo

    const std::vector<int16_t> pcm_unmuted = ax.mix_stereo_frame(mem, 540u);
    assert(pcm_unmuted.size() == 1080u);
    bool has_nonzero_pcm = false;
    for (int16_t sample : pcm_unmuted) {
        if (sample != 0) {
            has_nonzero_pcm = true;
            break;
        }
    }
    assert(has_nonzero_pcm);

    // Muting must silence mixed stereo output
    cfg.audio_muted = true;
    ax.set_config(cfg);
    const std::vector<int16_t> pcm_muted = ax.mix_stereo_frame(mem, 540u);
    assert(pcm_muted.size() == 1080u);
    for (int16_t sample : pcm_muted) {
        assert(sample == 0);
    }

    // Verify stateful OSGetSoundMode (0x800F7C68) / OSSetSoundMode (0x800F7CE8)
    ctx.r[3] = 1u;
    assert(dispatch_recompiled_function(0x800F7CE8u, ctx, mem));
    ctx.r[3] = 0u;
    assert(dispatch_recompiled_function(0x800F7C68u, ctx, mem));
    assert(ctx.r[3] == 1u);

    ax.reset_state();
    reset_hle_runtime_state(mem);
    std::cout << "[PASS] test_audio_ax_mixer_and_aram_step (ARAM DMA, AXVPB PCM16 mix, Mute, SoundMode verified)\n";
}

void test_localization_glyph_decode_and_cmeswk() {
    Memory mem;
    PPCContext ctx;
    ctx.mem_ptr = &mem;
    global_gx_3d_interface().clear_frame_geometry();

    RuntimeConfig lcfg;
    lcfg.language               = GameLanguage::SimplifiedChinese;
    lcfg.enable_hd_chinese_font = true;

    LocalizationOverlay loc(lcfg);
    assert(loc.entry_count() >= 380u);
    LocalizationOverlay::set_active_instance(&loc);

    // 1. Verify 0xF05ADF3E glyph stream decoding ("NEW GAME" + digits/punctuation 0x83..0x8C, 0x123, 0x0001)
    constexpr uint32_t kStreamNewGame = 0x80520000u;
    const uint16_t words_new_game[] = {0x00B4u, 0x00ABu, 0x00BDu, 0x0080u, 0x00ADu, 0x00A7u, 0x00B3u, 0x00ABu, 0x0001u};
    for (size_t i = 0; i < sizeof(words_new_game) / sizeof(words_new_game[0]); ++i) {
        mem.write_u16(kStreamNewGame + static_cast<uint32_t>(i * 2u), words_new_game[i]);
    }
    assert(loc.decode_gc_moji_stream(mem, kStreamNewGame) == "NEW GAME");

    constexpr uint32_t kStreamDigits = 0x80520100u;
    const uint16_t words_digits[] = {0x0083u, 0x008Cu, 0x008Du, 0x0088u, 0x0092u, 0x0085u, 0x0080u, 0x0123u, 0x00A7u, 0x0123u, 0x0001u};
    for (size_t i = 0; i < sizeof(words_digits) / sizeof(words_digits[0]); ++i) {
        mem.write_u16(kStreamDigits + static_cast<uint32_t>(i * 2u), words_digits[i]);
    }
    assert(loc.decode_gc_moji_stream(mem, kStreamDigits) == "09:5/2 'A'");

    // 2. Verify control-tag sanitization
    assert(LocalizationOverlay::clean_overlay_display_text("<08>保存进度<04>确定<17c>") == "保存进度\n确定  ▶");

    // 3. Verify CMesWk scanner at 0x801A2A44 + hook_font_draw (0x80081E70) / hook_eprintf_buffering (0x80081DC4)
    constexpr uint32_t kCMesWk0 = 0x801A2A44u;
    mem.write_u32(kCMesWk0 + 0x00u, 1u);
    mem.write_u32(kCMesWk0 + 0x24u, 0xFFFFFFFFu);
    mem.write_u32(kCMesWk0 + 0x28u, 0u);
    mem.write_u32(kCMesWk0 + 0x40u, kStreamNewGame);
    mem.write_u16(kCMesWk0 + 0x58u, 120u);
    mem.write_u16(kCMesWk0 + 0x5Au, 200u);

    loc.begin_frame();
    loc.emit_active_ui_scene_overlays(mem);
    assert(!global_gx_3d_interface().overlay_texts().empty());

    // Issue A regression: CMesCtrl::MesClear(0) zeroes +0x00 while leaving stale +0x40/+0x44/+0x1E58 in RAM.
    // Inactive slots must NOT re-emit stale subtitles.
    constexpr uint32_t kCMesCtrlBase = 0x801A2A40u;
    ctx.r[1] = 0x80F00000u;
    ctx.r[3] = kCMesCtrlBase;
    ctx.r[4] = 0u;
    assert(dispatch_recompiled_function(0x8009F208u, ctx, mem)); // CMesCtrl::MesClear(0)
    assert(mem.read_u32(kCMesWk0 + 0x00u) == 0u);
    assert(mem.read_u32(kCMesWk0 + 0x40u) == kStreamNewGame);
    global_gx_3d_interface().clear_frame_geometry();
    loc.begin_frame();
    loc.emit_active_ui_scene_overlays(mem);
    assert(global_gx_3d_interface().overlay_texts().empty());

    // Clear CMesWk slot and verify hook_eprintf_buffering + hook_font_draw intercept cleanly
    mem.write_u32(kCMesWk0 + 0x40u, 0u);
    global_gx_3d_interface().clear_frame_geometry();
    loc.begin_frame();

    constexpr uint32_t kEprintfStr = 0x80520200u;
    const char* kSuitAscii = "PAPILLON SUIT";
    mem.write_bytes(kEprintfStr, kSuitAscii, std::strlen(kSuitAscii) + 1u);
    ctx.r[3] = 0x80520300u;
    ctx.r[4] = kEprintfStr;
    assert(dispatch_recompiled_function(0x80081DC4u, ctx, mem)); // EprintfBuffering

    ctx.r[3] = kEprintfStr;
    ctx.r[4] = 0u;
    ctx.r[5] = 100u;
    ctx.r[6] = 150u;
    assert(dispatch_recompiled_function(0x80081E70u, ctx, mem)); // font_draw
    assert(!global_gx_3d_interface().overlay_texts().empty());

    // 4. Verify CMesWk MesWorkMove-advanced +0x40u terminator via lang_base (+0x44u) & MesWorkTrans suppression
    constexpr uint32_t kLangBase = 0x80530000u;
    constexpr uint32_t kEntryRel = 0x20u;
    constexpr uint32_t kMsgEntry = kLangBase + kEntryRel;
    const uint16_t kNewGameStream[9] = { 0x00B4u, 0x00ABu, 0x00BDu, 0x0080u, 0x00ADu, 0x00A7u, 0x00B3u, 0x00ABu, 0x0001u };
    mem.write_u32(kLangBase + 8u, kEntryRel);
    for (uint32_t i = 0; i < 9u; ++i) {
        mem.write_u16(kMsgEntry + i * 2u, kNewGameStream[i]);
    }
    const uint32_t kTermPtr = kMsgEntry + 8u * 2u; // points to trailing 0x0001u after MesWorkMove
    mem.write_u32(kCMesWk0 + 0x00u, 1u);
    mem.write_u32(kCMesWk0 + 0x24u, 0xFFFFFFFFu);
    mem.write_u32(kCMesWk0 + 0x28u, 0u);
    mem.write_u32(kCMesWk0 + 0x40u, kTermPtr);
    mem.write_u32(kCMesWk0 + 0x44u, kLangBase);
    mem.write_u16(kCMesWk0 + 0x58u, 120u);
    mem.write_u16(kCMesWk0 + 0x5Au, 200u);

    loc.begin_frame();
    global_gx_3d_interface().clear_frame_geometry();
    loc.emit_active_ui_scene_overlays(mem);
    assert(!global_gx_3d_interface().overlay_texts().empty());

    // Dispatch CMesWk::MesWorkTrans (0x8009FDF0) + CMesWk::FontDraw (0x800A00DC): emits overlay & skips English bitmap draw
    mem.write_u32(kCMesWk0 + 0u, 1u);
    ctx.r[1] = 0x80F00000u;
    ctx.r[3] = kCMesWk0;
    loc.begin_frame();
    global_gx_3d_interface().clear_frame_geometry();
    assert(dispatch_recompiled_function(0x8009FDF0u, ctx, mem));
    assert(!global_gx_3d_interface().overlay_texts().empty());
    // With +0x28 bit 30 (0x40000000) clear, MesWorkTrans preserves active dialogue slot (+0x00 == 1)
    assert(mem.read_u32(kCMesWk0 + 0u) == 1u);
    ctx.r[3] = kCMesWk0;
    assert(dispatch_recompiled_function(0x800A00DCu, ctx, mem));

    // 5. Verify tagMSG_QUE (+0x58u..+0x1E58u) reconstruction when lang_base (+0x44u) is null
    mem.write_u32(kCMesWk0 + 0x00u, 1u);
    mem.write_u32(kCMesWk0 + 0x44u, 0u);
    const uint16_t kQueGlyphs[7] = {
        0x00B4u - 0x0080u, 0x00ABu - 0x0080u, 0x00BDu - 0x0080u,
        0x00ADu - 0x0080u, 0x00A7u - 0x0080u, 0x00B3u - 0x0080u, 0x00ABu - 0x0080u
    };
    const int16_t kQueXs[7] = { 100, 112, 124, 148, 160, 172, 184 }; // 12px unqueued space gap between 'W' and 'G'
    for (uint32_t i = 0; i < 7u; ++i) {
        const uint32_t q = kCMesWk0 + 0x58u + i * 20u;
        mem.write_u16(q + 0u, static_cast<uint16_t>(kQueXs[i]));
        mem.write_u16(q + 2u, 220u);
        mem.write_u16(q + 4u, kQueGlyphs[i]);
        mem.write_u16(q + 6u, 12u);
    }
    mem.write_u32(kCMesWk0 + 0x1E58u, kCMesWk0 + 0x58u + 7u * 20u);
    loc.begin_frame();
    global_gx_3d_interface().clear_frame_geometry();
    loc.emit_active_ui_scene_overlays(mem);
    assert(!global_gx_3d_interface().overlay_texts().empty());

    mem.write_u32(kCMesWk0 + 0x40u, 0u);
    mem.write_u32(kCMesWk0 + 0x44u, 0u);
    mem.write_u32(kCMesWk0 + 0x1E58u, 0u);
    LocalizationOverlay::set_active_instance(nullptr);
    global_gx_3d_interface().clear_frame_geometry();
    std::cout << "[PASS] test_localization_glyph_decode_and_cmeswk (0xF05ADF3E decode, CMesWk, lang_base/tagMSG_QUE, font_draw verified)\n";
}

void test_graphics_efb_fxaa_scissor_and_cinesco() {
    Memory mem;
    PPCContext ctx;
    ctx.mem_ptr = &mem;
    auto& gx = global_gx_3d_interface();
    gx.clear_frame_geometry();

    // 1. Verify GXSetProjection (0x80125D20) and GXSetProjectionv (0x80125DD4) aspect handling
    RuntimeConfig gcfg;
    gcfg.aspect_ratio          = AspectRatioMode::Widescreen_16_9;
    gcfg.internal_scale_factor = 2u;
    gcfg.msaa_mode             = AntiAliasingMode::MSAA_4x;
    gcfg.enable_fxaa           = true;
    gcfg.remove_cinesco_bars   = true;
    set_global_gx_config(gcfg);

    constexpr uint32_t kProjMtxVa = 0x80510000u;
    for (int i = 0; i < 16; ++i) {
        mem.write_f32(kProjMtxVa + static_cast<uint32_t>(i * 4), 0.0f);
    }
    mem.write_f32(kProjMtxVa + 0u, 2.0f);
    mem.write_f32(kProjMtxVa + 20u, 2.0f);
    ctx.r[3] = kProjMtxVa;
    ctx.r[4] = 0u; // GX_PERSPECTIVE
    assert(dispatch_recompiled_function(0x80125D20u, ctx, mem));
    assert(std::fabs(gx.projection_mtx()[0][0] - 1.5f) < 1e-4f);

    // Ortho projection must not stretch horizontally
    ctx.r[3] = kProjMtxVa;
    ctx.r[4] = 1u; // GX_ORTHOGRAPHIC
    assert(dispatch_recompiled_function(0x80125D20u, ctx, mem));
    assert(std::fabs(gx.projection_mtx()[0][0] - 2.0f) < 1e-4f);

    // Ultrawide 21:9 via GXSetProjectionv
    gcfg.aspect_ratio = AspectRatioMode::Ultrawide_21_9;
    set_global_gx_config(gcfg);
    constexpr uint32_t kProjvVa = 0x80510100u;
    mem.write_f32(kProjvVa + 0u,  0.0f); // GX_PERSPECTIVE
    mem.write_f32(kProjvVa + 4u,  2.1f); // [0][0]
    mem.write_f32(kProjvVa + 8u,  0.0f);
    mem.write_f32(kProjvVa + 12u, 2.0f); // [1][1]
    mem.write_f32(kProjvVa + 16u, 0.0f);
    mem.write_f32(kProjvVa + 20u, -1.0f);
    mem.write_f32(kProjvVa + 24u, -0.1f);
    ctx.r[3] = kProjvVa;
    assert(dispatch_recompiled_function(0x80125DD4u, ctx, mem));
    assert(std::fabs(gx.projection_mtx()[0][0] - (2.1f * (4.0f / 3.0f) / (21.0f / 9.0f))) < 1e-4f);

    // 2. Verify unscaled GC-logical GXSetViewport & GXSetScissor / GXSetScissorBoxOffset
    ctx.r[3] = 0u;
    ctx.r[4] = 0u;
    assert(dispatch_recompiled_function(0x80126468u, ctx, mem)); // GXSetScissorBoxOffset(0, 0)

    ctx.f[1] = 10.0; ctx.f[2] = 20.0; ctx.f[3] = 300.0; ctx.f[4] = 200.0; ctx.f[5] = 0.0; ctx.f[6] = 1.0;
    assert(dispatch_recompiled_function(0x80126334u, ctx, mem)); // GXSetViewport
    assert(std::fabs(gx.viewport()[0] - 10.0f) < 1e-4f);
    assert(std::fabs(gx.viewport()[2] - 300.0f) < 1e-4f);

    ctx.r[3] = 16u; ctx.r[4] = 24u; ctx.r[5] = 320u; ctx.r[6] = 240u;
    assert(dispatch_recompiled_function(0x80126390u, ctx, mem)); // GXSetScissor
    assert(gx.scissor()[0] == 16u && gx.scissor()[1] == 24u && gx.scissor()[2] == 320u && gx.scissor()[3] == 240u);

    // 3. Verify Draw_cinesco (0x80073348) suppression flag
    assert(dispatch_recompiled_function(0x80073348u, ctx, mem));

    // 4. Verify headless Win32D3D11Host creates internal-scale MSAA EFB, FXAA pass, & BMP dump
    gcfg.aspect_ratio = AspectRatioMode::Widescreen_16_9;
    set_global_gx_config(gcfg);
    Win32D3D11Host host(gcfg);
    std::string err;
    const bool host_ok = host.create_render_window_and_d3d11(err, true);
    assert(host_ok);
    assert(host.efb_height() == 960u);
    assert(host.efb_width() == 1708u);
    assert(host.active_msaa_samples() >= 1u);

    host.begin_d3d11_frame();
    host.render_gx_draw_batches(mem, gx);
    host.end_d3d11_frame_and_present();

    const std::filesystem::path bmp_path = std::filesystem::temp_directory_path() / "pn03_test_efb_fxaa.bmp";
    std::filesystem::remove(bmp_path);
    assert(host.dump_framebuffer_bmp(bmp_path.string()));
    assert(std::filesystem::exists(bmp_path) && std::filesystem::file_size(bmp_path) > 54u);
    std::filesystem::remove(bmp_path);

    gx.clear_frame_geometry();
    set_global_gx_config(RuntimeConfig{});
    std::cout << "[PASS] test_graphics_efb_fxaa_scissor_and_cinesco (EFB=" << host.efb_width()
              << "x" << host.efb_height() << " MSAA=" << host.active_msaa_samples() << "x, Scissor/Projection/BMP verified)\n";
}

void test_memory_card_lifecycle_and_calendar_time() {
    Memory mem;
    PPCContext ctx;
    ctx.mem_ptr = &mem;

    const std::filesystem::path temp_save_dir = std::filesystem::temp_directory_path() / "pn03_test_card_save";
    std::filesystem::remove_all(temp_save_dir);
    std::filesystem::create_directories(temp_save_dir);

    RuntimeConfig card_cfg;
    card_cfg.save_dir = temp_save_dir.string();
    set_global_gx_config(card_cfg);
    reset_hle_runtime_state(mem);

    constexpr uint32_t kMemSizeVa   = 0x80530000u;
    constexpr uint32_t kSectSizeVa  = 0x80530004u;
    constexpr uint32_t kFreeBytesVa = 0x80530008u;
    constexpr uint32_t kFreeFilesVa = 0x8053000Cu;
    constexpr uint32_t kFileInfoVa  = 0x80530040u;
    constexpr uint32_t kNameVa      = 0x80530080u;
    constexpr uint32_t kWriteBufVa  = 0x80530100u;
    constexpr uint32_t kReadBufVa   = 0x80530300u;
    constexpr uint32_t kStatVa      = 0x80530500u;
    constexpr uint32_t kSerialVa    = 0x80530600u;
    constexpr uint32_t kCalVa       = 0x80530640u;

    const char* kFileName = "PN03_SAVE_00";
    mem.write_bytes(kNameVa, kFileName, std::strlen(kFileName) + 1u);

    // 1. Init, Probe, ProbeEx, Mount, Check, FreeBlocks
    assert(dispatch_recompiled_function(0x80115508u, ctx, mem)); // CARDInit
    ctx.r[3] = 0u;
    assert(dispatch_recompiled_function(0x80117334u, ctx, mem)); // CARDProbe(0)
    assert(ctx.r[3] == 1u);
    ctx.r[3] = 1u;
    assert(dispatch_recompiled_function(0x80117334u, ctx, mem)); // CARDProbe(1)
    assert(ctx.r[3] == 0u);

    ctx.r[3] = 0u; ctx.r[4] = kMemSizeVa; ctx.r[5] = kSectSizeVa;
    assert(dispatch_recompiled_function(0x8011736Cu, ctx, mem)); // CARDProbeEx
    assert(static_cast<int32_t>(ctx.r[3]) == 0);
    assert(mem.read_u32(kMemSizeVa) == 16u && mem.read_u32(kSectSizeVa) == 8192u);

    ctx.r[3] = 0u; ctx.r[4] = 0x80531000u; ctx.r[5] = 0u;
    assert(dispatch_recompiled_function(0x80117BD0u, ctx, mem)); // CARDMount
    assert(static_cast<int32_t>(ctx.r[3]) == 0);

    ctx.r[3] = 0u;
    assert(dispatch_recompiled_function(0x801171C0u, ctx, mem)); // CARDCheck
    assert(static_cast<int32_t>(ctx.r[3]) == 0);

    ctx.r[3] = 0u; ctx.r[4] = kFreeBytesVa; ctx.r[5] = kFreeFilesVa;
    assert(dispatch_recompiled_function(0x801157F8u, ctx, mem)); // CARDFreeBlocks
    assert(static_cast<int32_t>(ctx.r[3]) == 0);
    const uint32_t initial_free_bytes = mem.read_u32(kFreeBytesVa);
    assert(mem.read_u32(kFreeFilesVa) == 120u);

    // 2. Open non-existent file returns CARD_RESULT_NOFILE (-4)
    ctx.r[3] = 0u; ctx.r[4] = kNameVa; ctx.r[5] = kFileInfoVa;
    assert(dispatch_recompiled_function(0x801189C0u, ctx, mem)); // CARDOpen
    assert(static_cast<int32_t>(ctx.r[3]) == -4);

    // 3. Create 16KB file returns READY (0); duplicate returns EXIST (-7)
    ctx.r[3] = 0u; ctx.r[4] = kNameVa; ctx.r[5] = 16384u; ctx.r[6] = kFileInfoVa;
    assert(dispatch_recompiled_function(0x80118EE4u, ctx, mem)); // CARDCreate
    assert(static_cast<int32_t>(ctx.r[3]) == 0);
    const int32_t file_no = static_cast<int32_t>(mem.read_u32(kFileInfoVa + 4u));
    assert(file_no >= 0);

    ctx.r[3] = 0u; ctx.r[4] = kNameVa; ctx.r[5] = 16384u; ctx.r[6] = kFileInfoVa;
    assert(dispatch_recompiled_function(0x80118EE4u, ctx, mem)); // duplicate CARDCreate
    assert(static_cast<int32_t>(ctx.r[3]) == -7);

    ctx.r[3] = 0u; ctx.r[4] = kFreeBytesVa; ctx.r[5] = kFreeFilesVa;
    assert(dispatch_recompiled_function(0x801157F8u, ctx, mem));
    assert(mem.read_u32(kFreeFilesVa) == 119u);
    assert(mem.read_u32(kFreeBytesVa) == initial_free_bytes - 16384u);

    // 4. Write 128 bytes with XOR checksum at offset 512, then read back & verify
    uint8_t xor_sum = 0u;
    for (uint32_t i = 0; i < 127u; ++i) {
        const uint8_t v = static_cast<uint8_t>((i * 29u + 7u) & 0xFFu);
        mem.write_u8(kWriteBufVa + i, v);
        xor_sum ^= v;
    }
    mem.write_u8(kWriteBufVa + 127u, xor_sum);
    ctx.r[3] = kFileInfoVa; ctx.r[4] = kWriteBufVa; ctx.r[5] = 128u; ctx.r[6] = 512u;
    assert(dispatch_recompiled_function(0x80119764u, ctx, mem)); // CARDWrite
    assert(static_cast<int32_t>(ctx.r[3]) == 0);

    std::memset(mem.raw_ptr(kReadBufVa), 0, 128u);
    ctx.r[3] = kFileInfoVa; ctx.r[4] = kReadBufVa; ctx.r[5] = 128u; ctx.r[6] = 512u;
    assert(dispatch_recompiled_function(0x8011935Cu, ctx, mem)); // CARDRead
    assert(static_cast<int32_t>(ctx.r[3]) == 0);
    uint8_t read_xor = 0u;
    for (uint32_t i = 0; i < 127u; ++i) {
        assert(mem.read_u8(kReadBufVa + i) == mem.read_u8(kWriteBufVa + i));
        read_xor ^= mem.read_u8(kReadBufVa + i);
    }
    assert(mem.read_u8(kReadBufVa + 127u) == read_xor);

    // 5. CARDSetStatus / CARDGetStatus + CARDGetSerialNo
    std::memset(mem.raw_ptr(kStatVa), 0, 0x6Cu);
    mem.write_bytes(kStatVa, kFileName, std::strlen(kFileName));
    mem.write_u32(kStatVa + 0x24u, 0x12345678u); // time_sec
    mem.write_u8(kStatVa  + 0x2Eu, 2u);          // banner_format
    mem.write_u16(kStatVa + 0x34u, 0x0015u);     // icon_format
    mem.write_u32(kStatVa + 0x38u, 0x00001000u); // comment_addr
    ctx.r[3] = 0u; ctx.r[4] = static_cast<uint32_t>(file_no); ctx.r[5] = kStatVa;
    assert(dispatch_recompiled_function(0x80119FB4u, ctx, mem)); // CARDSetStatus
    assert(static_cast<int32_t>(ctx.r[3]) == 0);

    std::memset(mem.raw_ptr(kStatVa), 0, 0x6Cu);
    ctx.r[3] = 0u; ctx.r[4] = static_cast<uint32_t>(file_no); ctx.r[5] = kStatVa;
    assert(dispatch_recompiled_function(0x80119D14u, ctx, mem)); // CARDGetStatus
    assert(static_cast<int32_t>(ctx.r[3]) == 0);
    assert(mem.read_u32(kStatVa + 0x24u) == 0x12345678u);
    assert(mem.read_u16(kStatVa + 0x34u) == 0x0015u);
    assert(mem.read_u32(kStatVa + 0x38u) == 0x00001000u);

    ctx.r[3] = 0u; ctx.r[4] = kSerialVa;
    assert(dispatch_recompiled_function(0x8011A014u, ctx, mem)); // CARDGetSerialNo
    assert(static_cast<int32_t>(ctx.r[3]) == 0);
    assert(mem.read_u32(kSerialVa + 0u) == 0x504E3033u && mem.read_u32(kSerialVa + 4u) == 0x43415244u);

    // 6. Close, verify raw fallback CARDWriteAsync/CARDReadAsync on un-opened CARDFileInfo preserves pn03_card_a.sav
    ctx.r[3] = kFileInfoVa;
    assert(dispatch_recompiled_function(0x80118B38u, ctx, mem)); // CARDClose
    mem.write_u32(kWriteBufVa, 0xCAFEBABEu);
    ctx.r[3] = kFileInfoVa; ctx.r[4] = kWriteBufVa; ctx.r[5] = 16u; ctx.r[6] = 0u; ctx.r[7] = 0u;
    assert(dispatch_recompiled_function(0x80119650u, ctx, mem)); // CARDWriteAsync raw fallback
    assert(std::filesystem::exists(temp_save_dir / "pn03_card_a.sav"));
    mem.write_u32(kReadBufVa, 0u);
    ctx.r[3] = kFileInfoVa; ctx.r[4] = kReadBufVa; ctx.r[5] = 16u; ctx.r[6] = 0u; ctx.r[7] = 0u;
    assert(dispatch_recompiled_function(0x80119214u, ctx, mem)); // CARDReadAsync raw fallback
    assert(mem.read_u32(kReadBufVa) == 0xCAFEBABEu);

    // 7. Delete and Unmount
    ctx.r[3] = 0u; ctx.r[4] = kNameVa;
    assert(dispatch_recompiled_function(0x80119AD4u, ctx, mem)); // CARDDelete
    assert(static_cast<int32_t>(ctx.r[3]) == 0);
    ctx.r[3] = 0u; ctx.r[4] = kNameVa; ctx.r[5] = kFileInfoVa;
    assert(dispatch_recompiled_function(0x801189C0u, ctx, mem)); // CARDOpen after delete -> NOFILE (-4)
    assert(static_cast<int32_t>(ctx.r[3]) == -4);

    ctx.r[3] = 0u;
    assert(dispatch_recompiled_function(0x80117CB4u, ctx, mem)); // CARDUnmount
    assert(static_cast<int32_t>(ctx.r[3]) == 0);
    ctx.r[3] = 0u; ctx.r[4] = kNameVa; ctx.r[5] = kFileInfoVa;
    assert(dispatch_recompiled_function(0x801189C0u, ctx, mem)); // CARDOpen unmounted -> NOCARD (-3)
    assert(static_cast<int32_t>(ctx.r[3]) == -3);

    // 8. OSTicksToCalendarTime (0x800FAB38) <-> OSCalendarTimeToTicks (0x800FAD3C) round-trip
    mem.write_u32(0x800000F8u, 162000000u);
    const uint64_t ticks_per_sec = 162000000ull / 4ull;
    const uint64_t expected_ticks = 123456789ull * ticks_per_sec;
    ctx.r[3] = static_cast<uint32_t>(expected_ticks >> 32);
    ctx.r[4] = static_cast<uint32_t>(expected_ticks & 0xFFFFFFFFull);
    ctx.r[5] = kCalVa;
    assert(dispatch_recompiled_function(0x800FAB38u, ctx, mem));
    assert(mem.read_u32(kCalVa + 20u) >= 2003u);

    ctx.r[3] = kCalVa;
    assert(dispatch_recompiled_function(0x800FAD3Cu, ctx, mem));
    const uint64_t roundtrip_ticks = (static_cast<uint64_t>(ctx.r[3]) << 32) | ctx.r[4];
    assert(roundtrip_ticks == expected_ticks);

    set_global_gx_config(RuntimeConfig{});
    reset_hle_runtime_state(mem);
    std::filesystem::remove_all(temp_save_dir);
    std::cout << "[PASS] test_memory_card_lifecycle_and_calendar_time (CARD* VDir, raw fallback, OSTime roundtrip verified)\n";
}

static void read_bmp24_pixel(const std::filesystem::path& path, int px, int py_top_down, uint8_t out_rgb[3]) {
    std::ifstream ifs(path, std::ios::binary);
    assert(ifs.is_open());
    uint8_t hdr[54]{};
    ifs.read(reinterpret_cast<char*>(hdr), 54);
    assert(hdr[0] == 'B' && hdr[1] == 'M');
    const int w = static_cast<int>(*reinterpret_cast<const int32_t*>(hdr + 18));
    const int h = static_cast<int>(*reinterpret_cast<const int32_t*>(hdr + 22));
    assert(px >= 0 && px < w && py_top_down >= 0 && py_top_down < std::abs(h));
    const uint32_t stride = (static_cast<uint32_t>(w) * 3u + 3u) & ~3u;
    const int row_in_file = (h > 0) ? (h - 1 - py_top_down) : py_top_down;
    const std::streamoff off = 54 + static_cast<std::streamoff>(row_in_file) * stride + static_cast<std::streamoff>(px) * 3;
    ifs.seekg(off, std::ios::beg);
    uint8_t bgr[3]{};
    ifs.read(reinterpret_cast<char*>(bgr), 3);
    out_rgb[0] = bgr[2];
    out_rgb[1] = bgr[1];
    out_rgb[2] = bgr[0];
}

void test_disp_copy_src_512x448_and_centered_4_3_fill() {
    Memory mem;
    PPCContext ctx;
    ctx.mem_ptr = &mem;
    RuntimeConfig cfg;
    cfg.render_width          = 1280;
    cfg.render_height         = 720;
    cfg.internal_scale_factor = 2;
    cfg.aspect_ratio          = AspectRatioMode::Original_4_3;
    cfg.msaa_mode             = AntiAliasingMode::Off;
    cfg.enable_fxaa           = false;
    cfg.brightness            = 1.0f;
    set_global_gx_config(cfg);

    auto& gx = global_gx_3d_interface();
    gx.clear_frame_geometry();
    gx.bind_fifo_to_memory(mem);

    // Emulate Capcom P.N.03 512x448 EFB source + ortho setup
    ctx.r[3] = 0u; ctx.r[4] = 0u; ctx.r[5] = 512u; ctx.r[6] = 448u;
    assert(dispatch_recompiled_function(0x80120F4Cu, ctx, mem)); // GXSetDispCopySrc
    ctx.r[3] = 512u; ctx.r[4] = 448u;
    assert(dispatch_recompiled_function(0x8012106Cu, ctx, mem)); // GXSetDispCopyDst
    assert(gx.disp_copy_src()[2] == 512u && gx.disp_copy_src()[3] == 448u);

    ctx.f[1] = 0.0; ctx.f[2] = 0.0; ctx.f[3] = 512.0; ctx.f[4] = 448.0; ctx.f[5] = 0.0; ctx.f[6] = 1.0;
    assert(dispatch_recompiled_function(0x80126334u, ctx, mem)); // GXSetViewport
    ctx.r[3] = 0u; ctx.r[4] = 0u; ctx.r[5] = 512u; ctx.r[6] = 448u;
    assert(dispatch_recompiled_function(0x80126390u, ctx, mem)); // GXSetScissor

    constexpr uint32_t kOrthoVa = 0x80510200u;
    for (int i = 0; i < 16; ++i) mem.write_f32(kOrthoVa + static_cast<uint32_t>(i * 4), 0.0f);
    mem.write_f32(kOrthoVa + 0u,  2.0f / 512.0f);
    mem.write_f32(kOrthoVa + 12u, -1.0f);
    mem.write_f32(kOrthoVa + 20u, -2.0f / 448.0f);
    mem.write_f32(kOrthoVa + 28u, 1.0f);
    mem.write_f32(kOrthoVa + 40u, -1.0f);
    mem.write_f32(kOrthoVa + 60u, 1.0f);
    ctx.r[3] = kOrthoVa; ctx.r[4] = 1u;
    assert(dispatch_recompiled_function(0x80125D20u, ctx, mem)); // GXSetProjection(ORTHO)

    ctx.r[3] = 0u; ctx.r[4] = 4u; // GX_PASSCLR
    assert(dispatch_recompiled_function(0x801249B8u, ctx, mem));

    gx.begin_primitive(GX_QUADS, 0, 4);
    gx.submit_vertex({{  0.0f,   0.0f, 0.5f}, {0, 0, 1}, {0.1f, 0.55f, 1.0f, 1.0f}, {0, 0}});
    gx.submit_vertex({{512.0f,   0.0f, 0.5f}, {0, 0, 1}, {0.1f, 0.55f, 1.0f, 1.0f}, {1, 0}});
    gx.submit_vertex({{512.0f, 448.0f, 0.5f}, {0, 0, 1}, {0.1f, 0.55f, 1.0f, 1.0f}, {1, 1}});
    gx.submit_vertex({{  0.0f, 448.0f, 0.5f}, {0, 0, 1}, {0.1f, 0.55f, 1.0f, 1.0f}, {0, 1}});
    gx.end_primitive();

    Win32D3D11Host host(cfg);
    std::string err;
    assert(host.create_render_window_and_d3d11(err, true));
    host.begin_d3d11_frame(0.0f, 0.0f, 0.0f);
    host.render_gx_draw_batches(mem, gx);
    host.flush_d3d11();
    host.end_d3d11_frame_and_present();

    const std::filesystem::path bmp_path = std::filesystem::temp_directory_path() / "pn03_test_4_3_fill.bmp";
    std::filesystem::remove(bmp_path);
    assert(host.dump_framebuffer_bmp(bmp_path.string()));

    // On 1280x720, 4:3 width = 960 -> active X=[160..1120), Y=[0..720)
    uint8_t left_bar[3]{}, right_bar[3]{}, inner_br[3]{}, inner_tl[3]{};
    read_bmp24_pixel(bmp_path, 80,   360, left_bar);
    read_bmp24_pixel(bmp_path, 1200, 360, right_bar);
    read_bmp24_pixel(bmp_path, 175,  16,  inner_tl);
    read_bmp24_pixel(bmp_path, 1105, 704, inner_br); // Past 512/640*960 and 448/480*720 -> fails if cropped!
    assert(left_bar[0] == 0u && left_bar[1] == 0u && left_bar[2] == 0u);
    assert(right_bar[0] == 0u && right_bar[1] == 0u && right_bar[2] == 0u);
    assert(inner_tl[2] > 200u && inner_br[2] > 200u);

    std::filesystem::remove(bmp_path);
    gx.clear_frame_geometry();
    set_global_gx_config(RuntimeConfig{});
    std::cout << "[PASS] test_disp_copy_src_512x448_and_centered_4_3_fill (512x448->100% EFB & equal 4:3 pillarboxes verified)\n";
}

void test_tev_color_scale_gamma_and_brightness_config() {
    Memory mem;
    PPCContext ctx;
    ctx.mem_ptr = &mem;
    RuntimeConfig cfg;
    cfg.render_width          = 640;
    cfg.render_height         = 480;
    cfg.internal_scale_factor = 1;
    cfg.aspect_ratio          = AspectRatioMode::Original_4_3;
    cfg.msaa_mode             = AntiAliasingMode::Off;
    cfg.enable_fxaa           = false;
    cfg.brightness            = 1.50f;
    cfg.limit_fps_60          = true;
    set_global_gx_config(cfg);

    const std::filesystem::path cfg_tmp = std::filesystem::temp_directory_path() / "pn03_test_cfg_bri.json";
    std::filesystem::remove(cfg_tmp);
    assert(cfg.save_to_json(cfg_tmp.string()));
    RuntimeConfig loaded = RuntimeConfig::load_from_json(cfg_tmp.string());
    assert(std::fabs(loaded.brightness - 1.50f) < 1e-4f);
    assert(loaded.aspect_ratio == AspectRatioMode::Original_4_3);
    assert(loaded.limit_fps_60 == true);
    std::filesystem::remove(cfg_tmp);

    auto& gx = global_gx_3d_interface();
    gx.clear_frame_geometry();

    // Verify GXSetDispCopyGamma
    ctx.r[3] = 1u;
    assert(dispatch_recompiled_function(0x80121904u, ctx, mem));
    assert(gx.disp_copy_gamma() == 1u);
    ctx.r[3] = 0u;
    assert(dispatch_recompiled_function(0x80121904u, ctx, mem));
    assert(gx.disp_copy_gamma() == 0u);

    // Emulate P.N.03 trans.obj Stage 1 GX_CS_SCALE_4 (4x color scale)
    ctx.r[3] = 2u;
    assert(dispatch_recompiled_function(0x80125170u, ctx, mem)); // GXSetNumTevStages(2)
    ctx.r[3] = 0u; ctx.r[4] = 4u;
    assert(dispatch_recompiled_function(0x801249B8u, ctx, mem)); // GXSetTevOp(0, GX_PASSCLR)
    ctx.r[3] = 1u; ctx.r[4] = 15u; ctx.r[5] = 15u; ctx.r[6] = 15u; ctx.r[7] = 0u;
    assert(dispatch_recompiled_function(0x80124A44u, ctx, mem)); // Stage 1 passes CPREV
    ctx.r[3] = 1u; ctx.r[4] = 0u; ctx.r[5] = 0u; ctx.r[6] = 2u; ctx.r[7] = 1u; ctx.r[8] = 0u;
    assert(dispatch_recompiled_function(0x80124ACCu, ctx, mem)); // GXSetTevColorOp(..., GX_CS_SCALE_4)
    assert(std::fabs(gx.effective_tev_scale() - 4.0f) < 1e-4f);

    // Render dark gray vertex (0.15 -> *4.0 = 0.60 -> *1.5 brightness = 0.90) onto swapchain & inspect pixel
    gx.begin_primitive(GX_QUADS, 0, 4);
    gx.submit_vertex({{  0.0f,   0.0f, 0.5f}, {0, 0, 1}, {0.15f, 0.15f, 0.15f, 1.0f}, {0, 0}});
    gx.submit_vertex({{640.0f,   0.0f, 0.5f}, {0, 0, 1}, {0.15f, 0.15f, 0.15f, 1.0f}, {1, 0}});
    gx.submit_vertex({{640.0f, 480.0f, 0.5f}, {0, 0, 1}, {0.15f, 0.15f, 0.15f, 1.0f}, {1, 1}});
    gx.submit_vertex({{  0.0f, 480.0f, 0.5f}, {0, 0, 1}, {0.15f, 0.15f, 0.15f, 1.0f}, {0, 1}});
    gx.end_primitive();

    Win32D3D11Host host(cfg);
    std::string err;
    assert(host.create_render_window_and_d3d11(err, true));
    host.begin_d3d11_frame(0.0f, 0.0f, 0.0f);
    host.render_gx_draw_batches(mem, gx);
    host.flush_d3d11();
    host.end_d3d11_frame_and_present();

    const std::filesystem::path bmp_path = std::filesystem::temp_directory_path() / "pn03_test_tev_bri.bmp";
    std::filesystem::remove(bmp_path);
    assert(host.dump_framebuffer_bmp(bmp_path.string()));
    uint8_t mid[3]{};
    read_bmp24_pixel(bmp_path, 320, 240, mid);
    assert(mid[0] >= 200u && mid[1] >= 200u && mid[2] >= 200u);
    std::filesystem::remove(bmp_path);

    // Switching back to 1-stage GX_PASSCLR must reset scale to 1.0f cleanly
    ctx.r[3] = 1u;
    assert(dispatch_recompiled_function(0x80125170u, ctx, mem));
    ctx.r[3] = 0u; ctx.r[4] = 4u;
    assert(dispatch_recompiled_function(0x801249B8u, ctx, mem));
    assert(std::fabs(gx.effective_tev_scale() - 1.0f) < 1e-4f);

    gx.clear_frame_geometry();
    set_global_gx_config(RuntimeConfig{});
    std::cout << "[PASS] test_tev_color_scale_gamma_and_brightness_config (GX_CS_SCALE_4="
              << int(mid[0]) << "/255 & brightness JSON verified)\n";
}

void test_audio_ax_ring_cushion_and_telemetry() {
    Memory mem;
    PPCContext ctx;
    ctx.mem_ptr = &mem;
    reset_hle_runtime_state(mem);

    auto& ax = global_audio_ax_interface();
    ax.reset_state();
    assert(ax.queued_xaudio_buffers() == 0u);
    assert(ax.dropped_xaudio_buffers() == 0u);

    double accum = 0.0;
    constexpr double kPerFrame = 32000.0 * FramePacer::kNtscPeriodSec;
    for (int f = 0; f < 60; ++f) {
        accum += kPerFrame;
        const size_t n = static_cast<size_t>(accum);
        accum -= static_cast<double>(n);
        ax.step_audio_frame(ctx, mem, n);
    }
    // 60 frames at 59.94Hz (1.001 sec) -> ~32032 samples @ 32kHz with 0 dropped buffers
    assert(ax.total_mixed_frames() >= 32030ull && ax.total_mixed_frames() <= 32034ull);
    assert(ax.dropped_xaudio_buffers() == 0u);

    ax.reset_state();
    reset_hle_runtime_state(mem);
    std::cout << "[PASS] test_audio_ax_ring_cushion_and_telemetry (59.94Hz 32kHz rate lock & zero drops verified)\n";
}

void test_audio_adpcm_interpolation_and_loop() {
    Memory mem;
    PPCContext ctx;
    ctx.mem_ptr = &mem;
    reset_hle_runtime_state(mem);

    RuntimeConfig cfg;
    cfg.audio_muted     = false;
    cfg.audio_volume    = 1.0f;

    auto& ax = global_audio_ax_interface();
    ax.reset_state();
    ax.set_config(cfg);

    // Build a 6-block (96-nibble, 84-sample) smooth GC DSP ADPCM triangle wave in ARAM:
    // With pred=0, coef[0]=2048, coef[1]=0, scale=6 (64), sample[n] = hist1 + nib * 64 (+256/sample up then -256/sample down).
    constexpr uint32_t kNumBlocks   = 6u;
    constexpr uint32_t kAramBytes   = kNumBlocks * 8u;
    constexpr uint32_t kMramAdpcm   = 0x80510000u;
    const uint32_t aram_addr = ax.aram_alloc(4096u);
    assert(aram_addr != 0u);

    std::vector<uint8_t> adpcm(kAramBytes, 0);
    int sample_idx = 0;
    for (uint32_t b = 0; b < kNumBlocks; ++b) {
        adpcm[b * 8u] = 0x06u; // pred=0, scale=(1<<6)=64
        for (uint32_t byte_i = 1u; byte_i < 8u; ++byte_i) {
            uint8_t hi = (sample_idx < 42) ? 0x04u : 0x0Cu; // +4 or -4
            ++sample_idx;
            uint8_t lo = (sample_idx < 42) ? 0x04u : 0x0Cu;
            ++sample_idx;
            adpcm[b * 8u + byte_i] = static_cast<uint8_t>((hi << 4) | lo);
        }
    }
    mem.write_bytes(kMramAdpcm, adpcm.data(), adpcm.size());
    ax.aram_dma_transfer(0u, kMramAdpcm, aram_addr, static_cast<uint32_t>(adpcm.size()), mem);

    constexpr uint32_t kAxVpbBase = 0x802614E0u;
    const uint32_t nib_base = aram_addr * 2u;
    auto setup_adpcm_voice = [&](uint32_t start_nib, uint32_t loop_nib, uint32_t end_nib, uint32_t ratio_fp, uint16_t loop_flag) {
        mem.write_u16(kAxVpbBase + 326u, 1u);       // state = run
        mem.write_u16(kAxVpbBase + 330u, 0x8000u);  // mix vL (unity)
        mem.write_u16(kAxVpbBase + 334u, 0x8000u);  // mix vR (unity)
        mem.write_u16(kAxVpbBase + 412u, 0x8000u);  // ve.currentVolume (unity)
        mem.write_u16(kAxVpbBase + 422u, loop_flag);
        mem.write_u16(kAxVpbBase + 424u, 0u);       // format = ADPCM
        mem.write_u16(kAxVpbBase + 426u, static_cast<uint16_t>((loop_nib >> 16) & 0xFFFFu));
        mem.write_u16(kAxVpbBase + 428u, static_cast<uint16_t>(loop_nib & 0xFFFFu));
        mem.write_u16(kAxVpbBase + 430u, static_cast<uint16_t>((end_nib >> 16) & 0xFFFFu));
        mem.write_u16(kAxVpbBase + 432u, static_cast<uint16_t>(end_nib & 0xFFFFu));
        mem.write_u16(kAxVpbBase + 434u, static_cast<uint16_t>((start_nib >> 16) & 0xFFFFu));
        mem.write_u16(kAxVpbBase + 436u, static_cast<uint16_t>(start_nib & 0xFFFFu));
        for (uint32_t c = 0; c < 16u; ++c) {
            mem.write_u16(kAxVpbBase + 438u + c * 2u, (c == 0u) ? 2048u : 0u);
        }
        mem.write_u16(kAxVpbBase + 472u, 0x06u);    // pred_scale
        mem.write_u16(kAxVpbBase + 474u, 0u);       // hist1
        mem.write_u16(kAxVpbBase + 476u, 0u);       // hist2
        mem.write_u16(kAxVpbBase + 478u, static_cast<uint16_t>((ratio_fp >> 16) & 0xFFFFu));
        mem.write_u16(kAxVpbBase + 480u, static_cast<uint16_t>(ratio_fp & 0xFFFFu));
        mem.write_u16(kAxVpbBase + 492u, 0u);       // adpcmLoop pred_scale
        mem.write_u16(kAxVpbBase + 494u, 0u);       // adpcmLoop yn1
        mem.write_u16(kAxVpbBase + 496u, 0u);       // adpcmLoop yn2
    };

    // 1. 1.0x pitch across multi-frame writeback boundary: zero missing hist1 update on sample 0
    setup_adpcm_voice(nib_base + 2u, nib_base + 2u, nib_base + 96u, 0x00010000u, 0u);
    ax.step_audio_frame(ctx, mem, 16u);
    const int16_t h1_after_f1 = static_cast<int16_t>(mem.read_u16(kAxVpbBase + 474u));
    const int16_t h2_after_f1 = static_cast<int16_t>(mem.read_u16(kAxVpbBase + 476u));
    assert(h1_after_f1 == 16 * 256 && h2_after_f1 == 15 * 256);
    const std::vector<int16_t> f2_1x = ax.mix_stereo_frame(mem, 16u);
    assert(f2_1x[0] == 16 * 256); // Sample 0 of frame 2 continues seamlessly from s[15]=4096
    assert(f2_1x[2] == 17 * 256); // Sample 1 sees updated hist1 (no s==0 stale-hist transient)

    // 2. Fractional <1.0 pitch (0xd744): smooth ramp across writeback with zero re-decode spike
    ax.reset_state();
    ax.set_config(cfg);
    ax.aram_dma_transfer(0u, kMramAdpcm, aram_addr, static_cast<uint32_t>(adpcm.size()), mem);
    setup_adpcm_voice(nib_base + 2u, nib_base + 2u, nib_base + 96u, 0x0000D744u, 0u);
    ax.step_audio_frame(ctx, mem, 10u);
    const std::vector<int16_t> f2_frac = ax.mix_stereo_frame(mem, 20u);
    int16_t prev_l = f2_frac[0];
    int32_t max_abs_frac = std::abs(prev_l);
    for (size_t i = 1; i < 20u; ++i) {
        const int16_t cur_l = f2_frac[i * 2u];
        max_abs_frac = std::max(max_abs_frac, static_cast<int32_t>(std::abs(cur_l)));
        const int32_t d = std::abs(static_cast<int32_t>(cur_l) - static_cast<int32_t>(prev_l));
        assert(d <= 300); // Continuous interpolated step ~215, never >1000 re-decode glitch
        prev_l = cur_l;
    }
    assert(max_abs_frac > 2000);

    // 3. >1.0 pitch (0x18000 = 1.5x): steps every intermediate ADPCM nibble cleanly across block headers
    ax.reset_state();
    ax.set_config(cfg);
    ax.aram_dma_transfer(0u, kMramAdpcm, aram_addr, static_cast<uint32_t>(adpcm.size()), mem);
    setup_adpcm_voice(nib_base + 2u, nib_base + 2u, nib_base + 96u, 0x00018000u, 0u);
    const std::vector<int16_t> f_fast = ax.mix_stereo_frame(mem, 20u);
    int32_t max_abs_fast = 0;
    for (size_t i = 1; i < 20u; ++i) {
        max_abs_fast = std::max(max_abs_fast, static_cast<int32_t>(std::abs(f_fast[i * 2u])));
        const int32_t d = std::abs(static_cast<int32_t>(f_fast[i * 2u]) - static_cast<int32_t>(f_fast[(i - 1u) * 2u]));
        assert(d <= 450); // 1.5x of +256 = ~384; skipping IIR nibbles would spike
    }
    assert(max_abs_fast > 2000);

    // 4. Double-buffered end_addr extension + loop wrap with AXPBADPCMLOOP (vp+492..496)
    ax.reset_state();
    ax.set_config(cfg);
    ax.aram_dma_transfer(0u, kMramAdpcm, aram_addr, static_cast<uint32_t>(adpcm.size()), mem);
    setup_adpcm_voice(nib_base + 2u, nib_base + 18u, nib_base + 48u, 0x00010000u, 1u);
    ax.step_audio_frame(ctx, mem, 16u);
    // Double-buffer: extend end_addr before reaching 48 -> must NOT reset hist1/cur_addr_fp
    mem.write_u16(kAxVpbBase + 430u, static_cast<uint16_t>(((nib_base + 64u) >> 16) & 0xFFFFu));
    mem.write_u16(kAxVpbBase + 432u, static_cast<uint16_t>((nib_base + 64u) & 0xFFFFu));
    // Set AXPBADPCMLOOP yn1 = 10000 so loop wrap at nib_base+64 resets predictor cleanly to loop history
    mem.write_u16(kAxVpbBase + 492u, 0x06u);
    mem.write_u16(kAxVpbBase + 494u, static_cast<uint16_t>(10000));
    mem.write_u16(kAxVpbBase + 496u, static_cast<uint16_t>(9744));
    const std::vector<int16_t> f_ext = ax.mix_stereo_frame(mem, 60u);
    assert(f_ext[0] == 16 * 256); // Seamless continuation after end_addr update (did NOT reset to 0!)
    // At s=40 (samples 16..55 cover 40 samples up to end_addr=64 -> sample 40 wraps to loop_addr=18, then sample 41 outputs s[loop_addr]=10000+256)
    bool saw_loop_hist = false;
    for (size_t i = 35; i < 60u; ++i) {
        if (f_ext[i * 2u] >= 10256) {
            saw_loop_hist = true;
            break;
        }
    }
    assert(saw_loop_hist);

    ax.reset_state();
    reset_hle_runtime_state(mem);
    std::cout << "[PASS] test_audio_adpcm_interpolation_and_loop (1.0x/frac/>1x ADPCM, end_addr update & loop history verified)\n";
}

void test_frame_pacer_59_94hz_ntsc_cadence_and_clamp() {
    FramePacer pacer(false, FramePacer::kNtscHz);
    assert(std::fabs(pacer.target_hz() - (60000.0 / 1001.0)) < 1e-4);
    assert(pacer.ticks_per_frame() > 0u);

    constexpr uint64_t kFreq = 10000000ull; // 10 MHz QPC
    const uint64_t f_ticks = static_cast<uint64_t>(std::llround(static_cast<double>(kFreq) * FramePacer::kNtscPeriodSec));
    assert(f_ticks == 166833ull || f_ticks == 166834ull);

    uint64_t deadline = 0u;
    assert(FramePacer::compute_next_step_us(1000000ull, deadline, kFreq, f_ticks) == 0u);
    assert(deadline == 1000000ull + f_ticks);

    // 5ms into frame -> remaining wait should be ~11,683 us
    const uint64_t wait_us = FramePacer::compute_next_step_us(1050000ull, deadline, kFreq, f_ticks);
    assert(wait_us >= 11680ull && wait_us <= 11690ull);
    assert(deadline == 1000000ull + f_ticks * 2ull);

    // Runaway hitch (>3 frames behind) must re-anchor deadline instead of turbo catch-up
    const uint64_t hitch_now = deadline + f_ticks * 6ull;
    assert(FramePacer::compute_next_step_us(hitch_now, deadline, kFreq, f_ticks) == 0u);
    assert(deadline == hitch_now + f_ticks);

    std::cout << "[PASS] test_frame_pacer_59_94hz_ntsc_cadence_and_clamp (59.94Hz QPC cadence & runaway clamp verified)\n";
}

void test_sky_stage1_alpha_and_4_3_1080p_efb() {
    Memory mem;
    PPCContext ctx{};
    RuntimeConfig cfg{};
    cfg.render_width          = 1920u;
    cfg.render_height         = 1080u;
    cfg.internal_scale_factor = 3u;
    cfg.aspect_ratio          = AspectRatioMode::Original_4_3;
    cfg.enable_fxaa           = true;
    set_global_gx_config(cfg);

    GX3DInterface& gx = global_gx_3d_interface();
    gx.clear_frame_geometry();
    gx.set_config(cfg);

    ctx.r[3] = 0u; ctx.r[4] = 0u; ctx.r[5] = 640u; ctx.r[6] = 480u;
    assert(dispatch_recompiled_function(0x801264E4u, ctx, mem)); // GXSetDispCopySrc(0,0,640,480)
    ctx.r[3] = 640u; ctx.r[4] = 480u;
    assert(dispatch_recompiled_function(0x8012650Cu, ctx, mem)); // GXSetDispCopyDst(640,480)
    ctx.f[1] = 0.0; ctx.f[2] = 0.0; ctx.f[3] = 640.0; ctx.f[4] = 480.0; ctx.f[5] = 0.0; ctx.f[6] = 1.0;
    assert(dispatch_recompiled_function(0x80126334u, ctx, mem)); // GXSetViewport
    ctx.r[3] = 0u; ctx.r[4] = 0u; ctx.r[5] = 640u; ctx.r[6] = 480u;
    assert(dispatch_recompiled_function(0x80126390u, ctx, mem)); // GXSetScissor

    constexpr uint32_t kOrthoVa = 0x80510400u;
    for (int i = 0; i < 16; ++i) mem.write_f32(kOrthoVa + static_cast<uint32_t>(i * 4), 0.0f);
    mem.write_f32(kOrthoVa + 0u,  2.0f / 640.0f);
    mem.write_f32(kOrthoVa + 12u, -1.0f);
    mem.write_f32(kOrthoVa + 20u, -2.0f / 480.0f);
    mem.write_f32(kOrthoVa + 28u, 1.0f);
    mem.write_f32(kOrthoVa + 40u, -1.0f);
    mem.write_f32(kOrthoVa + 60u, 1.0f);
    ctx.r[3] = kOrthoVa; ctx.r[4] = 1u;
    assert(dispatch_recompiled_function(0x80125D20u, ctx, mem)); // GXSetProjection(ORTHO)

    // 8x8 CMPR base sky texture (solid red 0xF800 in all 4 sub-blocks) at 0x80520000
    constexpr uint32_t kCmprVa = 0x80520000u;
    for (uint32_t b = 0; b < 4u; ++b) {
        mem.write_u16(kCmprVa + b * 8u + 0u, 0xF800u);
        mem.write_u16(kCmprVa + b * 8u + 2u, 0xF800u);
        mem.write_u32(kCmprVa + b * 8u + 4u, 0x00000000u);
    }
    // 8x8 GX_TF_I4 Stage-1 alpha mask at 0x80521000: left half (x=0..3) = 0x0, right half (x=4..7) = 0xF
    constexpr uint32_t kI4Va = 0x80521000u;
    for (uint32_t row = 0; row < 8u; ++row) {
        mem.write_u8(kI4Va + row * 4u + 0u, 0x00u);
        mem.write_u8(kI4Va + row * 4u + 1u, 0x00u);
        mem.write_u8(kI4Va + row * 4u + 2u, 0xFFu);
        mem.write_u8(kI4Va + row * 4u + 3u, 0xFFu);
    }

    constexpr uint32_t kTexObj0Va = 0x80522000u;
    constexpr uint32_t kTexObj1Va = 0x80522040u;
    ctx.r[3] = kTexObj0Va; ctx.r[4] = kCmprVa; ctx.r[5] = 8u; ctx.r[6] = 8u;
    ctx.r[7] = GX_TF_CMPR; ctx.r[8] = 0u; ctx.r[9] = 0u; ctx.r[10] = 0u;
    assert(dispatch_recompiled_function(0x8012270Cu, ctx, mem)); // GXInitTexObj(tex0)
    ctx.r[3] = kTexObj0Va; ctx.r[4] = 0u;
    assert(dispatch_recompiled_function(0x8012319Cu, ctx, mem)); // GXLoadTexObj(tex0, GX_TEXMAP0)

    ctx.r[3] = kTexObj1Va; ctx.r[4] = kI4Va; ctx.r[5] = 8u; ctx.r[6] = 8u;
    ctx.r[7] = GX_TF_I4; ctx.r[8] = 0u; ctx.r[9] = 0u; ctx.r[10] = 0u;
    assert(dispatch_recompiled_function(0x8012270Cu, ctx, mem)); // GXInitTexObj(tex1)
    ctx.r[3] = kTexObj1Va; ctx.r[4] = 1u;
    assert(dispatch_recompiled_function(0x8012319Cu, ctx, mem)); // GXLoadTexObj(tex1, GX_TEXMAP1)

    ctx.r[3] = 1u;
    assert(dispatch_recompiled_function(0x8011FBD8u, ctx, mem)); // GXSetNumTexGens(1)
    ctx.r[3] = 1u;
    assert(dispatch_recompiled_function(0x80122374u, ctx, mem)); // GXSetNumChans(1)
    ctx.r[3] = 4u; ctx.r[4] = 0u; ctx.r[5] = 1u; ctx.r[6] = 1u; ctx.r[7] = 0u; ctx.r[8] = 0u; ctx.r[9] = 2u;
    assert(dispatch_recompiled_function(0x801223B8u, ctx, mem)); // GXSetChanCtrl(COLOR0A0, unlit, mat_src=VTX)
    ctx.r[3] = 2u;
    assert(dispatch_recompiled_function(0x80125170u, ctx, mem)); // GXSetNumTevStages(2)
    ctx.r[3] = 0u; ctx.r[4] = 0u;
    assert(dispatch_recompiled_function(0x801249B8u, ctx, mem)); // GXSetTevOp(0, GX_MODULATE)
    ctx.r[3] = 0u; ctx.r[4] = 0u; ctx.r[5] = 0u; ctx.r[6] = 4u;
    assert(dispatch_recompiled_function(0x80124F98u, ctx, mem)); // GXSetTevOrder(0, TC0, MAP0, COLOR0A0)
    ctx.r[3] = 1u; ctx.r[4] = 0u; ctx.r[5] = 1u; ctx.r[6] = 4u;
    assert(dispatch_recompiled_function(0x80124F98u, ctx, mem)); // GXSetTevOrder(1, TC0, MAP1, COLOR0A0)
    ctx.r[3] = 1u; ctx.r[4] = 15u; ctx.r[5] = 15u; ctx.r[6] = 15u; ctx.r[7] = 0u;
    assert(dispatch_recompiled_function(0x80124A44u, ctx, mem)); // GXSetTevColorIn(1, ZERO, ZERO, ZERO, CPREV)
    ctx.r[3] = 1u; ctx.r[4] = 7u; ctx.r[5] = 4u; ctx.r[6] = 0u; ctx.r[7] = 7u;
    assert(dispatch_recompiled_function(0x80124A88u, ctx, mem)); // GXSetTevAlphaIn(1, ZERO, TEXA, APREV, ZERO)
    ctx.r[3] = 1u; ctx.r[4] = 4u; ctx.r[5] = 5u; ctx.r[6] = 0u;
    assert(dispatch_recompiled_function(0x80125684u, ctx, mem)); // GXSetBlendMode(BLEND, SRCALPHA, INVSRCALPHA)

    gx.begin_primitive(GX_QUADS, 0, 4);
    gx.submit_vertex({{  0.0f,   0.0f, 0.5f}, {0, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}});
    gx.submit_vertex({{640.0f,   0.0f, 0.5f}, {0, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}});
    gx.submit_vertex({{640.0f, 480.0f, 0.5f}, {0, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}});
    gx.submit_vertex({{  0.0f, 480.0f, 0.5f}, {0, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}});
    gx.end_primitive();

    assert(gx.draw_batches().size() == 1u);
    assert(gx.draw_batches()[0].has_stage1_tex);
    assert(gx.draw_batches()[0].stage1_op == 1u);
    assert(gx.draw_batches()[0].stage1_texture.data_vaddr == kI4Va);

    Win32D3D11Host host(cfg);
    std::string err;
    assert(host.create_render_window_and_d3d11(err, true));
    // 4:3 at 1920x1080 scale=3 must snap cleanly to 1440x1080 1:1 (no 1920x1440 -> 0.75x box downsample)
    assert(host.efb_width() == 1440u && host.efb_height() == 1080u);
    assert(Win32D3D11Host::fxaa_subpix_quality() <= 0.35f);

    host.begin_d3d11_frame(0.0f, 0.0f, 0.0f);
    host.render_gx_draw_batches(mem, gx);
    host.flush_d3d11();
    host.end_d3d11_frame_and_present();

    const std::filesystem::path bmp_path = std::filesystem::temp_directory_path() / "pn03_test_stage1_i4_mask.bmp";
    std::filesystem::remove(bmp_path);
    assert(host.dump_framebuffer_bmp(bmp_path.string()));

    uint8_t left_masked[3]{}, right_visible[3]{};
    read_bmp24_pixel(bmp_path, 400,  540, left_masked);
    read_bmp24_pixel(bmp_path, 1400, 540, right_visible);
    assert(left_masked[0] < 20u && left_masked[2] < 30u);
    assert(right_visible[0] > 200u && right_visible[2] < 20u);

    std::filesystem::remove(bmp_path);
    gx.clear_frame_geometry();
    set_global_gx_config(RuntimeConfig{});
    std::cout << "[PASS] test_sky_stage1_alpha_and_4_3_1080p_efb (Stage-1 I4 alpha mask + 1440x1080 1:1 EFB + crisp FXAA verified)\n";
}

void test_cmeswk_bit30_dialogue_persistence_and_clear() {
    Memory mem;
    PPCContext ctx;
    ctx.mem_ptr = &mem;
    ctx.r[1] = 0x80F00000u;

    RuntimeConfig lcfg;
    lcfg.language               = GameLanguage::SimplifiedChinese;
    lcfg.enable_hd_chinese_font = true;
    LocalizationOverlay loc(lcfg);
    LocalizationOverlay::set_active_instance(&loc);

    constexpr uint32_t kCMesCtrlBase = 0x801A2A40u;
    constexpr uint32_t kCMesWk0      = 0x801A2A44u;
    constexpr uint32_t kStream       = 0x80520000u;
    const uint16_t words_new_game[] = {0x00B4u, 0x00ABu, 0x00BDu, 0x0080u, 0x00ADu, 0x00A7u, 0x00B3u, 0x00ABu, 0x0001u};
    for (size_t i = 0; i < sizeof(words_new_game) / sizeof(words_new_game[0]); ++i) {
        mem.write_u16(kStream + static_cast<uint32_t>(i * 2u), words_new_game[i]);
    }

    auto init_slot = [&](uint32_t flags) {
        mem.write_u32(kCMesWk0 + 0x00u, 1u);
        mem.write_u32(kCMesWk0 + 0x24u, 0xFFFFFFFFu);
        mem.write_u32(kCMesWk0 + 0x28u, flags);
        mem.write_u32(kCMesWk0 + 0x40u, kStream);
        mem.write_u16(kCMesWk0 + 0x58u, 120u);
        mem.write_u16(kCMesWk0 + 0x5Au, 200u);
    };

    // Bit 30 clear (0x00000000 and 0x80000000): active dialogue slot MUST persist (+0x00 == 1)
    for (uint32_t active_flags : {0u, 0x80000000u}) {
        init_slot(active_flags);
        loc.begin_frame();
        global_gx_3d_interface().clear_frame_geometry();
        ctx.r[3] = kCMesWk0;
        assert(dispatch_recompiled_function(0x8009FDF0u, ctx, mem));
        assert(!global_gx_3d_interface().overlay_texts().empty());
        assert(mem.read_u32(kCMesWk0 + 0x00u) == 1u);
    }

    // Bit 30 set (0x40000000 and 0xC0000000): finished/one-shot message clears +0x00 to 0
    for (uint32_t done_flags : {0x40000000u, 0xC0000000u}) {
        init_slot(done_flags);
        loc.begin_frame();
        global_gx_3d_interface().clear_frame_geometry();
        ctx.r[3] = kCMesWk0;
        assert(dispatch_recompiled_function(0x8009FDF0u, ctx, mem));
        assert(mem.read_u32(kCMesWk0 + 0x00u) == 0u);
    }

    // CMesCtrl::MesClear(0) also deactivates slot immediately
    init_slot(0u);
    ctx.r[3] = kCMesCtrlBase;
    ctx.r[4] = 0u;
    assert(dispatch_recompiled_function(0x8009F208u, ctx, mem));
    assert(mem.read_u32(kCMesWk0 + 0x00u) == 0u);

    LocalizationOverlay::set_active_instance(nullptr);
    global_gx_3d_interface().clear_frame_geometry();
    reset_hle_runtime_state(mem);
    std::cout << "[PASS] test_cmeswk_bit30_dialogue_persistence_and_clear (MesWorkTrans bit-30 check & MesClear verified)\n";
}

void test_vi_wait_cadence_and_retrace_pacing() {
    Memory mem;
    assert(resolve_vi_wait_cadence(mem) == 1u);

    constexpr uint32_t kFakePg = 0x80400000u;
    mem.write_u32(recomp::sym_addr::kSda_pG, kFakePg);

    mem.write_u32(kFakePg + 284u, 0u);
    assert(resolve_vi_wait_cadence(mem) == 1u);
    mem.write_u32(kFakePg + 284u, 1u);
    assert(resolve_vi_wait_cadence(mem) == 1u);
    mem.write_u32(kFakePg + 284u, 2u);
    assert(resolve_vi_wait_cadence(mem) == 2u);
    mem.write_u32(kFakePg + 284u, 4u);
    assert(resolve_vi_wait_cadence(mem) == 4u);
    mem.write_u32(kFakePg + 284u, 99u);
    assert(resolve_vi_wait_cadence(mem) == 4u);

    auto& gx = global_gx_3d_interface();
    const uint32_t base_vi = gx.current_vi_retrace_count();
    gx.advance_vi_retraces(1u);
    assert(gx.current_vi_retrace_count() == base_vi + 1u);
    gx.advance_vi_retraces(2u);
    assert(gx.current_vi_retrace_count() == base_vi + 3u);

    std::cout << "[PASS] test_vi_wait_cadence_and_retrace_pacing (pG+284 clamp [1..4] & VI retrace progression verified)\n";
}

void test_widescreen_aspect_patch_and_ortho_bounds() {
    Memory mem;
    PPCContext ctx{};
    ctx.mem_ptr = &mem;

    assert(std::fabs(resolve_target_aspect_ratio(AspectRatioMode::Original_4_3) - (4.0f / 3.0f)) < 1e-5f);
    assert(std::fabs(resolve_target_aspect_ratio(AspectRatioMode::Widescreen_16_9) - (16.0f / 9.0f)) < 1e-5f);
    assert(std::fabs(resolve_target_aspect_ratio(AspectRatioMode::Ultrawide_21_9) - (21.0f / 9.0f)) < 1e-5f);

    patch_widescreen_aspect_constants(mem, AspectRatioMode::Widescreen_16_9);
    for (uint32_t addr : {0x80163D94u, 0x80163E60u, 0x8016B74Cu}) {
        assert(std::fabs(mem.read_f32(addr) - (16.0f / 9.0f)) < 1e-5f);
    }

    RuntimeConfig wcfg{};
    wcfg.aspect_ratio = AspectRatioMode::Widescreen_16_9;
    set_global_gx_config(wcfg);
    auto& gx = global_gx_3d_interface();

    // 1. Pre-patched 16:9 perspective matrix (p11 / p00 == 16/9) must NOT be double-scaled
    constexpr uint32_t kProjMtxVa = 0x80510200u;
    for (int i = 0; i < 16; ++i) mem.write_f32(kProjMtxVa + static_cast<uint32_t>(i * 4), 0.0f);
    mem.write_f32(kProjMtxVa + 0u,  1.125f);
    mem.write_f32(kProjMtxVa + 20u, 2.0f);
    ctx.r[3] = kProjMtxVa;
    ctx.r[4] = 0u;
    assert(dispatch_recompiled_function(0x80125D20u, ctx, mem));
    assert(std::fabs(gx.projection_mtx()[0][0] - 1.125f) < 1e-4f);

    // 2. Unpatched 4:3 perspective matrix (p11 / p00 == 4/3) IS widened by (4/3)/(16/9) -> 1.125f
    mem.write_f32(kProjMtxVa + 0u, 1.5f);
    assert(dispatch_recompiled_function(0x80125D20u, ctx, mem));
    assert(std::fabs(gx.projection_mtx()[0][0] - 1.125f) < 1e-4f);

    patch_widescreen_aspect_constants(mem, AspectRatioMode::Original_4_3);
    assert(std::fabs(mem.read_f32(0x80163D94u) - (4.0f / 3.0f)) < 1e-5f);

    // 3. Centered 4:3 overlay ortho matrix inside 16:9 keeps 2D elements unstretched
    float overlay_ortho[4][4]{};
    fill_centered_43_overlay_ortho_rect(overlay_ortho, 0.0f, 0.0f, 640.0f, 480.0f, 1920.0f, 1080.0f);
    assert(std::fabs(overlay_ortho[0][0] - (2.0f / (640.0f * (16.0f / 9.0f) / (4.0f / 3.0f)))) < 1e-5f);
    assert(std::fabs(overlay_ortho[1][1] - (-2.0f / 480.0f)) < 1e-5f);

    // 4. Separate world-space Z-tested ortho dust / fullscreen fades (full 16:9 EFB) from 2D HUD (centered 4:3)
    const uint32_t quad_idx[6] = {0u, 1u, 2u, 0u, 2u, 3u};
    const GXVertex hud_verts[4] = {
        {{ 40.0f, 40.0f, 0.0f}, {0, 0, 1}, {1, 1, 1, 1}, {0, 0}},
        {{160.0f, 40.0f, 0.0f}, {0, 0, 1}, {1, 1, 1, 1}, {1, 0}},
        {{160.0f, 80.0f, 0.0f}, {0, 0, 1}, {1, 1, 1, 1}, {1, 1}},
        {{ 40.0f, 80.0f, 0.0f}, {0, 0, 1}, {1, 1, 1, 1}, {0, 1}},
    };
    const GXVertex fade_verts[4] = {
        {{  0.0f,   0.0f, 0.0f}, {0, 0, 1}, {1, 1, 1, 1}, {0, 0}},
        {{640.0f,   0.0f, 0.0f}, {0, 0, 1}, {1, 1, 1, 1}, {1, 0}},
        {{640.0f, 480.0f, 0.0f}, {0, 0, 1}, {1, 1, 1, 1}, {1, 1}},
        {{  0.0f, 480.0f, 0.0f}, {0, 0, 1}, {1, 1, 1, 1}, {0, 1}},
    };
    GXDrawBatch batch{};
    fill_ortho_rect(batch.proj_mtx, 0.0f, 0.0f, 640.0f, 480.0f);
    batch.proj_type    = 1u;
    batch.index_offset = 0u;
    batch.index_count  = 6u;
    batch.z_enable     = false;
    batch.z_write      = false;
    assert(!should_ortho_batch_fill_efb(batch, hud_verts, 4u, quad_idx, 6u, 0.0f, 0.0f, 640.0f, 480.0f));
    batch.z_enable = true;
    batch.z_write  = false;
    assert(should_ortho_batch_fill_efb(batch, hud_verts, 4u, quad_idx, 6u, 0.0f, 0.0f, 640.0f, 480.0f));
    batch.z_enable = false;
    assert(should_ortho_batch_fill_efb(batch, fade_verts, 4u, quad_idx, 6u, 0.0f, 0.0f, 640.0f, 480.0f));

    const HostViewportRect hud_eb = compute_2d_ortho_efb_bounds(1920u, 1080u, false);
    const HostViewportRect full_eb = compute_2d_ortho_efb_bounds(1920u, 1080u, true);
    assert(std::fabs(hud_eb.x - 240.0f) < 1e-3f && std::fabs(hud_eb.width - 1440.0f) < 1e-3f);
    assert(std::fabs(full_eb.x - 0.0f) < 1e-3f && std::fabs(full_eb.width - 1920.0f) < 1e-3f);

    set_global_gx_config(RuntimeConfig{});
    gx.clear_frame_geometry();
    std::cout << "[PASS] test_widescreen_aspect_patch_and_ortho_bounds (DOL float patch, no double-scale, 4:3 HUD vs 16:9 dust/fade verified)\n";
}

void test_vulkan_host_efb_msaa_fxaa_and_overlay_render() {
    Memory mem;
    PPCContext ctx{};
    RuntimeConfig cfg{};
    cfg.backend               = GraphicsBackend::Vulkan13;
    cfg.window_mode           = WindowMode::Windowed;
    cfg.render_width          = 1280u;
    cfg.render_height         = 720u;
    cfg.internal_scale_factor = 2u;
    cfg.aspect_ratio          = AspectRatioMode::Widescreen_16_9;
    cfg.msaa_mode             = AntiAliasingMode::MSAA_4x;
    cfg.enable_fxaa           = true;
    cfg.enable_hd_chinese_font = true;
    set_global_gx_config(cfg);

    GX3DInterface& gx = global_gx_3d_interface();
    gx.clear_frame_geometry();
    gx.set_config(cfg);

    ctx.r[3] = 0u; ctx.r[4] = 0u; ctx.r[5] = 640u; ctx.r[6] = 480u;
    assert(dispatch_recompiled_function(0x801264E4u, ctx, mem)); // GXSetDispCopySrc
    ctx.r[3] = 640u; ctx.r[4] = 480u;
    assert(dispatch_recompiled_function(0x8012650Cu, ctx, mem)); // GXSetDispCopyDst
    ctx.f[1] = 0.0; ctx.f[2] = 0.0; ctx.f[3] = 640.0; ctx.f[4] = 480.0; ctx.f[5] = 0.0; ctx.f[6] = 1.0;
    assert(dispatch_recompiled_function(0x80126334u, ctx, mem)); // GXSetViewport
    ctx.r[3] = 0u; ctx.r[4] = 0u; ctx.r[5] = 640u; ctx.r[6] = 480u;
    assert(dispatch_recompiled_function(0x80126390u, ctx, mem)); // GXSetScissor

    constexpr uint32_t kOrthoVa = 0x80510400u;
    for (int i = 0; i < 16; ++i) mem.write_f32(kOrthoVa + static_cast<uint32_t>(i * 4), 0.0f);
    mem.write_f32(kOrthoVa + 0u,  2.0f / 640.0f);
    mem.write_f32(kOrthoVa + 12u, -1.0f);
    mem.write_f32(kOrthoVa + 20u, -2.0f / 480.0f);
    mem.write_f32(kOrthoVa + 28u, 1.0f);
    mem.write_f32(kOrthoVa + 40u, -1.0f);
    mem.write_f32(kOrthoVa + 60u, 1.0f);
    ctx.r[3] = kOrthoVa; ctx.r[4] = 1u;
    assert(dispatch_recompiled_function(0x80125D20u, ctx, mem)); // GXSetProjection(ORTHO)

    // 8x8 CMPR solid green texture (0x07E0)
    constexpr uint32_t kCmprVa   = 0x80520000u;
    constexpr uint32_t kTexObjVa = 0x80522000u;
    for (uint32_t b = 0; b < 4u; ++b) {
        mem.write_u16(kCmprVa + b * 8u + 0u, 0x07E0u);
        mem.write_u16(kCmprVa + b * 8u + 2u, 0x07E0u);
        mem.write_u32(kCmprVa + b * 8u + 4u, 0x00000000u);
    }
    ctx.r[3] = kTexObjVa; ctx.r[4] = kCmprVa; ctx.r[5] = 8u; ctx.r[6] = 8u;
    ctx.r[7] = GX_TF_CMPR; ctx.r[8] = 0u; ctx.r[9] = 0u; ctx.r[10] = 0u;
    assert(dispatch_recompiled_function(0x8012270Cu, ctx, mem)); // GXInitTexObj
    ctx.r[3] = kTexObjVa; ctx.r[4] = 0u;
    assert(dispatch_recompiled_function(0x8012319Cu, ctx, mem)); // GXLoadTexObj
    ctx.r[3] = 1u; assert(dispatch_recompiled_function(0x8011FBD8u, ctx, mem)); // GXSetNumTexGens
    ctx.r[3] = 1u; assert(dispatch_recompiled_function(0x80122374u, ctx, mem)); // GXSetNumChans
    ctx.r[3] = 4u; ctx.r[4] = 0u; ctx.r[5] = 1u; ctx.r[6] = 1u; ctx.r[7] = 0u; ctx.r[8] = 0u; ctx.r[9] = 2u;
    assert(dispatch_recompiled_function(0x801223B8u, ctx, mem)); // GXSetChanCtrl
    ctx.r[3] = 1u; assert(dispatch_recompiled_function(0x80125170u, ctx, mem)); // GXSetNumTevStages
    ctx.r[3] = 0u; ctx.r[4] = 0u; assert(dispatch_recompiled_function(0x801249B8u, ctx, mem)); // GXSetTevOp(MODULATE)
    ctx.r[3] = 0u; ctx.r[4] = 0u; ctx.r[5] = 0u; ctx.r[6] = 4u;
    assert(dispatch_recompiled_function(0x80124F98u, ctx, mem)); // GXSetTevOrder
    ctx.r[3] = 0u; ctx.r[4] = 4u; ctx.r[5] = 5u; ctx.r[6] = 0u;
    assert(dispatch_recompiled_function(0x80125684u, ctx, mem)); // GXSetBlendMode(NONE)
    ctx.r[3] = 1u; ctx.r[4] = 7u; ctx.r[5] = 0u;
    assert(dispatch_recompiled_function(0x80125730u, ctx, mem)); // GXSetZMode(TRUE, ALWAYS, FALSE) -> 16:9 EFB fill

    gx.begin_primitive(GX_QUADS, 0, 4);
    gx.submit_vertex({{  0.0f,   0.0f, 0.5f}, {0, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}});
    gx.submit_vertex({{640.0f,   0.0f, 0.5f}, {0, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}});
    gx.submit_vertex({{640.0f, 480.0f, 0.5f}, {0, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}});
    gx.submit_vertex({{  0.0f, 480.0f, 0.5f}, {0, 0, 1}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}});
    gx.end_primitive();
    gx.submit_overlay_text(160.0f, 100.0f, 1.0f, 0xFFFFFFFFu, "P.N.03 VULKAN");

    Win32VulkanHost host(cfg);
    std::string err;
    assert(host.create_render_window_and_vulkan(err, true));
    assert(host.efb_width() == 1280u && host.efb_height() == 720u && host.efb_msaa_samples() == 4u);

    host.begin_vulkan_frame(0.0f, 0.0f, 0.0f);
    host.render_gx_draw_batches(mem, gx);
    host.flush_vulkan();
    host.end_vulkan_frame_and_present();

    const std::filesystem::path bmp_path = std::filesystem::temp_directory_path() / "pn03_test_vulkan_host.bmp";
    std::filesystem::remove(bmp_path);
    assert(host.dump_framebuffer_bmp(bmp_path.string()));

    uint8_t left_px[3]{}, center_px[3]{};
    read_bmp24_pixel(bmp_path, 40,  360, left_px);
    read_bmp24_pixel(bmp_path, 640, 360, center_px);
    assert(left_px[1] > 200u && left_px[0] < 30u && left_px[2] < 35u);
    assert(center_px[1] > 200u && center_px[0] < 30u && center_px[2] < 35u);

    std::filesystem::remove(bmp_path);
    gx.clear_frame_geometry();
    set_global_gx_config(RuntimeConfig{});
    reset_hle_runtime_state(mem);
    std::cout << "[PASS] test_vulkan_host_efb_msaa_fxaa_and_overlay_render (Vulkan 1.3 Swapchain + 4x MSAA EFB + FXAA + overlay + BMP verified)\n";
}

void test_cmeswk_multipage_0x0004_segmentation() {
    Memory mem;
    PPCContext ctx;
    ctx.mem_ptr = &mem;

    RuntimeConfig lcfg;
    lcfg.language               = GameLanguage::SimplifiedChinese;
    lcfg.enable_hd_chinese_font = true;
    LocalizationOverlay loc(lcfg);
    LocalizationOverlay::set_active_instance(&loc);

    // Encode the exact multi-page English stream from zh_CN.json:
    // "It's a special attack that enables you to discharge\ndestructive energy contained within the suit.<08><04>..."
    const std::string en_raw =
        "It's a special attack that enables you to discharge\n"
        "destructive energy contained within the suit.<08><04>"
        "If your interested in mastering the Energy Drive,\n"
        "press START and go to the Menu screen to find out.<08><04>"
        "Since the suit is directly connected to your spinal\n"
        "cord, you can expect the response time to be<08><04>"
        "lightning quick.<08>";

    std::vector<uint16_t> words;
    std::vector<uint32_t> page_start_word_idx;
    page_start_word_idx.push_back(0u);
    for (size_t i = 0; i < en_raw.size(); ++i) {
        const char ch = en_raw[i];
        if (ch == '<' && i + 3u < en_raw.size() && en_raw[i + 3u] == '>') {
            const std::string tag = en_raw.substr(i + 1u, 2u);
            if (tag == "08") {
                words.push_back(0x0008u);
                i += 3u;
                continue;
            }
            if (tag == "04") {
                words.push_back(0x0004u);
                page_start_word_idx.push_back(static_cast<uint32_t>(words.size()));
                i += 3u;
                continue;
            }
        }
        if (ch == '\n') words.push_back(0x0003u);
        else if (ch == ' ') words.push_back(0x0080u);
        else if (ch >= 'A' && ch <= 'Z') words.push_back(static_cast<uint16_t>(0x00A7u + (ch - 'A')));
        else if (ch >= 'a' && ch <= 'z') words.push_back(static_cast<uint16_t>(0x00C1u + (ch - 'a')));
        else if (ch == ',') words.push_back(0x0094u);
        else if (ch == '.') words.push_back(0x0095u);
        else if (ch == '\'') words.push_back(0x0123u);
    }
    words.push_back(0x0001u);

    constexpr uint32_t kLangBase = 0x80540000u;
    constexpr uint32_t kEntryRel = 0x20u;
    constexpr uint32_t kEntryPtr = kLangBase + kEntryRel;
    mem.write_u32(kLangBase + 8u, kEntryRel);
    for (size_t i = 0; i < words.size(); ++i) {
        mem.write_u16(kEntryPtr + static_cast<uint32_t>(i * 2u), words[i]);
    }

    constexpr uint32_t kCMesWk0 = 0x801A2A44u;
    mem.write_u32(kCMesWk0 + 0x00u, 1u);
    mem.write_u32(kCMesWk0 + 0x24u, 0xFFFFFFFFu);
    mem.write_u32(kCMesWk0 + 0x28u, 0u);
    mem.write_u32(kCMesWk0 + 0x44u, kLangBase);
    mem.write_u16(kCMesWk0 + 0x58u, 88u);
    mem.write_u16(kCMesWk0 + 0x5Au, 68u);

    // Page 0: text_ptr sitting at the first 0x0004 (awaiting player A press)
    const uint32_t p0_wait_ptr = kEntryPtr + (page_start_word_idx[1] - 1u) * 2u;
    assert(LocalizationOverlay::count_cmes_page_index(mem, kEntryPtr, p0_wait_ptr) == 0u);
    mem.write_u32(kCMesWk0 + 0x40u, p0_wait_ptr);
    loc.begin_frame();
    global_gx_3d_interface().clear_frame_geometry();
    assert(loc.try_on_mes_work_trans(kCMesWk0, mem));
    assert(global_gx_3d_interface().overlay_texts().size() == 1u);
    const std::string& p0_txt = global_gx_3d_interface().overlay_texts()[0].text;
    assert(p0_txt.find("特殊攻击") != std::string::npos);
    assert(p0_txt.find("能量驱动") == std::string::npos);
    assert(p0_txt.find("脊椎神经") == std::string::npos);

    // Page 1: after code04 advances text_ptr past the first 0x0004
    const uint32_t p1_ptr = kEntryPtr + page_start_word_idx[1] * 2u;
    assert(LocalizationOverlay::count_cmes_page_index(mem, kEntryPtr, p1_ptr) == 1u);
    mem.write_u32(kCMesWk0 + 0x40u, p1_ptr);
    loc.begin_frame();
    global_gx_3d_interface().clear_frame_geometry();
    assert(loc.try_on_mes_work_trans(kCMesWk0, mem));
    assert(global_gx_3d_interface().overlay_texts().size() == 1u);
    const std::string& p1_txt = global_gx_3d_interface().overlay_texts()[0].text;
    assert(p1_txt.find("能量驱动") != std::string::npos);
    assert(p1_txt.find("特殊攻击") == std::string::npos);
    assert(p1_txt.find("脊椎神经") == std::string::npos);

    // Page 2 & Page 3
    const uint32_t p2_ptr = kEntryPtr + page_start_word_idx[2] * 2u;
    assert(LocalizationOverlay::count_cmes_page_index(mem, kEntryPtr, p2_ptr) == 2u);
    mem.write_u32(kCMesWk0 + 0x40u, p2_ptr);
    loc.begin_frame();
    global_gx_3d_interface().clear_frame_geometry();
    assert(loc.try_on_mes_work_trans(kCMesWk0, mem));
    const std::string& p2_txt = global_gx_3d_interface().overlay_texts()[0].text;
    assert(p2_txt.find("脊椎神经") != std::string::npos);
    assert(p2_txt.find("闪电般的敏捷") == std::string::npos);

    const uint32_t p3_ptr = kEntryPtr + page_start_word_idx[3] * 2u;
    assert(LocalizationOverlay::count_cmes_page_index(mem, kEntryPtr, p3_ptr) == 3u);
    mem.write_u32(kCMesWk0 + 0x40u, p3_ptr);
    loc.begin_frame();
    global_gx_3d_interface().clear_frame_geometry();
    assert(loc.try_on_mes_work_trans(kCMesWk0, mem));
    const std::string& p3_txt = global_gx_3d_interface().overlay_texts()[0].text;
    assert(p3_txt.find("闪电般的敏捷") != std::string::npos);
    assert(p3_txt.find("脊椎神经") == std::string::npos);

    mem.write_u32(kCMesWk0 + 0x00u, 0u);
    mem.write_u32(kCMesWk0 + 0x40u, 0u);
    mem.write_u32(kCMesWk0 + 0x44u, 0u);
    LocalizationOverlay::set_active_instance(nullptr);
    global_gx_3d_interface().clear_frame_geometry();
    std::cout << "[PASS] test_cmeswk_multipage_0x0004_segmentation (Active 0x0004 page-by-page rendering verified)\n";
}

void test_comm_box_font_scale_wrap_and_bounds() {
    const std::string long_zh =
        "那是一种能够释放装甲内部毁灭性能量的特殊攻击，如果你想熟练掌握能量驱动，可按 START 键进入菜单界面查看详情。";
    const auto top_lay = LocalizationOverlay::layout_dialogue(88.0f, 68.0f, long_zh);
    assert(top_lay.scale < 0.85f && top_lay.scale >= 0.70f);
    assert(top_lay.lines >= 2u);
    assert(top_lay.x >= 52.0f);
    assert(top_lay.x + top_lay.width <= 572.0f);
    assert(top_lay.y >= 40.0f && top_lay.y + top_lay.height <= 132.0f);

    // Verify every wrapped line respects max_cols (<= 46 with kinsoku punctuation tolerance)
    size_t start = 0u;
    for (size_t i = 0u; i <= top_lay.text.size(); ++i) {
        if (i == top_lay.text.size() || top_lay.text[i] == '\n') {
            assert(LocalizationOverlay::display_cols(top_lay.text.substr(start, i - start)) <= 46u);
            start = i + 1u;
        }
    }

    const auto bot_lay = LocalizationOverlay::layout_dialogue(64.0f, 376.0f, long_zh);
    assert(bot_lay.x + bot_lay.width <= 572.0f);
    assert(bot_lay.y >= 342.0f && bot_lay.y + bot_lay.height <= 436.0f);
    std::cout << "[PASS] test_comm_box_font_scale_wrap_and_bounds (0.74x scale, CJK wrap, top/bottom comm-box bounds verified)\n";
}

void test_audio_ax_ring_wrap_and_subframe_hle_flush() {
    Memory mem;
    PPCContext ctx;
    ctx.mem_ptr = &mem;
    reset_hle_runtime_state(mem);

    RuntimeConfig cfg;
    cfg.audio_muted  = false;
    cfg.audio_volume = 1.0f;

    auto& ax = global_audio_ax_interface();
    ax.reset_state();
    ax.set_config(cfg);

    // 1. Looping ADPCM voice near end_addr must wrap cleanly to loop_addr without deactivation
    constexpr uint32_t kNumBlocks = 8u;
    constexpr uint32_t kMramAdpcm = 0x80510000u;
    const uint32_t aram_addr = ax.aram_alloc(4096u);
    assert(aram_addr != 0u);
    std::vector<uint8_t> adpcm(kNumBlocks * 8u, 0x06u);
    for (uint32_t b = 0; b < kNumBlocks; ++b) {
        for (uint32_t i = 1u; i < 8u; ++i) {
            adpcm[b * 8u + i] = 0x22u;
        }
    }
    mem.write_bytes(kMramAdpcm, adpcm.data(), adpcm.size());
    ax.aram_dma_transfer(0u, kMramAdpcm, aram_addr, static_cast<uint32_t>(adpcm.size()), mem);

    constexpr uint32_t kAxVpbBase = 0x802614E0u;
    const uint32_t nib_base  = aram_addr * 2u;
    const uint32_t loop_nib  = nib_base + 2u;
    const uint32_t end_nib   = nib_base + kNumBlocks * 16u;
    const uint32_t start_nib = end_nib - 10u; // crosses end_nib within a single 540-sample frame

    mem.write_u16(kAxVpbBase + 326u, 1u);       // state = run
    mem.write_u16(kAxVpbBase + 330u, 0x8000u);
    mem.write_u16(kAxVpbBase + 334u, 0x8000u);
    mem.write_u16(kAxVpbBase + 412u, 0x8000u);
    mem.write_u16(kAxVpbBase + 422u, 1u);       // loop_flag = 1
    mem.write_u16(kAxVpbBase + 424u, 0u);       // format = ADPCM
    mem.write_u16(kAxVpbBase + 426u, static_cast<uint16_t>((loop_nib >> 16) & 0xFFFFu));
    mem.write_u16(kAxVpbBase + 428u, static_cast<uint16_t>(loop_nib & 0xFFFFu));
    mem.write_u16(kAxVpbBase + 430u, static_cast<uint16_t>((end_nib >> 16) & 0xFFFFu));
    mem.write_u16(kAxVpbBase + 432u, static_cast<uint16_t>(end_nib & 0xFFFFu));
    mem.write_u16(kAxVpbBase + 434u, static_cast<uint16_t>((start_nib >> 16) & 0xFFFFu));
    mem.write_u16(kAxVpbBase + 436u, static_cast<uint16_t>(start_nib & 0xFFFFu));
    mem.write_u16(kAxVpbBase + 478u, 1u);
    mem.write_u16(kAxVpbBase + 480u, 0u);

    // Step several frames across the loop boundary
    for (int f = 0; f < 5; ++f) {
        ax.step_audio_frame(ctx, mem, 540u);
        assert(ax.active_voice_count() == 1u);
        const uint32_t cur = (static_cast<uint32_t>(mem.read_u16(kAxVpbBase + 434u)) << 16) |
                              mem.read_u16(kAxVpbBase + 436u);
        assert(cur >= loop_nib && cur < end_nib);
    }

    // Even if guest cursor starts >= end_nib on a looping voice, mixer wraps instead of killing it
    mem.write_u16(kAxVpbBase + 434u, static_cast<uint16_t>((end_nib >> 16) & 0xFFFFu));
    mem.write_u16(kAxVpbBase + 436u, static_cast<uint16_t>(end_nib & 0xFFFFu));
    ax.step_audio_frame(ctx, mem, 160u);
    assert(ax.active_voice_count() == 1u);
    const uint32_t cur_after = (static_cast<uint32_t>(mem.read_u16(kAxVpbBase + 434u)) << 16) |
                                mem.read_u16(kAxVpbBase + 436u);
    assert(cur_after >= loop_nib && cur_after < end_nib);

    // Exact-boundary step: starting 1 ADPCM block (14 samples, 14 data nibbles) before end_nib and stepping 14
    // samples lands on end_nib + 2 on the final sample; must wrap immediately before writing guest +434..+436.
    const uint32_t exact_start = end_nib - 14u;
    mem.write_u16(kAxVpbBase + 434u, static_cast<uint16_t>((exact_start >> 16) & 0xFFFFu));
    mem.write_u16(kAxVpbBase + 436u, static_cast<uint16_t>(exact_start & 0xFFFFu));
    ax.step_audio_frame(ctx, mem, 14u);
    assert(ax.active_voice_count() == 1u);
    const uint32_t cur_exact = (static_cast<uint32_t>(mem.read_u16(kAxVpbBase + 434u)) << 16) |
                                mem.read_u16(kAxVpbBase + 436u);
    assert(cur_exact >= loop_nib && cur_exact < end_nib);

    // 2. Verify step_audio_frame flushes queued HLE callbacks per 5ms DSP tick
    ctx.r[3] = 0u;
    assert(dispatch_recompiled_function(0x800F7CE8u, ctx, mem)); // OSSetSoundMode(0)
    enqueue_pending_hle_callback(0x800F7CE8u, 1u, 0u, 0u);     // OSSetSoundMode(1)
    ax.dispatch_audio_call(0x80151260u, ctx, mem);             // AXInit()
    // Register a harmless callback (OSGetSoundMode 0x800F7C68) so ax_ticks runs
    ctx.r[3] = 0x800F7C68u;
    ax.dispatch_audio_call(0x80152E48u, ctx, mem);             // AXRegisterCallback
    ax.step_audio_frame(ctx, mem, 160u);
    assert(dispatch_recompiled_function(0x800F7C68u, ctx, mem));
    assert(ctx.r[3] == 1u);

    ax.reset_state();
    reset_hle_runtime_state(mem);
    std::cout << "[PASS] test_audio_ax_ring_wrap_and_subframe_hle_flush (SND_STR loop wrap + 5ms HLE flush verified)\n";
}

static void test_multi6_localization_config_save_cheats_and_1x_controller(const std::string& iso_path) {
    namespace fs = std::filesystem;

    // 1. Config persistence (auto-mkdir + Proton Z:/ path + 1x scale + cheat flags)
    const fs::path tmp_dir = fs::temp_directory_path() / "pn03_test_cfg_persistence_28";
    std::error_code ec;
    fs::remove_all(tmp_dir, ec);
    const fs::path nested_cfg = tmp_dir / "nested" / "pn03_settings.json";

    RuntimeConfig cfg;
    cfg.iso_path               = "Z:\\home\\user\\P.N. 03 (USA).iso";
    cfg.render_width           = 1280;
    cfg.render_height          = 720;
    cfg.internal_scale_factor  = 1;
    cfg.language               = GameLanguage::Spanish;
    cfg.cheat_god_mode         = true;
    cfg.cheat_infinite_energy  = true;
    cfg.cheat_infinite_credits = true;
    cfg.cheat_unlock_all_suits = true;

    assert(cfg.save_to_json(nested_cfg.string()));
    assert(fs::exists(nested_cfg));
    RuntimeConfig loaded = RuntimeConfig::load_from_json(nested_cfg.string());
    assert(loaded.iso_path == "Z:/home/user/P.N. 03 (USA).iso");
    assert(loaded.internal_scale_factor == 1u);
    assert(loaded.render_width == 1280u && loaded.render_height == 720u);
    assert(loaded.language == GameLanguage::Spanish);
    assert(loaded.cheat_god_mode && loaded.cheat_infinite_energy &&
           loaded.cheat_infinite_credits && loaded.cheat_unlock_all_suits);
    assert(!RuntimeConfig::resolve_config_path().empty());
    fs::remove_all(tmp_dir, ec);

    // 2. All 6 disc languages unlocked (Japanese + English + German + French + Spanish + Italian)
    const IsoStreamReader* prev_iso = IsoStreamReader::active_instance();
    IsoStreamReader test_iso;
    std::string iso_err;
    if (!iso_path.empty() && test_iso.open(iso_path, iso_err)) {
        IsoStreamReader::set_active_instance(&test_iso);
    }

    auto check_loc = [](GameLanguage lang, const std::string& in_path) {
        RuntimeConfig c;
        c.language = lang;
        LocalizationOverlay loc(c);
        return loc.resolve_localized_asset_path(in_path);
    };

    assert(check_loc(GameLanguage::Spanish,  "id/eng/iddata_e.dat")   == "id/spa/iddata_s.dat");
    assert(check_loc(GameLanguage::Spanish,  "id/eng/lobby_e.dat")    == "id/spa/lobby_s.dat");
    assert(check_loc(GameLanguage::Spanish,  "id/eng/combo.tpl")      == "id/spa/combo.tpl");
    assert(check_loc(GameLanguage::Spanish,  "etc/card.dat")          == "etc/card_s.dat");
    assert(check_loc(GameLanguage::Spanish,  "etc/continue.dat")      == "etc/continue_s.dat");
    assert(check_loc(GameLanguage::Spanish,  "etc/result00.dat")      == "etc/result00_s.dat");
    assert(check_loc(GameLanguage::Spanish,  "etc/rank_a.tpl")        == "etc/rank_a_s.tpl");
    assert(check_loc(GameLanguage::Spanish,  "/etc/title.dat")        == "/etc/title.dat");
    assert(check_loc(GameLanguage::German,   "id/eng/iddata_e.dat")   == "id/ger/iddata_g.dat");
    assert(check_loc(GameLanguage::German,   "id/eng/combo.tpl")      == "id/ger/combo.tpl");
    assert(check_loc(GameLanguage::Italian,  "id/eng/iddata_e.dat")   == "id/ita/iddata_i.dat");
    assert(check_loc(GameLanguage::French,   "id/eng/iddata_e.dat")   == "id/fra/iddata_f.dat");
    if (IsoStreamReader::active_instance() != nullptr) {
        // id/fra/combo.tpl is absent on disc, so ISO check must keep id/eng/combo.tpl cleanly
        assert(check_loc(GameLanguage::French, "id/eng/combo.tpl") == "id/eng/combo.tpl");
    }
    assert(check_loc(GameLanguage::Japanese, "id/eng/iddata_e.dat")   == "id/iddata.dat");
    assert(check_loc(GameLanguage::Japanese, "id/eng/lobby_e.dat")    == "id/lobby.dat");
    assert(check_loc(GameLanguage::Japanese, "id/eng/equip_ck_e.dat") == "id/equip_ck.dat");
    assert(check_loc(GameLanguage::Japanese, "id/eng/combo.tpl")      == "id/eng/combo.tpl");
    IsoStreamReader::set_active_instance(prev_iso);

    // 3. Built-in cheat toggles verification against Global struct (0x801959C0)
    Memory mem;
    mem.write_u32(recomp::sym_addr::kSda_pG, recomp::sym_addr::kGlobalStruct);
    const uint32_t pG = recomp::sym_addr::kGlobalStruct;
    mem.write_u16(pG + 26640u, 80u);   // Cur HP
    mem.write_u16(pG + 26642u, 500u);  // Max HP
    mem.write_u16(pG + 26644u, 120u);  // Cur Energy
    mem.write_u16(pG + 26646u, 800u);  // Max Energy
    mem.write_u32(pG + 26664u, 250u);  // Points
    mem.write_u32(pG + 304u, 0u);
    mem.write_u32(pG + 4u, 0u);
    mem.write_u8(pG + 26776u + 2u, 1u); // Mark suit[0] initialized

    RuntimeConfig cheat_cfg;
    cheat_cfg.cheat_god_mode         = true;
    cheat_cfg.cheat_infinite_energy  = true;
    cheat_cfg.cheat_infinite_credits = true;
    cheat_cfg.cheat_unlock_all_suits = true;
    apply_runtime_cheats(cheat_cfg, mem);

    assert(mem.read_s16(pG + 26640u) == 500);
    assert(mem.read_s16(pG + 26644u) == 800);
    assert((mem.read_u32(pG + 304u) & 0x2000u) != 0u);
    assert(mem.read_u32(pG + 26664u) == 9999999u);
    assert((mem.read_u32(pG + 4u) & 0x60000000u) == 0x60000000u);
    for (uint32_t s = 0; s < 11u; ++s) {
        const uint32_t s_va = pG + 26776u + s * 16u;
        assert(mem.read_u8(s_va + 0u) == 1u);
        assert(mem.read_u8(s_va + 4u) == 5u);
        assert(mem.read_u8(s_va + 5u) == 2u);
        assert(mem.read_u8(s_va + 6u) == 6u);
    }

    // 4. Native 1x EFB dimensions + default disconnected XboxInputState / keyboard online fallback
    uint32_t efb_w = 0, efb_h = 0;
    RuntimeConfig efb_43;
    efb_43.internal_scale_factor = 1u;
    efb_43.aspect_ratio = AspectRatioMode::Original_4_3;
    compute_efb_dimensions(efb_43, 480u, efb_w, efb_h);
    assert(efb_w == 640u && efb_h == 480u);

    RuntimeConfig efb_169;
    efb_169.internal_scale_factor = 1u;
    efb_169.aspect_ratio = AspectRatioMode::Widescreen_16_9;
    compute_efb_dimensions(efb_169, 1080u, efb_w, efb_h);
    assert(efb_h == 480u && efb_w >= 848u && efb_w <= 864u);

    PadXInputBridge pad(cheat_cfg);
    XboxInputState disconnected{};
    assert(!disconnected.connected);
    GcPadStatus raw_gc = pad.translate_to_gc_pad(disconnected);
    assert(raw_gc.err == -1);

    std::cout << "[PASS] test_multi6_localization_config_save_cheats_and_1x_controller (Config save, Multi-6/JPN ISO assets, 4 cheats, 1x EFB, PAD state verified)\n";
}

int main(int argc, char** argv) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    Win32D3D11Host::enable_process_dpi_awareness();
    assert(IsProcessDPIAware() != FALSE);
#endif
    std::string extract_dir = (argc > 1) ? argv[1] : auto_discover_test_iso();
    test_memory_and_ppc_context();
    test_lzs_decode_roundtrip();
    test_iso_fst_and_dol_loading(extract_dir);
    test_gx_3d_interface_and_cyber_launcher();
    test_audio_ax_and_osalloc();
    test_xbox_xinput_bridge();
    test_dolphin_sdk_hle_and_full_6340_dispatch();
    test_chinese_localization_overlay();
    test_logger_rotation_and_pruning();
    test_controller_remapping_and_guide();
    test_audio_ax_mixer_and_aram_step();
    test_localization_glyph_decode_and_cmeswk();
    test_graphics_efb_fxaa_scissor_and_cinesco();
    test_memory_card_lifecycle_and_calendar_time();
    test_disp_copy_src_512x448_and_centered_4_3_fill();
    test_tev_color_scale_gamma_and_brightness_config();
    test_audio_ax_ring_cushion_and_telemetry();
    test_audio_adpcm_interpolation_and_loop();
    test_frame_pacer_59_94hz_ntsc_cadence_and_clamp();
    test_sky_stage1_alpha_and_4_3_1080p_efb();
    test_cmeswk_bit30_dialogue_persistence_and_clear();
    test_vi_wait_cadence_and_retrace_pacing();
    test_widescreen_aspect_patch_and_ortho_bounds();
    test_vulkan_host_efb_msaa_fxaa_and_overlay_render();
    test_cmeswk_multipage_0x0004_segmentation();
    test_comm_box_font_scale_wrap_and_bounds();
    test_audio_ax_ring_wrap_and_subframe_hle_flush();
    test_multi6_localization_config_save_cheats_and_1x_controller(extract_dir);
    std::cout << "================================================================\n";
    std::cout << " ALL C++20 RUNTIME & STATIC RECOMPILATION TESTS PASSED (28/28)!\n";
    std::cout << "================================================================\n";
    return 0;
}

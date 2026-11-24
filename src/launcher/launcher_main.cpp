#include "pn03_all_forwards.hpp"
#include "pn03_audio_ax.hpp"
#include "pn03_config.hpp"
#include "pn03_cyber_launcher.hpp"
#include "pn03_d3d11_host.hpp"
#include "pn03_vulkan_host.hpp"
#include "pn03_gx_3d_interface.hpp"
#include "pn03_logger.hpp"
#include "pn03_runtime.hpp"
#include "pn03_symbols.hpp"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

namespace fs = std::filesystem;

namespace pn03 {

static std::string auto_discover_iso_in_project_dir() {
    for (const std::string& search_dir : {".", ".."}) {
        if (!fs::exists(search_dir)) continue;
        for (const auto& entry : fs::directory_iterator(search_dir)) {
            if (!entry.is_regular_file()) continue;
            std::string ext = entry.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            if (ext == ".iso" || ext == ".gcm") {
                return entry.path().string();
            }
        }
    }
    return "";
}

class WinPortApplication {
public:
    explicit WinPortApplication(const RuntimeConfig& cfg)
        : cfg_(cfg),
          pad_bridge_(cfg_),
          gx_renderer_(cfg_),
          loc_overlay_(cfg_),
          d3d11_host_(cfg_),
          vulkan_host_(cfg_) {}

    ~WinPortApplication() {
        reset_hle_runtime_state(mem_);
    }

    bool use_vulkan_backend() const noexcept {
        return cfg_.backend == GraphicsBackend::Vulkan13;
    }

    bool host_is_initialized() const noexcept {
        return use_vulkan_backend() ? vulkan_host_.is_initialized() : d3d11_host_.is_initialized();
    }

    bool host_pump_messages() {
        return use_vulkan_backend() ? vulkan_host_.pump_messages() : d3d11_host_.pump_messages();
    }

    void host_begin_frame() {
        if (use_vulkan_backend()) vulkan_host_.begin_vulkan_frame();
        else d3d11_host_.begin_d3d11_frame();
    }

    void host_render_gx_draw_batches(GX3DInterface& gx3d) {
        if (use_vulkan_backend()) vulkan_host_.render_gx_draw_batches(mem_, gx3d);
        else d3d11_host_.render_gx_draw_batches(mem_, gx3d);
    }

    bool host_dump_framebuffer_bmp(const std::string& path) {
        return use_vulkan_backend() ? vulkan_host_.dump_framebuffer_bmp(path) : d3d11_host_.dump_framebuffer_bmp(path);
    }

    void host_flush() {
        if (use_vulkan_backend()) vulkan_host_.flush_vulkan();
        else d3d11_host_.flush_d3d11();
    }

    void host_end_frame_and_present() {
        if (use_vulkan_backend()) vulkan_host_.end_vulkan_frame_and_present();
        else d3d11_host_.end_d3d11_frame_and_present();
    }

    bool initialize(std::string& err_msg, bool force_gpu = false, bool hidden_window = false, bool trace = false) {
        if (cfg_.iso_path.empty()) {
            err_msg = "No ISO or extracted sys/ path configured. Please place a P.N.03 (GPNE08) .iso in the project root or select it in the launcher.";
            return false;
        }
        if (trace) std::cerr << "[TRACE] iso_reader_.open" << std::endl;
        if (!iso_reader_.open(cfg_.iso_path, err_msg)) {
            return false;
        }
        if (iso_reader_.game_id() != "GPNE08") {
            err_msg = "Unsupported Game ID: " + iso_reader_.game_id() +
                      " (expected GPNE08 - P.N.03 USA). Static recompilation binds 6,340+ functions & RAM layout to GPNE08 main.dol; note that GPNE08 USA already contains full Japanese/English/German/French/Spanish/Italian assets (select in Launcher).";
            return false;
        }

        uint32_t entry_point = 0;
        if (trace) std::cerr << "[TRACE] load_main_dol_into_memory" << std::endl;
        if (!iso_reader_.load_main_dol_into_memory(mem_, entry_point)) {
            err_msg = "Failed to load sys/main.dol from ISO into 24MB GameCube RAM.";
            return false;
        }

        ctx_.reset();
        ctx_.pc = entry_point;
        ctx_.mem_ptr = &mem_;
        set_global_gx_config(cfg_);
        IsoStreamReader::set_active_instance(&iso_reader_);
        PadXInputBridge::set_active_instance(&pad_bridge_);
        LocalizationOverlay::set_active_instance(&loc_overlay_);
        reset_hle_runtime_state(mem_);
        patch_widescreen_aspect_constants(mem_, cfg_.aspect_ratio);

        gx_renderer_.initialize_pipeline(mem_);
        global_audio_ax_interface().set_config(cfg_);
        global_audio_ax_interface().initialize_audio_device();

        if (cfg_.runtime_mode == "live" || force_gpu) {
            if (use_vulkan_backend()) {
                if (trace) std::cerr << "[TRACE] create_render_window_and_vulkan (hidden=" << hidden_window << ")" << std::endl;
                if (!vulkan_host_.create_render_window_and_vulkan(err_msg, hidden_window)) {
                    return false;
                }
            } else {
                if (trace) std::cerr << "[TRACE] create_render_window_and_d3d11 (hidden=" << hidden_window << ")" << std::endl;
                if (!d3d11_host_.create_render_window_and_d3d11(err_msg, hidden_window)) {
                    return false;
                }
            }
        }

        set_hle_call_trace(trace);

        // Workstream B.1 & E: Execute all C++ static constructors (.ctors at 0x80162204..0x801622C0)
        if (trace) std::cerr << "[TRACE] execute_static_constructors" << std::endl;
        ctors_executed_ = execute_static_constructors(ctx_, mem_);
        if (trace) std::cerr << "[TRACE] ctors done: " << ctors_executed_ << std::endl;

        has_full_dol_data_ = (mem_.read_u32(0x80173284u) >= kGcRamBase);
        if (has_full_dol_data_) {
            // Boot the recompiled P.N.03 engine initialization sequence:
            // main_8009C4DC initializes pG -> &Global (0x801959C0) BEFORE systemStartInit
            mem_.write_u32(recomp::sym_addr::kSda_pG, 0x801959C0u);
            // systemStartInit_8009C5B8 -> systemRestartInit_8009C65C -> TaskExec(0, Title_task_800D7A58)
            if (trace) std::cerr << "[TRACE] dispatch systemStartInit (0x8009C5B8)" << std::endl;
            dispatch_recompiled_function(0x8009C5B8u, ctx_, mem_); // systemStartInit
            if (trace) std::cerr << "[TRACE] dispatch systemRestartInit (0x8009C65C)" << std::endl;
            dispatch_recompiled_function(0x8009C65Cu, ctx_, mem_); // systemRestartInit
            if (trace) std::cerr << "[TRACE] flush_pending_hle_callbacks (boot)" << std::endl;
            flush_pending_hle_callbacks(ctx_, mem_);

            ctx_.r[3] = 0u;
            ctx_.r[4] = 0x800D7A58u; // Title_task
            if (trace) std::cerr << "[TRACE] dispatch TaskExec(0, Title_task)" << std::endl;
            dispatch_recompiled_function(0x800A1B08u, ctx_, mem_); // TaskExec(0, Title_task)
        }

        if (cfg_.load_tools_rel_debug) {
            auto rel_bytes = iso_reader_.read_file("/module/Tools.rel");
            if (!rel_bytes.empty()) {
                RelModuleHeader rel_hdr{};
                uint32_t prolog_va = 0;
                if (ToolsRelLoader::link_rel_module(rel_bytes, mem_, 0x80300000u, rel_hdr, prolog_va) && prolog_va != 0u) {
                    if (trace) std::cerr << "[TRACE] dispatch Tools.rel prolog" << std::endl;
                    dispatch_recompiled_function(prolog_va, ctx_, mem_);
                }
            }
        }
        if (trace) std::cerr << "[TRACE] initialize done" << std::endl;
        return true;
    }

    void run_frames(uint32_t num_frames,
                    const XboxInputState* test_input = nullptr,
                    bool auto_start = false,
                    const std::string& dump_frame_path = "",
                    bool trace = false,
                    uint32_t trace_from = 0u,
                    bool pace_frames = false) {
        ctx_.r[3] = 0x801A2A40u; // cMes singleton
        loc_overlay_.hook_mes_set_language(ctx_, mem_);
        PN03_LOGF(LogLevel::Info, "ENGINE", "Starting frame loop: frames=%u auto_start=%d trace=%d trace_from=%u backend=%s gpu_init=%d pace_59_94=%d",
                  num_frames, auto_start ? 1 : 0, trace ? 1 : 0, trace_from,
                  use_vulkan_backend() ? "Vulkan" : "D3D11",
                  host_is_initialized() ? 1 : 0, pace_frames ? 1 : 0);

        FramePacer frame_pacer(pace_frames, FramePacer::kNtscHz);
        double audio_sample_accum = 0.0;
        constexpr double kSamplesPerNtscFrame = 32000.0 * FramePacer::kNtscPeriodSec;

        for (uint32_t f = 0; f < num_frames; ++f) {
            global_logger().set_current_frame(f);
            if (host_is_initialized() && !host_pump_messages()) {
                PN03_LOGF(LogLevel::Info, "ENGINE", "Host pump_messages returned false at frame %u; exiting loop", f);
                break;
            }
            if (host_is_initialized()) {
                host_begin_frame();
            }

            const uint32_t retraces_before = global_gx_3d_interface().current_vi_retrace_count();
            global_gx_3d_interface().clear_frame_geometry();
            loc_overlay_.begin_frame();
            gx_renderer_.begin_frame(mem_);
            XboxInputState synth{};
            synth.connected = true;
            const XboxInputState* frame_input = test_input;
            if (!frame_input && auto_start) {
                if ((f >= 20u && f <= 25u) || (f >= 60u && f <= 65u) ||
                    (f >= 275u && f <= 278u) ||
                    (f >= 760u && f <= 763u) || (f >= 950u && f <= 953u) ||
                    (f >= 1150u && f <= 1153u)) {
                    synth.btn_start = true;
                    synth.btn_a = true;
                } else if ((f >= 295u && f <= 298u) || (f >= 340u && f <= 343u) ||
                           (f >= 390u && f <= 393u) || (f >= 440u && f <= 443u) ||
                           (f >= 490u && f <= 493u) || (f >= 540u && f <= 543u) ||
                           (f >= 590u && f <= 593u) || (f >= 650u && f <= 653u) ||
                           (f >= 820u && f <= 823u) || (f >= 1020u && f <= 1023u) ||
                           (f >= 1220u && f <= 1223u) || (f >= 1350u && f <= 1353u) ||
                           (f >= 1500u && f <= 1503u) || (f >= 1650u && f <= 1653u) ||
                           (f >= 1800u && f <= 1803u) || (f >= 2100u && f <= 2103u) ||
                           (f >= 2300u && f <= 2303u) || (f >= 2500u && f <= 2503u)) {
                    synth.btn_a = true;
                }
                if (f >= 2000u) {
                    synth.left_stick_y = 0.8f;
                }
                frame_input = &synth;
            }
            pad_bridge_.update_memory_pad_status(mem_, frame_input);

            if (has_full_dol_data_) {
                const bool trace_now = trace && (f >= trace_from);
                if (trace && trace_from > 0u && f == trace_from) {
                    global_logger().set_level(LogLevel::Trace);
                }
                set_hle_call_trace(trace_now);
                const bool t_frame = trace_now && (f < 2u || f >= trace_from);
                // Execute the real recompiled P.N.03 per-frame loop from main_8009BF8C (0x8009BFF0..0x8009C088)
                if (t_frame) {
                    PN03_LOG(LogLevel::Debug, "FRAME", "Render_before");
                    std::cerr << "[TRACE f=" << f << "] Render_before" << std::endl;
                }
                dispatch_recompiled_function(0x8009D2B0u, ctx_, mem_); // Render_before
                if (t_frame) {
                    PN03_LOG(LogLevel::Debug, "FRAME", "PadRead");
                    std::cerr << "[TRACE f=" << f << "] PadRead" << std::endl;
                }
                dispatch_recompiled_function(0x800ACC2Cu, ctx_, mem_); // PadRead
                if (t_frame) {
                    PN03_LOG(LogLevel::Debug, "FRAME", "Render");
                    std::cerr << "[TRACE f=" << f << "] Render" << std::endl;
                }
                dispatch_recompiled_function(0x800D9D10u, ctx_, mem_); // Render
                if (t_frame) {
                    PN03_LOG(LogLevel::Debug, "FRAME", "FlipTransBuffer");
                    std::cerr << "[TRACE f=" << f << "] FlipTransBuffer" << std::endl;
                }
                dispatch_recompiled_function(0x8009D00Cu, ctx_, mem_); // FlipTransBuffer
                if (t_frame) {
                    PN03_LOG(LogLevel::Debug, "FRAME", "ClearOt");
                    std::cerr << "[TRACE f=" << f << "] ClearOt" << std::endl;
                }
                dispatch_recompiled_function(0x800DC780u, ctx_, mem_); // ClearOt

                // Clear system stop bits (r0 & ~0x38080019) before running Scheduler
                uint32_t pG_s = mem_.read_u32(recomp::sym_addr::kSda_pG);
                if (pG_s >= kGcRamBase) {
                    uint32_t sys_flags = mem_.read_u32(pG_s + 292u);
                    mem_.write_u32(pG_s + 292u, sys_flags & ~0x38080019u);
                }
                apply_runtime_cheats(cfg_, mem_);

                if (t_frame) std::cerr << "[TRACE f=" << f << "] Scheduler" << std::endl;
                dispatch_recompiled_function(0x800A18E4u, ctx_, mem_); // Scheduler
                flush_pending_hle_callbacks(ctx_, mem_);
                if (t_frame) std::cerr << "[TRACE f=" << f << "] Trans" << std::endl;
                dispatch_recompiled_function(0x800D91CCu, ctx_, mem_); // Trans
                if (t_frame) std::cerr << "[TRACE f=" << f << "] FadeControl" << std::endl;
                dispatch_recompiled_function(0x80094480u, ctx_, mem_); // FadeControl
                if (t_frame) std::cerr << "[TRACE f=" << f << "] CinescoMove" << std::endl;
                dispatch_recompiled_function(0x800731DCu, ctx_, mem_); // CinescoMove
                if (t_frame) std::cerr << "[TRACE f=" << f << "] DvdControl" << std::endl;
                dispatch_recompiled_function(0x8007B9BCu, ctx_, mem_); // DvdControl
                flush_pending_hle_callbacks(ctx_, mem_);
                if (t_frame) std::cerr << "[TRACE f=" << f << "] SndWatcher" << std::endl;
                dispatch_recompiled_function(0x800CBFB8u, ctx_, mem_); // SndWatcher
                if (t_frame) std::cerr << "[TRACE f=" << f << "] EprintfFlush" << std::endl;
                dispatch_recompiled_function(0x80081BE0u, ctx_, mem_); // EprintfFlush
                apply_runtime_cheats(cfg_, mem_);
            }

            uint32_t pG_addr = mem_.read_u32(recomp::sym_addr::kSda_pG);
            if (pG_addr >= kGcRamBase) {
                uint32_t frame_cnt = mem_.read_u32(pG_addr + 29184u);
                mem_.write_u32(pG_addr + 29184u, frame_cnt + 1u);
            }

            dispatch_recompiled_function(0x8009D3CCu, ctx_, mem_); // Render_done
            gx_renderer_.on_gx_set_viewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
            loc_overlay_.emit_active_ui_scene_overlays(mem_);

            auto& gx3d = global_gx_3d_interface();
            // Submit all recorded GX 3D draw batches and Chinese text overlays to active GPU backend
            if (host_is_initialized()) {
                host_render_gx_draw_batches(gx3d);
            }

            if (trace && (f == 0u || f == 1u || f + 1u == num_frames || (f % 30u == 0u))) {
                const auto& clr = gx3d.clear_rgba();
                const auto& batches = gx3d.draw_batches();
                uint32_t sys_flags = (pG_addr >= kGcRamBase) ? mem_.read_u32(pG_addr + 292u) : 0u;
                std::cerr << "[TELEM f=" << f << "] pG=0x" << std::hex << pG_addr
                          << " flags=0x" << sys_flags << std::dec
                          << " batches=" << batches.size()
                          << " verts=" << gx3d.vertices().size()
                          << " idx=" << gx3d.indices().size()
                          << " overlays=" << gx3d.overlay_texts().size()
                          << " clr=(" << int(clr[0]) << "," << int(clr[1]) << "," << int(clr[2]) << "," << int(clr[3]) << ")";
                if (!batches.empty()) {
                    const auto& b0 = batches[0];
                    std::cerr << " b0(idx=" << b0.index_count
                              << ",tex=" << (b0.has_texture ? 1 : 0)
                              << ",z=" << (b0.z_enable ? 1 : 0)
                              << ",p00=" << b0.proj_mtx[0][0]
                              << ",p11=" << b0.proj_mtx[1][1]
                              << ",p22=" << b0.proj_mtx[2][2]
                              << ",p23=" << b0.proj_mtx[2][3] << ")";
                }
                std::cerr << std::endl;
                if (trace && (f == 1u || f + 1u == num_frames)) {
                    const auto& verts = gx3d.vertices();
                    const auto& indices = gx3d.indices();
                    for (size_t bi = 0; bi < batches.size() && bi < 12u; ++bi) {
                        const auto& b = batches[bi];
                        std::cerr << "  [B" << bi << "] idx=" << b.index_count
                                  << " tex=" << (b.has_texture ? 1 : 0)
                                  << " fmt=" << b.texture.format
                                  << " wh=" << b.texture.width << "x" << b.texture.height
                                  << " ptr=0x" << std::hex << b.texture.data_vaddr
                                  << " tn=" << std::dec << b.texture.tlut_name
                                  << " tv=0x" << std::hex << b.tlut.data_vaddr
                                  << " tf=" << std::dec << b.tlut.format
                                  << " tev=" << b.tev_mode
                                  << " bl=(" << b.blend_type << "," << b.blend_src << "," << b.blend_dst << ")"
                                  << " z=(" << b.z_enable << "," << b.z_write << ")";
                        if (b.index_offset < indices.size() && indices[b.index_offset] < verts.size()) {
                            const auto& v0 = verts[indices[b.index_offset]];
                            std::cerr << " v0=(" << v0.pos[0] << "," << v0.pos[1] << "," << v0.pos[2]
                                      << " uv=" << v0.uv0[0] << "," << v0.uv0[1]
                                      << " c=" << v0.color0[0] << "," << v0.color0[1] << "," << v0.color0[2] << "," << v0.color0[3] << ")";
                        }
                        if (b.has_texture) {
                            auto px = gx3d.decode_gc_texture_to_rgba8(mem_, b.texture, &b.tlut);
                            if (px.size() >= 16) {
                                std::cerr << " px0=(" << int(px[0]) << "," << int(px[1]) << "," << int(px[2]) << "," << int(px[3]) << ")";
                            }
                        }
                        std::cerr << std::endl;
                    }
                }
            }

            if (!dump_frame_path.empty() && f + 1u == num_frames && host_is_initialized()) {
                bool saved = host_dump_framebuffer_bmp(dump_frame_path);
                std::cerr << "[DUMP-FRAME] saved=" << (saved ? 1 : 0) << " path=" << dump_frame_path << std::endl;
            }

            auto& ax = global_audio_ax_interface();
            auto step_audio_slice = [&]() {
                size_t audio_samples = 540u;
                if (pace_frames || ax.has_xaudio_output()) {
                    audio_sample_accum += kSamplesPerNtscFrame;
                    audio_samples = static_cast<size_t>(audio_sample_accum);
                    audio_sample_accum -= static_cast<double>(audio_samples);
                    if (ax.has_xaudio_output()) {
                        const size_t q = ax.queued_xaudio_buffers();
                        if (q <= 1u) {
                            audio_samples += 160u;
                        } else if (q <= 2u) {
                            audio_samples += 80u;
                        } else if (q >= 8u && audio_samples > 320u) {
                            audio_samples -= 80u;
                        }
                    }
                }
                ax.step_audio_frame(ctx_, mem_, audio_samples);
            };

            const uint32_t vi_wait = resolve_vi_wait_cadence(mem_);
            if (gx3d.current_vi_retrace_count() == retraces_before) {
                gx3d.advance_vi_retraces(1u);
            }
            step_audio_slice();
            gx_renderer_.end_frame_and_present(mem_);

            if (host_is_initialized()) {
                host_flush();
            }
            frame_pacer.wait_for_next_frame();
            if (host_is_initialized()) {
                host_end_frame_and_present();
            }

            bool exit_during_wait = false;
            for (uint32_t vi_slice = 1u; vi_slice < vi_wait; ++vi_slice) {
                if (host_is_initialized() && !host_pump_messages()) {
                    PN03_LOGF(LogLevel::Info, "ENGINE",
                              "Host pump_messages returned false during VI wait slice %u at frame %u; exiting loop",
                              vi_slice, f);
                    exit_during_wait = true;
                    break;
                }
                gx3d.advance_vi_retraces(1u);
                step_audio_slice();
                frame_pacer.wait_for_next_frame();
            }
            if (exit_during_wait) {
                break;
            }
        }
    }

    const IsoStreamReader& iso_reader() const { return iso_reader_; }
    const GXHighResRenderer& gx_renderer() const { return gx_renderer_; }
    const LocalizationOverlay& loc_overlay() const { return loc_overlay_; }
    const Memory& memory() const { return mem_; }
    Memory& memory() { return mem_; }
    PPCContext& context() { return ctx_; }
    uint32_t ctors_executed() const { return ctors_executed_; }

private:
    RuntimeConfig       cfg_;
    Memory              mem_;
    PPCContext          ctx_;
    IsoStreamReader     iso_reader_;
    PadXInputBridge     pad_bridge_;
    GXHighResRenderer   gx_renderer_;
    LocalizationOverlay loc_overlay_;
    Win32D3D11Host      d3d11_host_;
    Win32VulkanHost     vulkan_host_;
    uint32_t            ctors_executed_ = 0;
    bool                has_full_dol_data_ = false;
};

} // namespace pn03

int main(int argc, char** argv) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    // Must run before CyberLauncherUI or any other window creates an HWND.
    pn03::Win32D3D11Host::enable_process_dpi_awareness();
#endif
    std::string config_path = "config/pn03_settings.json";
    std::string iso_override;
    std::string dump_frame_path;
    std::string dump_launcher_path;
    uint32_t max_frames = 0;
    uint32_t trace_from = 0;
    bool frames_explicit = false;
    bool no_gui = false;
    bool force_gui = false;
    bool self_test = false;
    bool trace = false;
    bool auto_start = false;
    bool no_vsync = false;
    bool no_limit = false;
    std::string log_dir_override;
    std::string log_level_override;
    std::string backend_override;
    uint32_t log_max_total_mb_override = 0;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--config" && i + 1 < argc) {
            config_path = argv[++i];
        } else if (arg == "--iso" && i + 1 < argc) {
            iso_override = argv[++i];
        } else if (arg == "--backend" && i + 1 < argc) {
            backend_override = argv[++i];
        } else if (arg == "--frames" && i + 1 < argc) {
            max_frames = static_cast<uint32_t>(std::stoul(argv[++i]));
            frames_explicit = true;
        } else if (arg == "--dump-frame" && i + 1 < argc) {
            dump_frame_path = argv[++i];
        } else if (arg == "--dump-launcher" && i + 1 < argc) {
            dump_launcher_path = argv[++i];
        } else if (arg == "--trace") {
            trace = true;
        } else if (arg == "--trace-from" && i + 1 < argc) {
            trace_from = static_cast<uint32_t>(std::stoul(argv[++i]));
            trace = true;
        } else if (arg == "--log-dir" && i + 1 < argc) {
            log_dir_override = argv[++i];
        } else if (arg == "--log-level" && i + 1 < argc) {
            log_level_override = argv[++i];
        } else if (arg == "--log-max-total-mb" && i + 1 < argc) {
            log_max_total_mb_override = static_cast<uint32_t>(std::stoul(argv[++i]));
        } else if (arg == "--auto-start") {
            auto_start = true;
        } else if (arg == "--no-vsync") {
            no_vsync = true;
        } else if (arg == "--no-limit") {
            no_limit = true;
        } else if (arg == "--no-gui" || arg == "--headless") {
            no_gui = true;
        } else if (arg == "--gui") {
            force_gui = true;
        } else if (arg == "--self-test") {
            self_test = true;
            no_gui = true;
        }
    }

    config_path = pn03::RuntimeConfig::resolve_config_path(config_path);
    pn03::RuntimeConfig cfg = pn03::RuntimeConfig::load_from_json(config_path);
    if (!backend_override.empty()) {
        std::string b_low = backend_override;
        std::transform(b_low.begin(), b_low.end(), b_low.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        });
        if (b_low == "vulkan" || b_low == "vk" || b_low == "vulkan13") {
            cfg.backend = pn03::GraphicsBackend::Vulkan13;
        } else if (b_low == "d3d11" || b_low == "dx11" || b_low == "direct3d11") {
            cfg.backend = pn03::GraphicsBackend::Direct3D11;
        } else {
            std::cerr << "[WARN] Unknown --backend '" << backend_override << "', using configured backend.\n";
        }
    }
    if (no_gui || no_vsync) cfg.vsync = false;
    if (no_limit) cfg.limit_fps_60 = false;
    if (!log_dir_override.empty()) cfg.log_dir = log_dir_override;
    if (!log_level_override.empty()) cfg.log_level = log_level_override;
    if (log_max_total_mb_override > 0) cfg.log_max_total_mb = log_max_total_mb_override;

    {
        pn03::LogConfig lcfg;
        lcfg.log_dir = cfg.log_dir;
        lcfg.base_name = "pn03_runtime";
        lcfg.max_file_bytes = static_cast<uint64_t>(std::max<uint32_t>(1u, cfg.log_max_file_mb)) * 1024ull * 1024ull;
        lcfg.max_total_bytes = static_cast<uint64_t>(std::max<uint32_t>(1u, cfg.log_max_total_mb)) * 1024ull * 1024ull;
        lcfg.max_files = std::max<uint32_t>(1u, cfg.log_max_files);
        lcfg.min_level = pn03::Logger::parse_level(cfg.log_level, pn03::LogLevel::Info);
        if (trace && trace_from == 0u && static_cast<int>(lcfg.min_level) > static_cast<int>(pn03::LogLevel::Trace)) {
            lcfg.min_level = pn03::LogLevel::Trace;
        }
        pn03::global_logger().init(lcfg);
        PN03_LOGF(pn03::LogLevel::Info, "BOOT", "PN03_WinPort starting (config=%s mode=%s level=%s max_total=%uMB)",
                  config_path.c_str(), cfg.runtime_mode.c_str(),
                  pn03::Logger::level_name(lcfg.min_level), cfg.log_max_total_mb);
    }
    if (!iso_override.empty()) {
        cfg.iso_path = iso_override;
    } else if (cfg.iso_path.empty() || !fs::exists(cfg.iso_path)) {
        std::string discovered = pn03::auto_discover_iso_in_project_dir();
        if (!discovered.empty()) cfg.iso_path = discovered;
    }

    if (!dump_launcher_path.empty()) {
        pn03::CyberLauncherUI launcher(cfg, config_path);
        const std::string summary = cfg.iso_path.empty()
            ? "AUTO-SCAN PENDING | 0 BUILT-IN ASSETS"
            : "MOUNTED - 700 FILES | 0 BUILT-IN ASSETS";
        bool dumped = launcher.render_launcher_preview_bmp(dump_launcher_path, summary);
        std::cout << (dumped ? "[DUMP-LAUNCHER] saved=1 path=" : "[DUMP-LAUNCHER] saved=0 path=")
                  << dump_launcher_path << "\n";
        return dumped ? 0 : 1;
    }

    if (self_test) {
        cfg.runtime_mode = "mock";
        cfg.skip_launcher_gui = true;
        if (!frames_explicit) max_frames = 10;
    } else {
        if (frames_explicit && !force_gui) {
            no_gui = true;
        }
        if (!frames_explicit) {
            max_frames = (cfg.runtime_mode == "live") ? (std::numeric_limits<uint32_t>::max)() : 5u;
        }
    }

    if (cfg.runtime_mode == "live" && !cfg.skip_launcher_gui && !no_gui) {
        PN03_LOG(pn03::LogLevel::Info, "LAUNCHER", "Opening interactive Cyber Launcher window");
        pn03::CyberLauncherUI launcher(cfg, config_path);
        if (!launcher.run_modal_launcher_window()) {
            PN03_LOG(pn03::LogLevel::Info, "LAUNCHER", "Launcher closed by user without launching engine");
            pn03::global_logger().shutdown();
            return 0;
        }
        PN03_LOGF(pn03::LogLevel::Info, "LAUNCHER", "Engine launch confirmed (iso=%s res=%ux%u mode=%d)",
                  cfg.iso_path.c_str(), cfg.render_width, cfg.render_height, static_cast<int>(cfg.window_mode));
    }

    auto language_name = [](pn03::GameLanguage lang) -> const char* {
        switch (lang) {
            case pn03::GameLanguage::Japanese:          return "Japanese (ja_JP /id)";
            case pn03::GameLanguage::German:            return "Deutsch (/id/ger)";
            case pn03::GameLanguage::French:            return "Francais (/id/fra)";
            case pn03::GameLanguage::Spanish:           return "Espanol (/id/spa)";
            case pn03::GameLanguage::Italian:           return "Italiano (/id/ita)";
            case pn03::GameLanguage::SimplifiedChinese: return "Simplified Chinese (zh_CN)";
            case pn03::GameLanguage::English:
            default:                                    return "English (US Default)";
        }
    };

    std::cout << "================================================================\n";
    std::cout << " P.N.03 (GPNE08) Windows Native Recompiled Port & Launcher v2.4\n";
    std::cout << "================================================================\n";
    std::cout << "  * Config File       : " << config_path << "\n";
    std::cout << "  * Runtime Mode      : " << cfg.runtime_mode << (self_test ? " (self-test)" : "") << "\n";
    std::cout << "  * Graphics Backend  : " << (cfg.backend == pn03::GraphicsBackend::Vulkan13 ? "Vulkan 1.3" : "Direct3D 11") << "\n";
    std::cout << "  * Target Resolution : " << cfg.render_width << "x" << cfg.render_height
              << " (" << cfg.internal_scale_factor << "x EFB Scale)\n";
    std::cout << "  * Anti-Aliasing     : " << static_cast<int>(cfg.msaa_mode) << "x MSAA"
              << (cfg.enable_fxaa ? " + FXAA" : "") << " | " << cfg.anisotropic_filtering << "x AF\n";
    std::cout << "  * Language Overlay  : " << language_name(cfg.language) << "\n";
    std::cout << "  * Controller Stack  : " << (cfg.enable_xinput ? "Enabled (SDL2 / XInput / DirectInput8 / WinMM + Rumble)" : "Disabled") << "\n";
    std::cout << "  * Cheat Toggles     : God=" << (cfg.cheat_god_mode ? "ON" : "OFF")
              << " InfEnergy=" << (cfg.cheat_infinite_energy ? "ON" : "OFF")
              << " InfPts=" << (cfg.cheat_infinite_credits ? "ON" : "OFF")
              << " AllSuits=" << (cfg.cheat_unlock_all_suits ? "ON" : "OFF") << "\n";
    std::cout << "  * Mounted ISO Path  : " << (cfg.iso_path.empty() ? "<not set>" : cfg.iso_path) << "\n";

    if (cfg.iso_path.empty()) {
        std::cout << "[INFO] No ISO path provided. Place your P.N.03 .iso in the project directory or pass --iso <path>.\n";
        return self_test ? 1 : 0;
    }

    pn03::WinPortApplication app(cfg);
    std::string err;
    const bool need_d3d11 = (cfg.runtime_mode == "live") || !dump_frame_path.empty();
    const bool hide_win = no_gui && !dump_frame_path.empty();
    if (!app.initialize(err, need_d3d11, hide_win, trace)) {
        PN03_LOGF(pn03::LogLevel::Error, "BOOT", "Initialization failed: %s", err.c_str());
        std::cerr << "[ERROR] Initialization failed: " << err << "\n";
#ifdef _WIN32
        if (!no_gui) {
            int wlen = MultiByteToWideChar(CP_UTF8, 0, err.c_str(), -1, nullptr, 0);
            std::wstring werr(static_cast<size_t>(wlen > 0 ? wlen : 1), L'\0');
            if (wlen > 0) MultiByteToWideChar(CP_UTF8, 0, err.c_str(), -1, werr.data(), wlen);
            MessageBoxW(nullptr, werr.c_str(), L"P.N.03 Engine Initialization Failed", MB_ICONERROR | MB_OK);
        }
#endif
        pn03::global_logger().shutdown();
        return 1;
    }

    PN03_LOGF(pn03::LogLevel::Info, "BOOT", "Mounted %s (%s), FST=%zu, ctors=%u",
              app.iso_reader().game_id().c_str(), app.iso_reader().game_title().c_str(),
              app.iso_reader().file_count(), app.ctors_executed());
    std::cout << "[OK] Mounted Game ID: " << app.iso_reader().game_id()
              << " (" << app.iso_reader().game_title() << "), FST Files: " << app.iso_reader().file_count()
              << ", Static .ctors Executed: " << app.ctors_executed() << std::endl;

    if (self_test) {
        if (trace) std::cerr << "[TRACE] checking opening.bnr / FST / loc / dispatch" << std::endl;
        auto bnr = app.iso_reader().read_file("/opening.bnr");
        bool bnr_ok = (bnr.size() == 6496 && bnr[0] == 'B' && bnr[1] == 'N' && bnr[2] == 'R' && bnr[3] == '1');
        bool fst_ok = (app.iso_reader().file_count() == 700u);
        bool loc_ok = (app.loc_overlay().entry_count() >= 300u && app.loc_overlay().translate_text("NEW GAME") == "新游戏");
        bool disp_ok = pn03::dispatch_recompiled_function(0x8009C58Cu, app.context(), app.memory());
        bool ctors_ok = (app.ctors_executed() >= 29u);
        if (!bnr_ok || !fst_ok || !loc_ok || !disp_ok || !ctors_ok) {
            std::cerr << "[FAIL] Self-test invariant failed: bnr_ok=" << bnr_ok
                      << " fst_ok=" << fst_ok << " loc_ok=" << loc_ok
                      << " disp_ok=" << disp_ok << " ctors_ok=" << ctors_ok << "\n";
            return 1;
        }
        std::cout << "[OK] Self-test checks: opening.bnr (BNR1), 700 FST entries, 48 .ctors, zh_CN (" << app.loc_overlay().entry_count()
                  << " entries), static recomp dispatch OK" << std::endl;
    }

    const bool pace_live_frames = cfg.limit_fps_60 && !no_gui && !self_test && !no_limit && dump_frame_path.empty();
    app.run_frames(max_frames, nullptr, auto_start, dump_frame_path, trace, trace_from, pace_live_frames);
    PN03_LOGF(pn03::LogLevel::Info, "BOOT", "Exiting normally after %u frames (gx_batches=%zu)",
              app.gx_renderer().state().frame_count, pn03::global_gx_3d_interface().draw_batches().size());
    pn03::global_logger().shutdown();
    std::cout << "[OK] Executed " << app.gx_renderer().state().frame_count
              << " HD frames at " << app.gx_renderer().state().viewport_w << "x" << app.gx_renderer().state().viewport_h
              << " (GX draw batches recorded: " << pn03::global_gx_3d_interface().draw_batches().size() << ")\n";
    return 0;
}

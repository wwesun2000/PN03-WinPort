#include "pn03_runtime.hpp"

namespace pn03 {

GXHighResRenderer::GXHighResRenderer(const RuntimeConfig& cfg) : cfg_(cfg) {
    state_.target_width          = cfg.render_width;
    state_.target_height         = cfg.render_height;
    state_.viewport_w            = static_cast<float>(cfg.render_width);
    state_.viewport_h            = static_cast<float>(cfg.render_height);
    state_.msaa_samples          = static_cast<uint32_t>(cfg.msaa_mode == AntiAliasingMode::FXAA ? 1 : static_cast<int>(cfg.msaa_mode));
    if (state_.msaa_samples == 0) state_.msaa_samples = 1;
    state_.fxaa_enabled          = cfg.enable_fxaa || (cfg.msaa_mode == AntiAliasingMode::FXAA);
    state_.fullscreen            = (cfg.window_mode != WindowMode::Windowed);
    state_.deflicker_disabled    = cfg.disable_copy_deflicker;
    state_.cinesco_bars_removed  = cfg.remove_cinesco_bars;
    state_.internal_scale_factor = std::max<uint32_t>(1u, std::min<uint32_t>(6u, cfg.internal_scale_factor));

    if (cfg.aspect_ratio == AspectRatioMode::Widescreen_16_9) {
        state_.aspect_ratio = 16.0f / 9.0f;
        // Original P.N.03 ortho range is [0..640] (width 640 for 4:3). For 16:9, expand width to 853.333:
        state_.ortho_left   = -106.6667f;
        state_.ortho_right  = 746.6667f;
    } else if (cfg.aspect_ratio == AspectRatioMode::Ultrawide_21_9) {
        state_.aspect_ratio = 21.0f / 9.0f;
        state_.ortho_left   = -240.0f;
        state_.ortho_right  = 880.0f;
    } else {
        state_.aspect_ratio = 4.0f / 3.0f;
        state_.ortho_left   = 0.0f;
        state_.ortho_right  = 640.0f;
    }
    state_.efb_height = std::min<uint32_t>(2880u, 480u * state_.internal_scale_factor);
    state_.efb_width  = std::max<uint32_t>(16u, (static_cast<uint32_t>(static_cast<float>(state_.efb_height) * state_.aspect_ratio + 0.5f) + 1u) & ~1u);
}

void GXHighResRenderer::initialize_pipeline(Memory& mem) {
    // Patch SDA1 global projection constants in GameCube RAM (0x8026E76C..0x8026E780)
    mem.write_f32(recomp::sym_addr::kSda_ZNEAR,   1.0f);
    mem.write_f32(recomp::sym_addr::kSda_ZFAR,    100000.0f);
    mem.write_f32(recomp::sym_addr::kSda_ORTHO_T, 0.0f);
    mem.write_f32(recomp::sym_addr::kSda_ORTHO_B, 480.0f);
    mem.write_f32(recomp::sym_addr::kSda_ORTHO_L, state_.ortho_left);
    mem.write_f32(recomp::sym_addr::kSda_ORTHO_R, state_.ortho_right);

    // Initialize pG (0x8026E754) -> &Global (0x801959C0)
    mem.write_u32(recomp::sym_addr::kSda_pG, recomp::sym_addr::kGlobalStruct);
}

void GXHighResRenderer::begin_frame(Memory& mem) {
    // Ensure widescreen ortho bounds stay enforced each frame before Render() (0x800D9D10)
    mem.write_f32(recomp::sym_addr::kSda_ORTHO_L, state_.ortho_left);
    mem.write_f32(recomp::sym_addr::kSda_ORTHO_R, state_.ortho_right);
}

void GXHighResRenderer::end_frame_and_present(Memory& mem) {
    state_.frame_count++;
    // Increment Retrace_cnt (0x8026E764) and vsync_cnt (0x8026DD0C) so game scheduler advances
    uint32_t retrace = mem.read_u32(0x8026E764u);
    mem.write_u32(0x8026E764u, retrace + 1u);
    uint32_t vsync = mem.read_u32(0x8026DD0Cu);
    mem.write_u32(0x8026DD0Cu, vsync + 1u);
}

void GXHighResRenderer::on_gx_set_viewport(float x, float y, float w, float h, float near_z, float far_z) {
    (void)x; (void)y; (void)near_z; (void)far_z;
    // Scale original 640x480 viewport to native target resolution
    float scale_x = static_cast<float>(state_.target_width) / 640.0f;
    float scale_y = static_cast<float>(state_.target_height) / 480.0f;
    state_.viewport_w = w * scale_x;
    state_.viewport_h = h * scale_y;
    state_.draw_call_count++;
}

void GXHighResRenderer::on_gx_set_copy_filter(bool aa, const uint8_t sample_pattern[12][2], bool vf, const uint8_t vfilter[7]) {
    (void)aa; (void)sample_pattern; (void)vf; (void)vfilter;
    // When disable_copy_deflicker is true, ignore GameCube 480i vertical blur filter for crisp HD output
    state_.deflicker_disabled = cfg_.disable_copy_deflicker;
}

// ============================================================================
// Tools.rel Relocatable Module Loader (OSLink 0x800F56E0)
// ============================================================================
static uint32_t read_be32_rel(const uint8_t* p) {
    return (static_cast<uint32_t>(p[0]) << 24) |
           (static_cast<uint32_t>(p[1]) << 16) |
           (static_cast<uint32_t>(p[2]) << 8)  |
           static_cast<uint32_t>(p[3]);
}

bool ToolsRelLoader::link_rel_module(
    const std::vector<uint8_t>& rel_bytes,
    Memory& mem,
    uint32_t base_load_vaddr,
    RelModuleHeader& out_hdr,
    uint32_t& out_prolog_vaddr
) {
    if (rel_bytes.size() < 64) return false;
    out_hdr.id               = read_be32_rel(&rel_bytes[0x00]);
    out_hdr.num_sections     = read_be32_rel(&rel_bytes[0x0C]);
    out_hdr.section_info_off = read_be32_rel(&rel_bytes[0x10]);
    out_hdr.version          = read_be32_rel(&rel_bytes[0x1C]);
    out_hdr.bss_size         = read_be32_rel(&rel_bytes[0x20]);
    out_hdr.rel_off          = read_be32_rel(&rel_bytes[0x24]);
    out_hdr.imp_off          = read_be32_rel(&rel_bytes[0x28]);
    out_hdr.imp_size         = read_be32_rel(&rel_bytes[0x2C]);
    out_hdr.prolog_section   = rel_bytes[0x30];
    out_hdr.epilog_section   = rel_bytes[0x31];
    out_hdr.prolog_offset    = read_be32_rel(&rel_bytes[0x34]);
    out_hdr.epilog_offset    = read_be32_rel(&rel_bytes[0x38]);

    if (out_hdr.section_info_off + out_hdr.num_sections * 8 > rel_bytes.size()) {
        return false;
    }

    std::vector<uint32_t> sec_vaddrs(out_hdr.num_sections, 0);
    uint32_t cur_vaddr = base_load_vaddr;

    for (uint32_t i = 0; i < out_hdr.num_sections; ++i) {
        const uint8_t* sinfo = &rel_bytes[out_hdr.section_info_off + i * 8];
        uint32_t off_raw = read_be32_rel(&sinfo[0]);
        uint32_t len     = read_be32_rel(&sinfo[4]);
        uint32_t sec_off = off_raw & ~3u;
        if (len == 0) continue;

        cur_vaddr = (cur_vaddr + 31u) & ~31u;
        sec_vaddrs[i] = cur_vaddr;
        if (sec_off > 0 && sec_off + len <= rel_bytes.size()) {
            mem.write_bytes(cur_vaddr, &rel_bytes[sec_off], len);
        }
        cur_vaddr += len;
    }

    if (out_hdr.prolog_section < sec_vaddrs.size()) {
        out_prolog_vaddr = sec_vaddrs[out_hdr.prolog_section] + out_hdr.prolog_offset;
    } else {
        out_prolog_vaddr = 0;
    }
    return true;
}

} // namespace pn03

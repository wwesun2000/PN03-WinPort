#include "pn03_gx_3d_interface.hpp"
#include "pn03_symbols.hpp"
#include <algorithm>
#include <bit>
#include <cmath>
#include <cstring>
#if defined(_MSC_VER)
#include <intrin.h>
#include <xmmintrin.h>
#endif

namespace pn03 {

static inline uint16_t read_be16_unaligned(const uint8_t* p) noexcept {
    uint16_t v = 0;
    std::memcpy(&v, p, 2);
#if defined(_MSC_VER)
    return _byteswap_ushort(v);
#else
    return static_cast<uint16_t>((v >> 8) | (v << 8));
#endif
}

static inline uint32_t read_be32_unaligned(const uint8_t* p) noexcept {
    uint32_t v = 0;
    std::memcpy(&v, p, 4);
#if defined(_MSC_VER)
    return _byteswap_ulong(v);
#else
    return ((v >> 24) & 0xFFu) | ((v >> 8) & 0xFF00u) | ((v & 0xFF00u) << 8) | (v << 24);
#endif
}

static inline float read_be_f32_unaligned(const uint8_t* p) noexcept {
    const uint32_t bits = read_be32_unaligned(p);
    float fv = 0.0f;
    std::memcpy(&fv, &bits, 4);
    return fv;
}

static inline float fast_inv_sqrt(float x) noexcept {
#if defined(_MSC_VER) && (defined(_M_X64) || defined(_M_IX86))
    const __m128 vx = _mm_set_ss(x);
    const __m128 y  = _mm_rsqrt_ss(vx);
    const __m128 half_x = _mm_mul_ss(_mm_set_ss(0.5f), vx);
    const __m128 y2 = _mm_mul_ss(y, y);
    const __m128 nr = _mm_mul_ss(y, _mm_sub_ss(_mm_set_ss(1.5f), _mm_mul_ss(half_x, y2)));
    return _mm_cvtss_f32(nr);
#else
    return 1.0f / std::sqrt(x);
#endif
}

static RuntimeConfig g_gx_cfg{};
static GX3DInterface g_gx_instance(g_gx_cfg);

GX3DInterface& global_gx_3d_interface() {
    return g_gx_instance;
}

void set_global_gx_config(const RuntimeConfig& cfg) {
    g_gx_cfg = cfg;
    g_gx_instance = GX3DInterface(cfg);
}

float resolve_target_aspect_ratio(AspectRatioMode mode) noexcept {
    switch (mode) {
        case AspectRatioMode::Widescreen_16_9: return 16.0f / 9.0f;
        case AspectRatioMode::Ultrawide_21_9:  return 21.0f / 9.0f;
        default:                               return 4.0f / 3.0f;
    }
}

void patch_widescreen_aspect_constants(Memory& mem, AspectRatioMode mode) {
    const float target_aspect = resolve_target_aspect_ratio(mode);
    static constexpr uint32_t kAspectConstAddrs[3] = {
        0x80163D94u, // ViewInitPerspective / camera constant (4/3)
        0x80163E60u, // C_MTXPerspective aspect constant (4/3)
        0x8016B74Cu, // Secondary C_MTXPerspective / frustum constant (4/3)
    };
    for (uint32_t vaddr : kAspectConstAddrs) {
        if (mem.is_valid_range(vaddr, 4u)) {
            mem.write_f32(vaddr, target_aspect);
        }
    }
}

uint32_t resolve_vi_wait_cadence(const Memory& mem) {
    if (!mem.is_valid_range(recomp::sym_addr::kSda_pG, 4u)) {
        return 1u;
    }
    const uint32_t pG_addr = mem.read_u32(recomp::sym_addr::kSda_pG);
    if (pG_addr < kGcRamBase || !mem.is_valid_range(pG_addr + 284u, 4u)) {
        return 1u;
    }
    const uint32_t wait_cnt = mem.read_u32(pG_addr + 284u);
    return (std::clamp)(wait_cnt, 1u, 4u);
}

static void fifo_cb_u8(void* user, uint8_t val) {
    static_cast<GX3DInterface*>(user)->on_fifo_write_u8(val);
}
static void fifo_cb_u16(void* user, uint16_t val) {
    static_cast<GX3DInterface*>(user)->on_fifo_write_u16(val);
}
static void fifo_cb_u32(void* user, uint32_t val) {
    static_cast<GX3DInterface*>(user)->on_fifo_write_u32(val);
}
static void fifo_cb_f32(void* user, float val) {
    static_cast<GX3DInterface*>(user)->on_fifo_write_f32(val);
}

GX3DInterface::GX3DInterface(const RuntimeConfig& cfg) : cfg_(cfg) {
    std::memset(proj_mtx_, 0, sizeof(proj_mtx_));
    // Default orthographic projection for 640x480 screen space:
    // X: [0..640] -> [-1..+1], Y: [0..480] -> [+1..-1], Z: [-1000..+1000] -> [0..1]
    proj_mtx_[0][0] =  2.0f / 640.0f;
    proj_mtx_[0][3] = -1.0f;
    proj_mtx_[1][1] = -2.0f / 480.0f;
    proj_mtx_[1][3] =  1.0f;
    proj_mtx_[2][2] =  1.0f / 2000.0f;
    proj_mtx_[2][3] = -0.5f;
    proj_mtx_[3][3] =  1.0f;
    proj_type_      =  1u; // GX_ORTHOGRAPHIC default until GXSetProjection is called

    for (int t = 0; t < 20; ++t) {
        std::memset(tex_mtx_[t], 0, sizeof(tex_mtx_[t]));
        tex_mtx_[t][0][0] = tex_mtx_[t][1][1] = tex_mtx_[t][2][2] = 1.0f;
    }

    for (int m = 0; m < 10; ++m) {
        std::memset(pos_mtx_[m], 0, sizeof(pos_mtx_[m]));
        pos_mtx_[m][0][0] = pos_mtx_[m][1][1] = pos_mtx_[m][2][2] = 1.0f;
        std::memset(nrm_mtx_[m], 0, sizeof(nrm_mtx_[m]));
        nrm_mtx_[m][0][0] = nrm_mtx_[m][1][1] = nrm_mtx_[m][2][2] = 1.0f;
    }
    for (int s = 0; s < 4; ++s) {
        tev_colors_[s][0]  = tev_colors_[s][1]  = tev_colors_[s][2]  = tev_colors_[s][3]  = 1.0f;
        tev_kcolors_[s][0] = tev_kcolors_[s][1] = tev_kcolors_[s][2] = tev_kcolors_[s][3] = 1.0f;
    }
    clear_vtx_desc();
    for (uint8_t fmt = 0; fmt < 8; ++fmt) {
        vat_table_[fmt][GX_VA_POS]  = {1u, 4u, 0u}; // XYZ, F32
        vat_table_[fmt][GX_VA_NRM]  = {0u, 4u, 0u}; // XYZ, F32
        vat_table_[fmt][GX_VA_CLR0] = {1u, 5u, 0u}; // RGBA, RGBA8
        vat_table_[fmt][GX_VA_CLR1] = {1u, 5u, 0u}; // RGBA, RGBA8
        for (uint32_t t = GX_VA_TEX0; t <= GX_VA_TEX7; ++t) {
            vat_table_[fmt][t] = {1u, 4u, 0u}; // ST, F32
        }
    }
}

void GX3DInterface::bind_fifo_to_memory(Memory& mem) {
    bound_mem_ = &mem;
    mem.set_fifo_callbacks(this, &fifo_cb_u8, &fifo_cb_u16, &fifo_cb_u32, &fifo_cb_f32);
}

void GX3DInterface::clear_frame_geometry() {
    prim_Staging_.clear();
    vertex_buffer_.clear();
    index_buffer_.clear();
    draw_batches_.clear();
    batch_state_dirty_ = true;
    overlay_texts_.clear();
    fifo_stream_buf_.clear();
    in_gx_begin_ = false;
    has_pending_vtx_mtx_idx_ = false;
}

void GX3DInterface::submit_overlay_text(float x, float y, float scale, uint32_t rgba, const std::string& text) {
    if (text.empty()) return;
    overlay_texts_.push_back(GXOverlayTextItem{x, y, scale, rgba, text});
}

void GX3DInterface::apply_aspect_ratio_to_projection() {
    if (proj_type_ != 0u) return; // Keep orthographic (UI/2D) projections unstretched
    if (cfg_.aspect_ratio == AspectRatioMode::Original_4_3) return;
    const float tgt_aspect = resolve_target_aspect_ratio(cfg_.aspect_ratio);
    if (tgt_aspect <= 0.0f) return;
    const float p00 = std::fabs(proj_mtx_[0][0]);
    const float p11 = std::fabs(proj_mtx_[1][1]);
    if (p00 > 1e-6f && p11 > 1e-6f) {
        const float encoded_aspect = p11 / p00;
        if (std::fabs(encoded_aspect - tgt_aspect) < 0.02f) {
            return; // Already constructed for target widescreen aspect via patched DOL constants
        }
    }
    proj_mtx_[0][0] *= (4.0f / 3.0f) / tgt_aspect;
}

float GX3DInterface::effective_tev_scale() const {
    if (!tev_scale_dirty_) {
        return cached_tev_scale_;
    }
    float scale_acc = 1.0f;
    const uint32_t count = std::clamp(num_tev_stages_, 1u, 16u);
    for (uint32_t s = 0; s < count; ++s) {
        const auto& st = tev_stages_[s];
        if (st.color_op <= 1u && st.color_out_reg == 0u) {
            float f = 1.0f;
            if (st.color_scale == 1u) f = 2.0f;
            else if (st.color_scale == 2u) f = 4.0f;
            else if (st.color_scale == 3u) f = 0.5f;
            const bool uses_cprev = (s == 0u) ||
                (st.color_in[0] == 0u || st.color_in[1] == 0u ||
                 st.color_in[2] == 0u || st.color_in[3] == 0u);
            if (uses_cprev) {
                scale_acc *= f;
            } else {
                scale_acc = f;
            }
        }
    }
    cached_tev_scale_ = std::clamp(scale_acc, 0.25f, 8.0f);
    tev_scale_dirty_  = false;
    return cached_tev_scale_;
}

void GX3DInterface::update_cached_stage1() const {
    cached_has_stage1_ = false;
    cached_stage1_op_  = 0u;
    for (uint32_t st_i = 1u; st_i < num_tev_stages_ && st_i < 4u; ++st_i) {
        const auto& st = tev_stages_[st_i];
        if (st.tex_map >= 8u || st.tex_coord != tev_stages_[0].tex_coord) continue;
        const auto& s1tex = bound_textures_[st.tex_map];
        if (s1tex.width == 0u || s1tex.height == 0u || s1tex.data_vaddr < kGcRamBase) continue;
        const bool color_mul = (st.color_op == 0u && st.color_in[0] == 15u && st.color_in[3] == 15u &&
                                ((st.color_in[1] == 8u && st.color_in[2] == 0u) ||
                                 (st.color_in[1] == 0u && st.color_in[2] == 8u)));
        const bool alpha_mul = (st.alpha_op == 0u && st.alpha_in[0] == 7u && st.alpha_in[3] == 7u &&
                                ((st.alpha_in[1] == 4u && st.alpha_in[2] == 0u) ||
                                 (st.alpha_in[1] == 0u && st.alpha_in[2] == 4u)));
        if (color_mul || alpha_mul) {
            cached_has_stage1_  = true;
            cached_stage1_op_   = (color_mul && alpha_mul) ? 2u : (alpha_mul ? 1u : 3u);
            cached_stage1_tex_  = s1tex;
            cached_stage1_tlut_ = tlut_slots_[s1tex.tlut_name % 20u];
            break;
        }
    }
    stage1_dirty_ = false;
}

void GX3DInterface::clear_vtx_desc() {
    vtx_desc_mask_ = 0u;
    vtx_desc_types_.fill(GX_NONE);
    dl_plan_valid_mask_ = 0u;
}

void GX3DInterface::set_vtx_desc(uint32_t attr, uint8_t type) {
    if (attr < GX_VA_MAX_ATTR && vtx_desc_types_[attr] != type) {
        vtx_desc_types_[attr] = type;
        if (type != GX_NONE) {
            vtx_desc_mask_ |= (1u << (attr & 31u));
        } else {
            vtx_desc_mask_ &= ~(1u << (attr & 31u));
        }
        dl_plan_valid_mask_ = 0u;
    }
}

void GX3DInterface::set_vtx_attr_fmt(uint8_t vtxfmt, uint32_t attr, uint32_t comp_cnt, uint32_t comp_type, uint8_t frac) {
    if (vtxfmt < 8 && attr < GX_VA_MAX_ATTR) {
        auto& slot = vat_table_[vtxfmt][attr];
        if (slot.comp_cnt != comp_cnt || slot.comp_type != comp_type || slot.frac != frac) {
            slot = GXVtxAttrFmtSpec{comp_cnt, comp_type, frac};
            dl_plan_valid_mask_ &= static_cast<uint16_t>(~((1u << vtxfmt) | (1u << (vtxfmt + 8u))));
        }
    }
}

void GX3DInterface::set_array(uint32_t attr, uint32_t base_vaddr, uint8_t stride) {
    if (attr < GX_VA_MAX_ATTR) {
        auto& slot = array_table_[attr];
        if (slot.base_vaddr != base_vaddr || slot.stride != stride) {
            slot = GXArraySpec{base_vaddr, stride};
            dl_plan_valid_mask_ = 0u;
        }
    }
}

static uint32_t comp_type_byte_size(uint32_t comp_type) noexcept {
    switch (comp_type) {
        case 0: // GX_U8
        case 1: // GX_S8
            return 1u;
        case 2: // GX_U16
        case 3: // GX_S16
            return 2u;
        case 4: // GX_F32
        default:
            return 4u;
    }
}

static uint32_t color_type_byte_size(uint32_t comp_type) noexcept {
    switch (comp_type) {
        case 0: // GX_RGB565
        case 3: // GX_RGBA4
            return 2u;
        case 1: // GX_RGB8
        case 4: // GX_RGBA6
            return 3u;
        case 2: // GX_RGBX8
        case 5: // GX_RGBA8
        default:
            return 4u;
    }
}

static uint32_t attr_byte_size(uint32_t attr, const GXVtxAttrFmtSpec& spec) noexcept {
    if (attr < GX_VA_POS) {
        return 1u;
    } else if (attr == GX_VA_POS) {
        uint32_t ncomp = (spec.comp_cnt == 0u) ? 2u : 3u;
        return ncomp * comp_type_byte_size(spec.comp_type);
    } else if (attr == GX_VA_NRM) {
        return 3u * comp_type_byte_size(spec.comp_type);
    } else if (attr == GX_VA_CLR0 || attr == GX_VA_CLR1) {
        return color_type_byte_size(spec.comp_type);
    } else if (attr >= GX_VA_TEX0 && attr <= GX_VA_TEX7) {
        uint32_t ncomp = (spec.comp_cnt == 0u) ? 1u : 2u;
        return ncomp * comp_type_byte_size(spec.comp_type);
    }
    return 0u;
}

uint32_t GX3DInterface::compute_vertex_byte_stride(uint8_t vtx_fmt) const {
    const auto& vat = vat_table_[vtx_fmt & 7u];
    uint32_t total = 0;
    uint32_t mask = vtx_desc_mask_ & 0x001FFFFFu;
    while (mask != 0u) {
        const uint32_t attr = static_cast<uint32_t>(std::countr_zero(mask));
        mask &= (mask - 1u);
        const uint8_t dt = vtx_desc_types_[attr];
        if (dt == GX_INDEX8) {
            total += 1u;
        } else if (dt == GX_INDEX16) {
            total += 2u;
        } else {
            total += attr_byte_size(attr, vat[attr]);
        }
    }
    return total;
}

static constexpr float kInvPow2[32] = {
    1.0f, 0.5f, 0.25f, 0.125f,
    1.0f / 16.0f, 1.0f / 32.0f, 1.0f / 64.0f, 1.0f / 128.0f,
    1.0f / 256.0f, 1.0f / 512.0f, 1.0f / 1024.0f, 1.0f / 2048.0f,
    1.0f / 4096.0f, 1.0f / 8192.0f, 1.0f / 16384.0f, 1.0f / 32768.0f,
    1.0f / 65536.0f, 1.0f / 131072.0f, 1.0f / 262144.0f, 1.0f / 524288.0f,
    1.0f / 1048576.0f, 1.0f / 2097152.0f, 1.0f / 4194304.0f, 1.0f / 8388608.0f,
    1.0f / 16777216.0f, 1.0f / 33554432.0f, 1.0f / 67108864.0f, 1.0f / 134217728.0f,
    1.0f / 268435456.0f, 1.0f / 536870912.0f, 1.0f / 1073741824.0f, 1.0f / 2147483648.0f
};

static constexpr float kInv15  = 1.0f / 15.0f;
static constexpr float kInv31  = 1.0f / 31.0f;
static constexpr float kInv63  = 1.0f / 63.0f;
static constexpr float kInv255 = 1.0f / 255.0f;

static inline float read_typed_component_scaled(const uint8_t* p, uint32_t& off, uint32_t comp_type, float scale) noexcept {
    switch (comp_type) {
        case 0: { // GX_U8
            const uint8_t v = p[off++];
            return static_cast<float>(v) * scale;
        }
        case 1: { // GX_S8
            const int8_t v = static_cast<int8_t>(p[off++]);
            return static_cast<float>(v) * scale;
        }
        case 2: { // GX_U16 BE
            const uint16_t v = read_be16_unaligned(p + off);
            off += 2;
            return static_cast<float>(v) * scale;
        }
        case 3: { // GX_S16 BE
            const int16_t v = static_cast<int16_t>(read_be16_unaligned(p + off));
            off += 2;
            return static_cast<float>(v) * scale;
        }
        case 4: // GX_F32 BE
        default: {
            const float fv = read_be_f32_unaligned(p + off);
            off += 4;
            return fv;
        }
    }
}

static inline float read_typed_component(const uint8_t* p, uint32_t& off, uint32_t comp_type, uint8_t frac) noexcept {
    const float scale = (frac < 31u) ? kInvPow2[frac] : 1.0f;
    return read_typed_component_scaled(p, off, comp_type, scale);
}

static PN03_FORCEINLINE void read_color_direct(const uint8_t* p, uint32_t comp_type, float out_rgba[4]) noexcept {
    switch (comp_type) {
        case 0: { // GX_RGB565
            const uint16_t v = read_be16_unaligned(p);
            out_rgba[0] = static_cast<float>((v >> 11) & 0x1Fu) * kInv31;
            out_rgba[1] = static_cast<float>((v >> 5)  & 0x3Fu) * kInv63;
            out_rgba[2] = static_cast<float>(v         & 0x1Fu) * kInv31;
            out_rgba[3] = 1.0f;
            break;
        }
        case 1: { // GX_RGB8
            out_rgba[0] = static_cast<float>(p[0]) * kInv255;
            out_rgba[1] = static_cast<float>(p[1]) * kInv255;
            out_rgba[2] = static_cast<float>(p[2]) * kInv255;
            out_rgba[3] = 1.0f;
            break;
        }
        case 3: { // GX_RGBA4
            const uint16_t v = read_be16_unaligned(p);
            out_rgba[0] = static_cast<float>((v >> 12) & 0xFu) * kInv15;
            out_rgba[1] = static_cast<float>((v >> 8)  & 0xFu) * kInv15;
            out_rgba[2] = static_cast<float>((v >> 4)  & 0xFu) * kInv15;
            out_rgba[3] = static_cast<float>(v         & 0xFu) * kInv15;
            break;
        }
        case 4: { // GX_RGBA6 (3 bytes: RRRRRRGG GGGGBBBB BBAAAAAA)
            const uint32_t packed = (uint32_t(p[0]) << 16) | (uint32_t(p[1]) << 8) | uint32_t(p[2]);
            out_rgba[0] = static_cast<float>((packed >> 18) & 0x3Fu) * kInv63;
            out_rgba[1] = static_cast<float>((packed >> 12) & 0x3Fu) * kInv63;
            out_rgba[2] = static_cast<float>((packed >>  6) & 0x3Fu) * kInv63;
            out_rgba[3] = static_cast<float>(packed         & 0x3Fu) * kInv63;
            break;
        }
        case 2: // GX_RGBX8
        case 5: // GX_RGBA8
        default: {
            out_rgba[0] = static_cast<float>(p[0]) * kInv255;
            out_rgba[1] = static_cast<float>(p[1]) * kInv255;
            out_rgba[2] = static_cast<float>(p[2]) * kInv255;
            out_rgba[3] = (comp_type == 2) ? 1.0f : (static_cast<float>(p[3]) * kInv255);
            break;
        }
    }
}

static PN03_FORCEINLINE void read_vec3_direct(const uint8_t* p, uint32_t comp_type, bool read_z, float scale, float out[3]) noexcept {
    switch (comp_type) {
        case 0: // GX_U8
            out[0] = static_cast<float>(p[0]) * scale;
            out[1] = static_cast<float>(p[1]) * scale;
            out[2] = read_z ? (static_cast<float>(p[2]) * scale) : 0.0f;
            break;
        case 1: // GX_S8
            out[0] = static_cast<float>(static_cast<int8_t>(p[0])) * scale;
            out[1] = static_cast<float>(static_cast<int8_t>(p[1])) * scale;
            out[2] = read_z ? (static_cast<float>(static_cast<int8_t>(p[2])) * scale) : 0.0f;
            break;
        case 2: // GX_U16 BE
            out[0] = static_cast<float>(read_be16_unaligned(p + 0)) * scale;
            out[1] = static_cast<float>(read_be16_unaligned(p + 2)) * scale;
            out[2] = read_z ? (static_cast<float>(read_be16_unaligned(p + 4)) * scale) : 0.0f;
            break;
        case 3: // GX_S16 BE
            out[0] = static_cast<float>(static_cast<int16_t>(read_be16_unaligned(p + 0))) * scale;
            out[1] = static_cast<float>(static_cast<int16_t>(read_be16_unaligned(p + 2))) * scale;
            out[2] = read_z ? (static_cast<float>(static_cast<int16_t>(read_be16_unaligned(p + 4))) * scale) : 0.0f;
            break;
        case 4: // GX_F32 BE
        default:
            out[0] = read_be_f32_unaligned(p + 0);
            out[1] = read_be_f32_unaligned(p + 4);
            out[2] = read_z ? read_be_f32_unaligned(p + 8) : 0.0f;
            break;
    }
}

static PN03_FORCEINLINE void read_vec2_direct(const uint8_t* p, uint32_t comp_type, bool read_t, float scale, float out[2]) noexcept {
    switch (comp_type) {
        case 0: // GX_U8
            out[0] = static_cast<float>(p[0]) * scale;
            out[1] = read_t ? (static_cast<float>(p[1]) * scale) : 0.0f;
            break;
        case 1: // GX_S8
            out[0] = static_cast<float>(static_cast<int8_t>(p[0])) * scale;
            out[1] = read_t ? (static_cast<float>(static_cast<int8_t>(p[1])) * scale) : 0.0f;
            break;
        case 2: // GX_U16 BE
            out[0] = static_cast<float>(read_be16_unaligned(p + 0)) * scale;
            out[1] = read_t ? (static_cast<float>(read_be16_unaligned(p + 2)) * scale) : 0.0f;
            break;
        case 3: // GX_S16 BE
            out[0] = static_cast<float>(static_cast<int16_t>(read_be16_unaligned(p + 0))) * scale;
            out[1] = read_t ? (static_cast<float>(static_cast<int16_t>(read_be16_unaligned(p + 2))) * scale) : 0.0f;
            break;
        case 4: // GX_F32 BE
        default:
            out[0] = read_be_f32_unaligned(p + 0);
            out[1] = read_t ? read_be_f32_unaligned(p + 4) : 0.0f;
            break;
    }
}

static inline void read_typed_color(const uint8_t* p, uint32_t& off, uint32_t comp_type, float out_rgba[4]) noexcept {
    read_color_direct(p + off, comp_type, out_rgba);
    off += color_type_byte_size(comp_type);
}

GXVertex GX3DInterface::decode_one_vertex_from_stream(
    const uint8_t* stream_ptr,
    uint32_t& io_offset,
    uint8_t vtx_fmt,
    const Memory* mem
) const {
    GXVertex v{};
    has_pending_vtx_mtx_idx_ = false;
    const auto& vat = vat_table_[vtx_fmt & 7u];

    uint32_t mask = vtx_desc_mask_ & 0x001FFFFFu;
    while (mask != 0u) {
        const uint32_t attr = static_cast<uint32_t>(std::countr_zero(mask));
        mask &= (mask - 1u);
        const uint8_t dt = vtx_desc_types_[attr];

        const uint8_t* src_ptr = stream_ptr;
        uint32_t local_off = 0;
        uint32_t* off_ptr = &io_offset;

        if (dt == GX_INDEX8 || dt == GX_INDEX16) {
            uint32_t idx = 0;
            if (dt == GX_INDEX8) {
                idx = stream_ptr[io_offset++];
            } else {
                idx = (uint32_t(stream_ptr[io_offset]) << 8) | uint32_t(stream_ptr[io_offset + 1]);
                io_offset += 2;
            }
            uint32_t arr_base = array_table_[attr].base_vaddr;
            uint32_t arr_stride = array_table_[attr].stride;
            if (arr_stride == 0) {
                if (attr == GX_VA_POS) arr_stride = 12;
                else if (attr == GX_VA_NRM) arr_stride = 12;
                else if (attr == GX_VA_CLR0 || attr == GX_VA_CLR1) arr_stride = 4;
                else arr_stride = 8;
            }
            uint32_t elem_vaddr = arr_base + idx * arr_stride;
            uint32_t elem_size = attr_byte_size(attr, vat[attr]);
            if (elem_size == 0) elem_size = 4u;
            if (mem && mem->is_valid_range(elem_vaddr, elem_size)) {
                src_ptr = mem->raw_ptr(elem_vaddr);
                local_off = 0;
                off_ptr = &local_off;
            } else {
                continue;
            }
        }

        if (attr < GX_VA_POS) {
            uint8_t idx_val = src_ptr[*off_ptr];
            (*off_ptr) += 1u;
            if (attr == 0u) { // GX_VA_PNMTXIDX
                pending_vtx_mtx_idx_     = static_cast<uint8_t>((idx_val / 3u) % 10u);
                has_pending_vtx_mtx_idx_ = true;
            }
        } else if (attr == GX_VA_POS) {
            uint32_t ncomp = (vat[attr].comp_cnt == 0u) ? 2u : 3u;
            v.pos[0] = read_typed_component(src_ptr, *off_ptr, vat[attr].comp_type, vat[attr].frac);
            v.pos[1] = read_typed_component(src_ptr, *off_ptr, vat[attr].comp_type, vat[attr].frac);
            v.pos[2] = (ncomp == 3u) ? read_typed_component(src_ptr, *off_ptr, vat[attr].comp_type, vat[attr].frac) : 0.0f;
        } else if (attr == GX_VA_NRM) {
            uint8_t nfrac = vat[attr].frac;
            if (nfrac == 0 && vat[attr].comp_type == 3) nfrac = 14; // Default S16 normal scale (1/16384)
            else if (nfrac == 0 && vat[attr].comp_type == 1) nfrac = 6; // Default S8 normal scale (1/64)
            v.nrm[0] = read_typed_component(src_ptr, *off_ptr, vat[attr].comp_type, nfrac);
            v.nrm[1] = read_typed_component(src_ptr, *off_ptr, vat[attr].comp_type, nfrac);
            v.nrm[2] = read_typed_component(src_ptr, *off_ptr, vat[attr].comp_type, nfrac);
        } else if (attr == GX_VA_CLR0) {
            read_typed_color(src_ptr, *off_ptr, vat[attr].comp_type, v.color0);
        } else if (attr == GX_VA_CLR1) {
            float dummy[4];
            read_typed_color(src_ptr, *off_ptr, vat[attr].comp_type, dummy);
        } else if (attr == GX_VA_TEX0) {
            uint32_t ncomp = (vat[attr].comp_cnt == 0u) ? 1u : 2u;
            v.uv0[0] = read_typed_component(src_ptr, *off_ptr, vat[attr].comp_type, vat[attr].frac);
            v.uv0[1] = (ncomp == 2u) ? read_typed_component(src_ptr, *off_ptr, vat[attr].comp_type, vat[attr].frac) : 0.0f;
        } else if (attr > GX_VA_TEX0 && attr <= GX_VA_TEX7) {
            uint32_t ncomp = (vat[attr].comp_cnt == 0u) ? 1u : 2u;
            for (uint32_t c = 0; c < ncomp; ++c) {
                (void)read_typed_component(src_ptr, *off_ptr, vat[attr].comp_type, vat[attr].frac);
            }
        }
    }
    return v;
}

void GX3DInterface::try_flush_fifo_vertices() {
    if (!in_gx_begin_ || expected_verts_ == 0 || current_vtx_byte_stride_ == 0) {
        return;
    }
    uint32_t needed_bytes = static_cast<uint32_t>(expected_verts_) * current_vtx_byte_stride_;
    if (fifo_stream_buf_.size() < needed_bytes) {
        return;
    }
    const Memory* mem = bound_mem_ ? bound_mem_ : Memory::active_instance();
    uint32_t off = 0;
    uint16_t nverts = expected_verts_;
    // Set in_gx_begin_ false before submitting so end_primitive resets cleanly
    in_gx_begin_ = false;
    for (uint16_t i = 0; i < nverts; ++i) {
        GXVertex v = decode_one_vertex_from_stream(fifo_stream_buf_.data(), off, active_vtx_fmt_, mem);
        submit_vertex(v);
    }
    fifo_stream_buf_.clear();
}

void GX3DInterface::on_fifo_write_u8(uint8_t val) {
    if (!in_gx_begin_) return;
    fifo_stream_buf_.push_back(val);
    try_flush_fifo_vertices();
}

void GX3DInterface::on_fifo_write_u16(uint16_t val) {
    if (!in_gx_begin_) return;
    fifo_stream_buf_.push_back(static_cast<uint8_t>(val >> 8));
    fifo_stream_buf_.push_back(static_cast<uint8_t>(val & 0xFFu));
    try_flush_fifo_vertices();
}

void GX3DInterface::on_fifo_write_u32(uint32_t val) {
    if (!in_gx_begin_) return;
    fifo_stream_buf_.push_back(static_cast<uint8_t>((val >> 24) & 0xFFu));
    fifo_stream_buf_.push_back(static_cast<uint8_t>((val >> 16) & 0xFFu));
    fifo_stream_buf_.push_back(static_cast<uint8_t>((val >> 8)  & 0xFFu));
    fifo_stream_buf_.push_back(static_cast<uint8_t>(val         & 0xFFu));
    try_flush_fifo_vertices();
}

void GX3DInterface::on_fifo_write_f32(float val) {
    uint32_t bits = 0;
    std::memcpy(&bits, &val, 4);
    on_fifo_write_u32(bits);
}

namespace {

static inline uint32_t default_array_stride(uint32_t attr) noexcept {
    if (attr == GX_VA_POS || attr == GX_VA_NRM) return 12u;
    if (attr == GX_VA_CLR0 || attr == GX_VA_CLR1) return 4u;
    return 8u;
}

static inline size_t expected_index_count(GXPrimitive prim, size_t n) noexcept {
    if (prim == GX_TRIANGLES) return (n / 3u) * 3u;
    if (prim == GX_TRIANGLESTRIP || prim == GX_TRIANGLEFAN) return (n >= 3u) ? (n - 2u) * 3u : 0u;
    if (prim == GX_QUADS) return (n / 4u) * 6u;
    if (prim == GX_LINES || prim == GX_LINESTRIP) return (n >= 2u) ? (n - 1u) * 3u : 0u;
    return 0u;
}

static PN03_FORCEINLINE float clamp01(float x) noexcept {
    return std::min(1.0f, std::max(0.0f, x));
}

static PN03_FORCEINLINE const uint8_t* resolve_dl_attr_ptr(
    const uint8_t dt, uint16_t dl_offset, const uint8_t* arr_ptr,
    uint32_t arr_base, uint16_t arr_stride, uint32_t max_byte_off,
    uint8_t elem_size, const uint8_t* vptr, const Memory& mem
) noexcept {
    if (dt == GX_DIRECT) {
        return vptr + dl_offset;
    }
    const uint32_t idx = (dt == GX_INDEX8)
        ? vptr[dl_offset]
        : read_be16_unaligned(vptr + dl_offset);
    const uint32_t byte_off = idx * static_cast<uint32_t>(arr_stride);
    if (arr_ptr) [[likely]] {
        return (byte_off <= max_byte_off) ? (arr_ptr + byte_off) : nullptr;
    }
    const uint32_t elem_vaddr = arr_base + byte_off;
    return mem.is_valid_range(elem_vaddr, elem_size) ? mem.raw_ptr(elem_vaddr) : nullptr;
}

} // namespace

void GX3DInterface::rebuild_dl_plan(const Memory& mem, uint8_t vtx_fmt, bool need_nrm, DLAttrPlan& plan) const {
    const auto& vat = vat_table_[vtx_fmt & 7u];
    plan = DLAttrPlan{};
    uint32_t mask = vtx_desc_mask_ & 0x001FFFFFu;
    while (mask != 0u) {
        const uint32_t attr = static_cast<uint32_t>(std::countr_zero(mask));
        mask &= (mask - 1u);
        const uint8_t dt = vtx_desc_types_[attr];

        uint32_t esize = attr_byte_size(attr, vat[attr]);
        if (esize == 0u) esize = 4u;
        const uint8_t stream_bytes = (dt == GX_INDEX8) ? 1u : ((dt == GX_INDEX16) ? 2u : static_cast<uint8_t>(esize));
        const uint16_t dl_offset = static_cast<uint16_t>(plan.vtx_stride);
        plan.vtx_stride += stream_bytes;

        DLAttrOp* dst = nullptr;
        float scale = 1.0f;
        if (attr == 0u) {
            plan.has_mtx = true;
            dst = &plan.op_mtx;
        } else if (attr == GX_VA_POS) {
            plan.has_pos = true;
            dst = &plan.op_pos;
            scale = (vat[attr].frac < 31u) ? kInvPow2[vat[attr].frac] : 1.0f;
        } else if (attr == GX_VA_NRM) {
            if (need_nrm) {
                plan.has_nrm = true;
                dst = &plan.op_nrm;
                uint8_t nfrac = vat[attr].frac;
                if (nfrac == 0u && vat[attr].comp_type == 3u) nfrac = 14u;
                else if (nfrac == 0u && vat[attr].comp_type == 1u) nfrac = 6u;
                scale = (nfrac < 31u) ? kInvPow2[nfrac] : 1.0f;
            }
        } else if (attr == GX_VA_CLR0) {
            plan.has_clr0 = true;
            dst = &plan.op_clr0;
        } else if (attr == GX_VA_TEX0) {
            plan.has_tex0 = true;
            dst = &plan.op_tex0;
            scale = (vat[attr].frac < 31u) ? kInvPow2[vat[attr].frac] : 1.0f;
        }
        if (!dst) continue;

        DLAttrOp& op = *dst;
        op = DLAttrOp{};
        op.dt        = dt;
        op.comp_cnt  = static_cast<uint8_t>(vat[attr].comp_cnt);
        op.comp_type = static_cast<uint8_t>(vat[attr].comp_type);
        op.elem_size = static_cast<uint8_t>(esize);
        op.dl_offset = dl_offset;
        op.scale     = scale;

        if (dt == GX_INDEX8 || dt == GX_INDEX16) {
            op.arr_base = array_table_[attr].base_vaddr;
            uint32_t stride = array_table_[attr].stride;
            if (stride == 0u) stride = default_array_stride(attr);
            op.arr_stride = static_cast<uint16_t>(stride);
            if (const uint8_t* p = mem.fast_ram_ptr(op.arr_base, esize)) {
                const uint32_t phys = op.arr_base & 0x01FFFFFFu;
                op.arr_ptr = p;
                op.max_byte_off = kGcRamSize - esize - phys;
            }
        }
    }
}

const GX3DInterface::DLAttrPlan& GX3DInterface::get_or_build_dl_plan(const Memory& mem, uint8_t vtx_fmt, bool need_nrm) const {
    if (&mem != dl_plan_mem_) {
        dl_plan_valid_mask_ = 0u;
        dl_plan_mem_ = &mem;
    }
    const uint32_t fmt = vtx_fmt & 7u;
    const uint32_t idx = (need_nrm ? 8u : 0u) | fmt;
    const uint16_t bit = static_cast<uint16_t>(1u << idx);
    if ((dl_plan_valid_mask_ & bit) == 0u) {
        rebuild_dl_plan(mem, static_cast<uint8_t>(fmt), need_nrm, dl_plans_[idx]);
        dl_plan_valid_mask_ |= bit;
    }
    return dl_plans_[idx];
}

void GX3DInterface::execute_display_list(const Memory& mem, uint32_t list_vaddr, uint32_t byte_len) {
    if (!mem.is_valid_range(list_vaddr, byte_len) || byte_len == 0) {
        return;
    }

    auto eval_dl_chan_light = [](
        const GXLightState& Lobj, const GXChanCtrlState& cc, const float tpos[3], const float tnrm[3]
    ) noexcept -> float {
        if (cc.attn_fn == 2u && cc.diff_fn != 0u) {
            float ndotl = 0.0f;
            if (Lobj.pos_is_zero) {
                if (Lobj.dir_valid) {
                    ndotl = tnrm[0] * Lobj.dir_unit[0] + tnrm[1] * Lobj.dir_unit[1] + tnrm[2] * Lobj.dir_unit[2];
                }
            } else {
                const float lvx = Lobj.pos[0] - tpos[0];
                const float lvy = Lobj.pos[1] - tpos[1];
                const float lvz = Lobj.pos[2] - tpos[2];
                const float dist2 = lvx * lvx + lvy * lvy + lvz * lvz;
                if (dist2 > 1e-12f) {
                    ndotl = (tnrm[0] * lvx + tnrm[1] * lvy + tnrm[2] * lvz) * fast_inv_sqrt(dist2);
                }
            }
            return (cc.diff_fn == 2u) ? (ndotl > 0.0f ? ndotl : 0.0f) : ndotl;
        }
        if (cc.attn_fn == 0u) { // GX_AF_SPEC
            const float hx = Lobj.dir_valid ? Lobj.dir_unit[0] : Lobj.dir[0];
            const float hy = Lobj.dir_valid ? Lobj.dir_unit[1] : Lobj.dir[1];
            const float hz = Lobj.dir_valid ? Lobj.dir_unit[2] : Lobj.dir[2];
            const float ndoth = tnrm[0] * hx + tnrm[1] * hy + tnrm[2] * hz;
            if (ndoth < 0.0f) return 0.0f;
            const float a = std::max(0.0f, Lobj.a[0] + Lobj.a[1] * ndoth + Lobj.a[2] * ndoth * ndoth);
            const float k = std::max(0.0f, Lobj.k[0] + Lobj.k[1] * ndoth + Lobj.k[2] * ndoth * ndoth);
            return a * k;
        }
        if (cc.diff_fn == 0u && cc.attn_fn == 2u) {
            return 1.0f;
        }
        float Lx = 0.0f, Ly = 0.0f, Lz = 1.0f;
        float dist = 0.0f, dist2 = 0.0f;
        if (Lobj.pos_is_zero) {
            if (Lobj.dir_valid) {
                Lx = Lobj.dir_unit[0];
                Ly = Lobj.dir_unit[1];
                Lz = Lobj.dir_unit[2];
                dist2 = Lobj.dir[0] * Lobj.dir[0] + Lobj.dir[1] * Lobj.dir[1] + Lobj.dir[2] * Lobj.dir[2];
                dist  = (dist2 > 1e-12f) ? (dist2 * fast_inv_sqrt(dist2)) : 0.0f;
            }
        } else {
            const float lvx = Lobj.pos[0] - tpos[0];
            const float lvy = Lobj.pos[1] - tpos[1];
            const float lvz = Lobj.pos[2] - tpos[2];
            dist2 = lvx * lvx + lvy * lvy + lvz * lvz;
            if (dist2 > 1e-12f) {
                const float invd = fast_inv_sqrt(dist2);
                Lx = lvx * invd;
                Ly = lvy * invd;
                Lz = lvz * invd;
                dist = dist2 * invd;
            }
        }
        const float ndotl = tnrm[0] * Lx + tnrm[1] * Ly + tnrm[2] * Lz;
        float diff = 1.0f;
        if (cc.diff_fn == 1u) diff = ndotl;
        else if (cc.diff_fn == 2u) diff = std::max(0.0f, ndotl);
        const float cos_s = Lobj.dir_valid
            ? std::max(0.0f, Lx * Lobj.dir_unit[0] + Ly * Lobj.dir_unit[1] + Lz * Lobj.dir_unit[2])
            : 1.0f;
        const float spot = std::max(0.0f, Lobj.a[0] + Lobj.a[1] * cos_s + Lobj.a[2] * cos_s * cos_s);
        const float denom = Lobj.k[0] + Lobj.k[1] * dist + Lobj.k[2] * dist2;
        const float dist_att = (denom > 1e-6f) ? (1.0f / denom) : 1.0f;
        return diff * spot * dist_att;
    };

    // Hoist GX pipeline state invariant across the entire display list (and any 0x40 sub-DLs).
    const bool need_lighting = (num_chans_ > 0u);
    const auto& cc_rgb = chan_ctrl_[0];
    const auto& cc_alp = chan_ctrl_[2];
    const uint32_t rgb_mask = (need_lighting && cc_rgb.enable) ? (cc_rgb.light_mask & loaded_lights_mask_) : 0u;
    const uint32_t alp_mask = (need_lighting && cc_alp.enable) ? (cc_alp.light_mask & loaded_lights_mask_) : 0u;
    const bool need_nrm = (rgb_mask != 0u && (cc_rgb.attn_fn == 0u || cc_rgb.diff_fn != 0u)) ||
                          (alp_mask != 0u && (cc_alp.attn_fn == 0u || cc_alp.diff_fn != 0u));

    const float (*tm)[4] = nullptr;
    if (num_tex_gens_ > 0u) {
        const uint8_t tc = (tev_stages_[0].tex_coord < 8u) ? tev_stages_[0].tex_coord : 0u;
        const uint32_t tm_id = tex_gen_mtx_[tc];
        if (tm_id >= 30u && tm_id <= 57u) {
            tm = tex_mtx_[(tm_id - 30u) / 3u];
        }
    }

    uint8_t rgb_light_ids[8]{};
    uint32_t n_rgb_lights = 0u;
    uint8_t alp_light_ids[8]{};
    uint32_t n_alp_lights = 0u;
    bool same_light_eval = false;
    bool fast_same_dir = false;
    bool diff_clamp = false;
    bool mat_rgb_reg = false;
    bool mat_alp_reg = false;
    bool amb_rgb_reg = false;
    bool amb_alp_reg = false;
    if (need_lighting) {
        for (uint32_t m_bits = rgb_mask; m_bits != 0u; m_bits &= (m_bits - 1u)) {
            rgb_light_ids[n_rgb_lights++] = static_cast<uint8_t>(std::countr_zero(m_bits));
        }
        for (uint32_t m_bits = alp_mask; m_bits != 0u; m_bits &= (m_bits - 1u)) {
            alp_light_ids[n_alp_lights++] = static_cast<uint8_t>(std::countr_zero(m_bits));
        }
        same_light_eval = cc_rgb.enable && cc_alp.enable &&
            rgb_mask != 0u && rgb_mask == alp_mask &&
            cc_rgb.diff_fn == cc_alp.diff_fn && cc_rgb.attn_fn == cc_alp.attn_fn;
        fast_same_dir = same_light_eval && cc_rgb.attn_fn == 2u && cc_rgb.diff_fn != 0u;
        diff_clamp    = (cc_rgb.diff_fn == 2u);
        mat_rgb_reg   = (cc_rgb.mat_src == 0u);
        mat_alp_reg   = (cc_alp.mat_src == 0u);
        amb_rgb_reg   = (cc_rgb.amb_src == 0u);
        amb_alp_reg   = (cc_alp.amb_src == 0u);
    }
    const float* const reg_mat = chan_mat_color_[0];
    const float* const reg_amb = chan_amb_color_[0];
    const uint32_t def_mtx_idx = current_mtx_idx_ % 10u;
    const float (*const fixed_pm)[4] = pos_mtx_[def_mtx_idx];
    const float (*const fixed_nm)[3] = has_nrm_mtx_[def_mtx_idx] ? nrm_mtx_[def_mtx_idx] : nullptr;

    const DLAttrPlan* cached_plans[8]{};
    const uint32_t dl_first_idx = static_cast<uint32_t>(index_buffer_.size());

    struct DLStackFrame {
        const uint8_t* dl;
        uint32_t byte_len;
        uint32_t cursor;
    };
    constexpr int kMaxInlineDepth = 16;
    DLStackFrame stack[kMaxInlineDepth];
    stack[0] = {mem.raw_ptr(list_vaddr), byte_len, 0u};
    int sp = 0;

    while (sp >= 0) {
        DLStackFrame& fr = stack[sp];
        if (fr.cursor >= fr.byte_len) {
            --sp;
            continue;
        }
        const uint8_t* dl = fr.dl;
        const uint32_t cur_len = fr.byte_len;
        uint32_t cursor = fr.cursor;
        const uint8_t cmd = dl[cursor++];

        if (cmd == 0x00u) {
            fr.cursor = cursor; // GX_CMD_NOP
        } else if (cmd == 0x08u) {
            fr.cursor = cursor + 5u; // GX_CMD_LOAD_CP_REG
        } else if (cmd == 0x10u) {
            if (cursor + 4u > cur_len) { --sp; continue; }
            const uint32_t xf_hdr = read_be32_unaligned(dl + cursor);
            cursor += 4u;
            const uint32_t count = ((xf_hdr >> 16) & 0xFFFFu) + 1u;
            if (cursor + count * 4u > cur_len) { --sp; continue; }
            fr.cursor = cursor + count * 4u;
        } else if (cmd == 0x20u || cmd == 0x28u || cmd == 0x30u || cmd == 0x38u) {
            fr.cursor = cursor + 4u; // GX_CMD_LOAD_INDX_A/B/C/D
        } else if (cmd == 0x40u) {
            if (cursor + 8u > cur_len) { --sp; continue; }
            const uint32_t sub_addr = read_be32_unaligned(dl + cursor);
            const uint32_t sub_len  = read_be32_unaligned(dl + cursor + 4);
            fr.cursor = cursor + 8u;
            if (sub_len > 0u && mem.is_valid_range(sub_addr, sub_len)) {
                if (sp + 1 < kMaxInlineDepth) {
                    stack[++sp] = {mem.raw_ptr(sub_addr), sub_len, 0u};
                } else {
                    execute_display_list(mem, sub_addr, sub_len);
                }
            }
        } else if (cmd == 0x48u) {
            fr.cursor = cursor; // GX_CMD_INVL_VC
        } else if (cmd == 0x61u) {
            fr.cursor = cursor + 4u; // GX_CMD_LOAD_BP_REG
        } else if ((cmd & 0x80u) != 0u) {
            if (cursor + 2u > cur_len) { --sp; continue; }
            const uint8_t prim = cmd & 0xF8u;
            const uint8_t vtx_fmt = cmd & 0x07u;
            const uint16_t nverts = read_be16_unaligned(dl + cursor);
            cursor += 2u;

            const DLAttrPlan* plan_ptr = cached_plans[vtx_fmt];
            if (!plan_ptr) [[unlikely]] {
                plan_ptr = &get_or_build_dl_plan(mem, vtx_fmt, need_nrm);
                cached_plans[vtx_fmt] = plan_ptr;
            }
            const DLAttrPlan& plan = *plan_ptr;
            const uint32_t vtx_stride = plan.vtx_stride;
            if (vtx_stride == 0 || cursor + uint32_t(nverts) * vtx_stride > cur_len) {
                --sp;
                continue;
            }
            fr.cursor = cursor + static_cast<uint32_t>(nverts) * vtx_stride;
            active_prim_             = static_cast<GXPrimitive>(prim);
            active_vtx_fmt_          = vtx_fmt;
            expected_verts_          = nverts;
            current_vtx_byte_stride_ = vtx_stride;
            in_gx_begin_             = false;
            has_pending_vtx_mtx_idx_ = false;
            if (nverts == 0u) continue;

            const uint32_t base_idx = static_cast<uint32_t>(vertex_buffer_.size());
            vertex_buffer_.resize(base_idx + nverts);
            GXVertex* dst_verts = vertex_buffer_.data() + base_idx;
            const uint8_t* vptr = dl + cursor;

            for (uint16_t v_i = 0; v_i < nverts; ++v_i, vptr += vtx_stride) {
                const float (*pm)[4] = fixed_pm;
                const float (*nm)[3] = fixed_nm;
                if (plan.has_mtx) {
                    if (const uint8_t* p = resolve_dl_attr_ptr(
                            plan.op_mtx.dt, plan.op_mtx.dl_offset, plan.op_mtx.arr_ptr,
                            plan.op_mtx.arr_base, plan.op_mtx.arr_stride, plan.op_mtx.max_byte_off,
                            plan.op_mtx.elem_size, vptr, mem)) {
                        const uint32_t mtx_idx = (p[0] / 3u) % 10u;
                        pm = pos_mtx_[mtx_idx];
                        nm = has_nrm_mtx_[mtx_idx] ? nrm_mtx_[mtx_idx] : nullptr;
                    }
                }

                float vp[3] = {0.0f, 0.0f, 0.0f};
                if (plan.has_pos) [[likely]] {
                    if (const uint8_t* p = resolve_dl_attr_ptr(
                            plan.op_pos.dt, plan.op_pos.dl_offset, plan.op_pos.arr_ptr,
                            plan.op_pos.arr_base, plan.op_pos.arr_stride, plan.op_pos.max_byte_off,
                            plan.op_pos.elem_size, vptr, mem)) [[likely]] {
                        read_vec3_direct(p, plan.op_pos.comp_type, plan.op_pos.comp_cnt != 0u, plan.op_pos.scale, vp);
                    }
                }

                GXVertex& tv = dst_verts[v_i];
                tv.pos[0] = pm[0][0] * vp[0] + pm[0][1] * vp[1] + pm[0][2] * vp[2] + pm[0][3];
                tv.pos[1] = pm[1][0] * vp[0] + pm[1][1] * vp[1] + pm[1][2] * vp[2] + pm[1][3];
                tv.pos[2] = pm[2][0] * vp[0] + pm[2][1] * vp[1] + pm[2][2] * vp[2] + pm[2][3];

                if (need_nrm) {
                    float vn[3] = {0.0f, 0.0f, 1.0f};
                    if (plan.has_nrm) [[likely]] {
                        if (const uint8_t* p = resolve_dl_attr_ptr(
                                plan.op_nrm.dt, plan.op_nrm.dl_offset, plan.op_nrm.arr_ptr,
                                plan.op_nrm.arr_base, plan.op_nrm.arr_stride, plan.op_nrm.max_byte_off,
                                plan.op_nrm.elem_size, vptr, mem)) [[likely]] {
                            read_vec3_direct(p, plan.op_nrm.comp_type, true, plan.op_nrm.scale, vn);
                        }
                    }
                    float nx, ny, nz;
                    if (nm) {
                        nx = nm[0][0] * vn[0] + nm[0][1] * vn[1] + nm[0][2] * vn[2];
                        ny = nm[1][0] * vn[0] + nm[1][1] * vn[1] + nm[1][2] * vn[2];
                        nz = nm[2][0] * vn[0] + nm[2][1] * vn[1] + nm[2][2] * vn[2];
                    } else {
                        nx = pm[0][0] * vn[0] + pm[0][1] * vn[1] + pm[0][2] * vn[2];
                        ny = pm[1][0] * vn[0] + pm[1][1] * vn[1] + pm[1][2] * vn[2];
                        nz = pm[2][0] * vn[0] + pm[2][1] * vn[1] + pm[2][2] * vn[2];
                    }
                    const float nlen2 = nx * nx + ny * ny + nz * nz;
                    if (nlen2 > 1e-12f) [[likely]] {
                        const float inv = fast_inv_sqrt(nlen2);
                        tv.nrm[0] = nx * inv;
                        tv.nrm[1] = ny * inv;
                        tv.nrm[2] = nz * inv;
                    } else {
                        tv.nrm[0] = 0.0f;
                        tv.nrm[1] = 0.0f;
                        tv.nrm[2] = 1.0f;
                    }
                } else {
                    tv.nrm[0] = 0.0f;
                    tv.nrm[1] = 0.0f;
                    tv.nrm[2] = 1.0f;
                }

                float vc[4] = {1.0f, 1.0f, 1.0f, 1.0f};
                if (plan.has_clr0) {
                    if (const uint8_t* p = resolve_dl_attr_ptr(
                            plan.op_clr0.dt, plan.op_clr0.dl_offset, plan.op_clr0.arr_ptr,
                            plan.op_clr0.arr_base, plan.op_clr0.arr_stride, plan.op_clr0.max_byte_off,
                            plan.op_clr0.elem_size, vptr, mem)) [[likely]] {
                        read_color_direct(p, plan.op_clr0.comp_type, vc);
                    }
                }

                if (!need_lighting) {
                    tv.color0[0] = vc[0];
                    tv.color0[1] = vc[1];
                    tv.color0[2] = vc[2];
                    tv.color0[3] = vc[3];
                } else if (fast_same_dir) {
                    const float mat_rgb[3] = {
                        mat_rgb_reg ? reg_mat[0] : vc[0],
                        mat_rgb_reg ? reg_mat[1] : vc[1],
                        mat_rgb_reg ? reg_mat[2] : vc[2]
                    };
                    const float mat_a = mat_alp_reg ? reg_mat[3] : vc[3];
                    float illum[4] = {
                        amb_rgb_reg ? reg_amb[0] : vc[0],
                        amb_rgb_reg ? reg_amb[1] : vc[1],
                        amb_rgb_reg ? reg_amb[2] : vc[2],
                        amb_alp_reg ? reg_amb[3] : vc[3]
                    };
                    for (uint32_t k = 0; k < n_rgb_lights; ++k) {
                        const GXLightState& L = lights_[rgb_light_ids[k]];
                        float ndotl = 0.0f;
                        if (L.pos_is_zero) {
                            if (L.dir_valid) {
                                ndotl = tv.nrm[0] * L.dir_unit[0] + tv.nrm[1] * L.dir_unit[1] + tv.nrm[2] * L.dir_unit[2];
                            }
                        } else {
                            const float lvx = L.pos[0] - tv.pos[0];
                            const float lvy = L.pos[1] - tv.pos[1];
                            const float lvz = L.pos[2] - tv.pos[2];
                            const float dist2 = lvx * lvx + lvy * lvy + lvz * lvz;
                            if (dist2 > 1e-12f) {
                                ndotl = (tv.nrm[0] * lvx + tv.nrm[1] * lvy + tv.nrm[2] * lvz) * fast_inv_sqrt(dist2);
                            }
                        }
                        const float w = diff_clamp ? (ndotl > 0.0f ? ndotl : 0.0f) : ndotl;
                        illum[0] += L.color[0] * w;
                        illum[1] += L.color[1] * w;
                        illum[2] += L.color[2] * w;
                        illum[3] += L.color[3] * w;
                    }
                    tv.color0[0] = clamp01(mat_rgb[0] * clamp01(illum[0]));
                    tv.color0[1] = clamp01(mat_rgb[1] * clamp01(illum[1]));
                    tv.color0[2] = clamp01(mat_rgb[2] * clamp01(illum[2]));
                    tv.color0[3] = clamp01(mat_a * clamp01(illum[3]));
                } else {
                    const float mat_rgb[3] = {
                        mat_rgb_reg ? reg_mat[0] : vc[0],
                        mat_rgb_reg ? reg_mat[1] : vc[1],
                        mat_rgb_reg ? reg_mat[2] : vc[2]
                    };
                    const float mat_a = mat_alp_reg ? reg_mat[3] : vc[3];
                    if (same_light_eval) {
                        float illum[4] = {
                            amb_rgb_reg ? reg_amb[0] : vc[0],
                            amb_rgb_reg ? reg_amb[1] : vc[1],
                            amb_rgb_reg ? reg_amb[2] : vc[2],
                            amb_alp_reg ? reg_amb[3] : vc[3]
                        };
                        for (uint32_t k = 0; k < n_rgb_lights; ++k) {
                            const GXLightState& L = lights_[rgb_light_ids[k]];
                            const float w = eval_dl_chan_light(L, cc_rgb, tv.pos, tv.nrm);
                            illum[0] += L.color[0] * w;
                            illum[1] += L.color[1] * w;
                            illum[2] += L.color[2] * w;
                            illum[3] += L.color[3] * w;
                        }
                        tv.color0[0] = clamp01(mat_rgb[0] * clamp01(illum[0]));
                        tv.color0[1] = clamp01(mat_rgb[1] * clamp01(illum[1]));
                        tv.color0[2] = clamp01(mat_rgb[2] * clamp01(illum[2]));
                        tv.color0[3] = clamp01(mat_a * clamp01(illum[3]));
                    } else {
                        if (cc_rgb.enable) {
                            float illum[3] = {
                                amb_rgb_reg ? reg_amb[0] : vc[0],
                                amb_rgb_reg ? reg_amb[1] : vc[1],
                                amb_rgb_reg ? reg_amb[2] : vc[2]
                            };
                            for (uint32_t k = 0; k < n_rgb_lights; ++k) {
                                const GXLightState& L = lights_[rgb_light_ids[k]];
                                const float w = eval_dl_chan_light(L, cc_rgb, tv.pos, tv.nrm);
                                illum[0] += L.color[0] * w;
                                illum[1] += L.color[1] * w;
                                illum[2] += L.color[2] * w;
                            }
                            tv.color0[0] = clamp01(mat_rgb[0] * clamp01(illum[0]));
                            tv.color0[1] = clamp01(mat_rgb[1] * clamp01(illum[1]));
                            tv.color0[2] = clamp01(mat_rgb[2] * clamp01(illum[2]));
                        } else {
                            tv.color0[0] = mat_rgb[0];
                            tv.color0[1] = mat_rgb[1];
                            tv.color0[2] = mat_rgb[2];
                        }
                        if (cc_alp.enable) {
                            float illum_a = amb_alp_reg ? reg_amb[3] : vc[3];
                            for (uint32_t k = 0; k < n_alp_lights; ++k) {
                                const GXLightState& L = lights_[alp_light_ids[k]];
                                illum_a += L.color[3] * eval_dl_chan_light(L, cc_alp, tv.pos, tv.nrm);
                            }
                            tv.color0[3] = clamp01(mat_a * clamp01(illum_a));
                        } else {
                            tv.color0[3] = mat_a;
                        }
                    }
                }

                float uv[2] = {0.0f, 0.0f};
                if (plan.has_tex0) {
                    if (const uint8_t* p = resolve_dl_attr_ptr(
                            plan.op_tex0.dt, plan.op_tex0.dl_offset, plan.op_tex0.arr_ptr,
                            plan.op_tex0.arr_base, plan.op_tex0.arr_stride, plan.op_tex0.max_byte_off,
                            plan.op_tex0.elem_size, vptr, mem)) [[likely]] {
                        read_vec2_direct(p, plan.op_tex0.comp_type, plan.op_tex0.comp_cnt != 0u, plan.op_tex0.scale, uv);
                    }
                }
                if (tm) {
                    const float s = uv[0], t = uv[1];
                    tv.uv0[0] = tm[0][0] * s + tm[0][1] * t + tm[0][2] + tm[0][3];
                    tv.uv0[1] = tm[1][0] * s + tm[1][1] * t + tm[1][2] + tm[1][3];
                } else {
                    tv.uv0[0] = uv[0];
                    tv.uv0[1] = uv[1];
                }
            }

            append_primitive_indices(base_idx, nverts);
        } else {
            --sp;
        }
    }

    const uint32_t added_indices = static_cast<uint32_t>(index_buffer_.size()) - dl_first_idx;
    if (added_indices > 0u) {
        emit_draw_batch(dl_first_idx, added_indices);
    }
}

void GX3DInterface::begin_primitive(GXPrimitive prim, uint8_t vtx_fmt, uint16_t num_verts) {
    active_prim_    = prim;
    active_vtx_fmt_ = vtx_fmt & 7u;
    expected_verts_ = num_verts;
    prim_Staging_.clear();
    prim_Staging_.reserve(num_verts);
    fifo_stream_buf_.clear();
    current_vtx_byte_stride_ = compute_vertex_byte_stride(active_vtx_fmt_);
    in_gx_begin_ = (current_vtx_byte_stride_ > 0 && num_verts > 0);
}

void GX3DInterface::transform_and_shade_vertex(
    const GXVertex& v, GXVertex& tv, uint32_t mtx_idx, bool need_lighting, bool need_nrm
) const {
    const auto& m = pos_mtx_[mtx_idx];
    tv.pos[0] = m[0][0] * v.pos[0] + m[0][1] * v.pos[1] + m[0][2] * v.pos[2] + m[0][3];
    tv.pos[1] = m[1][0] * v.pos[0] + m[1][1] * v.pos[1] + m[1][2] * v.pos[2] + m[1][3];
    tv.pos[2] = m[2][0] * v.pos[0] + m[2][1] * v.pos[1] + m[2][2] * v.pos[2] + m[2][3];

    if (need_nrm) {
        float nx = 0.0f, ny = 0.0f, nz = 1.0f;
        if (has_nrm_mtx_[mtx_idx]) {
            const auto& nm = nrm_mtx_[mtx_idx];
            nx = nm[0][0] * v.nrm[0] + nm[0][1] * v.nrm[1] + nm[0][2] * v.nrm[2];
            ny = nm[1][0] * v.nrm[0] + nm[1][1] * v.nrm[1] + nm[1][2] * v.nrm[2];
            nz = nm[2][0] * v.nrm[0] + nm[2][1] * v.nrm[1] + nm[2][2] * v.nrm[2];
        } else {
            nx = m[0][0] * v.nrm[0] + m[0][1] * v.nrm[1] + m[0][2] * v.nrm[2];
            ny = m[1][0] * v.nrm[0] + m[1][1] * v.nrm[1] + m[1][2] * v.nrm[2];
            nz = m[2][0] * v.nrm[0] + m[2][1] * v.nrm[1] + m[2][2] * v.nrm[2];
        }
        const float nlen2 = nx * nx + ny * ny + nz * nz;
        if (nlen2 > 1e-12f) {
            const float inv = fast_inv_sqrt(nlen2);
            tv.nrm[0] = nx * inv;
            tv.nrm[1] = ny * inv;
            tv.nrm[2] = nz * inv;
        } else {
            tv.nrm[0] = 0.0f;
            tv.nrm[1] = 0.0f;
            tv.nrm[2] = 1.0f;
        }
    } else {
        tv.nrm[0] = v.nrm[0];
        tv.nrm[1] = v.nrm[1];
        tv.nrm[2] = v.nrm[2];
    }

    if (need_lighting) {
        const auto& cc_rgb = chan_ctrl_[0];
        const auto& cc_alp = chan_ctrl_[2];
        const float mat_rgb[3] = {
            (cc_rgb.mat_src == 0u) ? chan_mat_color_[0][0] : v.color0[0],
            (cc_rgb.mat_src == 0u) ? chan_mat_color_[0][1] : v.color0[1],
            (cc_rgb.mat_src == 0u) ? chan_mat_color_[0][2] : v.color0[2]
        };
        const float mat_a = (cc_alp.mat_src == 0u) ? chan_mat_color_[0][3] : v.color0[3];

        auto eval_light = [&](uint32_t li, const GXChanCtrlState& cc) -> float {
            const auto& Lobj = lights_[li];
            if (cc.attn_fn == 0u) { // GX_AF_SPEC
                const float hx = Lobj.dir_valid ? Lobj.dir_unit[0] : Lobj.dir[0];
                const float hy = Lobj.dir_valid ? Lobj.dir_unit[1] : Lobj.dir[1];
                const float hz = Lobj.dir_valid ? Lobj.dir_unit[2] : Lobj.dir[2];
                const float ndoth = tv.nrm[0] * hx + tv.nrm[1] * hy + tv.nrm[2] * hz;
                if (ndoth < 0.0f) return 0.0f;
                const float a = std::max(0.0f, Lobj.a[0] + Lobj.a[1] * ndoth + Lobj.a[2] * ndoth * ndoth);
                const float k = std::max(0.0f, Lobj.k[0] + Lobj.k[1] * ndoth + Lobj.k[2] * ndoth * ndoth);
                return a * k;
            }
            if (cc.diff_fn == 0u && cc.attn_fn == 2u) {
                return 1.0f;
            }
            float Lx = 0.0f, Ly = 0.0f, Lz = 1.0f;
            float dist = 0.0f, dist2 = 0.0f;
            if (Lobj.pos_is_zero) {
                if (Lobj.dir_valid) {
                    Lx = Lobj.dir_unit[0];
                    Ly = Lobj.dir_unit[1];
                    Lz = Lobj.dir_unit[2];
                    if (cc.attn_fn == 1u) {
                        dist2 = Lobj.dir[0] * Lobj.dir[0] + Lobj.dir[1] * Lobj.dir[1] + Lobj.dir[2] * Lobj.dir[2];
                        dist  = (dist2 > 1e-12f) ? (dist2 * fast_inv_sqrt(dist2)) : 0.0f;
                    }
                }
            } else {
                const float lvx = Lobj.pos[0] - tv.pos[0];
                const float lvy = Lobj.pos[1] - tv.pos[1];
                const float lvz = Lobj.pos[2] - tv.pos[2];
                dist2 = lvx * lvx + lvy * lvy + lvz * lvz;
                if (dist2 > 1e-12f) {
                    const float invd = fast_inv_sqrt(dist2);
                    Lx = lvx * invd;
                    Ly = lvy * invd;
                    Lz = lvz * invd;
                    if (cc.attn_fn == 1u) {
                        dist = dist2 * invd;
                    }
                }
            }
            const float ndotl = tv.nrm[0] * Lx + tv.nrm[1] * Ly + tv.nrm[2] * Lz;
            float diff = 1.0f;
            if (cc.diff_fn == 1u) {
                diff = ndotl;
            } else if (cc.diff_fn == 2u) {
                diff = std::max(0.0f, ndotl);
            }
            float attn = 1.0f;
            if (cc.attn_fn == 1u) { // GX_AF_SPOT
                const float cos_s = Lobj.dir_valid
                    ? std::max(0.0f, Lx * Lobj.dir_unit[0] + Ly * Lobj.dir_unit[1] + Lz * Lobj.dir_unit[2])
                    : 1.0f;
                const float spot = std::max(0.0f, Lobj.a[0] + Lobj.a[1] * cos_s + Lobj.a[2] * cos_s * cos_s);
                const float denom = Lobj.k[0] + Lobj.k[1] * dist + Lobj.k[2] * dist2;
                const float dist_att = (denom > 1e-6f) ? (1.0f / denom) : 1.0f;
                attn = spot * dist_att;
            }
            return diff * attn;
        };

        const uint32_t rgb_mask = cc_rgb.enable ? (cc_rgb.light_mask & loaded_lights_mask_) : 0u;
        const uint32_t alp_mask = cc_alp.enable ? (cc_alp.light_mask & loaded_lights_mask_) : 0u;
        const bool same_light_eval = cc_rgb.enable && cc_alp.enable &&
            rgb_mask != 0u && rgb_mask == alp_mask &&
            cc_rgb.diff_fn == cc_alp.diff_fn && cc_rgb.attn_fn == cc_alp.attn_fn;

        if (same_light_eval) {
            float illum[4] = {
                (cc_rgb.amb_src == 0u) ? chan_amb_color_[0][0] : v.color0[0],
                (cc_rgb.amb_src == 0u) ? chan_amb_color_[0][1] : v.color0[1],
                (cc_rgb.amb_src == 0u) ? chan_amb_color_[0][2] : v.color0[2],
                (cc_alp.amb_src == 0u) ? chan_amb_color_[0][3] : v.color0[3]
            };
            uint32_t m_bits = rgb_mask;
            while (m_bits != 0u) {
                const uint32_t li = static_cast<uint32_t>(std::countr_zero(m_bits));
                m_bits &= (m_bits - 1u);
                const float w = eval_light(li, cc_rgb);
                illum[0] += lights_[li].color[0] * w;
                illum[1] += lights_[li].color[1] * w;
                illum[2] += lights_[li].color[2] * w;
                illum[3] += lights_[li].color[3] * w;
            }
            for (int c = 0; c < 3; ++c) {
                tv.color0[c] = std::clamp(mat_rgb[c] * std::clamp(illum[c], 0.0f, 1.0f), 0.0f, 1.0f);
            }
            tv.color0[3] = std::clamp(mat_a * std::clamp(illum[3], 0.0f, 1.0f), 0.0f, 1.0f);
        } else {
            if (cc_rgb.enable) {
                float illum[3] = {
                    (cc_rgb.amb_src == 0u) ? chan_amb_color_[0][0] : v.color0[0],
                    (cc_rgb.amb_src == 0u) ? chan_amb_color_[0][1] : v.color0[1],
                    (cc_rgb.amb_src == 0u) ? chan_amb_color_[0][2] : v.color0[2]
                };
                uint32_t m_bits = rgb_mask;
                while (m_bits != 0u) {
                    const uint32_t li = static_cast<uint32_t>(std::countr_zero(m_bits));
                    m_bits &= (m_bits - 1u);
                    const float w = eval_light(li, cc_rgb);
                    illum[0] += lights_[li].color[0] * w;
                    illum[1] += lights_[li].color[1] * w;
                    illum[2] += lights_[li].color[2] * w;
                }
                for (int c = 0; c < 3; ++c) {
                    tv.color0[c] = std::clamp(mat_rgb[c] * std::clamp(illum[c], 0.0f, 1.0f), 0.0f, 1.0f);
                }
            } else {
                tv.color0[0] = mat_rgb[0];
                tv.color0[1] = mat_rgb[1];
                tv.color0[2] = mat_rgb[2];
            }

            if (cc_alp.enable) {
                float illum_a = (cc_alp.amb_src == 0u) ? chan_amb_color_[0][3] : v.color0[3];
                uint32_t m_bits = alp_mask;
                while (m_bits != 0u) {
                    const uint32_t li = static_cast<uint32_t>(std::countr_zero(m_bits));
                    m_bits &= (m_bits - 1u);
                    const float w = eval_light(li, cc_alp);
                    illum_a += lights_[li].color[3] * w;
                }
                tv.color0[3] = std::clamp(mat_a * std::clamp(illum_a, 0.0f, 1.0f), 0.0f, 1.0f);
            } else {
                tv.color0[3] = mat_a;
            }
        }
    } else {
        tv.color0[0] = v.color0[0];
        tv.color0[1] = v.color0[1];
        tv.color0[2] = v.color0[2];
        tv.color0[3] = v.color0[3];
    }

    tv.uv0[0] = v.uv0[0];
    tv.uv0[1] = v.uv0[1];
    if (num_tex_gens_ > 0u) {
        const uint8_t tc = (tev_stages_[0].tex_coord < 8u) ? tev_stages_[0].tex_coord : 0u;
        const uint32_t tm_id = tex_gen_mtx_[tc];
        if (tm_id >= 30u && tm_id <= 57u) {
            const uint32_t tm_idx = (tm_id - 30u) / 3u;
            const auto& tm = tex_mtx_[tm_idx];
            const float s = v.uv0[0];
            const float t = v.uv0[1];
            tv.uv0[0] = tm[0][0] * s + tm[0][1] * t + tm[0][2] + tm[0][3];
            tv.uv0[1] = tm[1][0] * s + tm[1][1] * t + tm[1][2] + tm[1][3];
        }
    }
}

void GX3DInterface::submit_vertex(const GXVertex& v) {
    // Transform vertex by per-vertex PNMTXIDX (if present) or current_mtx_idx_ PosMtx before staging
    const uint32_t mtx_idx = has_pending_vtx_mtx_idx_ ? pending_vtx_mtx_idx_ : (current_mtx_idx_ % 10u);
    has_pending_vtx_mtx_idx_ = false;
    const bool need_lighting = (num_chans_ > 0u);
    const uint8_t rgb_lights = (need_lighting && chan_ctrl_[0].enable)
        ? static_cast<uint8_t>(chan_ctrl_[0].light_mask & loaded_lights_mask_) : 0u;
    const uint8_t alp_lights = (need_lighting && chan_ctrl_[2].enable)
        ? static_cast<uint8_t>(chan_ctrl_[2].light_mask & loaded_lights_mask_) : 0u;
    const bool need_nrm = (rgb_lights != 0u && (chan_ctrl_[0].attn_fn == 0u || chan_ctrl_[0].diff_fn != 0u)) ||
                          (alp_lights != 0u && (chan_ctrl_[2].attn_fn == 0u || chan_ctrl_[2].diff_fn != 0u));
    GXVertex tv{};
    transform_and_shade_vertex(v, tv, mtx_idx, need_lighting, need_nrm);
    prim_Staging_.push_back(tv);
    if (expected_verts_ > 0 && prim_Staging_.size() >= expected_verts_) {
        end_primitive();
    }
}

void GX3DInterface::append_primitive_indices(uint32_t base_idx, size_t n) {
    const size_t add_cnt = expected_index_count(active_prim_, n);
    if (add_cnt == 0u) return;
    const size_t old_sz = index_buffer_.size();
    index_buffer_.resize(old_sz + add_cnt);
    uint32_t* out = index_buffer_.data() + old_sz;

    if (active_prim_ == GX_TRIANGLES) {
        for (size_t i = 0; i + 2 < n; i += 3) {
            out[0] = base_idx + static_cast<uint32_t>(i);
            out[1] = base_idx + static_cast<uint32_t>(i + 1);
            out[2] = base_idx + static_cast<uint32_t>(i + 2);
            out += 3;
        }
    } else if (active_prim_ == GX_TRIANGLESTRIP) {
        for (size_t i = 0; i + 2 < n; ++i) {
            if ((i & 1) == 0) {
                out[0] = base_idx + static_cast<uint32_t>(i);
                out[1] = base_idx + static_cast<uint32_t>(i + 1);
                out[2] = base_idx + static_cast<uint32_t>(i + 2);
            } else {
                out[0] = base_idx + static_cast<uint32_t>(i + 1);
                out[1] = base_idx + static_cast<uint32_t>(i);
                out[2] = base_idx + static_cast<uint32_t>(i + 2);
            }
            out += 3;
        }
    } else if (active_prim_ == GX_TRIANGLEFAN) {
        for (size_t i = 1; i + 1 < n; ++i) {
            out[0] = base_idx;
            out[1] = base_idx + static_cast<uint32_t>(i);
            out[2] = base_idx + static_cast<uint32_t>(i + 1);
            out += 3;
        }
    } else if (active_prim_ == GX_QUADS) {
        // Convert GameCube quads (used heavily by CMesWk::FontDraw @ 0x800A00DC and CId) into 2 triangles
        for (size_t i = 0; i + 3 < n; i += 4) {
            out[0] = base_idx + static_cast<uint32_t>(i);
            out[1] = base_idx + static_cast<uint32_t>(i + 1);
            out[2] = base_idx + static_cast<uint32_t>(i + 2);
            out[3] = base_idx + static_cast<uint32_t>(i);
            out[4] = base_idx + static_cast<uint32_t>(i + 2);
            out[5] = base_idx + static_cast<uint32_t>(i + 3);
            out += 6;
        }
    } else if (active_prim_ == GX_LINES || active_prim_ == GX_LINESTRIP) {
        for (size_t i = 0; i + 1 < n; ++i) {
            out[0] = base_idx + static_cast<uint32_t>(i);
            out[1] = base_idx + static_cast<uint32_t>(i + 1);
            out[2] = base_idx + static_cast<uint32_t>(i + 1);
            out += 3;
        }
    }
}

void GX3DInterface::emit_draw_batch(uint32_t first_idx_offset, uint32_t added_indices) {
    if (!batch_state_dirty_ && !draw_batches_.empty()) {
        GXDrawBatch& prev = draw_batches_.back();
        if (prev.index_offset + prev.index_count == first_idx_offset) {
            prev.index_count += added_indices;
            return;
        }
    }
    GXDrawBatch& batch = draw_batches_.emplace_back();
    batch_state_dirty_ = false;
    batch.index_offset = first_idx_offset;
    batch.index_count  = added_indices;
    std::memcpy(batch.proj_mtx, proj_mtx_, sizeof(proj_mtx_));
    batch.proj_type    = proj_type_;
    std::memcpy(batch.tev_color, tev_colors_[0], sizeof(batch.tev_color));
    const uint8_t tex_map = tev_stages_[0].tex_map;
    const bool map_valid  = (tex_map < 8u);
    batch.tev_mode     = tev_mode_;
    batch.tev_scale    = effective_tev_scale();
    batch.has_texture  = (num_tex_gens_ > 0 && tev_mode_ != 4u && tev_mode_ != 7u && map_valid &&
                          bound_textures_[tex_map].width > 0 && bound_textures_[tex_map].data_vaddr >= kGcRamBase);
    if (map_valid) {
        batch.texture  = bound_textures_[tex_map];
        batch.tlut     = tlut_slots_[bound_textures_[tex_map].tlut_name % 20u];
    }
    if (batch.has_texture && num_tev_stages_ >= 2u) {
        if (stage1_dirty_) {
            update_cached_stage1();
        }
        if (cached_has_stage1_) {
            batch.has_stage1_tex = true;
            batch.stage1_op      = cached_stage1_op_;
            batch.stage1_texture = cached_stage1_tex_;
            batch.stage1_tlut    = cached_stage1_tlut_;
        }
    }
    batch.z_enable     = z_compare_enable_;
    batch.z_write      = z_write_enable_;
    batch.blend_type   = blend_type_;
    batch.blend_src    = blend_src_;
    batch.blend_dst    = blend_dst_;
    batch.cull_mode    = cull_mode_;
    std::memcpy(batch.viewport, viewport_, sizeof(viewport_));
    const int32_t sc_x = static_cast<int32_t>(scissor_[0]) - scissor_offset_[0];
    const int32_t sc_y = static_cast<int32_t>(scissor_[1]) - scissor_offset_[1];
    const int32_t sc_r = sc_x + static_cast<int32_t>(scissor_[2]);
    const int32_t sc_b = sc_y + static_cast<int32_t>(scissor_[3]);
    const int32_t clamped_x = (sc_x > 0) ? sc_x : 0;
    const int32_t clamped_y = (sc_y > 0) ? sc_y : 0;
    batch.scissor[0]   = static_cast<uint32_t>(clamped_x);
    batch.scissor[1]   = static_cast<uint32_t>(clamped_y);
    batch.scissor[2]   = static_cast<uint32_t>((sc_r > clamped_x) ? (sc_r - clamped_x) : 0);
    batch.scissor[3]   = static_cast<uint32_t>((sc_b > clamped_y) ? (sc_b - clamped_y) : 0);
}

void GX3DInterface::end_primitive() {
    in_gx_begin_ = false;
    size_t n = prim_Staging_.size();
    if (n == 0) return;
    uint32_t base_idx = static_cast<uint32_t>(vertex_buffer_.size());
    uint32_t first_idx_offset = static_cast<uint32_t>(index_buffer_.size());
    vertex_buffer_.insert(vertex_buffer_.end(), prim_Staging_.begin(), prim_Staging_.end());
    append_primitive_indices(base_idx, n);
    uint32_t added_indices = static_cast<uint32_t>(index_buffer_.size()) - first_idx_offset;
    if (added_indices > 0) {
        emit_draw_batch(first_idx_offset, added_indices);
    }
    prim_Staging_.clear();
}

static inline void decode_rgb5a3_u16(uint16_t val, uint8_t out_rgba[4]) {
    if (val & 0x8000u) {
        out_rgba[0] = static_cast<uint8_t>(((val >> 10) & 0x1Fu) * 255u / 31u);
        out_rgba[1] = static_cast<uint8_t>(((val >> 5)  & 0x1Fu) * 255u / 31u);
        out_rgba[2] = static_cast<uint8_t>((val         & 0x1Fu) * 255u / 31u);
        out_rgba[3] = 255u;
    } else {
        out_rgba[3] = static_cast<uint8_t>(((val >> 12) & 0x07u) * 255u / 7u);
        out_rgba[0] = static_cast<uint8_t>(((val >> 8)  & 0x0Fu) * 255u / 15u);
        out_rgba[1] = static_cast<uint8_t>(((val >> 4)  & 0x0Fu) * 255u / 15u);
        out_rgba[2] = static_cast<uint8_t>((val         & 0x0Fu) * 255u / 15u);
    }
}

static inline void decode_rgb565_u16(uint16_t val, uint8_t out_rgba[4]) {
    out_rgba[0] = static_cast<uint8_t>(((val >> 11) & 0x1Fu) * 255u / 31u);
    out_rgba[1] = static_cast<uint8_t>(((val >> 5)  & 0x3Fu) * 255u / 63u);
    out_rgba[2] = static_cast<uint8_t>((val         & 0x1Fu) * 255u / 31u);
    out_rgba[3] = 255u;
}

static inline void decode_tlut_entry(const Memory& mem, const GXTlutSlot& tlut, uint32_t idx, uint8_t out_rgba[4]) {
    if (tlut.data_vaddr < kGcRamBase || !mem.is_valid_range(tlut.data_vaddr + idx * 2u, 2)) {
        out_rgba[0] = out_rgba[1] = out_rgba[2] = out_rgba[3] = 255u;
        return;
    }
    uint16_t raw = mem.read_u16(tlut.data_vaddr + idx * 2u);
    if (tlut.format == 0u) { // GX_TL_IA8
        uint8_t a = static_cast<uint8_t>(raw >> 8);
        uint8_t i = static_cast<uint8_t>(raw & 0xFFu);
        out_rgba[0] = out_rgba[1] = out_rgba[2] = i;
        out_rgba[3] = a;
    } else if (tlut.format == 1u) { // GX_TL_RGB565
        decode_rgb565_u16(raw, out_rgba);
    } else { // GX_TL_RGB5A3
        decode_rgb5a3_u16(raw, out_rgba);
    }
}

std::vector<uint8_t> GX3DInterface::decode_gc_texture_to_rgba8(
    const Memory& mem,
    const GXBoundTexture& tex,
    const GXTlutSlot* override_tlut
) const {
    if (tex.width == 0 || tex.height == 0 || tex.data_vaddr < kGcRamBase || !mem.is_valid_range(tex.data_vaddr, 4)) {
        return {};
    }
    uint32_t w = tex.width;
    uint32_t h = tex.height;
    std::vector<uint8_t> rgba(w * h * 4, 255);
    uint32_t ptr = tex.data_vaddr;
    const GXTlutSlot& tlut = override_tlut ? *override_tlut : tlut_slots_[tex.tlut_name % 20u];

    if (tex.format == GX_TF_I4) {
        // 8x8 tiled 4-bit intensity blocks
        for (uint32_t by = 0; by < h; by += 8) {
            for (uint32_t bx = 0; bx < w; bx += 8) {
                for (uint32_t y = 0; y < 8; ++y) {
                    for (uint32_t x = 0; x < 8; x += 2) {
                        if (!mem.is_valid_range(ptr, 1)) break;
                        uint8_t b = mem.read_u8(ptr++);
                        uint8_t i0 = static_cast<uint8_t>((b >> 4) * 17u);
                        uint8_t i1 = static_cast<uint8_t>((b & 0xFu) * 17u);
                        if (bx + x < w && by + y < h) {
                            uint8_t* dst = &rgba[((by + y) * w + (bx + x)) * 4];
                            dst[0] = dst[1] = dst[2] = dst[3] = i0;
                        }
                        if (bx + x + 1 < w && by + y < h) {
                            uint8_t* dst = &rgba[((by + y) * w + (bx + x + 1)) * 4];
                            dst[0] = dst[1] = dst[2] = dst[3] = i1;
                        }
                    }
                }
            }
        }
    } else if (tex.format == GX_TF_I8) {
        // 8x4 tiled 8-bit intensity blocks
        for (uint32_t by = 0; by < h; by += 4) {
            for (uint32_t bx = 0; bx < w; bx += 8) {
                for (uint32_t y = 0; y < 4; ++y) {
                    for (uint32_t x = 0; x < 8; ++x) {
                        if (!mem.is_valid_range(ptr, 1)) break;
                        uint8_t iv = mem.read_u8(ptr++);
                        if (bx + x < w && by + y < h) {
                            uint8_t* dst = &rgba[((by + y) * w + (bx + x)) * 4];
                            dst[0] = dst[1] = dst[2] = dst[3] = iv;
                        }
                    }
                }
            }
        }
    } else if (tex.format == GX_TF_IA4) {
        // 8x4 tiled 4-bit alpha + 4-bit intensity
        for (uint32_t by = 0; by < h; by += 4) {
            for (uint32_t bx = 0; bx < w; bx += 8) {
                for (uint32_t y = 0; y < 4; ++y) {
                    for (uint32_t x = 0; x < 8; ++x) {
                        if (!mem.is_valid_range(ptr, 1)) break;
                        uint8_t b  = mem.read_u8(ptr++);
                        uint8_t a  = static_cast<uint8_t>((b >> 4) * 17u);
                        uint8_t iv = static_cast<uint8_t>((b & 0xFu) * 17u);
                        if (bx + x < w && by + y < h) {
                            uint8_t* dst = &rgba[((by + y) * w + (bx + x)) * 4];
                            dst[0] = dst[1] = dst[2] = iv;
                            dst[3] = a;
                        }
                    }
                }
            }
        }
    } else if (tex.format == GX_TF_IA8) {
        // 4x4 tiled 8-bit alpha + 8-bit intensity
        for (uint32_t by = 0; by < h; by += 4) {
            for (uint32_t bx = 0; bx < w; bx += 4) {
                for (uint32_t y = 0; y < 4; ++y) {
                    for (uint32_t x = 0; x < 4; ++x) {
                        if (!mem.is_valid_range(ptr, 2)) break;
                        uint16_t raw = mem.read_u16(ptr);
                        ptr += 2;
                        if (bx + x < w && by + y < h) {
                            uint8_t* dst = &rgba[((by + y) * w + (bx + x)) * 4];
                            dst[0] = dst[1] = dst[2] = static_cast<uint8_t>(raw & 0xFFu);
                            dst[3] = static_cast<uint8_t>(raw >> 8);
                        }
                    }
                }
            }
        }
    } else if (tex.format == GX_TF_RGB5A3 || tex.format == GX_TF_RGB565) {
        // 4x4 tiled 16-bit blocks
        for (uint32_t by = 0; by < h; by += 4) {
            for (uint32_t bx = 0; bx < w; bx += 4) {
                for (uint32_t y = 0; y < 4; ++y) {
                    for (uint32_t x = 0; x < 4; ++x) {
                        if (!mem.is_valid_range(ptr, 2)) break;
                        uint16_t raw = mem.read_u16(ptr);
                        ptr += 2;
                        if (bx + x < w && by + y < h) {
                            uint8_t* dst = &rgba[((by + y) * w + (bx + x)) * 4];
                            if (tex.format == GX_TF_RGB5A3) decode_rgb5a3_u16(raw, dst);
                            else decode_rgb565_u16(raw, dst);
                        }
                    }
                }
            }
        }
    } else if (tex.format == GX_TF_RGBA8) {
        // 4x4 tiled 32-bit RGBA8 stored as two 32-byte cachelines (AR plane then GB plane)
        for (uint32_t by = 0; by < h; by += 4) {
            for (uint32_t bx = 0; bx < w; bx += 4) {
                if (!mem.is_valid_range(ptr, 64)) break;
                for (uint32_t y = 0; y < 4; ++y) {
                    for (uint32_t x = 0; x < 4; ++x) {
                        uint32_t idx = y * 4u + x;
                        uint8_t a = mem.read_u8(ptr + idx * 2u + 0u);
                        uint8_t r = mem.read_u8(ptr + idx * 2u + 1u);
                        uint8_t g = mem.read_u8(ptr + 32u + idx * 2u + 0u);
                        uint8_t b = mem.read_u8(ptr + 32u + idx * 2u + 1u);
                        if (bx + x < w && by + y < h) {
                            uint8_t* dst = &rgba[((by + y) * w + (bx + x)) * 4];
                            dst[0] = r; dst[1] = g; dst[2] = b; dst[3] = a;
                        }
                    }
                }
                ptr += 64u;
            }
        }
    } else if (tex.format == GX_TF_C4) {
        // 8x8 tiled 4-bit color-indexed palette texture
        for (uint32_t by = 0; by < h; by += 8) {
            for (uint32_t bx = 0; bx < w; bx += 8) {
                for (uint32_t y = 0; y < 8; ++y) {
                    for (uint32_t x = 0; x < 8; x += 2) {
                        if (!mem.is_valid_range(ptr, 1)) break;
                        uint8_t b = mem.read_u8(ptr++);
                        if (bx + x < w && by + y < h) {
                            decode_tlut_entry(mem, tlut, (b >> 4) & 0xFu, &rgba[((by + y) * w + (bx + x)) * 4]);
                        }
                        if (bx + x + 1 < w && by + y < h) {
                            decode_tlut_entry(mem, tlut, b & 0xFu, &rgba[((by + y) * w + (bx + x + 1)) * 4]);
                        }
                    }
                }
            }
        }
    } else if (tex.format == GX_TF_C8) {
        // 8x4 tiled 8-bit color-indexed palette texture
        for (uint32_t by = 0; by < h; by += 4) {
            for (uint32_t bx = 0; bx < w; bx += 8) {
                for (uint32_t y = 0; y < 4; ++y) {
                    for (uint32_t x = 0; x < 8; ++x) {
                        if (!mem.is_valid_range(ptr, 1)) break;
                        uint8_t ci = mem.read_u8(ptr++);
                        if (bx + x < w && by + y < h) {
                            decode_tlut_entry(mem, tlut, ci, &rgba[((by + y) * w + (bx + x)) * 4]);
                        }
                    }
                }
            }
        }
    } else if (tex.format == GX_TF_C14X2) {
        // 4x4 tiled 14-bit color-indexed palette texture
        for (uint32_t by = 0; by < h; by += 4) {
            for (uint32_t bx = 0; bx < w; bx += 4) {
                for (uint32_t y = 0; y < 4; ++y) {
                    for (uint32_t x = 0; x < 4; ++x) {
                        if (!mem.is_valid_range(ptr, 2)) break;
                        uint16_t ci = mem.read_u16(ptr) & 0x3FFFu;
                        ptr += 2;
                        if (bx + x < w && by + y < h) {
                            decode_tlut_entry(mem, tlut, ci, &rgba[((by + y) * w + (bx + x)) * 4]);
                        }
                    }
                }
            }
        }
    } else if (tex.format == GX_TF_CMPR) {
        // GameCube CMPR (8x8 macro-blocks of four 4x4 S3TC/DXT1 sub-blocks)
        for (uint32_t by = 0; by < h; by += 8) {
            for (uint32_t bx = 0; bx < w; bx += 8) {
                for (uint32_t sb = 0; sb < 4; ++sb) {
                    if (!mem.is_valid_range(ptr, 8)) break;
                    uint32_t sbx  = bx + (sb & 1u) * 4u;
                    uint32_t sby  = by + (sb >> 1u) * 4u;
                    uint16_t c0   = mem.read_u16(ptr + 0);
                    uint16_t c1   = mem.read_u16(ptr + 2);
                    uint32_t bits = mem.read_u32(ptr + 4);
                    ptr += 8;

                    uint8_t pal[4][4]{};
                    decode_rgb565_u16(c0, pal[0]);
                    decode_rgb565_u16(c1, pal[1]);
                    if (c0 > c1) {
                        for (int k = 0; k < 3; ++k) {
                            pal[2][k] = static_cast<uint8_t>((2 * pal[0][k] + pal[1][k]) / 3);
                            pal[3][k] = static_cast<uint8_t>((pal[0][k] + 2 * pal[1][k]) / 3);
                        }
                        pal[2][3] = pal[3][3] = 255;
                    } else {
                        for (int k = 0; k < 3; ++k) {
                            pal[2][k] = static_cast<uint8_t>((pal[0][k] + pal[1][k]) / 2);
                            pal[3][k] = 0;
                        }
                        pal[2][3] = 255;
                        pal[3][3] = 0;
                    }

                    for (uint32_t y = 0; y < 4; ++y) {
                        for (uint32_t x = 0; x < 4; ++x) {
                            uint32_t shift = 30u - ((y * 4u + x) * 2u);
                            uint32_t idx   = (bits >> shift) & 3u;
                            if (sbx + x < w && sby + y < h) {
                                std::memcpy(&rgba[((sby + y) * w + (sbx + x)) * 4], pal[idx], 4);
                            }
                        }
                    }
                }
            }
        }
    }
    return rgba;
}

bool GX3DInterface::dispatch_gx_vi_call(uint32_t vaddr, PPCContext& ctx, Memory& mem) {
    bind_fifo_to_memory(mem);

    switch (vaddr) {
        // ====================================================================
        // VI (Video Interface) Functions (0x8010C434..0x8010EBC4)
        // ====================================================================
        case 0x8010C8ACu: // __VIInit
        case 0x8010CC48u: // VIInit
        case 0x8010DA0Cu: // VIConfigure
        case 0x8010E234u: // VIConfigurePan
        case 0x8010E5C8u: // VIFlush
        case 0x8010E7E0u: // VISetBlack
        case 0x8010C434u: // VISetRegs
            return true;
        case 0x8010C784u: // VISetPreRetraceCallback
        case 0x8010C7C8u: { // VISetPostRetraceCallback
            uint32_t prev = vi_post_cb_vaddr_;
            vi_post_cb_vaddr_ = ctx.r[3];
            ctx.r[3] = prev;
            return true;
        }
        case 0x8010E6F8u: // VISetNextFrameBuffer
            vi_xfb_vaddr_ = ctx.r[3];
            return true;
        case 0x8010E764u: // VIGetNextFrameBuffer
        case 0x8010E76Cu: // VIGetCurrentFrameBuffer
            ctx.r[3] = vi_xfb_vaddr_;
            return true;
        case 0x8010D0F8u: // VIWaitForRetrace
            vi_retrace_count_++;
            return true;
        case 0x8010E95Cu: // VIGetRetraceCount
            ctx.r[3] = vi_retrace_count_;
            return true;
        case 0x8010EA1Cu: // VIGetNextField
            ctx.r[3] = 1u; // Progressive / upper field
            return true;
        case 0x8010EB5Cu: // VIGetTvFormat
            ctx.r[3] = 0u; // VI_NTSC (60Hz)
            return true;
        case 0x8010EBC4u: // VIGetDTVStatus
            ctx.r[3] = 1u; // Progressive scan component cable active
            return true;

        // ====================================================================
        // GX Lifecycle, FIFO & Sync (0x8011C108..0x801208E0)
        // ====================================================================
        case 0x8011C108u: // GXInit
            ctx.r[3] = 0x8026E7B0u; // DefaultFifoObj
            return true;
        case 0x8011C998u: // __GXInitGX
        case 0x8011D4A0u: // GXInitFifoBase
        case 0x8011D50Cu: // GXInitFifoPtrs
        case 0x8011D57Cu: // GXInitFifoLimits
        case 0x8011D588u: // GXSetCPUFifo
        case 0x8011D698u: // GXSetGPFifo
        case 0x8011D810u: // GXSaveCPUFifo
        case 0x8011DEF4u: // GXSetCurrentGXThread
        case 0x8011FC18u: // GXSetMisc
        case 0x8011FCACu: // GXFlush
        case 0x8011FFE8u: // GXAbortFrame
        case 0x80120158u: // GXSetDrawSync
        case 0x8012021Cu: // GXSetDrawDone
        case 0x801202B4u: // GXWaitDrawDone
        case 0x80120300u: // GXDrawDone
        case 0x80120380u: // GXPixModeSync
        case 0x801203A4u: // GXTexModeSync
        case 0x8011F8F8u: // GXInvalidateVtxCache
        case 0x8012363Cu: // GXInvalidateTexRegion
        case 0x80123748u: // GXInvalidateTexAll
            return true;
        case 0x80120598u: // GXSetDrawSyncCallback
        case 0x80120664u: // GXSetDrawDoneCallback
            ctx.r[3] = 0u;
            return true;

        // ====================================================================
        // GX Vertex Attributes, Arrays & Display Lists (0x8011E354..0x80125B3C)
        // ====================================================================
        case 0x8011EDD4u: // GXClearVtxDesc
            clear_vtx_desc();
            return true;
        case 0x8011E354u: // GXSetVtxDesc(GXAttr attr [r3], GXAttrType type [r4])
            set_vtx_desc(ctx.r[3], static_cast<uint8_t>(ctx.r[4] & 3u));
            return true;
        case 0x8011E6A4u: { // GXSetVtxDescv(const GXVtxDescList* attrPtr [r3])
            uint32_t ptr = ctx.r[3];
            while (mem.is_valid_range(ptr, 8)) {
                uint32_t attr = mem.read_u32(ptr);
                uint32_t type = mem.read_u32(ptr + 4);
                if (attr == 0xFFu || attr >= GX_VA_MAX_ATTR) break;
                set_vtx_desc(attr, static_cast<uint8_t>(type & 3u));
                ptr += 8;
            }
            return true;
        }
        case 0x8011EE0Cu: // GXSetVtxAttrFmt(GXVtxFmt vtxfmt [r3], GXAttr attr [r4], GXCompCnt cnt [r5], GXCompType type [r6], u8 frac [r7])
            set_vtx_attr_fmt(
                static_cast<uint8_t>(ctx.r[3] & 7u),
                ctx.r[4],
                ctx.r[5],
                ctx.r[6],
                static_cast<uint8_t>(ctx.r[7] & 0xFFu)
            );
            return true;
        case 0x8011F164u: { // GXSetVtxAttrFmtv(GXVtxFmt vtxfmt [r3], const GXVtxAttrFmtList* list [r4])
            uint8_t fmt = static_cast<uint8_t>(ctx.r[3] & 7u);
            uint32_t ptr = ctx.r[4];
            while (mem.is_valid_range(ptr, 16)) {
                uint32_t attr = mem.read_u32(ptr + 0);
                if (attr == 0xFFu || attr >= GX_VA_MAX_ATTR) break;
                uint32_t cnt  = mem.read_u32(ptr + 4);
                uint32_t type = mem.read_u32(ptr + 8);
                uint8_t  frac = mem.read_u8(ptr + 12);
                set_vtx_attr_fmt(fmt, attr, cnt, type, frac);
                ptr += 16;
            }
            return true;
        }
        case 0x8011F86Cu: // GXSetArray(GXAttr attr [r3], const void* base_ptr [r4], u8 stride [r5])
            set_array(ctx.r[3], ctx.r[4], static_cast<uint8_t>(ctx.r[5] & 0xFFu));
            return true;
        case 0x8011F908u: { // GXSetTexCoordGen2(dst_coord [r3], func [r4], src [r5], mtx [r6], norm [r7], postmtx [r8])
            uint32_t coord = ctx.r[3];
            if (coord < 8u) {
                tex_gen_func_[coord] = ctx.r[4];
                tex_gen_src_[coord]  = ctx.r[5];
                tex_gen_mtx_[coord]  = ctx.r[6];
            }
            return true;
        }
        case 0x8011FBD8u: // GXSetNumTexGens
            num_tex_gens_ = ctx.r[3];
            batch_state_dirty_ = true;
            return true;
        case 0x80120A9Cu: // GXBegin(GXPrimitive type [r3], GXVtxFmt vtxfmt [r4], u16 nverts [r5])
            begin_primitive(static_cast<GXPrimitive>(ctx.r[3] & 0xFFu), static_cast<uint8_t>(ctx.r[4]), static_cast<uint16_t>(ctx.r[5]));
            return true;
        case 0x80125B3Cu: { // GXCallDisplayList(const void* list [r3], u32 nbytes [r4])
            execute_display_list(mem, ctx.r[3], ctx.r[4]);
            return true;
        }
        case 0x80120C14u: // GXSetLineWidth
        case 0x80120C78u: // GXSetPointSize
        case 0x80120CE0u: // GXEnableTexOffsets
        case 0x80120DCCu: // GXSetCoPlanar
            return true;
        case 0x80120D3Cu: // GXSetCullMode
            cull_mode_ = ctx.r[3];
            batch_state_dirty_ = true;
            return true;

        // ====================================================================
        // GX Transform, Projection, Viewport & Scissor (0x80125BAC..0x801264A8)
        // ====================================================================
        case 0x80125D20u: { // GXSetProjection(const f32 mtx[4][4] [r3], GXProjectionType type [r4])
            proj_type_ = ctx.r[4];
            if (const uint8_t* p = mem.fast_ram_ptr(ctx.r[3], 64u)) {
                for (int r = 0; r < 4; ++r, p += 16) {
                    proj_mtx_[r][0] = read_be_f32_unaligned(p + 0);
                    proj_mtx_[r][1] = read_be_f32_unaligned(p + 4);
                    proj_mtx_[r][2] = read_be_f32_unaligned(p + 8);
                    proj_mtx_[r][3] = read_be_f32_unaligned(p + 12);
                }
                apply_aspect_ratio_to_projection();
            } else if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 64)) {
                for (int r = 0; r < 4; ++r) {
                    for (int c = 0; c < 4; ++c) {
                        proj_mtx_[r][c] = mem.read_f32(ctx.r[3] + static_cast<uint32_t>((r * 4 + c) * 4));
                    }
                }
                apply_aspect_ratio_to_projection();
            }
            batch_state_dirty_ = true;
            return true;
        }
        case 0x80125DD4u: { // GXSetProjectionv(const f32* ptr [r3])
            if (const uint8_t* p = mem.fast_ram_ptr(ctx.r[3], 28u)) {
                proj_type_ = static_cast<uint32_t>(read_be_f32_unaligned(p + 0));
                std::memset(proj_mtx_, 0, sizeof(proj_mtx_));
                proj_mtx_[0][0] = read_be_f32_unaligned(p + 4);
                proj_mtx_[1][1] = read_be_f32_unaligned(p + 12);
                proj_mtx_[2][2] = read_be_f32_unaligned(p + 20);
                proj_mtx_[2][3] = read_be_f32_unaligned(p + 24);
                if (proj_type_ == 0) {
                    proj_mtx_[0][2] = read_be_f32_unaligned(p + 8);
                    proj_mtx_[1][2] = read_be_f32_unaligned(p + 16);
                    proj_mtx_[3][2] = -1.0f;
                    apply_aspect_ratio_to_projection();
                } else {
                    proj_mtx_[0][3] = read_be_f32_unaligned(p + 8);
                    proj_mtx_[1][3] = read_be_f32_unaligned(p + 16);
                    proj_mtx_[3][3] = 1.0f;
                }
            } else if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 28)) {
                proj_type_ = static_cast<uint32_t>(mem.read_f32(ctx.r[3] + 0));
                std::memset(proj_mtx_, 0, sizeof(proj_mtx_));
                proj_mtx_[0][0] = mem.read_f32(ctx.r[3] + 4);
                proj_mtx_[1][1] = mem.read_f32(ctx.r[3] + 12);
                proj_mtx_[2][2] = mem.read_f32(ctx.r[3] + 20);
                proj_mtx_[2][3] = mem.read_f32(ctx.r[3] + 24);
                if (proj_type_ == 0) {
                    proj_mtx_[0][2] = mem.read_f32(ctx.r[3] + 8);
                    proj_mtx_[1][2] = mem.read_f32(ctx.r[3] + 16);
                    proj_mtx_[3][2] = -1.0f;
                    apply_aspect_ratio_to_projection();
                } else {
                    proj_mtx_[0][3] = mem.read_f32(ctx.r[3] + 8);
                    proj_mtx_[1][3] = mem.read_f32(ctx.r[3] + 16);
                    proj_mtx_[3][3] = 1.0f;
                }
            }
            batch_state_dirty_ = true;
            return true;
        }
        case 0x80125FACu: { // GXLoadPosMtxImm(const f32 mtx[3][4] [r3], u32 id [r4])
            const uint32_t idx = (ctx.r[4] / 3u) % 10u;
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 48)) {
                const uint8_t* src = mem.raw_ptr(ctx.r[3]);
                for (int r = 0; r < 3; ++r) {
                    for (int c = 0; c < 4; ++c) {
                        pos_mtx_[idx][r][c] = read_be_f32_unaligned(src + (r * 4 + c) * 4);
                    }
                }
            }
            return true;
        }
        case 0x80126024u: { // GXLoadNrmMtxImm(const f32 mtx[3][4] [r3], u32 id [r4])
            const uint32_t idx = (ctx.r[4] / 3u) % 10u;
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 44)) {
                const uint8_t* src = mem.raw_ptr(ctx.r[3]);
                for (int r = 0; r < 3; ++r) {
                    for (int c = 0; c < 3; ++c) {
                        nrm_mtx_[idx][r][c] = read_be_f32_unaligned(src + (r * 4 + c) * 4);
                    }
                }
                has_nrm_mtx_[idx] = true;
            }
            return true;
        }
        case 0x80126074u: { // GXLoadNrmMtxImm3x3(const f32 mtx[3][3] [r3], u32 id [r4])
            const uint32_t idx = (ctx.r[4] / 3u) % 10u;
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 36)) {
                const uint8_t* src = mem.raw_ptr(ctx.r[3]);
                for (int r = 0; r < 3; ++r) {
                    for (int c = 0; c < 3; ++c) {
                        nrm_mtx_[idx][r][c] = read_be_f32_unaligned(src + (r * 3 + c) * 4);
                    }
                }
                has_nrm_mtx_[idx] = true;
            }
            return true;
        }
        case 0x80126120u: { // GXLoadTexMtxImm(const f32* mtx [r3], u32 id [r4], GXTexMtxType type [r5])
            uint32_t id = ctx.r[4];
            int slot = -1;
            if (id >= 30u && id <= 57u) {
                slot = static_cast<int>((id - 30u) / 3u);
            } else if (id >= 64u && id <= 121u) {
                int post_slot = static_cast<int>(10u + (id - 64u) / 3u);
                if (post_slot < 20) slot = post_slot;
            }
            if (slot >= 0 && slot < 20) {
                std::memset(tex_mtx_[slot], 0, sizeof(tex_mtx_[slot]));
                tex_mtx_[slot][0][0] = tex_mtx_[slot][1][1] = tex_mtx_[slot][2][2] = 1.0f;
                const int rows = (ctx.r[5] == 1u) ? 2 : 3;
                if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], static_cast<uint32_t>(rows * 16))) {
                    const uint8_t* src = mem.raw_ptr(ctx.r[3]);
                    for (int r = 0; r < rows; ++r) {
                        for (int c = 0; c < 4; ++c) {
                            tex_mtx_[slot][r][c] = read_be_f32_unaligned(src + (r * 4 + c) * 4);
                        }
                    }
                }
            }
            return true;
        }
        case 0x801260E8u: // GXSetCurrentMtx(u32 id [r3])
            current_mtx_idx_ = (ctx.r[3] / 3u) % 10u;
            return true;
        case 0x80126230u: // GXSetViewportJitter
        case 0x80126334u: { // GXSetViewport(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz)
            viewport_[0] = static_cast<float>(ctx.f[1]);
            viewport_[1] = static_cast<float>(ctx.f[2]);
            viewport_[2] = static_cast<float>(ctx.f[3]);
            viewport_[3] = static_cast<float>(ctx.f[4]);
            viewport_[4] = static_cast<float>(ctx.f[5]);
            viewport_[5] = static_cast<float>(ctx.f[6]);
            batch_state_dirty_ = true;
            return true;
        }
        case 0x80126390u: { // GXSetScissor(u32 left, u32 top, u32 wd, u32 ht)
            scissor_[0] = ctx.r[3];
            scissor_[1] = ctx.r[4];
            scissor_[2] = ctx.r[5];
            scissor_[3] = ctx.r[6];
            batch_state_dirty_ = true;
            return true;
        }
        case 0x80126468u: { // GXSetScissorBoxOffset(s32 x_off, s32 y_off)
            scissor_offset_[0] = static_cast<int32_t>(ctx.r[3]);
            scissor_offset_[1] = static_cast<int32_t>(ctx.r[4]);
            batch_state_dirty_ = true;
            return true;
        }
        case 0x801264A8u: // GXSetClipMode
            return true;

        // ====================================================================
        // GX Texture, TLUT Palette & TPL Management (0x801224E8..0x801279EC)
        // ====================================================================
        case 0x8012270Cu: { // GXInitTexObj(GXTexObj* obj [r3], void* image_ptr [r4], u16 wd [r5], u16 ht [r6], GXTexFmt fmt [r7], wrap_s [r8], wrap_t [r9], mipmap [r10])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 32)) {
                mem.write_u32(ctx.r[3] + 0,  ctx.r[4]);
                mem.write_u16(ctx.r[3] + 4,  static_cast<uint16_t>(ctx.r[5]));
                mem.write_u16(ctx.r[3] + 6,  static_cast<uint16_t>(ctx.r[6]));
                mem.write_u32(ctx.r[3] + 8,  ctx.r[7]);
                mem.write_u8(ctx.r[3]  + 12, static_cast<uint8_t>(ctx.r[8]));
                mem.write_u8(ctx.r[3]  + 13, static_cast<uint8_t>(ctx.r[9]));
                mem.write_u32(ctx.r[3] + 16, 0u);
            }
            return true;
        }
        case 0x80122980u: { // GXInitTexObjCI(GXTexObj* obj [r3], void* image_ptr [r4], u16 wd [r5], u16 ht [r6], GXCITexFmt fmt [r7], wrap_s [r8], wrap_t [r9], mipmap [r10], u32 tlut_name [stack+8])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 32)) {
                uint32_t tlut_name = mem.is_valid_range(ctx.r[1] + 8, 4) ? mem.read_u32(ctx.r[1] + 8) : 0u;
                mem.write_u32(ctx.r[3] + 0,  ctx.r[4]);
                mem.write_u16(ctx.r[3] + 4,  static_cast<uint16_t>(ctx.r[5]));
                mem.write_u16(ctx.r[3] + 6,  static_cast<uint16_t>(ctx.r[6]));
                mem.write_u32(ctx.r[3] + 8,  ctx.r[7]);
                mem.write_u8(ctx.r[3]  + 12, static_cast<uint8_t>(ctx.r[8]));
                mem.write_u8(ctx.r[3]  + 13, static_cast<uint8_t>(ctx.r[9]));
                mem.write_u32(ctx.r[3] + 16, tlut_name);
            }
            return true;
        }
        case 0x80122B9Cu: { // GXInitTexObjTlut(GXTexObj* obj [r3], u32 tlut_name [r4])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 20)) {
                mem.write_u32(ctx.r[3] + 16, ctx.r[4]);
            }
            return true;
        }
        case 0x8012319Cu: { // GXLoadTexObj(const GXTexObj* obj [r3], GXTexMapID id [r4])
            const uint32_t slot = ctx.r[4] & 7u;
            if (const uint8_t* src = mem.fast_ram_ptr(ctx.r[3], 20u)) {
                bound_textures_[slot].data_vaddr = read_be32_unaligned(src + 0);
                bound_textures_[slot].width      = read_be16_unaligned(src + 4);
                bound_textures_[slot].height     = read_be16_unaligned(src + 6);
                bound_textures_[slot].format     = read_be32_unaligned(src + 8);
                bound_textures_[slot].wrap_s     = src[12];
                bound_textures_[slot].wrap_t     = src[13];
                bound_textures_[slot].tlut_name  = read_be32_unaligned(src + 16);
                bound_textures_[slot].max_aniso  = cfg_.anisotropic_filtering;
                stage1_dirty_ = true;
                batch_state_dirty_ = true;
            }
            return true;
        }
        case 0x801231F0u: { // GXInitTlutObj(GXTlutObj* tlut_obj [r3], const void* lut [r4], GXTlutFmt fmt [r5], u16 n_entries [r6])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 12)) {
                mem.write_u32(ctx.r[3] + 0, ctx.r[4]);
                mem.write_u32(ctx.r[3] + 4, ctx.r[5]);
                mem.write_u16(ctx.r[3] + 8, static_cast<uint16_t>(ctx.r[6]));
            }
            return true;
        }
        case 0x8012327Cu: { // GXLoadTlut(const GXTlutObj* tlut_obj [r3], u32 tlut_name [r4])
            const uint32_t idx = ctx.r[4] % 20u;
            if (const uint8_t* src = mem.fast_ram_ptr(ctx.r[3], 12u)) {
                tlut_slots_[idx].data_vaddr  = read_be32_unaligned(src + 0);
                tlut_slots_[idx].format      = read_be32_unaligned(src + 4);
                tlut_slots_[idx].num_entries = read_be16_unaligned(src + 8);
                stage1_dirty_ = true;
                batch_state_dirty_ = true;
            }
            return true;
        }
        case 0x801229C8u: // GXInitTexObjLOD
        case 0x80122BA4u: // GXInitTexObjFilter
            return true;
        case 0x80122B5Cu: // GXInitTexObjData(GXTexObj* obj [r3], void* image_ptr [r4])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 4)) {
                mem.write_u32(ctx.r[3] + 0, ctx.r[4]);
            }
            return true;
        case 0x80122B74u: // GXInitTexObjWrapMode(GXTexObj* obj [r3], u32 wrap_s [r4], u32 wrap_t [r5])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 14)) {
                mem.write_u8(ctx.r[3] + 12, static_cast<uint8_t>(ctx.r[4]));
                mem.write_u8(ctx.r[3] + 13, static_cast<uint8_t>(ctx.r[5]));
            }
            return true;

        case 0x80127870u: { // TEXGet(TEXPalettePtr pal [r3], u32 id [r4]) -> returns TEXDescriptorPtr
            uint32_t pal = ctx.r[3];
            uint32_t id  = ctx.r[4];
            if (pal >= kGcRamBase && mem.is_valid_range(pal, 12)) {
                uint32_t desc_arr = mem.read_u32(pal + 8);
                if (desc_arr < kGcRamBase) desc_arr += pal;
                ctx.r[3] = desc_arr + id * 8u;
            } else {
                ctx.r[3] = 0u;
            }
            return true;
        }
        case 0x80127918u: { // TEXGetGXTexObjFromPalette(TEXPalettePtr pal [r3], GXTexObj* to [r4], u32 id [r5])
            uint32_t pal = ctx.r[3];
            uint32_t to  = ctx.r[4];
            uint32_t id  = ctx.r[5];
            if (pal >= kGcRamBase && to >= kGcRamBase && mem.is_valid_range(pal, 12)) {
                uint32_t desc_arr = mem.read_u32(pal + 8);
                if (desc_arr < kGcRamBase) desc_arr += pal;
                uint32_t td = desc_arr + id * 8u;
                uint32_t th = mem.read_u32(td + 0);
                if (th < kGcRamBase) th += pal;
                if (mem.is_valid_range(th, 20)) {
                    uint16_t ht  = mem.read_u16(th + 0);
                    uint16_t wd  = mem.read_u16(th + 2);
                    uint32_t fmt = mem.read_u32(th + 4);
                    uint32_t dat = mem.read_u32(th + 8);
                    if (dat < kGcRamBase) dat += pal;
                    mem.write_u32(to + 0,  dat);
                    mem.write_u16(to + 4,  wd);
                    mem.write_u16(to + 6,  ht);
                    mem.write_u32(to + 8,  fmt);
                    mem.write_u8(to  + 12, static_cast<uint8_t>(mem.read_u32(th + 12)));
                    mem.write_u8(to  + 13, static_cast<uint8_t>(mem.read_u32(th + 16)));
                    mem.write_u32(to + 16, 0u);
                }
            }
            return true;
        }
        case 0x801279ECu: { // TEXGetGXTexObjFromPaletteCI(TEXPalettePtr pal [r3], GXTexObj* to [r4], GXTlutObj* tlo [r5], GXTlut tlut [r6], u32 id [r7])
            uint32_t pal  = ctx.r[3];
            uint32_t to   = ctx.r[4];
            uint32_t tlo  = ctx.r[5];
            uint32_t tlut = ctx.r[6];
            uint32_t id   = ctx.r[7];
            if (pal >= kGcRamBase && to >= kGcRamBase && mem.is_valid_range(pal, 12)) {
                uint32_t desc_arr = mem.read_u32(pal + 8);
                if (desc_arr < kGcRamBase) desc_arr += pal;
                uint32_t td = desc_arr + id * 8u;
                uint32_t th = mem.read_u32(td + 0);
                uint32_t ch = mem.read_u32(td + 4);
                if (th < kGcRamBase) th += pal;
                if (ch != 0 && ch < kGcRamBase) ch += pal;
                if (mem.is_valid_range(th, 20)) {
                    uint16_t ht  = mem.read_u16(th + 0);
                    uint16_t wd  = mem.read_u16(th + 2);
                    uint32_t fmt = mem.read_u32(th + 4);
                    uint32_t dat = mem.read_u32(th + 8);
                    if (dat < kGcRamBase) dat += pal;
                    mem.write_u32(to + 0,  dat);
                    mem.write_u16(to + 4,  wd);
                    mem.write_u16(to + 6,  ht);
                    mem.write_u32(to + 8,  fmt);
                    mem.write_u8(to  + 12, static_cast<uint8_t>(mem.read_u32(th + 12)));
                    mem.write_u8(to  + 13, static_cast<uint8_t>(mem.read_u32(th + 16)));
                    mem.write_u32(to + 16, tlut);
                }
                if (tlo >= kGcRamBase && ch >= kGcRamBase && mem.is_valid_range(ch, 12)) {
                    uint16_t n_ent = mem.read_u16(ch + 0);
                    uint32_t c_fmt = mem.read_u32(ch + 4);
                    uint32_t c_dat = mem.read_u32(ch + 8);
                    if (c_dat < kGcRamBase) c_dat += pal;
                    mem.write_u32(tlo + 0, c_dat);
                    mem.write_u32(tlo + 4, c_fmt);
                    mem.write_u16(tlo + 8, n_ent);
                }
            }
            return true;
        }

        // ====================================================================
        // GX Lighting, Channels, TEV Combiner & Pixel Engine (0x80121C64..0x80125924)
        // ====================================================================
        case 0x80121C64u: { // GXInitLightAttn(GXLightObj* lt [r3], a0..k2 [f1..f6])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 40)) {
                for (uint32_t i = 0; i < 6u; ++i) {
                    mem.write_f32(ctx.r[3] + 16u + i * 4u, static_cast<float>(ctx.f[1 + i]));
                }
            }
            return true;
        }
        case 0x80121C80u: { // GXInitLightAttnA(GXLightObj* lt [r3], a0, a1, a2 [f1..f3])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 28)) {
                for (uint32_t i = 0; i < 3u; ++i) {
                    mem.write_f32(ctx.r[3] + 16u + i * 4u, static_cast<float>(ctx.f[1 + i]));
                }
            }
            return true;
        }
        case 0x80121CACu: { // GXInitLightAttnK(GXLightObj* lt [r3], k0, k1, k2 [f1..f3])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 40)) {
                for (uint32_t i = 0; i < 3u; ++i) {
                    mem.write_f32(ctx.r[3] + 28u + i * 4u, static_cast<float>(ctx.f[1 + i]));
                }
            }
            return true;
        }
        case 0x80121CD8u: { // GXInitLightSpot(GXLightObj* lt [r3], f32 cutoff [f1], GXSpotFn spot_func [r4])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 28)) {
                const float cutoff = static_cast<float>(ctx.f[1]);
                uint32_t fn = ctx.r[4];
                if (cutoff <= 0.0f || cutoff > 90.0f) fn = 0u;
                float a0 = 1.0f, a1 = 0.0f, a2 = 0.0f;
                if (fn >= 1u && fn <= 6u) {
                    const float d = std::cos(cutoff * 3.14159265358979323846f / 180.0f);
                    const float omd = 1.0f - d;
                    if (std::fabs(omd) > 1e-6f) {
                        const float inv2 = 1.0f / (omd * omd);
                        switch (fn) {
                            case 1u: a0 = -1000.0f * d; a1 = 1000.0f; a2 = 0.0f; break;
                            case 2u: a0 = -d / omd; a1 = 1.0f / omd; a2 = 0.0f; break;
                            case 3u: a0 = 0.0f; a1 = -d / omd; a2 = 1.0f / omd; break;
                            case 4u: a0 = d * (d - 2.0f) * inv2; a1 = 2.0f * inv2; a2 = -inv2; break;
                            case 5u: a0 = -4.0f * d * inv2; a1 = 4.0f * (1.0f + d) * inv2; a2 = -4.0f * inv2; break;
                            case 6u: a0 = 1.0f - 2.0f * d * d * inv2; a1 = 4.0f * d * inv2; a2 = -2.0f * inv2; break;
                            default: break;
                        }
                    }
                }
                mem.write_f32(ctx.r[3] + 16u, a0);
                mem.write_f32(ctx.r[3] + 20u, a1);
                mem.write_f32(ctx.r[3] + 24u, a2);
            }
            return true;
        }
        case 0x80121E68u: { // GXInitLightDistAttn(GXLightObj* lt [r3], ref_dist [f1], ref_br [f2], dist_func [r4])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 40)) {
                const float ref_dist = static_cast<float>(ctx.f[1]);
                const float ref_br   = static_cast<float>(ctx.f[2]);
                uint32_t fn = ctx.r[4];
                if (ref_dist < 0.0f || ref_br <= 0.0f || ref_br >= 1.0f) fn = 0u;
                float k0 = 1.0f, k1 = 0.0f, k2 = 0.0f;
                if (ref_dist > 1e-6f && ref_br > 1e-6f) {
                    const float omb = 1.0f - ref_br;
                    if (fn == 1u) {
                        k1 = omb / (ref_br * ref_dist);
                    } else if (fn == 2u) {
                        k1 = 0.5f * omb / (ref_br * ref_dist);
                        k2 = 0.5f * omb / (ref_br * ref_dist * ref_dist);
                    } else if (fn == 3u) {
                        k2 = omb / (ref_br * ref_dist * ref_dist);
                    }
                }
                mem.write_f32(ctx.r[3] + 28u, k0);
                mem.write_f32(ctx.r[3] + 32u, k1);
                mem.write_f32(ctx.r[3] + 36u, k2);
            }
            return true;
        }
        case 0x80121F38u: { // GXInitLightPos(GXLightObj* lt [r3], x, y, z [f1..f3])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 52)) {
                mem.write_f32(ctx.r[3] + 40u, static_cast<float>(ctx.f[1]));
                mem.write_f32(ctx.r[3] + 44u, static_cast<float>(ctx.f[2]));
                mem.write_f32(ctx.r[3] + 48u, static_cast<float>(ctx.f[3]));
            }
            return true;
        }
        case 0x80121F64u: { // GXInitLightDir(GXLightObj* lt [r3], nx, ny, nz [f1..f3])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 64)) {
                mem.write_f32(ctx.r[3] + 52u, -static_cast<float>(ctx.f[1]));
                mem.write_f32(ctx.r[3] + 56u, -static_cast<float>(ctx.f[2]));
                mem.write_f32(ctx.r[3] + 60u, -static_cast<float>(ctx.f[3]));
            }
            return true;
        }
        case 0x80121FA8u: { // GXInitSpecularDir(GXLightObj* lt [r3], nx, ny, nz [f1..f3])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 64)) {
                const float hx = -static_cast<float>(ctx.f[1]);
                const float hy = -static_cast<float>(ctx.f[2]);
                const float hz = 1.0f - static_cast<float>(ctx.f[3]);
                const float mag = std::sqrt(hx * hx + hy * hy + hz * hz);
                const float inv = (mag > 1e-6f) ? (1.0f / mag) : 0.0f;
                mem.write_f32(ctx.r[3] + 52u, hx * inv);
                mem.write_f32(ctx.r[3] + 56u, hy * inv);
                mem.write_f32(ctx.r[3] + 60u, hz * inv);
                mem.write_f32(ctx.r[3] + 40u, -static_cast<float>(ctx.f[1]) * 100000.0f);
                mem.write_f32(ctx.r[3] + 44u, -static_cast<float>(ctx.f[2]) * 100000.0f);
                mem.write_f32(ctx.r[3] + 48u, -static_cast<float>(ctx.f[3]) * 100000.0f);
            }
            return true;
        }
        case 0x8012208Cu: { // GXInitSpecularDirHA(GXLightObj* lt [r3], nx, ny, nz, hx, hy, hz [f1..f6])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 64)) {
                mem.write_f32(ctx.r[3] + 52u, static_cast<float>(ctx.f[4]));
                mem.write_f32(ctx.r[3] + 56u, static_cast<float>(ctx.f[5]));
                mem.write_f32(ctx.r[3] + 60u, static_cast<float>(ctx.f[6]));
                mem.write_f32(ctx.r[3] + 40u, -static_cast<float>(ctx.f[1]) * 100000.0f);
                mem.write_f32(ctx.r[3] + 44u, -static_cast<float>(ctx.f[2]) * 100000.0f);
                mem.write_f32(ctx.r[3] + 48u, -static_cast<float>(ctx.f[3]) * 100000.0f);
            }
            return true;
        }
        case 0x801220B8u: { // GXInitLightColor(GXLightObj* lt [r3], GXColor color [r4 pointer])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 16) &&
                ctx.r[4] >= kGcRamBase && mem.is_valid_range(ctx.r[4], 4)) {
                mem.write_u32(ctx.r[3] + 12u, mem.read_u32(ctx.r[4]));
            }
            return true;
        }
        case 0x801220D0u: { // GXLoadLightObjImm(const GXLightObj* lt [r3], GXLightID id [r4])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 64)) {
                const uint8_t* src = mem.raw_ptr(ctx.r[3]);
                GXLightState ls{};
                for (int k = 0; k < 4; ++k) {
                    ls.color[k] = static_cast<float>(src[12 + k]) * kInv255;
                }
                ls.a[0] = read_be_f32_unaligned(src + 16);
                ls.a[1] = read_be_f32_unaligned(src + 20);
                ls.a[2] = read_be_f32_unaligned(src + 24);
                ls.k[0] = read_be_f32_unaligned(src + 28);
                ls.k[1] = read_be_f32_unaligned(src + 32);
                ls.k[2] = read_be_f32_unaligned(src + 36);
                ls.pos[0] = read_be_f32_unaligned(src + 40);
                ls.pos[1] = read_be_f32_unaligned(src + 44);
                ls.pos[2] = read_be_f32_unaligned(src + 48);
                ls.dir[0] = read_be_f32_unaligned(src + 52);
                ls.dir[1] = read_be_f32_unaligned(src + 56);
                ls.dir[2] = read_be_f32_unaligned(src + 60);
                const float pmag2 = ls.pos[0] * ls.pos[0] + ls.pos[1] * ls.pos[1] + ls.pos[2] * ls.pos[2];
                ls.pos_is_zero = (pmag2 < 1e-6f);
                const float dlen2 = ls.dir[0] * ls.dir[0] + ls.dir[1] * ls.dir[1] + ls.dir[2] * ls.dir[2];
                if (dlen2 > 1e-12f) {
                    const float invd = fast_inv_sqrt(dlen2);
                    ls.dir_unit[0] = ls.dir[0] * invd;
                    ls.dir_unit[1] = ls.dir[1] * invd;
                    ls.dir_unit[2] = ls.dir[2] * invd;
                    ls.dir_valid = true;
                } else {
                    ls.dir_valid = false;
                }
                ls.loaded = true;
                loaded_lights_mask_ |= static_cast<uint8_t>(ctx.r[4] & 0xFFu);
                for (uint32_t i = 0; i < 8u; ++i) {
                    if ((ctx.r[4] & (1u << i)) != 0u) {
                        lights_[i] = ls;
                    }
                }
            }
            return true;
        }
        case 0x8012218Cu: { // GXSetChanAmbColor(GXChannelID chan [r3], GXColor amb_color [r4])
            if (ctx.r[4] >= kGcRamBase && mem.is_valid_range(ctx.r[4], 4)) {
                const uint32_t chan = ctx.r[3];
                const uint32_t ch = chan & 1u;
                float c[4];
                for (int k = 0; k < 4; ++k) c[k] = mem.read_u8(ctx.r[4] + k) / 255.0f;
                if (chan == 0u || chan == 1u) {
                    chan_amb_color_[ch][0] = c[0];
                    chan_amb_color_[ch][1] = c[1];
                    chan_amb_color_[ch][2] = c[2];
                } else if (chan == 2u || chan == 3u) {
                    chan_amb_color_[ch][3] = c[3];
                } else if (chan == 4u || chan == 5u) {
                    for (int k = 0; k < 4; ++k) chan_amb_color_[ch][k] = c[k];
                }
            }
            return true;
        }
        case 0x80122280u: { // GXSetChanMatColor(GXChannelID chan [r3], GXColor mat_color [r4])
            if (ctx.r[4] >= kGcRamBase && mem.is_valid_range(ctx.r[4], 4)) {
                const uint32_t chan = ctx.r[3];
                const uint32_t ch = chan & 1u;
                float c[4];
                for (int k = 0; k < 4; ++k) c[k] = mem.read_u8(ctx.r[4] + k) / 255.0f;
                if (chan == 0u || chan == 1u) {
                    chan_mat_color_[ch][0] = c[0];
                    chan_mat_color_[ch][1] = c[1];
                    chan_mat_color_[ch][2] = c[2];
                } else if (chan == 2u || chan == 3u) {
                    chan_mat_color_[ch][3] = c[3];
                } else if (chan == 4u || chan == 5u) {
                    for (int k = 0; k < 4; ++k) chan_mat_color_[ch][k] = c[k];
                }
            }
            return true;
        }
        case 0x80122374u: // GXSetNumChans
            num_chans_ = ctx.r[3];
            return true;
        case 0x801223B8u: { // GXSetChanCtrl(chan [r3], enable [r4], amb_src [r5], mat_src [r6], light_mask [r7], diff_fn [r8], attn_fn [r9])
            GXChanCtrlState st{};
            st.enable     = (ctx.r[4] != 0u);
            st.amb_src    = ctx.r[5] & 1u;
            st.mat_src    = ctx.r[6] & 1u;
            st.light_mask = ctx.r[7] & 0xFFu;
            st.diff_fn    = ctx.r[8];
            st.attn_fn    = ctx.r[9];
            const uint32_t chan = ctx.r[3];
            if (chan < 4u) {
                chan_ctrl_[chan] = st;
            } else if (chan == 4u) {
                chan_ctrl_[0] = st;
                chan_ctrl_[2] = st;
            } else if (chan == 5u) {
                chan_ctrl_[1] = st;
                chan_ctrl_[3] = st;
            }
            return true;
        }
        case 0x80125170u: // GXSetNumTevStages(u8 nStages [r3])
            num_tev_stages_ = std::clamp(ctx.r[3], 1u, 16u);
            tev_scale_dirty_ = true;
            stage1_dirty_    = true;
            batch_state_dirty_ = true;
            return true;
        case 0x801249B8u: // GXSetTevOp(GXTevStageID id [r3], GXTevMode mode [r4])
            {
                const uint32_t st = ctx.r[3] & 15u;
                tev_stages_[st].color_op      = 0u;
                tev_stages_[st].color_bias    = 0u;
                tev_stages_[st].color_scale   = 0u;
                tev_stages_[st].color_clamp   = 1u;
                tev_stages_[st].color_out_reg = 0u;
                tev_stages_[st].alpha_op      = 0u;
                tev_stages_[st].alpha_scale   = 0u;
            }
            if (ctx.r[3] == 0u) {
                tev_mode_ = ctx.r[4];
                auto set_c = [&](uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3) {
                    tev_stages_[0].color_in[0] = c0;
                    tev_stages_[0].color_in[1] = c1;
                    tev_stages_[0].color_in[2] = c2;
                    tev_stages_[0].color_in[3] = c3;
                };
                if (tev_mode_ == 0u) set_c(15, 8, 10, 15);
                else if (tev_mode_ == 1u) set_c(10, 8, 9, 15);
                else if (tev_mode_ == 2u) set_c(10, 12, 8, 15);
                else if (tev_mode_ == 3u) set_c(15, 15, 15, 8);
                else if (tev_mode_ == 4u) set_c(15, 15, 15, 10);
            }
            tev_scale_dirty_ = true;
            stage1_dirty_    = true;
            batch_state_dirty_ = true;
            return true;
        case 0x80124B9Cu: { // GXSetTevColor(GXTevRegID id [r3], GXColor color [r4])
            uint32_t id = ctx.r[3] & 3u;
            if (const uint8_t* p = mem.fast_ram_ptr(ctx.r[4], 4u)) {
                for (int k = 0; k < 4; ++k) tev_colors_[id][k] = p[k] / 255.0f;
            } else if (ctx.r[4] >= kGcRamBase && mem.is_valid_range(ctx.r[4], 4)) {
                for (int k = 0; k < 4; ++k) tev_colors_[id][k] = mem.read_u8(ctx.r[4] + k) / 255.0f;
            }
            if (id == 0u) batch_state_dirty_ = true;
            return true;
        }
        case 0x80124C10u: { // GXSetTevColorS10(GXTevRegID id [r3], GXColorS10 color [r4])
            uint32_t id = ctx.r[3] & 3u;
            if (const uint8_t* p = mem.fast_ram_ptr(ctx.r[4], 8u)) {
                for (int k = 0; k < 4; ++k) {
                    const int16_t s = static_cast<int16_t>(read_be16_unaligned(p + k * 2));
                    tev_colors_[id][k] = std::clamp(s / 255.0f, 0.0f, 1.0f);
                }
            } else if (ctx.r[4] >= kGcRamBase && mem.is_valid_range(ctx.r[4], 8)) {
                for (int k = 0; k < 4; ++k) tev_colors_[id][k] = std::clamp(mem.read_s16(ctx.r[4] + k * 2) / 255.0f, 0.0f, 1.0f);
            }
            if (id == 0u) batch_state_dirty_ = true;
            return true;
        }
        case 0x80124C84u: // GXSetTevKColor
            return true;
        case 0x80124A88u: { // GXSetTevAlphaIn(stage [r3], a [r4], b [r5], c [r6], d [r7])
            uint32_t st = ctx.r[3] & 15u;
            tev_stages_[st].alpha_in[0] = static_cast<uint8_t>(ctx.r[4] & 0xFFu);
            tev_stages_[st].alpha_in[1] = static_cast<uint8_t>(ctx.r[5] & 0xFFu);
            tev_stages_[st].alpha_in[2] = static_cast<uint8_t>(ctx.r[6] & 0xFFu);
            tev_stages_[st].alpha_in[3] = static_cast<uint8_t>(ctx.r[7] & 0xFFu);
            stage1_dirty_ = true;
            batch_state_dirty_ = true;
            return true;
        }
        case 0x80124ACCu: { // GXSetTevColorOp(stage [r3], op [r4], bias [r5], scale [r6], clamp [r7], out_reg [r8])
            const uint32_t st = ctx.r[3] & 15u;
            tev_stages_[st].color_op      = static_cast<uint8_t>(ctx.r[4] & 0xFFu);
            tev_stages_[st].color_bias    = static_cast<uint8_t>(ctx.r[5] & 0x03u);
            tev_stages_[st].color_scale   = static_cast<uint8_t>(ctx.r[6] & 0x03u);
            tev_stages_[st].color_clamp   = static_cast<uint8_t>(ctx.r[7] ? 1u : 0u);
            tev_stages_[st].color_out_reg = static_cast<uint8_t>(ctx.r[8] & 0x03u);
            tev_scale_dirty_ = true;
            stage1_dirty_    = true;
            batch_state_dirty_ = true;
            return true;
        }
        case 0x80124B34u: { // GXSetTevAlphaOp(stage [r3], op [r4], bias [r5], scale [r6], clamp [r7], out_reg [r8])
            const uint32_t st = ctx.r[3] & 15u;
            tev_stages_[st].alpha_op    = static_cast<uint8_t>(ctx.r[4] & 0xFFu);
            tev_stages_[st].alpha_scale = static_cast<uint8_t>(ctx.r[6] & 0x03u);
            stage1_dirty_ = true;
            batch_state_dirty_ = true;
            return true;
        }
        case 0x80124EC0u: // GXSetAlphaCompare
        case 0x801251A0u: // GXSetFog
            return true;
        case 0x80124A44u: { // GXSetTevColorIn(stage [r3], a [r4], b [r5], c [r6], d [r7])
            uint32_t st = ctx.r[3] & 15u;
            const uint8_t a = static_cast<uint8_t>(ctx.r[4] & 0xFFu);
            const uint8_t b = static_cast<uint8_t>(ctx.r[5] & 0xFFu);
            const uint8_t c = static_cast<uint8_t>(ctx.r[6] & 0xFFu);
            const uint8_t d = static_cast<uint8_t>(ctx.r[7] & 0xFFu);
            tev_stages_[st].color_in[0] = a;
            tev_stages_[st].color_in[1] = b;
            tev_stages_[st].color_in[2] = c;
            tev_stages_[st].color_in[3] = d;
            if (st == 0u) {
                if ((a == 15u && b == 15u && c == 15u && d == 8u) ||
                    (a == 15u && ((b == 8u && c == 12u) || (b == 12u && c == 8u)) && d == 15u)) {
                    tev_mode_ = 3u; // GX_REPLACE
                } else if ((a == 15u && b == 15u && c == 15u && d == 10u) ||
                           (a == 15u && ((b == 10u && c == 12u) || (b == 12u && c == 10u)) && d == 15u)) {
                    tev_mode_ = 4u; // GX_PASSCLR
                } else if (a == 10u && b == 8u && c == 9u && d == 15u) {
                    tev_mode_ = 1u; // GX_DECAL
                } else if (a == 10u && b == 12u && c == 8u && d == 15u) {
                    tev_mode_ = 2u; // GX_BLEND (lerp RASC -> ONE by TEXC)
                } else if (a == 10u && b == 2u && c == 8u && d == 15u) {
                    tev_mode_ = 6u; // lerp(RASC, C0, TEXC)
                } else if (a == 15u && ((b == 8u && c == 2u) || (b == 2u && c == 8u)) && d == 15u) {
                    tev_mode_ = 5u; // TEXC * C0
                } else if (a == 15u && b == 15u && c == 15u && d == 2u) {
                    tev_mode_ = 7u; // C0 flat
                } else if (a == 8u || b == 8u || c == 8u || d == 8u ||
                           a == 9u || b == 9u || c == 9u || d == 9u) {
                    tev_mode_ = 0u; // GX_MODULATE
                } else {
                    tev_mode_ = 4u; // untextured RASC
                }
            }
            tev_scale_dirty_ = true;
            stage1_dirty_    = true;
            batch_state_dirty_ = true;
            return true;
        }
        case 0x80124F98u: { // GXSetTevOrder(stage [r3], coord [r4], map [r5], color [r6])
            uint32_t st = ctx.r[3] & 15u;
            tev_stages_[st].tex_coord = static_cast<uint8_t>(ctx.r[4] & 0xFFu);
            tev_stages_[st].tex_map   = static_cast<uint8_t>(ctx.r[5] & 0xFFu);
            tev_stages_[st].chan_id   = static_cast<uint8_t>(ctx.r[6] & 0xFFu);
            stage1_dirty_ = true;
            batch_state_dirty_ = true;
            return true;
        }
        case 0x80125684u: // GXSetBlendMode(type [r3], src [r4], dst [r5], op [r6])
            blend_type_ = ctx.r[3];
            blend_src_  = ctx.r[4];
            blend_dst_  = ctx.r[5];
            batch_state_dirty_ = true;
            return true;
        case 0x801256D8u: // GXSetColorUpdate
        case 0x80125704u: // GXSetAlphaUpdate
        case 0x80125764u: // GXSetZCompLoc
        case 0x8012579Cu: // GXSetPixelFmt
        case 0x80125884u: // GXSetDither
        case 0x801258B0u: // GXSetDstAlpha
            return true;
        case 0x80125730u: // GXSetZMode(compare_enable [r3], func [r4], update_enable [r5])
            z_compare_enable_ = (ctx.r[3] != 0);
            z_func_           = ctx.r[4];
            z_write_enable_   = (ctx.r[5] != 0);
            batch_state_dirty_ = true;
            return true;
        case 0x80121674u: // GXSetCopyClear(GXColor clear_clr [r3], u32 clear_z [r4])
            if (ctx.r[3] >= kGcRamBase && mem.is_valid_range(ctx.r[3], 4)) {
                clear_rgba_[0] = mem.read_u8(ctx.r[3] + 0);
                clear_rgba_[1] = mem.read_u8(ctx.r[3] + 1);
                clear_rgba_[2] = mem.read_u8(ctx.r[3] + 2);
                clear_rgba_[3] = mem.read_u8(ctx.r[3] + 3);
            }
            clear_z_ = ctx.r[4];
            return true;
        case 0x801216DCu: // GXSetCopyFilter
            return true;
        case 0x80120F4Cu: { // GXSetDispCopySrc(left [r3], top [r4], wd [r5], ht [r6])
            const uint16_t w = static_cast<uint16_t>(ctx.r[5] & 0xFFFFu);
            const uint16_t h = static_cast<uint16_t>(ctx.r[6] & 0xFFFFu);
            if (w > 0u && h > 0u) {
                disp_copy_src_[0] = static_cast<uint16_t>(ctx.r[3] & 0xFFFFu);
                disp_copy_src_[1] = static_cast<uint16_t>(ctx.r[4] & 0xFFFFu);
                disp_copy_src_[2] = w;
                disp_copy_src_[3] = h;
            }
            return true;
        }
        case 0x8012106Cu: { // GXSetDispCopyDst(wd [r3], ht [r4])
            const uint16_t w = static_cast<uint16_t>(ctx.r[3] & 0xFFFFu);
            const uint16_t h = static_cast<uint16_t>(ctx.r[4] & 0xFFFFu);
            if (w > 0u && h > 0u) {
                disp_copy_dst_[0] = w;
                disp_copy_dst_[1] = h;
            }
            return true;
        }
        case 0x801215ACu: // GXSetDispCopyYScale
            return true;
        case 0x80121904u: // GXSetDispCopyGamma(GXGamma gamma [r3])
            disp_copy_gamma_ = ctx.r[3] & 0x03u;
            return true;
        case 0x80121920u: // GXCopyDisp
        case 0x80121A7Cu: // GXCopyTex
            return true;

        default:
            // Catch-all for any remaining GX* (0x8011BED8..0x801279EC) or VI* (0x8010C434..0x8010EEC8) calls
            if ((vaddr >= 0x8010C434u && vaddr <= 0x8010EEC8u) ||
                (vaddr >= 0x8011BED8u && vaddr <= 0x801279ECu)) {
                return true;
            }
            break;
    }
    return false;
}

} // namespace pn03

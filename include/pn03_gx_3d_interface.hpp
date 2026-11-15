#pragma once
#include "pn03_config.hpp"
#include "pn03_ppc_context.hpp"
#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace pn03 {

// ============================================================================
// GameCube Flipper GPU (GX + VI) Complete 3D Hardware Interface & State Machine
// Maps all 270 GX* and VI* SDK functions (0x8010C434..0x801279EC) in main.dol
// plus 0xCC008000 Write-Gather Pipe & GXCallDisplayList to Direct3D 11 draw calls.
// ============================================================================

enum GXPrimitive : uint8_t {
    GX_QUADS         = 0x80,
    GX_TRIANGLES     = 0x90,
    GX_TRIANGLESTRIP = 0x98,
    GX_TRIANGLEFAN   = 0xA0,
    GX_LINES         = 0xA8,
    GX_LINESTRIP     = 0xB0,
    GX_POINTS        = 0xB8
};

enum GXTexFmt : uint32_t {
    GX_TF_I4     = 0x0,
    GX_TF_I8     = 0x1,
    GX_TF_IA4    = 0x2,
    GX_TF_IA8    = 0x3,
    GX_TF_RGB565 = 0x4,
    GX_TF_RGB5A3 = 0x5,
    GX_TF_RGBA8  = 0x6,
    GX_TF_C4     = 0x8,
    GX_TF_C8     = 0x9,
    GX_TF_C14X2  = 0xA,
    GX_TF_CMPR   = 0xE // GameCube S3TC / DXT1 8x8 tiled compressed format
};

enum GXAttr : uint32_t {
    GX_VA_PNMTXIDX   = 0,
    GX_VA_TEX0MTXIDX = 1,
    GX_VA_POS        = 9,
    GX_VA_NRM        = 10,
    GX_VA_CLR0       = 11,
    GX_VA_CLR1       = 12,
    GX_VA_TEX0       = 13,
    GX_VA_TEX1       = 14,
    GX_VA_TEX2       = 15,
    GX_VA_TEX3       = 16,
    GX_VA_TEX4       = 17,
    GX_VA_TEX5       = 18,
    GX_VA_TEX6       = 19,
    GX_VA_TEX7       = 20,
    GX_VA_MAX_ATTR   = 26
};

enum GXAttrType : uint8_t {
    GX_NONE    = 0,
    GX_DIRECT  = 1,
    GX_INDEX8  = 2,
    GX_INDEX16 = 3
};

struct GXVtxAttrFmtSpec {
    uint32_t comp_cnt  = 1;
    uint32_t comp_type = 4; // 0=U8, 1=S8, 2=U16, 3=S16, 4=F32, 5=RGBA8
    uint8_t  frac      = 0;
};

struct GXArraySpec {
    uint32_t base_vaddr = 0;
    uint8_t  stride     = 0;
};

struct GXVertex {
    float pos[3]    = {0.0f, 0.0f, 0.0f};
    float nrm[3]    = {0.0f, 0.0f, 1.0f};
    float color0[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float uv0[2]    = {0.0f, 0.0f};
};

struct GXTevStageConfig {
    uint8_t color_in[4]   = {15, 15, 15, 10}; // a, b, c, d
    uint8_t alpha_in[4]   = {7, 7, 7, 5};
    uint8_t color_op      = 0;
    uint8_t color_bias    = 0;
    uint8_t color_scale   = 0; // 0=1x, 1=2x, 2=4x, 3=0.5x
    uint8_t color_clamp   = 1;
    uint8_t color_out_reg = 0; // 0=GX_TEVPREV
    uint8_t alpha_op      = 0;
    uint8_t alpha_scale   = 0;
    uint8_t tex_coord     = 0;
    uint8_t tex_map       = 0;
    uint8_t chan_id       = 0;
};

struct GXBoundTexture {
    uint32_t data_vaddr = 0;
    uint16_t width      = 0;
    uint16_t height     = 0;
    uint32_t format     = GX_TF_RGBA8;
    uint8_t  wrap_s     = 1;
    uint8_t  wrap_t     = 1;
    uint32_t tlut_name  = 0;
    uint32_t max_aniso  = 16;
};

struct GXTlutSlot {
    uint32_t data_vaddr  = 0;
    uint32_t format      = 1; // 0=GX_TL_IA8, 1=GX_TL_RGB565, 2=GX_TL_RGB5A3
    uint16_t num_entries = 0;
};

struct GXDrawBatch {
    uint32_t       index_offset = 0;
    uint32_t       index_count  = 0;
    float          proj_mtx[4][4]{};
    uint32_t       proj_type    = 0;
    float          tev_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    bool           has_texture  = false;
    GXBoundTexture texture{};
    GXTlutSlot     tlut{};
    bool           has_stage1_tex = false;
    uint32_t       stage1_op      = 0; // 0=none, 1=mul alpha (out.a*=tex1.a), 2=modulate rgba (out*=tex1)
    GXBoundTexture stage1_texture{};
    GXTlutSlot     stage1_tlut{};
    bool           z_enable     = true;
    bool           z_write      = true;
    uint32_t       blend_type   = 0;
    uint32_t       blend_src    = 4;
    uint32_t       blend_dst    = 5;
    uint32_t       cull_mode    = 0;
    uint32_t       tev_mode     = 0;
    float          tev_scale    = 1.0f;
    float          viewport[6]  = {0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f};
    uint32_t       scissor[4]   = {0, 0, 640, 480};
};

struct GXOverlayTextItem {
    float       x = 0.0f;
    float       y = 0.0f;
    float       scale = 1.0f;
    uint32_t    rgba = 0xFFFFFFFFu;
    std::string text;
};

class GX3DInterface {
public:
    explicit GX3DInterface(const RuntimeConfig& cfg);

    // Master HLE router for all VI*, GX*, and TEX* calls
    bool dispatch_gx_vi_call(uint32_t vaddr, PPCContext& ctx, Memory& mem);

    // Attaches 0xCC008000 Write-Gather Pipe callbacks to Memory
    void bind_fifo_to_memory(Memory& mem);

    // Hardware FIFO Write-Gather Pipe handlers (0xCC008000)
    void on_fifo_write_u8(uint8_t val);
    void on_fifo_write_u16(uint16_t val);
    void on_fifo_write_u32(uint32_t val);
    void on_fifo_write_f32(float val);

    // Executes a compiled GameCube binary display list (GXCallDisplayList @ 0x80125B3C)
    void execute_display_list(const Memory& mem, uint32_t list_vaddr, uint32_t byte_len);

    // Decodes any GameCube tiled texture (I4/I8/IA4/IA8/RGB565/RGB5A3/RGBA8/C4/C8/C14X2/CMPR) into linear RGBA8
    std::vector<uint8_t> decode_gc_texture_to_rgba8(
        const Memory& mem,
        const GXBoundTexture& tex,
        const GXTlutSlot* override_tlut = nullptr
    ) const;

    // Submits a high-level vertex batch and converts GX_QUADS / GX_TRIANGLEFAN into indexed D3D11 triangles
    void begin_primitive(GXPrimitive prim, uint8_t vtx_fmt, uint16_t num_verts);
    void submit_vertex(const GXVertex& v);
    void end_primitive();

    // Per-frame reset & overlay text submission
    void clear_frame_geometry();
    void submit_overlay_text(float x, float y, float scale, uint32_t rgba, const std::string& text);

    // Vertex descriptor & attribute format helpers
    void set_vtx_desc(uint32_t attr, uint8_t type);
    void clear_vtx_desc();
    void set_vtx_attr_fmt(uint8_t vtxfmt, uint32_t attr, uint32_t comp_cnt, uint32_t comp_type, uint8_t frac);
    void set_array(uint32_t attr, uint32_t base_vaddr, uint8_t stride);
    uint32_t compute_vertex_byte_stride(uint8_t vtx_fmt) const;

    // Accessors for D3D11 rendering & unit test verification
    uint32_t active_tev_stages() const { return num_tev_stages_; }
    uint32_t current_mtx_idx() const { return current_mtx_idx_; }
    size_t   submitted_triangle_count() const { return index_buffer_.size() / 3; }
    const float (&projection_mtx() const)[4][4] { return proj_mtx_; }
    const float (&pos_mtx(size_t idx) const)[3][4] { return pos_mtx_[idx % 10]; }
    const GXBoundTexture& bound_texture(size_t slot) const { return bound_textures_[slot & 7]; }
    const GXTlutSlot& tlut_slot(size_t slot) const { return tlut_slots_[slot % 20]; }
    const std::vector<GXVertex>& vertices() const { return vertex_buffer_; }
    const std::vector<uint32_t>& indices() const { return index_buffer_; }
    const std::vector<GXDrawBatch>& draw_batches() const { return draw_batches_; }
    const std::vector<GXOverlayTextItem>& overlay_texts() const { return overlay_texts_; }
    const uint8_t (&clear_rgba() const)[4] { return clear_rgba_; }
    const float (&viewport() const)[6] { return viewport_; }
    const uint32_t (&scissor() const)[4] { return scissor_; }
    const uint16_t (&disp_copy_src() const)[4] { return disp_copy_src_; }
    uint32_t disp_copy_gamma() const { return disp_copy_gamma_; }
    float effective_tev_scale() const;
    void set_config(const RuntimeConfig& cfg) { cfg_ = cfg; }
    const RuntimeConfig& config() const { return cfg_; }
    uint32_t current_vi_retrace_count() const noexcept { return vi_retrace_count_; }
    void advance_vi_retraces(uint32_t count = 1u) noexcept { vi_retrace_count_ += count; }

private:
    struct DLAttrOp {
        uint8_t        dt           = GX_NONE;
        uint8_t        comp_cnt     = 0;
        uint8_t        comp_type    = 4;
        uint8_t        elem_size    = 0;
        uint16_t       dl_offset    = 0;
        uint16_t       arr_stride   = 0;
        uint32_t       arr_base     = 0;
        uint32_t       max_byte_off = 0;
        const uint8_t* arr_ptr      = nullptr;
        float          scale        = 1.0f;
    };
    struct DLAttrPlan {
        DLAttrOp op_mtx{};
        DLAttrOp op_pos{};
        DLAttrOp op_nrm{};
        DLAttrOp op_clr0{};
        DLAttrOp op_tex0{};
        uint32_t vtx_stride = 0;
        bool     has_mtx    = false;
        bool     has_pos    = false;
        bool     has_nrm    = false;
        bool     has_clr0   = false;
        bool     has_tex0   = false;
    };

    void rebuild_dl_plan(const Memory& mem, uint8_t vtx_fmt, bool need_nrm, DLAttrPlan& plan) const;
    const DLAttrPlan& get_or_build_dl_plan(const Memory& mem, uint8_t vtx_fmt, bool need_nrm) const;
    void update_cached_stage1() const;

    GXVertex decode_one_vertex_from_stream(const uint8_t* stream_ptr, uint32_t& io_offset, uint8_t vtx_fmt, const Memory* mem) const;
    void transform_and_shade_vertex(const GXVertex& v, GXVertex& tv, uint32_t mtx_idx, bool need_lighting, bool need_nrm) const;
    void append_primitive_indices(uint32_t base_idx, size_t n);
    void emit_draw_batch(uint32_t first_idx_offset, uint32_t added_indices);
    void try_flush_fifo_vertices();
    void apply_aspect_ratio_to_projection();

    RuntimeConfig cfg_;

    // Transform Unit (XF) Matrices
    float    proj_mtx_[4][4]{};
    uint32_t proj_type_        = 0; // 0 = GX_PERSPECTIVE, 1 = GX_ORTHOGRAPHIC
    float    pos_mtx_[10][3][4]{};
    float    nrm_mtx_[10][3][3]{};
    bool     has_nrm_mtx_[10]{};
    float    tex_mtx_[20][3][4]{};
    uint32_t current_mtx_idx_  = 0;
    std::array<uint32_t, 8> tex_gen_func_{};
    std::array<uint32_t, 8> tex_gen_src_{};
    std::array<uint32_t, 8> tex_gen_mtx_{60u, 60u, 60u, 60u, 60u, 60u, 60u, 60u};
    mutable uint8_t         pending_vtx_mtx_idx_     = 0;
    mutable bool            has_pending_vtx_mtx_idx_ = false;

    // Viewport, Scissor & EFB Copy State
    float    viewport_[6]       = {0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f};
    uint32_t scissor_[4]        = {0, 0, 640, 480};
    int32_t  scissor_offset_[2] = {0, 0};
    uint16_t disp_copy_src_[4]  = {0u, 0u, 640u, 480u};
    uint16_t disp_copy_dst_[2]  = {640u, 480u};
    uint32_t disp_copy_gamma_   = 0u; // 0=1.0, 1=1.7, 2=2.2
    uint8_t  clear_rgba_[4]     = {8, 12, 22, 255};
    uint32_t clear_z_          = 0x00FFFFFFu;

    // Vertex Descriptor, VAT, Array, TEV & Pixel Engine State
    uint32_t vtx_desc_mask_    = 0;
    std::array<uint8_t, GX_VA_MAX_ATTR> vtx_desc_types_{};
    std::array<std::array<GXVtxAttrFmtSpec, GX_VA_MAX_ATTR>, 8> vat_table_{};
    std::array<GXArraySpec, GX_VA_MAX_ATTR> array_table_{};
    mutable DLAttrPlan     dl_plans_[16]{};
    mutable uint16_t       dl_plan_valid_mask_ = 0;
    mutable const Memory*  dl_plan_mem_        = nullptr;

    uint32_t num_tev_stages_   = 1;
    uint32_t num_tex_gens_     = 1;
    uint32_t num_chans_        = 1;
    uint32_t cull_mode_        = 0; // GX_CULL_NONE
    bool     z_compare_enable_ = true;
    uint32_t z_func_           = 3; // GX_LEQUAL
    bool     z_write_enable_   = true;
    uint32_t blend_type_       = 0;
    uint32_t blend_src_        = 4;
    uint32_t blend_dst_        = 5;
    uint32_t tev_mode_         = 4; // 0=MODULATE, 1=DECAL, 2=BLEND, 3=REPLACE, 4=PASSCLR
    std::array<GXTevStageConfig, 16> tev_stages_{};
    float    tev_colors_[4][4]{};
    float    tev_kcolors_[4][4]{};
    mutable float          cached_tev_scale_   = 1.0f;
    mutable bool           tev_scale_dirty_    = true;
    mutable bool           stage1_dirty_       = true;
    mutable bool           cached_has_stage1_  = false;
    mutable uint32_t       cached_stage1_op_   = 0;
    mutable GXBoundTexture cached_stage1_tex_{};
    mutable GXTlutSlot     cached_stage1_tlut_{};
    float    chan_mat_color_[2][4] = {{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}};
    float    chan_amb_color_[2][4] = {{1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}};

    struct GXChanCtrlState {
        bool     enable     = false;
        uint32_t amb_src    = 1; // 0 = GX_SRC_REG, 1 = GX_SRC_VTX
        uint32_t mat_src    = 1; // 0 = GX_SRC_REG, 1 = GX_SRC_VTX
        uint32_t light_mask = 0;
        uint32_t diff_fn    = 0; // 0 = GX_DF_NONE, 1 = GX_DF_SIGNED, 2 = GX_DF_CLAMP
        uint32_t attn_fn    = 2; // 0 = GX_AF_SPEC, 1 = GX_AF_SPOT, 2 = GX_AF_NONE
    };
    struct GXLightState {
        float pos[3]      = {0.0f, 0.0f, 0.0f};
        float dir[3]      = {0.0f, 0.0f, -1.0f};
        float dir_unit[3] = {0.0f, 0.0f, -1.0f};
        float color[4]    = {1.0f, 1.0f, 1.0f, 1.0f};
        float a[3]        = {1.0f, 0.0f, 0.0f};
        float k[3]        = {1.0f, 0.0f, 0.0f};
        bool  loaded      = false;
        bool  pos_is_zero = true;
        bool  dir_valid   = false;
    };
    std::array<GXChanCtrlState, 4> chan_ctrl_{}; // [0]=COLOR0, [1]=COLOR1, [2]=ALPHA0, [3]=ALPHA1
    std::array<GXLightState, 8>    lights_{};    // GX_LIGHT0..GX_LIGHT7
    uint8_t                        loaded_lights_mask_ = 0;

    // Texture & TLUT Units
    std::array<GXBoundTexture, 8> bound_textures_{};
    std::array<GXTlutSlot, 20>    tlut_slots_{};

    // Immediate/FIFO/DisplayList Geometry Assembly Buffer
    GXPrimitive             active_prim_             = GX_TRIANGLES;
    uint8_t                 active_vtx_fmt_          = 0;
    uint16_t                expected_verts_          = 0;
    bool                    in_gx_begin_             = false;
    uint32_t                current_vtx_byte_stride_ = 0;
    std::vector<uint8_t>    fifo_stream_buf_{};
    Memory*                 bound_mem_               = nullptr;

    std::vector<GXVertex>          prim_Staging_{};
    std::vector<GXVertex>          vertex_buffer_{};
    std::vector<uint32_t>          index_buffer_{};
    std::vector<GXDrawBatch>       draw_batches_{};
    bool                           batch_state_dirty_ = true;
    std::vector<GXOverlayTextItem> overlay_texts_{};

    // VI State
    uint32_t vi_xfb_vaddr_     = 0;
    uint32_t vi_retrace_count_ = 0;
    uint32_t vi_post_cb_vaddr_ = 0;
};

// Global singleton accessor used by dolphin_sdk_hle.cpp
GX3DInterface& global_gx_3d_interface();
void set_global_gx_config(const RuntimeConfig& cfg);
float resolve_target_aspect_ratio(AspectRatioMode mode) noexcept;
void patch_widescreen_aspect_constants(Memory& mem, AspectRatioMode mode);
uint32_t resolve_vi_wait_cadence(const Memory& mem);

} // namespace pn03

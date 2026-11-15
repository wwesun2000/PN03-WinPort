#pragma once
#include "pn03_config.hpp"
#include "pn03_gx_3d_interface.hpp"
#include "pn03_ppc_context.hpp"
#include <cstdint>
#include <string>
#include <unordered_map>

namespace pn03 {

// Complete Windows Native Direct3D 11 + Win32 Window & Pre-Launch Settings GUI Host
class Win32D3D11Host {
public:
    explicit Win32D3D11Host(RuntimeConfig& cfg) : cfg_(cfg) {}
    ~Win32D3D11Host();

    // Displays the interactive Windows GUI Pre-Launch Configuration Dialog
    bool show_prelaunch_settings_window();

    // Creates the native Win32 game window and initializes Direct3D 11 SwapChain, Shaders, Buffers & States
    bool create_render_window_and_d3d11(std::string& err_msg, bool hidden_window = false);

    // Captures the current D3D11 backbuffer to a 24-bit BMP file
    bool dump_framebuffer_bmp(const std::string& path);

    // Pumps Win32 messages (Alt+Enter fullscreen toggle, ESC exit)
    bool pump_messages();

    // Clears MSAA render target & depth-stencil view
    void begin_d3d11_frame(float clear_r = 0.03f, float clear_g = 0.05f, float clear_b = 0.09f);

    // Uploads GX3DInterface vertex/index buffers, binds decoded GC textures, executes DrawIndexed batches
    void render_gx_draw_batches(const Memory& mem, GX3DInterface& gx);

    // Submits queued GX batches (if not yet submitted) and flushes the D3D11 command queue before frame pacing
    void flush_d3d11();

    // Renders any remaining queued GX batches and presents the DXGI swap chain
    void end_d3d11_frame_and_present();

    bool is_initialized() const { return initialized_; }
    bool is_close_requested() const { return close_requested_; }
    void mark_close_requested() { close_requested_ = true; }
    size_t last_rendered_batch_count() const { return last_rendered_batches_; }
    size_t last_rendered_triangle_count() const { return last_rendered_triangles_; }
    uint32_t efb_width() const { return efb_width_; }
    uint32_t efb_height() const { return efb_height_; }
    uint32_t swapchain_width() const { return swapchain_width_; }
    uint32_t swapchain_height() const { return swapchain_height_; }
    uint32_t active_msaa_samples() const { return efb_msaa_samples_; }
    void handle_window_resize(uint32_t width, uint32_t height);
    static void enable_process_dpi_awareness();

    // Embedded HLSL Shaders for GameCube GX TEV Emulation & FXAA Anti-Aliasing
    static const char* gx_tev_hlsl_source();
    static const char* fxaa_post_hlsl_source();
    static constexpr float fxaa_subpix_quality() { return 0.25f; }
    static constexpr float fxaa_edge_threshold() { return 0.166f; }

private:
    RuntimeConfig& cfg_;
    bool   initialized_             = false;
    bool   close_requested_         = false;
    size_t last_rendered_batches_   = 0;
    size_t last_rendered_triangles_ = 0;
    bool   batches_rendered_this_frame_ = false;

    void ensure_frame_batches_rendered();

#ifdef _WIN32
    bool create_offscreen_efb_and_fxaa(std::string& err_msg);
    void resolve_and_postprocess_to_swapchain();
    void render_overlay_texts_to_swapchain(const GX3DInterface& gx);
    void* get_or_create_texture_srv(const Memory& mem, const GX3DInterface& gx, const GXBoundTexture& tex, const GXTlutSlot& tlut);
    void* get_or_create_text_srv(const std::string& utf8_text, int& out_w, int& out_h);

    void* hwnd_                 = nullptr;
    void* d3d_device_           = nullptr;
    void* d3d_context_          = nullptr;
    void* swap_chain_           = nullptr;
    void* swapchain_rtv_        = nullptr;
    void* efb_color_tex_        = nullptr;
    void* efb_depth_tex_        = nullptr;
    void* efb_resolved_tex_     = nullptr;
    void* efb_resolved_srv_     = nullptr;
    void* msaa_rtv_             = nullptr;
    void* msaa_dsv_             = nullptr;

    // Compiled Shaders, Input Layout, Dynamic Buffers & Pipeline States
    void* vs_                   = nullptr;
    void* ps_                   = nullptr;
    void* fxaa_vs_              = nullptr;
    void* fxaa_ps_              = nullptr;
    void* blit_ps_              = nullptr;
    void* fxaa_cb_              = nullptr;
    void* input_layout_         = nullptr;
    void* dynamic_vb_           = nullptr;
    void* dynamic_ib_           = nullptr;
    void* scene_cb_             = nullptr;
    void* default_white_srv_    = nullptr;
    void* sampler_aniso_        = nullptr;
    void* sampler_linear_clamp_ = nullptr;
    void* samplers_[9]{}; // [wrap_s * 3 + wrap_t] for 0=CLAMP, 1=WRAP, 2=MIRROR
    void* blend_opaque_         = nullptr;
    void* blend_alpha_          = nullptr;
    void* blend_additive_       = nullptr;
    void* dss_depth_rw_         = nullptr;
    void* dss_depth_ro_         = nullptr;
    void* dss_depth_none_       = nullptr;
    void* rs_cull_none_         = nullptr;
    void* rs_cull_front_        = nullptr;
    void* rs_cull_back_         = nullptr;
    void* rs_fullscreen_        = nullptr;

    std::unordered_map<uint64_t, void*>    tex_srv_cache_;
    std::unordered_map<uint64_t, uint64_t> tex_srv_lru_;
    std::unordered_map<std::string, void*> text_srv_cache_;
    std::unordered_map<std::string, uint64_t> text_srv_lru_;
    std::unordered_map<std::string, std::pair<int, int>> text_size_cache_;
    uint64_t cache_lru_tick_ = 0u;
#endif
    uint32_t efb_width_         = 1920u;
    uint32_t efb_height_        = 1080u;
    uint32_t efb_msaa_samples_  = 1u;
    uint32_t swapchain_width_   = 1920u;
    uint32_t swapchain_height_  = 1080u;
    uint32_t last_disp_gamma_   = 0u;
};

} // namespace pn03

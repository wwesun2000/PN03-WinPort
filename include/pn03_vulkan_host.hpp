#pragma once

#include "pn03_config.hpp"
#include "pn03_gx_3d_interface.hpp"
#include "pn03_ppc_context.hpp"
#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace pn03 {

// Real-time Win32 Vulkan 1.3 rendering backend for P.N.03 Windows Native Port.
// Renders GameCube GX 3D/2D draw batches into an internal offscreen EFB (1x..6x + MSAA),
// runs a full-screen FXAA 3.11 + gamma/brightness post-process pass to the swapchain,
// composites crisp GDI UTF-8 Chinese localization overlays, and supports 24-bit BMP capture.
class Win32VulkanHost {
public:
    explicit Win32VulkanHost(RuntimeConfig& cfg);
    ~Win32VulkanHost();

    Win32VulkanHost(const Win32VulkanHost&) = delete;
    Win32VulkanHost& operator=(const Win32VulkanHost&) = delete;

    // Shows pre-launch settings window / Cyber Launcher (or ISO picker if skipped)
    bool show_prelaunch_settings_window();

    // Creates native Win32 window + Vulkan 1.3 instance, device, swapchain, EFB & pipelines
    bool create_render_window_and_vulkan(std::string& err_msg, bool hidden_window = false);
    bool is_initialized() const { return initialized_; }

    // Window & message loop helpers
    bool pump_messages();
    void begin_vulkan_frame(float clear_r = 0.04f, float clear_g = 0.06f, float clear_b = 0.12f);
    void render_gx_draw_batches(const Memory& mem, GX3DInterface& gx);
    void flush_vulkan();
    void end_vulkan_frame_and_present();

    // Captures the most recent swapchain output framebuffer to a 24-bit BMP file
    bool dump_framebuffer_bmp(const std::string& path);

    size_t   last_rendered_batches() const { return last_rendered_batches_; }
    size_t   last_rendered_triangles() const { return last_rendered_triangles_; }
    uint32_t efb_width() const { return efb_width_; }
    uint32_t efb_height() const { return efb_height_; }
    uint32_t efb_msaa_samples() const { return efb_msaa_samples_; }
    const std::string& adapter_name() const { return adapter_name_; }
    uint32_t vulkan_api_version() const { return vk_api_version_; }

    void mark_close_requested() { close_requested_ = true; }
    void handle_window_resize(uint32_t width, uint32_t height);

    static void enable_process_dpi_awareness();
    static constexpr float fxaa_subpix_quality() { return 0.25f; }
    static constexpr float fxaa_edge_threshold() { return 0.166f; }

private:
    RuntimeConfig& cfg_;
    bool           initialized_                 = false;
    bool           close_requested_             = false;
    bool           hidden_window_               = false;
    size_t         last_rendered_batches_       = 0;
    size_t         last_rendered_triangles_     = 0;
    bool           batches_rendered_this_frame_ = false;
    float          pending_clear_color_[4]      = {0.04f, 0.06f, 0.12f, 1.0f};
    std::string    adapter_name_{};
    uint32_t       vk_api_version_              = 0;

    void*    hwnd_             = nullptr;
    uint32_t swapchain_width_  = 1280u;
    uint32_t swapchain_height_ = 720u;
    uint32_t efb_width_        = 640u;
    uint32_t efb_height_       = 480u;
    uint32_t efb_msaa_samples_ = 1u;
    uint32_t last_disp_gamma_  = 0u;

    struct Impl;
    Impl* impl_ = nullptr;

    bool create_swapchain_and_views(std::string& err_msg);
    void destroy_swapchain_and_views();
    bool create_offscreen_efb_and_postprocess(std::string& err_msg);
    void destroy_offscreen_efb();
    bool recreate_swapchain_for_resize(uint32_t width, uint32_t height);
    void submit_empty_clear_frame_if_needed();
    void render_gx_internal(const Memory* mem, GX3DInterface& gx);
};

} // namespace pn03

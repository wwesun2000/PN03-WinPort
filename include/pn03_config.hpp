#pragma once
#include <cstdint>
#include <string>

namespace pn03 {

enum class WindowMode : int {
    Windowed = 0,
    BorderlessFullscreen = 1,
    ExclusiveFullscreen = 2
};

enum class GraphicsBackend : int {
    Direct3D11 = 0,
    OpenGL46   = 1,
    Vulkan13   = 2
};

enum class AntiAliasingMode : int {
    Off     = 0,
    MSAA_2x = 2,
    MSAA_4x = 4,
    MSAA_8x = 8,
    FXAA    = 16
};

enum class AspectRatioMode : int {
    Original_4_3   = 0, // Original 640x480 (4:3)
    Widescreen_16_9 = 1, // 16:9 expanded frustum & ORTHO_L/R
    Ultrawide_21_9  = 2  // 21:9 expanded frustum
};

enum class GameLanguage : int {
    Japanese          = 0,
    English           = 1, // Default hardcoded in US GPNE08
    German            = 2, // /id/ger (*_g.dat)
    French            = 3, // /id/fra (*_f.dat)
    Spanish           = 4, // /id/spa (*_s.dat)
    Italian           = 5, // /id/ita (*_i.dat)
    SimplifiedChinese = 6  // External UTF-8 Chinese Localization Overlay (zh_CN)
};

enum class XboxInputSource : int {
    None      = 0,
    BtnA      = 1,
    BtnB      = 2,
    BtnX      = 3,
    BtnY      = 4,
    BtnLB     = 5,
    BtnRB     = 6,
    TriggerLT = 7,
    TriggerRT = 8,
    BtnBack   = 9,
    BtnStart  = 10,
    BtnGuide  = 11, // Center Xbox [X] Nexus Button (0x0400 via XInputGetStateEx ordinal 100)
    BtnLStick = 12,
    BtnRStick = 13,
    DpadUp    = 14,
    DpadDown  = 15,
    DpadLeft  = 16,
    DpadRight = 17
};

enum class GuideActionTarget : int {
    Disabled = 0,
    GcStart  = 1, // Pause / System Menu
    GcZ      = 2, // Status / Map
    GcY      = 3, // Energy Drive
    GcX      = 4, // Barrier / Palm
    GcL      = 5, // Lock-On / Turn Left
    GcR      = 6, // Quick-Turn / Boost
    GcA      = 7, // Shoot / Confirm
    GcB      = 8  // Dodge / Back
};

struct RuntimeConfig {
    // ISO & Runtime Mode ("mock" for sandbox testing without full 1.35GB ISO, "live" for Windows production)
    std::string      runtime_mode           = "live";
    std::string      iso_path               = "";
    std::string      locale_overlay_path    = "assets/locales/zh_CN.json";
    std::string      save_dir               = "saves";

    // 3D Graphics & Display Settings
    GraphicsBackend  backend                = GraphicsBackend::Direct3D11;
    uint32_t         render_width           = 1920;
    uint32_t         render_height          = 1080;
    uint32_t         internal_scale_factor  = 3; // 3x (1920x1440 EFB -> 1080p)
    WindowMode       window_mode            = WindowMode::BorderlessFullscreen;
    AntiAliasingMode msaa_mode              = AntiAliasingMode::MSAA_4x;
    bool             enable_fxaa            = true;
    uint32_t         anisotropic_filtering  = 16;
    AspectRatioMode  aspect_ratio           = AspectRatioMode::Original_4_3;
    bool             remove_cinesco_bars    = true; // Bypass Draw_cinesco (0x80073348) letterbox
    bool             disable_copy_deflicker = true; // Disable GXSetCopyFilter 480i blur
    bool             vsync                  = true;
    float            brightness             = 1.0f; // 0.50 .. 2.00 display brightness scale
    bool             limit_fps_60           = true; // Dolphin-style QPC 59.94Hz frame limiter

    // Localization Settings
    float            audio_volume           = 1.0f;
    bool             audio_muted            = false;
    GameLanguage     language               = GameLanguage::SimplifiedChinese;
    bool             enable_hd_chinese_font = true;

    // Xbox Controller (XInput) Settings
    bool             enable_xinput          = true;
    int              controller_index       = 0;
    int              control_scheme_preset  = 0; // 0=Type A, 1=Type B, 2=Type C, 3=Type D, 4=Custom
    float            left_stick_deadzone    = 0.15f;
    float            right_stick_deadzone   = 0.15f;
    float            trigger_threshold      = 0.35f;
    bool             enable_vibration       = true;
    float            vibration_strength     = 1.0f;

    // Custom Xbox -> GameCube Button Mappings (XboxInputSource values)
    int              bind_gc_a              = static_cast<int>(XboxInputSource::BtnA);
    int              bind_gc_b              = static_cast<int>(XboxInputSource::BtnB);
    int              bind_gc_x              = static_cast<int>(XboxInputSource::BtnX);
    int              bind_gc_y              = static_cast<int>(XboxInputSource::BtnY);
    int              bind_gc_l              = static_cast<int>(XboxInputSource::TriggerLT);
    int              bind_gc_r              = static_cast<int>(XboxInputSource::TriggerRT);
    int              bind_gc_z              = static_cast<int>(XboxInputSource::BtnRB);
    int              bind_gc_start          = static_cast<int>(XboxInputSource::BtnStart);
    int              bind_guide_target      = static_cast<int>(GuideActionTarget::GcStart);

    // Developer / Module Settings
    bool             load_tools_rel_debug   = false; // Load module/Tools.rel (Sound Test & File Reload)
    bool             skip_launcher_gui      = false;

    // Rotating Debug Log Settings
    std::string      log_dir                = "logs";
    std::string      log_level              = "info"; // trace, debug, info, warn, error, off
    uint32_t         log_max_file_mb        = 4;
    uint32_t         log_max_total_mb       = 16;
    uint32_t         log_max_files          = 12;

    void apply_control_preset(int preset_idx);
    static const char* xbox_input_source_label(int src);
    static const char* guide_action_label(int target);

    bool save_to_json(const std::string& path) const;
    static RuntimeConfig load_from_json(const std::string& path);
};

} // namespace pn03

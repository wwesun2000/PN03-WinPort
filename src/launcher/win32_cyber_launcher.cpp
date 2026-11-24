#include "pn03_cyber_launcher.hpp"
#include "pn03_logger.hpp"
#include "pn03_config.hpp"
#include "pn03_runtime.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <vector>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <objidl.h>
#include <commdlg.h>
#include <dwmapi.h>
#include <gdiplus.h>
#include <xinput.h>
#endif

namespace fs = std::filesystem;

namespace pn03 {

std::string CyberLauncherUI::build_diagnostic_readout(size_t fst_files, size_t total_syms, size_t recomp_funcs) const {
    std::ostringstream ss;
    ss << "DIAGNOSTIC STATUS READOUT: GPNE08 (MEKA) | "
       << "SYMBOLS: " << total_syms << " | "
       << "RECOMP FUNCS: " << recomp_funcs << " | "
       << "FST FILES: " << fst_files << " | "
       << "TARGET: " << cfg_.render_width << "x" << cfg_.render_height
       << " (" << static_cast<int>(cfg_.msaa_mode) << "x MSAA" << (cfg_.enable_fxaa ? "+FXAA" : "") << ")";
    return ss.str();
}

#ifdef _WIN32

namespace {

constexpr int kClientW = 1260;
constexpr int kClientH = 720;
constexpr UINT_PTR kTimerTelemetryId = 101;
constexpr int IDC_EDIT_ISO_PATH = 1001;

struct GdiplusSessionGuard {
    ULONG_PTR token = 0;
    bool active = false;
    GdiplusSessionGuard() {
        Gdiplus::GdiplusStartupInput input{};
        if (Gdiplus::GdiplusStartup(&token, &input, nullptr) == Gdiplus::Ok) {
            active = true;
        }
    }
    ~GdiplusSessionGuard() {
        if (active) {
            Gdiplus::GdiplusShutdown(token);
        }
    }
    GdiplusSessionGuard(const GdiplusSessionGuard&) = delete;
    GdiplusSessionGuard& operator=(const GdiplusSessionGuard&) = delete;
};

static std::wstring utf8_to_wide(const std::string& s) {
    if (s.empty()) return {};
    int needed = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), static_cast<int>(s.size()), nullptr, 0);
    if (needed <= 0) {
        needed = MultiByteToWideChar(CP_ACP, 0, s.c_str(), static_cast<int>(s.size()), nullptr, 0);
        if (needed <= 0) return {};
        std::wstring w(static_cast<size_t>(needed), L'\0');
        MultiByteToWideChar(CP_ACP, 0, s.c_str(), static_cast<int>(s.size()), w.data(), needed);
        return w;
    }
    std::wstring w(static_cast<size_t>(needed), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), static_cast<int>(s.size()), w.data(), needed);
    return w;
}

static std::string wide_to_utf8(const std::wstring& w) {
    if (w.empty()) return {};
    int needed = WideCharToMultiByte(CP_UTF8, 0, w.c_str(), static_cast<int>(w.size()), nullptr, 0, nullptr, nullptr);
    if (needed <= 0) return {};
    std::string s(static_cast<size_t>(needed), '\0');
    WideCharToMultiByte(CP_UTF8, 0, w.c_str(), static_cast<int>(w.size()), s.data(), needed, nullptr, nullptr);
    return s;
}

static std::wstring resolve_ui_asset_path(const std::wstring& rel_name) {
    std::vector<fs::path> bases = {
        fs::current_path(),
        fs::current_path().parent_path(),
        fs::current_path().parent_path().parent_path()
    };
    wchar_t exe_buf[MAX_PATH] = {0};
    if (GetModuleFileNameW(nullptr, exe_buf, MAX_PATH) > 0) {
        fs::path exe_dir = fs::path(exe_buf).parent_path();
        bases.push_back(exe_dir);
        bases.push_back(exe_dir.parent_path());
        bases.push_back(exe_dir.parent_path().parent_path());
    }
    for (const auto& base : bases) {
        fs::path cand = base / L"assets" / L"ui" / rel_name;
        std::error_code ec;
        if (fs::exists(cand, ec)) {
            return cand.wstring();
        }
    }
    return {};
}

static void enable_dark_titlebar(HWND hwnd) {
    HMODULE dwm = GetModuleHandleW(L"dwmapi.dll");
    if (!dwm) dwm = LoadLibraryW(L"dwmapi.dll");
    if (!dwm) return;
    using FnDwmSetAttr = HRESULT(WINAPI*)(HWND, DWORD, LPCVOID, DWORD);
    auto fn = reinterpret_cast<FnDwmSetAttr>(GetProcAddress(dwm, "DwmSetWindowAttribute"));
    if (!fn) return;
    BOOL dark = TRUE;
    fn(hwnd, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
    COLORREF cap = RGB(10, 14, 21);
    fn(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &cap, sizeof(cap));
    COLORREF border = RGB(28, 48, 72);
    fn(hwnd, 34 /* DWMWA_BORDER_COLOR */, &border, sizeof(border));
}

enum HitZoneId : int {
    HZ_NONE = 0,
    HZ_BROWSE_ISO = 1,
    HZ_DD_RESOLUTION = 2,
    HZ_DD_DISPLAY_MODE = 3,
    HZ_DD_ANTIALIASING = 4,
    HZ_DD_ASPECT = 5,
    HZ_DD_ANISO = 6,
    HZ_SW_VSYNC = 7,
    HZ_DD_LANGUAGE = 8,
    HZ_SW_HD_FONT = 9,
    HZ_SW_TOOLS_REL = 10,
    HZ_SW_DEFLICKER = 11,
    HZ_PRESET_A = 12,
    HZ_PRESET_B = 13,
    HZ_PRESET_C = 14,
    HZ_PRESET_D = 15,
    HZ_SLIDER_DEADZONE = 16,
    HZ_SLIDER_RUMBLE = 17,
    HZ_BTN_LAUNCH = 18,
    HZ_BIND_A = 19,
    HZ_BIND_B = 20,
    HZ_BIND_X = 21,
    HZ_BIND_Y = 22,
    HZ_BIND_L = 23,
    HZ_BIND_R = 24,
    HZ_BIND_Z = 25,
    HZ_BIND_START = 26,
    HZ_BIND_GUIDE = 27,
    HZ_SLIDER_BRIGHTNESS = 28,
    HZ_SW_LIMIT_FPS = 29,
    HZ_DD_BACKEND = 30,
    HZ_SW_CHEAT_GOD = 31,
    HZ_SW_CHEAT_ENERGY = 32,
    HZ_SW_CHEAT_CREDITS = 33,
    HZ_SW_CHEAT_SUITS = 34
};

struct HitZone {
    HitZoneId id = HZ_NONE;
    Gdiplus::RectF rect{};
};

struct DropdownChoice {
    std::wstring label;
    int value = 0;
};

struct LauncherUiState {
    RuntimeConfig* cfg = nullptr;
    std::string config_path = "config/pn03_settings.json";
    std::string iso_mount_summary;
    std::string pad_backend_label = "READY";
    std::unique_ptr<Gdiplus::Image> img_crest;
    std::unique_ptr<Gdiplus::Image> img_vanessa;

    HWND hwnd = nullptr;
    HWND edit_iso = nullptr;
    HBRUSH edit_bg_brush = nullptr;
    HFONT edit_font = nullptr;

    float anim_phase = 0.42f;
    bool pad_connected = false;
    float pad_lx = 0.0f;
    float pad_ly = 0.0f;
    float pad_rx = 0.0f;
    float pad_ry = 0.0f;
    WORD pad_buttons = 0;
    float pad_lt = 0.0f;
    float pad_rt = 0.0f;

    HitZoneId hover_id = HZ_NONE;
    HitZoneId dragging_slider = HZ_NONE;
    HitZoneId listening_zone = HZ_NONE;
    WORD listen_prev_buttons = 0;
    bool listen_prev_lt = false;
    bool listen_prev_rt = false;
    std::vector<HitZone> zones;
    std::vector<std::wstring> active_menu_labels;
    bool live_edit_control = false;
    bool launched = false;
    bool closed = false;
};

#ifndef XINPUT_GAMEPAD_GUIDE
#define XINPUT_GAMEPAD_GUIDE 0x0400
#endif

static void save_launcher_state(LauncherUiState& st) {
    if (!st.cfg) return;
    if (st.edit_iso && IsWindow(st.edit_iso)) {
        wchar_t iso_buf[MAX_PATH * 2] = {0};
        GetWindowTextW(st.edit_iso, iso_buf, MAX_PATH * 2);
        std::string typed = wide_to_utf8(iso_buf);
        while (!typed.empty() && (typed.front() == ' ' || typed.front() == '\t' || typed.front() == '"')) {
            typed.erase(0, 1);
        }
        while (!typed.empty() && (typed.back() == ' ' || typed.back() == '\t' || typed.back() == '"')) {
            typed.pop_back();
        }
        st.cfg->iso_path = typed;
    }
    const std::string target = !st.config_path.empty()
        ? st.config_path
        : RuntimeConfig::resolve_config_path();
    st.cfg->save_to_json(target);
}

static WORD pack_xinput_mask_from_state(const XboxInputState& x) {
    WORD w = 0;
    if (x.dpad_up)    w |= XINPUT_GAMEPAD_DPAD_UP;
    if (x.dpad_down)  w |= XINPUT_GAMEPAD_DPAD_DOWN;
    if (x.dpad_left)  w |= XINPUT_GAMEPAD_DPAD_LEFT;
    if (x.dpad_right) w |= XINPUT_GAMEPAD_DPAD_RIGHT;
    if (x.btn_start)  w |= XINPUT_GAMEPAD_START;
    if (x.btn_back)   w |= XINPUT_GAMEPAD_BACK;
    if (x.btn_ls)     w |= XINPUT_GAMEPAD_LEFT_THUMB;
    if (x.btn_rs)     w |= XINPUT_GAMEPAD_RIGHT_THUMB;
    if (x.btn_lb)     w |= XINPUT_GAMEPAD_LEFT_SHOULDER;
    if (x.btn_rb)     w |= XINPUT_GAMEPAD_RIGHT_SHOULDER;
    if (x.btn_guide)  w |= XINPUT_GAMEPAD_GUIDE;
    if (x.btn_a)      w |= XINPUT_GAMEPAD_A;
    if (x.btn_b)      w |= XINPUT_GAMEPAD_B;
    if (x.btn_x)      w |= XINPUT_GAMEPAD_X;
    if (x.btn_y)      w |= XINPUT_GAMEPAD_Y;
    return w;
}

static int* config_bind_ptr_for_zone(RuntimeConfig& cfg, HitZoneId id) {
    switch (id) {
        case HZ_BIND_A:     return &cfg.bind_gc_a;
        case HZ_BIND_B:     return &cfg.bind_gc_b;
        case HZ_BIND_X:     return &cfg.bind_gc_x;
        case HZ_BIND_Y:     return &cfg.bind_gc_y;
        case HZ_BIND_L:     return &cfg.bind_gc_l;
        case HZ_BIND_R:     return &cfg.bind_gc_r;
        case HZ_BIND_Z:     return &cfg.bind_gc_z;
        case HZ_BIND_START: return &cfg.bind_gc_start;
        default:            return nullptr;
    }
}

static const wchar_t* gc_slot_short_name(HitZoneId id) {
    switch (id) {
        case HZ_BIND_A:     return L"GC A";
        case HZ_BIND_B:     return L"GC B";
        case HZ_BIND_X:     return L"GC X";
        case HZ_BIND_Y:     return L"GC Y";
        case HZ_BIND_L:     return L"GC L";
        case HZ_BIND_R:     return L"GC R";
        case HZ_BIND_Z:     return L"GC Z";
        case HZ_BIND_START: return L"START";
        default:            return L"";
    }
}

static int detect_captured_xbox_source(WORD just_pressed, bool lt_edge, bool rt_edge) {
    if (just_pressed & XINPUT_GAMEPAD_A)              return static_cast<int>(XboxInputSource::BtnA);
    if (just_pressed & XINPUT_GAMEPAD_B)              return static_cast<int>(XboxInputSource::BtnB);
    if (just_pressed & XINPUT_GAMEPAD_X)              return static_cast<int>(XboxInputSource::BtnX);
    if (just_pressed & XINPUT_GAMEPAD_Y)              return static_cast<int>(XboxInputSource::BtnY);
    if (just_pressed & XINPUT_GAMEPAD_LEFT_SHOULDER)  return static_cast<int>(XboxInputSource::BtnLB);
    if (just_pressed & XINPUT_GAMEPAD_RIGHT_SHOULDER) return static_cast<int>(XboxInputSource::BtnRB);
    if (lt_edge)                                      return static_cast<int>(XboxInputSource::TriggerLT);
    if (rt_edge)                                      return static_cast<int>(XboxInputSource::TriggerRT);
    if (just_pressed & XINPUT_GAMEPAD_BACK)           return static_cast<int>(XboxInputSource::BtnBack);
    if (just_pressed & XINPUT_GAMEPAD_START)          return static_cast<int>(XboxInputSource::BtnStart);
    if (just_pressed & XINPUT_GAMEPAD_GUIDE)          return static_cast<int>(XboxInputSource::BtnGuide);
    if (just_pressed & XINPUT_GAMEPAD_LEFT_THUMB)     return static_cast<int>(XboxInputSource::BtnLStick);
    if (just_pressed & XINPUT_GAMEPAD_RIGHT_THUMB)    return static_cast<int>(XboxInputSource::BtnRStick);
    if (just_pressed & XINPUT_GAMEPAD_DPAD_UP)        return static_cast<int>(XboxInputSource::DpadUp);
    if (just_pressed & XINPUT_GAMEPAD_DPAD_DOWN)      return static_cast<int>(XboxInputSource::DpadDown);
    if (just_pressed & XINPUT_GAMEPAD_DPAD_LEFT)      return static_cast<int>(XboxInputSource::DpadLeft);
    if (just_pressed & XINPUT_GAMEPAD_DPAD_RIGHT)     return static_cast<int>(XboxInputSource::DpadRight);
    return -1;
}

static std::wstring resolution_label(const RuntimeConfig& cfg) {
    if (cfg.internal_scale_factor <= 1u) {
        if (cfg.render_width >= 1920u) return L"1920x1080 FHD (1x Native EFB)";
        if (cfg.render_width >= 1280u) return L"1280x720 HD (1x Native EFB - iGPU)";
        return L"640x480 480p (1x Native EFB - Fastest)";
    }
    if (cfg.render_width >= 3840u && cfg.internal_scale_factor >= 6u) return L"3840x2160 4K (6x EFB)";
    if (cfg.render_width >= 2560u && cfg.internal_scale_factor >= 4u) return L"2560x1440 QHD (4x EFB)";
    if (cfg.render_width >= 1920u && cfg.internal_scale_factor >= 3u) return L"1920x1080 FHD (3x EFB)";
    return L"1280x720 HD (2x EFB)";
}

static std::wstring display_mode_label(const RuntimeConfig& cfg) {
    switch (cfg.window_mode) {
        case WindowMode::Windowed:             return L"Windowed";
        case WindowMode::ExclusiveFullscreen:  return L"Exclusive Fullscreen";
        case WindowMode::BorderlessFullscreen:
        default:                               return L"Borderless Fullscreen";
    }
}

static std::wstring antialiasing_label(const RuntimeConfig& cfg) {
    if (cfg.msaa_mode == AntiAliasingMode::MSAA_8x) return cfg.enable_fxaa ? L"8x MSAA + FXAA Active" : L"8x MSAA";
    if (cfg.msaa_mode == AntiAliasingMode::MSAA_4x) return cfg.enable_fxaa ? L"4x MSAA + FXAA Active" : L"4x MSAA";
    if (cfg.msaa_mode == AntiAliasingMode::MSAA_2x) return cfg.enable_fxaa ? L"2x MSAA + FXAA Active" : L"2x MSAA";
    if (cfg.msaa_mode == AntiAliasingMode::FXAA || cfg.enable_fxaa) return L"FXAA 3.11 Active";
    return L"Off";
}

static std::wstring aspect_ratio_label(const RuntimeConfig& cfg) {
    switch (cfg.aspect_ratio) {
        case AspectRatioMode::Original_4_3:   return L"4:3 Original (Centered HD)";
        case AspectRatioMode::Ultrawide_21_9: return L"21:9 Ultrawide + No Letterbox";
        case AspectRatioMode::Widescreen_16_9:
        default:                              return L"16:9 Widescreen + No Letterbox";
    }
}

static std::wstring aniso_label(const RuntimeConfig& cfg) {
    if (cfg.anisotropic_filtering >= 16) return L"16x AF";
    if (cfg.anisotropic_filtering >= 8)  return L"8x AF";
    if (cfg.anisotropic_filtering >= 4)  return L"4x AF";
    return L"1x AF";
}

static std::wstring backend_label(const RuntimeConfig& cfg) {
    return (cfg.backend == GraphicsBackend::Vulkan13) ? L"Vulkan 1.3" : L"Direct3D 11";
}

static std::wstring language_label(const RuntimeConfig& cfg) {
    switch (cfg.language) {
        case GameLanguage::SimplifiedChinese: return L"\u7B80\u4F53\u4E2D\u6587 (Simplified Chinese)";
        case GameLanguage::Japanese:          return L"\u65E5\u672C\u8A9E (Japanese)";
        case GameLanguage::German:            return L"Deutsch (/id/ger)";
        case GameLanguage::French:            return L"Fran\u00E7ais (/id/fra)";
        case GameLanguage::Spanish:           return L"Espa\u00F1ol (/id/spa)";
        case GameLanguage::Italian:           return L"Italiano (/id/ita)";
        case GameLanguage::English:
        default:                              return L"English (US Default)";
    }
}

static void add_chamfer_rect(Gdiplus::GraphicsPath& path, const Gdiplus::RectF& r, float cut_tl, float cut_tr, float cut_br, float cut_bl) {
    path.Reset();
    path.AddLine(r.X + cut_tl, r.Y, r.GetRight() - cut_tr, r.Y);
    if (cut_tr > 0.0f) path.AddLine(r.GetRight() - cut_tr, r.Y, r.GetRight(), r.Y + cut_tr);
    path.AddLine(r.GetRight(), r.Y + cut_tr, r.GetRight(), r.GetBottom() - cut_br);
    if (cut_br > 0.0f) path.AddLine(r.GetRight(), r.GetBottom() - cut_br, r.GetRight() - cut_br, r.GetBottom());
    path.AddLine(r.GetRight() - cut_br, r.GetBottom(), r.X + cut_bl, r.GetBottom());
    if (cut_bl > 0.0f) path.AddLine(r.X + cut_bl, r.GetBottom(), r.X, r.GetBottom() - cut_bl);
    path.AddLine(r.X, r.GetBottom() - cut_bl, r.X, r.Y + cut_tl);
    if (cut_tl > 0.0f) path.AddLine(r.X, r.Y + cut_tl, r.X + cut_tl, r.Y);
    path.CloseFigure();
}

static void add_round_rect(Gdiplus::GraphicsPath& path, const Gdiplus::RectF& r, float rad) {
    path.Reset();
    float d = rad * 2.0f;
    path.AddArc(r.X, r.Y, d, d, 180.0f, 90.0f);
    path.AddArc(r.GetRight() - d, r.Y, d, d, 270.0f, 90.0f);
    path.AddArc(r.GetRight() - d, r.GetBottom() - d, d, d, 0.0f, 90.0f);
    path.AddArc(r.X, r.GetBottom() - d, d, d, 90.0f, 90.0f);
    path.CloseFigure();
}

static void draw_led_pair(Gdiplus::Graphics& g, float right_x, float y, bool left_on, bool right_on, bool cyan_mode = false) {
    Gdiplus::Color on_col  = cyan_mode ? Gdiplus::Color(255, 0, 229, 255) : Gdiplus::Color(255, 255, 118, 24);
    Gdiplus::Color off_col = cyan_mode ? Gdiplus::Color(255, 16, 48, 60)  : Gdiplus::Color(255, 68, 34, 14);
    Gdiplus::Color glow_col = cyan_mode ? Gdiplus::Color(90, 0, 229, 255) : Gdiplus::Color(90, 255, 118, 24);

    for (int i = 0; i < 2; ++i) {
        bool on = (i == 0) ? left_on : right_on;
        float px = right_x - (2 - i) * 20.0f + 4.0f;
        Gdiplus::RectF rc(px, y, 15.0f, 6.0f);
        if (on) {
            Gdiplus::SolidBrush gb(glow_col);
            g.FillRectangle(&gb, px - 2.0f, y - 2.0f, 19.0f, 10.0f);
        }
        Gdiplus::SolidBrush b(on ? on_col : off_col);
        g.FillRectangle(&b, rc);
    }
}

static void draw_cyber_dropdown(Gdiplus::Graphics& g, LauncherUiState& st, HitZoneId id,
                                float x, float y, float w, const std::wstring& title,
                                const std::wstring& value_text, int leds_on,
                                const Gdiplus::Font& lbl_font, const Gdiplus::Font& val_font,
                                bool accent_cyan = false) {
    Gdiplus::SolidBrush lbl_br(Gdiplus::Color(255, 196, 214, 232));
    g.DrawString(title.c_str(), -1, &lbl_font, Gdiplus::PointF(x, y), &lbl_br);

    if (leds_on >= 0) {
        draw_led_pair(g, x + w, y + 5.0f, leds_on >= 1, leds_on >= 2, false);
    }

    Gdiplus::RectF pill(x, y + 20.0f, w, 31.0f);
    st.zones.push_back({id, pill});
    bool hovered = (st.hover_id == id);

    Gdiplus::GraphicsPath p;
    add_chamfer_rect(p, pill, 0.0f, 6.0f, 0.0f, 6.0f);

    Gdiplus::LinearGradientBrush bg(
        Gdiplus::PointF(pill.X, pill.Y), Gdiplus::PointF(pill.X, pill.GetBottom()),
        hovered ? Gdiplus::Color(245, 22, 36, 52) : Gdiplus::Color(240, 11, 18, 27),
        Gdiplus::Color(240, 8, 13, 20));
    g.FillPath(&bg, &p);

    Gdiplus::Color border_c = (hovered || accent_cyan)
        ? Gdiplus::Color(hovered ? 245 : 185, 0, 229, 255)
        : Gdiplus::Color(220, 56, 78, 104);
    Gdiplus::Pen border_pen(border_c, (hovered || accent_cyan) ? 1.35f : 1.0f);
    g.DrawPath(&border_pen, &p);

    if (accent_cyan || hovered) {
        Gdiplus::SolidBrush left_bar(Gdiplus::Color(255, 0, 229, 255));
        g.FillRectangle(&left_bar, pill.X + 1.0f, pill.Y + 4.0f, 2.5f, pill.Height - 8.0f);
    }

    Gdiplus::StringFormat sf;
    sf.SetAlignment(Gdiplus::StringAlignmentNear);
    sf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
    sf.SetTrimming(Gdiplus::StringTrimmingEllipsisCharacter);
    sf.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);

    Gdiplus::RectF text_rc(pill.X + 10.0f, pill.Y, pill.Width - 36.0f, pill.Height);
    Gdiplus::SolidBrush txt_br((accent_cyan || hovered)
        ? Gdiplus::Color(255, 175, 246, 255)
        : Gdiplus::Color(255, 232, 241, 250));
    g.DrawString(value_text.c_str(), -1, &val_font, text_rc, &sf, &txt_br);

    // Crisp chevron arrow on right
    float cx = pill.GetRight() - 16.0f;
    float cy = pill.Y + pill.Height * 0.5f - 2.0f;
    Gdiplus::Pen chev_pen(hovered ? Gdiplus::Color(255, 0, 229, 255) : Gdiplus::Color(255, 146, 174, 202), 1.6f);
    g.DrawLine(&chev_pen, cx - 4.5f, cy, cx, cy + 4.5f);
    g.DrawLine(&chev_pen, cx, cy + 4.5f, cx + 4.5f, cy);
}

static void draw_cyber_switch_row(Gdiplus::Graphics& g, LauncherUiState& st, HitZoneId id,
                                  float x, float y, float w, const std::wstring& label,
                                  bool on, bool orange_accent, const Gdiplus::Font& lbl_font,
                                  const Gdiplus::Font& small_font) {
    Gdiplus::RectF row_rc(x, y, w, 34.0f);
    bool hovered = (st.hover_id == id);

    Gdiplus::GraphicsPath row_bg;
    add_round_rect(row_bg, row_rc, 4.0f);
    Gdiplus::SolidBrush bg_br(hovered ? Gdiplus::Color(180, 20, 32, 46) : Gdiplus::Color(135, 11, 18, 27));
    g.FillPath(&bg_br, &row_bg);
    Gdiplus::Pen row_pen(hovered ? Gdiplus::Color(180, 0, 229, 255) : Gdiplus::Color(130, 44, 62, 84), 1.0f);
    g.DrawPath(&row_pen, &row_bg);

    Gdiplus::StringFormat sf;
    sf.SetAlignment(Gdiplus::StringAlignmentNear);
    sf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
    sf.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);
    Gdiplus::RectF txt_rc(x + 10.0f, y, w - 72.0f, 34.0f);
    Gdiplus::SolidBrush txt_br(Gdiplus::Color(255, 212, 226, 240));
    g.DrawString(label.c_str(), -1, &lbl_font, txt_rc, &sf, &txt_br);

    Gdiplus::RectF sw_rc(x + w - 58.0f, y + 6.0f, 50.0f, 22.0f);
    st.zones.push_back({id, row_rc});

    Gdiplus::Color accent = orange_accent ? Gdiplus::Color(255, 255, 128, 30) : Gdiplus::Color(255, 0, 229, 255);
    Gdiplus::Color fill_c = on
        ? (orange_accent ? Gdiplus::Color(70, 255, 118, 24) : Gdiplus::Color(65, 0, 229, 255))
        : Gdiplus::Color(240, 22, 32, 46);
    Gdiplus::GraphicsPath sw_p;
    add_round_rect(sw_p, sw_rc, 11.0f);
    Gdiplus::SolidBrush sw_fill(fill_c);
    g.FillPath(&sw_fill, &sw_p);
    Gdiplus::Pen sw_pen(on ? accent : Gdiplus::Color(200, 65, 86, 112), 1.2f);
    g.DrawPath(&sw_pen, &sw_p);

    float knob_x = on ? (sw_rc.GetRight() - 19.0f) : (sw_rc.X + 3.0f);
    Gdiplus::SolidBrush knob_br(on ? accent : Gdiplus::Color(255, 130, 152, 178));
    g.FillEllipse(&knob_br, knob_x, sw_rc.Y + 3.0f, 16.0f, 16.0f);

    Gdiplus::StringFormat ssf;
    ssf.SetAlignment(Gdiplus::StringAlignmentCenter);
    ssf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
    Gdiplus::RectF st_rc(on ? sw_rc.X + 3.0f : sw_rc.X + 18.0f, sw_rc.Y, 28.0f, sw_rc.Height);
    Gdiplus::SolidBrush st_br(on ? accent : Gdiplus::Color(255, 130, 152, 178));
    g.DrawString(on ? L"ON" : L"OFF", -1, &small_font, st_rc, &ssf, &st_br);
}

static void draw_cyber_slider(Gdiplus::Graphics& g, LauncherUiState& st, HitZoneId id,
                              float x, float y, float w, const std::wstring& title,
                              float norm_t, const std::wstring& val_label, bool orange_mode,
                              const Gdiplus::Font& lbl_font, const Gdiplus::Font& mono_font) {
    norm_t = (std::max)(0.0f, (std::min)(1.0f, norm_t));
    Gdiplus::SolidBrush lbl_br(Gdiplus::Color(255, 198, 216, 234));
    g.DrawString(title.c_str(), -1, &lbl_font, Gdiplus::PointF(x, y), &lbl_br);

    Gdiplus::StringFormat rsf;
    rsf.SetAlignment(Gdiplus::StringAlignmentFar);
    Gdiplus::SolidBrush val_br(orange_mode ? Gdiplus::Color(255, 255, 148, 56) : Gdiplus::Color(255, 0, 229, 255));
    g.DrawString(val_label.c_str(), -1, &mono_font, Gdiplus::RectF(x, y, w, 18.0f), &rsf, &val_br);

    Gdiplus::RectF track_hit(x, y + 18.0f, w, 24.0f);
    st.zones.push_back({id, track_hit});

    float ty = y + 29.0f;
    float tw = w - 6.0f;
    float tx = x + 3.0f;

    Gdiplus::GraphicsPath base_p;
    add_round_rect(base_p, Gdiplus::RectF(tx, ty - 3.0f, tw, 6.0f), 3.0f);
    Gdiplus::SolidBrush base_br(Gdiplus::Color(255, 22, 34, 48));
    g.FillPath(&base_br, &base_p);

    float fill_w = (std::max)(6.0f, tw * norm_t);
    if (norm_t > 0.01f) {
        Gdiplus::GraphicsPath fill_p;
        add_round_rect(fill_p, Gdiplus::RectF(tx, ty - 3.0f, fill_w, 6.0f), 3.0f);
        Gdiplus::LinearGradientBrush fill_br(
            Gdiplus::PointF(tx, ty), Gdiplus::PointF(tx + tw, ty),
            orange_mode ? Gdiplus::Color(255, 255, 109, 0) : Gdiplus::Color(255, 0, 165, 210),
            orange_mode ? Gdiplus::Color(255, 255, 185, 64) : Gdiplus::Color(255, 0, 229, 255));
        g.FillPath(&fill_br, &fill_p);
    }

    float kx = tx + tw * norm_t;
    bool active = (st.hover_id == id || st.dragging_slider == id);
    Gdiplus::Color kc = orange_mode ? Gdiplus::Color(255, 255, 140, 40) : Gdiplus::Color(255, 0, 229, 255);
    if (active) {
        Gdiplus::SolidBrush glow(Gdiplus::Color(80, kc.GetR(), kc.GetG(), kc.GetB()));
        g.FillEllipse(&glow, kx - 11.0f, ty - 11.0f, 22.0f, 22.0f);
    }
    Gdiplus::SolidBrush kfill(Gdiplus::Color(255, 14, 22, 32));
    g.FillEllipse(&kfill, kx - 7.0f, ty - 7.0f, 14.0f, 14.0f);
    Gdiplus::Pen kpen(kc, 2.0f);
    g.DrawEllipse(&kpen, kx - 7.0f, ty - 7.0f, 14.0f, 14.0f);
}

static void draw_card_shell(Gdiplus::Graphics& g, float x, float y, float w, float h,
                            const std::wstring& header_title, bool left_led, bool right_led,
                            bool cyan_led, const Gdiplus::Font& hdr_font) {
    Gdiplus::RectF card_rc(x, y, w, h);
    Gdiplus::GraphicsPath card_p;
    add_chamfer_rect(card_p, card_rc, 14.0f, 0.0f, 14.0f, 0.0f);

    Gdiplus::LinearGradientBrush card_bg(
        Gdiplus::PointF(x, y), Gdiplus::PointF(x, y + h),
        Gdiplus::Color(238, 16, 23, 34),
        Gdiplus::Color(242, 10, 15, 23));
    g.FillPath(&card_bg, &card_p);

    // Header band inside card clip
    g.SetClip(&card_p);
    Gdiplus::LinearGradientBrush hdr_bg(
        Gdiplus::PointF(x, y), Gdiplus::PointF(x + w, y),
        Gdiplus::Color(245, 34, 48, 66),
        Gdiplus::Color(230, 17, 25, 36));
    g.FillRectangle(&hdr_bg, x, y, w, 36.0f);
    Gdiplus::Pen hdr_sep(Gdiplus::Color(175, 0, 229, 255), 1.0f);
    g.DrawLine(&hdr_sep, x, y + 36.0f, x + w, y + 36.0f);
    g.ResetClip();

    // Card border + cyan corner L-accents
    Gdiplus::Pen border_pen(Gdiplus::Color(220, 48, 68, 92), 1.2f);
    g.DrawPath(&border_pen, &card_p);

    Gdiplus::Pen corner_pen(Gdiplus::Color(220, 0, 229, 255), 1.8f);
    g.DrawLine(&corner_pen, x + 14.0f, y, x + 38.0f, y);
    g.DrawLine(&corner_pen, x, y + 14.0f, x, y + 36.0f);
    g.DrawLine(&corner_pen, x + w - 38.0f, y + h, x + w - 14.0f, y + h);
    g.DrawLine(&corner_pen, x + w, y + h - 36.0f, x + w, y + h - 14.0f);

    // Small hex badge beside title
    float hx = x + 22.0f;
    float hy = y + 18.0f;
    Gdiplus::PointF hex[6];
    for (int i = 0; i < 6; ++i) {
        float ang = static_cast<float>(i) * 1.04719755f;
        hex[i] = Gdiplus::PointF(hx + 6.5f * std::cos(ang), hy + 6.5f * std::sin(ang));
    }
    Gdiplus::SolidBrush hex_fill(Gdiplus::Color(60, 0, 229, 255));
    g.FillPolygon(&hex_fill, hex, 6);
    Gdiplus::Pen hex_pen(Gdiplus::Color(255, 0, 229, 255), 1.3f);
    g.DrawPolygon(&hex_pen, hex, 6);

    Gdiplus::StringFormat sf;
    sf.SetAlignment(Gdiplus::StringAlignmentNear);
    sf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
    Gdiplus::SolidBrush hdr_txt(Gdiplus::Color(255, 240, 247, 255));
    g.DrawString(header_title.c_str(), -1, &hdr_font, Gdiplus::RectF(x + 36.0f, y, w - 92.0f, 36.0f), &sf, &hdr_txt);

    draw_led_pair(g, x + w - 12.0f, y + 15.0f, left_led, right_led, cyan_led);
}

static void draw_oscilloscope_box(Gdiplus::Graphics& g, const LauncherUiState& st,
                                  float x, float y, float w, float h,
                                  const Gdiplus::Font& tiny_font, const Gdiplus::Font& mono_font) {
    Gdiplus::RectF box(x, y, w, h);
    Gdiplus::GraphicsPath bp;
    add_chamfer_rect(bp, box, 6.0f, 0.0f, 6.0f, 0.0f);
    Gdiplus::SolidBrush bg(Gdiplus::Color(245, 7, 12, 19));
    g.FillPath(&bg, &bp);
    Gdiplus::Pen bpen(Gdiplus::Color(210, 34, 62, 86), 1.0f);
    g.DrawPath(&bpen, &bp);

    // Header row inside oscilloscope
    Gdiplus::SolidBrush hdr_bg(Gdiplus::Color(210, 12, 22, 34));
    g.FillRectangle(&hdr_bg, x + 1.0f, y + 1.0f, w - 2.0f, 22.0f);

    Gdiplus::StringFormat lsf;
    lsf.SetAlignment(Gdiplus::StringAlignmentNear);
    lsf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
    Gdiplus::SolidBrush cyan_br(Gdiplus::Color(255, 0, 229, 255));
    g.DrawString(L"MINI LIVE TELEMETRY OSCILLOSCOPE:", -1, &tiny_font, Gdiplus::RectF(x + 8.0f, y + 1.0f, 225.0f, 22.0f), &lsf, &cyan_br);

    std::wstring ortho = L"ORTHO: [-106.7..746.7]";
    if (st.cfg->aspect_ratio == AspectRatioMode::Original_4_3) ortho = L"ORTHO: [0.0..640.0]";
    else if (st.cfg->aspect_ratio == AspectRatioMode::Ultrawide_21_9) ortho = L"ORTHO: [-240.0..880.0]";

    Gdiplus::StringFormat rsf;
    rsf.SetAlignment(Gdiplus::StringAlignmentFar);
    rsf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
    Gdiplus::SolidBrush mute_br(Gdiplus::Color(255, 152, 186, 212));
    g.DrawString(ortho.c_str(), -1, &tiny_font, Gdiplus::RectF(x + w - 160.0f, y + 1.0f, 152.0f, 22.0f), &rsf, &mute_br);

    // CRT plot area
    float px = x + 6.0f;
    float py = y + 26.0f;
    float pw = w - 12.0f;
    float ph = h - 50.0f;
    g.SetClip(Gdiplus::RectF(px, py, pw, ph));

    Gdiplus::Pen grid_pen(Gdiplus::Color(34, 0, 229, 255), 1.0f);
    for (float gx = px; gx < px + pw; gx += 22.0f) g.DrawLine(&grid_pen, gx, py, gx, py + ph);
    for (float gy = py; gy < py + ph; gy += 20.0f) g.DrawLine(&grid_pen, px, gy, px + pw, gy);

    // Center AEGIS reticle diamond + outer ring
    const float scale_y = (std::min)(1.0f, ph / 110.0f);
    float rcx = px + pw * 0.5f;
    float rcy = py + ph * 0.5f;
    const float r_out = 38.0f * scale_y;
    const float r_in  = 24.0f * scale_y;
    const float r_dia = 30.0f * scale_y;
    Gdiplus::Pen ring_pen(Gdiplus::Color(70, 0, 229, 255), 1.2f);
    g.DrawEllipse(&ring_pen, rcx - r_out, rcy - r_out, r_out * 2.0f, r_out * 2.0f);
    g.DrawEllipse(&ring_pen, rcx - r_in,  rcy - r_in,  r_in  * 2.0f, r_in  * 2.0f);
    float rot = st.anim_phase * 0.8f;
    Gdiplus::PointF dia[4];
    for (int k = 0; k < 4; ++k) {
        float a = rot + static_cast<float>(k) * 1.5707963f;
        dia[k] = Gdiplus::PointF(rcx + r_dia * std::cos(a), rcy + r_dia * std::sin(a));
    }
    Gdiplus::Pen dia_pen(Gdiplus::Color(130, 0, 229, 255), 1.4f);
    g.DrawPolygon(&dia_pen, dia, 4);

    // Dual oscilloscope waveforms (Cyan GX pipeline pulse + Amber ADPCM audio harmonic)
    constexpr int kSamples = 72;
    std::array<Gdiplus::PointF, kSamples> wave_cyan{};
    std::array<Gdiplus::PointF, kSamples> wave_amber{};
    for (int i = 0; i < kSamples; ++i) {
        float u = static_cast<float>(i) / static_cast<float>(kSamples - 1);
        float sx = px + u * pw;
        float env = std::sin(u * 3.1415926f);
        float cy_off = (std::sin(u * 14.0f + st.anim_phase * 3.0f) * 26.0f * env
                      + std::cos(u * 29.0f - st.anim_phase * 4.5f) * 8.0f * env) * scale_y;
        float am_off = (std::cos(u * 11.0f - st.anim_phase * 2.4f) * 18.0f * env
                      + std::sin(u * 23.0f + st.anim_phase * 3.8f) * 6.0f) * scale_y;
        wave_cyan[static_cast<size_t>(i)]  = Gdiplus::PointF(sx, rcy + cy_off);
        wave_amber[static_cast<size_t>(i)] = Gdiplus::PointF(sx, rcy + am_off * 0.72f);
    }
    Gdiplus::Pen am_pen(Gdiplus::Color(150, 255, 130, 32), 1.4f);
    Gdiplus::Pen cy_glow(Gdiplus::Color(70, 0, 229, 255), 4.5f);
    Gdiplus::Pen cy_pen(Gdiplus::Color(245, 0, 229, 255), 1.8f);
    g.DrawLines(&am_pen, wave_amber.data(), kSamples);
    g.DrawLines(&cy_glow, wave_cyan.data(), kSamples);
    g.DrawLines(&cy_pen, wave_cyan.data(), kSamples);
    g.ResetClip();

    // Footer status strip
    std::wostringstream foot;
    foot << L"TEV: 16-STAGE | EFB: " << st.cfg->internal_scale_factor << L"x | FXAA: "
         << (st.cfg->enable_fxaa ? L"ON" : L"OFF");
    Gdiplus::SolidBrush foot_br(Gdiplus::Color(255, 128, 170, 200));
    g.DrawString(foot.str().c_str(), -1, &mono_font, Gdiplus::RectF(x + 8.0f, y + h - 22.0f, w - 16.0f, 18.0f), &lsf, &foot_br);
}

static void draw_cyber_cheat_pill(Gdiplus::Graphics& g, LauncherUiState& st, HitZoneId id,
                                  float x, float y, float w, float h,
                                  const std::wstring& label, bool enabled,
                                  const Gdiplus::Font& tiny_font) {
    Gdiplus::RectF rc(x, y, w, h);
    st.zones.push_back({id, rc});
    const bool hov = (st.hover_id == id);

    Gdiplus::GraphicsPath p;
    add_round_rect(p, rc, 4.0f);
    Gdiplus::SolidBrush bg(enabled
        ? Gdiplus::Color(225, 48, 28, 12)
        : (hov ? Gdiplus::Color(235, 20, 36, 54) : Gdiplus::Color(225, 11, 18, 28)));
    g.FillPath(&bg, &p);
    Gdiplus::Pen pen(enabled
        ? Gdiplus::Color(255, 255, 156, 36)
        : (hov ? Gdiplus::Color(255, 0, 229, 255) : Gdiplus::Color(200, 44, 68, 94)),
        (enabled || hov) ? 1.4f : 1.0f);
    g.DrawPath(&pen, &p);

    Gdiplus::StringFormat lsf, rsf;
    lsf.SetAlignment(Gdiplus::StringAlignmentNear);
    lsf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
    lsf.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);
    rsf.SetAlignment(Gdiplus::StringAlignmentFar);
    rsf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
    rsf.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);

    Gdiplus::SolidBrush lbl_br(enabled ? Gdiplus::Color(255, 255, 234, 196) : Gdiplus::Color(255, 208, 222, 238));
    Gdiplus::SolidBrush val_br(enabled ? Gdiplus::Color(255, 255, 168, 42) : Gdiplus::Color(255, 120, 144, 170));
    g.DrawString(label.c_str(), -1, &tiny_font, Gdiplus::RectF(x + 8.0f, y, w - 42.0f, h), &lsf, &lbl_br);
    g.DrawString(enabled ? L"ON" : L"OFF", -1, &tiny_font, Gdiplus::RectF(x + w - 38.0f, y, 30.0f, h), &rsf, &val_br);
}

static void draw_xbox_wireframe(Gdiplus::Graphics& g, const LauncherUiState& st,
                                float x, float y, float w, float h,
                                const Gdiplus::Font& tiny_font, const Gdiplus::Font& btn_font) {
    Gdiplus::RectF box(x, y, w, h);
    Gdiplus::GraphicsPath bp;
    add_chamfer_rect(bp, box, 6.0f, 0.0f, 6.0f, 0.0f);
    Gdiplus::SolidBrush bg(Gdiplus::Color(235, 7, 13, 21));
    g.FillPath(&bg, &bp);
    Gdiplus::Pen bpen(Gdiplus::Color(200, 32, 56, 80), 1.0f);
    g.DrawPath(&bpen, &bp);

    // Top telemetry strip inside controller diagram box
    std::wostringstream hdr;
    if (st.cfg->control_scheme_preset >= 0 && st.cfg->control_scheme_preset <= 3) {
        wchar_t preset_ch = static_cast<wchar_t>(L'A' + st.cfg->control_scheme_preset);
        hdr << L"PAD // PRESET " << preset_ch;
    } else {
        hdr << L"PAD // CUSTOM REMAP";
    }
    Gdiplus::StringFormat lsf;
    lsf.SetAlignment(Gdiplus::StringAlignmentNear);
    Gdiplus::SolidBrush cy_txt(Gdiplus::Color(255, 146, 182, 210));
    g.DrawString(hdr.str().c_str(), -1, &tiny_font, Gdiplus::RectF(x + 8.0f, y + 4.0f, w - 150.0f, 15.0f), &lsf, &cy_txt);

    Gdiplus::StringFormat rsf;
    rsf.SetAlignment(Gdiplus::StringAlignmentFar);
    Gdiplus::SolidBrush st_txt(st.pad_connected ? Gdiplus::Color(255, 88, 255, 164) : Gdiplus::Color(255, 0, 229, 255));
    std::wstring st_msg = st.pad_connected ? (L"ACTIVE: " + utf8_to_wide(st.pad_backend_label)) : L"READY (SDL/XI/DI8)";
    g.DrawString(st_msg.c_str(), -1, &tiny_font, Gdiplus::RectF(x + w - 168.0f, y + 4.0f, 160.0f, 15.0f), &rsf, &st_txt);

    // Coordinate transform from 260x155 SVG space to compact diagram center
    const float sc = 0.78f;
    const float ox = x + (w - 260.0f * sc) * 0.5f;
    const float oy = y + 18.0f;
    auto pt = [&](float sx, float sy) -> Gdiplus::PointF {
        return Gdiplus::PointF(ox + sx * sc, oy + sy * sc);
    };

    // Contoured Xbox controller silhouette via smooth closed curve / bezier segments
    Gdiplus::GraphicsPath shell;
    shell.StartFigure();
    shell.AddBezier(pt(65, 28), pt(100, 18), pt(160, 18), pt(195, 28));
    shell.AddBezier(pt(195, 28), pt(226, 36), pt(244, 78), pt(236, 122));
    shell.AddBezier(pt(236, 122), pt(231, 144), pt(210, 146), pt(194, 126));
    shell.AddLine(pt(194, 126), pt(175, 104));
    shell.AddBezier(pt(175, 104), pt(150, 99), pt(110, 99), pt(85, 104));
    shell.AddLine(pt(85, 104), pt(66, 126));
    shell.AddBezier(pt(66, 126), pt(50, 146), pt(29, 144), pt(24, 122));
    shell.AddBezier(pt(24, 122), pt(16, 78), pt(34, 36), pt(65, 28));
    shell.CloseFigure();

    Gdiplus::LinearGradientBrush shell_fill(
        Gdiplus::PointF(x, oy + 20.0f), Gdiplus::PointF(x, oy + 145.0f * sc),
        Gdiplus::Color(220, 22, 34, 52),
        Gdiplus::Color(235, 11, 18, 28));
    g.FillPath(&shell_fill, &shell);

    Gdiplus::Pen shell_glow(Gdiplus::Color(60, 0, 229, 255), 4.0f);
    Gdiplus::Pen shell_pen(Gdiplus::Color(235, 86, 128, 168), 1.6f);
    g.DrawPath(&shell_glow, &shell);
    g.DrawPath(&shell_pen, &shell);

    // Shoulder bumpers / triggers LT/RT
    Gdiplus::Pen trig_pen(Gdiplus::Color(210, 0, 229, 255), 1.5f);
    g.DrawArc(&trig_pen, ox + 52 * sc, oy + 12 * sc, 36 * sc, 16 * sc, 195.0f, 150.0f);
    g.DrawArc(&trig_pen, ox + 172 * sc, oy + 12 * sc, 36 * sc, 16 * sc, 195.0f, 150.0f);

    // Internal wireframe circuit ribs
    Gdiplus::Pen rib_pen(Gdiplus::Color(70, 0, 229, 255), 1.0f);
    g.DrawLine(&rib_pen, pt(85, 104), pt(96, 36));
    g.DrawLine(&rib_pen, pt(175, 104), pt(164, 36));
    g.DrawBezier(&rib_pen, pt(50, 62), pt(105, 76), pt(155, 76), pt(210, 62));

    // Xbox Guide Nexus Button (Center [X]) - active telemetry highlight + clickable target
    Gdiplus::PointF gp = pt(130, 44);
    bool guide_down = (st.pad_buttons & XINPUT_GAMEPAD_GUIDE) != 0;
    Gdiplus::SolidBrush gp_fill(guide_down ? Gdiplus::Color(230, 255, 148, 36) : Gdiplus::Color(115, 0, 229, 255));
    g.FillEllipse(&gp_fill, gp.X - 9.0f * sc, gp.Y - 9.0f * sc, 18.0f * sc, 18.0f * sc);
    Gdiplus::Pen gp_pen(guide_down ? Gdiplus::Color(255, 255, 230, 180) : Gdiplus::Color(245, 210, 232, 250), 1.5f);
    g.DrawEllipse(&gp_pen, gp.X - 9.0f * sc, gp.Y - 9.0f * sc, 18.0f * sc, 18.0f * sc);
    g.DrawLine(&gp_pen, gp.X - 3.5f, gp.Y - 3.5f, gp.X + 3.5f, gp.Y + 3.5f);
    g.DrawLine(&gp_pen, gp.X + 3.5f, gp.Y - 3.5f, gp.X - 3.5f, gp.Y + 3.5f);

    // Small View (Back) & Menu (Start) micro-buttons on wireframe
    auto draw_micro_btn = [&](Gdiplus::PointF cp, WORD mask) {
        bool down = (st.pad_buttons & mask) != 0;
        Gdiplus::SolidBrush mf(down ? Gdiplus::Color(220, 0, 229, 255) : Gdiplus::Color(190, 24, 38, 56));
        Gdiplus::Pen mp(Gdiplus::Color(230, 128, 172, 210), 1.1f);
        g.FillEllipse(&mf, cp.X - 4.0f, cp.Y - 4.0f, 8.0f, 8.0f);
        g.DrawEllipse(&mp, cp.X - 4.0f, cp.Y - 4.0f, 8.0f, 8.0f);
    };
    draw_micro_btn(pt(109, 58), XINPUT_GAMEPAD_BACK);
    draw_micro_btn(pt(151, 58), XINPUT_GAMEPAD_START);

    // Left Stick + axis callout
    Gdiplus::PointF ls = pt(74, 62);
    Gdiplus::SolidBrush stick_bg(Gdiplus::Color(45, 0, 229, 255));
    Gdiplus::Pen stick_ring(Gdiplus::Color(245, 0, 229, 255), 1.5f);
    g.FillEllipse(&stick_bg, ls.X - 14.0f * sc, ls.Y - 14.0f * sc, 28.0f * sc, 28.0f * sc);
    g.DrawEllipse(&stick_ring, ls.X - 14.0f * sc, ls.Y - 14.0f * sc, 28.0f * sc, 28.0f * sc);
    Gdiplus::PointF ls_knob(ls.X + st.pad_lx * 5.0f, ls.Y - st.pad_ly * 5.0f);
    Gdiplus::SolidBrush stick_cap(Gdiplus::Color(255, 0, 229, 255));
    g.FillEllipse(&stick_cap, ls_knob.X - 6.5f * sc, ls_knob.Y - 6.5f * sc, 13.0f * sc, 13.0f * sc);
    Gdiplus::Pen call_pen(Gdiplus::Color(165, 0, 229, 255), 1.0f);
    g.DrawLine(&call_pen, ls.X - 14.0f * sc, ls.Y, x + 52.0f, ls.Y);

    // D-Pad Cross
    Gdiplus::PointF dpad_pts[12] = {
        pt(96, 80), pt(106, 80), pt(106, 90), pt(116, 90),
        pt(116, 100), pt(106, 100), pt(106, 110), pt(96, 110),
        pt(96, 100), pt(86, 100), pt(86, 90), pt(96, 90)
    };
    Gdiplus::SolidBrush dp_fill(Gdiplus::Color(220, 12, 20, 32));
    Gdiplus::Pen dp_pen(Gdiplus::Color(230, 138, 168, 202), 1.2f);
    g.FillPolygon(&dp_fill, dpad_pts, 12);
    g.DrawPolygon(&dp_pen, dpad_pts, 12);

    // Right C-Stick + callout
    Gdiplus::PointF rs = pt(158, 94);
    g.FillEllipse(&stick_bg, rs.X - 13.0f * sc, rs.Y - 13.0f * sc, 26.0f * sc, 26.0f * sc);
    g.DrawEllipse(&stick_ring, rs.X - 13.0f * sc, rs.Y - 13.0f * sc, 26.0f * sc, 26.0f * sc);
    Gdiplus::PointF rs_knob(rs.X + st.pad_rx * 5.0f, rs.Y - st.pad_ry * 5.0f);
    g.FillEllipse(&stick_cap, rs_knob.X - 6.0f * sc, rs_knob.Y - 6.0f * sc, 12.0f * sc, 12.0f * sc);
    g.DrawLine(&call_pen, rs.X + 13.0f * sc, rs.Y, x + w - 58.0f, rs.Y);

    // ABXY Face Buttons
    struct FaceBtn { float bx; float by; wchar_t ch[2]; Gdiplus::Color col; WORD mask; };
    const FaceBtn btns[4] = {
        {192.0f, 48.0f, L"Y", Gdiplus::Color(255, 255, 214, 0),   XINPUT_GAMEPAD_Y},
        {176.0f, 62.0f, L"X", Gdiplus::Color(255, 0, 229, 255),   XINPUT_GAMEPAD_X},
        {208.0f, 62.0f, L"B", Gdiplus::Color(255, 255, 82, 82),   XINPUT_GAMEPAD_B},
        {192.0f, 76.0f, L"A", Gdiplus::Color(255, 105, 240, 174), XINPUT_GAMEPAD_A}
    };
    Gdiplus::StringFormat csf;
    csf.SetAlignment(Gdiplus::StringAlignmentCenter);
    csf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
    for (const auto& b : btns) {
        Gdiplus::PointF bp_c = pt(b.bx, b.by);
        bool pressed = (st.pad_buttons & b.mask) != 0;
        Gdiplus::SolidBrush bfill(Gdiplus::Color(pressed ? 160 : 40, b.col.GetR(), b.col.GetG(), b.col.GetB()));
        Gdiplus::Pen bpen_c(b.col, 1.3f);
        g.FillEllipse(&bfill, bp_c.X - 7.5f * sc, bp_c.Y - 7.5f * sc, 15.0f * sc, 15.0f * sc);
        g.DrawEllipse(&bpen_c, bp_c.X - 7.5f * sc, bp_c.Y - 7.5f * sc, 15.0f * sc, 15.0f * sc);
        Gdiplus::SolidBrush btxt(b.col);
        g.DrawString(b.ch, 1, &btn_font,
                     Gdiplus::RectF(bp_c.X - 8.0f * sc, bp_c.Y - 8.0f * sc, 16.0f * sc, 16.0f * sc), &csf, &btxt);
    }

    // Crisp side callout legends (including explicit Center [X] Guide callout!)
    Gdiplus::SolidBrush orange_txt(Gdiplus::Color(255, 255, 172, 64));
    g.DrawString(L"LT/LB", -1, &tiny_font, Gdiplus::RectF(x + 8.0f, oy + 4.0f, 56.0f, 14.0f), &lsf, &cy_txt);
    g.DrawString(L"LS:MOVE", -1, &tiny_font, Gdiplus::RectF(x + 6.0f, ls.Y - 7.0f, 52.0f, 14.0f), &lsf, &cy_txt);
    g.DrawString(L"DPAD", -1, &tiny_font, Gdiplus::RectF(x + 8.0f, y + h - 22.0f, 56.0f, 14.0f), &lsf, &cy_txt);

    g.DrawString(L"RT/RB", -1, &tiny_font, Gdiplus::RectF(x + w - 64.0f, oy + 4.0f, 56.0f, 14.0f), &rsf, &cy_txt);
    g.DrawString(L"RS:CAM", -1, &tiny_font, Gdiplus::RectF(x + w - 58.0f, rs.Y - 7.0f, 50.0f, 14.0f), &rsf, &cy_txt);
    g.DrawString(L"[X]=GUIDE", -1, &tiny_font, Gdiplus::RectF(gp.X - 42.0f, y + h - 20.0f, 84.0f, 14.0f), &csf, &orange_txt);
}

static void draw_bind_slot(Gdiplus::Graphics& g, LauncherUiState& st, HitZoneId id,
                           float x, float y, float w, float h,
                           const std::wstring& gc_lbl, const std::wstring& xb_lbl,
                           bool accent_amber, const Gdiplus::Font& tiny_font) {
    Gdiplus::RectF rc(x, y, w, h);
    st.zones.push_back({id, rc});
    bool hov = (st.hover_id == id);
    bool listening = (st.listening_zone == id);

    Gdiplus::GraphicsPath p;
    add_round_rect(p, rc, 3.0f);
    Gdiplus::SolidBrush bg(listening
        ? Gdiplus::Color(220, 56, 32, 8)
        : (hov ? Gdiplus::Color(235, 20, 38, 56) : Gdiplus::Color(225, 11, 18, 28)));
    g.FillPath(&bg, &p);
    Gdiplus::Pen pen(listening
        ? Gdiplus::Color(255, 255, 168, 32)
        : (hov ? Gdiplus::Color(255, 0, 229, 255)
               : (accent_amber ? Gdiplus::Color(210, 255, 136, 28) : Gdiplus::Color(200, 44, 68, 94))),
        (listening || hov) ? 1.4f : 1.0f);
    g.DrawPath(&pen, &p);

    Gdiplus::StringFormat lsf;
    lsf.SetAlignment(Gdiplus::StringAlignmentNear);
    lsf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
    lsf.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);

    Gdiplus::StringFormat rsf;
    rsf.SetAlignment(Gdiplus::StringAlignmentFar);
    rsf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
    rsf.SetTrimming(Gdiplus::StringTrimmingEllipsisCharacter);
    rsf.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);

    Gdiplus::SolidBrush left_br(accent_amber ? Gdiplus::Color(255, 255, 178, 72) : Gdiplus::Color(255, 152, 190, 222));
    Gdiplus::SolidBrush right_br(listening ? Gdiplus::Color(255, 255, 220, 120) : Gdiplus::Color(255, 232, 248, 255));
    float split = (std::min)(124.0f, w * 0.48f);
    g.DrawString(gc_lbl.c_str(), -1, &tiny_font, Gdiplus::RectF(x + 6.0f, y, split, h), &lsf, &left_br);
    std::wstring rtext = listening ? L"PRESS PAD BTN..." : xb_lbl;
    g.DrawString(rtext.c_str(), -1, &tiny_font, Gdiplus::RectF(x + split, y, w - split - 6.0f, h), &rsf, &right_br);
}

static void render_launcher_to_graphics(Gdiplus::Graphics& g, int width, int height, LauncherUiState& st) {
    st.zones.clear();
    g.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
    g.SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);
    g.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

    // 1. Obsidian Tech-Grid Backdrop
    Gdiplus::LinearGradientBrush bg_grad(
        Gdiplus::PointF(0, 0), Gdiplus::PointF(0, static_cast<float>(height)),
        Gdiplus::Color(255, 8, 12, 18),
        Gdiplus::Color(255, 11, 16, 25));
    g.FillRectangle(&bg_grad, 0, 0, width, height);

    Gdiplus::Pen grid_pen(Gdiplus::Color(15, 0, 229, 255), 1.0f);
    for (int gx = 0; gx < width; gx += 32) g.DrawLine(&grid_pen, gx, 0, gx, height);
    for (int gy = 0; gy < height; gy += 32) g.DrawLine(&grid_pen, 0, gy, width, gy);

    // Subtle top cyan ambient header wash
    Gdiplus::LinearGradientBrush top_glow(
        Gdiplus::PointF(0, 0), Gdiplus::PointF(0, 128.0f),
        Gdiplus::Color(42, 0, 185, 255),
        Gdiplus::Color(0, 8, 12, 18));
    g.FillRectangle(&top_glow, 0, 0, width, 128);

    // Outer steel frame border
    Gdiplus::Pen outer_pen(Gdiplus::Color(255, 34, 52, 74), 1.5f);
    g.DrawRectangle(&outer_pen, 6.0f, 6.0f, static_cast<float>(width - 12), static_cast<float>(height - 12));

    // Typography setup
    Gdiplus::FontFamily ff_ui(L"Segoe UI");
    Gdiplus::FontFamily ff_mono(L"Consolas");
    Gdiplus::Font f_hero(&ff_ui, 22.0f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::Font f_sub(&ff_ui, 11.5f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::Font f_card_hdr(&ff_ui, 14.0f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::Font f_lbl(&ff_ui, 12.5f, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    Gdiplus::Font f_val(&ff_ui, 13.0f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::Font f_mono(&ff_mono, 11.5f, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    Gdiplus::Font f_diag(&ff_mono, 10.2f, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    Gdiplus::Font f_tiny(&ff_mono, 9.8f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::Font f_btn(&ff_ui, 12.5f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
    Gdiplus::Font f_cta(&ff_ui, 17.0f, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);

    // 2. Hero Header Bar (y = 8..112)
    if (st.img_crest) {
        g.DrawImage(st.img_crest.get(), 22.0f, 8.0f, 96.0f, 97.0f);
        // Subtle vignette edge blend around crest box
        Gdiplus::Pen crest_ring(Gdiplus::Color(90, 0, 229, 255), 1.2f);
        g.DrawRectangle(&crest_ring, 22.0f, 8.0f, 96.0f, 97.0f);
    }

    if (st.img_vanessa) {
        float vx = static_cast<float>(width) - 252.0f;
        float vy = 6.0f;
        float vw = 234.0f;
        float vh = 112.0f;
        g.DrawImage(st.img_vanessa.get(), vx, vy, vw, vh);
        // Soft left & bottom fade into obsidian background
        Gdiplus::LinearGradientBrush left_fade(
            Gdiplus::PointF(vx - 1.0f, vy), Gdiplus::PointF(vx + 56.0f, vy),
            Gdiplus::Color(255, 9, 13, 20), Gdiplus::Color(0, 9, 13, 20));
        g.FillRectangle(&left_fade, vx - 1.0f, vy, 58.0f, vh);
        Gdiplus::LinearGradientBrush bot_fade(
            Gdiplus::PointF(vx, vy + vh - 22.0f), Gdiplus::PointF(vx, vy + vh + 1.0f),
            Gdiplus::Color(0, 9, 13, 20), Gdiplus::Color(255, 9, 13, 20));
        g.FillRectangle(&bot_fade, vx, vy + vh - 22.0f, vw + 2.0f, 24.0f);
    }

    Gdiplus::SolidBrush white_br(Gdiplus::Color(255, 244, 250, 255));
    Gdiplus::SolidBrush cyan_br(Gdiplus::Color(255, 0, 229, 255));
    Gdiplus::SolidBrush muted_br(Gdiplus::Color(255, 142, 174, 204));
    const bool is_vk = (st.cfg->backend == GraphicsBackend::Vulkan13);
    g.DrawString(L"P.N.03", -1, &f_hero, Gdiplus::PointF(132.0f, 16.0f), &white_br);
    g.DrawString(L"// GPNE08 WINDOWS x64 STATIC RECOMPILATION", -1, &f_hero, Gdiplus::PointF(214.0f, 16.0f), &cyan_br);
    g.DrawString(is_vk ? L"AEGIS SYSTEM INITIALIZED  |  SN PRODG MEKA.SYM + GDX/VULKAN 1.3 NATIVE PIPELINE"
                       : L"AEGIS SYSTEM INITIALIZED  |  SN PRODG MEKA.SYM + GDX/D3D11 NATIVE PIPELINE",
                 -1, &f_sub, Gdiplus::PointF(134.0f, 48.0f), &muted_br);

    // Verification pill under header subtitle
    Gdiplus::RectF ver_rc(134.0f, 70.0f, 510.0f, 26.0f);
    Gdiplus::GraphicsPath ver_p;
    add_chamfer_rect(ver_p, ver_rc, 5.0f, 0.0f, 5.0f, 0.0f);
    Gdiplus::SolidBrush ver_bg(Gdiplus::Color(220, 11, 24, 36));
    g.FillPath(&ver_bg, &ver_p);
    Gdiplus::Pen ver_pen(Gdiplus::Color(150, 0, 229, 255), 1.0f);
    g.DrawPath(&ver_pen, &ver_p);
    Gdiplus::SolidBrush led_green(Gdiplus::Color(255, 72, 255, 158));
    g.FillEllipse(&led_green, 145.0f, 79.0f, 8.0f, 8.0f);
    g.DrawString(L"GPNE08 VERIFIED  |  700 FST FILES  |  6,340 RECOMP FUNCS  |  0 BUILT-IN ASSETS",
                 -1, &f_tiny, Gdiplus::PointF(160.0f, 76.0f), &cyan_br);

    // 3. ISO File Selector Bar (y = 118..160)
    Gdiplus::RectF iso_rc(24.0f, 118.0f, static_cast<float>(width - 48), 42.0f);
    Gdiplus::GraphicsPath iso_p;
    add_chamfer_rect(iso_p, iso_rc, 0.0f, 8.0f, 0.0f, 8.0f);
    Gdiplus::SolidBrush iso_bg(Gdiplus::Color(242, 13, 20, 30));
    g.FillPath(&iso_bg, &iso_p);
    Gdiplus::Pen iso_pen(Gdiplus::Color(220, 48, 70, 96), 1.1f);
    g.DrawPath(&iso_pen, &iso_p);
    g.FillRectangle(&cyan_br, iso_rc.X, iso_rc.Y, 3.5f, iso_rc.Height);

    Gdiplus::StringFormat lsf;
    lsf.SetAlignment(Gdiplus::StringAlignmentNear);
    lsf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
    lsf.SetTrimming(Gdiplus::StringTrimmingEllipsisPath);
    lsf.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);
    g.DrawString(L"ISO PATH:", -1, &f_sub, Gdiplus::RectF(38.0f, 118.0f, 76.0f, 42.0f), &lsf, &muted_br);

    // If not using a live HWND EDIT child overlay, draw path text cleanly right inside the bar
    if (!st.live_edit_control) {
        std::wstring iso_w = st.cfg->iso_path.empty()
            ? L"<AUTO-SCAN ROOT *.ISO / *.GCM OR BROWSE>"
            : utf8_to_wide(st.cfg->iso_path);
        g.DrawString(iso_w.c_str(), -1, &f_mono, Gdiplus::RectF(116.0f, 118.0f, 680.0f, 42.0f), &lsf, &white_br);
    }

    // D3D11 + Mounted Status Pills
    Gdiplus::RectF d3d_rc(808.0f, 126.0f, 94.0f, 26.0f);
    Gdiplus::SolidBrush badge_bg(Gdiplus::Color(210, 12, 34, 48));
    g.FillRectangle(&badge_bg, d3d_rc);
    g.DrawRectangle(&ver_pen, d3d_rc);
    Gdiplus::StringFormat csf;
    csf.SetAlignment(Gdiplus::StringAlignmentCenter);
    csf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
    g.DrawString(is_vk ? L"VULKAN 1.3" : L"D3D11 / DX11", -1, &f_tiny, d3d_rc, &csf, &cyan_br);

    Gdiplus::RectF mnt_rc(910.0f, 126.0f, 178.0f, 26.0f);
    g.FillRectangle(&badge_bg, mnt_rc);
    g.DrawRectangle(&ver_pen, mnt_rc);
    std::wstring short_sum = L"MOUNTED - 700 FILES";
    if (!st.iso_mount_summary.empty()) {
        std::wstring ws = utf8_to_wide(st.iso_mount_summary);
        auto bar_pos = ws.find(L'|');
        if (bar_pos != std::wstring::npos) ws = ws.substr(0, bar_pos);
        while (!ws.empty() && ws.back() == L' ') ws.pop_back();
        if (!ws.empty()) short_sum = ws;
    }
    g.DrawString(short_sum.c_str(), -1, &f_tiny, mnt_rc, &csf, &led_green);

    // Metallic White "BROWSE ISO" Button
    Gdiplus::RectF brw_rc(1098.0f, 124.0f, 126.0f, 30.0f);
    st.zones.push_back({HZ_BROWSE_ISO, brw_rc});
    bool brw_hov = (st.hover_id == HZ_BROWSE_ISO);
    Gdiplus::GraphicsPath brw_p;
    add_chamfer_rect(brw_p, brw_rc, 5.0f, 0.0f, 5.0f, 0.0f);
    Gdiplus::LinearGradientBrush brw_grad(
        Gdiplus::PointF(brw_rc.X, brw_rc.Y), Gdiplus::PointF(brw_rc.X, brw_rc.GetBottom()),
        brw_hov ? Gdiplus::Color(255, 255, 255, 255) : Gdiplus::Color(255, 232, 240, 248),
        brw_hov ? Gdiplus::Color(255, 200, 238, 255) : Gdiplus::Color(255, 190, 206, 224));
    g.FillPath(&brw_grad, &brw_p);
    Gdiplus::Pen brw_pen(brw_hov ? Gdiplus::Color(255, 0, 229, 255) : Gdiplus::Color(255, 255, 255, 255), 1.3f);
    g.DrawPath(&brw_pen, &brw_p);
    Gdiplus::SolidBrush dark_ink(Gdiplus::Color(255, 10, 16, 24));
    g.DrawString(L"BROWSE ISO", -1, &f_btn, brw_rc, &csf, &dark_ink);

    // 4. Three Equal-Width Chamfered Obsidian-Glass Cards (y = 174..614)
    const float card_y = 174.0f;
    const float card_h = 440.0f;
    const float card_w = 392.0f;
    const float card_x1 = 24.0f;
    const float card_x2 = 434.0f;
    const float card_x3 = 844.0f;

    // --- CARD 1: 3D GRAPHICS & DISPLAY ---
    draw_card_shell(g, card_x1, card_y, card_w, card_h, L"3D GRAPHICS & DISPLAY", true, true, false, f_card_hdr);
    draw_cyber_dropdown(g, st, HZ_DD_RESOLUTION, card_x1 + 18.0f, card_y + 42.0f, card_w - 36.0f,
                        L"Resolution", resolution_label(*st.cfg), -1, f_lbl, f_val, true);
    draw_cyber_dropdown(g, st, HZ_DD_DISPLAY_MODE, card_x1 + 18.0f, card_y + 98.0f, card_w - 36.0f,
                        L"Display Mode", display_mode_label(*st.cfg), -1, f_lbl, f_val, false);
    draw_cyber_dropdown(g, st, HZ_DD_ANTIALIASING, card_x1 + 18.0f, card_y + 154.0f, card_w - 36.0f,
                        L"Anti-Aliasing", antialiasing_label(*st.cfg),
                        (st.cfg->msaa_mode != AntiAliasingMode::Off) ? 2 : 0, f_lbl, f_val, false);
    draw_cyber_dropdown(g, st, HZ_DD_ASPECT, card_x1 + 18.0f, card_y + 210.0f, card_w - 36.0f,
                        L"Aspect Ratio", aspect_ratio_label(*st.cfg),
                        (st.cfg->aspect_ratio != AspectRatioMode::Original_4_3) ? 1 : 2, f_lbl, f_val, false);
    const float half_dd_w = 173.0f;
    draw_cyber_dropdown(g, st, HZ_DD_BACKEND, card_x1 + 18.0f, card_y + 266.0f, half_dd_w,
                        L"Graphics Backend", backend_label(*st.cfg),
                        -1, f_lbl, f_val, is_vk);
    draw_cyber_dropdown(g, st, HZ_DD_ANISO, card_x1 + 18.0f + half_dd_w + 10.0f, card_y + 266.0f, half_dd_w,
                        L"Anisotropic Filter", aniso_label(*st.cfg),
                        (st.cfg->anisotropic_filtering >= 8) ? 1 : 0, f_lbl, f_val, false);

    int bri_pct = static_cast<int>(std::lround(std::clamp(st.cfg->brightness, 0.50f, 2.00f) * 100.0f));
    float bri_norm = (static_cast<float>(bri_pct) - 50.0f) / 150.0f;
    std::wostringstream bri_lbl;
    bri_lbl << bri_pct << L"%";
    draw_cyber_slider(g, st, HZ_SLIDER_BRIGHTNESS, card_x1 + 18.0f, card_y + 321.0f, card_w - 36.0f,
                      L"Display Brightness", bri_norm, bri_lbl.str(), false, f_lbl, f_mono);

    draw_cyber_switch_row(g, st, HZ_SW_VSYNC, card_x1 + 18.0f, card_y + 362.0f, card_w - 36.0f,
                          L"V-Sync (Display Sync)", st.cfg->vsync, false, f_lbl, f_tiny);
    draw_cyber_switch_row(g, st, HZ_SW_LIMIT_FPS, card_x1 + 18.0f, card_y + 399.0f, card_w - 36.0f,
                          L"Frame Limiter (59.94 FPS Lock)", st.cfg->limit_fps_60, true, f_lbl, f_tiny);

    // --- CARD 2: LOCALIZATION & SYSTEM ---
    draw_card_shell(g, card_x2, card_y, card_w, card_h, L"LOCALIZATION & SYSTEM", true, st.cfg->load_tools_rel_debug, true, f_card_hdr);
    draw_cyber_dropdown(g, st, HZ_DD_LANGUAGE, card_x2 + 18.0f, card_y + 48.0f, card_w - 36.0f,
                        L"Language (CMesCtrl::MesSetLanguage Hook)", language_label(*st.cfg), -1, f_lbl, f_val, true);
    draw_cyber_switch_row(g, st, HZ_SW_HD_FONT, card_x2 + 18.0f, card_y + 114.0f, card_w - 36.0f,
                          L"Chinese HD Font / \u7B80\u4F53\u4E2D\u6587 HD\u5B57\u4F53", st.cfg->enable_hd_chinese_font, false, f_lbl, f_tiny);
    draw_cyber_switch_row(g, st, HZ_SW_TOOLS_REL, card_x2 + 18.0f, card_y + 156.0f, card_w - 36.0f,
                          L"Tools.rel Sound Test & Debug Hooks", st.cfg->load_tools_rel_debug, true, f_lbl, f_tiny);
    draw_cyber_switch_row(g, st, HZ_SW_DEFLICKER, card_x2 + 18.0f, card_y + 198.0f, card_w - 36.0f,
                          L"Bypass 480i Copy Deflicker Filter", st.cfg->disable_copy_deflicker, false, f_lbl, f_tiny);
    draw_oscilloscope_box(g, st, card_x2 + 18.0f, card_y + 240.0f, card_w - 36.0f, 102.0f, f_tiny, f_mono);
    g.DrawString(L"BUILTIN CHEAT TOGGLES (OFF BY DEFAULT):", -1, &f_tiny,
                 Gdiplus::PointF(card_x2 + 18.0f, card_y + 347.0f), &muted_br);
    const float cp_w = 173.0f;
    const float cp_h = 25.0f;
    const float cp_x0 = card_x2 + 18.0f;
    const float cp_x1 = cp_x0 + cp_w + 10.0f;
    draw_cyber_cheat_pill(g, st, HZ_SW_CHEAT_GOD,     cp_x0, card_y + 365.0f, cp_w, cp_h, L"INF SHIELD HP",  st.cfg->cheat_god_mode,         f_tiny);
    draw_cyber_cheat_pill(g, st, HZ_SW_CHEAT_ENERGY,  cp_x1, card_y + 365.0f, cp_w, cp_h, L"INF ENERGY / ED",st.cfg->cheat_infinite_energy,  f_tiny);
    draw_cyber_cheat_pill(g, st, HZ_SW_CHEAT_CREDITS, cp_x0, card_y + 395.0f, cp_w, cp_h, L"9.99M CREDITS",  st.cfg->cheat_infinite_credits, f_tiny);
    draw_cyber_cheat_pill(g, st, HZ_SW_CHEAT_SUITS,   cp_x1, card_y + 395.0f, cp_w, cp_h, L"ALL SUITS MAX",  st.cfg->cheat_unlock_all_suits, f_tiny);

    // --- CARD 3: GAMEPAD CONTROLLER (SDL2 / XINPUT / DIRECTINPUT / WINMM) ---
    draw_card_shell(g, card_x3, card_y, card_w, card_h, L"GAMEPAD CONTROLLER", st.cfg->enable_xinput, st.pad_connected, true, f_card_hdr);
    g.DrawString(L"Preset (A-D)", -1, &f_lbl,
                 Gdiplus::RectF(card_x3 + 18.0f, card_y + 44.0f, 110.0f, 26.0f), &lsf, &white_br);

    for (int i = 0; i < 4; ++i) {
        HitZoneId pid = static_cast<HitZoneId>(HZ_PRESET_A + i);
        Gdiplus::RectF prc(card_x3 + card_w - 18.0f - static_cast<float>(4 - i) * 36.0f + 4.0f, card_y + 44.0f, 32.0f, 26.0f);
        st.zones.push_back({pid, prc});
        bool active = (st.cfg->control_scheme_preset == i);
        bool hov = (st.hover_id == pid);
        Gdiplus::GraphicsPath pp;
        add_chamfer_rect(pp, prc, 4.0f, 0.0f, 4.0f, 0.0f);
        Gdiplus::SolidBrush pbg(active ? Gdiplus::Color(70, 0, 229, 255) : Gdiplus::Color(235, 13, 21, 31));
        g.FillPath(&pbg, &pp);
        Gdiplus::Pen ppen((active || hov) ? Gdiplus::Color(255, 0, 229, 255) : Gdiplus::Color(220, 58, 78, 104), active ? 1.5f : 1.0f);
        g.DrawPath(&ppen, &pp);
        wchar_t lbl[2] = {static_cast<wchar_t>(L'A' + i), L'\0'};
        g.DrawString(lbl, 1, &f_btn, prc, &csf, active ? &cyan_br : &white_br);
    }

    draw_xbox_wireframe(g, st, card_x3 + 18.0f, card_y + 74.0f, card_w - 36.0f, 144.0f, f_tiny, f_tiny);

    // Custom Interactive Button Remapping Grid (click to pick or capture on controller)
    g.DrawString(L"CUSTOM BUTTON REMAP (CLICK TO BIND / R-CLICK CAPTURE):", -1, &f_tiny,
                 Gdiplus::PointF(card_x3 + 18.0f, card_y + 222.0f), &muted_br);

    const float col0_x = card_x3 + 18.0f;
    const float col1_x = card_x3 + 200.0f;
    const float bw = 174.0f;
    const float bh = 20.0f;
    const float by0 = card_y + 238.0f;
    draw_bind_slot(g, st, HZ_BIND_A,     col0_x, by0 +  0.0f, bw, bh, L"GC A (Shoot)",  utf8_to_wide(RuntimeConfig::xbox_input_source_label(st.cfg->bind_gc_a)),     false, f_tiny);
    draw_bind_slot(g, st, HZ_BIND_L,     col1_x, by0 +  0.0f, bw, bh, L"GC L (Lock)",   utf8_to_wide(RuntimeConfig::xbox_input_source_label(st.cfg->bind_gc_l)),     false, f_tiny);
    draw_bind_slot(g, st, HZ_BIND_B,     col0_x, by0 + 22.0f, bw, bh, L"GC B (Dodge)",  utf8_to_wide(RuntimeConfig::xbox_input_source_label(st.cfg->bind_gc_b)),     false, f_tiny);
    draw_bind_slot(g, st, HZ_BIND_R,     col1_x, by0 + 22.0f, bw, bh, L"GC R (Turn)",   utf8_to_wide(RuntimeConfig::xbox_input_source_label(st.cfg->bind_gc_r)),     false, f_tiny);
    draw_bind_slot(g, st, HZ_BIND_X,     col0_x, by0 + 44.0f, bw, bh, L"GC X (Barrier)",utf8_to_wide(RuntimeConfig::xbox_input_source_label(st.cfg->bind_gc_x)),     false, f_tiny);
    draw_bind_slot(g, st, HZ_BIND_Z,     col1_x, by0 + 44.0f, bw, bh, L"GC Z (Map)",    utf8_to_wide(RuntimeConfig::xbox_input_source_label(st.cfg->bind_gc_z)),     false, f_tiny);
    draw_bind_slot(g, st, HZ_BIND_Y,     col0_x, by0 + 66.0f, bw, bh, L"GC Y (Energy)", utf8_to_wide(RuntimeConfig::xbox_input_source_label(st.cfg->bind_gc_y)),     false, f_tiny);
    draw_bind_slot(g, st, HZ_BIND_START, col1_x, by0 + 66.0f, bw, bh, L"GC START",      utf8_to_wide(RuntimeConfig::xbox_input_source_label(st.cfg->bind_gc_start)), false, f_tiny);

    // Explicit Center Xbox [X] Guide Button Target Row
    draw_bind_slot(g, st, HZ_BIND_GUIDE, col0_x, by0 + 89.0f, card_w - 36.0f, 20.0f,
                   L"CENTER [X] GUIDE ->",
                   utf8_to_wide(RuntimeConfig::guide_action_label(st.cfg->bind_guide_target)),
                   true, f_tiny);

    int dz_pct = static_cast<int>(std::lround(st.cfg->left_stick_deadzone * 100.0f));
    float dz_norm = (static_cast<float>(dz_pct) - 5.0f) / 35.0f;
    std::wostringstream dz_lbl;
    dz_lbl << dz_pct << L"%";
    draw_cyber_slider(g, st, HZ_SLIDER_DEADZONE, card_x3 + 18.0f, card_y + 352.0f, card_w - 36.0f,
                      L"Left/Right Stick Deadzone", dz_norm, dz_lbl.str(), false, f_lbl, f_mono);

    int vib_pct = st.cfg->enable_vibration ? static_cast<int>(std::lround(st.cfg->vibration_strength * 100.0f)) : 0;
    float vib_norm = static_cast<float>(vib_pct) / 100.0f;
    std::wostringstream vib_lbl;
    if (vib_pct == 0) vib_lbl << L"MUTED";
    else vib_lbl << vib_pct << L"%";
    draw_cyber_slider(g, st, HZ_SLIDER_RUMBLE, card_x3 + 18.0f, card_y + 394.0f, card_w - 36.0f,
                      L"Dual-Motor Haptic Rumble", vib_norm, vib_lbl.str(), true, f_lbl, f_mono);

    // 5. Bottom Diagnostic HUD & Primary Action Bar (y = 628..696)
    Gdiplus::RectF diag_rc(24.0f, 628.0f, 788.0f, 68.0f);
    Gdiplus::GraphicsPath diag_p;
    add_chamfer_rect(diag_p, diag_rc, 0.0f, 8.0f, 0.0f, 8.0f);
    Gdiplus::SolidBrush diag_bg(Gdiplus::Color(242, 11, 16, 24));
    g.FillPath(&diag_bg, &diag_p);
    Gdiplus::Pen diag_pen(Gdiplus::Color(220, 46, 62, 82), 1.1f);
    g.DrawPath(&diag_pen, &diag_p);
    Gdiplus::SolidBrush orange_br(Gdiplus::Color(255, 255, 136, 28));
    g.FillRectangle(&orange_br, diag_rc.X, diag_rc.Y, 3.5f, diag_rc.Height);

    CyberLauncherUI helper(*st.cfg);
    std::wstring diag_line1 = utf8_to_wide(helper.build_diagnostic_readout());
    const bool use_vk = (st.cfg->backend == GraphicsBackend::Vulkan13);
    std::wostringstream diag_line2;
    diag_line2 << (use_vk ? L"VULKAN 1.3" : L"D3D11 HW")
               << L" | KB PLAY: WASD Move | IJKL Cam | Space/Z=A Shift/X=B Q=L E=R Tab=Z Enter/Esc=Pause";
    Gdiplus::StringFormat dsf;
    dsf.SetAlignment(Gdiplus::StringAlignmentNear);
    dsf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
    dsf.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);
    g.DrawString(diag_line1.c_str(), -1, &f_diag, Gdiplus::RectF(36.0f, 636.0f, 768.0f, 22.0f), &dsf, &orange_br);
    g.DrawString(diag_line2.str().c_str(), -1, &f_diag, Gdiplus::RectF(36.0f, 662.0f, 768.0f, 22.0f), &dsf, &muted_br);

    // Primary Chamfered Orange/Amber Launch CTA Button
    Gdiplus::RectF launch_rc(844.0f, 628.0f, 392.0f, 68.0f);
    st.zones.push_back({HZ_BTN_LAUNCH, launch_rc});
    bool lhov = (st.hover_id == HZ_BTN_LAUNCH);

    Gdiplus::GraphicsPath lglow_p;
    add_chamfer_rect(lglow_p, Gdiplus::RectF(launch_rc.X - 3, launch_rc.Y - 3, launch_rc.Width + 6, launch_rc.Height + 6), 14.0f, 0.0f, 14.0f, 0.0f);
    Gdiplus::SolidBrush lglow_br(Gdiplus::Color(lhov ? 95 : 55, 255, 120, 10));
    g.FillPath(&lglow_br, &lglow_p);

    Gdiplus::GraphicsPath launch_p;
    add_chamfer_rect(launch_p, launch_rc, 12.0f, 0.0f, 12.0f, 0.0f);
    Gdiplus::LinearGradientBrush launch_grad(
        Gdiplus::PointF(launch_rc.X, launch_rc.Y), Gdiplus::PointF(launch_rc.GetRight(), launch_rc.GetBottom()),
        lhov ? Gdiplus::Color(255, 255, 168, 48) : Gdiplus::Color(255, 255, 138, 22),
        lhov ? Gdiplus::Color(255, 255, 112, 18) : Gdiplus::Color(255, 236, 86, 0));
    g.FillPath(&launch_grad, &launch_p);

    Gdiplus::Pen launch_rim(lhov ? Gdiplus::Color(255, 255, 245, 210) : Gdiplus::Color(255, 255, 210, 120), 1.8f);
    g.DrawPath(&launch_rim, &launch_p);

    g.DrawString(L"LAUNCH P.N.03 ENGINE  >>", -1, &f_cta,
                 Gdiplus::RectF(launch_rc.X, launch_rc.Y + 8.0f, launch_rc.Width, 30.0f), &csf, &dark_ink);
    Gdiplus::SolidBrush dark_sub(Gdiplus::Color(215, 26, 12, 4));
    g.DrawString(use_vk ? L"SAVE CONFIG & BOOT VULKAN 1.3" : L"SAVE CONFIG & BOOT D3D11", -1, &f_tiny,
                 Gdiplus::RectF(launch_rc.X, launch_rc.Y + 38.0f, launch_rc.Width, 20.0f), &csf, &dark_sub);
}

static void populate_dropdown_choices(HitZoneId id, const RuntimeConfig& cfg,
                                      std::vector<DropdownChoice>& out_choices, int& out_selected_idx) {
    out_choices.clear();
    out_selected_idx = 0;
    if (id == HZ_DD_RESOLUTION) {
        out_choices = {
            {L"3840x2160 4K (6x EFB)", 0},
            {L"2560x1440 QHD (4x EFB)", 1},
            {L"1920x1080 FHD (3x EFB)", 2},
            {L"1280x720 HD (2x EFB)", 3},
            {L"1920x1080 FHD (1x Native EFB)", 4},
            {L"1280x720 HD (1x Native EFB - iGPU)", 5},
            {L"640x480 480p (1x Native EFB - Fastest)", 6}
        };
        if (cfg.internal_scale_factor <= 1u) {
            if (cfg.render_width >= 1920u) out_selected_idx = 4;
            else if (cfg.render_width >= 1280u) out_selected_idx = 5;
            else out_selected_idx = 6;
        } else if (cfg.render_width >= 3840u && cfg.internal_scale_factor >= 6u) out_selected_idx = 0;
        else if (cfg.render_width >= 2560u && cfg.internal_scale_factor >= 4u) out_selected_idx = 1;
        else if (cfg.render_width >= 1920u && cfg.internal_scale_factor >= 3u) out_selected_idx = 2;
        else out_selected_idx = 3;
    } else if (id == HZ_DD_DISPLAY_MODE) {
        out_choices = {
            {L"Borderless Fullscreen", static_cast<int>(WindowMode::BorderlessFullscreen)},
            {L"Exclusive Fullscreen", static_cast<int>(WindowMode::ExclusiveFullscreen)},
            {L"Windowed", static_cast<int>(WindowMode::Windowed)}
        };
        for (size_t i = 0; i < out_choices.size(); ++i) {
            if (out_choices[i].value == static_cast<int>(cfg.window_mode)) out_selected_idx = static_cast<int>(i);
        }
    } else if (id == HZ_DD_ANTIALIASING) {
        out_choices = {
            {L"8x MSAA + FXAA Active", 0},
            {L"4x MSAA + FXAA Active", 1},
            {L"4x MSAA", 2},
            {L"2x MSAA", 3},
            {L"FXAA 3.11 Active", 4},
            {L"Off", 5}
        };
        if (cfg.msaa_mode == AntiAliasingMode::MSAA_8x) out_selected_idx = 0;
        else if (cfg.msaa_mode == AntiAliasingMode::MSAA_4x) out_selected_idx = cfg.enable_fxaa ? 1 : 2;
        else if (cfg.msaa_mode == AntiAliasingMode::MSAA_2x) out_selected_idx = 3;
        else if (cfg.enable_fxaa || cfg.msaa_mode == AntiAliasingMode::FXAA) out_selected_idx = 4;
        else out_selected_idx = 5;
    } else if (id == HZ_DD_ASPECT) {
        out_choices = {
            {L"4:3 Original (Centered HD)", static_cast<int>(AspectRatioMode::Original_4_3)},
            {L"16:9 Widescreen + No Letterbox", static_cast<int>(AspectRatioMode::Widescreen_16_9)},
            {L"21:9 Ultrawide + No Letterbox", static_cast<int>(AspectRatioMode::Ultrawide_21_9)}
        };
        for (size_t i = 0; i < out_choices.size(); ++i) {
            if (out_choices[i].value == static_cast<int>(cfg.aspect_ratio)) out_selected_idx = static_cast<int>(i);
        }
    } else if (id == HZ_DD_BACKEND) {
        out_choices = {
            {L"Direct3D 11 (Native DX11)", static_cast<int>(GraphicsBackend::Direct3D11)},
            {L"Vulkan 1.3 (Dynamic SPIR-V)", static_cast<int>(GraphicsBackend::Vulkan13)}
        };
        for (size_t i = 0; i < out_choices.size(); ++i) {
            if (out_choices[i].value == static_cast<int>(cfg.backend)) out_selected_idx = static_cast<int>(i);
        }
    } else if (id == HZ_DD_ANISO) {
        out_choices = {
            {L"16x AF", 16},
            {L"8x AF", 8},
            {L"4x AF", 4},
            {L"1x AF", 1}
        };
        for (size_t i = 0; i < out_choices.size(); ++i) {
            if (out_choices[i].value == static_cast<int>(cfg.anisotropic_filtering)) out_selected_idx = static_cast<int>(i);
        }
    } else if (id == HZ_DD_LANGUAGE) {
        out_choices = {
            {L"\u7B80\u4F53\u4E2D\u6587 (Simplified Chinese)", static_cast<int>(GameLanguage::SimplifiedChinese)},
            {L"English (US Default)", static_cast<int>(GameLanguage::English)},
            {L"\u65E5\u672C\u8A9E (Japanese)", static_cast<int>(GameLanguage::Japanese)},
            {L"Fran\u00E7ais (/id/fra)", static_cast<int>(GameLanguage::French)},
            {L"Deutsch (/id/ger)", static_cast<int>(GameLanguage::German)},
            {L"Espa\u00F1ol (/id/spa)", static_cast<int>(GameLanguage::Spanish)},
            {L"Italiano (/id/ita)", static_cast<int>(GameLanguage::Italian)}
        };
        for (size_t i = 0; i < out_choices.size(); ++i) {
            if (out_choices[i].value == static_cast<int>(cfg.language)) out_selected_idx = static_cast<int>(i);
        }
    } else if (id >= HZ_BIND_A && id <= HZ_BIND_START) {
        const int* ptr = config_bind_ptr_for_zone(const_cast<RuntimeConfig&>(cfg), id);
        int cur = ptr ? *ptr : 0;
        out_choices = {
            {L">> [CAPTURE PRESS ON XBOX CONTROLLER] <<", -1},
            {L"Xbox A",               static_cast<int>(XboxInputSource::BtnA)},
            {L"Xbox B",               static_cast<int>(XboxInputSource::BtnB)},
            {L"Xbox X",               static_cast<int>(XboxInputSource::BtnX)},
            {L"Xbox Y",               static_cast<int>(XboxInputSource::BtnY)},
            {L"LB (Left Bumper)",     static_cast<int>(XboxInputSource::BtnLB)},
            {L"RB (Right Bumper)",    static_cast<int>(XboxInputSource::BtnRB)},
            {L"LT (Left Trigger)",    static_cast<int>(XboxInputSource::TriggerLT)},
            {L"RT (Right Trigger)",   static_cast<int>(XboxInputSource::TriggerRT)},
            {L"View (Back)",          static_cast<int>(XboxInputSource::BtnBack)},
            {L"Menu (Start)",         static_cast<int>(XboxInputSource::BtnStart)},
            {L"Center Xbox [X] Guide",static_cast<int>(XboxInputSource::BtnGuide)},
            {L"LS Click (L3)",        static_cast<int>(XboxInputSource::BtnLStick)},
            {L"RS Click (R3)",        static_cast<int>(XboxInputSource::BtnRStick)},
            {L"D-Pad Up",             static_cast<int>(XboxInputSource::DpadUp)},
            {L"D-Pad Down",           static_cast<int>(XboxInputSource::DpadDown)},
            {L"D-Pad Left",           static_cast<int>(XboxInputSource::DpadLeft)},
            {L"D-Pad Right",          static_cast<int>(XboxInputSource::DpadRight)},
            {L"Unbound (Disabled)",   static_cast<int>(XboxInputSource::None)}
        };
        for (size_t i = 0; i < out_choices.size(); ++i) {
            if (out_choices[i].value == cur) out_selected_idx = static_cast<int>(i);
        }
    } else if (id == HZ_BIND_GUIDE) {
        out_choices = {
            {L"Pause / System Menu (GC START)", static_cast<int>(GuideActionTarget::GcStart)},
            {L"Status / Map Screen (GC Z)",     static_cast<int>(GuideActionTarget::GcZ)},
            {L"Energy Drive (GC Y)",            static_cast<int>(GuideActionTarget::GcY)},
            {L"Barrier / Palm (GC X)",          static_cast<int>(GuideActionTarget::GcX)},
            {L"Lock-On / Turn Left (GC L)",     static_cast<int>(GuideActionTarget::GcL)},
            {L"Quick-Turn / Boost (GC R)",      static_cast<int>(GuideActionTarget::GcR)},
            {L"Shoot / Confirm (GC A)",         static_cast<int>(GuideActionTarget::GcA)},
            {L"Dodge / Cancel (GC B)",          static_cast<int>(GuideActionTarget::GcB)},
            {L"Disabled (or Custom Slot Bind)", static_cast<int>(GuideActionTarget::Disabled)}
        };
        for (size_t i = 0; i < out_choices.size(); ++i) {
            if (out_choices[i].value == cfg.bind_guide_target) out_selected_idx = static_cast<int>(i);
        }
    }
}

static void apply_dropdown_choice(HitZoneId id, int val, LauncherUiState& st) {
    RuntimeConfig& cfg = *st.cfg;
    if (id == HZ_DD_RESOLUTION) {
        if (val == 0)      { cfg.render_width = 3840; cfg.render_height = 2160; cfg.internal_scale_factor = 6; }
        else if (val == 1) { cfg.render_width = 2560; cfg.render_height = 1440; cfg.internal_scale_factor = 4; }
        else if (val == 2) { cfg.render_width = 1920; cfg.render_height = 1080; cfg.internal_scale_factor = 3; }
        else if (val == 3) { cfg.render_width = 1280; cfg.render_height = 720;  cfg.internal_scale_factor = 2; }
        else if (val == 4) { cfg.render_width = 1920; cfg.render_height = 1080; cfg.internal_scale_factor = 1; }
        else if (val == 5) { cfg.render_width = 1280; cfg.render_height = 720;  cfg.internal_scale_factor = 1; }
        else               { cfg.render_width = 640;  cfg.render_height = 480;  cfg.internal_scale_factor = 1; }
    } else if (id == HZ_DD_DISPLAY_MODE) {
        cfg.window_mode = static_cast<WindowMode>(val);
    } else if (id == HZ_DD_ANTIALIASING) {
        if (val == 0)      { cfg.msaa_mode = AntiAliasingMode::MSAA_8x; cfg.enable_fxaa = true; }
        else if (val == 1) { cfg.msaa_mode = AntiAliasingMode::MSAA_4x; cfg.enable_fxaa = true; }
        else if (val == 2) { cfg.msaa_mode = AntiAliasingMode::MSAA_4x; cfg.enable_fxaa = false; }
        else if (val == 3) { cfg.msaa_mode = AntiAliasingMode::MSAA_2x; cfg.enable_fxaa = false; }
        else if (val == 4) { cfg.msaa_mode = AntiAliasingMode::FXAA;    cfg.enable_fxaa = true; }
        else               { cfg.msaa_mode = AntiAliasingMode::Off;     cfg.enable_fxaa = false; }
    } else if (id == HZ_DD_ASPECT) {
        cfg.aspect_ratio = static_cast<AspectRatioMode>(val);
        cfg.remove_cinesco_bars = (cfg.aspect_ratio != AspectRatioMode::Original_4_3);
    } else if (id == HZ_DD_BACKEND) {
        cfg.backend = static_cast<GraphicsBackend>(val);
    } else if (id == HZ_DD_ANISO) {
        cfg.anisotropic_filtering = static_cast<uint32_t>(val);
    } else if (id == HZ_DD_LANGUAGE) {
        cfg.language = static_cast<GameLanguage>(val);
    } else if (id >= HZ_BIND_A && id <= HZ_BIND_START) {
        if (val == -1) {
            st.listening_zone = id;
            st.listen_prev_buttons = st.pad_buttons;
            st.listen_prev_lt = (st.pad_lt > 0.55f);
            st.listen_prev_rt = (st.pad_rt > 0.55f);
        } else if (int* ptr = config_bind_ptr_for_zone(cfg, id)) {
            *ptr = val;
            cfg.control_scheme_preset = 4; // Custom
            st.listening_zone = HZ_NONE;
        }
    } else if (id == HZ_BIND_GUIDE) {
        cfg.bind_guide_target = val;
    }
}

static HitZoneId hit_test_zones(const LauncherUiState& st, float x, float y) {
    for (const auto& z : st.zones) {
        if (z.rect.Contains(x, y)) return z.id;
    }
    return HZ_NONE;
}

static void update_slider_from_x(LauncherUiState& st, HitZoneId id, float mx) {
    for (const auto& z : st.zones) {
        if (z.id != id) continue;
        float tx = z.rect.X + 3.0f;
        float tw = z.rect.Width - 6.0f;
        float t = (mx - tx) / (std::max)(1.0f, tw);
        t = (std::max)(0.0f, (std::min)(1.0f, t));
        if (id == HZ_SLIDER_DEADZONE) {
            float dz = 0.05f + t * 0.35f;
            st.cfg->left_stick_deadzone = dz;
            st.cfg->right_stick_deadzone = dz;
        } else if (id == HZ_SLIDER_RUMBLE) {
            st.cfg->vibration_strength = t;
            st.cfg->enable_vibration = (t >= 0.02f);
        } else if (id == HZ_SLIDER_BRIGHTNESS) {
            st.cfg->brightness = 0.50f + t * 1.50f;
        }
        break;
    }
}

static void show_cyber_dropdown_menu(HWND hwnd, LauncherUiState& st, HitZoneId id) {
    std::vector<DropdownChoice> choices;
    int selected_idx = 0;
    populate_dropdown_choices(id, *st.cfg, choices, selected_idx);
    if (choices.empty()) return;

    Gdiplus::RectF anchor(40.0f, 220.0f, 340.0f, 31.0f);
    for (const auto& z : st.zones) {
        if (z.id == id) { anchor = z.rect; break; }
    }

    st.active_menu_labels.clear();
    HMENU hMenu = CreatePopupMenu();
    for (size_t i = 0; i < choices.size(); ++i) {
        st.active_menu_labels.push_back(choices[i].label);
        UINT flags = MF_OWNERDRAW | ((static_cast<int>(i) == selected_idx) ? MF_CHECKED : 0u);
        AppendMenuW(hMenu, flags, 5000u + static_cast<UINT_PTR>(i), choices[i].label.c_str());
    }

    POINT pt{static_cast<LONG>(anchor.X), static_cast<LONG>(anchor.GetBottom())};
    ClientToScreen(hwnd, &pt);
    UINT cmd = TrackPopupMenuEx(hMenu, TPM_RETURNCMD | TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y, hwnd, nullptr);
    DestroyMenu(hMenu);
    if (cmd >= 5000u && (cmd - 5000u) < choices.size()) {
        apply_dropdown_choice(id, choices[cmd - 5000u].value, st);
        InvalidateRect(hwnd, nullptr, FALSE);
    }
}

static LRESULT CALLBACK CyberLauncherWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    auto* st = reinterpret_cast<LauncherUiState*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

    switch (msg) {
        case WM_CREATE: {
            auto* cs = reinterpret_cast<CREATESTRUCTW*>(lParam);
            st = reinterpret_cast<LauncherUiState*>(cs->lpCreateParams);
            SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(st));
            st->hwnd = hwnd;

            st->edit_bg_brush = CreateSolidBrush(RGB(13, 20, 30));
            st->edit_font = CreateFontW(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                        CLEARTYPE_QUALITY, FIXED_PITCH | FF_MODERN, L"Consolas");
            std::wstring iso_w = utf8_to_wide(st->cfg->iso_path);
            st->edit_iso = CreateWindowExW(0, L"EDIT", iso_w.c_str(),
                                           WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                                           116, 131, 680, 18, hwnd,
                                           reinterpret_cast<HMENU>(static_cast<INT_PTR>(IDC_EDIT_ISO_PATH)), cs->hInstance, nullptr);
            SendMessageW(st->edit_iso, WM_SETFONT, reinterpret_cast<WPARAM>(st->edit_font), TRUE);
            st->live_edit_control = true;

            SetTimer(hwnd, kTimerTelemetryId, 33, nullptr);
            return 0;
        }

        case WM_CTLCOLOREDIT: {
            if (st && reinterpret_cast<HWND>(lParam) == st->edit_iso) {
                HDC hdc = reinterpret_cast<HDC>(wParam);
                SetTextColor(hdc, RGB(236, 245, 255));
                SetBkColor(hdc, RGB(13, 20, 30));
                return reinterpret_cast<LRESULT>(st->edit_bg_brush);
            }
            break;
        }

        case WM_ERASEBKGND:
            return 1;

        case WM_MEASUREITEM: {
            auto* mis = reinterpret_cast<MEASUREITEMSTRUCT*>(lParam);
            if (mis && mis->CtlType == ODT_MENU) {
                mis->itemWidth = 320;
                mis->itemHeight = 28;
                return TRUE;
            }
            break;
        }

        case WM_DRAWITEM: {
            auto* dis = reinterpret_cast<DRAWITEMSTRUCT*>(lParam);
            if (st && dis && dis->CtlType == ODT_MENU) {
                size_t idx = (dis->itemID >= 5000u) ? static_cast<size_t>(dis->itemID - 5000u) : 0u;
                bool sel = (dis->itemState & ODS_SELECTED) != 0;
                bool chk = (dis->itemState & ODS_CHECKED) != 0;

                HBRUSH bg = CreateSolidBrush(sel ? RGB(20, 44, 66) : RGB(12, 18, 28));
                FillRect(dis->hDC, &dis->rcItem, bg);
                DeleteObject(bg);
                if (sel) {
                    HBRUSH bar = CreateSolidBrush(RGB(0, 229, 255));
                    RECT brc{dis->rcItem.left, dis->rcItem.top + 2, dis->rcItem.left + 3, dis->rcItem.bottom - 2};
                    FillRect(dis->hDC, &brc, bar);
                    DeleteObject(bar);
                }

                SetBkMode(dis->hDC, TRANSPARENT);
                SetTextColor(dis->hDC, (sel || chk) ? RGB(0, 229, 255) : RGB(224, 236, 248));
                HFONT old_f = st->edit_font ? reinterpret_cast<HFONT>(SelectObject(dis->hDC, st->edit_font)) : nullptr;
                RECT trc = dis->rcItem;
                trc.left += 12;
                std::wstring text = (idx < st->active_menu_labels.size()) ? st->active_menu_labels[idx] : L"";
                if (chk) text = L"* " + text;
                DrawTextW(dis->hDC, text.c_str(), -1, &trc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
                if (old_f) SelectObject(dis->hDC, old_f);
                return TRUE;
            }
            break;
        }

        case WM_TIMER: {
            if (st && wParam == kTimerTelemetryId) {
                st->anim_phase += 0.09f;
                if (st->anim_phase > 628.3f) st->anim_phase = 0.0f;

                std::string pad_backend;
                const XboxInputState xs = PadXInputBridge::poll_any_controller(*st->cfg, &pad_backend);
                if (xs.connected) {
                    st->pad_connected = true;
                    st->pad_backend_label = pad_backend;
                    st->pad_lx = xs.left_stick_x;
                    st->pad_ly = xs.left_stick_y;
                    st->pad_rx = xs.right_stick_x;
                    st->pad_ry = xs.right_stick_y;
                    st->pad_buttons = pack_xinput_mask_from_state(xs);
                    st->pad_lt = xs.left_trigger;
                    st->pad_rt = xs.right_trigger;

                    if (st->listening_zone >= HZ_BIND_A && st->listening_zone <= HZ_BIND_START) {
                        WORD just_pressed = static_cast<WORD>(st->pad_buttons & ~st->listen_prev_buttons);
                        bool lt_now = (st->pad_lt > 0.55f);
                        bool rt_now = (st->pad_rt > 0.55f);
                        bool lt_edge = lt_now && !st->listen_prev_lt;
                        bool rt_edge = rt_now && !st->listen_prev_rt;
                        int captured = detect_captured_xbox_source(just_pressed, lt_edge, rt_edge);
                        if (captured >= 0) {
                            if (int* ptr = config_bind_ptr_for_zone(*st->cfg, st->listening_zone)) {
                                *ptr = captured;
                                st->cfg->control_scheme_preset = 4; // Custom
                                save_launcher_state(*st);
                            }
                            st->listening_zone = HZ_NONE;
                        }
                        st->listen_prev_buttons = st->pad_buttons;
                        st->listen_prev_lt = lt_now;
                        st->listen_prev_rt = rt_now;
                    }
                } else {
                    st->pad_connected = false;
                    st->pad_backend_label = "READY";
                    st->pad_lx = st->pad_ly = st->pad_rx = st->pad_ry = 0.0f;
                    st->pad_buttons = 0;
                    st->pad_lt = st->pad_rt = 0.0f;
                }
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        }

        case WM_KEYDOWN: {
            if (st && wParam == VK_ESCAPE && st->listening_zone != HZ_NONE) {
                st->listening_zone = HZ_NONE;
                InvalidateRect(hwnd, nullptr, FALSE);
                return 0;
            }
            break;
        }

        case WM_RBUTTONDOWN: {
            if (!st) break;
            float mx = static_cast<float>(static_cast<short>(LOWORD(lParam)));
            float my = static_cast<float>(static_cast<short>(HIWORD(lParam)));
            HitZoneId h = hit_test_zones(*st, mx, my);
            if (h >= HZ_BIND_A && h <= HZ_BIND_START) {
                st->listening_zone = h;
                st->listen_prev_buttons = st->pad_buttons;
                st->listen_prev_lt = (st->pad_lt > 0.55f);
                st->listen_prev_rt = (st->pad_rt > 0.55f);
                InvalidateRect(hwnd, nullptr, FALSE);
                return 0;
            }
            break;
        }

        case WM_MOUSEMOVE: {
            if (!st) break;
            float mx = static_cast<float>(static_cast<short>(LOWORD(lParam)));
            float my = static_cast<float>(static_cast<short>(HIWORD(lParam)));
            if (st->dragging_slider != HZ_NONE) {
                update_slider_from_x(*st, st->dragging_slider, mx);
                InvalidateRect(hwnd, nullptr, FALSE);
                return 0;
            }
            HitZoneId h = hit_test_zones(*st, mx, my);
            if (h != st->hover_id) {
                st->hover_id = h;
                SetCursor(LoadCursor(nullptr, (h != HZ_NONE) ? IDC_HAND : IDC_ARROW));
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        }

        case WM_LBUTTONDOWN: {
            if (!st) break;
            float mx = static_cast<float>(static_cast<short>(LOWORD(lParam)));
            float my = static_cast<float>(static_cast<short>(HIWORD(lParam)));
            HitZoneId h = hit_test_zones(*st, mx, my);
            if (h == HZ_SLIDER_DEADZONE || h == HZ_SLIDER_RUMBLE || h == HZ_SLIDER_BRIGHTNESS) {
                st->dragging_slider = h;
                SetCapture(hwnd);
                update_slider_from_x(*st, h, mx);
                InvalidateRect(hwnd, nullptr, FALSE);
            } else if (h == HZ_BROWSE_ISO) {
                wchar_t file_buf[MAX_PATH * 2] = {0};
                OPENFILENAMEW ofn{};
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = hwnd;
                ofn.lpstrFilter = L"GameCube ISO/GCM/DOL (*.iso;*.gcm;*.dol)\0*.iso;*.gcm;*.dol\0All Files (*.*)\0*.*\0";
                ofn.lpstrFile = file_buf;
                ofn.nMaxFile = MAX_PATH * 2;
                ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
                if (GetOpenFileNameW(&ofn)) {
                    SetWindowTextW(st->edit_iso, file_buf);
                    save_launcher_state(*st);
                    InvalidateRect(hwnd, nullptr, FALSE);
                }
            } else if (h == HZ_DD_RESOLUTION || h == HZ_DD_DISPLAY_MODE || h == HZ_DD_ANTIALIASING ||
                       h == HZ_DD_ASPECT || h == HZ_DD_BACKEND || h == HZ_DD_ANISO || h == HZ_DD_LANGUAGE ||
                       (h >= HZ_BIND_A && h <= HZ_BIND_GUIDE)) {
                st->listening_zone = HZ_NONE;
                show_cyber_dropdown_menu(hwnd, *st, h);
                save_launcher_state(*st);
            } else if (h == HZ_SW_VSYNC) {
                st->cfg->vsync = !st->cfg->vsync;
                save_launcher_state(*st);
                InvalidateRect(hwnd, nullptr, FALSE);
            } else if (h == HZ_SW_LIMIT_FPS) {
                st->cfg->limit_fps_60 = !st->cfg->limit_fps_60;
                save_launcher_state(*st);
                InvalidateRect(hwnd, nullptr, FALSE);
            } else if (h == HZ_SW_HD_FONT) {
                st->cfg->enable_hd_chinese_font = !st->cfg->enable_hd_chinese_font;
                save_launcher_state(*st);
                InvalidateRect(hwnd, nullptr, FALSE);
            } else if (h == HZ_SW_TOOLS_REL) {
                st->cfg->load_tools_rel_debug = !st->cfg->load_tools_rel_debug;
                save_launcher_state(*st);
                InvalidateRect(hwnd, nullptr, FALSE);
            } else if (h == HZ_SW_DEFLICKER) {
                st->cfg->disable_copy_deflicker = !st->cfg->disable_copy_deflicker;
                save_launcher_state(*st);
                InvalidateRect(hwnd, nullptr, FALSE);
            } else if (h == HZ_SW_CHEAT_GOD) {
                st->cfg->cheat_god_mode = !st->cfg->cheat_god_mode;
                save_launcher_state(*st);
                InvalidateRect(hwnd, nullptr, FALSE);
            } else if (h == HZ_SW_CHEAT_ENERGY) {
                st->cfg->cheat_infinite_energy = !st->cfg->cheat_infinite_energy;
                save_launcher_state(*st);
                InvalidateRect(hwnd, nullptr, FALSE);
            } else if (h == HZ_SW_CHEAT_CREDITS) {
                st->cfg->cheat_infinite_credits = !st->cfg->cheat_infinite_credits;
                save_launcher_state(*st);
                InvalidateRect(hwnd, nullptr, FALSE);
            } else if (h == HZ_SW_CHEAT_SUITS) {
                st->cfg->cheat_unlock_all_suits = !st->cfg->cheat_unlock_all_suits;
                save_launcher_state(*st);
                InvalidateRect(hwnd, nullptr, FALSE);
            } else if (h >= HZ_PRESET_A && h <= HZ_PRESET_D) {
                st->listening_zone = HZ_NONE;
                st->cfg->apply_control_preset(static_cast<int>(h - HZ_PRESET_A));
                save_launcher_state(*st);
                InvalidateRect(hwnd, nullptr, FALSE);
            } else if (h == HZ_BTN_LAUNCH) {
                save_launcher_state(*st);
                st->launched = true;
                PN03_LOGF(LogLevel::Info, "LAUNCHER", "LAUNCH button clicked -> launching engine (iso=%s cfg=%s)",
                          st->cfg->iso_path.c_str(), st->config_path.c_str());
                DestroyWindow(hwnd);
            }
            return 0;
        }

        case WM_LBUTTONUP: {
            if (st && st->dragging_slider != HZ_NONE) {
                st->dragging_slider = HZ_NONE;
                ReleaseCapture();
                save_launcher_state(*st);
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        }

        case WM_PAINT: {
            if (!st) break;
            PAINTSTRUCT ps{};
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT cr{};
            GetClientRect(hwnd, &cr);
            int cw = (std::max)(1, static_cast<int>(cr.right - cr.left));
            int ch = (std::max)(1, static_cast<int>(cr.bottom - cr.top));

            {
                Gdiplus::Bitmap back_buf(cw, ch, PixelFormat32bppARGB);
                Gdiplus::Graphics g_mem(&back_buf);
                g_mem.ScaleTransform(static_cast<float>(cw) / static_cast<float>(kClientW),
                                     static_cast<float>(ch) / static_cast<float>(kClientH));
                render_launcher_to_graphics(g_mem, kClientW, kClientH, *st);

                Gdiplus::Graphics g_scr(hdc);
                g_scr.DrawImage(&back_buf, 0, 0, cw, ch);
            }
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_CLOSE:
            if (st) {
                save_launcher_state(*st);
            }
            DestroyWindow(hwnd);
            return 0;

        case WM_DESTROY:
            KillTimer(hwnd, kTimerTelemetryId);
            if (st) {
                if (st->edit_bg_brush) { DeleteObject(st->edit_bg_brush); st->edit_bg_brush = nullptr; }
                if (st->edit_font) { DeleteObject(st->edit_font); st->edit_font = nullptr; }
                st->closed = true;
            }
            PostQuitMessage(0);
            return 0;

        default:
            break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static bool write_gdiplus_bitmap_to_bmp24(Gdiplus::Bitmap& bmp, const std::string& bmp_path) {
    const UINT w = bmp.GetWidth();
    const UINT h = bmp.GetHeight();
    if (w == 0 || h == 0) return false;

    Gdiplus::Rect lock_rc(0, 0, static_cast<INT>(w), static_cast<INT>(h));
    Gdiplus::BitmapData bd{};
    if (bmp.LockBits(&lock_rc, Gdiplus::ImageLockModeRead, PixelFormat24bppRGB, &bd) != Gdiplus::Ok) {
        return false;
    }

    const uint32_t row_bytes = ((w * 3u + 3u) / 4u) * 4u;
    const uint32_t img_size = row_bytes * h;

    std::error_code ec;
    fs::path out_p = fs::path(bmp_path);
    if (out_p.has_parent_path()) {
        fs::create_directories(out_p.parent_path(), ec);
    }

    std::ofstream ofs(out_p, std::ios::binary | std::ios::trunc);
    if (!ofs.is_open()) {
        bmp.UnlockBits(&bd);
        return false;
    }

    BITMAPFILEHEADER bfh{};
    bfh.bfType = 0x4D42;
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    bfh.bfSize = bfh.bfOffBits + img_size;

    BITMAPINFOHEADER bih{};
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = static_cast<LONG>(w);
    bih.biHeight = static_cast<LONG>(h); // positive = bottom-up DIB
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = BI_RGB;
    bih.biSizeImage = img_size;

    ofs.write(reinterpret_cast<const char*>(&bfh), sizeof(bfh));
    ofs.write(reinterpret_cast<const char*>(&bih), sizeof(bih));

    std::vector<uint8_t> row_buf(row_bytes, 0);
    const uint8_t* src_base = reinterpret_cast<const uint8_t*>(bd.Scan0);
    for (UINT y = 0; y < h; ++y) {
        const UINT src_y = h - 1u - y;
        const uint8_t* src_row = src_base + static_cast<ptrdiff_t>(src_y) * bd.Stride;
        std::memcpy(row_buf.data(), src_row, w * 3u);
        ofs.write(reinterpret_cast<const char*>(row_buf.data()), static_cast<std::streamsize>(row_bytes));
    }

    ofs.close();
    bmp.UnlockBits(&bd);
    return ofs.good();
}

} // namespace

bool CyberLauncherUI::run_modal_launcher_window(const std::string& iso_mount_summary) {
    GdiplusSessionGuard gdip_guard;
    if (!gdip_guard.active) return true;

    LauncherUiState state{};
    state.cfg = &cfg_;
    state.config_path = config_path_;
    state.iso_mount_summary = iso_mount_summary;

    std::wstring crest_path = resolve_ui_asset_path(L"pn03_header_crest.png");
    std::wstring vanessa_path = resolve_ui_asset_path(L"pn03_header_vanessa.png");
    if (!crest_path.empty()) state.img_crest = std::make_unique<Gdiplus::Image>(crest_path.c_str());
    if (!vanessa_path.empty()) state.img_vanessa = std::make_unique<Gdiplus::Image>(vanessa_path.c_str());

    HINSTANCE hInst = GetModuleHandleW(nullptr);
    const wchar_t* kClassName = L"PN03AegisCyberLauncherWnd";
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = CyberLauncherWndProc;
    wc.hInstance = hInst;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = kClassName;

    HICON app_icon = nullptr;
    if (!crest_path.empty()) {
        Gdiplus::Bitmap bmp_icon(crest_path.c_str());
        bmp_icon.GetHICON(&app_icon);
    }
    wc.hIcon = app_icon;
    RegisterClassExW(&wc);

    DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    DWORD dwExStyle = WS_EX_APPWINDOW;
    RECT wr{0, 0, kClientW, kClientH};
    AdjustWindowRectEx(&wr, dwStyle, FALSE, dwExStyle);
    int win_w = wr.right - wr.left;
    int win_h = wr.bottom - wr.top;

    RECT wa{};
    SystemParametersInfoW(SPI_GETWORKAREA, 0, &wa, 0);
    int pos_x = wa.left + ((wa.right - wa.left) - win_w) / 2;
    int pos_y = wa.top + ((wa.bottom - wa.top) - win_h) / 2;

    HWND hwnd = CreateWindowExW(
        dwExStyle, kClassName, L"P.N.03 // GPNE08 WINDOWS x64 HD LAUNCHER",
        dwStyle | WS_VISIBLE, pos_x, pos_y, win_w, win_h,
        nullptr, nullptr, hInst, &state);
    if (!hwnd) return true;

    enable_dark_titlebar(hwnd);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (state.edit_iso && msg.hwnd == state.edit_iso && msg.message == WM_KEYDOWN && msg.wParam == VK_RETURN) {
            SetFocus(hwnd);
            continue;
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    // Drain any residual WM_QUIT so the subsequent D3D11 game loop never exits prematurely on Frame 0
    MSG quit_msg{};
    while (PeekMessageW(&quit_msg, nullptr, WM_QUIT, WM_QUIT, PM_REMOVE)) {}

    if (app_icon) DestroyIcon(app_icon);
    return state.launched;
}

bool CyberLauncherUI::render_launcher_preview_bmp(const std::string& bmp_path, const std::string& iso_mount_summary) {
    GdiplusSessionGuard gdip_guard;
    if (!gdip_guard.active) return false;

    LauncherUiState state{};
    state.cfg = &cfg_;
    state.config_path = config_path_;
    state.iso_mount_summary = iso_mount_summary;
    state.live_edit_control = false;
    state.pad_connected = true;
    state.anim_phase = 0.55f;

    std::wstring crest_path = resolve_ui_asset_path(L"pn03_header_crest.png");
    std::wstring vanessa_path = resolve_ui_asset_path(L"pn03_header_vanessa.png");
    if (!crest_path.empty()) state.img_crest = std::make_unique<Gdiplus::Image>(crest_path.c_str());
    if (!vanessa_path.empty()) state.img_vanessa = std::make_unique<Gdiplus::Image>(vanessa_path.c_str());

    Gdiplus::Bitmap canvas(kClientW, kClientH, PixelFormat24bppRGB);
    {
        Gdiplus::Graphics g(&canvas);
        render_launcher_to_graphics(g, kClientW, kClientH, state);
    }
    return write_gdiplus_bitmap_to_bmp24(canvas, bmp_path);
}

#else

bool CyberLauncherUI::run_modal_launcher_window(const std::string& iso_mount_summary) {
    (void)iso_mount_summary;
    return true;
}

bool CyberLauncherUI::render_launcher_preview_bmp(const std::string& bmp_path, const std::string& iso_mount_summary) {
    (void)bmp_path;
    (void)iso_mount_summary;
    return false;
}

#endif

} // namespace pn03

#pragma once

#include "pn03_config.hpp"
#include "pn03_gx_3d_interface.hpp"

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <commdlg.h>
#endif

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace pn03 {

struct alignas(16) GXSceneConstantsCPU {
    float    uProjection[4][4];
    float    uModelView[4][4];
    float    uTevColor0[4];
    float    uKonstColor[4];
    float    uViewportSize[2];
    uint32_t uEnableAlphaTest;
    float    uAlphaRef;
    uint32_t uTevMode;
    float    uTevScale;
    uint32_t uStage1Mode;
    float    uPad0;
};

struct alignas(16) FxaaConstantsCPU {
    float uInvScreenSize[2];
    float uSubpixQuality;
    float uEdgeThreshold;
    float uBrightness;
    float uGamma;
    float uPad[2];
};

struct HostViewportRect {
    float x      = 0.0f;
    float y      = 0.0f;
    float width  = 0.0f;
    float height = 0.0f;
};

constexpr size_t kHostMaxDynamicVertices = 524288u;
constexpr size_t kHostMaxDynamicIndices  = 1572864u;

inline float resolve_disp_gamma_value(uint32_t disp_copy_gamma) noexcept {
    return (disp_copy_gamma == 1u) ? 1.35f : ((disp_copy_gamma >= 2u) ? 1.65f : 1.0f);
}

inline HostViewportRect compute_output_viewport_rect(
    AspectRatioMode mode,
    uint32_t target_w,
    uint32_t target_h
) noexcept {
    const float out_w = static_cast<float>((std::max)(1u, target_w));
    const float out_h = static_cast<float>((std::max)(1u, target_h));
    const float win_aspect = out_w / out_h;
    const float tgt_aspect = resolve_target_aspect_ratio(mode);
    HostViewportRect vp{};
    if (std::fabs(win_aspect - tgt_aspect) < 0.01f) {
        vp.x      = 0.0f;
        vp.y      = 0.0f;
        vp.width  = out_w;
        vp.height = out_h;
    } else if (win_aspect > tgt_aspect) {
        vp.width  = out_h * tgt_aspect;
        vp.height = out_h;
        vp.x      = (out_w - vp.width) * 0.5f;
        vp.y      = 0.0f;
    } else {
        vp.width  = out_w;
        vp.height = out_w / tgt_aspect;
        vp.x      = 0.0f;
        vp.y      = (out_h - vp.height) * 0.5f;
    }
    return vp;
}

inline void compute_efb_dimensions(
    const RuntimeConfig& cfg,
    uint32_t swapchain_height,
    uint32_t& out_efb_w,
    uint32_t& out_efb_h
) noexcept {
    const float aspect = resolve_target_aspect_ratio(cfg.aspect_ratio);
    const uint32_t scale = (std::max)(1u, (std::min)(6u, cfg.internal_scale_factor));
    uint32_t target_h = (std::min)(2880u, 480u * scale);
    // Avoid fractional non-integer downsampling while preserving <=1x or exact integer SSAA
    if (swapchain_height > 0u && target_h > swapchain_height && (target_h % swapchain_height) != 0u) {
        target_h = swapchain_height;
    }
    out_efb_h = target_h;
    out_efb_w = (std::max)(16u, (static_cast<uint32_t>(static_cast<float>(out_efb_h) * aspect + 0.5f) + 1u) & ~1u);
}

inline void fill_ortho_rect(
    float proj[4][4],
    float left,
    float top,
    float width,
    float height
) noexcept {
    const float w = (width > 1.0f) ? width : 640.0f;
    const float h = (height > 1.0f) ? height : 480.0f;
    std::memset(proj, 0, 16u * sizeof(float));
    proj[0][0] =  2.0f / w;
    proj[0][3] = -1.0f - (2.0f * left) / w;
    proj[1][1] = -2.0f / h;
    proj[1][3] =  1.0f + (2.0f * top) / h;
    proj[2][2] =  1.0f / 2000.0f;
    proj[2][3] = -0.5f;
    proj[3][3] =  1.0f;
}

inline void fill_centered_43_overlay_ortho_rect(
    float proj[4][4],
    float src_x,
    float src_y,
    float src_w,
    float src_h,
    float out_w,
    float out_h
) noexcept {
    const float w = (src_w > 1.0f) ? src_w : 640.0f;
    const float h = (src_h > 1.0f) ? src_h : 480.0f;
    const float win_aspect = (out_h > 1.0f) ? (out_w / out_h) : (4.0f / 3.0f);
    constexpr float kBase43Aspect = 4.0f / 3.0f;
    if (win_aspect > kBase43Aspect + 0.01f) {
        const float span_w = w * (win_aspect / kBase43Aspect);
        const float centered_left = src_x - (span_w - w) * 0.5f;
        fill_ortho_rect(proj, centered_left, src_y, span_w, h);
    } else if (win_aspect < kBase43Aspect - 0.01f && win_aspect > 0.1f) {
        const float span_h = h * (kBase43Aspect / win_aspect);
        const float centered_top = src_y - (span_h - h) * 0.5f;
        fill_ortho_rect(proj, src_x, centered_top, w, span_h);
    } else {
        fill_ortho_rect(proj, src_x, src_y, w, h);
    }
}

inline bool ortho_batch_covers_full_clip_rect(
    const GXDrawBatch& batch,
    const GXVertex* verts,
    size_t vert_count,
    const uint32_t* indices,
    size_t index_count,
    float src_x,
    float src_y,
    float src_w,
    float src_h
) noexcept {
    if (batch.proj_type != 1u || !verts || !indices || batch.index_count < 4u || batch.index_count > 36u) {
        return false;
    }
    if (static_cast<size_t>(batch.index_offset) + static_cast<size_t>(batch.index_count) > index_count) {
        return false;
    }

    float proj[4][4]{};
    std::memcpy(proj, batch.proj_mtx, sizeof(proj));
    if (std::fabs(proj[0][0] - 1.0f) < 1e-4f && std::fabs(proj[1][1] - 1.0f) < 1e-4f) {
        fill_ortho_rect(proj, src_x, src_y, src_w, src_h);
    }

    float min_nx =  1e9f;
    float max_nx = -1e9f;
    float min_ny =  1e9f;
    float max_ny = -1e9f;
    bool  any    = false;

    for (uint32_t i = 0; i < batch.index_count; ++i) {
        const uint32_t vi = indices[static_cast<size_t>(batch.index_offset) + i];
        if (vi >= vert_count) {
            return false;
        }
        const float px = verts[vi].pos[0];
        const float py = verts[vi].pos[1];
        const float pz = verts[vi].pos[2];
        const float cx = proj[0][0] * px + proj[0][1] * py + proj[0][2] * pz + proj[0][3];
        const float cy = proj[1][0] * px + proj[1][1] * py + proj[1][2] * pz + proj[1][3];
        const float cw = proj[3][0] * px + proj[3][1] * py + proj[3][2] * pz + proj[3][3];
        const float inv_w = (std::fabs(cw) > 1e-6f) ? (1.0f / cw) : 1.0f;
        const float nx = cx * inv_w;
        const float ny = cy * inv_w;
        min_nx = (std::min)(min_nx, nx);
        max_nx = (std::max)(max_nx, nx);
        min_ny = (std::min)(min_ny, ny);
        max_ny = (std::max)(max_ny, ny);
        any = true;
    }
    return any && min_nx <= -0.95f && max_nx >= 0.95f && min_ny <= -0.95f && max_ny >= 0.95f;
}

inline bool is_fullscreen_untextured_ortho_quad(
    const GXDrawBatch& batch,
    const GXVertex* verts,
    size_t vert_count,
    const uint32_t* indices,
    size_t index_count,
    float src_x,
    float src_y,
    float src_w,
    float src_h
) noexcept {
    if (batch.has_texture || batch.has_stage1_tex || batch.index_count > 24u) {
        return false;
    }
    return ortho_batch_covers_full_clip_rect(
        batch, verts, vert_count, indices, index_count, src_x, src_y, src_w, src_h);
}

inline bool is_fullscreen_ortho_effect_quad(
    const GXDrawBatch& batch,
    const GXVertex* verts,
    size_t vert_count,
    const uint32_t* indices,
    size_t index_count,
    float src_x,
    float src_y,
    float src_w,
    float src_h
) noexcept {
    if (is_fullscreen_untextured_ortho_quad(
            batch, verts, vert_count, indices, index_count, src_x, src_y, src_w, src_h)) {
        return true;
    }
    // Half-res EFB copy post-filter passes (e.g. 256x224 RGBA8 fullscreen bloom/glare overlay)
    const bool is_efb_filter_tex =
        batch.has_texture && !batch.has_stage1_tex && batch.blend_type != 0u &&
        batch.texture.format == 6u && batch.texture.width <= 320u && batch.texture.height <= 240u;
    if (!is_efb_filter_tex) {
        return false;
    }
    return ortho_batch_covers_full_clip_rect(
        batch, verts, vert_count, indices, index_count, src_x, src_y, src_w, src_h);
}

inline bool should_ortho_batch_fill_efb(
    const GXDrawBatch& batch,
    const GXVertex* verts,
    size_t vert_count,
    const uint32_t* indices,
    size_t index_count,
    float src_x,
    float src_y,
    float src_w,
    float src_h
) noexcept {
    if (batch.proj_type != 1u) {
        return true;
    }
    // Depth-tested non-depth-writing ortho sprites are world-space particles / post-effects (not 2D HUD)
    if (batch.z_enable && !batch.z_write) {
        return true;
    }
    return is_fullscreen_ortho_effect_quad(
        batch, verts, vert_count, indices, index_count, src_x, src_y, src_w, src_h);
}

inline HostViewportRect compute_2d_ortho_efb_bounds(
    uint32_t efb_width,
    uint32_t efb_height,
    bool full_efb_width
) noexcept {
    const float ew = static_cast<float>((std::max)(1u, efb_width));
    const float eh = static_cast<float>((std::max)(1u, efb_height));
    if (full_efb_width) {
        return {0.0f, 0.0f, ew, eh};
    }
    constexpr float kBase43Aspect = 4.0f / 3.0f;
    const float efb_aspect = ew / eh;
    if (efb_aspect > kBase43Aspect + 0.01f) {
        const float ui_w = (std::min)(ew, eh * kBase43Aspect);
        const float ui_x = (ew - ui_w) * 0.5f;
        return {ui_x, 0.0f, ui_w, eh};
    }
    if (efb_aspect < kBase43Aspect - 0.01f) {
        const float ui_h = (std::min)(eh, ew / kBase43Aspect);
        const float ui_y = (eh - ui_h) * 0.5f;
        return {0.0f, ui_y, ew, ui_h};
    }
    return {0.0f, 0.0f, ew, eh};
}

inline void enable_host_dpi_awareness() noexcept {
#ifdef _WIN32
    static bool s_attempted = false;
    if (s_attempted) return;
    s_attempted = true;
    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    if (user32) {
        using FnSetDpiCtx = BOOL(WINAPI*)(HANDLE);
        auto fn = reinterpret_cast<FnSetDpiCtx>(GetProcAddress(user32, "SetProcessDpiAwarenessContext"));
        if (fn) {
            if (fn(reinterpret_cast<HANDLE>(static_cast<INT_PTR>(-4))) ||
                fn(reinterpret_cast<HANDLE>(static_cast<INT_PTR>(-3)))) {
                return;
            }
        }
    }
    SetProcessDPIAware();
#endif
}

#ifdef _WIN32
inline HICON load_bmp_as_app_icon(const char* bmp_path) noexcept {
    HBITMAP hbm = static_cast<HBITMAP>(LoadImageA(nullptr, bmp_path, IMAGE_BITMAP, 32, 32, LR_LOADFROMFILE));
    if (!hbm) return nullptr;
    HBITMAP hmask = CreateBitmap(32, 32, 1, 1, nullptr);
    ICONINFO ii{};
    ii.fIcon    = TRUE;
    ii.hbmMask  = hmask;
    ii.hbmColor = hbm;
    HICON hicon = CreateIconIndirect(&ii);
    if (hmask) DeleteObject(hmask);
    DeleteObject(hbm);
    return hicon;
}

inline bool rasterize_utf8_text_rgba8(
    const std::string& utf8_text,
    int& out_w,
    int& out_h,
    std::vector<uint8_t>& out_rgba
) {
    if (utf8_text.empty()) return false;
    const int wlen = MultiByteToWideChar(CP_UTF8, 0, utf8_text.c_str(), -1, nullptr, 0);
    if (wlen <= 1) return false;
    std::wstring wstr(static_cast<size_t>(wlen), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, utf8_text.c_str(), -1, wstr.data(), wlen);

    HDC hdc = CreateCompatibleDC(nullptr);
    if (!hdc) return false;
    HFONT hfont = CreateFontW(
        -24, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Microsoft YaHei"
    );
    HGDIOBJ old_font = SelectObject(hdc, hfont);

    RECT rc{0, 0, 540, 160};
    DrawTextW(hdc, wstr.c_str(), -1, &rc, DT_CALCRECT | DT_WORDBREAK | DT_NOPREFIX);
    const int bmp_w = (std::clamp)(static_cast<int>(rc.right - rc.left) + 8, 16, 600);
    const int bmp_h = (std::clamp)(static_cast<int>(rc.bottom - rc.top) + 8, 16, 200);

    BITMAPINFO bmi{};
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = bmp_w;
    bmi.bmiHeader.biHeight      = -bmp_h; // top-down
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* bits = nullptr;
    HBITMAP hbm = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!hbm || !bits) {
        if (hbm) DeleteObject(hbm);
        SelectObject(hdc, old_font);
        DeleteObject(hfont);
        DeleteDC(hdc);
        return false;
    }
    HGDIOBJ old_bm = SelectObject(hdc, hbm);

    std::memset(bits, 0, static_cast<size_t>(bmp_w) * bmp_h * 4u);
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255, 255, 255));
    RECT draw_rc{4, 4, bmp_w - 4, bmp_h - 4};
    DrawTextW(hdc, wstr.c_str(), -1, &draw_rc, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX);

    out_rgba.assign(static_cast<size_t>(bmp_w) * bmp_h * 4u, 0u);
    const uint8_t* src = static_cast<const uint8_t*>(bits);
    for (int i = 0; i < bmp_w * bmp_h; ++i) {
        const uint8_t lum = (std::max)({src[i * 4 + 0], src[i * 4 + 1], src[i * 4 + 2]});
        out_rgba[i * 4 + 0] = 255u;
        out_rgba[i * 4 + 1] = 255u;
        out_rgba[i * 4 + 2] = 255u;
        out_rgba[i * 4 + 3] = lum;
    }

    SelectObject(hdc, old_bm);
    SelectObject(hdc, old_font);
    DeleteObject(hbm);
    DeleteObject(hfont);
    DeleteDC(hdc);

    out_w = bmp_w;
    out_h = bmp_h;
    return true;
}
#endif

inline bool write_bmp24_from_rgba8(
    const std::string& path,
    uint32_t width,
    uint32_t height,
    const uint8_t* pixels,
    size_t row_pitch_bytes,
    bool bgra_input = false
) {
    if (!pixels || width == 0u || height == 0u || row_pitch_bytes < static_cast<size_t>(width) * 4u) {
        return false;
    }
    const uint32_t row_stride = (width * 3u + 3u) & ~3u;
    const uint32_t img_bytes  = row_stride * height;
    const uint32_t off_bits   = 54u;
    const uint32_t file_size  = off_bits + img_bytes;

    std::error_code ec;
    std::filesystem::path fpath(path);
    if (fpath.has_parent_path()) {
        std::filesystem::create_directories(fpath.parent_path(), ec);
    }
    std::ofstream out(path, std::ios::binary);
    if (!out) {
        return false;
    }

    uint8_t hdr[54]{};
    auto put_u16 = [&](size_t off, uint16_t v) {
        hdr[off + 0] = static_cast<uint8_t>(v & 0xFFu);
        hdr[off + 1] = static_cast<uint8_t>((v >> 8) & 0xFFu);
    };
    auto put_u32 = [&](size_t off, uint32_t v) {
        hdr[off + 0] = static_cast<uint8_t>(v & 0xFFu);
        hdr[off + 1] = static_cast<uint8_t>((v >> 8) & 0xFFu);
        hdr[off + 2] = static_cast<uint8_t>((v >> 16) & 0xFFu);
        hdr[off + 3] = static_cast<uint8_t>((v >> 24) & 0xFFu);
    };
    put_u16(0,  0x4D42u); // 'BM'
    put_u32(2,  file_size);
    put_u32(10, off_bits);
    put_u32(14, 40u);     // BITMAPINFOHEADER size
    put_u32(18, width);
    put_u32(22, height);  // positive = bottom-up BMP
    put_u16(26, 1u);      // planes
    put_u16(28, 24u);     // 24bpp
    put_u32(34, img_bytes);
    out.write(reinterpret_cast<const char*>(hdr), sizeof(hdr));

    std::vector<uint8_t> row(row_stride, 0u);
    for (int32_t y = static_cast<int32_t>(height) - 1; y >= 0; --y) {
        const uint8_t* src_row = pixels + static_cast<size_t>(y) * row_pitch_bytes;
        for (uint32_t x = 0; x < width; ++x) {
            const uint8_t c0 = src_row[x * 4u + 0u];
            const uint8_t c1 = src_row[x * 4u + 1u];
            const uint8_t c2 = src_row[x * 4u + 2u];
            if (bgra_input) {
                row[x * 3u + 0u] = c0; // B
                row[x * 3u + 1u] = c1; // G
                row[x * 3u + 2u] = c2; // R
            } else {
                row[x * 3u + 0u] = c2; // B
                row[x * 3u + 1u] = c1; // G
                row[x * 3u + 2u] = c0; // R
            }
        }
        out.write(reinterpret_cast<const char*>(row.data()), static_cast<std::streamsize>(row_stride));
    }
    return static_cast<bool>(out);
}

#ifdef _WIN32
inline bool show_iso_picker_if_empty(RuntimeConfig& cfg) {
    if (cfg.skip_launcher_gui && !cfg.iso_path.empty()) {
        return true;
    }
    if (cfg.iso_path.empty()) {
        char file_buf[MAX_PATH] = {0};
        OPENFILENAMEA ofn{};
        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFilter = "GameCube ISO/GCM Disc Images (*.iso;*.gcm)\0*.iso;*.gcm\0All Files (*.*)\0*.*\0";
        ofn.lpstrFile   = file_buf;
        ofn.nMaxFile    = MAX_PATH;
        ofn.lpstrTitle  = "P.N.03 (GPNE08) Windows Port - \xE8\xAF\xB7\xE9\x80\x89\xE6\x8B\xA9\xE5\xAF\xBC\xE5\x85\xA5\xE5\x8E\x9F\xE7\x89\x88 P.N.03 ISO \xE9\x95\x9C\xE5\x83\x8F\xE6\x96\x87\xE4\xBB\xB6";
        ofn.Flags       = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetOpenFileNameA(&ofn)) {
            cfg.iso_path = file_buf;
            cfg.save_to_json("config/pn03_settings.json");
        } else {
            return false;
        }
    }
    return true;
}

inline HWND create_pn03_win32_window(
    const RuntimeConfig& cfg,
    bool hidden_window,
    const wchar_t* class_name,
    WNDPROC wnd_proc,
    void* user_data,
    uint32_t& out_client_w,
    uint32_t& out_client_h
) {
    enable_host_dpi_awareness();
    HICON hicon = load_bmp_as_app_icon("assets/ui/pn03_icon_32x32.bmp");
    WNDCLASSEXW wc{};
    wc.cbSize        = sizeof(WNDCLASSEXW);
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = wnd_proc;
    wc.hInstance     = GetModuleHandleW(nullptr);
    wc.hIcon         = hicon;
    wc.hIconSm       = hicon;
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = class_name;
    RegisterClassExW(&wc);

    const DWORD style = (cfg.window_mode == WindowMode::Windowed) ? WS_OVERLAPPEDWINDOW : WS_POPUP;
    const DWORD vis_flag = hidden_window ? 0u : WS_VISIBLE;

    MONITORINFO mi{};
    mi.cbSize = sizeof(mi);
    GetMonitorInfoW(MonitorFromPoint({0, 0}, MONITOR_DEFAULTTOPRIMARY), &mi);
    const int mon_w  = (std::max)(640, static_cast<int>(mi.rcMonitor.right - mi.rcMonitor.left));
    const int mon_h  = (std::max)(480, static_cast<int>(mi.rcMonitor.bottom - mi.rcMonitor.top));
    const int work_w = (std::max)(640, static_cast<int>(mi.rcWork.right - mi.rcWork.left));
    const int work_h = (std::max)(480, static_cast<int>(mi.rcWork.bottom - mi.rcWork.top));

    int pos_x = mi.rcMonitor.left;
    int pos_y = mi.rcMonitor.top;
    int win_w = mon_w;
    int win_h = mon_h;
    if (cfg.window_mode == WindowMode::Windowed) {
        int client_w = static_cast<int>(cfg.render_width);
        int client_h = static_cast<int>(cfg.render_height);
        if (client_w > work_w - 32 || client_h > work_h - 64) {
            const double sx = static_cast<double>(work_w - 32) / static_cast<double>(client_w);
            const double sy = static_cast<double>(work_h - 64) / static_cast<double>(client_h);
            const double sc = (std::min)(sx, sy);
            client_w = (std::max)(640, static_cast<int>(client_w * sc));
            client_h = (std::max)(480, static_cast<int>(client_h * sc));
        }
        RECT wr{0, 0, client_w, client_h};
        AdjustWindowRectEx(&wr, style, FALSE, 0);
        win_w = wr.right - wr.left;
        win_h = wr.bottom - wr.top;
        pos_x = mi.rcWork.left + (work_w - win_w) / 2;
        pos_y = mi.rcWork.top  + (work_h - win_h) / 2;
    }

    HWND hwnd = CreateWindowExW(
        0,
        wc.lpszClassName,
        L"P.N.03 (GPNE08) - Windows HD Recompiled Port [WASD/Controller | Esc: Pause | X/Alt+F4: Exit]",
        style | vis_flag,
        pos_x, pos_y, win_w, win_h,
        nullptr, nullptr, wc.hInstance, nullptr
    );
    if (!hwnd) {
        return nullptr;
    }
    SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(user_data));
    if (!hidden_window) {
        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);
        SetForegroundWindow(hwnd);
        SetFocus(hwnd);
    }

    out_client_w = cfg.render_width;
    out_client_h = cfg.render_height;
    if (!hidden_window && cfg.window_mode != WindowMode::ExclusiveFullscreen) {
        RECT cr{};
        if (GetClientRect(hwnd, &cr) && cr.right > cr.left && cr.bottom > cr.top) {
            out_client_w = static_cast<uint32_t>(cr.right - cr.left);
            out_client_h = static_cast<uint32_t>(cr.bottom - cr.top);
        }
    }
    return hwnd;
}

inline bool pump_win32_window_messages(HWND hwnd, bool& close_requested, std::string* out_stop_reason = nullptr) {
    if (close_requested) {
        if (out_stop_reason) *out_stop_reason = "pump_messages observed close_requested_=true";
        return false;
    }
    MSG msg{};
    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            if (out_stop_reason) *out_stop_reason = "WM_QUIT received, stopping frame loop";
            close_requested = true;
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
        if (close_requested) {
            if (out_stop_reason) *out_stop_reason = "Window close requested during message dispatch";
            return false;
        }
    }
    if (hwnd && !IsWindow(hwnd)) {
        if (out_stop_reason) *out_stop_reason = "Window handle no longer valid in pump_messages";
        close_requested = true;
        return false;
    }
    return true;
}
#endif

} // namespace pn03

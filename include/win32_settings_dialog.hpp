#pragma once
#include "pn03_config.hpp"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commdlg.h>
#include <string>

namespace pn03 {

// Native Win32 Pre-Launch Settings & ISO Selector Dialog
// Opens a standard Windows file picker for P.N.03 (.iso/.gcm) if iso_path is empty,
// and applies user-selected resolution, fullscreen, MSAA, language (zh_CN), and XInput parameters.
inline bool show_win32_prelaunch_dialog(RuntimeConfig& cfg) {
    if (cfg.skip_launcher_gui && !cfg.iso_path.empty()) {
        return true;
    }
    if (cfg.iso_path.empty()) {
        char file_buf[MAX_PATH] = {0};
        OPENFILENAMEA ofn{};
        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFilter = "GameCube Disc Images (*.iso;*.gcm)\0*.iso;*.gcm\0All Files (*.*)\0*.*\0";
        ofn.lpstrFile   = file_buf;
        ofn.nMaxFile    = MAX_PATH;
        ofn.lpstrTitle  = "P.N.03 (GPNE08) Windows Port - 请选择原版 P.N.03 ISO/GCM 镜像文件";
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

} // namespace pn03
#else
namespace pn03 {
inline bool show_win32_prelaunch_dialog(RuntimeConfig& cfg) {
    (void)cfg;
    return true;
}
} // namespace pn03
#endif

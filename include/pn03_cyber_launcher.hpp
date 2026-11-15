#pragma once
#include "pn03_config.hpp"
#include <string>

namespace pn03 {

// ============================================================================
// P.N.03 Cyber-Minimalist Windows GUI Launcher (Built 1:1 to Visual Design Reference)
// Provides:
//   1. Native Win32 Dark-Obsidian + Cyan (#00E5FF) + Orange (#FF6D00) 3-Card GUI Dialog
//      ("3D GRAPHICS & DISPLAY", "LOCALIZATION & SYSTEM", "XBOX XINPUT CONTROLLER")
//   2. Interactive HTML5/Canvas/WebView2 Launcher UI (`assets/ui/pn03_launcher_ui.html`)
// ============================================================================
class CyberLauncherUI {
public:
    explicit CyberLauncherUI(RuntimeConfig& cfg) : cfg_(cfg) {}

    // Opens the native Win32 3-Card Sci-Fi Launcher Window on Windows (_WIN32)
    // Returns true if user clicked "LAUNCH P.N.03 ENGINE", false if closed/cancelled.
    bool run_modal_launcher_window(const std::string& iso_mount_summary = "MOUNTED - 700 FILES");

    // Generates a real-time diagnostic status readout string matching the bottom-left HUD panel
    std::string build_diagnostic_readout(size_t fst_files = 700, size_t total_syms = 9530, size_t recomp_funcs = 6340) const;

    // Renders the 3-card sci-fi launcher UI into a 24-bit BMP image for automated visual verification
    bool render_launcher_preview_bmp(const std::string& bmp_path, const std::string& iso_mount_summary = "MOUNTED - 700 FILES");

private:
    RuntimeConfig& cfg_;
};

} // namespace pn03

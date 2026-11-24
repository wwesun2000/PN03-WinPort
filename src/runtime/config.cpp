#include "pn03_config.hpp"
#include "pn03_runtime.hpp"
#include "pn03_symbols.hpp"
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <regex>
#include <thread>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <mmsystem.h>
#include <immintrin.h>
#endif

namespace pn03 {

static std::string extract_json_str(const std::string& content, const std::string& key, const std::string& def_val) {
    std::regex re("\"" + key + "\"\\s*:\\s*\"([^\"]*)\"");
    std::smatch m;
    if (std::regex_search(content, m, re)) {
        return m[1].str();
    }
    return def_val;
}

static int extract_json_int(const std::string& content, const std::string& key, int def_val) {
    std::regex re("\"" + key + "\"\\s*:\\s*(-?[0-9]+)");
    std::smatch m;
    if (std::regex_search(content, m, re)) {
        return std::stoi(m[1].str());
    }
    return def_val;
}

static float extract_json_float(const std::string& content, const std::string& key, float def_val) {
    std::regex re("\"" + key + "\"\\s*:\\s*(-?[0-9]+(?:\\.[0-9]+)?)");
    std::smatch m;
    if (std::regex_search(content, m, re)) {
        return std::stof(m[1].str());
    }
    return def_val;
}

static std::string normalize_json_path(const std::string& p) {
    std::string out = p;
    for (char& ch : out) {
        if (ch == '\\') ch = '/';
    }
    return out;
}

static bool extract_json_bool(const std::string& content, const std::string& key, bool def_val) {
    std::regex re("\"" + key + "\"\\s*:\\s*(true|false)");
    std::smatch m;
    if (std::regex_search(content, m, re)) {
        return m[1].str() == "true";
    }
    return def_val;
}

std::string RuntimeConfig::resolve_config_path(const std::string& explicit_or_default_path) {
    namespace fs = std::filesystem;
    std::error_code ec;
    if (!explicit_or_default_path.empty() && explicit_or_default_path != "config/pn03_settings.json" &&
        explicit_or_default_path != "config\\pn03_settings.json") {
        return explicit_or_default_path;
    }

    std::vector<fs::path> existing_candidates;
    existing_candidates.push_back(fs::current_path(ec) / "config" / "pn03_settings.json");

    fs::path exe_dir;
#ifdef _WIN32
    wchar_t exe_buf[MAX_PATH] = {0};
    if (GetModuleFileNameW(nullptr, exe_buf, MAX_PATH) > 0) {
        exe_dir = fs::path(exe_buf).parent_path();
        existing_candidates.push_back(exe_dir / "config" / "pn03_settings.json");
        if (exe_dir.has_parent_path()) {
            existing_candidates.push_back(exe_dir.parent_path() / "config" / "pn03_settings.json");
            if (exe_dir.parent_path().has_parent_path()) {
                existing_candidates.push_back(exe_dir.parent_path().parent_path() / "config" / "pn03_settings.json");
            }
        }
    }
#endif

    for (const auto& cand : existing_candidates) {
        if (!cand.empty() && fs::exists(cand, ec)) {
            return normalize_json_path(cand.string());
        }
    }

    if (!exe_dir.empty()) {
        if (exe_dir.has_parent_path() &&
            (fs::is_directory(exe_dir.parent_path() / "config", ec) ||
             fs::exists(exe_dir.parent_path() / "README.md", ec))) {
            return normalize_json_path((exe_dir.parent_path() / "config" / "pn03_settings.json").string());
        }
        return normalize_json_path((exe_dir / "config" / "pn03_settings.json").string());
    }
    return "config/pn03_settings.json";
}

bool RuntimeConfig::save_to_json(const std::string& path) const {
    namespace fs = std::filesystem;
    std::error_code ec;
    fs::path p(path);
    if (p.has_parent_path()) {
        fs::create_directories(p.parent_path(), ec);
    }
    std::ofstream out(p, std::ios::binary | std::ios::trunc);
    if (!out.is_open()) return false;
    out << "{\n"
        << "  \"runtime_mode\": \"" << runtime_mode << "\",\n"
        << "  \"iso_path\": \"" << normalize_json_path(iso_path) << "\",\n"
        << "  \"locale_overlay_path\": \"" << normalize_json_path(locale_overlay_path) << "\",\n"
        << "  \"save_dir\": \"" << normalize_json_path(save_dir) << "\",\n"
        << "  \"backend\": " << static_cast<int>(backend) << ",\n"
        << "  \"render_width\": " << render_width << ",\n"
        << "  \"render_height\": " << render_height << ",\n"
        << "  \"internal_scale_factor\": " << internal_scale_factor << ",\n"
        << "  \"window_mode\": " << static_cast<int>(window_mode) << ",\n"
        << "  \"msaa_mode\": " << static_cast<int>(msaa_mode) << ",\n"
        << "  \"enable_fxaa\": " << (enable_fxaa ? "true" : "false") << ",\n"
        << "  \"anisotropic_filtering\": " << anisotropic_filtering << ",\n"
        << "  \"aspect_ratio\": " << static_cast<int>(aspect_ratio) << ",\n"
        << "  \"remove_cinesco_bars\": " << (remove_cinesco_bars ? "true" : "false") << ",\n"
        << "  \"disable_copy_deflicker\": " << (disable_copy_deflicker ? "true" : "false") << ",\n"
        << "  \"vsync\": " << (vsync ? "true" : "false") << ",\n"
        << "  \"brightness\": " << brightness << ",\n"
        << "  \"limit_fps_60\": " << (limit_fps_60 ? "true" : "false") << ",\n"
        << "  \"audio_volume\": " << audio_volume << ",\n"
        << "  \"audio_muted\": " << (audio_muted ? "true" : "false") << ",\n"
        << "  \"language\": " << static_cast<int>(language) << ",\n"
        << "  \"enable_hd_chinese_font\": " << (enable_hd_chinese_font ? "true" : "false") << ",\n"
        << "  \"enable_xinput\": " << (enable_xinput ? "true" : "false") << ",\n"
        << "  \"controller_index\": " << controller_index << ",\n"
        << "  \"control_scheme_preset\": " << control_scheme_preset << ",\n"
        << "  \"left_stick_deadzone\": " << left_stick_deadzone << ",\n"
        << "  \"right_stick_deadzone\": " << right_stick_deadzone << ",\n"
        << "  \"trigger_threshold\": " << trigger_threshold << ",\n"
        << "  \"enable_vibration\": " << (enable_vibration ? "true" : "false") << ",\n"
        << "  \"vibration_strength\": " << vibration_strength << ",\n"
        << "  \"bind_gc_a\": " << bind_gc_a << ",\n"
        << "  \"bind_gc_b\": " << bind_gc_b << ",\n"
        << "  \"bind_gc_x\": " << bind_gc_x << ",\n"
        << "  \"bind_gc_y\": " << bind_gc_y << ",\n"
        << "  \"bind_gc_l\": " << bind_gc_l << ",\n"
        << "  \"bind_gc_r\": " << bind_gc_r << ",\n"
        << "  \"bind_gc_z\": " << bind_gc_z << ",\n"
        << "  \"bind_gc_start\": " << bind_gc_start << ",\n"
        << "  \"bind_guide_target\": " << bind_guide_target << ",\n"
        << "  \"load_tools_rel_debug\": " << (load_tools_rel_debug ? "true" : "false") << ",\n"
        << "  \"skip_launcher_gui\": " << (skip_launcher_gui ? "true" : "false") << ",\n"
        << "  \"cheat_god_mode\": " << (cheat_god_mode ? "true" : "false") << ",\n"
        << "  \"cheat_infinite_energy\": " << (cheat_infinite_energy ? "true" : "false") << ",\n"
        << "  \"cheat_infinite_credits\": " << (cheat_infinite_credits ? "true" : "false") << ",\n"
        << "  \"cheat_unlock_all_suits\": " << (cheat_unlock_all_suits ? "true" : "false") << ",\n"
        << "  \"log_dir\": \"" << normalize_json_path(log_dir) << "\",\n"
        << "  \"log_level\": \"" << log_level << "\",\n"
        << "  \"log_max_file_mb\": " << log_max_file_mb << ",\n"
        << "  \"log_max_total_mb\": " << log_max_total_mb << ",\n"
        << "  \"log_max_files\": " << log_max_files << "\n"
        << "}\n";
    return true;
}

RuntimeConfig RuntimeConfig::load_from_json(const std::string& path) {
    RuntimeConfig cfg;
    std::ifstream in(path, std::ios::binary);
    if (!in.is_open()) return cfg;
    std::ostringstream ss;
    ss << in.rdbuf();
    std::string s = ss.str();

    cfg.runtime_mode           = extract_json_str(s, "runtime_mode", cfg.runtime_mode);
    cfg.iso_path               = extract_json_str(s, "iso_path", cfg.iso_path);
    cfg.locale_overlay_path    = extract_json_str(s, "locale_overlay_path", cfg.locale_overlay_path);
    cfg.save_dir               = extract_json_str(s, "save_dir", cfg.save_dir);
    cfg.backend                = static_cast<GraphicsBackend>(extract_json_int(s, "backend", static_cast<int>(cfg.backend)));
    cfg.render_width           = static_cast<uint32_t>(extract_json_int(s, "render_width", static_cast<int>(cfg.render_width)));
    cfg.render_height          = static_cast<uint32_t>(extract_json_int(s, "render_height", static_cast<int>(cfg.render_height)));
    cfg.internal_scale_factor  = static_cast<uint32_t>(extract_json_int(s, "internal_scale_factor", static_cast<int>(cfg.internal_scale_factor)));
    cfg.window_mode            = static_cast<WindowMode>(extract_json_int(s, "window_mode", static_cast<int>(cfg.window_mode)));
    cfg.msaa_mode              = static_cast<AntiAliasingMode>(extract_json_int(s, "msaa_mode", static_cast<int>(cfg.msaa_mode)));
    cfg.enable_fxaa            = extract_json_bool(s, "enable_fxaa", cfg.enable_fxaa);
    cfg.anisotropic_filtering  = static_cast<uint32_t>(extract_json_int(s, "anisotropic_filtering", static_cast<int>(cfg.anisotropic_filtering)));
    cfg.aspect_ratio           = static_cast<AspectRatioMode>(extract_json_int(s, "aspect_ratio", static_cast<int>(cfg.aspect_ratio)));
    cfg.remove_cinesco_bars    = extract_json_bool(s, "remove_cinesco_bars", cfg.remove_cinesco_bars);
    cfg.disable_copy_deflicker = extract_json_bool(s, "disable_copy_deflicker", cfg.disable_copy_deflicker);
    cfg.vsync                  = extract_json_bool(s, "vsync", cfg.vsync);
    cfg.brightness             = (std::max)(0.50f, (std::min)(2.00f, extract_json_float(s, "brightness", cfg.brightness)));
    cfg.limit_fps_60           = extract_json_bool(s, "limit_fps_60", cfg.limit_fps_60);
    cfg.audio_volume           = extract_json_float(s, "audio_volume", cfg.audio_volume);
    cfg.audio_muted            = extract_json_bool(s, "audio_muted", cfg.audio_muted);
    cfg.language               = static_cast<GameLanguage>(extract_json_int(s, "language", static_cast<int>(cfg.language)));
    cfg.enable_hd_chinese_font = extract_json_bool(s, "enable_hd_chinese_font", cfg.enable_hd_chinese_font);
    cfg.enable_xinput          = extract_json_bool(s, "enable_xinput", cfg.enable_xinput);
    cfg.controller_index       = extract_json_int(s, "controller_index", cfg.controller_index);
    cfg.control_scheme_preset  = extract_json_int(s, "control_scheme_preset", cfg.control_scheme_preset);
    cfg.left_stick_deadzone    = extract_json_float(s, "left_stick_deadzone", cfg.left_stick_deadzone);
    cfg.right_stick_deadzone   = extract_json_float(s, "right_stick_deadzone", cfg.right_stick_deadzone);
    cfg.trigger_threshold      = extract_json_float(s, "trigger_threshold", cfg.trigger_threshold);
    cfg.enable_vibration       = extract_json_bool(s, "enable_vibration", cfg.enable_vibration);
    cfg.vibration_strength     = extract_json_float(s, "vibration_strength", cfg.vibration_strength);
    cfg.bind_gc_a              = extract_json_int(s, "bind_gc_a", cfg.bind_gc_a);
    cfg.bind_gc_b              = extract_json_int(s, "bind_gc_b", cfg.bind_gc_b);
    cfg.bind_gc_x              = extract_json_int(s, "bind_gc_x", cfg.bind_gc_x);
    cfg.bind_gc_y              = extract_json_int(s, "bind_gc_y", cfg.bind_gc_y);
    cfg.bind_gc_l              = extract_json_int(s, "bind_gc_l", cfg.bind_gc_l);
    cfg.bind_gc_r              = extract_json_int(s, "bind_gc_r", cfg.bind_gc_r);
    cfg.bind_gc_z              = extract_json_int(s, "bind_gc_z", cfg.bind_gc_z);
    cfg.bind_gc_start          = extract_json_int(s, "bind_gc_start", cfg.bind_gc_start);
    cfg.bind_guide_target      = extract_json_int(s, "bind_guide_target", cfg.bind_guide_target);
    cfg.load_tools_rel_debug   = extract_json_bool(s, "load_tools_rel_debug", cfg.load_tools_rel_debug);
    cfg.skip_launcher_gui      = extract_json_bool(s, "skip_launcher_gui", cfg.skip_launcher_gui);
    cfg.cheat_god_mode         = extract_json_bool(s, "cheat_god_mode", cfg.cheat_god_mode);
    cfg.cheat_infinite_energy  = extract_json_bool(s, "cheat_infinite_energy", cfg.cheat_infinite_energy);
    cfg.cheat_infinite_credits = extract_json_bool(s, "cheat_infinite_credits", cfg.cheat_infinite_credits);
    cfg.cheat_unlock_all_suits = extract_json_bool(s, "cheat_unlock_all_suits", cfg.cheat_unlock_all_suits);
    cfg.log_dir                = extract_json_str(s, "log_dir", cfg.log_dir);
    cfg.log_level              = extract_json_str(s, "log_level", cfg.log_level);
    cfg.log_max_file_mb        = static_cast<uint32_t>(extract_json_int(s, "log_max_file_mb", static_cast<int>(cfg.log_max_file_mb)));
    cfg.log_max_total_mb       = static_cast<uint32_t>(extract_json_int(s, "log_max_total_mb", static_cast<int>(cfg.log_max_total_mb)));
    cfg.log_max_files          = static_cast<uint32_t>(extract_json_int(s, "log_max_files", static_cast<int>(cfg.log_max_files)));
    return cfg;
}

void RuntimeConfig::apply_control_preset(int preset_idx) {
    control_scheme_preset = (preset_idx < 0 || preset_idx > 3) ? 0 : preset_idx;
    switch (control_scheme_preset) {
        case 1: // Type B (Trigger Fire)
            bind_gc_a     = static_cast<int>(XboxInputSource::TriggerRT);
            bind_gc_b     = static_cast<int>(XboxInputSource::BtnA);
            bind_gc_x     = static_cast<int>(XboxInputSource::BtnB);
            bind_gc_y     = static_cast<int>(XboxInputSource::BtnY);
            bind_gc_l     = static_cast<int>(XboxInputSource::TriggerLT);
            bind_gc_r     = static_cast<int>(XboxInputSource::BtnRB);
            bind_gc_z     = static_cast<int>(XboxInputSource::BtnLB);
            bind_gc_start = static_cast<int>(XboxInputSource::BtnStart);
            break;
        case 2: // Type C (Shoulder Tactical)
            bind_gc_a     = static_cast<int>(XboxInputSource::BtnA);
            bind_gc_b     = static_cast<int>(XboxInputSource::BtnX);
            bind_gc_x     = static_cast<int>(XboxInputSource::BtnB);
            bind_gc_y     = static_cast<int>(XboxInputSource::BtnY);
            bind_gc_l     = static_cast<int>(XboxInputSource::BtnLB);
            bind_gc_r     = static_cast<int>(XboxInputSource::BtnRB);
            bind_gc_z     = static_cast<int>(XboxInputSource::BtnBack);
            bind_gc_start = static_cast<int>(XboxInputSource::BtnStart);
            break;
        case 3: // Type D (Legacy Quick-Step)
            bind_gc_a     = static_cast<int>(XboxInputSource::BtnX);
            bind_gc_b     = static_cast<int>(XboxInputSource::BtnA);
            bind_gc_x     = static_cast<int>(XboxInputSource::BtnB);
            bind_gc_y     = static_cast<int>(XboxInputSource::BtnY);
            bind_gc_l     = static_cast<int>(XboxInputSource::TriggerLT);
            bind_gc_r     = static_cast<int>(XboxInputSource::TriggerRT);
            bind_gc_z     = static_cast<int>(XboxInputSource::BtnRB);
            bind_gc_start = static_cast<int>(XboxInputSource::BtnStart);
            break;
        case 0: // Type A (Standard P.N.03)
        default:
            bind_gc_a     = static_cast<int>(XboxInputSource::BtnA);
            bind_gc_b     = static_cast<int>(XboxInputSource::BtnB);
            bind_gc_x     = static_cast<int>(XboxInputSource::BtnX);
            bind_gc_y     = static_cast<int>(XboxInputSource::BtnY);
            bind_gc_l     = static_cast<int>(XboxInputSource::TriggerLT);
            bind_gc_r     = static_cast<int>(XboxInputSource::TriggerRT);
            bind_gc_z     = static_cast<int>(XboxInputSource::BtnRB);
            bind_gc_start = static_cast<int>(XboxInputSource::BtnStart);
            break;
    }
}

const char* RuntimeConfig::xbox_input_source_label(int src) {
    switch (static_cast<XboxInputSource>(src)) {
        case XboxInputSource::BtnA:      return "Xbox A";
        case XboxInputSource::BtnB:      return "Xbox B";
        case XboxInputSource::BtnX:      return "Xbox X";
        case XboxInputSource::BtnY:      return "Xbox Y";
        case XboxInputSource::BtnLB:     return "LB";
        case XboxInputSource::BtnRB:     return "RB";
        case XboxInputSource::TriggerLT: return "LT";
        case XboxInputSource::TriggerRT: return "RT";
        case XboxInputSource::BtnBack:   return "View (Back)";
        case XboxInputSource::BtnStart:  return "Menu (Start)";
        case XboxInputSource::BtnGuide:  return "Xbox [X] Guide";
        case XboxInputSource::BtnLStick: return "LS Click";
        case XboxInputSource::BtnRStick: return "RS Click";
        case XboxInputSource::DpadUp:    return "D-Pad Up";
        case XboxInputSource::DpadDown:  return "D-Pad Down";
        case XboxInputSource::DpadLeft:  return "D-Pad Left";
        case XboxInputSource::DpadRight: return "D-Pad Right";
        case XboxInputSource::None:
        default:                         return "Unbound";
    }
}

const char* RuntimeConfig::guide_action_label(int target) {
    switch (static_cast<GuideActionTarget>(target)) {
        case GuideActionTarget::GcStart: return "PAUSE / MENU (START)";
        case GuideActionTarget::GcZ:     return "STATUS / MAP (Z)";
        case GuideActionTarget::GcY:     return "ENERGY DRIVE (Y)";
        case GuideActionTarget::GcX:     return "BARRIER / PALM (X)";
        case GuideActionTarget::GcL:     return "LOCK-ON (L)";
        case GuideActionTarget::GcR:     return "QUICK TURN / BOOST (R)";
        case GuideActionTarget::GcA:     return "SHOOT / CONFIRM (A)";
        case GuideActionTarget::GcB:     return "DODGE / BACK (B)";
        case GuideActionTarget::Disabled:
        default:                         return "DISABLED (OR CUSTOM BIND)";
    }
}

static uint64_t query_qpc_counter_now() noexcept {
#ifdef _WIN32
    LARGE_INTEGER li{};
    QueryPerformanceCounter(&li);
    return static_cast<uint64_t>((std::max)(0LL, li.QuadPart));
#else
    return static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count());
#endif
}

static uint64_t query_qpc_freq_hz() noexcept {
#ifdef _WIN32
    LARGE_INTEGER li{};
    QueryPerformanceFrequency(&li);
    return static_cast<uint64_t>((std::max)(1LL, li.QuadPart));
#else
    return 1000000ull;
#endif
}

FramePacer::FramePacer(bool enabled, double target_hz)
    : target_hz_((target_hz > 1.0) ? target_hz : kNtscHz) {
    qpc_freq_ = query_qpc_freq_hz();
    frame_ticks_ = static_cast<uint64_t>(std::llround(static_cast<double>(qpc_freq_) / target_hz_));
    if (frame_ticks_ == 0u) frame_ticks_ = 1u;
    set_enabled(enabled);
}

FramePacer::~FramePacer() {
    set_enabled(false);
}

void FramePacer::set_enabled(bool enabled) {
    if (enabled_ == enabled) return;
    enabled_ = enabled;
#ifdef _WIN32
    if (enabled_ && !winmm_period_active_) {
        if (timeBeginPeriod(1) == TIMERR_NOERROR) {
            winmm_period_active_ = true;
        }
    } else if (!enabled_ && winmm_period_active_) {
        timeEndPeriod(1);
        winmm_period_active_ = false;
    }
#endif
    next_deadline_ticks_ = 0;
}

void FramePacer::reset() {
    next_deadline_ticks_ = query_qpc_counter_now() + frame_ticks_;
}

uint64_t FramePacer::compute_next_step_us(uint64_t now_ticks, uint64_t& io_next_deadline_ticks,
                                          uint64_t qpc_freq, uint64_t frame_ticks) {
    if (qpc_freq == 0u || frame_ticks == 0u) return 0u;
    if (io_next_deadline_ticks == 0u) {
        io_next_deadline_ticks = now_ticks + frame_ticks;
        return 0u;
    }
    if (now_ticks >= io_next_deadline_ticks) {
        const uint64_t behind = now_ticks - io_next_deadline_ticks;
        if (behind > frame_ticks * 3u) {
            io_next_deadline_ticks = now_ticks + frame_ticks;
        } else {
            io_next_deadline_ticks += frame_ticks;
        }
        return 0u;
    }
    const uint64_t wait_ticks = io_next_deadline_ticks - now_ticks;
    io_next_deadline_ticks += frame_ticks;
    return (wait_ticks * 1000000ull) / qpc_freq;
}

void FramePacer::wait_for_next_frame() {
    if (!enabled_) return;
    const uint64_t target_deadline = next_deadline_ticks_;
    const uint64_t now = query_qpc_counter_now();
    const uint64_t wait_us = compute_next_step_us(now, next_deadline_ticks_, qpc_freq_, frame_ticks_);
    if (wait_us == 0u || target_deadline == 0u) return;

#ifdef _WIN32
    uint64_t cur = now;
    while (cur < target_deadline) {
        const uint64_t rem_us = ((target_deadline - cur) * 1000000ull) / qpc_freq_;
        if (rem_us >= 2200ull) {
            const DWORD sleep_ms = static_cast<DWORD>((rem_us - 1200ull) / 1000ull);
            if (sleep_ms > 0u) {
                Sleep(sleep_ms);
            }
        } else {
            _mm_pause();
        }
        cur = query_qpc_counter_now();
    }
#else
    std::this_thread::sleep_for(std::chrono::microseconds(wait_us));
#endif
}

void apply_runtime_cheats(const RuntimeConfig& cfg, Memory& mem) {
    if (!cfg.cheat_god_mode && !cfg.cheat_infinite_energy &&
        !cfg.cheat_infinite_credits && !cfg.cheat_unlock_all_suits) {
        return;
    }
    const uint32_t pG = mem.read_u32(recomp::sym_addr::kSda_pG);
    if (pG < kGcRamBase || !mem.is_valid_range(pG, 0x7000u)) {
        return;
    }
    if (cfg.cheat_god_mode) {
        const int16_t max_hp = mem.read_s16(pG + 26642u); // Global + 0x6812 (max barrier HP)
        if (max_hp > 0) {
            const int16_t cur_hp = mem.read_s16(pG + 26640u); // Global + 0x6810 (current HP)
            if (cur_hp < max_hp) {
                mem.write_u16(pG + 26640u, static_cast<uint16_t>(max_hp));
            }
        }
    }
    if (cfg.cheat_infinite_energy) {
        // Capcom native unlimited suit energy flag checked in PlGaugeCheck (0x800AE550) & PlGaugeDown (0x800AE58C)
        const uint32_t flags304 = mem.read_u32(pG + 304u);
        mem.write_u32(pG + 304u, flags304 | 0x00002000u);
        const int16_t max_en = mem.read_s16(pG + 26646u); // Global + 0x6816 (max Energy)
        if (max_en > 0) {
            const int16_t cur_en = mem.read_s16(pG + 26644u); // Global + 0x6814 (current Energy)
            if (cur_en < max_en) {
                mem.write_u16(pG + 26644u, static_cast<uint16_t>(max_en));
            }
        }
    }
    if (cfg.cheat_infinite_credits) {
        const uint32_t pts = mem.read_u32(pG + 26664u); // Global + 0x6828 (Shop Points, 7 digits)
        if (pts < 9999999u) {
            mem.write_u32(pG + 26664u, 9999999u);
        }
    }
    if (cfg.cheat_unlock_all_suits) {
        constexpr uint32_t kSuitTblBase = 26776u; // Global + 0x6898 (Suit[0..10], 16B each)
        // Gate on initialized suit table so boot/title-screen work isn't disturbed pre-game.
        if (mem.read_u8(pG + kSuitTblBase + 2u) > 0u || mem.read_u8(pG + kSuitTblBase) != 0u) {
            const uint32_t gflags = mem.read_u32(pG + 4u);
            mem.write_u32(pG + 4u, gflags | 0x60000000u); // Unlock Black (#9), Papillon (#10), max upgrade caps
            for (uint32_t i = 0; i < 11u; ++i) {
                const uint32_t s_va = pG + kSuitTblBase + i * 16u;
                mem.write_u8(s_va + 0u, 1u); // owned (cSuitCtrl::getSuitHave)
                if (i != 10u && mem.read_u8(s_va + 3u) < 5u) mem.write_u8(s_va + 3u, 5u); // Barrier Lv5
                if (mem.read_u8(s_va + 4u) < 5u) mem.write_u8(s_va + 4u, 5u); // Palm Shot Lv5
                if (mem.read_u8(s_va + 5u) < 2u) mem.write_u8(s_va + 5u, 2u); // Automatic Lv2
                if (mem.read_u8(s_va + 6u) < 6u) mem.write_u8(s_va + 6u, 6u); // Energy Drive Lv6
            }
        }
    }
}

} // namespace pn03

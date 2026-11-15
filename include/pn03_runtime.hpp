#pragma once
#include "pn03_config.hpp"
#include "pn03_ppc_context.hpp"
#include "pn03_symbols.hpp"
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace pn03 {

// ============================================================================
// 1. Direct GameCube ISO / GCM Stream Reader & LZS (.lze) Decompressor
//    (Zero built-in game assets; reads directly from user-imported ISO/GCM)
// ============================================================================
struct IsoFileEntry {
    std::string path;
    uint32_t    disc_offset = 0;
    uint32_t    size_bytes  = 0;
    bool        is_dir      = false;
};

class IsoStreamReader {
public:
    IsoStreamReader() = default;
    ~IsoStreamReader();

    // Opens either a full GameCube .iso/.gcm image OR a directory with extracted sys/boot.bin & sys/fst.bin
    bool open(const std::string& iso_or_sys_path, std::string& err_msg);
    bool is_open() const { return is_open_; }
    std::string game_id() const { return game_id_; }
    std::string game_title() const { return game_title_; }
    uint32_t dol_offset() const { return dol_offset_; }
    uint32_t fst_offset() const { return fst_offset_; }
    size_t file_count() const { return files_.size(); }

    // Case-insensitive lookup matching Dolphin DVDConvertPathToEntrynum behavior
    const IsoFileEntry* find_file(const std::string& virtual_path) const;
    int32_t find_entrynum(const std::string& virtual_path) const;
    const IsoFileEntry* get_file_by_entrynum(int32_t entrynum) const;
    std::vector<uint8_t> read_file(const std::string& virtual_path) const;
    std::vector<uint8_t> read_file_slice(int32_t entrynum, uint32_t offset, uint32_t length) const;
    std::vector<uint8_t> read_slice(uint32_t disc_offset, uint32_t length) const;

    // Loads main.dol directly from the mounted ISO into the 24MB GameCube RAM
    bool load_main_dol_into_memory(Memory& mem, uint32_t& out_entry_point) const;

    // Bit-exact implementation of Capcom P.N.03 LzsDecode (0x80077680 in compless.obj)
    static std::vector<uint8_t> lzs_decode(const uint8_t* src, size_t src_len);
    static std::vector<uint8_t> lzs_encode_for_test(const uint8_t* raw, size_t raw_len);

    // Active instance registration for Dolphin DVD* HLE
    static void set_active_instance(const IsoStreamReader* reader);
    static const IsoStreamReader* active_instance();

private:
    static std::string normalize_gc_path(const std::string& p);
    bool parse_headers(const std::vector<uint8_t>& boot_bin, const std::vector<uint8_t>& fst_bin, std::string& err_msg);

    bool is_open_ = false;
    bool is_extracted_dir_ = false;
    std::string base_path_;
    std::string game_id_;
    std::string game_title_;
    uint32_t dol_offset_ = 0;
    uint32_t fst_offset_ = 0;
    uint32_t fst_size_   = 0;
    std::vector<IsoFileEntry> files_;
    std::unordered_map<std::string, size_t> path_index_;
};

// ============================================================================
// 2. Xbox Controller (XInput) -> GameCube PADStatus Bridge (pad.obj)
// ============================================================================
// Matches Nintendo Dolphin SDK PADStatus struct (12 bytes per controller at 0x801C4A68)
enum GcPadButton : uint16_t {
    PAD_BUTTON_LEFT  = 0x0001,
    PAD_BUTTON_RIGHT = 0x0002,
    PAD_BUTTON_DOWN  = 0x0004,
    PAD_BUTTON_UP    = 0x0008,
    PAD_TRIGGER_Z    = 0x0010,
    PAD_TRIGGER_R    = 0x0020,
    PAD_TRIGGER_L    = 0x0040,
    PAD_BUTTON_A     = 0x0100,
    PAD_BUTTON_B     = 0x0200,
    PAD_BUTTON_X     = 0x0400,
    PAD_BUTTON_Y     = 0x0800,
    PAD_BUTTON_START = 0x1000
};

struct GcPadStatus {
    uint16_t button       = 0;
    int8_t   stickX       = 0;
    int8_t   stickY       = 0;
    int8_t   substickX    = 0;
    int8_t   substickY    = 0;
    uint8_t  triggerLeft  = 0;
    uint8_t  triggerRight = 0;
    uint8_t  analogA      = 0;
    uint8_t  analogB      = 0;
    int8_t   err          = 0; // 0 = PAD_ERR_NONE, -1 = PAD_ERR_NO_CONTROLLER
    uint8_t  padding      = 0;
};

struct XboxInputState {
    bool     connected      = true;
    bool     btn_a          = false;
    bool     btn_b          = false;
    bool     btn_x          = false;
    bool     btn_y          = false;
    bool     btn_start      = false;
    bool     btn_back       = false;
    bool     btn_lb         = false;
    bool     btn_rb         = false;
    bool     dpad_up        = false;
    bool     dpad_down      = false;
    bool     dpad_left      = false;
    bool     dpad_right     = false;
    float    left_stick_x   = 0.0f; // -1.0 .. +1.0
    float    left_stick_y   = 0.0f; // -1.0 .. +1.0
    float    right_stick_x  = 0.0f;
    float    right_stick_y  = 0.0f;
    float    left_trigger   = 0.0f; // 0.0 .. 1.0
    float    right_trigger  = 0.0f; // 0.0 .. 1.0
    bool     btn_guide      = false; // Center Xbox [X] button (0x0400 via XInputGetStateEx)
    bool     btn_ls         = false; // Left Stick click
    bool     btn_rs         = false; // Right Stick click
};

class PadXInputBridge {
public:
    explicit PadXInputBridge(const RuntimeConfig& cfg) : cfg_(cfg) {}

    // Polls Windows XInput hardware (when compiled on Windows) or uses injected state
    XboxInputState poll_xbox_controller() const;
    GcPadStatus translate_to_gc_pad(const XboxInputState& xstate) const;

    // Writes translated PADStatus[4] directly into GameCube RAM (0x801C4A68 Pad_data)
    void update_memory_pad_status(Memory& mem, const XboxInputState* override_state = nullptr);
    void write_pad_status_to_addr(Memory& mem, uint32_t dest_vaddr, const XboxInputState* override_state = nullptr);

    // Controls Xbox rumble motors when P.N.03 calls VibControl (0x800AD160) / PADControlMotor
    void set_rumble(uint32_t command, float intensity = 1.0f);
    bool is_rumbling() const { return rumble_active_; }

    void set_active_override(const XboxInputState* ov) { active_override_ = ov; }
    const XboxInputState* active_override() const { return active_override_; }

    static void set_active_instance(PadXInputBridge* bridge);
    static PadXInputBridge* active_instance();

private:
    static int8_t apply_deadzone_and_clamp(float v, float deadzone);
    RuntimeConfig cfg_;
    bool rumble_active_ = false;
    const XboxInputState* active_override_ = nullptr;
};

// ============================================================================
// 3. GX High-Resolution 3D Renderer Backend (D3D11 / OpenGL)
// ============================================================================
struct GXRenderState {
    uint32_t target_width         = 1920;
    uint32_t target_height        = 1080;
    float    viewport_w           = 1920.0f;
    float    viewport_h           = 1080.0f;
    uint32_t msaa_samples         = 4;
    bool     fxaa_enabled         = true;
    bool     fullscreen           = true;
    bool     deflicker_disabled   = true;
    bool     cinesco_bars_removed = true;
    float    ortho_left           = -106.6667f; // Expanded 16:9 from [0..640] to [-106.67..746.67]
    float    ortho_right          = 746.6667f;
    float    aspect_ratio         = 16.0f / 9.0f;
    uint64_t draw_call_count      = 0;
    uint64_t frame_count          = 0;
    uint32_t internal_scale_factor = 3;
    uint32_t efb_width            = 2560;
    uint32_t efb_height           = 1440;
};

class GXHighResRenderer {
public:
    explicit GXHighResRenderer(const RuntimeConfig& cfg);

    // Called on Render_init (0x8009D098) and Render_before (0x8009D2B0)
    void initialize_pipeline(Memory& mem);
    void begin_frame(Memory& mem);
    void end_frame_and_present(Memory& mem);

    // HLE hooks for GXSetViewport, GXSetCopyFilter, Draw_cinesco
    void on_gx_set_viewport(float x, float y, float w, float h, float near_z, float far_z);
    void on_gx_set_copy_filter(bool aa, const uint8_t sample_pattern[12][2], bool vf, const uint8_t vfilter[7]);
    bool should_skip_cinesco_letterbox() const { return state_.cinesco_bars_removed; }

    const GXRenderState& state() const { return state_; }

private:
    RuntimeConfig cfg_;
    GXRenderState state_;
};

// ============================================================================
// 4. Chinese Localization Overlay & High-Res Font Hook (mes.obj / cockpit.obj)
// ============================================================================
class LocalizationOverlay {
public:
    explicit LocalizationOverlay(const RuntimeConfig& cfg);

    bool load_dictionary(const std::string& json_path);

    // Hooks CMesCtrl::MesSetLanguage (0x8009F12C) which hardcoded language=1 in US GPNE08
    void hook_mes_set_language(PPCContext& ctx, Memory& mem) const;

    // Translates original English/European message ID or string to Simplified Chinese (UTF-8)
    std::string translate_by_id(uint32_t msg_id) const;
    std::string translate_text(const std::string& original_en) const;

    // Decodes Capcom 16-bit glyph stream (0xF05ADF3E table) in GameCube RAM to English string
    std::string decode_gc_moji_stream(const Memory& mem, uint32_t msg_vaddr, size_t max_words = 256) const;

    // Records HD Chinese text overlay when CMesWk::MesWorkTrans (0x8009FDF0) renders active message.
    // Returns true when an active Simplified Chinese overlay covers this message (caller should suppress English bitmap glyphs).
    bool try_on_mes_work_trans(uint32_t mes_wk_vaddr, const Memory& mem) const;
    void on_mes_work_trans(uint32_t mes_wk_vaddr, const Memory& mem) const;
    bool is_chinese_overlay_enabled() const {
        return cfg_.language == GameLanguage::SimplifiedChinese && cfg_.enable_hd_chinese_font;
    }

    // Redirects language-specific asset paths (e.g. /id/eng/iddata_e.dat -> /id/fra/iddata_f.dat)
    std::string resolve_localized_asset_path(const std::string& orig_path) const;

    size_t entry_count() const { return id_to_zh_.size() + en_to_zh_.size(); }
    GameLanguage configured_language() const { return cfg_.language; }

    // Frame lifecycle, active CMesWk scanner, and Eprintf / font_draw interception
    void set_config(const RuntimeConfig& cfg) { cfg_ = cfg; }
    void begin_frame() const;
    bool hook_font_draw(PPCContext& ctx, Memory& mem) const;
    void hook_eprintf_buffering(PPCContext& ctx, Memory& mem) const;
    void emit_active_ui_scene_overlays(const Memory& mem) const;
    static std::string clean_overlay_display_text(const std::string& s);

    // Multi-page (0x0004) CMesWk dialogue support: only the page currently being typed / awaiting input is rendered.
    // count_cmes_page_index() counts 0x0004 page-break words in [entry_ptr, text_ptr) of the raw glyph stream
    // (text_ptr sits on the 0x0004 word while waiting for A; code04 advances it by 2 once the player confirms).
    static size_t count_cmes_page_index(const Memory& mem, uint32_t entry_ptr, uint32_t text_ptr);
    // Returns page `page_idx` (clamped to the last page) of a raw "<04>"-separated translated string.
    static std::string extract_page_segment(const std::string& raw_with_tags, size_t page_idx);
    // Width-aware UTF-8 / CJK wrapper (CJK = 2 columns, ASCII = 1 column). Existing '\n' are preserved.
    static std::string wrap_comm_text(const std::string& text, size_t max_cols = 44u);
    static size_t display_cols(const std::string& utf8_line);

    // Fits dialogue inside the GameCube 640x480 comm-box safe area (right margin <= 572, top box above y=132).
    struct CommLayout {
        float x = 56.0f;
        float y = 368.0f;
        float scale = 0.74f;
        float width = 0.0f;
        float height = 0.0f;
        size_t lines = 0u;
        std::string text;
    };
    static CommLayout layout_dialogue(float base_x, float base_y, const std::string& display);

    static void set_active_instance(const LocalizationOverlay* loc);
    static const LocalizationOverlay* active_instance();

private:
    RuntimeConfig cfg_;
    std::unordered_map<uint32_t, std::string> id_to_zh_;
    std::unordered_map<std::string, std::string> en_to_zh_;
    std::unordered_map<std::string, std::string> en_norm_to_zh_;
    mutable std::vector<uint32_t> frame_emitted_mes_ptrs_;
};

// ============================================================================
// 5. Tools.rel Relocatable Module Loader (OSLink 0x800F56E0)
// ============================================================================
struct RelModuleHeader {
    uint32_t id               = 0;
    uint32_t num_sections     = 0;
    uint32_t section_info_off = 0;
    uint32_t version          = 0;
    uint32_t bss_size         = 0;
    uint32_t rel_off          = 0;
    uint32_t imp_off          = 0;
    uint32_t imp_size         = 0;
    uint8_t  prolog_section   = 0;
    uint8_t  epilog_section   = 0;
    uint32_t prolog_offset    = 0;
    uint32_t epilog_offset    = 0;
};

class ToolsRelLoader {
public:
    static bool link_rel_module(
        const std::vector<uint8_t>& rel_bytes,
        Memory& mem,
        uint32_t base_load_vaddr,
        RelModuleHeader& out_hdr,
        uint32_t& out_prolog_vaddr
    );
};

// ============================================================================
// 6. Recompiled Boot & HLE Runtime Control Helpers (dolphin_sdk_hle.cpp)
// ============================================================================
void reset_hle_runtime_state(Memory& mem);
void set_hle_call_trace(bool enabled);
void enqueue_pending_hle_callback(uint32_t callback_vaddr, uint32_t arg0, uint32_t arg1 = 0u, uint32_t dvd_file_info = 0u);
void flush_pending_hle_callbacks(PPCContext& ctx, Memory& mem);
uint32_t execute_static_constructors(PPCContext& ctx, Memory& mem);

// ============================================================================
// 7. Dolphin-Style High-Precision 59.94Hz Frame Limiter
// ============================================================================
class FramePacer {
public:
    static constexpr double kNtscHz        = 60000.0 / 1001.0; // ~59.94006 FPS
    static constexpr double kNtscPeriodSec = 1001.0 / 60000.0;

    explicit FramePacer(bool enabled = true, double target_hz = kNtscHz);
    ~FramePacer();

    void set_enabled(bool enabled);
    bool is_enabled() const { return enabled_; }
    double target_hz() const { return target_hz_; }
    uint64_t ticks_per_frame() const { return frame_ticks_; }

    // Resets QPC deadline anchor to current monotonic time
    void reset();

    // Sleeps/spins cleanly to hit next fixed 59.94Hz deadline (noop when disabled)
    void wait_for_next_frame();

    // Pure testable cadence step: given current QPC ticks, returns microseconds to wait and advances next_deadline
    static uint64_t compute_next_step_us(uint64_t now_ticks, uint64_t& io_next_deadline_ticks,
                                         uint64_t qpc_freq, uint64_t frame_ticks);

private:
    bool     enabled_             = false;
    bool     winmm_period_active_ = false;
    double   target_hz_           = kNtscHz;
    uint64_t qpc_freq_            = 0;
    uint64_t frame_ticks_         = 0;
    uint64_t next_deadline_ticks_ = 0;
};

} // namespace pn03

#include "pn03_runtime.hpp"
#include "pn03_gx_3d_interface.hpp"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <sstream>

namespace pn03 {

namespace {

const LocalizationOverlay* g_active_loc_overlay = nullptr;
std::mutex g_loc_frame_mtx;

// Verified Capcom P.N.03 (GPNE08) CMesCtrl / CMesWk globals from meka_symbols_full.json & mes_hl.cpp:
// cMes = 0x801A2A40; CMesWk[0..4] array begins at cMes + 4 = 0x801A2A44, stride 0x1E84 (7812 bytes).
constexpr uint32_t kCMesWkBase      = 0x801A2A44u;
constexpr uint32_t kCMesWkStride    = 0x1E84u;
constexpr uint32_t kCMesWkSlots     = 5u;
constexpr uint32_t kMesOffRgba      = 0x24u;
constexpr uint32_t kMesOffMsgId     = 0x28u;
constexpr uint32_t kMesOffTextPtr   = 0x40u;
constexpr uint32_t kMesOffLangBase  = 0x44u;
constexpr uint32_t kMesOffMsgQue    = 0x58u;
constexpr uint32_t kMesOffMsgQueX   = 0x58u;
constexpr uint32_t kMesOffMsgQueY   = 0x5Au;
constexpr uint32_t kMesOffMsgQueEnd = 0x1E58u;
constexpr uint32_t kMesQueStride    = 20u;
constexpr uint32_t kMesQueMaxCount  = 384u; // (0x1E58 - 0x58) / 20 == 384

inline bool is_valid_ram(uint32_t va) {
    return va >= 0x80000000u && va < 0x81800000u;
}

void append_gc_moji_token(std::string& out, uint16_t v) {
    if (v == 0x0000u || v == 0x0002u) {
        return;
    }
    if (v == 0x0003u) {
        out.push_back('\n');
    } else if (v == 0x0080u) {
        out.push_back(' ');
    } else if (v >= 0x0083u && v <= 0x008Cu) {
        out.push_back(static_cast<char>('0' + (v - 0x0083u)));
    } else if (v >= 0x00A7u && v <= 0x00C0u) {
        out.push_back(static_cast<char>('A' + (v - 0x00A7u)));
    } else if (v >= 0x00C1u && v <= 0x00DAu) {
        out.push_back(static_cast<char>('a' + (v - 0x00C1u)));
    } else {
        switch (v) {
            case 0x008Du: out.push_back(':'); break;
            case 0x0090u: out.push_back('+'); break;
            case 0x0091u: out.push_back('-'); break;
            case 0x0092u: out.push_back('/'); break;
            case 0x0094u: out.push_back(','); break;
            case 0x0095u: out.push_back('.'); break;
            case 0x0098u: out.push_back('('); break;
            case 0x0099u: out.push_back(')'); break;
            case 0x009Au: out.push_back('!'); break;
            case 0x009Bu: out.push_back('?'); break;
            case 0x009Cu:
            case 0x009Du: out.push_back('"'); break;
            case 0x0123u: out.push_back('\''); break;
            default: {
                char tag[12];
                std::snprintf(tag, sizeof(tag), "<%02x>", static_cast<unsigned>(v));
                out += tag;
                break;
            }
        }
    }
}

std::string trim_ascii(const std::string& s) {
    size_t b = 0;
    while (b < s.size() && (s[b] == ' ' || s[b] == '\t' || s[b] == '\r' || s[b] == '\n')) {
        ++b;
    }
    size_t e = s.size();
    while (e > b && (s[e - 1] == ' ' || s[e - 1] == '\t' || s[e - 1] == '\r' || s[e - 1] == '\n')) {
        --e;
    }
    return s.substr(b, e - b);
}

uint32_t resolve_cmes_entry_start(const Memory& mem, uint32_t lang_base, uint32_t text_ptr) {
    if (!is_valid_ram(lang_base) || !is_valid_ram(text_ptr) || text_ptr < lang_base + 12u) {
        return 0u;
    }
    uint32_t best_entry = 0u;
    uint32_t min_table_end = 0x01000000u;
    constexpr uint32_t kMaxEntries = 4096u;
    for (uint32_t i = 0; i < kMaxEntries; ++i) {
        const uint32_t off_va = lang_base + 8u + i * 4u;
        if (!is_valid_ram(off_va) || (8u + i * 4u) >= min_table_end) {
            break;
        }
        const uint32_t off = mem.read_u32(off_va);
        if (off == 0u && i > 0u) {
            continue;
        }
        if (off < 12u || off >= 0x01000000u) {
            break;
        }
        const uint32_t entry_va = lang_base + off;
        if (!is_valid_ram(entry_va)) {
            break;
        }
        if (off < min_table_end) {
            min_table_end = off;
        }
        if (entry_va <= text_ptr && entry_va > best_entry) {
            best_entry = entry_va;
        }
    }
    if (best_entry != 0u && (text_ptr - best_entry) > 4096u) {
        return 0u;
    }
    return best_entry;
}

std::string decode_cmes_msg_que(const Memory& mem, uint32_t mes_wk_vaddr) {
    const uint32_t q_begin = mes_wk_vaddr + kMesOffMsgQue;
    const uint32_t q_end   = mem.read_u32(mes_wk_vaddr + kMesOffMsgQueEnd);
    if (q_end <= q_begin || q_end > mes_wk_vaddr + kMesOffMsgQueEnd) {
        return {};
    }
    const uint32_t raw_count = (q_end - q_begin) / kMesQueStride;
    const uint32_t count = std::min<uint32_t>(raw_count, kMesQueMaxCount);
    std::string out;
    out.reserve(count + 8u);
    int32_t prev_x = 0;
    int32_t prev_y = 0;
    uint16_t prev_adv_w = 0u;
    for (uint32_t i = 0; i < count; ++i) {
        const uint32_t q = q_begin + i * kMesQueStride;
        const int32_t x = static_cast<int32_t>(static_cast<int16_t>(mem.read_u16(q + 0u)));
        const int32_t y = static_cast<int32_t>(static_cast<int16_t>(mem.read_u16(q + 2u)));
        const uint16_t glyph_idx = mem.read_u16(q + 4u);
        const uint16_t adv_w = mem.read_u16(q + 6u);
        if (i > 0u) {
            if (y - prev_y >= 8 || prev_y - y >= 8) {
                out.push_back('\n');
            } else if (prev_adv_w > 0u) {
                if (x >= prev_x + static_cast<int32_t>(prev_adv_w) + 4) {
                    out.push_back(' ');
                }
            } else if (x - prev_x >= 18) {
                out.push_back(' ');
            }
        }
        append_gc_moji_token(out, static_cast<uint16_t>(glyph_idx + 0x0080u));
        prev_x = x;
        prev_y = y;
        prev_adv_w = adv_w;
    }
    return trim_ascii(out);
}

std::string strip_hex_tags(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '<') {
            size_t j = i + 1;
            while (j < s.size() && std::isxdigit(static_cast<unsigned char>(s[j]))) {
                ++j;
            }
            if (j > i + 1 && j < s.size() && s[j] == '>') {
                const std::string tag = s.substr(i + 1, j - i - 1);
                if (tag == "04") {
                    out.push_back('\n');
                } else if (tag == "ffff" || tag == "FFFF") {
                    out += "%s";
                }
                i = j;
                continue;
            }
        }
        out.push_back(s[i]);
    }
    return trim_ascii(out);
}

std::string normalize_lookup_key(const std::string& s) {
    std::string stripped = strip_hex_tags(s);
    std::string out;
    out.reserve(stripped.size());
    bool prev_space = false;
    for (unsigned char c : stripped) {
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            if (!out.empty() && !prev_space) {
                out.push_back(' ');
                prev_space = true;
            }
        } else {
            out.push_back(static_cast<char>(std::toupper(c)));
            prev_space = false;
        }
    }
    if (!out.empty() && out.back() == ' ') {
        out.pop_back();
    }
    return out;
}

void append_utf8(uint32_t cp, std::string& out) {
    if (cp <= 0x7Fu) {
        out.push_back(static_cast<char>(cp));
    } else if (cp <= 0x7FFu) {
        out.push_back(static_cast<char>(0xC0u | (cp >> 6)));
        out.push_back(static_cast<char>(0x80u | (cp & 0x3Fu)));
    } else {
        out.push_back(static_cast<char>(0xE0u | (cp >> 12)));
        out.push_back(static_cast<char>(0x80u | ((cp >> 6) & 0x3Fu)));
        out.push_back(static_cast<char>(0x80u | (cp & 0x3Fu)));
    }
}

bool parse_json_string(const std::string& src, size_t& pos, std::string& out) {
    if (pos >= src.size() || src[pos] != '"') {
        return false;
    }
    ++pos;
    out.clear();
    while (pos < src.size()) {
        const char ch = src[pos++];
        if (ch == '"') {
            return true;
        }
        if (ch == '\\' && pos < src.size()) {
            const char esc = src[pos++];
            switch (esc) {
                case '"':  out.push_back('"'); break;
                case '\\': out.push_back('\\'); break;
                case '/':  out.push_back('/'); break;
                case 'b':  out.push_back('\b'); break;
                case 'f':  out.push_back('\f'); break;
                case 'n':  out.push_back('\n'); break;
                case 'r':  out.push_back('\r'); break;
                case 't':  out.push_back('\t'); break;
                case 'u': {
                    if (pos + 4 <= src.size()) {
                        uint32_t cp = 0;
                        bool ok = true;
                        for (int k = 0; k < 4; ++k) {
                            const char h = src[pos + k];
                            cp <<= 4;
                            if (h >= '0' && h <= '9') cp |= static_cast<uint32_t>(h - '0');
                            else if (h >= 'a' && h <= 'f') cp |= static_cast<uint32_t>(h - 'a' + 10);
                            else if (h >= 'A' && h <= 'F') cp |= static_cast<uint32_t>(h - 'A' + 10);
                            else { ok = false; break; }
                        }
                        if (ok) {
                            pos += 4;
                            append_utf8(cp, out);
                        }
                    }
                    break;
                }
                default:
                    out.push_back(esc);
                    break;
            }
        } else {
            out.push_back(ch);
        }
    }
    return false;
}

void skip_ws_and_delim(const std::string& src, size_t& pos) {
    while (pos < src.size()) {
        const char c = src[pos];
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == ',' || c == ':') {
            ++pos;
        } else {
            break;
        }
    }
}

} // namespace

void LocalizationOverlay::set_active_instance(const LocalizationOverlay* loc) {
    g_active_loc_overlay = loc;
}

const LocalizationOverlay* LocalizationOverlay::active_instance() {
    return g_active_loc_overlay;
}

LocalizationOverlay::LocalizationOverlay(const RuntimeConfig& cfg) : cfg_(cfg) {
    std::vector<std::string> candidates;
    if (!cfg_.locale_overlay_path.empty()) {
        candidates.push_back(cfg_.locale_overlay_path);
    }
    candidates.push_back("assets/locales/zh_CN.json");
    candidates.push_back("../assets/locales/zh_CN.json");
    candidates.push_back("../../assets/locales/zh_CN.json");

    for (const auto& p : candidates) {
        if (!p.empty() && std::filesystem::exists(p) && load_dictionary(p)) {
            break;
        }
    }
}

bool LocalizationOverlay::load_dictionary(const std::string& json_path) {
    std::ifstream ifs(json_path, std::ios::binary);
    if (!ifs.is_open()) {
        return false;
    }
    std::ostringstream oss;
    oss << ifs.rdbuf();
    const std::string content = oss.str();

    id_to_zh_.clear();
    en_to_zh_.clear();
    en_norm_to_zh_.clear();

    size_t pos = 0;
    while (pos < content.size()) {
        skip_ws_and_delim(content, pos);
        if (pos >= content.size()) break;
        if (content[pos] == '{' || content[pos] == '}') {
            ++pos;
            continue;
        }
        if (content[pos] != '"') {
            ++pos;
            continue;
        }
        std::string key;
        if (!parse_json_string(content, pos, key)) {
            break;
        }
        skip_ws_and_delim(content, pos);
        if (pos >= content.size() || content[pos] != '"') {
            continue;
        }
        std::string val;
        if (!parse_json_string(content, pos, val)) {
            break;
        }

        if (key == "locale" || key == "game_id" || key == "font_atlas") {
            continue;
        }
        if (key.size() > 2 && key[0] == '0' && (key[1] == 'x' || key[1] == 'X')) {
            char* endp = nullptr;
            const unsigned long id = std::strtoul(key.c_str(), &endp, 16);
            if (endp && *endp == '\0') {
                id_to_zh_[static_cast<uint32_t>(id)] = val;
                continue;
            }
        }
        en_to_zh_[key] = val;
        const std::string stripped = strip_hex_tags(key);
        if (!stripped.empty() && en_to_zh_.find(stripped) == en_to_zh_.end()) {
            en_to_zh_[stripped] = val;
        }
        const std::string norm = normalize_lookup_key(key);
        if (!norm.empty()) {
            en_norm_to_zh_.emplace(norm, val);
        }
    }
    return (id_to_zh_.size() + en_to_zh_.size()) > 0u;
}

void LocalizationOverlay::hook_mes_set_language(PPCContext& ctx, Memory& mem) const {
    const uint32_t dst_addr = ctx.r[3];
    if (is_valid_ram(dst_addr)) {
        mem.write_u32(dst_addr, static_cast<uint32_t>(cfg_.language));
    }
    // Also mirror the GameLanguage enum inside runtime work / return r3 cleanly
    ctx.r[3] = static_cast<uint32_t>(cfg_.language);
}

std::string LocalizationOverlay::translate_by_id(uint32_t msg_id) const {
    auto it = id_to_zh_.find(msg_id);
    return (it != id_to_zh_.end()) ? it->second : std::string{};
}

std::string LocalizationOverlay::translate_text(const std::string& original_en) const {
    if (original_en.empty()) {
        return {};
    }
    auto it = en_to_zh_.find(original_en);
    if (it != en_to_zh_.end()) {
        return it->second;
    }
    const std::string trimmed = trim_ascii(original_en);
    it = en_to_zh_.find(trimmed);
    if (it != en_to_zh_.end()) {
        return it->second;
    }
    const std::string stripped = strip_hex_tags(original_en);
    it = en_to_zh_.find(stripped);
    if (it != en_to_zh_.end()) {
        return it->second;
    }
    const std::string norm = normalize_lookup_key(original_en);
    auto nit = en_norm_to_zh_.find(norm);
    if (nit != en_norm_to_zh_.end()) {
        return nit->second;
    }
    return original_en;
}

std::string LocalizationOverlay::decode_gc_moji_stream(const Memory& mem, uint32_t msg_vaddr, size_t max_words) const {
    if (!is_valid_ram(msg_vaddr)) {
        return {};
    }
    std::string out;
    out.reserve(64);
    for (size_t i = 0; i < max_words; ++i) {
        const uint16_t v = mem.read_u16(msg_vaddr + static_cast<uint32_t>(i * 2u));
        if (v == 0x0001u) {
            break;
        }
        append_gc_moji_token(out, v);
    }
    return trim_ascii(out);
}

std::string LocalizationOverlay::clean_overlay_display_text(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '<') {
            size_t j = i + 1;
            while (j < s.size() && std::isxdigit(static_cast<unsigned char>(s[j]))) {
                ++j;
            }
            if (j > i + 1 && j < s.size() && s[j] == '>') {
                const std::string tag = s.substr(i + 1, j - i - 1);
                if (tag == "04") {
                    if (!out.empty() && out.back() != '\n') {
                        out.push_back('\n');
                    }
                } else if (tag == "17c" || tag == "17C") {
                    out += "  ▶ ";
                }
                i = j;
                continue;
            }
        }
        out.push_back(s[i]);
    }
    return trim_ascii(out);
}

namespace {

// Decodes one UTF-8 code point starting at s[i]; advances i. Invalid bytes decode as single Latin-1 units.
uint32_t next_utf8_cp(const std::string& s, size_t& i, size_t& byte_len) {
    const unsigned char c = static_cast<unsigned char>(s[i]);
    size_t n = 1u;
    uint32_t cp = c;
    if (c >= 0xF0u && i + 3u < s.size() + 0u) { n = 4u; cp = c & 0x07u; }
    else if (c >= 0xE0u && i + 2u < s.size() + 0u) { n = 3u; cp = c & 0x0Fu; }
    else if (c >= 0xC0u && i + 1u < s.size() + 0u) { n = 2u; cp = c & 0x1Fu; }
    for (size_t k = 1u; k < n; ++k) {
        cp = (cp << 6u) | (static_cast<unsigned char>(s[i + k]) & 0x3Fu);
    }
    byte_len = n;
    i += n;
    return cp;
}

size_t cp_cols(uint32_t cp) {
    if (cp >= 0x1100u && (cp <= 0x115Fu || (cp >= 0x2E80u && cp <= 0xA4CFu) || (cp >= 0xAC00u && cp <= 0xD7A3u) ||
                          (cp >= 0xF900u && cp <= 0xFAFFu) || (cp >= 0xFE30u && cp <= 0xFE6Fu) ||
                          (cp >= 0xFF00u && cp <= 0xFF60u) || (cp >= 0xFFE0u && cp <= 0xFFE6u) ||
                          (cp >= 0x20000u && cp <= 0x3FFFDu))) {
        return 2u;
    }
    // Arrows / geometric shapes used for the '▶' continue marker render roughly full width.
    if (cp >= 0x2190u && cp <= 0x25FFu) return 2u;
    if (cp >= 0x2000u && cp <= 0x206Fu) return 2u; // general punctuation (curly quotes, ellipsis, em dash)
    return 1u;
}

// Closing punctuation must never start a wrapped line (kinsoku).
bool cp_no_line_start(uint32_t cp) {
    switch (cp) {
        case 0x3001u: case 0x3002u: case 0xFF0Cu: case 0xFF0Eu: case 0xFF01u: case 0xFF1Fu: case 0xFF1Bu:
        case 0xFF1Au: case 0xFF09u: case 0x3009u: case 0x300Bu: case 0x300Du: case 0x300Fu: case 0x3011u:
        case 0x2026u: case 0x2019u: case 0x201Du: case 0x2014u: case 0x00B7u:
        case '.': case ',': case '!': case '?': case ':': case ';': case ')': case ']': case '}':
            return true;
        default:
            return false;
    }
}

} // namespace

size_t LocalizationOverlay::display_cols(const std::string& utf8_line) {
    size_t cols = 0u;
    size_t i = 0u;
    while (i < utf8_line.size()) {
        size_t n = 1u;
        const uint32_t cp = next_utf8_cp(utf8_line, i, n);
        cols += cp_cols(cp);
    }
    return cols;
}

size_t LocalizationOverlay::count_cmes_page_index(const Memory& mem, uint32_t entry_ptr, uint32_t text_ptr) {
    if (!is_valid_ram(entry_ptr) || !is_valid_ram(text_ptr) || text_ptr <= entry_ptr) {
        return 0u;
    }
    // Mirror decode_gc_moji_stream(): stop at the 0x0001 terminator, at most 512 words.
    const uint32_t words = std::min<uint32_t>((text_ptr - entry_ptr) / 2u, 512u);
    size_t pages = 0u;
    for (uint32_t i = 0u; i < words; ++i) {
        const uint16_t v = mem.read_u16(entry_ptr + i * 2u);
        if (v == 0x0001u) {
            break;
        }
        if (v == 0x0004u) {
            ++pages;
        }
    }
    return pages;
}

std::string LocalizationOverlay::extract_page_segment(const std::string& raw_with_tags, size_t page_idx) {
    std::vector<std::string> pages;
    size_t start = 0u;
    for (size_t i = 0u; i < raw_with_tags.size(); ++i) {
        if (raw_with_tags[i] == '<' && i + 3u < raw_with_tags.size() + 0u && raw_with_tags[i + 1u] == '0' &&
            raw_with_tags[i + 2u] == '4' && raw_with_tags[i + 3u] == '>') {
            pages.push_back(raw_with_tags.substr(start, i - start));
            start = i + 4u;
            i += 3u;
        }
    }
    pages.push_back(raw_with_tags.substr(start));
    // A trailing "<04>" with nothing after it must not create an empty final page.
    while (pages.size() > 1u && trim_ascii(clean_overlay_display_text(pages.back())).empty()) {
        pages.pop_back();
    }
    return pages[std::min(page_idx, pages.size() - 1u)];
}

std::string LocalizationOverlay::wrap_comm_text(const std::string& text, size_t max_cols) {
    if (max_cols < 4u) {
        max_cols = 4u;
    }
    std::string out;
    out.reserve(text.size() + 8u);
    size_t line_cols = 0u;
    size_t line_start_out = 0u;       // index in `out` where the current line begins
    size_t last_space_out = std::string::npos; // index in `out` of last ASCII space on current line
    size_t cols_at_space = 0u;
    size_t i = 0u;
    while (i < text.size()) {
        const size_t cp_begin = i;
        size_t n = 1u;
        const uint32_t cp = next_utf8_cp(text, i, n);
        if (cp == '\n') {
            out.push_back('\n');
            line_cols = 0u;
            line_start_out = out.size();
            last_space_out = std::string::npos;
            continue;
        }
        if (cp == '\r') {
            continue;
        }
        const size_t w = cp_cols(cp);
        if (line_cols + w > max_cols && !(cp_no_line_start(cp) && line_cols + w <= max_cols + 2u)) {
            if (cp == ' ') {
                // swallow the space at the wrap point
                out.push_back('\n');
                line_cols = 0u;
                line_start_out = out.size();
                last_space_out = std::string::npos;
                continue;
            }
            const bool ascii_word = cp < 0x80u && cp != ' ';
            if (ascii_word && last_space_out != std::string::npos && last_space_out > line_start_out) {
                // move the partially written ASCII word to the next line
                const std::string tail = out.substr(last_space_out + 1u);
                out.resize(last_space_out);
                out.push_back('\n');
                line_start_out = out.size();
                out += tail;
                line_cols = line_cols - cols_at_space - 1u;
                last_space_out = std::string::npos;
            } else {
                out.push_back('\n');
                line_start_out = out.size();
                line_cols = 0u;
                last_space_out = std::string::npos;
            }
        }
        if (cp == ' ') {
            if (line_cols == 0u) {
                continue; // no leading blanks on wrapped lines
            }
            last_space_out = out.size();
            cols_at_space = line_cols;
        }
        out.append(text, cp_begin, n);
        line_cols += w;
    }
    return out;
}

LocalizationOverlay::CommLayout LocalizationOverlay::layout_dialogue(float base_x, float base_y, const std::string& display) {
    constexpr float kScale      = 0.74f;
    constexpr float kRightLimit = 572.0f; // GameCube comm-box right border in 640x480 space
    constexpr float kTopBandEnd = 132.0f; // top •CLIENT band must end above the center portrait cards
    constexpr float kGlyphPx    = 12.0f;  // rasterized width of one halfwidth column (24px em)
    constexpr float kLinePx     = 32.0f;  // rasterized line pitch (Microsoft YaHei 24px)
    constexpr float kPadPx      = 8.0f;

    CommLayout L;
    L.scale = kScale;
    L.text  = wrap_comm_text(display, 44u);

    size_t max_cols = 0u;
    size_t lines = 1u;
    size_t cur_begin = 0u;
    for (size_t i = 0u; i <= L.text.size(); ++i) {
        if (i == L.text.size() || L.text[i] == '\n') {
            max_cols = std::max(max_cols, display_cols(L.text.substr(cur_begin, i - cur_begin)));
            cur_begin = i + 1u;
            if (i != L.text.size()) {
                ++lines;
            }
        }
    }
    L.lines  = lines;
    L.width  = (static_cast<float>(max_cols) * kGlyphPx + kPadPx) * kScale;
    L.height = (static_cast<float>(lines) * kLinePx + kPadPx) * kScale;

    float x = base_x;
    if (base_x < 200.0f) {
        x = std::clamp(base_x, 52.0f, 120.0f);
    }
    x = std::min(x, kRightLimit - L.width);
    x = std::max(x, 24.0f);

    float y = base_y;
    if (base_y < 240.0f) {
        const float max_y = std::max(40.0f, kTopBandEnd - L.height);
        y = std::clamp(base_y, 40.0f, max_y);
    } else {
        const float max_y = std::max(342.0f, 436.0f - L.height);
        y = std::clamp(base_y, 342.0f, max_y);
    }
    L.x = x;
    L.y = y;
    return L;
}

void LocalizationOverlay::begin_frame() const {
    std::lock_guard<std::mutex> lock(g_loc_frame_mtx);
    frame_emitted_mes_ptrs_.clear();
}

bool LocalizationOverlay::try_on_mes_work_trans(uint32_t mes_wk_vaddr, const Memory& mem) const {
    if (cfg_.language != GameLanguage::SimplifiedChinese || !cfg_.enable_hd_chinese_font) {
        return false;
    }
    if (!is_valid_ram(mes_wk_vaddr)) {
        return false;
    }
    // CMesCtrl::MesTrans only processes slots whose status word (+0x00) has bit 0 set.
    // CMesCtrl::MesClear (0x8009F208) zeroes +0x00 without clearing stale +0x40/+0x44/+0x1E58.
    if ((mem.read_u32(mes_wk_vaddr + 0u) & 1u) == 0u) {
        return false;
    }

    const uint32_t text_ptr  = mem.read_u32(mes_wk_vaddr + kMesOffTextPtr);
    const uint32_t lang_base = mem.read_u32(mes_wk_vaddr + kMesOffLangBase);
    const uint32_t q_end     = mem.read_u32(mes_wk_vaddr + kMesOffMsgQueEnd);
    const uint32_t msg_id    = mem.read_u32(mes_wk_vaddr + kMesOffMsgId);

    const uint32_t entry_ptr = resolve_cmes_entry_start(mem, lang_base, text_ptr);
    const bool has_ptr       = is_valid_ram(text_ptr);
    const bool has_que       = (q_end > mes_wk_vaddr + kMesOffMsgQue) && (q_end <= mes_wk_vaddr + kMesOffMsgQueEnd);
    if (entry_ptr == 0u && !has_ptr && !has_que && msg_id == 0u) {
        return false;
    }

    uint32_t dedup_key = 0u;
    std::string zh;
    size_t page_idx = 0u; // active 0x0004-delimited dialogue page (0-based)
    auto try_translate_stream = [&](uint32_t va) {
        const std::string decoded = decode_gc_moji_stream(mem, va, 512);
        if (!decoded.empty()) {
            const std::string tr = translate_text(decoded);
            if (tr != decoded) {
                zh = tr;
                dedup_key = va;
                return true;
            }
        }
        return false;
    };

    // Prefer the true start of the message in lang_base (+0x44) because MesWorkMove advances
    // text_ptr (+0x40) in-place until it points to the trailing 0x0001/0x0004 terminator.
    if (entry_ptr != 0u) {
        if (try_translate_stream(entry_ptr)) {
            // CMesWk::code04 advances text_ptr past each confirmed 0x0004 page break, so the number of
            // 0x0004 words in [entry_ptr, text_ptr) is exactly the index of the page being shown.
            page_idx = count_cmes_page_index(mem, entry_ptr, text_ptr);
        }
    }
    if (zh.empty() && has_ptr) {
        try_translate_stream(text_ptr);
    }
    if (zh.empty() && has_que) {
        const std::string decoded = decode_cmes_msg_que(mem, mes_wk_vaddr);
        if (!decoded.empty()) {
            const std::string tr = translate_text(decoded);
            if (tr != decoded) {
                zh = tr;
                dedup_key = mes_wk_vaddr;
            }
        }
    }
    if (zh.empty() && msg_id != 0u) {
        zh = translate_by_id(msg_id);
        dedup_key = 0xF0000000u | (msg_id & 0x0FFFFFFFu);
        if (!zh.empty() && entry_ptr != 0u) {
            page_idx = count_cmes_page_index(mem, entry_ptr, text_ptr);
        }
    }
    if (zh.empty()) {
        return false;
    }

    // Render ONLY the active page; later pages appear after the player confirms (code04 -> next 0x0004 segment).
    const std::string display = clean_overlay_display_text(extract_page_segment(zh, page_idx));
    if (display.empty()) {
        return false;
    }
    dedup_key ^= static_cast<uint32_t>(page_idx) * 0x9E3779B9u;

    {
        std::lock_guard<std::mutex> lock(g_loc_frame_mtx);
        if (std::find(frame_emitted_mes_ptrs_.begin(), frame_emitted_mes_ptrs_.end(), dedup_key) != frame_emitted_mes_ptrs_.end()) {
            return true;
        }
        frame_emitted_mes_ptrs_.push_back(dedup_key);
    }

    uint32_t rgba = mem.read_u32(mes_wk_vaddr + kMesOffRgba);
    if ((rgba & 0xFFu) == 0u) {
        rgba = 0xFFFFFFFFu;
    }

    const int16_t qx = static_cast<int16_t>(mem.read_u16(mes_wk_vaddr + kMesOffMsgQueX));
    const int16_t qy = static_cast<int16_t>(mem.read_u16(mes_wk_vaddr + kMesOffMsgQueY));
    const float base_x = (qx > 0 && qx < 620) ? static_cast<float>(qx) : 56.0f;
    const float base_y = (qy > 0 && qy < 460) ? static_cast<float>(qy) : 368.0f;
    const CommLayout lay = layout_dialogue(base_x, base_y, display);
    global_gx_3d_interface().submit_overlay_text(lay.x, lay.y, lay.scale, rgba, lay.text);
    return true;
}

void LocalizationOverlay::on_mes_work_trans(uint32_t mes_wk_vaddr, const Memory& mem) const {
    (void)try_on_mes_work_trans(mes_wk_vaddr, mem);
}

bool LocalizationOverlay::hook_font_draw(PPCContext& ctx, Memory& mem) const {
    if (cfg_.language != GameLanguage::SimplifiedChinese || !cfg_.enable_hd_chinese_font) {
        return false;
    }
    const uint32_t str_va = ctx.r[3];
    const uint32_t col_va = ctx.r[4];
    const int32_t  x      = static_cast<int32_t>(ctx.r[5]);
    const int32_t  y      = static_cast<int32_t>(ctx.r[6]);
    if (!is_valid_ram(str_va)) {
        return false;
    }
    const std::string src = mem.read_cstring(str_va, 256);
    if (src.empty()) {
        return false;
    }
    const std::string tr = translate_text(src);
    if (tr.empty() || tr == src) {
        return false;
    }
    const std::string display = clean_overlay_display_text(tr);
    if (display.empty()) {
        return false;
    }
    uint32_t rgba = 0xFFFFFFFFu;
    if (is_valid_ram(col_va)) {
        rgba = mem.read_u32(col_va);
        if ((rgba & 0xFFu) == 0u) rgba |= 0xFFu;
    }
    const float fx = std::clamp(static_cast<float>(x), 8.0f, 600.0f);
    const float fy = std::clamp(static_cast<float>(y), 8.0f, 456.0f);
    global_gx_3d_interface().submit_overlay_text(fx, fy, 1.0f, rgba, display);
    return true;
}

void LocalizationOverlay::hook_eprintf_buffering(PPCContext& ctx, Memory& mem) const {
    if (cfg_.language != GameLanguage::SimplifiedChinese || !cfg_.enable_hd_chinese_font) {
        return;
    }
    const uint32_t font_va = ctx.r[3];
    const uint32_t str_va  = ctx.r[4];
    if (!is_valid_ram(font_va) || !is_valid_ram(str_va)) {
        return;
    }
    const std::string src = mem.read_cstring(str_va, 256);
    if (src.empty()) {
        return;
    }
    const std::string tr = translate_text(src);
    if (tr.empty() || tr == src) {
        return;
    }
    const std::string display = clean_overlay_display_text(tr);
    if (display.empty()) {
        return;
    }
    // tagFONT begins with cursor coordinates (s16/s32 x, y) + GXColor; clamp safely
    const int16_t tx = static_cast<int16_t>(mem.read_u16(font_va + 2u));
    const int16_t ty = static_cast<int16_t>(mem.read_u16(font_va + 6u));
    const float fx = (tx > 0 && tx < 620) ? static_cast<float>(tx) : 40.0f;
    const float fy = (ty > 0 && ty < 460) ? static_cast<float>(ty) : 40.0f;
    global_gx_3d_interface().submit_overlay_text(fx, fy, 1.0f, 0xFFFFFFFFu, display);
}

void LocalizationOverlay::emit_active_ui_scene_overlays(const Memory& mem) const {
    if (cfg_.language != GameLanguage::SimplifiedChinese || !cfg_.enable_hd_chinese_font) {
        return;
    }
    for (uint32_t i = 0; i < kCMesWkSlots; ++i) {
        const uint32_t wk_va = kCMesWkBase + i * kCMesWkStride;
        if ((mem.read_u32(wk_va + 0u) & 1u) == 0u) {
            continue;
        }
        const uint32_t ptr   = mem.read_u32(wk_va + kMesOffTextPtr);
        const uint32_t lbase = mem.read_u32(wk_va + kMesOffLangBase);
        const uint32_t q_end = mem.read_u32(wk_va + kMesOffMsgQueEnd);
        const bool has_que   = (q_end > wk_va + kMesOffMsgQue) && (q_end <= wk_va + kMesOffMsgQueEnd);
        if (is_valid_ram(ptr) || is_valid_ram(lbase) || has_que) {
            (void)try_on_mes_work_trans(wk_va, mem);
        }
    }
}

std::string LocalizationOverlay::resolve_localized_asset_path(const std::string& orig_path) const {
    if (cfg_.language != GameLanguage::SimplifiedChinese) {
        return orig_path;
    }
    const std::string mod_rel = "assets/locales/zh_CN/iso_override/" + orig_path;
    if (std::filesystem::exists(mod_rel)) {
        return mod_rel;
    }
    return orig_path;
}

} // namespace pn03

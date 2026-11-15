#include "pn03_logger.hpp"

#include <algorithm>
#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;

namespace pn03 {

namespace {

struct ArchiveEntry {
    fs::path path;
    uint64_t size = 0;
    fs::file_time_type mtime{};
    std::string name;
};

static std::string to_lower_ascii(std::string s) {
    for (char& ch : s) {
        if (ch >= 'A' && ch <= 'Z') {
            ch = static_cast<char>(ch - 'A' + 'a');
        }
    }
    return s;
}

static bool has_log_extension(const fs::path& p) {
    return to_lower_ascii(p.extension().string()) == ".log";
}

static void format_local_timestamp(std::string& out_log_ts, std::string& out_file_ts) {
    using namespace std::chrono;
    const auto now = system_clock::now();
    const auto ms  = duration_cast<milliseconds>(now.time_since_epoch()).count() % 1000;
    const std::time_t tt = system_clock::to_time_t(now);
    std::tm tm_val{};
#ifdef _WIN32
    localtime_s(&tm_val, &tt);
#else
    localtime_r(&tt, &tm_val);
#endif
    char buf_log[32];
    std::snprintf(buf_log, sizeof(buf_log),
                  "%04d-%02d-%02d %02d:%02d:%02d.%03d",
                  tm_val.tm_year + 1900, tm_val.tm_mon + 1, tm_val.tm_mday,
                  tm_val.tm_hour, tm_val.tm_min, tm_val.tm_sec, static_cast<int>(ms));
    out_log_ts = buf_log;

    char buf_file[32];
    std::snprintf(buf_file, sizeof(buf_file),
                  "%04d%02d%02d_%02d%02d%02d",
                  tm_val.tm_year + 1900, tm_val.tm_mon + 1, tm_val.tm_mday,
                  tm_val.tm_hour, tm_val.tm_min, tm_val.tm_sec);
    out_file_ts = buf_file;
}

} // namespace

Logger::~Logger() {
    shutdown();
}

LogLevel Logger::parse_level(const std::string& s, LogLevel fallback) {
    const std::string v = to_lower_ascii(s);
    if (v == "trace") return LogLevel::Trace;
    if (v == "debug") return LogLevel::Debug;
    if (v == "info")  return LogLevel::Info;
    if (v == "warn" || v == "warning") return LogLevel::Warn;
    if (v == "error" || v == "err")    return LogLevel::Error;
    if (v == "off" || v == "none")     return LogLevel::Off;
    return fallback;
}

const char* Logger::level_name(LogLevel lvl) {
    switch (lvl) {
        case LogLevel::Trace: return "TRACE";
        case LogLevel::Debug: return "DEBUG";
        case LogLevel::Info:  return "INFO ";
        case LogLevel::Warn:  return "WARN ";
        case LogLevel::Error: return "ERROR";
        case LogLevel::Off:   return "OFF  ";
        default:              return "INFO ";
    }
}

bool Logger::init(const LogConfig& cfg) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (stream_.is_open()) {
        stream_.flush();
        stream_.close();
    }

    cfg_ = cfg;
    if (cfg_.log_dir.empty()) cfg_.log_dir = "logs";
    if (cfg_.base_name.empty()) cfg_.base_name = "pn03_runtime";
    if (cfg_.max_file_bytes < 256u) cfg_.max_file_bytes = 256u;
    if (cfg_.max_total_bytes < cfg_.max_file_bytes) cfg_.max_total_bytes = cfg_.max_file_bytes;
    if (cfg_.max_files < 1u) cfg_.max_files = 1u;

    min_level_.store(static_cast<int>(cfg_.min_level), std::memory_order_release);

    std::error_code ec;
    fs::create_directories(cfg_.log_dir, ec);
    if (ec) {
        initialized_.store(false, std::memory_order_release);
        return false;
    }

    active_path_ = (fs::path(cfg_.log_dir) / (cfg_.base_name + ".log")).string();
    if (!open_active_file_locked()) {
        initialized_.store(false, std::memory_order_release);
        return false;
    }
    prune_old_logs_locked();
    initialized_.store(true, std::memory_order_release);
    return true;
}

void Logger::shutdown() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (stream_.is_open()) {
        stream_.flush();
        stream_.close();
    }
    initialized_.store(false, std::memory_order_release);
}

void Logger::set_level(LogLevel lvl) {
    std::lock_guard<std::mutex> lock(mutex_);
    cfg_.min_level = lvl;
    min_level_.store(static_cast<int>(lvl), std::memory_order_release);
}

void Logger::set_mirror_stderr(bool enable) {
    std::lock_guard<std::mutex> lock(mutex_);
    cfg_.mirror_stderr = enable;
}

bool Logger::open_active_file_locked() {
    std::error_code ec;
    const fs::path p(active_path_);
    if (fs::exists(p, ec)) {
        const uint64_t existing_sz = static_cast<uint64_t>(fs::file_size(p, ec));
        if (!ec && existing_sz >= cfg_.max_file_bytes) {
            current_bytes_ = existing_sz;
            rotate_locked();
            return stream_.is_open();
        }
        current_bytes_ = ec ? 0 : existing_sz;
    } else {
        current_bytes_ = 0;
    }

    stream_.open(p, std::ios::binary | std::ios::app);
    return stream_.is_open();
}

void Logger::rotate_locked() {
    if (stream_.is_open()) {
        stream_.flush();
        stream_.close();
    }

    std::string log_ts, file_ts;
    format_local_timestamp(log_ts, file_ts);

    const fs::path src(active_path_);
    std::error_code ec;
    if (fs::exists(src, ec)) {
        fs::path dst;
        for (int attempt = 0; attempt < 10000; ++attempt) {
            char seqbuf[16];
            std::snprintf(seqbuf, sizeof(seqbuf), "%04u", (++rotate_seq_) % 10000u);
            dst = fs::path(cfg_.log_dir) / (cfg_.base_name + "_" + file_ts + "_" + seqbuf + ".log");
            if (!fs::exists(dst, ec)) break;
        }
        fs::rename(src, dst, ec);
        if (ec) {
            fs::remove(src, ec);
        }
    }

    current_bytes_ = 0;
    stream_.open(src, std::ios::binary | std::ios::trunc);
    prune_old_logs_locked();
}

void Logger::prune_old_logs_locked() {
    std::error_code ec;
    const fs::path dir(cfg_.log_dir);
    if (!fs::exists(dir, ec)) return;

    const fs::path active_norm = fs::weakly_canonical(fs::path(active_path_), ec);
    const std::string active_name = fs::path(active_path_).filename().string();

    std::vector<ArchiveEntry> archives;
    uint64_t total_bytes = current_bytes_;
    if (total_bytes == 0 && fs::exists(active_path_, ec)) {
        total_bytes = static_cast<uint64_t>(fs::file_size(active_path_, ec));
    }

    for (const auto& entry : fs::directory_iterator(dir, ec)) {
        if (!entry.is_regular_file(ec)) continue;
        const fs::path p = entry.path();
        if (!has_log_extension(p)) continue;
        if (p.filename().string() == active_name) continue;
        if (!active_norm.empty()) {
            std::error_code ec2;
            if (fs::weakly_canonical(p, ec2) == active_norm) continue;
        }

        const uint64_t sz = static_cast<uint64_t>(entry.file_size(ec));
        const auto mt = entry.last_write_time(ec);
        total_bytes += sz;
        archives.push_back(ArchiveEntry{p, sz, mt, p.filename().string()});
    }

    std::sort(archives.begin(), archives.end(), [](const ArchiveEntry& a, const ArchiveEntry& b) {
        if (a.mtime != b.mtime) return a.mtime < b.mtime;
        return a.name < b.name;
    });

    size_t idx = 0;
    while (idx < archives.size() &&
           (total_bytes > cfg_.max_total_bytes || (archives.size() - idx + 1u) > cfg_.max_files)) {
        std::error_code rm_ec;
        if (fs::remove(archives[idx].path, rm_ec)) {
            if (total_bytes >= archives[idx].size) total_bytes -= archives[idx].size;
            else total_bytes = 0;
        }
        ++idx;
    }
}

uint64_t Logger::total_directory_log_bytes_locked() const {
    std::error_code ec;
    const fs::path dir(cfg_.log_dir);
    if (!fs::exists(dir, ec)) return 0;
    uint64_t total = 0;
    for (const auto& entry : fs::directory_iterator(dir, ec)) {
        if (!entry.is_regular_file(ec)) continue;
        if (has_log_extension(entry.path())) {
            total += static_cast<uint64_t>(entry.file_size(ec));
        }
    }
    return total;
}

void Logger::log(LogLevel lvl, const char* category, const std::string& msg) {
    if (!should_log(lvl)) return;

    std::string log_ts, file_ts;
    format_local_timestamp(log_ts, file_ts);

    const uint32_t frame = current_frame_.load(std::memory_order_relaxed);
    const char* cat = (category && category[0]) ? category : "CORE";

    std::string clean_msg = msg;
    while (!clean_msg.empty() && (clean_msg.back() == '\n' || clean_msg.back() == '\r')) {
        clean_msg.pop_back();
    }

    char prefix[96];
    std::snprintf(prefix, sizeof(prefix), "%s [%s] [f=%06u] [%-8.8s] ",
                  log_ts.c_str(), level_name(lvl), frame, cat);

    std::string line;
    line.reserve(std::char_traits<char>::length(prefix) + clean_msg.size() + 1u);
    line += prefix;
    line += clean_msg;
    line += '\n';

    std::lock_guard<std::mutex> lock(mutex_);
    if (!initialized_.load(std::memory_order_relaxed)) return;

    if (current_bytes_ > 0 && current_bytes_ + line.size() > cfg_.max_file_bytes) {
        rotate_locked();
    }

    if (stream_.is_open()) {
        stream_.write(line.data(), static_cast<std::streamsize>(line.size()));
        current_bytes_ += line.size();
        ++line_counter_;
        if (static_cast<int>(lvl) >= static_cast<int>(LogLevel::Warn) ||
            lvl == LogLevel::Trace ||
            (line_counter_ & 31u) == 0u) {
            stream_.flush();
        }
        if (current_bytes_ >= cfg_.max_file_bytes) {
            rotate_locked();
        }
    }

    if (cfg_.mirror_stderr) {
        std::cerr << line;
        if (static_cast<int>(lvl) >= static_cast<int>(LogLevel::Warn)) {
            std::cerr.flush();
        }
    }
}

void Logger::logf(LogLevel lvl, const char* category, const char* fmt, ...) {
    if (!should_log(lvl) || !fmt) return;

    char stack_buf[1024];
    va_list args;
    va_start(args, fmt);
    va_list args_copy;
    va_copy(args_copy, args);
    int n = std::vsnprintf(stack_buf, sizeof(stack_buf), fmt, args);
    va_end(args);

    if (n < 0) {
        va_end(args_copy);
        return;
    }

    if (static_cast<size_t>(n) < sizeof(stack_buf)) {
        va_end(args_copy);
        log(lvl, category, std::string(stack_buf, static_cast<size_t>(n)));
    } else {
        std::string big(static_cast<size_t>(n) + 1u, '\0');
        std::vsnprintf(big.data(), big.size(), fmt, args_copy);
        va_end(args_copy);
        big.resize(static_cast<size_t>(n));
        log(lvl, category, big);
    }
}

void Logger::flush() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (stream_.is_open()) {
        stream_.flush();
    }
}

void Logger::prune_old_logs() {
    std::lock_guard<std::mutex> lock(mutex_);
    prune_old_logs_locked();
}

std::string Logger::active_log_path() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return active_path_;
}

uint64_t Logger::total_directory_log_bytes() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return total_directory_log_bytes_locked();
}

uint32_t Logger::archive_count() const {
    std::lock_guard<std::mutex> lock(mutex_);
    std::error_code ec;
    const fs::path dir(cfg_.log_dir);
    if (!fs::exists(dir, ec)) return 0;
    const std::string active_name = fs::path(active_path_).filename().string();
    uint32_t count = 0;
    for (const auto& entry : fs::directory_iterator(dir, ec)) {
        if (!entry.is_regular_file(ec)) continue;
        if (!has_log_extension(entry.path())) continue;
        if (entry.path().filename().string() != active_name) ++count;
    }
    return count;
}

Logger& global_logger() {
    static Logger instance;
    return instance;
}

} // namespace pn03

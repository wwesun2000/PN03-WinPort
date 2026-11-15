#pragma once
#include <atomic>
#include <cstdint>
#include <fstream>
#include <mutex>
#include <string>

namespace pn03 {

enum class LogLevel : int {
    Trace = 0,
    Debug = 1,
    Info  = 2,
    Warn  = 3,
    Error = 4,
    Off   = 5
};

struct LogConfig {
    std::string log_dir         = "logs";
    std::string base_name       = "pn03_runtime";
    uint64_t    max_file_bytes  = 4ull * 1024ull * 1024ull;
    uint64_t    max_total_bytes = 16ull * 1024ull * 1024ull;
    uint32_t    max_files       = 12;
    LogLevel    min_level       = LogLevel::Info;
    bool        mirror_stderr   = false;
};

class Logger {
public:
    Logger() = default;
    ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    bool init(const LogConfig& cfg);
    void shutdown();
    bool is_initialized() const { return initialized_.load(std::memory_order_acquire); }

    void set_level(LogLevel lvl);
    LogLevel level() const { return static_cast<LogLevel>(min_level_.load(std::memory_order_acquire)); }

    void set_mirror_stderr(bool enable);
    bool should_log(LogLevel lvl) const {
        return initialized_.load(std::memory_order_acquire) &&
               static_cast<int>(lvl) >= min_level_.load(std::memory_order_acquire) &&
               min_level_.load(std::memory_order_acquire) < static_cast<int>(LogLevel::Off);
    }

    void set_current_frame(uint32_t frame) { current_frame_.store(frame, std::memory_order_relaxed); }
    uint32_t current_frame() const { return current_frame_.load(std::memory_order_relaxed); }

    void log(LogLevel lvl, const char* category, const std::string& msg);
    void logf(LogLevel lvl, const char* category, const char* fmt, ...);
    void flush();
    void prune_old_logs();

    std::string active_log_path() const;
    uint64_t total_directory_log_bytes() const;
    uint32_t archive_count() const;

    static LogLevel parse_level(const std::string& s, LogLevel fallback = LogLevel::Info);
    static const char* level_name(LogLevel lvl);

private:
    bool open_active_file_locked();
    void rotate_locked();
    void prune_old_logs_locked();
    uint64_t total_directory_log_bytes_locked() const;

    LogConfig cfg_{};
    mutable std::mutex mutex_;
    std::ofstream stream_;
    std::string active_path_;
    uint64_t current_bytes_ = 0;
    uint64_t line_counter_  = 0;
    uint32_t rotate_seq_    = 0;
    std::atomic<bool> initialized_{false};
    std::atomic<int> min_level_{static_cast<int>(LogLevel::Info)};
    std::atomic<uint32_t> current_frame_{0};
};

Logger& global_logger();

inline void log_msg(LogLevel lvl, const char* category, const std::string& msg) {
    Logger& l = global_logger();
    if (l.should_log(lvl)) {
        l.log(lvl, category, msg);
    }
}

#define PN03_LOG(lvl, cat, msg) ::pn03::log_msg((lvl), (cat), (msg))
#define PN03_LOGF(lvl, cat, ...) \
    do { \
        auto& _pn03_lg = ::pn03::global_logger(); \
        if (_pn03_lg.should_log((lvl))) { \
            _pn03_lg.logf((lvl), (cat), __VA_ARGS__); \
        } \
    } while (0)

} // namespace pn03

#pragma once
#include <bit>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#ifdef _MSC_VER
#ifndef PN03_HAS_MSVC_BUILTIN_CLZ
#define PN03_HAS_MSVC_BUILTIN_CLZ 1
static inline int __builtin_clz(unsigned int x) noexcept {
    return std::countl_zero(x);
}
#endif
#define PN03_FORCEINLINE __forceinline
#define PN03_NOINLINE __declspec(noinline)
#else
#define PN03_FORCEINLINE inline
#define PN03_NOINLINE
#endif

namespace pn03 {

// GameCube 1T-SRAM Main Memory Constants (24 MB @ 0x80000000..0x817FFFFF)
constexpr uint32_t kGcRamBase       = 0x80000000u;
constexpr uint32_t kGcRamSize       = 0x01800000u; // 24 MB
constexpr uint32_t kGcEntryPoint    = 0x80003100u;
constexpr uint32_t kGcInitialSp     = 0x802808A0u;
constexpr uint32_t kGcSda1Base      = 0x80275BE0u; // r13 (_SDA_BASE_)
constexpr uint32_t kGcSda2Base      = 0x80285BE0u; // r2  (_SDA2_BASE_)
constexpr uint32_t kGcFifoAddr      = 0xCC008000u; // Flipper GX Write-Gather Pipe

PN03_FORCEINLINE uint16_t bswap16(uint16_t v) noexcept {
#ifdef _MSC_VER
    return _byteswap_ushort(v);
#else
    return static_cast<uint16_t>((v >> 8) | (v << 8));
#endif
}

PN03_FORCEINLINE uint32_t bswap32(uint32_t v) noexcept {
#ifdef _MSC_VER
    return _byteswap_ulong(v);
#else
    return ((v & 0xFF000000u) >> 24) |
           ((v & 0x00FF0000u) >> 8)  |
           ((v & 0x0000FF00u) << 8)  |
           ((v & 0x000000FFu) << 24);
#endif
}

PN03_FORCEINLINE uint64_t bswap64(uint64_t v) noexcept {
#ifdef _MSC_VER
    return _byteswap_uint64(v);
#else
    return ((v & 0xFF00000000000000ull) >> 56) |
           ((v & 0x00FF000000000000ull) >> 40) |
           ((v & 0x0000FF0000000000ull) >> 24) |
           ((v & 0x000000FF00000000ull) >> 8)  |
           ((v & 0x00000000FF000000ull) << 8)  |
           ((v & 0x0000000000FF0000ull) << 24) |
           ((v & 0x000000000000FF00ull) << 40) |
           ((v & 0x00000000000000FFull) << 56);
#endif
}

class Memory {
public:
    static constexpr uint32_t kRam1Base = kGcRamBase;
    static constexpr uint32_t kRam1Size = kGcRamSize;
    static constexpr uint32_t kAramBase = 0x90000000u;
    static constexpr uint32_t kAramSize = 0x01000000u;
    static constexpr uint32_t kLcBase   = 0xE0000000u;
    static constexpr uint32_t kLcSize   = 0x00004000u; // 16 KB Gekko Locked L1 Cache
    static constexpr uint32_t kMmioSize = 0x00010000u;

    // Hardware GX FIFO Write-Gather Pipe callbacks (0xCC008000)
    void* fifo_user = nullptr;
    void (*on_fifo_u8)(void* user, uint8_t val) = nullptr;
    void (*on_fifo_u16)(void* user, uint16_t val) = nullptr;
    void (*on_fifo_u32)(void* user, uint32_t val) = nullptr;
    void (*on_fifo_f32)(void* user, float val) = nullptr;

    static Memory*& active_instance() noexcept {
        static thread_local Memory* s_inst = nullptr;
        return s_inst;
    }

    Memory() : ram_(kGcRamSize, 0), aram_(kAramSize, 0), lc_(kLcSize, 0), mmio_(kMmioSize, 0) {
        active_instance() = this;
    }

    ~Memory() {
        if (active_instance() == this) {
            active_instance() = nullptr;
        }
    }

    Memory(const Memory& other)
        : fifo_user(other.fifo_user),
          on_fifo_u8(other.on_fifo_u8),
          on_fifo_u16(other.on_fifo_u16),
          on_fifo_u32(other.on_fifo_u32),
          on_fifo_f32(other.on_fifo_f32),
          ram_(other.ram_),
          aram_(other.aram_),
          lc_(other.lc_),
          mmio_(other.mmio_) {
        active_instance() = this;
    }

    Memory& operator=(const Memory& other) {
        if (this != &other) {
            fifo_user   = other.fifo_user;
            on_fifo_u8  = other.on_fifo_u8;
            on_fifo_u16 = other.on_fifo_u16;
            on_fifo_u32 = other.on_fifo_u32;
            on_fifo_f32 = other.on_fifo_f32;
            ram_        = other.ram_;
            aram_       = other.aram_;
            lc_         = other.lc_;
            mmio_       = other.mmio_;
            active_instance() = this;
        }
        return *this;
    }

    void set_fifo_callbacks(
        void* user,
        void (*u8_fn)(void*, uint8_t),
        void (*u16_fn)(void*, uint16_t),
        void (*u32_fn)(void*, uint32_t),
        void (*f32_fn)(void*, float)) noexcept {
        fifo_user   = user;
        on_fifo_u8  = u8_fn;
        on_fifo_u16 = u16_fn;
        on_fifo_u32 = u32_fn;
        on_fifo_f32 = f32_fn;
    }

    static inline bool is_fifo_addr(uint32_t vaddr) noexcept {
        return ((vaddr & 0xFFFF8000u) == 0xCC008000u) || ((vaddr & 0xFFFF8000u) == 0x0C008000u);
    }

    static inline bool is_mmio_addr(uint32_t vaddr) noexcept {
        return ((vaddr & 0xFFFF0000u) == 0xCC000000u) || ((vaddr & 0xFFFF0000u) == 0x0C000000u);
    }

    static inline uint32_t translate(uint32_t vaddr) noexcept {
        uint32_t phys = vaddr & 0x1FFFFFFFu;
        return (phys < kGcRamSize) ? phys : 0u;
    }

    PN03_FORCEINLINE uint8_t* fast_ram_ptr(uint32_t vaddr, size_t access_bytes) noexcept {
        if ((vaddr & 0xBE000000u) == 0x80000000u) [[likely]] {
            const uint32_t phys = vaddr & 0x01FFFFFFu;
            if (phys <= kGcRamSize && access_bytes <= (ram_.size() - phys)) [[likely]] {
                return ram_.data() + phys;
            }
        }
        return nullptr;
    }

    PN03_FORCEINLINE const uint8_t* fast_ram_ptr(uint32_t vaddr, size_t access_bytes) const noexcept {
        if ((vaddr & 0xBE000000u) == 0x80000000u) [[likely]] {
            const uint32_t phys = vaddr & 0x01FFFFFFu;
            if (phys <= kGcRamSize && access_bytes <= (ram_.size() - phys)) [[likely]] {
                return ram_.data() + phys;
            }
        }
        return nullptr;
    }

    PN03_FORCEINLINE uint8_t* translate(uint32_t vaddr, size_t access_bytes) noexcept {
        if (uint8_t* p = fast_ram_ptr(vaddr, access_bytes)) [[likely]] {
            return p;
        }
        return translate_slow(vaddr, access_bytes);
    }

    PN03_FORCEINLINE const uint8_t* translate(uint32_t vaddr, size_t access_bytes) const noexcept {
        if (const uint8_t* p = fast_ram_ptr(vaddr, access_bytes)) [[likely]] {
            return p;
        }
        return translate_slow(vaddr, access_bytes);
    }

    PN03_FORCEINLINE bool is_valid_range(uint32_t vaddr, size_t access_bytes = 1) const noexcept {
        if ((vaddr & 0xBE000000u) == 0x80000000u) [[likely]] {
            const uint32_t phys = vaddr & 0x01FFFFFFu;
            return (phys <= ram_.size()) && (access_bytes <= (ram_.size() - phys));
        }
        return is_valid_range_slow(vaddr, access_bytes);
    }

    PN03_FORCEINLINE uint8_t read_u8(uint32_t vaddr) const {
        if (const uint8_t* p = fast_ram_ptr(vaddr, 1)) [[likely]] {
            return *p;
        }
        return read_u8_slow(vaddr);
    }

    PN03_FORCEINLINE int8_t read_s8(uint32_t vaddr) const {
        return static_cast<int8_t>(read_u8(vaddr));
    }

    PN03_FORCEINLINE uint16_t read_u16(uint32_t vaddr) const {
        const uint8_t* p = translate(vaddr, 2);
        uint16_t raw = 0;
        std::memcpy(&raw, p, sizeof(uint16_t));
        return bswap16(raw);
    }

    PN03_FORCEINLINE int16_t read_s16(uint32_t vaddr) const {
        return static_cast<int16_t>(read_u16(vaddr));
    }

    PN03_FORCEINLINE uint32_t read_u32(uint32_t vaddr) const {
        const uint8_t* p = translate(vaddr, 4);
        uint32_t raw = 0;
        std::memcpy(&raw, p, sizeof(uint32_t));
        return bswap32(raw);
    }

    PN03_FORCEINLINE int32_t read_s32(uint32_t vaddr) const {
        return static_cast<int32_t>(read_u32(vaddr));
    }

    PN03_FORCEINLINE uint64_t read_u64(uint32_t vaddr) const {
        const uint8_t* p = translate(vaddr, 8);
        uint64_t raw = 0;
        std::memcpy(&raw, p, sizeof(uint64_t));
        return bswap64(raw);
    }

    PN03_FORCEINLINE float read_f32(uint32_t vaddr) const {
        uint32_t bits = read_u32(vaddr);
        float val = 0.0f;
        std::memcpy(&val, &bits, sizeof(float));
        return val;
    }

    PN03_FORCEINLINE double read_f64(uint32_t vaddr) const {
        uint64_t bits = read_u64(vaddr);
        double val = 0.0;
        std::memcpy(&val, &bits, sizeof(double));
        return val;
    }

    PN03_FORCEINLINE void write_u8(uint32_t vaddr, uint8_t val) {
        if (uint8_t* p = fast_ram_ptr(vaddr, 1)) [[likely]] {
            *p = val;
            return;
        }
        write_u8_slow(vaddr, val);
    }

    PN03_FORCEINLINE void write_u16(uint32_t vaddr, uint16_t val) {
        if (uint8_t* p = fast_ram_ptr(vaddr, 2)) [[likely]] {
            uint16_t be = bswap16(val);
            std::memcpy(p, &be, sizeof(uint16_t));
            return;
        }
        write_u16_slow(vaddr, val);
    }

    PN03_FORCEINLINE void write_u32(uint32_t vaddr, uint32_t val) {
        if (uint8_t* p = fast_ram_ptr(vaddr, 4)) [[likely]] {
            uint32_t be = bswap32(val);
            std::memcpy(p, &be, sizeof(uint32_t));
            return;
        }
        write_u32_slow(vaddr, val);
    }

    PN03_FORCEINLINE void write_u64(uint32_t vaddr, uint64_t val) {
        if (uint8_t* p = fast_ram_ptr(vaddr, 8)) [[likely]] {
            uint64_t be = bswap64(val);
            std::memcpy(p, &be, sizeof(uint64_t));
            return;
        }
        write_u64_slow(vaddr, val);
    }

    PN03_FORCEINLINE void write_f32(uint32_t vaddr, float val) {
        if (uint8_t* p = fast_ram_ptr(vaddr, 4)) [[likely]] {
            uint32_t bits = 0;
            std::memcpy(&bits, &val, sizeof(uint32_t));
            uint32_t be = bswap32(bits);
            std::memcpy(p, &be, sizeof(uint32_t));
            return;
        }
        write_f32_slow(vaddr, val);
    }

    PN03_FORCEINLINE void write_f64(uint32_t vaddr, double val) {
        uint64_t bits = 0;
        std::memcpy(&bits, &val, sizeof(uint64_t));
        write_u64(vaddr, bits);
    }

    std::string read_cstring(uint32_t vaddr, size_t max_len = 256) const {
        if (!is_valid_range(vaddr, 1)) return {};
        const uint8_t* p = translate(vaddr, 1);
        uint32_t off = vaddr & 0x1FFFFFFFu;
        std::string s;
        for (size_t i = 0; i < max_len && (off + i) < ram_.size(); ++i) {
            char c = static_cast<char>(p[i]);
            if (c == '\0') break;
            s.push_back(c);
        }
        return s;
    }

    const char* read_cstr(uint32_t vaddr) const {
        if (!is_valid_range(vaddr, 1)) return "";
        return reinterpret_cast<const char*>(translate(vaddr, 1));
    }

    void write_bytes(uint32_t vaddr, const void* src, size_t len) {
        if (len == 0) return;
        uint8_t* p = translate(vaddr, len);
        std::memcpy(p, src, len);
    }

    PN03_FORCEINLINE uint8_t* raw_ptr(uint32_t vaddr) {
        return translate(vaddr, 1);
    }

    PN03_FORCEINLINE const uint8_t* raw_ptr(uint32_t vaddr) const {
        return translate(vaddr, 1);
    }

    PN03_FORCEINLINE uint8_t* raw_ram() noexcept { return ram_.data(); }
    PN03_FORCEINLINE const uint8_t* raw_ram() const noexcept { return ram_.data(); }

    std::vector<uint8_t>& aram_buffer() noexcept { return aram_; }
    const std::vector<uint8_t>& aram_buffer() const noexcept { return aram_; }

private:
    PN03_NOINLINE uint8_t* translate_slow(uint32_t vaddr, size_t access_bytes) noexcept {
        if (is_mmio_addr(vaddr)) {
            uint32_t off = vaddr & 0xFFFFu;
            if (off + access_bytes <= mmio_.size()) return &mmio_[off];
        }
        if (vaddr >= kAramBase && vaddr < kAramBase + kAramSize && (vaddr - kAramBase) + access_bytes <= aram_.size()) {
            return &aram_[vaddr - kAramBase];
        }
        if (vaddr >= kLcBase && vaddr < kLcBase + kLcSize && (vaddr - kLcBase) + access_bytes <= lc_.size()) {
            return &lc_[vaddr - kLcBase];
        }
        uint32_t phys = vaddr & 0x1FFFFFFFu;
        if (((vaddr >= 0x80000000u && vaddr < 0x80000000u + kGcRamSize) ||
             (vaddr >= 0xC0000000u && vaddr < 0xC0000000u + kGcRamSize)) &&
            (phys + access_bytes <= ram_.size())) {
            return &ram_[phys];
        }
        return &mmio_[0];
    }

    PN03_NOINLINE const uint8_t* translate_slow(uint32_t vaddr, size_t access_bytes) const noexcept {
        if (is_mmio_addr(vaddr)) {
            uint32_t off = vaddr & 0xFFFFu;
            if (off + access_bytes <= mmio_.size()) return &mmio_[off];
        }
        if (vaddr >= kAramBase && vaddr < kAramBase + kAramSize && (vaddr - kAramBase) + access_bytes <= aram_.size()) {
            return &aram_[vaddr - kAramBase];
        }
        if (vaddr >= kLcBase && vaddr < kLcBase + kLcSize && (vaddr - kLcBase) + access_bytes <= lc_.size()) {
            return &lc_[vaddr - kLcBase];
        }
        uint32_t phys = vaddr & 0x1FFFFFFFu;
        if (((vaddr >= 0x80000000u && vaddr < 0x80000000u + kGcRamSize) ||
             (vaddr >= 0xC0000000u && vaddr < 0xC0000000u + kGcRamSize)) &&
            (phys + access_bytes <= ram_.size())) {
            return &ram_[phys];
        }
        return &mmio_[0];
    }

    PN03_NOINLINE bool is_valid_range_slow(uint32_t vaddr, size_t access_bytes) const noexcept {
        if (is_mmio_addr(vaddr)) {
            return ((vaddr & 0xFFFFu) + access_bytes) <= mmio_.size();
        }
        if (vaddr >= kAramBase && vaddr < kAramBase + kAramSize) {
            return ((vaddr - kAramBase) + access_bytes) <= aram_.size();
        }
        if (vaddr >= kLcBase && vaddr < kLcBase + kLcSize) {
            return ((vaddr - kLcBase) + access_bytes) <= lc_.size();
        }
        return false;
    }

    PN03_NOINLINE uint8_t read_u8_slow(uint32_t vaddr) const {
        if (is_mmio_addr(vaddr)) return mmio_[vaddr & 0xFFFFu];
        if (vaddr >= kAramBase && vaddr < kAramBase + kAramSize) return aram_[vaddr - kAramBase];
        if (vaddr >= kLcBase && vaddr < kLcBase + kLcSize) return lc_[vaddr - kLcBase];
        return ram_[translate(vaddr)];
    }

    PN03_NOINLINE void write_u8_slow(uint32_t vaddr, uint8_t val) {
        if (is_fifo_addr(vaddr)) {
            if (on_fifo_u8) on_fifo_u8(fifo_user, val);
            return;
        }
        *translate_slow(vaddr, 1) = val;
    }

    PN03_NOINLINE void write_u16_slow(uint32_t vaddr, uint16_t val) {
        if (is_fifo_addr(vaddr)) {
            if (on_fifo_u16) on_fifo_u16(fifo_user, val);
            return;
        }
        uint8_t* p = translate_slow(vaddr, 2);
        uint16_t be = bswap16(val);
        std::memcpy(p, &be, sizeof(uint16_t));
    }

    PN03_NOINLINE void write_u32_slow(uint32_t vaddr, uint32_t val) {
        if (is_fifo_addr(vaddr)) {
            if (on_fifo_u32) on_fifo_u32(fifo_user, val);
            return;
        }
        uint8_t* p = translate_slow(vaddr, 4);
        uint32_t be = bswap32(val);
        std::memcpy(p, &be, sizeof(uint32_t));
    }

    PN03_NOINLINE void write_u64_slow(uint32_t vaddr, uint64_t val) {
        if (is_fifo_addr(vaddr)) {
            if (on_fifo_u32) {
                on_fifo_u32(fifo_user, static_cast<uint32_t>(val >> 32));
                on_fifo_u32(fifo_user, static_cast<uint32_t>(val & 0xFFFFFFFFu));
            }
            return;
        }
        uint8_t* p = translate_slow(vaddr, 8);
        uint64_t be = bswap64(val);
        std::memcpy(p, &be, sizeof(uint64_t));
    }

    PN03_NOINLINE void write_f32_slow(uint32_t vaddr, float val) {
        if (is_fifo_addr(vaddr)) {
            if (on_fifo_f32) {
                on_fifo_f32(fifo_user, val);
            } else if (on_fifo_u32) {
                uint32_t bits = 0;
                std::memcpy(&bits, &val, sizeof(uint32_t));
                on_fifo_u32(fifo_user, bits);
            }
            return;
        }
        uint32_t bits = 0;
        std::memcpy(&bits, &val, sizeof(uint32_t));
        write_u32_slow(vaddr, bits);
    }
    std::vector<uint8_t> ram_;
    std::vector<uint8_t> aram_; // 16 MB Audio RAM
    std::vector<uint8_t> lc_;   // 16 KB Gekko Locked L1 Data Cache (0xE0000000..0xE0003FFF)
    std::vector<uint8_t> mmio_; // 64 KB MMIO space
};

struct PPCContext;
using RecompFuncPtr = void(*)(PPCContext&, Memory&);
using RecompiledFunc = RecompFuncPtr;

// Master Indirect Call Dispatcher (implemented in src/runtime/dolphin_sdk_hle.cpp)
bool dispatch_recompiled_function(uint32_t target_vaddr, PPCContext& ctx, Memory& mem);
bool try_hle_intercept(uint32_t target_vaddr, PPCContext& ctx, Memory& mem);

struct PPCContext {
    uint32_t r[32]{};
    double   f[32]{};
    float    ps0[32]{};
    float    ps1[32]{};
    uint8_t  cr[8]{}; // CR0..CR7 fields (4 bits each: LT=8, GT=4, EQ=2, SO=1)
    uint32_t lr  = 0;
    uint32_t ctr = 0;
    uint32_t xer = 0;
    uint32_t gqr[8]{};
    uint32_t pc  = kGcEntryPoint;
    uint32_t msr = 0x00008000u;
    uint32_t fpscr = 0;
    uint64_t tb_ticks = 0;
    uint64_t exec_raw_count = 0;
    Memory*  mem_ptr = nullptr;

    PPCContext() {
        reset();
    }

    void reset(uint32_t initial_sp = kGcInitialSp) {
        Memory* saved_mem = mem_ptr;
        std::memset(r, 0, sizeof(r));
        std::memset(f, 0, sizeof(f));
        std::memset(ps0, 0, sizeof(ps0));
        std::memset(ps1, 0, sizeof(ps1));
        std::memset(cr, 0, sizeof(cr));
        std::memset(gqr, 0, sizeof(gqr));
        r[1]  = initial_sp;
        r[2]  = kGcSda2Base;
        r[13] = kGcSda1Base;
        lr    = 0;
        ctr   = 0;
        xer   = 0;
        pc    = kGcEntryPoint;
        msr   = 0x00008000u;
        fpscr = 0;
        tb_ticks = 0;
        exec_raw_count = 0;
        mem_ptr = saved_mem;
    }

    inline void set_ca(bool ca) noexcept {
        if (ca) xer |= 0x20000000u;
        else    xer &= ~0x20000000u;
    }

    inline bool get_ca() const noexcept {
        return (xer & 0x20000000u) != 0;
    }

    // Gekko Paired-Singles Quantization / Dequantization via GQR[0..7]
    // Hardware layout: upper 16 bits = LD (scale [29:24], type [18:16]), lower 16 bits = ST (scale [13:8], type [2:0])
    static inline float gqr_dequant_scale(uint32_t scale6) noexcept {
        int32_t s = static_cast<int32_t>(scale6 & 0x3Fu);
        if (s & 0x20) s -= 64;
        return std::ldexp(1.0f, -s);
    }

    static inline float gqr_quant_scale(uint32_t scale6) noexcept {
        int32_t s = static_cast<int32_t>(scale6 & 0x3Fu);
        if (s & 0x20) s -= 64;
        return std::ldexp(1.0f, s);
    }

    static inline uint32_t gqr_elem_size(uint32_t qtype) noexcept {
        switch (qtype & 7u) {
            case 4u: // U8
            case 6u: // S8
                return 1u;
            case 5u: // U16
            case 7u: // S16
                return 2u;
            default: // float32
                return 4u;
        }
    }

    inline float read_quantized(const Memory& mem, uint32_t vaddr, uint32_t qtype, uint32_t scale6) const {
        switch (qtype & 7u) {
            case 4u: return static_cast<float>(mem.read_u8(vaddr)) * gqr_dequant_scale(scale6);
            case 5u: return static_cast<float>(mem.read_u16(vaddr)) * gqr_dequant_scale(scale6);
            case 6u: return static_cast<float>(mem.read_s8(vaddr)) * gqr_dequant_scale(scale6);
            case 7u: return static_cast<float>(mem.read_s16(vaddr)) * gqr_dequant_scale(scale6);
            default: return mem.read_f32(vaddr);
        }
    }

    inline void write_quantized(Memory& mem, uint32_t vaddr, float val, uint32_t qtype, uint32_t scale6) const {
        uint32_t qt = qtype & 7u;
        if (qt < 4u) {
            mem.write_f32(vaddr, val);
            return;
        }
        float v = std::isnan(val) ? 0.0f : (val * gqr_quant_scale(scale6));
        if (qt == 4u) {
            if (v < 0.0f) v = 0.0f; else if (v > 255.0f) v = 255.0f;
            mem.write_u8(vaddr, static_cast<uint8_t>(static_cast<int32_t>(v)));
        } else if (qt == 5u) {
            if (v < 0.0f) v = 0.0f; else if (v > 65535.0f) v = 65535.0f;
            mem.write_u16(vaddr, static_cast<uint16_t>(static_cast<int32_t>(v)));
        } else if (qt == 6u) {
            if (v < -128.0f) v = -128.0f; else if (v > 127.0f) v = 127.0f;
            mem.write_u8(vaddr, static_cast<uint8_t>(static_cast<int8_t>(static_cast<int32_t>(v))));
        } else {
            if (v < -32768.0f) v = -32768.0f; else if (v > 32767.0f) v = 32767.0f;
            mem.write_u16(vaddr, static_cast<uint16_t>(static_cast<int16_t>(static_cast<int32_t>(v))));
        }
    }

    inline void psq_load(const Memory& mem, int frd, uint32_t ea, bool w_bit, int gqr_idx) {
        uint32_t g = gqr[gqr_idx & 7];
        if (g == 0u) {
            ps0[frd] = mem.read_f32(ea);
            ps1[frd] = w_bit ? 1.0f : mem.read_f32(ea + 4u);
            return;
        }
        uint32_t qtype = (g >> 16) & 7u;
        uint32_t scale = (g >> 24) & 0x3Fu;
        ps0[frd] = read_quantized(mem, ea, qtype, scale);
        ps1[frd] = w_bit ? 1.0f : read_quantized(mem, ea + gqr_elem_size(qtype), qtype, scale);
    }

    inline void psq_store(Memory& mem, int frs, uint32_t ea, bool w_bit, int gqr_idx) const {
        uint32_t g = gqr[gqr_idx & 7];
        if (g == 0u) {
            mem.write_f32(ea, ps0[frs]);
            if (!w_bit) mem.write_f32(ea + 4u, ps1[frs]);
            return;
        }
        uint32_t qtype = g & 7u;
        uint32_t scale = (g >> 8) & 0x3Fu;
        write_quantized(mem, ea, ps0[frs], qtype, scale);
        if (!w_bit) write_quantized(mem, ea + gqr_elem_size(qtype), ps1[frs], qtype, scale);
    }

    inline void cmp_s32(int crf, int32_t a, int32_t b) {
        uint8_t flags = (xer & 0x80000000u) ? 0x1u : 0x0u;
        if (a < b) flags |= 0x8u;
        else if (a > b) flags |= 0x4u;
        else flags |= 0x2u;
        cr[crf & 7] = flags;
    }

    inline void cmp_u32(int crf, uint32_t a, uint32_t b) {
        uint8_t flags = (xer & 0x80000000u) ? 0x1u : 0x0u;
        if (a < b) flags |= 0x8u;
        else if (a > b) flags |= 0x4u;
        else flags |= 0x2u;
        cr[crf & 7] = flags;
    }

    inline void cmp_f64(int crf, double a, double b) {
        uint8_t flags = 0;
        if (std::isnan(a) || std::isnan(b)) flags = 0x1u;
        else if (a < b) flags = 0x8u;
        else if (a > b) flags = 0x4u;
        else flags = 0x2u;
        cr[crf & 7] = flags;
    }

    inline uint32_t pack_cr() const {
        uint32_t v = 0;
        for (int i = 0; i < 8; ++i) {
            v |= (static_cast<uint32_t>(cr[i] & 0xFu) << ((7 - i) * 4));
        }
        return v;
    }

    inline void unpack_cr(uint32_t crm, uint32_t val) {
        for (int i = 0; i < 8; ++i) {
            if ((crm >> (7 - i)) & 1u) {
                cr[i] = static_cast<uint8_t>((val >> ((7 - i) * 4)) & 0xFu);
            }
        }
    }

    inline bool get_cr_bit(int bit_idx) const {
        int crf = (bit_idx >> 2) & 7;
        int sub = 3 - (bit_idx & 3);
        return ((cr[crf] >> sub) & 1) != 0;
    }

    inline void set_cr_bit(int bit_idx, bool v) {
        int crf = (bit_idx >> 2) & 7;
        int sub = 3 - (bit_idx & 3);
        if (v) cr[crf] |= static_cast<uint8_t>(1u << sub);
        else   cr[crf] &= static_cast<uint8_t>(~(1u << sub));
    }

    inline bool eval_bc(uint32_t bo, uint32_t bi) {
        if (!(bo & 0x04)) {
            ctr -= 1;
        }
        bool ctr_ok = (bo & 0x04) || ((bo & 0x02) ? (ctr == 0) : (ctr != 0));
        bool bit_set = get_cr_bit(static_cast<int>(bi));
        bool cond_ok = (bo & 0x10) || ((bo & 0x08) ? bit_set : !bit_set);
        return ctr_ok && cond_ok;
    }

    PN03_FORCEINLINE void lmw(Memory& mem, int start_reg, uint32_t addr) {
        mem_ptr = &mem;
        if (start_reg >= 0 && start_reg < 32) [[likely]] {
            if (const uint8_t* p = mem.fast_ram_ptr(addr, static_cast<size_t>(32 - start_reg) * 4u)) [[likely]] {
                for (int reg = start_reg; reg < 32; ++reg, p += 4) {
                    uint32_t raw = 0;
                    std::memcpy(&raw, p, sizeof(uint32_t));
                    r[reg] = bswap32(raw);
                }
                return;
            }
        }
        for (int reg = start_reg; reg < 32; ++reg, addr += 4) {
            r[reg] = mem.read_u32(addr);
        }
    }

    PN03_FORCEINLINE void stmw(Memory& mem, int start_reg, uint32_t addr) {
        mem_ptr = &mem;
        if (start_reg >= 0 && start_reg < 32) [[likely]] {
            if (uint8_t* p = mem.fast_ram_ptr(addr, static_cast<size_t>(32 - start_reg) * 4u)) [[likely]] {
                for (int reg = start_reg; reg < 32; ++reg, p += 4) {
                    const uint32_t be = bswap32(r[reg]);
                    std::memcpy(p, &be, sizeof(uint32_t));
                }
                return;
            }
        }
        for (int reg = start_reg; reg < 32; ++reg, addr += 4) {
            mem.write_u32(addr, r[reg]);
        }
    }

    static inline uint32_t rotl32(uint32_t val, uint32_t sh) {
        sh &= 31u;
        return (sh == 0) ? val : ((val << sh) | (val >> (32u - sh)));
    }

    static inline uint32_t ppc_mask(uint32_t mb, uint32_t me) {
        uint32_t m_mb = 0xFFFFFFFFu >> mb;
        uint32_t m_me = (me == 31u) ? 0u : (0xFFFFFFFFu >> (me + 1u));
        return (mb <= me) ? (m_mb ^ m_me) : (m_mb | ~m_me);
    }

    inline void rlwinm(int ra, int rs, uint32_t sh, uint32_t mb, uint32_t me, bool rc) {
        r[ra] = rotl32(r[rs], sh) & ppc_mask(mb, me);
        if (rc) cmp_s32(0, static_cast<int32_t>(r[ra]), 0);
    }

    inline void rlwimi(int ra, int rs, uint32_t sh, uint32_t mb, uint32_t me, bool rc) {
        uint32_t mask = ppc_mask(mb, me);
        r[ra] = (rotl32(r[rs], sh) & mask) | (r[ra] & ~mask);
        if (rc) cmp_s32(0, static_cast<int32_t>(r[ra]), 0);
    }

    inline void rlwnm(int ra, int rs, int rb, uint32_t mb, uint32_t me, bool rc) {
        r[ra] = rotl32(r[rs], r[rb] & 31u) & ppc_mask(mb, me);
        if (rc) cmp_s32(0, static_cast<int32_t>(r[ra]), 0);
    }

    // Algebraic right shift immediate with XER[CA] update (srawi)
    inline uint32_t srawi_op(uint32_t rs_val, uint32_t sh, bool rc = false) noexcept {
        int32_t s = static_cast<int32_t>(rs_val);
        uint32_t res;
        sh &= 31u;
        if (sh == 0) {
            res = rs_val;
            set_ca(false);
        } else {
            uint32_t mask = (1u << sh) - 1u;
            set_ca(s < 0 && (rs_val & mask) != 0);
            res = static_cast<uint32_t>(s >> sh);
        }
        if (rc) cmp_s32(0, static_cast<int32_t>(res), 0);
        return res;
    }

    // Algebraic right shift register with XER[CA] update (sraw)
    inline uint32_t sraw_op(uint32_t rs_val, uint32_t rb_val, bool rc = false) noexcept {
        int32_t s = static_cast<int32_t>(rs_val);
        uint32_t sh = rb_val & 63u;
        uint32_t res;
        if (sh == 0) {
            res = rs_val;
            set_ca(false);
        } else if (sh >= 32) {
            res = (s < 0) ? 0xFFFFFFFFu : 0u;
            set_ca(s < 0);
        } else {
            uint32_t mask = (1u << sh) - 1u;
            set_ca(s < 0 && (rs_val & mask) != 0);
            res = static_cast<uint32_t>(s >> sh);
        }
        if (rc) cmp_s32(0, static_cast<int32_t>(res), 0);
        return res;
    }

    inline void call_indirect(uint32_t target_pc, Memory& mem) {
        mem_ptr = &mem;
        pc = target_pc;
        if (target_pc != 0) {
            dispatch_recompiled_function(target_pc, *this, mem);
        }
    }

    inline void branch_external(uint32_t target_pc) {
        pc = target_pc;
    }

    /**
     * Full Gekko / PowerPC 750CL raw instruction interpreter (Workstream A).
     * Emulates all 41 previously-unlifted (op, xo) pairs across all 791 exec_raw sites.
     */
    void exec_raw(uint32_t insn_pc, uint32_t insn, Memory* explicit_mem = nullptr) noexcept {
        pc = insn_pc;
        ++exec_raw_count;
        if (insn == 0u) return;

        Memory* m = explicit_mem ? explicit_mem : (mem_ptr ? mem_ptr : Memory::active_instance());

        const uint32_t op   = (insn >> 26) & 0x3Fu;
        const uint32_t rd   = (insn >> 21) & 0x1Fu;
        const uint32_t ra   = (insn >> 16) & 0x1Fu;
        const uint32_t rb   = (insn >> 11) & 0x1Fu;
        const uint32_t rc   = (insn >>  6) & 0x1Fu;
        const uint32_t xo10 = (insn >>  1) & 0x3FFu;
        const uint32_t xo5  = (insn >>  1) & 0x1Fu;
        const bool     rc_b = (insn & 1u) != 0;

        auto ea_ab = [&]() noexcept -> uint32_t {
            return (ra ? r[ra] : 0u) + r[rb];
        };

        switch (op) {
            case 21:
                rlwinm(ra, rd, rb, (insn >> 6) & 31, (insn >> 1) & 31, rc_b);
                return;
            case 20:
                rlwimi(ra, rd, rb, (insn >> 6) & 31, (insn >> 1) & 31, rc_b);
                return;
            case 23:
                rlwnm(ra, rd, rb, (insn >> 6) & 31, (insn >> 1) & 31, rc_b);
                return;

            case 4: { // Gekko Paired-Single & Cache Lock
                if (xo10 == 1014u) { // dcbz_l rA, rB (4 sites)
                    if (m) {
                        uint32_t line = ea_ab() & ~31u;
                        if (m->is_valid_range(line, 32)) {
                            std::memset(m->translate(line, 32), 0, 32);
                        }
                    }
                    return;
                }
                if (xo10 == 0u || xo10 == 32u) { // ps_cmpu0 / ps_cmpo0 (2 sites)
                    cmp_f64(static_cast<int>(rd >> 2), static_cast<double>(ps0[ra]), static_cast<double>(ps0[rb]));
                    return;
                }
                if (xo10 == 64u || xo10 == 96u) { // ps_cmpu1 / ps_cmpo1
                    cmp_f64(static_cast<int>(rd >> 2), static_cast<double>(ps1[ra]), static_cast<double>(ps1[rb]));
                    return;
                }
                if (xo10 == 40u) {
                    ps0[rd] = -ps0[rb]; ps1[rd] = -ps1[rb]; f[rd] = ps0[rd];
                    if (rc_b) cmp_f64(1, f[rd], 0.0);
                    return;
                }
                if (xo10 == 72u) {
                    ps0[rd] = ps0[rb]; ps1[rd] = ps1[rb]; f[rd] = ps0[rd];
                    if (rc_b) cmp_f64(1, f[rd], 0.0);
                    return;
                }
                if (xo10 == 136u) {
                    ps0[rd] = -std::fabs(ps0[rb]); ps1[rd] = -std::fabs(ps1[rb]); f[rd] = ps0[rd];
                    if (rc_b) cmp_f64(1, f[rd], 0.0);
                    return;
                }
                if (xo10 == 264u) {
                    ps0[rd] = std::fabs(ps0[rb]); ps1[rd] = std::fabs(ps1[rb]); f[rd] = ps0[rd];
                    if (rc_b) cmp_f64(1, f[rd], 0.0);
                    return;
                }
                switch (xo5) {
                    case 18: { // ps_div
                        ps0[rd] = (ps0[rb] != 0.0f) ? (ps0[ra] / ps0[rb]) : 0.0f;
                        ps1[rd] = (ps1[rb] != 0.0f) ? (ps1[ra] / ps1[rb]) : 0.0f;
                        f[rd]   = ps0[rd];
                        break;
                    }
                    case 20: { // ps_sub
                        ps0[rd] = ps0[ra] - ps0[rb]; ps1[rd] = ps1[ra] - ps1[rb]; f[rd] = ps0[rd];
                        break;
                    }
                    case 21: { // ps_add
                        ps0[rd] = ps0[ra] + ps0[rb]; ps1[rd] = ps1[ra] + ps1[rb]; f[rd] = ps0[rd];
                        break;
                    }
                    case 23: { // ps_sel (1 site)
                        float r0 = (ps0[ra] >= 0.0f) ? ps0[rc] : ps0[rb];
                        float r1 = (ps1[ra] >= 0.0f) ? ps1[rc] : ps1[rb];
                        ps0[rd] = r0; ps1[rd] = r1; f[rd] = ps0[rd];
                        break;
                    }
                    case 24: { // ps_res
                        ps0[rd] = (ps0[rb] != 0.0f) ? (1.0f / ps0[rb]) : 0.0f;
                        ps1[rd] = (ps1[rb] != 0.0f) ? (1.0f / ps1[rb]) : 0.0f;
                        f[rd]   = ps0[rd];
                        break;
                    }
                    case 25: { // ps_mul
                        ps0[rd] = ps0[ra] * ps0[rc]; ps1[rd] = ps1[ra] * ps1[rc]; f[rd] = ps0[rd];
                        break;
                    }
                    case 26: { // ps_rsqrte
                        ps0[rd] = (ps0[rb] > 0.0f) ? (1.0f / std::sqrt(ps0[rb])) : 0.0f;
                        ps1[rd] = (ps1[rb] > 0.0f) ? (1.0f / std::sqrt(ps1[rb])) : 0.0f;
                        f[rd]   = ps0[rd];
                        break;
                    }
                    case 28: { // ps_msub (213 sites)
                        float r0 = ps0[ra] * ps0[rc] - ps0[rb];
                        float r1 = ps1[ra] * ps1[rc] - ps1[rb];
                        ps0[rd] = r0; ps1[rd] = r1; f[rd] = ps0[rd];
                        break;
                    }
                    case 29: { // ps_madd
                        float r0 = ps0[ra] * ps0[rc] + ps0[rb];
                        float r1 = ps1[ra] * ps1[rc] + ps1[rb];
                        ps0[rd] = r0; ps1[rd] = r1; f[rd] = ps0[rd];
                        break;
                    }
                    case 30: { // ps_nmadd (133 sites)
                        float r0 = -(ps0[ra] * ps0[rc] + ps0[rb]);
                        float r1 = -(ps1[ra] * ps1[rc] + ps1[rb]);
                        ps0[rd] = r0; ps1[rd] = r1; f[rd] = ps0[rd];
                        break;
                    }
                    case 31: { // ps_nmsub (5 sites)
                        float r0 = -(ps0[ra] * ps0[rc] - ps0[rb]);
                        float r1 = -(ps1[ra] * ps1[rc] - ps1[rb]);
                        ps0[rd] = r0; ps1[rd] = r1; f[rd] = ps0[rd];
                        break;
                    }
                    default: break;
                }
                if (rc_b) cmp_f64(1, f[rd], 0.0);
                return;
            }

            case 17: // sc (3 sites)
            case 19: // rfi (xo=50, 13 sites)
                return;

            case 31: {
                switch (xo10) {
                    case 202: { // addze rD, rA (81 sites)
                        uint64_t ca  = get_ca() ? 1ull : 0ull;
                        uint64_t sum = static_cast<uint64_t>(r[ra]) + ca;
                        r[rd] = static_cast<uint32_t>(sum);
                        set_ca(sum > 0xFFFFFFFFull);
                        if (rc_b) cmp_s32(0, static_cast<int32_t>(r[rd]), 0);
                        return;
                    }
                    case 200: { // subfze rD, rA (2 sites)
                        uint64_t ca  = get_ca() ? 1ull : 0ull;
                        uint32_t inv = ~r[ra];
                        uint64_t sum = static_cast<uint64_t>(inv) + ca;
                        r[rd] = static_cast<uint32_t>(sum);
                        set_ca(sum > 0xFFFFFFFFull);
                        if (rc_b) cmp_s32(0, static_cast<int32_t>(r[rd]), 0);
                        return;
                    }
                    case 284: { // eqv rA, rS, rB (94 sites)
                        r[ra] = ~(r[rd] ^ r[rb]);
                        if (rc_b) cmp_s32(0, static_cast<int32_t>(r[ra]), 0);
                        return;
                    }
                    case 476: { // nand rA, rS, rB (5 sites)
                        r[ra] = ~(r[rd] & r[rb]);
                        if (rc_b) cmp_s32(0, static_cast<int32_t>(r[ra]), 0);
                        return;
                    }
                    case 412: { // orc rA, rS, rB (1 site)
                        r[ra] = r[rd] | ~r[rb];
                        if (rc_b) cmp_s32(0, static_cast<int32_t>(r[ra]), 0);
                        return;
                    }
                    case 83: { // mfmsr rD (28 sites)
                        r[rd] = msr;
                        return;
                    }
                    case 146: { // mtmsr rS (21 sites)
                        msr = r[rd];
                        return;
                    }
                    case 371: { // mftb rD, TBR (6 sites)
                        tb_ticks += 4050ull;
                        uint32_t tbr = (rb << 5) | ra;
                        if (tbr == 269u) {
                            r[rd] = static_cast<uint32_t>(tb_ticks >> 32);
                        } else {
                            r[rd] = static_cast<uint32_t>(tb_ticks & 0xFFFFFFFFull);
                        }
                        return;
                    }
                    case 512: { // mcrxr crfD (2 sites)
                        cr[(rd >> 2) & 7u] = static_cast<uint8_t>((xer >> 28) & 0xFu);
                        xer &= ~0xF0000000u;
                        return;
                    }
                    case 983: { // stfiwx fS, rA, rB (26 sites)
                        if (m) {
                            uint64_t u = 0;
                            std::memcpy(&u, &f[rd], 8);
                            m->write_u32(ea_ab(), static_cast<uint32_t>(u & 0xFFFFFFFFull));
                        }
                        return;
                    }
                    case 343: { // lhax rD, rA, rB (21 sites)
                        if (m) {
                            r[rd] = static_cast<uint32_t>(static_cast<int32_t>(m->read_s16(ea_ab())));
                        }
                        return;
                    }
                    case 55: { // lwzux rD, rA, rB (12 sites)
                        if (m) {
                            uint32_t ea = r[ra] + r[rb];
                            r[rd] = m->read_u32(ea);
                            r[ra] = ea;
                        }
                        return;
                    }
                    case 183: { // stwux rS, rA, rB (8 sites)
                        if (m) {
                            uint32_t ea = r[ra] + r[rb];
                            m->write_u32(ea, r[rd]);
                            r[ra] = ea;
                        }
                        return;
                    }
                    case 311: { // lhzux rD, rA, rB (1 site)
                        if (m) {
                            uint32_t ea = r[ra] + r[rb];
                            r[rd] = m->read_u16(ea);
                            r[ra] = ea;
                        }
                        return;
                    }
                    case 534: { // lwbrx rD, rA, rB (2 sites)
                        if (m) {
                            r[rd] = bswap32(m->read_u32(ea_ab()));
                        }
                        return;
                    }
                    case 790: { // lhbrx rD, rA, rB (2 sites)
                        if (m) {
                            r[rd] = bswap16(m->read_u16(ea_ab()));
                        }
                        return;
                    }
                    case 662: { // stwbrx rS, rA, rB (1 site)
                        if (m) {
                            m->write_u32(ea_ab(), bswap32(r[rd]));
                        }
                        return;
                    }
                    case 918: { // sthbrx rS, rA, rB (1 site)
                        if (m) {
                            m->write_u16(ea_ab(), bswap16(static_cast<uint16_t>(r[rd])));
                        }
                        return;
                    }
                    case 1014: { // dcbz rA, rB (14 sites)
                        if (m) {
                            uint32_t line = ea_ab() & ~31u;
                            if (m->is_valid_range(line, 32)) {
                                std::memset(m->translate(line, 32), 0, 32);
                            }
                        }
                        return;
                    }
                    case 598: // sync (26 sites)
                    case 854: // eieio (1 site)
                    case 54:  // dcbst (5 sites)
                    case 86:  // dcbf (3 sites)
                    case 278: // dcbt (3 sites)
                    case 246: // dcbtst
                    case 470: // dcbi (5 sites)
                    case 982: // icbi (3 sites)
                        return;
                    default:
                        break;
                }
                return;
            }

            case 59: {
                if (xo5 == 24u) { // fres fD, fB (4 sites)
                    float v = (f[rb] != 0.0) ? static_cast<float>(1.0 / f[rb]) : 0.0f;
                    f[rd] = static_cast<double>(v);
                    ps0[rd] = ps1[rd] = v;
                    if (rc_b) cmp_f64(1, f[rd], 0.0);
                }
                return;
            }

            case 63: {
                switch (xo10) {
                    case 583: { // mffs fD (3 sites)
                        uint64_t u = static_cast<uint64_t>(fpscr);
                        std::memcpy(&f[rd], &u, 8);
                        if (rc_b) cmp_f64(1, f[rd], 0.0);
                        return;
                    }
                    case 711: { // mtfsf FM, fB (5 sites)
                        uint64_t u = 0;
                        std::memcpy(&u, &f[rb], 8);
                        fpscr = static_cast<uint32_t>(u & 0xFFFFFFFFull);
                        return;
                    }
                    case 70: { // mtfsb0 crbD (1 site)
                        fpscr &= ~(1u << (31u - rd));
                        return;
                    }
                    case 38: { // mtfsb1 crbD (1 site)
                        fpscr |= (1u << (31u - rd));
                        return;
                    }
                    default:
                        break;
                }
                switch (xo5) {
                    case 23: { // fsel fD, fA, fC, fB
                        f[rd] = (f[ra] >= 0.0) ? f[rc] : f[rb];
                        ps0[rd] = static_cast<float>(f[rd]);
                        if (rc_b) cmp_f64(1, f[rd], 0.0);
                        return;
                    }
                    case 26: { // frsqrte fD, fB (20 sites)
                        double v = (f[rb] > 0.0) ? (1.0 / std::sqrt(f[rb])) : 0.0;
                        f[rd] = v;
                        ps0[rd] = ps1[rd] = static_cast<float>(v);
                        if (rc_b) cmp_f64(1, f[rd], 0.0);
                        return;
                    }
                    case 30: { // fnmadd fD, fA, fC, fB (1 site)
                        f[rd] = -(f[ra] * f[rc] + f[rb]);
                        ps0[rd] = static_cast<float>(f[rd]);
                        if (rc_b) cmp_f64(1, f[rd], 0.0);
                        return;
                    }
                    case 31: { // fnmsub fD, fA, fC, fB
                        f[rd] = -(f[ra] * f[rc] - f[rb]);
                        ps0[rd] = static_cast<float>(f[rd]);
                        if (rc_b) cmp_f64(1, f[rd], 0.0);
                        return;
                    }
                    default:
                        break;
                }
                return;
            }

            default:
                return;
        }
    }
};

} // namespace pn03

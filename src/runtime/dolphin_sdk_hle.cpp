#include "pn03_all_forwards.hpp"
#include "pn03_audio_ax.hpp"
#include "pn03_gx_3d_interface.hpp"
#include "pn03_ppc_context.hpp"
#include "pn03_runtime.hpp"
#include "pn03_logger.hpp"
#include "pn03_symbols.hpp"
#include <algorithm>
#include <cmath>
#include <condition_variable>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

namespace pn03 {

namespace recomp {
    RecompFuncPtr lookup_recompiled_function(uint32_t vaddr);
}

// ============================================================================
// 1. Multi-Heap OSAlloc Manager & Arena State (0x80350000..0x817FFFFF)
// ============================================================================
struct GcHeapState {
    uint32_t start  = 0;
    uint32_t end    = 0;
    uint32_t cursor = 0;
    bool     active = false;
};

static uint32_t g_arena_lo    = 0x80350000u;
static uint32_t g_arena_hi    = 0x817F0000u;
static uint32_t g_heap_base   = 0x80350000u;
static uint32_t g_max_heaps   = 0u;
static int32_t  g_curr_heap   = 0;
static uint32_t g_heap_cursor = 0x80350000u;
static GcHeapState g_heaps[8]{};

// Pending async callbacks (DVDReadAsyncPrio / ARQPostRequest)
struct PendingHleCallback {
    uint32_t callback_vaddr = 0;
    uint32_t arg0           = 0;
    uint32_t arg1           = 0;
    uint32_t dvd_file_info  = 0;
};
static std::vector<PendingHleCallback> g_pending_callbacks;
static std::mutex                      g_pending_callbacks_mtx;

// ============================================================================
// 2. Cooperative OSThread Scheduler (for Scheduler_800A18E4 & TaskSleep_800A1B5C)
// ============================================================================
struct GcThreadExitSignal {};

struct GcCoopThread {
    uint32_t                thread_vaddr = 0;
    uint32_t                entry_vaddr  = 0;
    uint32_t                param        = 0;
    uint32_t                stack_top    = 0;
    uint32_t                stack_size   = 0;
    uint32_t                sleep_queue  = 0;
    PPCContext              ctx{};
    Memory*                 mem_ptr      = nullptr;
    std::mutex              mtx;
    std::condition_variable cv_task;
    std::condition_variable cv_main;
    std::thread             worker;
    bool                    started      = false;
    bool                    turn_is_task = false;
    bool                    sleeping     = false;
    bool                    terminated   = false;
    bool                    cancel_req   = false;
};

static std::unordered_map<uint32_t, std::shared_ptr<GcCoopThread>> g_coop_threads;
static thread_local GcCoopThread* tls_current_coop_thread = nullptr;
static uint32_t g_active_thread_vaddr = 0x801A28E8u;

static void stop_and_join_all_coop_threads() {
    for (auto& kv : g_coop_threads) {
        auto& t = kv.second;
        if (!t) continue;
        {
            std::lock_guard<std::mutex> lk(t->mtx);
            t->cancel_req   = true;
            t->turn_is_task = true;
        }
        t->cv_task.notify_all();
        if (t->worker.joinable()) {
            t->worker.join();
        }
    }
    g_coop_threads.clear();
}

static void run_coop_thread_step(const std::shared_ptr<GcCoopThread>& t, Memory& mem) {
    if (!t || t->terminated) return;
    t->mem_ptr = &mem;
    if (!t->started) {
        t->started = true;
        t->turn_is_task = true;
        t->worker = std::thread([t]() {
            tls_current_coop_thread = t.get();
            {
                std::unique_lock<std::mutex> lk(t->mtx);
                t->cv_task.wait(lk, [&]() { return t->turn_is_task || t->cancel_req; });
            }
            if (!t->cancel_req && t->mem_ptr) {
                try {
                    dispatch_recompiled_function(t->entry_vaddr, t->ctx, *t->mem_ptr);
                } catch (const GcThreadExitSignal&) {
                } catch (...) {
                }
            }
            {
                std::lock_guard<std::mutex> lk(t->mtx);
                t->terminated   = true;
                t->turn_is_task = false;
            }
            t->cv_main.notify_all();
            tls_current_coop_thread = nullptr;
        });
    } else {
        std::lock_guard<std::mutex> lk(t->mtx);
        t->sleeping     = false;
        t->turn_is_task = true;
        t->cv_task.notify_all();
    }

    std::unique_lock<std::mutex> lk(t->mtx);
    t->cv_main.wait(lk, [&]() { return !t->turn_is_task || t->terminated; });
}

static bool g_hle_call_trace = false;
static uint64_t g_hle_call_seq = 0;
static thread_local int g_hle_call_depth = 0;

void set_hle_call_trace(bool enabled) {
    g_hle_call_trace = enabled;
    if (enabled) {
        g_hle_call_seq = 0;
    }
}

static void reset_card_state_for_runtime_reset();

void reset_hle_runtime_state(Memory& mem) {
    stop_and_join_all_coop_threads();
    reset_card_state_for_runtime_reset();
    {
        std::lock_guard<std::mutex> lk(g_pending_callbacks_mtx);
        g_pending_callbacks.clear();
    }
    g_arena_lo    = 0x80350000u;
    g_arena_hi    = 0x817F0000u;
    g_heap_base   = 0x80350000u;
    g_max_heaps   = 0u;
    g_curr_heap   = 0;
    g_heap_cursor = 0x80350000u;
    for (auto& h : g_heaps) h = GcHeapState{};

    mem.write_u32(0x80000028u, 0x01800000u); // 24 MB physical RAM
    mem.write_u32(0x80000030u, g_arena_lo);
    mem.write_u32(0x80000034u, g_arena_hi);
    mem.write_u32(0x800000F8u, 162000000u);  // Bus clock 162 MHz
    mem.write_u32(0x800000FCu, 486000000u);  // Core clock 486 MHz
    mem.write_u32(0x8026E290u, 0xFFFFFFFFu); // __OSCurrHeap
    mem.write_u32(0x8026E970u, 0u);          // HeapArray
    mem.write_u32(0x8026E974u, 0u);          // NumHeaps
    mem.write_u32(0x8026E978u, g_arena_lo);  // ArenaStart
    mem.write_u32(0x8026E97Cu, g_arena_hi);  // ArenaEnd
}

void enqueue_pending_hle_callback(uint32_t callback_vaddr, uint32_t arg0, uint32_t arg1, uint32_t dvd_file_info) {
    if (callback_vaddr < kGcRamBase || callback_vaddr >= kGcRamBase + kGcRamSize) return;
    std::lock_guard<std::mutex> lk(g_pending_callbacks_mtx);
    g_pending_callbacks.push_back(PendingHleCallback{
        callback_vaddr,
        arg0,
        arg1,
        dvd_file_info
    });
}

void flush_pending_hle_callbacks(PPCContext& ctx, Memory& mem) {
    for (;;) {
        std::vector<PendingHleCallback> batch;
        {
            std::lock_guard<std::mutex> lk(g_pending_callbacks_mtx);
            if (g_pending_callbacks.empty()) break;
            batch = std::move(g_pending_callbacks);
            g_pending_callbacks.clear();
        }
        for (const auto& cb : batch) {
            if (cb.dvd_file_info != 0u && mem.is_valid_range(cb.dvd_file_info, 60u)) {
                mem.write_u32(cb.dvd_file_info + 12u, 0u); // DVD_STATE_END
            }
            if (cb.callback_vaddr >= kGcRamBase && cb.callback_vaddr < kGcRamBase + kGcRamSize) {
                uint32_t saved_r0  = ctx.r[0];
                uint32_t saved_gpr[10]{}; // r3..r12
                std::memcpy(saved_gpr, &ctx.r[3], sizeof(saved_gpr));
                uint32_t saved_lr  = ctx.lr;
                uint32_t saved_ctr = ctx.ctr;
                uint32_t saved_xer = ctx.xer;
                uint32_t saved_cr  = ctx.pack_cr();

                ctx.r[3] = cb.arg0;
                ctx.r[4] = cb.arg1;
                dispatch_recompiled_function(cb.callback_vaddr, ctx, mem);

                ctx.r[0] = saved_r0;
                std::memcpy(&ctx.r[3], saved_gpr, sizeof(saved_gpr));
                ctx.lr   = saved_lr;
                ctx.ctr  = saved_ctr;
                ctx.xer  = saved_xer;
                ctx.unpack_cr(0xFFu, saved_cr);
            }
        }
    }
}

uint32_t execute_static_constructors(PPCContext& ctx, Memory& mem) {
    uint32_t count = 0;
    for (uint32_t ptr_va = 0x80162204u; ptr_va < 0x801622C4u; ptr_va += 4u) {
        uint32_t fn_va = mem.read_u32(ptr_va);
        if (fn_va == 0u) break;
        if (fn_va >= 0x80003100u && fn_va < 0x80162200u) {
            dispatch_recompiled_function(fn_va, ctx, mem);
            count++;
        }
    }
    return count;
}

// ============================================================================
// 3. OS Arena & Multi-Heap HLE
// ============================================================================
static void hle_OSGetArenaLo(PPCContext& ctx, Memory& mem) {
    (void)mem;
    ctx.r[3] = g_arena_lo;
}

static void hle_OSGetArenaHi(PPCContext& ctx, Memory& mem) {
    (void)mem;
    ctx.r[3] = g_arena_hi;
}

static void hle_OSSetArenaLo(PPCContext& ctx, Memory& mem) {
    (void)mem;
    g_arena_lo = ctx.r[3];
}

static void hle_OSSetArenaHi(PPCContext& ctx, Memory& mem) {
    (void)mem;
    g_arena_hi = ctx.r[3];
}

static void hle_OSInitAlloc(PPCContext& ctx, Memory& mem) {
    uint32_t arena_start = ctx.r[3];
    uint32_t arena_end   = ctx.r[4];
    uint32_t max_heaps   = ctx.r[5];

    if (arena_start < 0x80300000u || arena_start >= 0x81700000u) {
        arena_start = 0x80350000u;
    }
    g_heap_base = arena_start;
    g_max_heaps = (max_heaps > 0u && max_heaps <= 8u) ? max_heaps : 0u;

    if (g_max_heaps > 0u) {
        uint32_t array_bytes  = g_max_heaps * 12u;
        uint32_t usable_start = (arena_start + array_bytes + 31u) & ~31u;
        for (uint32_t i = 0; i < g_max_heaps; ++i) {
            uint32_t hd = g_heap_base + i * 12u;
            mem.write_u32(hd + 0u, 0xFFFFFFFFu); // size (-1 = free descriptor)
            mem.write_u32(hd + 4u, 0u);          // freeList
            mem.write_u32(hd + 8u, 0u);          // allocatedList
            g_heaps[i] = GcHeapState{0u, 0u, 0u, false};
        }
        g_heap_cursor = usable_start;
        g_arena_lo    = usable_start;
        if (arena_end > usable_start && arena_end <= kGcRamBase + kGcRamSize) {
            g_arena_hi = arena_end & ~31u;
        }
        g_curr_heap = -1;
        mem.write_u32(0x8026E970u, g_heap_base);
        mem.write_u32(0x8026E974u, g_max_heaps);
        mem.write_u32(0x8026E978u, usable_start);
        mem.write_u32(0x8026E97Cu, g_arena_hi);
        mem.write_u32(0x8026E290u, 0xFFFFFFFFu);
        ctx.r[3] = usable_start;
    } else {
        g_heap_cursor = (arena_start + 31u) & ~31u;
        ctx.r[3] = g_heap_cursor;
    }
}

static void hle_OSCreateHeap(PPCContext& ctx, Memory& mem) {
    uint32_t start = (ctx.r[3] + 31u) & ~31u;
    uint32_t end   = ctx.r[4] & ~31u;
    if (start < 0x80300000u || start >= kGcRamBase + kGcRamSize) {
        start = g_heap_cursor;
    }
    if (end <= start || end > kGcRamBase + kGcRamSize) {
        end = 0x817E0000u;
    }

    int32_t chosen = -1;
    if (g_max_heaps > 0u) {
        for (uint32_t i = 0; i < g_max_heaps; ++i) {
            uint32_t hd = g_heap_base + i * 12u;
            int32_t sz = static_cast<int32_t>(mem.read_u32(hd + 0u));
            if (sz < 0 || !g_heaps[i].active) {
                chosen = static_cast<int32_t>(i);
                break;
            }
        }
        if (chosen < 0) {
            ctx.r[3] = 0xFFFFFFFFu;
            return;
        }
        uint32_t hd        = g_heap_base + static_cast<uint32_t>(chosen) * 12u;
        uint32_t heap_sz   = (end > start) ? (end - start) : 0u;
        uint32_t free_cell = start;
        mem.write_u32(free_cell + 0u, 0u);
        mem.write_u32(free_cell + 4u, 0u);
        mem.write_u32(free_cell + 8u, heap_sz);
        mem.write_u32(hd + 0u, heap_sz);
        mem.write_u32(hd + 4u, free_cell);
        mem.write_u32(hd + 8u, 0u);
        g_heaps[chosen] = GcHeapState{start, end, start + 32u, true};
        if (start > g_heap_cursor) g_heap_cursor = start;
    } else {
        chosen = 0;
        g_heap_cursor = start;
    }
    ctx.r[3] = static_cast<uint32_t>(chosen);
}

static void hle_OSDestroyHeap(PPCContext& ctx, Memory& mem) {
    uint32_t h = ctx.r[3];
    if (h < 8u) {
        g_heaps[h].active = false;
        if (g_max_heaps > 0u && h < g_max_heaps) {
            uint32_t hd = g_heap_base + h * 12u;
            mem.write_u32(hd + 0u, 0xFFFFFFFFu);
            mem.write_u32(hd + 4u, 0u);
            mem.write_u32(hd + 8u, 0u);
        }
    }
}

static void hle_OSSetCurrentHeap(PPCContext& ctx, Memory& mem) {
    int32_t prev = g_curr_heap;
    g_curr_heap = static_cast<int32_t>(ctx.r[3]);
    mem.write_u32(0x8026E290u, ctx.r[3]); // __OSCurrHeap
    ctx.r[3] = static_cast<uint32_t>(prev);
}

static void hle_OSAllocFromHeap(PPCContext& ctx, Memory& mem) {
    uint32_t h       = ctx.r[3];
    uint32_t user_sz = (ctx.r[4] + 31u) & ~31u;
    if (user_sz == 0u) user_sz = 32u;
    uint32_t req = user_sz + 32u; // 32-byte Cell header + aligned payload

    if (g_max_heaps > 0u) {
        if (h >= g_max_heaps || !g_heaps[h].active) {
            if (g_hle_call_trace) {
                std::printf("[HLE-OOM] OSAllocFromHeap invalid heap h=%u sz=0x%08X\n", h, req);
            }
            ctx.r[3] = 0u;
            return;
        }
        auto& hs    = g_heaps[h];
        uint32_t hd = g_heap_base + h * 12u;

        uint32_t cell  = mem.read_u32(hd + 4u);
        uint32_t steps = 0u;
        uint32_t total_free   = 0u;
        uint32_t largest_free = 0u;
        while (cell != 0u && cell >= hs.start && cell + 32u <= hs.end && steps < 65536u) {
            uint32_t cell_sz = mem.read_u32(cell + 8u);
            if (cell_sz < 32u || cell + cell_sz > hs.end) break;
            total_free += cell_sz;
            if (cell_sz > largest_free) largest_free = cell_sz;
            if (req <= cell_sz) {
                uint32_t cell_prev = mem.read_u32(cell + 0u);
                uint32_t cell_next = mem.read_u32(cell + 4u);
                uint32_t rem       = cell_sz - req;
                if (rem < 64u) {
                    if (cell_next != 0u) mem.write_u32(cell_next + 0u, cell_prev);
                    if (cell_prev != 0u) mem.write_u32(cell_prev + 4u, cell_next);
                    else                 mem.write_u32(hd + 4u, cell_next);
                } else {
                    mem.write_u32(cell + 8u, req);
                    uint32_t new_free = cell + req;
                    mem.write_u32(new_free + 0u, cell_prev);
                    mem.write_u32(new_free + 4u, cell_next);
                    mem.write_u32(new_free + 8u, rem);
                    if (cell_next != 0u) mem.write_u32(cell_next + 0u, new_free);
                    if (cell_prev != 0u) mem.write_u32(cell_prev + 4u, new_free);
                    else                 mem.write_u32(hd + 4u, new_free);
                }
                uint32_t alloc_head = mem.read_u32(hd + 8u);
                mem.write_u32(cell + 0u, 0u);
                mem.write_u32(cell + 4u, alloc_head);
                if (alloc_head != 0u) mem.write_u32(alloc_head + 0u, cell);
                mem.write_u32(hd + 8u, cell);
                if (cell + req > hs.cursor) hs.cursor = cell + req;
                ctx.r[3] = cell + 32u;
                return;
            }
            cell = mem.read_u32(cell + 4u);
            ++steps;
        }
        if (g_hle_call_trace) {
            std::printf("[HLE-OOM] OSAllocFromHeap(h=%u req=0x%08X [0x%08X..0x%08X]) failed: free=0x%08X largest=0x%08X\n",
                        h, req, hs.start, hs.end, total_free, largest_free);
        }
        ctx.r[3] = 0u;
        return;
    }

    if (g_heap_cursor + req >= g_arena_hi) {
        ctx.r[3] = 0u;
        return;
    }
    uint32_t ptr = g_heap_cursor + 32u;
    g_heap_cursor += req;
    ctx.r[3] = ptr;
}

static void hle_OSFreeToHeap(PPCContext& ctx, Memory& mem) {
    uint32_t h   = ctx.r[3];
    uint32_t ptr = ctx.r[4];
    if (ptr == 0u || g_max_heaps == 0u || h >= g_max_heaps || !g_heaps[h].active) return;

    const auto& hs = g_heaps[h];
    if (ptr < hs.start + 32u || ptr >= hs.end || (ptr & 31u) != 0u) return;

    uint32_t cell    = ptr - 32u;
    uint32_t hd      = g_heap_base + h * 12u;
    uint32_t cell_sz = mem.read_u32(cell + 8u);
    if (cell_sz < 64u || cell + cell_sz > hs.end || (cell_sz & 31u) != 0u) return;

    uint32_t prev = mem.read_u32(cell + 0u);
    uint32_t next = mem.read_u32(cell + 4u);
    bool linked_head = (prev == 0u && mem.read_u32(hd + 8u) == cell);
    bool linked_mid  = (prev >= hs.start && prev + 32u <= hs.end && mem.read_u32(prev + 4u) == cell);
    if (!linked_head && !linked_mid) return;

    if (next != 0u) mem.write_u32(next + 0u, prev);
    if (prev != 0u) mem.write_u32(prev + 4u, next);
    else            mem.write_u32(hd + 8u, next);

    uint32_t f_prev = 0u;
    uint32_t f_curr = mem.read_u32(hd + 4u);
    uint32_t steps  = 0u;
    while (f_curr != 0u && f_curr < cell && f_curr >= hs.start && f_curr < hs.end && steps < 65536u) {
        f_prev = f_curr;
        f_curr = mem.read_u32(f_curr + 4u);
        ++steps;
    }

    mem.write_u32(cell + 0u, f_prev);
    mem.write_u32(cell + 4u, f_curr);
    if (f_curr != 0u) {
        mem.write_u32(f_curr + 0u, cell);
        if (cell + cell_sz == f_curr) {
            cell_sz += mem.read_u32(f_curr + 8u);
            mem.write_u32(cell + 8u, cell_sz);
            f_curr = mem.read_u32(f_curr + 4u);
            mem.write_u32(cell + 4u, f_curr);
            if (f_curr != 0u) mem.write_u32(f_curr + 0u, cell);
        }
    }
    if (f_prev != 0u) {
        mem.write_u32(f_prev + 4u, cell);
        uint32_t prev_sz = mem.read_u32(f_prev + 8u);
        if (f_prev + prev_sz == cell) {
            mem.write_u32(f_prev + 8u, prev_sz + cell_sz);
            mem.write_u32(f_prev + 4u, f_curr);
            if (f_curr != 0u) mem.write_u32(f_curr + 0u, f_prev);
        }
    } else {
        mem.write_u32(hd + 4u, cell);
    }
}

static void hle_OSCheckHeap(PPCContext& ctx, Memory& mem) {
    uint32_t h = ctx.r[3];
    if (g_max_heaps > 0u && h < g_max_heaps && g_heaps[h].active) {
        const auto& hs = g_heaps[h];
        uint32_t hd    = g_heap_base + h * 12u;
        uint32_t cell  = mem.read_u32(hd + 4u);
        uint32_t free_bytes = 0u;
        uint32_t steps = 0u;
        while (cell != 0u && cell >= hs.start && cell + 32u <= hs.end && steps < 65536u) {
            uint32_t sz = mem.read_u32(cell + 8u);
            if (sz < 32u || cell + sz > hs.end) break;
            free_bytes += (sz - 32u);
            cell = mem.read_u32(cell + 4u);
            ++steps;
        }
        ctx.r[3] = free_bytes;
    } else {
        ctx.r[3] = 0x00800000u;
    }
}

// ============================================================================
// 4. Cooperative OSThread / Semaphore / Time HLE
// ============================================================================
static void hle_OSInitSemaphore(PPCContext& ctx, Memory& mem) {
    if (mem.is_valid_range(ctx.r[3], 12u)) {
        mem.write_u32(ctx.r[3] + 0u, ctx.r[4]);
    }
}

static void hle_OSWaitSemaphore(PPCContext& ctx, Memory& mem) {
    if (mem.is_valid_range(ctx.r[3], 4u)) {
        int32_t c = mem.read_s32(ctx.r[3]);
        if (c > 0) mem.write_u32(ctx.r[3], static_cast<uint32_t>(c - 1));
        ctx.r[3] = static_cast<uint32_t>((std::max)(c, 1));
    } else {
        ctx.r[3] = 1u;
    }
}

static void hle_OSTryWaitSemaphore(PPCContext& ctx, Memory& mem) {
    hle_OSWaitSemaphore(ctx, mem);
}

static void hle_OSSignalSemaphore(PPCContext& ctx, Memory& mem) {
    if (mem.is_valid_range(ctx.r[3], 4u)) {
        int32_t c = mem.read_s32(ctx.r[3]);
        mem.write_u32(ctx.r[3], static_cast<uint32_t>(c + 1));
        ctx.r[3] = static_cast<uint32_t>(c);
    } else {
        ctx.r[3] = 0u;
    }
}

static void hle_OSGetSemaphoreCount(PPCContext& ctx, Memory& mem) {
    ctx.r[3] = mem.is_valid_range(ctx.r[3], 4u) ? mem.read_u32(ctx.r[3]) : 1u;
}

static void hle_OSCreateThread(PPCContext& ctx, Memory& mem) {
    uint32_t thread_va  = ctx.r[3];
    uint32_t func_va    = ctx.r[4];
    uint32_t param      = ctx.r[5];
    uint32_t stack_top  = ctx.r[6];
    uint32_t stack_size = ctx.r[7];
    uint32_t prio       = ctx.r[8];

    // Write stack overflow canary 0xDEADBABE at stack_top - stack_size (checked by StackOverflowCheck_800A19E8)
    if (stack_top > stack_size && mem.is_valid_range(stack_top - stack_size, 16u)) {
        mem.write_u32(stack_top - stack_size, 0xDEADBABEu);
        mem.write_u32(stack_top - stack_size + 4u, 0xDEADBABEu);
    }
    if (mem.is_valid_range(thread_va, 792u)) {
        mem.write_u16(thread_va + 0x2BCu, 1u); // OS_THREAD_STATE_READY
        mem.write_u32(thread_va + 0x2C0u, prio);
        mem.write_u32(thread_va + 0x304u, stack_top);
        mem.write_u32(thread_va + 0x308u, stack_top - stack_size);
    }

    auto it = g_coop_threads.find(thread_va);
    if (it != g_coop_threads.end() && it->second) {
        auto old = it->second;
        {
            std::lock_guard<std::mutex> lk(old->mtx);
            old->cancel_req   = true;
            old->turn_is_task = true;
        }
        old->cv_task.notify_all();
        if (old->worker.joinable()) old->worker.join();
        g_coop_threads.erase(it);
    }

    auto t = std::make_shared<GcCoopThread>();
    t->thread_vaddr = thread_va;
    t->entry_vaddr  = func_va;
    t->param        = param;
    t->stack_top    = stack_top;
    t->stack_size   = stack_size;
    t->sleep_queue  = thread_va + (808u - 16u);
    t->ctx.reset();
    if (stack_top >= kGcRamBase + 64u && stack_top <= kGcRamBase + kGcRamSize) {
        t->ctx.r[1] = (stack_top - 32u) & ~7u;
    }
    t->ctx.r[3] = param;
    g_coop_threads[thread_va] = t;
    ctx.r[3] = 1u;
}

static void hle_OSResumeThread(PPCContext& ctx, Memory& mem) {
    uint32_t thread_va = ctx.r[3];
    auto it = g_coop_threads.find(thread_va);
    if (it != g_coop_threads.end() && it->second && !it->second->terminated) {
        uint32_t prev_active = g_active_thread_vaddr;
        g_active_thread_vaddr = thread_va;
        run_coop_thread_step(it->second, mem);
        g_active_thread_vaddr = prev_active;
        flush_pending_hle_callbacks(ctx, mem);
    }
    ctx.r[3] = 1u;
}

static void hle_OSSleepThread(PPCContext& ctx, Memory& mem) {
    uint32_t queue_va = ctx.r[3];
    if (tls_current_coop_thread != nullptr) {
        GcCoopThread* t = tls_current_coop_thread;
        std::unique_lock<std::mutex> lk(t->mtx);
        t->sleep_queue  = queue_va;
        t->sleeping     = true;
        t->turn_is_task = false;
        t->cv_main.notify_all();
        t->cv_task.wait(lk, [&]() { return t->turn_is_task || t->cancel_req; });
        if (t->cancel_req) {
            throw GcThreadExitSignal{};
        }
    } else {
        flush_pending_hle_callbacks(ctx, mem);
    }
}

static void hle_OSWakeupThread(PPCContext& ctx, Memory& mem) {
    uint32_t queue_va = ctx.r[3];
    for (auto& kv : g_coop_threads) {
        auto& t = kv.second;
        if (t && !t->terminated && t->sleeping && t->sleep_queue == queue_va) {
            uint32_t prev_active = g_active_thread_vaddr;
            g_active_thread_vaddr = t->thread_vaddr;
            run_coop_thread_step(t, mem);
            g_active_thread_vaddr = prev_active;
            flush_pending_hle_callbacks(ctx, mem);
            break;
        }
    }
}

static void hle_OSExitThread(PPCContext& ctx, Memory& mem) {
    (void)ctx;
    (void)mem;
    if (tls_current_coop_thread != nullptr) {
        throw GcThreadExitSignal{};
    }
}

static void hle_OSCancelThread(PPCContext& ctx, Memory& mem) {
    (void)mem;
    uint32_t thread_va = ctx.r[3];
    auto it = g_coop_threads.find(thread_va);
    if (it != g_coop_threads.end() && it->second) {
        auto t = it->second;
        if (tls_current_coop_thread == t.get()) {
            throw GcThreadExitSignal{};
        }
        {
            std::lock_guard<std::mutex> lk(t->mtx);
            t->cancel_req   = true;
            t->turn_is_task = true;
        }
        t->cv_task.notify_all();
        if (t->worker.joinable()) t->worker.join();
        g_coop_threads.erase(it);
    }
}

static void hle_OSClearStack(PPCContext& ctx, Memory& mem) {
    uint32_t val = ctx.r[3];
    for (int i = 0; i < 4; ++i) {
        uint32_t task_va  = 0x801AC6D8u + static_cast<uint32_t>(i * 824);
        uint32_t stack_top = mem.read_u32(task_va);
        uint16_t stack_sz  = mem.read_u16(0x801760B4u + static_cast<uint32_t>(i * 2));
        if (stack_top > stack_sz && mem.is_valid_range(stack_top - stack_sz, 16u)) {
            mem.write_u32(stack_top - stack_sz, val);
        }
    }
}

// ============================================================================
// 5. Dolphin DVD* / AR* / ARQ* HLE Backed by IsoStreamReader
// ============================================================================
static void hle_DVDConvertPathToEntrynum(PPCContext& ctx, Memory& mem) {
    std::string path = mem.read_cstring(ctx.r[3], 512);
    if (const auto* loc = LocalizationOverlay::active_instance()) {
        path = loc->resolve_localized_asset_path(path);
    }
    int32_t entrynum = -1;
    if (const auto* iso = IsoStreamReader::active_instance()) {
        entrynum = iso->find_entrynum(path);
    }
    if (entrynum < 0) {
        std::string lower_path = path;
        for (char& ch : lower_path) {
            if (ch >= 'A' && ch <= 'Z') {
                ch = static_cast<char>(ch + ('a' - 'A'));
            } else if (ch == '\\') {
                ch = '/';
            }
        }
        const bool is_optional_probe =
            (lower_path == "etc/moji8.tpl" || lower_path == "/etc/moji8.tpl");
        PN03_LOGF(is_optional_probe ? LogLevel::Debug : LogLevel::Warn,
                  "DVD", "DVDConvertPathToEntrynum failed path='%s'", path.c_str());
    } else {
        PN03_LOGF(LogLevel::Debug, "DVD", "DVDConvertPathToEntrynum('%s') -> %d", path.c_str(), entrynum);
    }
    ctx.r[3] = static_cast<uint32_t>(entrynum);
}

static void hle_DVDFastOpen(PPCContext& ctx, Memory& mem) {
    int32_t entrynum   = static_cast<int32_t>(ctx.r[3]);
    uint32_t file_info = ctx.r[4];
    const auto* iso    = IsoStreamReader::active_instance();
    const IsoFileEntry* fe = iso ? iso->get_file_by_entrynum(entrynum) : nullptr;
    if (!fe || !mem.is_valid_range(file_info, 60u)) {
        ctx.r[3] = 0u;
        return;
    }
    mem.write_u32(file_info + 12u, 0u); // status = DVD_STATE_END
    mem.write_u32(file_info + 48u, fe->disc_offset);
    mem.write_u32(file_info + 52u, fe->size_bytes);
    mem.write_u32(file_info + 56u, static_cast<uint32_t>(entrynum));
    ctx.r[3] = 1u;
}

static void hle_DVDOpen(PPCContext& ctx, Memory& mem) {
    std::string path   = mem.read_cstring(ctx.r[3], 512);
    uint32_t file_info = ctx.r[4];
    if (const auto* loc = LocalizationOverlay::active_instance()) {
        path = loc->resolve_localized_asset_path(path);
    }
    const auto* iso = IsoStreamReader::active_instance();
    int32_t entrynum = iso ? iso->find_entrynum(path) : -1;
    if (entrynum < 0) {
        PN03_LOGF(LogLevel::Warn, "DVD", "DVDOpen failed path='%s'", path.c_str());
    } else {
        PN03_LOGF(LogLevel::Debug, "DVD", "DVDOpen('%s') -> entry=%d", path.c_str(), entrynum);
    }
    ctx.r[3] = static_cast<uint32_t>(entrynum);
    ctx.r[4] = file_info;
    hle_DVDFastOpen(ctx, mem);
}

static void hle_DVDClose(PPCContext& ctx, Memory& mem) {
    if (mem.is_valid_range(ctx.r[3], 60u)) {
        mem.write_u32(ctx.r[3] + 12u, 0u);
    }
    ctx.r[3] = 1u;
}

static void hle_DVDReadAsyncPrio(PPCContext& ctx, Memory& mem) {
    uint32_t file_info = ctx.r[3];
    uint32_t dst_addr  = ctx.r[4];
    uint32_t length    = ctx.r[5];
    uint32_t offset    = ctx.r[6];
    uint32_t callback  = ctx.r[7];

    int32_t bytes_read = -1;
    if (mem.is_valid_range(file_info, 60u) && mem.is_valid_range(dst_addr, length)) {
        int32_t entrynum = static_cast<int32_t>(mem.read_u32(file_info + 56u));
        const auto* iso  = IsoStreamReader::active_instance();
        if (iso) {
            auto data = iso->read_file_slice(entrynum, offset, length);
            if (!data.empty()) {
                mem.write_bytes(dst_addr, data.data(), data.size());
                bytes_read = static_cast<int32_t>(data.size());
            }
        }
        mem.write_u32(file_info + 36u, static_cast<uint32_t>((std::max)(bytes_read, 0)));
        const bool has_cb = (callback >= kGcRamBase && callback < kGcRamBase + kGcRamSize);
        mem.write_u32(file_info + 12u, has_cb ? 1u : 0u); // DVD_STATE_BUSY until deferred cb runs
    }
    enqueue_pending_hle_callback(
        callback,
        static_cast<uint32_t>(bytes_read),
        file_info,
        file_info
    );
    ctx.r[3] = 1u;
}

static void hle_DVDReadPrio(PPCContext& ctx, Memory& mem) {
    uint32_t file_info = ctx.r[3];
    uint32_t dst_addr  = ctx.r[4];
    uint32_t length    = ctx.r[5];
    uint32_t offset    = ctx.r[6];

    int32_t bytes_read = -1;
    if (mem.is_valid_range(file_info, 60u) && mem.is_valid_range(dst_addr, length)) {
        int32_t entrynum = static_cast<int32_t>(mem.read_u32(file_info + 56u));
        const auto* iso  = IsoStreamReader::active_instance();
        if (iso) {
            auto data = iso->read_file_slice(entrynum, offset, length);
            if (!data.empty()) {
                mem.write_bytes(dst_addr, data.data(), data.size());
                bytes_read = static_cast<int32_t>(data.size());
            }
        }
        mem.write_u32(file_info + 12u, 0u);
        mem.write_u32(file_info + 36u, static_cast<uint32_t>((std::max)(bytes_read, 0)));
    }
    ctx.r[3] = static_cast<uint32_t>(bytes_read);
}

// Static AR helper functions removed: all AI/AR/ARQ/AX/DSP/snd_* calls route
// directly to AudioAXInterface::dispatch_audio_call().

// ============================================================================
// 6. Fast Native LzsDecode HLE (0x80077680 in compless.obj)
// ============================================================================
static void hle_LzsDecode(PPCContext& ctx, Memory& mem) {
    // Signature in compless.obj (0x80077680): void LzsDecode(unsigned char* dst, unsigned char* src)
    // r3 = dst, r4 = src (big-endian header: [0]=decomp_sz, [4]=bitstream_sz, [8]=unk, [12..]=bits+data)
    uint32_t dst_va = ctx.r[3];
    uint32_t src_va = ctx.r[4];
    if (!mem.is_valid_range(src_va, 12u)) {
        PN03_LOGF(LogLevel::Warn, "LZS", "Invalid src_va=0x%08X dst_va=0x%08X", src_va, dst_va);
        ctx.r[3] = 0u;
        return;
    }
    uint32_t decomp_sz = mem.read_u32(src_va + 0u);
    uint32_t bitstream_sz = mem.read_u32(src_va + 4u);
    if (decomp_sz == 0u || decomp_sz > 0x01800000u || !mem.is_valid_range(dst_va, decomp_sz)) {
        PN03_LOGF(LogLevel::Warn, "LZS", "Invalid LZS hdr src=0x%08X dst=0x%08X decomp_sz=%u bit_sz=%u",
                  src_va, dst_va, decomp_sz, bitstream_sz);
        ctx.r[3] = 0u;
        return;
    }
    size_t max_src = static_cast<size_t>((kGcRamBase + kGcRamSize) - src_va);
    if (static_cast<size_t>(bitstream_sz) + 12u >= max_src) {
        PN03_LOGF(LogLevel::Warn, "LZS", "Truncated LZS src=0x%08X bit_sz=%u max_src=%zu",
                  src_va, bitstream_sz, max_src);
        ctx.r[3] = 0u;
        return;
    }

    const uint8_t* src = mem.raw_ptr(src_va);
    uint8_t* dst = mem.raw_ptr(dst_va);
    size_t bit_ptr = 12u;
    size_t data_ptr = 12u + static_cast<size_t>(bitstream_sz);
    uint8_t cur_bits = src[bit_ptr];
    int bit_idx = 7;

    auto get_bit = [&]() -> int {
        int b;
        if (bit_idx == 0) {
            b = cur_bits & 1;
            bit_idx = 7;
            ++bit_ptr;
            cur_bits = (bit_ptr < max_src) ? src[bit_ptr] : 0;
        } else {
            b = (cur_bits >> bit_idx) & 1;
            --bit_idx;
        }
        return b;
    };

    size_t out_pos = 0;
    while (data_ptr < max_src) {
        if (get_bit() == 1) {
            if (out_pos < decomp_sz) {
                dst[out_pos++] = src[data_ptr++];
            } else {
                ++data_ptr;
                break;
            }
        } else if (get_bit() == 1) {
            if (data_ptr + 1u >= max_src) break;
            uint8_t b0 = src[data_ptr];
            uint8_t b1 = src[data_ptr + 1u];
            data_ptr += 2u;
            uint32_t dist = ((static_cast<uint32_t>(b1) << 8) | static_cast<uint32_t>(b0)) >> 3;
            uint32_t len3 = b0 & 7u;
            uint32_t match_len = 0;
            if (len3 == 0u) {
                uint8_t ext = (data_ptr < max_src) ? src[data_ptr++] : 0u;
                if (dist == 0u) break;
                match_len = static_cast<uint32_t>(ext) + 9u;
            } else {
                match_len = len3 + 2u;
            }
            for (uint32_t k = 0; k < match_len; ++k) {
                uint8_t v = (dist > 0u && dist <= out_pos) ? dst[out_pos - dist] : 0u;
                if (out_pos < decomp_sz) dst[out_pos++] = v;
            }
        } else {
            int bc = get_bit();
            int bd = get_bit();
            if (data_ptr >= max_src) break;
            uint32_t dist = src[data_ptr++];
            uint32_t match_len = static_cast<uint32_t>((bc << 1) | bd) + 2u;
            for (uint32_t k = 0; k < match_len; ++k) {
                uint8_t v = (dist > 0u && dist <= out_pos) ? dst[out_pos - dist] : 0u;
                if (out_pos < decomp_sz) dst[out_pos++] = v;
            }
        }
    }
    PN03_LOGF(LogLevel::Debug, "LZS", "LzsDecode src=0x%08X dst=0x%08X hdr_sz=%u out=%zu",
              src_va, dst_va, decomp_sz, out_pos);
    ctx.r[3] = dst_va + static_cast<uint32_t>(out_pos > 0 ? out_pos - 1 : 0);
}

// ============================================================================
// 7. PSMTX / PSVEC / CARD / PAD / C-Stdlib / Math HLE
// ============================================================================
static PN03_FORCEINLINE float read_f32_be_ptr(const uint8_t* p) noexcept {
    uint32_t raw = 0;
    std::memcpy(&raw, p, sizeof(uint32_t));
    const uint32_t bits = bswap32(raw);
    float val = 0.0f;
    std::memcpy(&val, &bits, sizeof(float));
    return val;
}

static PN03_FORCEINLINE void write_f32_be_ptr(uint8_t* p, float val) noexcept {
    uint32_t bits = 0;
    std::memcpy(&bits, &val, sizeof(float));
    const uint32_t be = bswap32(bits);
    std::memcpy(p, &be, sizeof(uint32_t));
}

static PN03_FORCEINLINE void read_mtx34(const Memory& mem, uint32_t vaddr, float m[3][4]) {
    if (const uint8_t* p = mem.fast_ram_ptr(vaddr, 48u)) [[likely]] {
        for (int r = 0; r < 3; ++r, p += 16) {
            m[r][0] = read_f32_be_ptr(p + 0);
            m[r][1] = read_f32_be_ptr(p + 4);
            m[r][2] = read_f32_be_ptr(p + 8);
            m[r][3] = read_f32_be_ptr(p + 12);
        }
        return;
    }
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 4; ++c) {
            m[r][c] = mem.read_f32(vaddr + static_cast<uint32_t>((r * 4 + c) * 4));
        }
    }
}

static PN03_FORCEINLINE void write_mtx34(Memory& mem, uint32_t vaddr, const float m[3][4]) {
    if (uint8_t* p = mem.fast_ram_ptr(vaddr, 48u)) [[likely]] {
        for (int r = 0; r < 3; ++r, p += 16) {
            write_f32_be_ptr(p + 0, m[r][0]);
            write_f32_be_ptr(p + 4, m[r][1]);
            write_f32_be_ptr(p + 8, m[r][2]);
            write_f32_be_ptr(p + 12, m[r][3]);
        }
        return;
    }
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 4; ++c) {
            mem.write_f32(vaddr + static_cast<uint32_t>((r * 4 + c) * 4), m[r][c]);
        }
    }
}

static PN03_FORCEINLINE void read_vec3(const Memory& mem, uint32_t vaddr, float v[3]) {
    if (const uint8_t* p = mem.fast_ram_ptr(vaddr, 12u)) [[likely]] {
        v[0] = read_f32_be_ptr(p + 0);
        v[1] = read_f32_be_ptr(p + 4);
        v[2] = read_f32_be_ptr(p + 8);
        return;
    }
    v[0] = mem.read_f32(vaddr + 0);
    v[1] = mem.read_f32(vaddr + 4);
    v[2] = mem.read_f32(vaddr + 8);
}

static PN03_FORCEINLINE void write_vec3(Memory& mem, uint32_t vaddr, const float v[3]) {
    if (uint8_t* p = mem.fast_ram_ptr(vaddr, 12u)) [[likely]] {
        write_f32_be_ptr(p + 0, v[0]);
        write_f32_be_ptr(p + 4, v[1]);
        write_f32_be_ptr(p + 8, v[2]);
        return;
    }
    mem.write_f32(vaddr + 0, v[0]);
    mem.write_f32(vaddr + 4, v[1]);
    mem.write_f32(vaddr + 8, v[2]);
}

static void hle_PSMTXIdentity(PPCContext& ctx, Memory& mem) {
    const float id[3][4] = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
    };
    write_mtx34(mem, ctx.r[3], id);
}

static void hle_PSMTXCopy(PPCContext& ctx, Memory& mem) {
    if (ctx.r[3] == ctx.r[4]) return;
    float m[3][4];
    read_mtx34(mem, ctx.r[3], m);
    write_mtx34(mem, ctx.r[4], m);
}

static void hle_PSMTXConcat(PPCContext& ctx, Memory& mem) {
    float a[3][4], b[3][4], out[3][4]{};
    read_mtx34(mem, ctx.r[3], a);
    read_mtx34(mem, ctx.r[4], b);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            out[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j] + (j == 3 ? a[i][3] : 0.0f);
        }
    }
    write_mtx34(mem, ctx.r[5], out);
}

static void hle_PSMTXInverse(PPCContext& ctx, Memory& mem) {
    float m[3][4];
    read_mtx34(mem, ctx.r[3], m);
    float det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
                m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
                m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    if (std::fabs(det) < 1e-8f) {
        hle_PSMTXIdentity(ctx, mem);
        ctx.r[3] = 0u;
        return;
    }
    float inv_det = 1.0f / det;
    float out[3][4]{};
    out[0][0] =  (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * inv_det;
    out[0][1] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]) * inv_det;
    out[0][2] =  (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * inv_det;
    out[1][0] = -(m[1][0] * m[2][2] - m[1][2] * m[2][0]) * inv_det;
    out[1][1] =  (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * inv_det;
    out[1][2] = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]) * inv_det;
    out[2][0] =  (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * inv_det;
    out[2][1] = -(m[0][0] * m[2][1] - m[0][1] * m[2][0]) * inv_det;
    out[2][2] =  (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * inv_det;
    for (int i = 0; i < 3; ++i) {
        out[i][3] = -(out[i][0] * m[0][3] + out[i][1] * m[1][3] + out[i][2] * m[2][3]);
    }
    write_mtx34(mem, ctx.r[4], out);
    ctx.r[3] = 1u;
}

static void hle_PSMTXTrans(PPCContext& ctx, Memory& mem) {
    const float xt = static_cast<float>(ctx.f[1]);
    const float yt = static_cast<float>(ctx.f[2]);
    const float zt = static_cast<float>(ctx.f[3]);
    const float m[3][4] = {
        {1.0f, 0.0f, 0.0f, xt},
        {0.0f, 1.0f, 0.0f, yt},
        {0.0f, 0.0f, 1.0f, zt},
    };
    write_mtx34(mem, ctx.r[3], m);
}

static void hle_PSMTXScale(PPCContext& ctx, Memory& mem) {
    const float xs = static_cast<float>(ctx.f[1]);
    const float ys = static_cast<float>(ctx.f[2]);
    const float zs = static_cast<float>(ctx.f[3]);
    const float m[3][4] = {
        {xs,   0.0f, 0.0f, 0.0f},
        {0.0f, ys,   0.0f, 0.0f},
        {0.0f, 0.0f, zs,   0.0f},
    };
    write_mtx34(mem, ctx.r[3], m);
}

static void hle_PSMTXMultVec(PPCContext& ctx, Memory& mem) {
    float m[3][4], v[3], out[3];
    read_mtx34(mem, ctx.r[3], m);
    read_vec3(mem, ctx.r[4], v);
    out[0] = m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3];
    out[1] = m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3];
    out[2] = m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3];
    write_vec3(mem, ctx.r[5], out);
}

static void hle_PSMTXMultVecSR(PPCContext& ctx, Memory& mem) {
    float m[3][4], v[3], out[3];
    read_mtx34(mem, ctx.r[3], m);
    read_vec3(mem, ctx.r[4], v);
    out[0] = m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2];
    out[1] = m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2];
    out[2] = m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2];
    write_vec3(mem, ctx.r[5], out);
}

static void hle_C_MTXOrtho(PPCContext& ctx, Memory& mem) {
    uint32_t m_va = ctx.r[3];
    float t = static_cast<float>(ctx.f[1]);
    float b = static_cast<float>(ctx.f[2]);
    float l = static_cast<float>(ctx.f[3]);
    float r = static_cast<float>(ctx.f[4]);
    float n = static_cast<float>(ctx.f[5]);
    float f = static_cast<float>(ctx.f[6]);
    if (!mem.is_valid_range(m_va, 64u)) return;
    for (int i = 0; i < 16; ++i) mem.write_f32(m_va + static_cast<uint32_t>(i * 4), 0.0f);
    if (std::fabs(r - l) > 1e-6f) {
        mem.write_f32(m_va + 0u,  2.0f / (r - l));
        mem.write_f32(m_va + 12u, -(r + l) / (r - l));
    }
    if (std::fabs(t - b) > 1e-6f) {
        mem.write_f32(m_va + 20u, 2.0f / (t - b));
        mem.write_f32(m_va + 28u, -(t + b) / (t - b));
    }
    if (std::fabs(f - n) > 1e-6f) {
        mem.write_f32(m_va + 40u, -1.0f / (f - n));
        mem.write_f32(m_va + 44u, -f / (f - n));
    }
    mem.write_f32(m_va + 60u, 1.0f);
}

static void hle_C_MTXPerspective(PPCContext& ctx, Memory& mem) {
    uint32_t m_va = ctx.r[3];
    float fov_y  = static_cast<float>(ctx.f[1]);
    float aspect = static_cast<float>(ctx.f[2]);
    float n      = static_cast<float>(ctx.f[3]);
    float f      = static_cast<float>(ctx.f[4]);
    if (!mem.is_valid_range(m_va, 64u)) return;
    for (int i = 0; i < 16; ++i) mem.write_f32(m_va + static_cast<uint32_t>(i * 4), 0.0f);
    float rad = fov_y * 0.5f * (3.1415926535f / 180.0f);
    float cot = (std::fabs(std::sin(rad)) > 1e-6f) ? (std::cos(rad) / std::sin(rad)) : 1.0f;
    mem.write_f32(m_va + 0u,  (std::fabs(aspect) > 1e-6f) ? (cot / aspect) : cot);
    mem.write_f32(m_va + 20u, cot);
    if (std::fabs(f - n) > 1e-6f) {
        mem.write_f32(m_va + 40u, -n / (f - n));
        mem.write_f32(m_va + 44u, -(f * n) / (f - n));
    }
    mem.write_f32(m_va + 56u, -1.0f);
}

static void hle_C_MTXLookAt(PPCContext& ctx, Memory& mem) {
    float eye[3], up[3], tgt[3];
    read_vec3(mem, ctx.r[4], eye);
    read_vec3(mem, ctx.r[5], up);
    read_vec3(mem, ctx.r[6], tgt);
    float look[3] = {eye[0] - tgt[0], eye[1] - tgt[1], eye[2] - tgt[2]};
    float lmag = std::sqrt(look[0] * look[0] + look[1] * look[1] + look[2] * look[2]);
    if (lmag > 1e-6f) { look[0] /= lmag; look[1] /= lmag; look[2] /= lmag; }
    float right[3] = {
        up[1] * look[2] - up[2] * look[1],
        up[2] * look[0] - up[0] * look[2],
        up[0] * look[1] - up[1] * look[0]
    };
    float rmag = std::sqrt(right[0] * right[0] + right[1] * right[1] + right[2] * right[2]);
    if (rmag > 1e-6f) { right[0] /= rmag; right[1] /= rmag; right[2] /= rmag; }
    float vup[3] = {
        look[1] * right[2] - look[2] * right[1],
        look[2] * right[0] - look[0] * right[2],
        look[0] * right[1] - look[1] * right[0]
    };
    float m[3][4] = {
        {right[0], right[1], right[2], -(eye[0] * right[0] + eye[1] * right[1] + eye[2] * right[2])},
        {vup[0],   vup[1],   vup[2],   -(eye[0] * vup[0]   + eye[1] * vup[1]   + eye[2] * vup[2])},
        {look[0],  look[1],  look[2],  -(eye[0] * look[0]  + eye[1] * look[1]  + eye[2] * look[2])},
    };
    write_mtx34(mem, ctx.r[3], m);
}

static void hle_PSVECAdd(PPCContext& ctx, Memory& mem) {
    float a[3], b[3], out[3];
    read_vec3(mem, ctx.r[3], a);
    read_vec3(mem, ctx.r[4], b);
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
    write_vec3(mem, ctx.r[5], out);
}

static void hle_PSVECSubtract(PPCContext& ctx, Memory& mem) {
    float a[3], b[3], out[3];
    read_vec3(mem, ctx.r[3], a);
    read_vec3(mem, ctx.r[4], b);
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
    write_vec3(mem, ctx.r[5], out);
}

static void hle_PSVECScale(PPCContext& ctx, Memory& mem) {
    float a[3], out[3];
    read_vec3(mem, ctx.r[3], a);
    float s = static_cast<float>(ctx.f[1]);
    out[0] = a[0] * s;
    out[1] = a[1] * s;
    out[2] = a[2] * s;
    write_vec3(mem, ctx.r[4], out);
}

static void hle_PSVECNormalize(PPCContext& ctx, Memory& mem) {
    float a[3], out[3]{};
    read_vec3(mem, ctx.r[3], a);
    float mag = std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    if (mag > 1e-8f) {
        out[0] = a[0] / mag;
        out[1] = a[1] / mag;
        out[2] = a[2] / mag;
    }
    write_vec3(mem, ctx.r[4], out);
}

static void hle_PSVECMag(PPCContext& ctx, Memory& mem) {
    float a[3];
    read_vec3(mem, ctx.r[3], a);
    ctx.f[1] = std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    ctx.ps0[1] = static_cast<float>(ctx.f[1]);
}

static void hle_PSVECDotProduct(PPCContext& ctx, Memory& mem) {
    float a[3], b[3];
    read_vec3(mem, ctx.r[3], a);
    read_vec3(mem, ctx.r[4], b);
    ctx.f[1] = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    ctx.ps0[1] = static_cast<float>(ctx.f[1]);
}

static void hle_PSVECCrossProduct(PPCContext& ctx, Memory& mem) {
    float a[3], b[3], out[3];
    read_vec3(mem, ctx.r[3], a);
    read_vec3(mem, ctx.r[4], b);
    out[0] = a[1] * b[2] - a[2] * b[1];
    out[1] = a[2] * b[0] - a[0] * b[2];
    out[2] = a[0] * b[1] - a[1] * b[0];
    write_vec3(mem, ctx.r[5], out);
}

static void hle_PSVECDistance(PPCContext& ctx, Memory& mem) {
    float a[3], b[3];
    read_vec3(mem, ctx.r[3], a);
    read_vec3(mem, ctx.r[4], b);
    float dx = a[0] - b[0], dy = a[1] - b[1], dz = a[2] - b[2];
    ctx.f[1] = std::sqrt(dx * dx + dy * dy + dz * dz);
    ctx.ps0[1] = static_cast<float>(ctx.f[1]);
}

static uint32_t g_os_sound_mode = 0u; // 0 = Stereo, 1 = Mono

static constexpr int32_t kCardResultReady   = 0;
static constexpr int32_t kCardResultBusy    = -1;
static constexpr int32_t kCardResultWrong   = -2;
static constexpr int32_t kCardResultNoCard  = -3;
static constexpr int32_t kCardResultNoFile  = -4;
static constexpr int32_t kCardResultBroken  = -6;
static constexpr int32_t kCardResultExist   = -7;
static constexpr int32_t kCardResultNoEnt   = -8;
static constexpr int32_t kCardResultInsSpace= -9;
static constexpr int32_t kCardResultFatal   = -128;

static constexpr uint32_t kCardSectorSize   = 8192u;
static constexpr uint32_t kCardMemSizeMb    = 16u;
static constexpr uint32_t kCardTotalBlocks  = 251u;
static constexpr uint32_t kCardMaxFiles     = 127u;
static constexpr uint16_t kCardOpenMagic    = 0x504Eu; // "PN" open handle token in CARDFileInfo::iBlock

struct VirtualCardFile {
    bool                 in_use             = false;
    std::string          file_name{};
    char                 game_code[4]       = {'G', 'P', 'N', 'E'};
    char                 company[2]         = {'0', '8'};
    uint32_t             length             = 0u;
    uint32_t             time_sec           = 100000000u;
    uint8_t              banner_format      = 0u;
    uint32_t             icon_addr          = 0xFFFFFFFFu;
    uint16_t             icon_format        = 0u;
    uint16_t             icon_speed         = 0u;
    uint32_t             comment_addr       = 0xFFFFFFFFu;
    uint32_t             offset_banner      = 0xFFFFFFFFu;
    uint32_t             offset_banner_tlut = 0xFFFFFFFFu;
    uint32_t             offset_icon[8]     = {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
                                               0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu};
    uint32_t             offset_icon_tlut   = 0xFFFFFFFFu;
    uint32_t             offset_data        = 0xFFFFFFFFu;
    std::vector<uint8_t> data{};
};

struct VirtualCardSlot {
    bool                         inserted        = false;
    bool                         mounted         = false;
    bool                         loaded_disk     = false;
    int32_t                      last_result     = kCardResultReady;
    uint32_t                     last_xfer_bytes = 0u;
    std::vector<VirtualCardFile> files{};
};

static std::mutex      g_card_mtx;
static VirtualCardSlot g_card_slots[2]{};

static std::string get_card_save_dir() {
    const std::string& cfg_dir = global_gx_3d_interface().config().save_dir;
    std::string dir = cfg_dir.empty() ? std::string("saves") : cfg_dir;
    std::error_code ec;
    fs::create_directories(dir, ec);
    return dir;
}

static std::string get_card_save_path() {
    return (fs::path(get_card_save_dir()) / "pn03_card_a.sav").string();
}

static std::string get_card_vdir_path() {
    return (fs::path(get_card_save_dir()) / "pn03_card_a.vdir").string();
}

static void card_save_vdir_locked(uint32_t chan) {
    if (chan != 0u) return;
    const std::string vpath = get_card_vdir_path();
    std::ofstream f(vpath, std::ios::binary | std::ios::trunc);
    if (!f.is_open()) return;

    const char magic[8] = {'P', 'N', 'V', 'C', '0', '0', '0', '1'};
    f.write(magic, 8);
    const uint32_t count = static_cast<uint32_t>(g_card_slots[0].files.size());
    f.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const auto& entry : g_card_slots[0].files) {
        uint8_t used = entry.in_use ? 1u : 0u;
        f.write(reinterpret_cast<const char*>(&used), sizeof(used));
        if (!entry.in_use) continue;

        uint32_t name_len = static_cast<uint32_t>(entry.file_name.size());
        f.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        f.write(entry.file_name.data(), name_len);
        f.write(entry.game_code, 4);
        f.write(entry.company, 2);
        f.write(reinterpret_cast<const char*>(&entry.length), sizeof(entry.length));
        f.write(reinterpret_cast<const char*>(&entry.time_sec), sizeof(entry.time_sec));
        f.write(reinterpret_cast<const char*>(&entry.banner_format), sizeof(entry.banner_format));
        f.write(reinterpret_cast<const char*>(&entry.icon_addr), sizeof(entry.icon_addr));
        f.write(reinterpret_cast<const char*>(&entry.icon_format), sizeof(entry.icon_format));
        f.write(reinterpret_cast<const char*>(&entry.icon_speed), sizeof(entry.icon_speed));
        f.write(reinterpret_cast<const char*>(&entry.comment_addr), sizeof(entry.comment_addr));
        f.write(reinterpret_cast<const char*>(&entry.offset_banner), sizeof(entry.offset_banner));
        f.write(reinterpret_cast<const char*>(&entry.offset_banner_tlut), sizeof(entry.offset_banner_tlut));
        f.write(reinterpret_cast<const char*>(entry.offset_icon), sizeof(entry.offset_icon));
        f.write(reinterpret_cast<const char*>(&entry.offset_icon_tlut), sizeof(entry.offset_icon_tlut));
        f.write(reinterpret_cast<const char*>(&entry.offset_data), sizeof(entry.offset_data));
        uint32_t data_sz = static_cast<uint32_t>(entry.data.size());
        f.write(reinterpret_cast<const char*>(&data_sz), sizeof(data_sz));
        if (data_sz > 0u) {
            f.write(reinterpret_cast<const char*>(entry.data.data()), data_sz);
        }
    }
}

static void card_ensure_slot_locked(uint32_t chan) {
    g_card_slots[0].inserted = true;
    g_card_slots[1].inserted = false;
    if (chan != 0u) return;
    auto& slot = g_card_slots[0];
    if (slot.files.size() != kCardMaxFiles) {
        slot.files.assign(kCardMaxFiles, VirtualCardFile{});
    }
    if (slot.loaded_disk) return;
    slot.loaded_disk = true;

    const std::string vpath = get_card_vdir_path();
    std::ifstream f(vpath, std::ios::binary);
    if (!f.is_open()) return;

    char magic[8]{};
    f.read(magic, 8);
    if (std::memcmp(magic, "PNVC0001", 8) != 0) return;
    uint32_t count = 0u;
    f.read(reinterpret_cast<char*>(&count), sizeof(count));
    const uint32_t n = (std::min)(count, kCardMaxFiles);
    for (uint32_t i = 0; i < n; ++i) {
        uint8_t used = 0u;
        f.read(reinterpret_cast<char*>(&used), sizeof(used));
        if (!f.good()) break;
        if (!used) continue;

        auto& entry = slot.files[i];
        entry.in_use = true;
        uint32_t name_len = 0u;
        f.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
        name_len = (std::min)(name_len, 64u);
        entry.file_name.resize(name_len);
        if (name_len > 0u) f.read(entry.file_name.data(), name_len);
        f.read(entry.game_code, 4);
        f.read(entry.company, 2);
        f.read(reinterpret_cast<char*>(&entry.length), sizeof(entry.length));
        f.read(reinterpret_cast<char*>(&entry.time_sec), sizeof(entry.time_sec));
        f.read(reinterpret_cast<char*>(&entry.banner_format), sizeof(entry.banner_format));
        f.read(reinterpret_cast<char*>(&entry.icon_addr), sizeof(entry.icon_addr));
        f.read(reinterpret_cast<char*>(&entry.icon_format), sizeof(entry.icon_format));
        f.read(reinterpret_cast<char*>(&entry.icon_speed), sizeof(entry.icon_speed));
        f.read(reinterpret_cast<char*>(&entry.comment_addr), sizeof(entry.comment_addr));
        f.read(reinterpret_cast<char*>(&entry.offset_banner), sizeof(entry.offset_banner));
        f.read(reinterpret_cast<char*>(&entry.offset_banner_tlut), sizeof(entry.offset_banner_tlut));
        f.read(reinterpret_cast<char*>(entry.offset_icon), sizeof(entry.offset_icon));
        f.read(reinterpret_cast<char*>(&entry.offset_icon_tlut), sizeof(entry.offset_icon_tlut));
        f.read(reinterpret_cast<char*>(&entry.offset_data), sizeof(entry.offset_data));
        uint32_t data_sz = 0u;
        f.read(reinterpret_cast<char*>(&data_sz), sizeof(data_sz));
        data_sz = (std::min)(data_sz, 0x200000u);
        entry.data.resize(data_sz);
        if (data_sz > 0u) {
            f.read(reinterpret_cast<char*>(entry.data.data()), data_sz);
        }
    }
}

static void reset_card_state_for_runtime_reset() {
    std::lock_guard<std::mutex> lk(g_card_mtx);
    g_os_sound_mode = 0u;
    for (int i = 0; i < 2; ++i) {
        g_card_slots[i] = VirtualCardSlot{};
    }
    g_card_slots[0].inserted = true;
}

static void invoke_card_callback_now(uint32_t cb_vaddr, int32_t chan, int32_t result, PPCContext& ctx, Memory& mem) {
    if (cb_vaddr < kGcRamBase || cb_vaddr >= kGcRamBase + kGcRamSize) return;
    RecompFuncPtr fn = recomp::lookup_recompiled_function(cb_vaddr);
    if (fn == nullptr) return;

    const uint32_t saved_r0  = ctx.r[0];
    uint32_t saved_gpr[10]{};
    std::memcpy(saved_gpr, &ctx.r[3], sizeof(saved_gpr));
    const uint32_t saved_lr  = ctx.lr;
    const uint32_t saved_ctr = ctx.ctr;
    const uint32_t saved_xer = ctx.xer;
    const uint32_t saved_cr  = ctx.pack_cr();

    ctx.r[3] = static_cast<uint32_t>(chan);
    ctx.r[4] = static_cast<uint32_t>(result);
    fn(ctx, mem);

    ctx.r[0] = saved_r0;
    std::memcpy(&ctx.r[3], saved_gpr, sizeof(saved_gpr));
    ctx.lr   = saved_lr;
    ctx.ctr  = saved_ctr;
    ctx.xer  = saved_xer;
    ctx.unpack_cr(0xFFu, saved_cr);
}

static int32_t card_validate_channel(int32_t chan, bool require_mounted = true) {
    if (chan < 0 || chan >= 2) return kCardResultFatal;
    card_ensure_slot_locked(static_cast<uint32_t>(chan));
    if (!g_card_slots[chan].inserted) return kCardResultNoCard;
    if (require_mounted && !g_card_slots[chan].mounted) return kCardResultNoCard;
    return kCardResultReady;
}

static void card_fill_file_info(Memory& mem, uint32_t fi_va, int32_t chan, int32_t file_no, uint32_t length) {
    if (fi_va >= kGcRamBase && mem.is_valid_range(fi_va, 20u)) {
        mem.write_u32(fi_va + 0u, static_cast<uint32_t>(chan));
        mem.write_u32(fi_va + 4u, static_cast<uint32_t>(file_no));
        mem.write_u32(fi_va + 8u, 0u);
        mem.write_u32(fi_va + 12u, length);
        mem.write_u16(fi_va + 16u, kCardOpenMagic);
        mem.write_u16(fi_va + 18u, 0u);
    }
}

static int32_t card_find_file_locked(uint32_t chan, const std::string& name) {
    if (chan != 0u) return -1;
    const auto& files = g_card_slots[0].files;
    for (uint32_t i = 0; i < files.size(); ++i) {
        if (files[i].in_use && files[i].file_name == name) {
            return static_cast<int32_t>(i);
        }
    }
    return -1;
}

static void hle_CARDInit(PPCContext& ctx, Memory& mem) {
    (void)ctx; (void)mem;
    std::lock_guard<std::mutex> lk(g_card_mtx);
    card_ensure_slot_locked(0u);
    g_card_slots[0].last_result = kCardResultReady;
    g_card_slots[1].last_result = kCardResultNoCard;
}

static void hle_CARDGetResultCode(PPCContext& ctx, Memory& mem) {
    (void)mem;
    const int32_t chan = static_cast<int32_t>(ctx.r[3]);
    std::lock_guard<std::mutex> lk(g_card_mtx);
    if (chan < 0 || chan >= 2) {
        ctx.r[3] = static_cast<uint32_t>(kCardResultFatal);
        return;
    }
    card_ensure_slot_locked(static_cast<uint32_t>(chan));
    ctx.r[3] = static_cast<uint32_t>(g_card_slots[chan].last_result);
}

static void hle_CARDProbe(PPCContext& ctx, Memory& mem) {
    (void)mem;
    const int32_t chan = static_cast<int32_t>(ctx.r[3]);
    std::lock_guard<std::mutex> lk(g_card_mtx);
    if (chan < 0 || chan >= 2) { ctx.r[3] = 0u; return; }
    card_ensure_slot_locked(static_cast<uint32_t>(chan));
    ctx.r[3] = g_card_slots[chan].inserted ? 1u : 0u;
}

static void hle_CARDProbeEx(PPCContext& ctx, Memory& mem) {
    const int32_t chan = static_cast<int32_t>(ctx.r[3]);
    std::lock_guard<std::mutex> lk(g_card_mtx);
    if (chan == 0) {
        card_ensure_slot_locked(0u);
        if (ctx.r[4] >= kGcRamBase && mem.is_valid_range(ctx.r[4], 4u)) mem.write_u32(ctx.r[4], kCardMemSizeMb);
        if (ctx.r[5] >= kGcRamBase && mem.is_valid_range(ctx.r[5], 4u)) mem.write_u32(ctx.r[5], kCardSectorSize);
        g_card_slots[0].last_result = kCardResultReady;
        ctx.r[3] = static_cast<uint32_t>(kCardResultReady);
    } else {
        ctx.r[3] = static_cast<uint32_t>(kCardResultNoCard);
    }
}

static void hle_CARDFreeBlocks(PPCContext& ctx, Memory& mem) {
    const int32_t chan = static_cast<int32_t>(ctx.r[3]);
    std::lock_guard<std::mutex> lk(g_card_mtx);
    const int32_t err = card_validate_channel(chan);
    if (err != kCardResultReady) {
        ctx.r[3] = static_cast<uint32_t>(err);
        return;
    }
    uint32_t used_blocks = 0u;
    uint32_t used_files = 0u;
    for (const auto& f : g_card_slots[0].files) {
        if (!f.in_use) continue;
        ++used_files;
        used_blocks += (f.length + kCardSectorSize - 1u) / kCardSectorSize;
    }
    const uint32_t free_blocks = (kCardTotalBlocks > used_blocks) ? (kCardTotalBlocks - used_blocks) : 0u;
    const uint32_t free_files  = (120u > used_files) ? (120u - used_files) : 0u;
    if (ctx.r[4] >= kGcRamBase && mem.is_valid_range(ctx.r[4], 4u)) mem.write_u32(ctx.r[4], free_blocks * kCardSectorSize);
    if (ctx.r[5] >= kGcRamBase && mem.is_valid_range(ctx.r[5], 4u)) mem.write_u32(ctx.r[5], free_files);
    g_card_slots[0].last_result = kCardResultReady;
    ctx.r[3] = static_cast<uint32_t>(kCardResultReady);
}

static void hle_CARDMount(PPCContext& ctx, Memory& mem, bool is_async) {
    const int32_t  chan      = static_cast<int32_t>(ctx.r[3]);
    const uint32_t attach_cb = is_async ? ctx.r[6] : 0u;
    int32_t res = kCardResultNoCard;
    {
        std::lock_guard<std::mutex> lk(g_card_mtx);
        res = card_validate_channel(chan, false);
        if (res == kCardResultReady) {
            g_card_slots[chan].mounted     = true;
            g_card_slots[chan].last_result = kCardResultReady;
        } else if (chan >= 0 && chan < 2) {
            g_card_slots[chan].last_result = res;
        }
    }
    ctx.r[3] = static_cast<uint32_t>(res);
    if (res == kCardResultReady && attach_cb != 0u) {
        invoke_card_callback_now(attach_cb, chan, res, ctx, mem);
    }
}

static void hle_CARDUnmount(PPCContext& ctx, Memory& mem) {
    (void)mem;
    const int32_t chan = static_cast<int32_t>(ctx.r[3]);
    std::lock_guard<std::mutex> lk(g_card_mtx);
    if (chan < 0 || chan >= 2) {
        ctx.r[3] = static_cast<uint32_t>(kCardResultFatal);
        return;
    }
    card_ensure_slot_locked(static_cast<uint32_t>(chan));
    g_card_slots[chan].mounted     = false;
    g_card_slots[chan].last_result = kCardResultReady;
    ctx.r[3] = static_cast<uint32_t>(kCardResultReady);
}

static void hle_CARDCheck(PPCContext& ctx, Memory& mem, bool has_xfer, bool is_async) {
    const int32_t  chan     = static_cast<int32_t>(ctx.r[3]);
    const uint32_t xfer_va  = has_xfer ? ctx.r[4] : 0u;
    const uint32_t cb_va    = is_async ? (has_xfer ? ctx.r[5] : ctx.r[4]) : 0u;
    int32_t res = kCardResultNoCard;
    {
        std::lock_guard<std::mutex> lk(g_card_mtx);
        res = card_validate_channel(chan, true);
        if (res == kCardResultReady) {
            if (xfer_va >= kGcRamBase && mem.is_valid_range(xfer_va, 4u)) mem.write_u32(xfer_va, 0u);
            g_card_slots[chan].last_xfer_bytes = 0u;
            g_card_slots[chan].last_result     = kCardResultReady;
        }
    }
    ctx.r[3] = static_cast<uint32_t>(res);
    if (res == kCardResultReady && cb_va != 0u) {
        invoke_card_callback_now(cb_va, chan, res, ctx, mem);
    }
}

static void hle_CARDFormat(PPCContext& ctx, Memory& mem, bool is_async) {
    const int32_t  chan  = static_cast<int32_t>(ctx.r[3]);
    const uint32_t cb_va = is_async ? ctx.r[4] : 0u;
    int32_t res = kCardResultNoCard;
    {
        std::lock_guard<std::mutex> lk(g_card_mtx);
        res = card_validate_channel(chan, false);
        if (res == kCardResultReady) {
            g_card_slots[chan].files.assign(kCardMaxFiles, VirtualCardFile{});
            g_card_slots[chan].mounted     = true;
            g_card_slots[chan].last_result = kCardResultReady;
            card_save_vdir_locked(static_cast<uint32_t>(chan));
        }
    }
    ctx.r[3] = static_cast<uint32_t>(res);
    if (res == kCardResultReady && cb_va != 0u) {
        invoke_card_callback_now(cb_va, chan, res, ctx, mem);
    }
}

static void hle_CARDOpen(PPCContext& ctx, Memory& mem, bool by_fileno) {
    const int32_t  chan  = static_cast<int32_t>(ctx.r[3]);
    const uint32_t fi_va = ctx.r[5];
    int32_t res = kCardResultNoFile;
    {
        std::lock_guard<std::mutex> lk(g_card_mtx);
        res = card_validate_channel(chan, true);
        if (res == kCardResultReady) {
            int32_t file_no = -1;
            if (by_fileno) {
                file_no = static_cast<int32_t>(ctx.r[4]);
            } else if (ctx.r[4] >= kGcRamBase && mem.is_valid_range(ctx.r[4], 1u)) {
                file_no = card_find_file_locked(static_cast<uint32_t>(chan), mem.read_cstring(ctx.r[4], 32u));
            }
            if (file_no >= 0 && static_cast<uint32_t>(file_no) < kCardMaxFiles && g_card_slots[0].files[file_no].in_use) {
                card_fill_file_info(mem, fi_va, chan, file_no, g_card_slots[0].files[file_no].length);
                res = kCardResultReady;
            } else {
                res = kCardResultNoFile;
            }
            g_card_slots[chan].last_result = res;
        }
    }
    ctx.r[3] = static_cast<uint32_t>(res);
}

static void hle_CARDCreate(PPCContext& ctx, Memory& mem, bool is_async) {
    const int32_t  chan    = static_cast<int32_t>(ctx.r[3]);
    const uint32_t name_va = ctx.r[4];
    const uint32_t size    = ctx.r[5];
    const uint32_t fi_va   = ctx.r[6];
    const uint32_t cb_va   = is_async ? ctx.r[7] : 0u;
    int32_t res = kCardResultNoCard;
    {
        std::lock_guard<std::mutex> lk(g_card_mtx);
        res = card_validate_channel(chan, true);
        if (res == kCardResultReady) {
            const std::string name = (name_va >= kGcRamBase && mem.is_valid_range(name_va, 1u))
                                         ? mem.read_cstring(name_va, 32u)
                                         : std::string();
            if (name.empty() || size == 0u || size > kCardTotalBlocks * kCardSectorSize) {
                res = kCardResultFatal;
            } else if (card_find_file_locked(0u, name) >= 0) {
                res = kCardResultExist;
            } else {
                int32_t free_idx = -1;
                for (uint32_t i = 0; i < kCardMaxFiles; ++i) {
                    if (!g_card_slots[0].files[i].in_use) {
                        free_idx = static_cast<int32_t>(i);
                        break;
                    }
                }
                if (free_idx < 0) {
                    res = kCardResultNoEnt;
                } else {
                    auto& entry = g_card_slots[0].files[free_idx];
                    entry = VirtualCardFile{};
                    entry.in_use      = true;
                    entry.file_name   = name;
                    entry.length      = size;
                    entry.offset_data = 0u;
                    entry.data.assign(size, 0u);
                    card_fill_file_info(mem, fi_va, chan, free_idx, size);
                    card_save_vdir_locked(0u);
                    res = kCardResultReady;
                }
            }
            g_card_slots[chan].last_result = res;
        }
    }
    ctx.r[3] = static_cast<uint32_t>(res);
    if (res == kCardResultReady && cb_va != 0u) {
        invoke_card_callback_now(cb_va, chan, res, ctx, mem);
    }
}

static void hle_CARDClose(PPCContext& ctx, Memory& mem) {
    const uint32_t fi_va = ctx.r[3];
    if (fi_va >= kGcRamBase && mem.is_valid_range(fi_va, 20u)) {
        mem.write_u16(fi_va + 16u, 0xFFFFu);
    }
    ctx.r[3] = static_cast<uint32_t>(kCardResultReady);
}

static void hle_CARDDelete(PPCContext& ctx, Memory& mem, bool by_fileno, bool is_async) {
    const int32_t  chan  = static_cast<int32_t>(ctx.r[3]);
    const uint32_t cb_va = is_async ? ctx.r[5] : 0u;
    int32_t res = kCardResultNoCard;
    {
        std::lock_guard<std::mutex> lk(g_card_mtx);
        res = card_validate_channel(chan, true);
        if (res == kCardResultReady) {
            int32_t file_no = -1;
            if (by_fileno) {
                file_no = static_cast<int32_t>(ctx.r[4]);
            } else if (ctx.r[4] >= kGcRamBase && mem.is_valid_range(ctx.r[4], 1u)) {
                file_no = card_find_file_locked(0u, mem.read_cstring(ctx.r[4], 32u));
            }
            if (file_no >= 0 && static_cast<uint32_t>(file_no) < kCardMaxFiles && g_card_slots[0].files[file_no].in_use) {
                g_card_slots[0].files[file_no] = VirtualCardFile{};
                card_save_vdir_locked(0u);
                res = kCardResultReady;
            } else {
                res = kCardResultNoFile;
            }
            g_card_slots[chan].last_result = res;
        }
    }
    ctx.r[3] = static_cast<uint32_t>(res);
    if (res == kCardResultReady && cb_va != 0u) {
        invoke_card_callback_now(cb_va, chan, res, ctx, mem);
    }
}

static void hle_CARDWrite(PPCContext& ctx, Memory& mem, bool is_async) {
    const uint32_t fi_va     = ctx.r[3];
    const uint32_t buf_vaddr = ctx.r[4];
    const uint32_t length    = ctx.r[5];
    const uint32_t offset    = ctx.r[6];
    const uint32_t cb_va     = is_async ? ctx.r[7] : 0u;
    int32_t cb_chan = 0;
    int32_t res = kCardResultReady;
    {
        std::lock_guard<std::mutex> lk(g_card_mtx);
        card_ensure_slot_locked(0u);
        const bool fi_valid = (fi_va >= kGcRamBase && mem.is_valid_range(fi_va, 20u));
        const uint16_t magic = fi_valid ? mem.read_u16(fi_va + 16u) : 0u;
        if (magic == kCardOpenMagic) {
            const int32_t chan    = static_cast<int32_t>(mem.read_u32(fi_va + 0u));
            const int32_t file_no = static_cast<int32_t>(mem.read_u32(fi_va + 4u));
            cb_chan = chan;
            if (chan != 0 || file_no < 0 || static_cast<uint32_t>(file_no) >= kCardMaxFiles ||
                !g_card_slots[0].files[file_no].in_use) {
                res = kCardResultNoFile;
            } else if (!mem.is_valid_range(buf_vaddr, length) || length > 0x200000u) {
                res = kCardResultFatal;
            } else {
                auto& entry = g_card_slots[0].files[file_no];
                if (offset + length > entry.data.size()) {
                    entry.data.resize(offset + length, 0u);
                    entry.length = static_cast<uint32_t>(entry.data.size());
                }
                if (length > 0u) {
                    std::memcpy(entry.data.data() + offset, mem.raw_ptr(buf_vaddr), length);
                }
                g_card_slots[0].last_xfer_bytes = length;
                card_save_vdir_locked(0u);
                res = kCardResultReady;
            }
            g_card_slots[0].last_result = res;
        } else {
            // Backward-compatible direct raw-card fallback when CARDWriteAsync is called on un-opened CARDFileInfo
            if (mem.is_valid_range(buf_vaddr, length) && length > 0u && length <= 0x200000u) {
                const std::string spath = get_card_save_path();
                std::fstream f(spath, std::ios::in | std::ios::out | std::ios::binary);
                if (!f.is_open()) {
                    f.open(spath, std::ios::out | std::ios::binary);
                }
                if (f.is_open()) {
                    f.seekp(offset, std::ios::beg);
                    f.write(reinterpret_cast<const char*>(mem.raw_ptr(buf_vaddr)), length);
                }
            }
            g_card_slots[0].last_xfer_bytes = length;
            g_card_slots[0].last_result     = kCardResultReady;
        }
    }
    ctx.r[3] = static_cast<uint32_t>(res);
    if (res == kCardResultReady && cb_va != 0u) {
        invoke_card_callback_now(cb_va, cb_chan, res, ctx, mem);
    }
}

static void hle_CARDRead(PPCContext& ctx, Memory& mem, bool is_async) {
    const uint32_t fi_va     = ctx.r[3];
    const uint32_t buf_vaddr = ctx.r[4];
    const uint32_t length    = ctx.r[5];
    const uint32_t offset    = ctx.r[6];
    const uint32_t cb_va     = is_async ? ctx.r[7] : 0u;
    int32_t cb_chan = 0;
    int32_t res = kCardResultReady;
    {
        std::lock_guard<std::mutex> lk(g_card_mtx);
        card_ensure_slot_locked(0u);
        const bool fi_valid = (fi_va >= kGcRamBase && mem.is_valid_range(fi_va, 20u));
        const uint16_t magic = fi_valid ? mem.read_u16(fi_va + 16u) : 0u;
        if (magic == kCardOpenMagic) {
            const int32_t chan    = static_cast<int32_t>(mem.read_u32(fi_va + 0u));
            const int32_t file_no = static_cast<int32_t>(mem.read_u32(fi_va + 4u));
            cb_chan = chan;
            if (chan != 0 || file_no < 0 || static_cast<uint32_t>(file_no) >= kCardMaxFiles ||
                !g_card_slots[0].files[file_no].in_use) {
                res = kCardResultNoFile;
            } else if (!mem.is_valid_range(buf_vaddr, length)) {
                res = kCardResultFatal;
            } else {
                const auto& entry = g_card_slots[0].files[file_no];
                if (length > 0u) {
                    std::memset(mem.raw_ptr(buf_vaddr), 0, length);
                    if (offset < entry.data.size()) {
                        const size_t avail = (std::min)(static_cast<size_t>(length), entry.data.size() - offset);
                        mem.write_bytes(buf_vaddr, entry.data.data() + offset, avail);
                    }
                }
                g_card_slots[0].last_xfer_bytes = length;
                res = kCardResultReady;
            }
            g_card_slots[0].last_result = res;
        } else {
            const std::string spath = get_card_save_path();
            if (mem.is_valid_range(buf_vaddr, length) && length > 0u && fs::exists(spath)) {
                std::ifstream f(spath, std::ios::binary);
                f.seekg(offset, std::ios::beg);
                f.read(reinterpret_cast<char*>(mem.raw_ptr(buf_vaddr)), length);
            }
            g_card_slots[0].last_xfer_bytes = length;
            g_card_slots[0].last_result     = kCardResultReady;
        }
    }
    ctx.r[3] = static_cast<uint32_t>(res);
    if (res == kCardResultReady && cb_va != 0u) {
        invoke_card_callback_now(cb_va, cb_chan, res, ctx, mem);
    }
}

static void hle_CARDGetStatus(PPCContext& ctx, Memory& mem) {
    const int32_t  chan    = static_cast<int32_t>(ctx.r[3]);
    const int32_t  file_no = static_cast<int32_t>(ctx.r[4]);
    const uint32_t stat_va = ctx.r[5];
    std::lock_guard<std::mutex> lk(g_card_mtx);
    int32_t res = card_validate_channel(chan, true);
    if (res == kCardResultReady) {
        if (file_no < 0 || static_cast<uint32_t>(file_no) >= kCardMaxFiles || !g_card_slots[0].files[file_no].in_use) {
            res = kCardResultNoFile;
        } else if (stat_va >= kGcRamBase && mem.is_valid_range(stat_va, 0x6Cu)) {
            const auto& entry = g_card_slots[0].files[file_no];
            std::memset(mem.raw_ptr(stat_va), 0, 0x6Cu);
            const size_t nlen = (std::min)(entry.file_name.size(), size_t(31));
            if (nlen > 0u) mem.write_bytes(stat_va + 0x00u, entry.file_name.data(), nlen);
            mem.write_u32(stat_va + 0x20u, entry.length);
            mem.write_u32(stat_va + 0x24u, entry.time_sec);
            mem.write_bytes(stat_va + 0x28u, entry.game_code, 4u);
            mem.write_bytes(stat_va + 0x2Cu, entry.company, 2u);
            mem.write_u8(stat_va + 0x2Eu, entry.banner_format);
            mem.write_u32(stat_va + 0x30u, entry.icon_addr);
            mem.write_u16(stat_va + 0x34u, entry.icon_format);
            mem.write_u16(stat_va + 0x36u, entry.icon_speed);
            mem.write_u32(stat_va + 0x38u, entry.comment_addr);
            mem.write_u32(stat_va + 0x3Cu, entry.offset_banner);
            mem.write_u32(stat_va + 0x40u, entry.offset_banner_tlut);
            for (int i = 0; i < 8; ++i) {
                mem.write_u32(stat_va + 0x44u + static_cast<uint32_t>(i * 4), entry.offset_icon[i]);
            }
            mem.write_u32(stat_va + 0x64u, entry.offset_icon_tlut);
            mem.write_u32(stat_va + 0x68u, entry.offset_data);
            res = kCardResultReady;
        } else {
            res = kCardResultFatal;
        }
        g_card_slots[chan].last_result = res;
    }
    ctx.r[3] = static_cast<uint32_t>(res);
}

static void hle_CARDSetStatus(PPCContext& ctx, Memory& mem, bool is_async) {
    const int32_t  chan    = static_cast<int32_t>(ctx.r[3]);
    const int32_t  file_no = static_cast<int32_t>(ctx.r[4]);
    const uint32_t stat_va = ctx.r[5];
    const uint32_t cb_va   = is_async ? ctx.r[6] : 0u;
    int32_t res = kCardResultNoCard;
    {
        std::lock_guard<std::mutex> lk(g_card_mtx);
        res = card_validate_channel(chan, true);
        if (res == kCardResultReady) {
            if (file_no < 0 || static_cast<uint32_t>(file_no) >= kCardMaxFiles || !g_card_slots[0].files[file_no].in_use) {
                res = kCardResultNoFile;
            } else if (stat_va >= kGcRamBase && mem.is_valid_range(stat_va, 0x3Cu)) {
                auto& entry = g_card_slots[0].files[file_no];
                const std::string new_name = mem.read_cstring(stat_va + 0x00u, 32u);
                if (!new_name.empty()) entry.file_name = new_name;
                entry.time_sec      = mem.read_u32(stat_va + 0x24u);
                entry.banner_format = mem.read_u8(stat_va + 0x2Eu);
                entry.icon_addr     = mem.read_u32(stat_va + 0x30u);
                entry.icon_format   = mem.read_u16(stat_va + 0x34u);
                entry.icon_speed    = mem.read_u16(stat_va + 0x36u);
                entry.comment_addr  = mem.read_u32(stat_va + 0x38u);
                card_save_vdir_locked(0u);
                res = kCardResultReady;
            } else {
                res = kCardResultFatal;
            }
            g_card_slots[chan].last_result = res;
        }
    }
    ctx.r[3] = static_cast<uint32_t>(res);
    if (res == kCardResultReady && cb_va != 0u) {
        invoke_card_callback_now(cb_va, chan, res, ctx, mem);
    }
}

static void hle_OSTicksToCalendarTime(PPCContext& ctx, Memory& mem) {
    const uint64_t ticks = (static_cast<uint64_t>(ctx.r[3]) << 32) | static_cast<uint64_t>(ctx.r[4]);
    const uint32_t td_va = ctx.r[5];
    if (td_va < kGcRamBase || !mem.is_valid_range(td_va, 40u)) return;

    uint32_t bus_clock = mem.read_u32(0x800000F8u);
    if (bus_clock == 0u) bus_clock = 162000000u;
    const uint64_t ticks_per_sec = static_cast<uint64_t>(bus_clock) / 4ull;
    const uint64_t sec_since_2000 = ticks / ticks_per_sec;
    const uint64_t rem_ticks      = ticks % ticks_per_sec;
    const uint32_t usec_total     = static_cast<uint32_t>((rem_ticks * 1000000ull) / ticks_per_sec);

    constexpr int64_t kGcEpochUnixSec = 946684800LL; // 2000-01-01 00:00:00 UTC
    const int64_t unix_sec = kGcEpochUnixSec + static_cast<int64_t>(sec_since_2000);
    std::tm tm_utc{};
#ifdef _WIN32
    const __time64_t t64 = static_cast<__time64_t>(unix_sec);
    _gmtime64_s(&tm_utc, &t64);
#else
    const time_t tt = static_cast<time_t>(unix_sec);
    gmtime_r(&tt, &tm_utc);
#endif
    mem.write_u32(td_va + 0u,  static_cast<uint32_t>(tm_utc.tm_sec));
    mem.write_u32(td_va + 4u,  static_cast<uint32_t>(tm_utc.tm_min));
    mem.write_u32(td_va + 8u,  static_cast<uint32_t>(tm_utc.tm_hour));
    mem.write_u32(td_va + 12u, static_cast<uint32_t>(tm_utc.tm_mday));
    mem.write_u32(td_va + 16u, static_cast<uint32_t>(tm_utc.tm_mon));
    mem.write_u32(td_va + 20u, static_cast<uint32_t>(tm_utc.tm_year + 1900));
    mem.write_u32(td_va + 24u, static_cast<uint32_t>(tm_utc.tm_wday));
    mem.write_u32(td_va + 28u, static_cast<uint32_t>(tm_utc.tm_yday));
    mem.write_u32(td_va + 32u, usec_total / 1000u);
    mem.write_u32(td_va + 36u, usec_total % 1000u);
}

static void hle_OSCalendarTimeToTicks(PPCContext& ctx, Memory& mem) {
    const uint32_t td_va = ctx.r[3];
    if (td_va < kGcRamBase || !mem.is_valid_range(td_va, 40u)) {
        ctx.r[3] = 0u;
        ctx.r[4] = 0u;
        return;
    }
    std::tm tm_utc{};
    tm_utc.tm_sec  = static_cast<int>(mem.read_u32(td_va + 0u));
    tm_utc.tm_min  = static_cast<int>(mem.read_u32(td_va + 4u));
    tm_utc.tm_hour = static_cast<int>(mem.read_u32(td_va + 8u));
    tm_utc.tm_mday = static_cast<int>(mem.read_u32(td_va + 12u));
    tm_utc.tm_mon  = static_cast<int>(mem.read_u32(td_va + 16u));
    tm_utc.tm_year = static_cast<int>(mem.read_u32(td_va + 20u)) - 1900;
    const uint32_t msec = mem.read_u32(td_va + 32u);
    const uint32_t usec = mem.read_u32(td_va + 36u);
#ifdef _WIN32
    const int64_t unix_sec = static_cast<int64_t>(_mkgmtime64(&tm_utc));
#else
    const int64_t unix_sec = static_cast<int64_t>(timegm(&tm_utc));
#endif
    constexpr int64_t kGcEpochUnixSec = 946684800LL;
    uint32_t bus_clock = mem.read_u32(0x800000F8u);
    if (bus_clock == 0u) bus_clock = 162000000u;
    const uint64_t ticks_per_sec = static_cast<uint64_t>(bus_clock) / 4ull;
    const uint64_t sec_since_2000 = (unix_sec > kGcEpochUnixSec) ? static_cast<uint64_t>(unix_sec - kGcEpochUnixSec) : 0ull;
    const uint64_t sub_us = static_cast<uint64_t>(msec) * 1000ull + static_cast<uint64_t>(usec);
    const uint64_t total_ticks = sec_since_2000 * ticks_per_sec + (sub_us * ticks_per_sec) / 1000000ull;
    ctx.r[3] = static_cast<uint32_t>(total_ticks >> 32);
    ctx.r[4] = static_cast<uint32_t>(total_ticks & 0xFFFFFFFFull);
}

static void hle_PADRead(PPCContext& ctx, Memory& mem) {
    uint32_t dst_va = ctx.r[3];
    if (auto* pad = PadXInputBridge::active_instance()) {
        pad->write_pad_status_to_addr(mem, dst_va);
    } else if (mem.is_valid_range(dst_va, 48u) && mem.is_valid_range(recomp::sym_addr::kPadData, 48u)) {
        std::memcpy(mem.raw_ptr(dst_va), mem.raw_ptr(recomp::sym_addr::kPadData), 48u);
    }
    ctx.r[3] = 0x80000000u;
}

static void hle_PADControlMotor(PPCContext& ctx, Memory& mem) {
    (void)mem;
    if (ctx.r[3] == 0u) {
        if (auto* pad = PadXInputBridge::active_instance()) {
            pad->set_rumble(ctx.r[4], 1.0f);
        }
    }
}

static void hle_memcpy(PPCContext& ctx, Memory& mem) {
    uint32_t dst = ctx.r[3], src = ctx.r[4], len = ctx.r[5];
    if (len > 0 && mem.is_valid_range(dst, len) && mem.is_valid_range(src, len)) {
        std::memcpy(mem.raw_ptr(dst), mem.raw_ptr(src), len);
    }
}

static void hle_memmove(PPCContext& ctx, Memory& mem) {
    uint32_t dst = ctx.r[3], src = ctx.r[4], len = ctx.r[5];
    if (len > 0 && mem.is_valid_range(dst, len) && mem.is_valid_range(src, len)) {
        std::memmove(mem.raw_ptr(dst), mem.raw_ptr(src), len);
    }
}

static void hle_memset(PPCContext& ctx, Memory& mem) {
    uint32_t dst = ctx.r[3], val = ctx.r[4] & 0xFFu, len = ctx.r[5];
    if (len > 0 && mem.is_valid_range(dst, len)) {
        std::memset(mem.raw_ptr(dst), static_cast<int>(val), len);
    }
}

static void hle_strlen(PPCContext& ctx, Memory& mem) {
    std::string s = mem.read_cstring(ctx.r[3], 4096);
    ctx.r[3] = static_cast<uint32_t>(s.size());
}

static void hle_strcpy(PPCContext& ctx, Memory& mem) {
    uint32_t dst = ctx.r[3];
    std::string s = mem.read_cstring(ctx.r[4], 4096);
    if (mem.is_valid_range(dst, s.size() + 1u)) {
        mem.write_bytes(dst, s.c_str(), s.size() + 1u);
    }
}

static void hle_strcat(PPCContext& ctx, Memory& mem) {
    uint32_t dst = ctx.r[3];
    std::string d = mem.read_cstring(dst, 4096);
    std::string s = mem.read_cstring(ctx.r[4], 4096);
    uint32_t write_va = dst + static_cast<uint32_t>(d.size());
    if (mem.is_valid_range(write_va, s.size() + 1u)) {
        mem.write_bytes(write_va, s.c_str(), s.size() + 1u);
    }
}

static void hle_strcmp(PPCContext& ctx, Memory& mem) {
    std::string a = mem.read_cstring(ctx.r[3], 4096);
    std::string b = mem.read_cstring(ctx.r[4], 4096);
    ctx.r[3] = static_cast<uint32_t>(std::strcmp(a.c_str(), b.c_str()));
}

static void hle_strncmp(PPCContext& ctx, Memory& mem) {
    std::string a = mem.read_cstring(ctx.r[3], 4096);
    std::string b = mem.read_cstring(ctx.r[4], 4096);
    ctx.r[3] = static_cast<uint32_t>(std::strncmp(a.c_str(), b.c_str(), ctx.r[5]));
}

static void hle_strchr(PPCContext& ctx, Memory& mem) {
    uint32_t str_va = ctx.r[3];
    char target = static_cast<char>(ctx.r[4] & 0xFFu);
    std::string s = mem.read_cstring(str_va, 4096);
    const char* p = std::strchr(s.c_str(), target);
    ctx.r[3] = p ? (str_va + static_cast<uint32_t>(p - s.c_str())) : 0u;
}

static void hle_strrchr(PPCContext& ctx, Memory& mem) {
    uint32_t str_va = ctx.r[3];
    char target = static_cast<char>(ctx.r[4] & 0xFFu);
    std::string s = mem.read_cstring(str_va, 4096);
    const char* p = std::strrchr(s.c_str(), target);
    ctx.r[3] = p ? (str_va + static_cast<uint32_t>(p - s.c_str())) : 0u;
}

struct PpcVaReader {
    PPCContext& ctx;
    Memory& mem;
    bool from_va_list = false;
    uint32_t gpr_idx = 0; // 0..7 -> r3..r10
    uint32_t fpr_idx = 0; // 0..7 -> f1..f8
    uint32_t overflow_va = 0;
    uint32_t reg_save_va = 0;

    static PpcVaReader direct(PPCContext& c, Memory& m, uint32_t first_gpr) {
        PpcVaReader r{c, m, false, first_gpr - 3u, 0u, c.r[1] + 8u, 0u};
        return r;
    }

    static PpcVaReader from_valist(PPCContext& c, Memory& m, uint32_t va_addr) {
        PpcVaReader r{c, m, true, 0u, 0u, 0u, 0u};
        if (m.is_valid_range(va_addr, 12u)) {
            r.gpr_idx     = m.read_u8(va_addr);
            r.fpr_idx     = m.read_u8(va_addr + 1u);
            r.overflow_va = m.read_u32(va_addr + 4u);
            r.reg_save_va = m.read_u32(va_addr + 8u);
        }
        return r;
    }

    uint32_t next_u32() {
        if (from_va_list) {
            if (gpr_idx < 8u && reg_save_va != 0u) {
                return mem.read_u32(reg_save_va + 4u * (gpr_idx++));
            }
            if (overflow_va != 0u) {
                uint32_t v = mem.read_u32(overflow_va);
                overflow_va += 4u;
                return v;
            }
            return 0u;
        }
        if (gpr_idx < 8u) {
            return ctx.r[3u + (gpr_idx++)];
        }
        uint32_t v = mem.read_u32(overflow_va);
        overflow_va += 4u;
        return v;
    }

    double next_f64() {
        if (from_va_list) {
            if (fpr_idx < 8u && reg_save_va != 0u) {
                return mem.read_f64(reg_save_va + 32u + 8u * (fpr_idx++));
            }
            if (overflow_va != 0u) {
                overflow_va = (overflow_va + 7u) & ~7u;
                double v = mem.read_f64(overflow_va);
                overflow_va += 8u;
                return v;
            }
            return 0.0;
        }
        if (fpr_idx < 8u) {
            return ctx.f[1u + (fpr_idx++)];
        }
        overflow_va = (overflow_va + 7u) & ~7u;
        double v = mem.read_f64(overflow_va);
        overflow_va += 8u;
        return v;
    }
};

static std::string hle_format_string(Memory& mem, uint32_t fmt_va, PpcVaReader& va) {
    std::string fmt = mem.read_cstring(fmt_va, 2048);
    std::string out;
    out.reserve(fmt.size() + 32);
    for (size_t i = 0; i < fmt.size(); ++i) {
        if (fmt[i] != '%' || i + 1 >= fmt.size()) {
            out.push_back(fmt[i]);
            continue;
        }
        ++i;
        if (fmt[i] == '%') {
            out.push_back('%');
            continue;
        }
        std::string sub_fmt = "%";
        while (i < fmt.size() && (fmt[i] == '-' || fmt[i] == '+' || fmt[i] == ' ' || fmt[i] == '#' || fmt[i] == '0')) {
            sub_fmt.push_back(fmt[i++]);
        }
        if (i < fmt.size() && fmt[i] == '*') {
            sub_fmt += std::to_string(static_cast<int32_t>(va.next_u32()));
            ++i;
        } else {
            while (i < fmt.size() && std::isdigit(static_cast<unsigned char>(fmt[i]))) {
                sub_fmt.push_back(fmt[i++]);
            }
        }
        if (i < fmt.size() && fmt[i] == '.') {
            sub_fmt.push_back('.');
            ++i;
            if (i < fmt.size() && fmt[i] == '*') {
                sub_fmt += std::to_string(static_cast<int32_t>(va.next_u32()));
                ++i;
            } else {
                while (i < fmt.size() && std::isdigit(static_cast<unsigned char>(fmt[i]))) {
                    sub_fmt.push_back(fmt[i++]);
                }
            }
        }
        while (i < fmt.size() && (fmt[i] == 'l' || fmt[i] == 'h' || fmt[i] == 'z')) {
            ++i;
        }
        if (i >= fmt.size()) break;
        char spec = fmt[i];
        sub_fmt.push_back(spec);
        char buf[1024]{};
        if (spec == 's') {
            uint32_t str_va = va.next_u32();
            std::string str_val = (str_va != 0u) ? mem.read_cstring(str_va, 1024) : "(null)";
            int n = std::snprintf(buf, sizeof(buf), sub_fmt.c_str(), str_val.c_str());
            if (n > 0) {
                out.append(buf, static_cast<size_t>(std::min<int>(n, static_cast<int>(sizeof(buf) - 1))));
            }
        } else if (spec == 'd' || spec == 'i') {
            int32_t val = static_cast<int32_t>(va.next_u32());
            int n = std::snprintf(buf, sizeof(buf), sub_fmt.c_str(), val);
            if (n > 0) out.append(buf, static_cast<size_t>(std::min<int>(n, static_cast<int>(sizeof(buf) - 1))));
        } else if (spec == 'u' || spec == 'x' || spec == 'X' || spec == 'o') {
            uint32_t val = va.next_u32();
            int n = std::snprintf(buf, sizeof(buf), sub_fmt.c_str(), val);
            if (n > 0) out.append(buf, static_cast<size_t>(std::min<int>(n, static_cast<int>(sizeof(buf) - 1))));
        } else if (spec == 'p') {
            uint32_t val = va.next_u32();
            std::snprintf(buf, sizeof(buf), "0x%08X", val);
            out += buf;
        } else if (spec == 'c') {
            int val = static_cast<int>(va.next_u32() & 0xFFu);
            int n = std::snprintf(buf, sizeof(buf), sub_fmt.c_str(), val);
            if (n > 0) out.append(buf, static_cast<size_t>(std::min<int>(n, static_cast<int>(sizeof(buf) - 1))));
        } else if (spec == 'f' || spec == 'F' || spec == 'e' || spec == 'E' || spec == 'g' || spec == 'G') {
            double val = va.next_f64();
            int n = std::snprintf(buf, sizeof(buf), sub_fmt.c_str(), val);
            if (n > 0) out.append(buf, static_cast<size_t>(std::min<int>(n, static_cast<int>(sizeof(buf) - 1))));
        } else if (spec == 'n') {
            uint32_t ptr_va = va.next_u32();
            if (ptr_va != 0u) mem.write_u32(ptr_va, static_cast<uint32_t>(out.size()));
        } else {
            out.push_back(spec);
        }
    }
    return out;
}

static void hle_write_formatted_dst(Memory& mem, uint32_t dst_va, const std::string& out, uint32_t max_len, PPCContext& ctx) {
    if (max_len > 0u && dst_va != 0u) {
        size_t copy_len = std::min<size_t>(out.size(), static_cast<size_t>(max_len - 1u));
        if (mem.is_valid_range(dst_va, copy_len + 1u)) {
            if (copy_len > 0u) mem.write_bytes(dst_va, out.data(), copy_len);
            mem.write_u8(dst_va + static_cast<uint32_t>(copy_len), 0u);
        }
    }
    ctx.r[3] = static_cast<uint32_t>(out.size());
}

static void hle_sprintf(PPCContext& ctx, Memory& mem) {
    auto va = PpcVaReader::direct(ctx, mem, 5u);
    std::string out = hle_format_string(mem, ctx.r[4], va);
    hle_write_formatted_dst(mem, ctx.r[3], out, 0x7FFFFFFFu, ctx);
}

static void hle_sprintf_r(PPCContext& ctx, Memory& mem) {
    auto va = PpcVaReader::direct(ctx, mem, 6u);
    std::string out = hle_format_string(mem, ctx.r[5], va);
    hle_write_formatted_dst(mem, ctx.r[4], out, 0x7FFFFFFFu, ctx);
}

static void hle_vsprintf(PPCContext& ctx, Memory& mem) {
    auto va = PpcVaReader::from_valist(ctx, mem, ctx.r[5]);
    std::string out = hle_format_string(mem, ctx.r[4], va);
    hle_write_formatted_dst(mem, ctx.r[3], out, 0x7FFFFFFFu, ctx);
}

static void hle_vsnprintf(PPCContext& ctx, Memory& mem) {
    auto va = PpcVaReader::from_valist(ctx, mem, ctx.r[6]);
    std::string out = hle_format_string(mem, ctx.r[5], va);
    hle_write_formatted_dst(mem, ctx.r[3], out, ctx.r[4], ctx);
}

static void hle_OSReport(PPCContext& ctx, Memory& mem) {
    if (!g_hle_call_trace && !global_logger().should_log(LogLevel::Info)) return;
    auto va = PpcVaReader::direct(ctx, mem, 4u);
    std::string out = hle_format_string(mem, ctx.r[3], va);
    if (!out.empty() && out.back() == '\n') out.pop_back();
    PN03_LOG(LogLevel::Info, "OSReport", out);
    if (g_hle_call_trace) {
        std::fprintf(stderr, "[OSReport] %s\n", out.c_str());
        std::fflush(stderr);
    }
}

static void hle_OSPanic(PPCContext& ctx, Memory& mem) {
    std::string file = mem.read_cstring(ctx.r[3], 256);
    int32_t line = static_cast<int32_t>(ctx.r[4]);
    auto va = PpcVaReader::direct(ctx, mem, 6u);
    std::string msg = hle_format_string(mem, ctx.r[5], va);
    if (!msg.empty() && msg.back() == '\n') msg.pop_back();
    PN03_LOGF(LogLevel::Error, "OSPanic", "%s:%d: %s", file.c_str(), line, msg.c_str());
    if (g_hle_call_trace) {
        std::fprintf(stderr, "[OSPanic] %s:%d: %s\n", file.c_str(), line, msg.c_str());
        std::fflush(stderr);
    }
}

static inline void set_fp_return(PPCContext& ctx, double v) {
    ctx.f[1]   = v;
    ctx.ps0[1] = static_cast<float>(v);
    ctx.ps1[1] = static_cast<float>(v);
}

// Additional verified Dolphin MTX / VEC / QUAT / Cache / Stdlib HLE helpers
static void hle_DCZeroRange(PPCContext& ctx, Memory& mem) {
    uint32_t addr = ctx.r[3] & ~31u;
    uint32_t len  = ctx.r[4];
    if (len > 0 && mem.is_valid_range(addr, len)) {
        std::memset(mem.raw_ptr(addr), 0, len);
    }
}

static void hle_PSMTXTranspose(PPCContext& ctx, Memory& mem) {
    float m[3][4]{};
    read_mtx34(mem, ctx.r[3], m);
    float out[3][4]{};
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            out[r][c] = m[c][r];
        }
        out[r][3] = 0.0f;
    }
    write_mtx34(mem, ctx.r[4], out);
}

static void hle_PSMTXInvXpose(PPCContext& ctx, Memory& mem) {
    // Inverse transpose of upper 3x3
    float m[3][4]{};
    read_mtx34(mem, ctx.r[3], m);
    float det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
                m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
                m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    if (std::fabs(det) < 1e-8f) {
        const float id[3][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0}};
        write_mtx34(mem, ctx.r[4], id);
        ctx.r[3] = 0u;
        return;
    }
    float idet = 1.0f / det;
    float out[3][4]{};
    out[0][0] =  (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * idet;
    out[1][0] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]) * idet;
    out[2][0] =  (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * idet;
    out[0][1] = -(m[1][0] * m[2][2] - m[1][2] * m[2][0]) * idet;
    out[1][1] =  (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * idet;
    out[2][1] = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]) * idet;
    out[0][2] =  (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * idet;
    out[1][2] = -(m[0][0] * m[2][1] - m[0][1] * m[2][0]) * idet;
    out[2][2] =  (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * idet;
    write_mtx34(mem, ctx.r[4], out);
    ctx.r[3] = 1u;
}

static void hle_PSMTXRotRad(PPCContext& ctx, Memory& mem) {
    char axis = static_cast<char>(ctx.r[4] & 0xFFu);
    float rad = static_cast<float>(ctx.f[1]);
    float s = std::sin(rad), c = std::cos(rad);
    float m[3][4] = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
    };
    if (axis == 'x' || axis == 'X') {
        m[1][1] = c; m[1][2] = -s; m[2][1] = s; m[2][2] = c;
    } else if (axis == 'y' || axis == 'Y') {
        m[0][0] = c; m[0][2] = s; m[2][0] = -s; m[2][2] = c;
    } else if (axis == 'z' || axis == 'Z') {
        m[0][0] = c; m[0][1] = -s; m[1][0] = s; m[1][1] = c;
    }
    write_mtx34(mem, ctx.r[3], m);
}

static void hle_PSMTXRotTrig(PPCContext& ctx, Memory& mem) {
    char axis = static_cast<char>(ctx.r[4] & 0xFFu);
    float s = static_cast<float>(ctx.f[1]);
    float c = static_cast<float>(ctx.f[2]);
    float m[3][4] = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
    };
    if (axis == 'x' || axis == 'X') {
        m[1][1] = c; m[1][2] = -s; m[2][1] = s; m[2][2] = c;
    } else if (axis == 'y' || axis == 'Y') {
        m[0][0] = c; m[0][2] = s; m[2][0] = -s; m[2][2] = c;
    } else if (axis == 'z' || axis == 'Z') {
        m[0][0] = c; m[0][1] = -s; m[1][0] = s; m[1][1] = c;
    }
    write_mtx34(mem, ctx.r[3], m);
}

static void hle_PSMTXRotAxisRad(PPCContext& ctx, Memory& mem) {
    float a[3]{};
    read_vec3(mem, ctx.r[4], a);
    float mag = std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    if (mag > 1e-8f) { a[0] /= mag; a[1] /= mag; a[2] /= mag; }
    float rad = static_cast<float>(ctx.f[1]);
    float s = std::sin(rad), c = std::cos(rad), t = 1.0f - c;
    float x = a[0], y = a[1], z = a[2];
    float m[3][4] = {
        {t * x * x + c,     t * x * y - s * z, t * x * z + s * y, 0.0f},
        {t * x * y + s * z, t * y * y + c,     t * y * z - s * x, 0.0f},
        {t * x * z - s * y, t * y * z + s * x, t * z * z + c,     0.0f},
    };
    write_mtx34(mem, ctx.r[3], m);
}

static void hle_PSMTXTransApply(PPCContext& ctx, Memory& mem) {
    float m[3][4]{};
    read_mtx34(mem, ctx.r[3], m);
    m[0][3] += static_cast<float>(ctx.f[1]);
    m[1][3] += static_cast<float>(ctx.f[2]);
    m[2][3] += static_cast<float>(ctx.f[3]);
    write_mtx34(mem, ctx.r[4], m);
}

static void hle_PSMTXScaleApply(PPCContext& ctx, Memory& mem) {
    float m[3][4]{};
    read_mtx34(mem, ctx.r[3], m);
    float sx = static_cast<float>(ctx.f[1]);
    float sy = static_cast<float>(ctx.f[2]);
    float sz = static_cast<float>(ctx.f[3]);
    for (int c = 0; c < 4; ++c) {
        m[0][c] *= sx;
        m[1][c] *= sy;
        m[2][c] *= sz;
    }
    write_mtx34(mem, ctx.r[4], m);
}

static void hle_PSMTXQuat(PPCContext& ctx, Memory& mem) {
    float x = mem.read_f32(ctx.r[4] + 0);
    float y = mem.read_f32(ctx.r[4] + 4);
    float z = mem.read_f32(ctx.r[4] + 8);
    float w = mem.read_f32(ctx.r[4] + 12);
    float s = 2.0f / std::max(1e-8f, x*x + y*y + z*z + w*w);
    float xs = x * s, ys = y * s, zs = z * s;
    float wx = w * xs, wy = w * ys, wz = w * zs;
    float xx = x * xs, xy = x * ys, xz = x * zs;
    float yy = y * ys, yz = y * zs, zz = z * zs;
    float m[3][4] = {
        {1.0f - (yy + zz), xy - wz, xz + wy, 0.0f},
        {xy + wz, 1.0f - (xx + zz), yz - wx, 0.0f},
        {xz - wy, yz + wx, 1.0f - (xx + yy), 0.0f},
    };
    write_mtx34(mem, ctx.r[3], m);
}

static void hle_C_MTXFrustum(PPCContext& ctx, Memory& mem) {
    float top = static_cast<float>(ctx.f[1]);
    float bot = static_cast<float>(ctx.f[2]);
    float lft = static_cast<float>(ctx.f[3]);
    float rgt = static_cast<float>(ctx.f[4]);
    float nr  = static_cast<float>(ctx.f[5]);
    float fr  = static_cast<float>(ctx.f[6]);
    float dx = (rgt - lft != 0.0f) ? (rgt - lft) : 1.0f;
    float dy = (top - bot != 0.0f) ? (top - bot) : 1.0f;
    float dz = (fr - nr != 0.0f)   ? (fr - nr)   : 1.0f;
    float m[4][4]{};
    m[0][0] = (2.0f * nr) / dx;
    m[0][2] = (rgt + lft) / dx;
    m[1][1] = (2.0f * nr) / dy;
    m[1][2] = (top + bot) / dy;
    m[2][2] = -nr / dz;
    m[2][3] = -(fr * nr) / dz;
    m[3][2] = -1.0f;
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            mem.write_f32(ctx.r[3] + static_cast<uint32_t>((r * 4 + c) * 4), m[r][c]);
}

static void hle_C_MTXOrthoExact(PPCContext& ctx, Memory& mem) {
    float top = static_cast<float>(ctx.f[1]);
    float bot = static_cast<float>(ctx.f[2]);
    float lft = static_cast<float>(ctx.f[3]);
    float rgt = static_cast<float>(ctx.f[4]);
    float nr  = static_cast<float>(ctx.f[5]);
    float fr  = static_cast<float>(ctx.f[6]);
    float dx = (rgt - lft != 0.0f) ? (rgt - lft) : 1.0f;
    float dy = (top - bot != 0.0f) ? (top - bot) : 1.0f;
    float dz = (fr - nr != 0.0f)   ? (fr - nr)   : 1.0f;
    float m[4][4]{};
    m[0][0] =  2.0f / dx;
    m[0][3] = -(rgt + lft) / dx;
    m[1][1] =  2.0f / dy;
    m[1][3] = -(top + bot) / dy;
    m[2][2] = -1.0f / dz;
    m[2][3] = -fr / dz;
    m[3][3] =  1.0f;
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            mem.write_f32(ctx.r[3] + static_cast<uint32_t>((r * 4 + c) * 4), m[r][c]);
}

static void hle_C_MTXPerspectiveExact(PPCContext& ctx, Memory& mem) {
    float fovy   = static_cast<float>(ctx.f[1]);
    float aspect = static_cast<float>(ctx.f[2]);
    float nr     = static_cast<float>(ctx.f[3]);
    float fr     = static_cast<float>(ctx.f[4]);
    constexpr float kDegToRad = 0.017453292519943295f;
    float half_rad = 0.5f * fovy * kDegToRad;
    float tan_half = std::tan(half_rad);
    float cot = (tan_half != 0.0f) ? (1.0f / tan_half) : 1.0f;
    float dz  = (fr - nr != 0.0f) ? (fr - nr) : 1.0f;
    float m[4][4]{};
    m[0][0] = cot / (aspect != 0.0f ? aspect : 1.0f);
    m[1][1] = cot;
    m[2][2] = -nr / dz;
    m[2][3] = -(fr * nr) / dz;
    m[3][2] = -1.0f;
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            mem.write_f32(ctx.r[3] + static_cast<uint32_t>((r * 4 + c) * 4), m[r][c]);
}

static void hle_PSVECSquareMag(PPCContext& ctx, Memory& mem) {
    float a[3]{};
    read_vec3(mem, ctx.r[3], a);
    double sq = static_cast<double>(a[0]) * a[0] + static_cast<double>(a[1]) * a[1] + static_cast<double>(a[2]) * a[2];
    ctx.f[1] = sq;
    ctx.ps0[1] = static_cast<float>(sq);
}

static void hle_PSVECSquareDistance(PPCContext& ctx, Memory& mem) {
    float a[3]{}, b[3]{};
    read_vec3(mem, ctx.r[3], a);
    read_vec3(mem, ctx.r[4], b);
    double dx = a[0] - b[0], dy = a[1] - b[1], dz = a[2] - b[2];
    double sq = dx * dx + dy * dy + dz * dz;
    ctx.f[1] = sq;
    ctx.ps0[1] = static_cast<float>(sq);
}

static void hle_memcmp(PPCContext& ctx, Memory& mem) {
    uint32_t a = ctx.r[3], b = ctx.r[4], n = ctx.r[5];
    if (n > 0 && mem.is_valid_range(a, n) && mem.is_valid_range(b, n)) {
        int r = std::memcmp(mem.raw_ptr(a), mem.raw_ptr(b), n);
        ctx.r[3] = static_cast<uint32_t>(static_cast<int32_t>(r));
    } else {
        ctx.r[3] = 0u;
    }
}

static void hle_strncpy(PPCContext& ctx, Memory& mem) {
    uint32_t dst = ctx.r[3], src = ctx.r[4], n = ctx.r[5];
    if (n > 0 && mem.is_valid_range(dst, n) && mem.is_valid_range(src, 1u)) {
        size_t i = 0;
        for (; i < n; ++i) {
            uint8_t ch = mem.read_u8(src + static_cast<uint32_t>(i));
            mem.write_u8(dst + static_cast<uint32_t>(i), ch);
            if (ch == 0) break;
        }
        for (; i < n; ++i) mem.write_u8(dst + static_cast<uint32_t>(i), 0u);
    }
}

// ---------------------------------------------------------------------------
// 5. OSFont (OSInitFont / OSLoadFont / OSGetFontTexture / OSGetFontWidth) HLE
// Generates an IPL-independent 256x128 GX_TF_I4 ANSI bitmap font sheet in GC RAM
// so Progressive Scan prompts and SDK diagnostics render legibly without a BootROM.
// ---------------------------------------------------------------------------
static uint32_t g_osfont_header_vaddr = 0u;
static uint32_t g_osfont_sheet_vaddr  = 0u;

static const uint8_t kOsFont8x8Basic[95][8] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 0x20 ' '
    {0x18,0x18,0x18,0x18,0x18,0x00,0x18,0x00}, // 0x21 '!'
    {0x6C,0x6C,0x24,0x00,0x00,0x00,0x00,0x00}, // 0x22 '"'
    {0x24,0x7E,0x24,0x24,0x7E,0x24,0x00,0x00}, // 0x23 '#'
    {0x18,0x3E,0x60,0x3C,0x06,0x7C,0x18,0x00}, // 0x24 '$'
    {0x62,0x64,0x08,0x10,0x26,0x46,0x00,0x00}, // 0x25 '%'
    {0x38,0x4C,0x38,0x76,0xCC,0xCC,0x76,0x00}, // 0x26 '&'
    {0x18,0x18,0x30,0x00,0x00,0x00,0x00,0x00}, // 0x27 '\''
    {0x0C,0x18,0x30,0x30,0x30,0x18,0x0C,0x00}, // 0x28 '('
    {0x30,0x18,0x0C,0x0C,0x0C,0x18,0x30,0x00}, // 0x29 ')'
    {0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00}, // 0x2A '*'
    {0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00}, // 0x2B '+'
    {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x30}, // 0x2C ','
    {0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00}, // 0x2D '-'
    {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00}, // 0x2E '.'
    {0x06,0x0C,0x18,0x30,0x60,0xC0,0x80,0x00}, // 0x2F '/'
    {0x3C,0x66,0x6E,0x76,0x66,0x66,0x3C,0x00}, // 0x30 '0'
    {0x18,0x38,0x18,0x18,0x18,0x18,0x7E,0x00}, // 0x31 '1'
    {0x3C,0x66,0x06,0x1C,0x30,0x60,0x7E,0x00}, // 0x32 '2'
    {0x3C,0x66,0x06,0x1C,0x06,0x66,0x3C,0x00}, // 0x33 '3'
    {0x0C,0x1C,0x3C,0x6C,0x7E,0x0C,0x0C,0x00}, // 0x34 '4'
    {0x7E,0x60,0x7C,0x06,0x06,0x66,0x3C,0x00}, // 0x35 '5'
    {0x3C,0x60,0x7C,0x66,0x66,0x66,0x3C,0x00}, // 0x36 '6'
    {0x7E,0x66,0x0C,0x18,0x18,0x18,0x18,0x00}, // 0x37 '7'
    {0x3C,0x66,0x66,0x3C,0x66,0x66,0x3C,0x00}, // 0x38 '8'
    {0x3C,0x66,0x66,0x3E,0x06,0x0C,0x38,0x00}, // 0x39 '9'
    {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00}, // 0x3A ':'
    {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x30}, // 0x3B ';'
    {0x0C,0x18,0x30,0x60,0x30,0x18,0x0C,0x00}, // 0x3C '<'
    {0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00}, // 0x3D '='
    {0x30,0x18,0x0C,0x06,0x0C,0x18,0x30,0x00}, // 0x3E '>'
    {0x3C,0x66,0x06,0x1C,0x18,0x00,0x18,0x00}, // 0x3F '?'
    {0x3C,0x66,0x6E,0x6E,0x60,0x62,0x3C,0x00}, // 0x40 '@'
    {0x18,0x3C,0x66,0x66,0x7E,0x66,0x66,0x00}, // 0x41 'A'
    {0x7C,0x66,0x66,0x7C,0x66,0x66,0x7C,0x00}, // 0x42 'B'
    {0x3C,0x66,0x60,0x60,0x60,0x66,0x3C,0x00}, // 0x43 'C'
    {0x78,0x6C,0x66,0x66,0x66,0x6C,0x78,0x00}, // 0x44 'D'
    {0x7E,0x60,0x60,0x7C,0x60,0x60,0x7E,0x00}, // 0x45 'E'
    {0x7E,0x60,0x60,0x7C,0x60,0x60,0x60,0x00}, // 0x46 'F'
    {0x3C,0x66,0x60,0x6E,0x66,0x66,0x3E,0x00}, // 0x47 'G'
    {0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0x00}, // 0x48 'H'
    {0x3C,0x18,0x18,0x18,0x18,0x18,0x3C,0x00}, // 0x49 'I'
    {0x1E,0x0C,0x0C,0x0C,0x6C,0x6C,0x38,0x00}, // 0x4A 'J'
    {0x66,0x6C,0x78,0x70,0x78,0x6C,0x66,0x00}, // 0x4B 'K'
    {0x60,0x60,0x60,0x60,0x60,0x60,0x7E,0x00}, // 0x4C 'L'
    {0xC6,0xEE,0xFE,0xD6,0xC6,0xC6,0xC6,0x00}, // 0x4D 'M'
    {0x66,0x76,0x7E,0x7E,0x6E,0x66,0x66,0x00}, // 0x4E 'N'
    {0x3C,0x66,0x66,0x66,0x66,0x66,0x3C,0x00}, // 0x4F 'O'
    {0x7C,0x66,0x66,0x7C,0x60,0x60,0x60,0x00}, // 0x50 'P'
    {0x3C,0x66,0x66,0x66,0x6A,0x6C,0x36,0x00}, // 0x51 'Q'
    {0x7C,0x66,0x66,0x7C,0x6C,0x66,0x66,0x00}, // 0x52 'R'
    {0x3C,0x66,0x60,0x3C,0x06,0x66,0x3C,0x00}, // 0x53 'S'
    {0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x00}, // 0x54 'T'
    {0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x00}, // 0x55 'U'
    {0x66,0x66,0x66,0x66,0x66,0x3C,0x18,0x00}, // 0x56 'V'
    {0xC6,0xC6,0xC6,0xD6,0xFE,0xEE,0xC6,0x00}, // 0x57 'W'
    {0x66,0x66,0x3C,0x18,0x3C,0x66,0x66,0x00}, // 0x58 'X'
    {0x66,0x66,0x66,0x3C,0x18,0x18,0x18,0x00}, // 0x59 'Y'
    {0x7E,0x06,0x0C,0x18,0x30,0x60,0x7E,0x00}, // 0x5A 'Z'
    {0x3C,0x30,0x30,0x30,0x30,0x30,0x3C,0x00}, // 0x5B '['
    {0xC0,0x60,0x30,0x18,0x0C,0x06,0x02,0x00}, // 0x5C '\\'
    {0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x00}, // 0x5D ']'
    {0x18,0x3C,0x66,0x00,0x00,0x00,0x00,0x00}, // 0x5E '^'
    {0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00}, // 0x5F '_'
    {0x30,0x18,0x0C,0x00,0x00,0x00,0x00,0x00}, // 0x60 '`'
    {0x00,0x00,0x3C,0x06,0x3E,0x66,0x3E,0x00}, // 0x61 'a'
    {0x60,0x60,0x7C,0x66,0x66,0x66,0x7C,0x00}, // 0x62 'b'
    {0x00,0x00,0x3C,0x66,0x60,0x66,0x3C,0x00}, // 0x63 'c'
    {0x06,0x06,0x3E,0x66,0x66,0x66,0x3E,0x00}, // 0x64 'd'
    {0x00,0x00,0x3C,0x66,0x7E,0x60,0x3C,0x00}, // 0x65 'e'
    {0x1C,0x30,0x7C,0x30,0x30,0x30,0x30,0x00}, // 0x66 'f'
    {0x00,0x00,0x3E,0x66,0x66,0x3E,0x06,0x3C}, // 0x67 'g'
    {0x60,0x60,0x7C,0x66,0x66,0x66,0x66,0x00}, // 0x68 'h'
    {0x18,0x00,0x38,0x18,0x18,0x18,0x3C,0x00}, // 0x69 'i'
    {0x0C,0x00,0x1C,0x0C,0x0C,0x6C,0x38,0x00}, // 0x6A 'j'
    {0x60,0x60,0x66,0x6C,0x78,0x6C,0x66,0x00}, // 0x6B 'k'
    {0x38,0x18,0x18,0x18,0x18,0x18,0x3C,0x00}, // 0x6C 'l'
    {0x00,0x00,0xCC,0xFE,0xD6,0xC6,0xC6,0x00}, // 0x6D 'm'
    {0x00,0x00,0x7C,0x66,0x66,0x66,0x66,0x00}, // 0x6E 'n'
    {0x00,0x00,0x3C,0x66,0x66,0x66,0x3C,0x00}, // 0x6F 'o'
    {0x00,0x00,0x7C,0x66,0x66,0x7C,0x60,0x60}, // 0x70 'p'
    {0x00,0x00,0x3E,0x66,0x66,0x3E,0x06,0x06}, // 0x71 'q'
    {0x00,0x00,0x7C,0x66,0x60,0x60,0x60,0x00}, // 0x72 'r'
    {0x00,0x00,0x3E,0x60,0x3C,0x06,0x7C,0x00}, // 0x73 's'
    {0x30,0x30,0x7C,0x30,0x30,0x36,0x1C,0x00}, // 0x74 't'
    {0x00,0x00,0x66,0x66,0x66,0x66,0x3E,0x00}, // 0x75 'u'
    {0x00,0x00,0x66,0x66,0x66,0x3C,0x18,0x00}, // 0x76 'v'
    {0x00,0x00,0xC6,0xC6,0xD6,0xFE,0x6C,0x00}, // 0x77 'w'
    {0x00,0x00,0x66,0x3C,0x18,0x3C,0x66,0x00}, // 0x78 'x'
    {0x00,0x00,0x66,0x66,0x66,0x3E,0x06,0x3C}, // 0x79 'y'
    {0x00,0x00,0x7E,0x0C,0x18,0x30,0x7E,0x00}, // 0x7A 'z'
    {0x0E,0x18,0x18,0x70,0x18,0x18,0x0E,0x00}, // 0x7B '{'
    {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00}, // 0x7C '|'
    {0x70,0x18,0x18,0x0E,0x18,0x18,0x70,0x00}, // 0x7D '}'
    {0x32,0x4C,0x00,0x00,0x00,0x00,0x00,0x00}  // 0x7E '~'
};

static inline void osfont_write_i4_pixel(Memory& mem, uint32_t sheet_base, uint32_t sheet_w,
                                         uint32_t px, uint32_t py, uint8_t i4) {
    uint32_t tile_x = px >> 3;
    uint32_t tile_y = py >> 3;
    uint32_t tiles_per_row = sheet_w >> 3;
    uint32_t in_x = px & 7u;
    uint32_t in_y = py & 7u;
    uint32_t byte_off = ((tile_y * tiles_per_row + tile_x) * 32u) + (in_y * 4u) + (in_x >> 1);
    uint8_t cur = mem.read_u8(sheet_base + byte_off);
    if ((in_x & 1u) == 0u) {
        cur = static_cast<uint8_t>((cur & 0x0Fu) | ((i4 & 0x0Fu) << 4));
    } else {
        cur = static_cast<uint8_t>((cur & 0xF0u) | (i4 & 0x0Fu));
    }
    mem.write_u8(sheet_base + byte_off, cur);
}

static bool osfont_build_in_ram(PPCContext& ctx, Memory& mem, uint32_t font_data_vaddr) {
    constexpr uint32_t kWidthTableOff   = 0x40u;
    constexpr uint32_t kSheetOff        = 0x200u;
    constexpr uint32_t kCellWidth       = 24u;
    constexpr uint32_t kCellHeight      = 16u;
    constexpr uint32_t kSheetWidth      = 16u * kCellWidth;                 // 384 px (tile-aligned /8)
    constexpr uint32_t kSheetHeight     = 8u * kCellHeight;                 // 128 px
    constexpr uint32_t kSheetBytes      = (kSheetWidth * kSheetHeight) / 2u; // 24576 bytes
    constexpr uint32_t kTotalBytes      = kSheetOff + kSheetBytes;          // 25088 bytes (< 0x10120)

    if (font_data_vaddr == 0u || !mem.is_valid_range(font_data_vaddr, kTotalBytes)) {
        return false;
    }

    // Clear header, width table, and I4 pixel sheet
    for (uint32_t i = 0; i < kTotalBytes; i += 4u) {
        mem.write_u32(font_data_vaddr + i, 0u);
    }

    const uint32_t sheet_vaddr = font_data_vaddr + kSheetOff;

    // Populate OSFontHeader (44 bytes, Big-Endian)
    mem.write_u16(font_data_vaddr + 0u,  0u);          // fontType = 0 (OS_FONT_ENCODE_ANSI)
    mem.write_u16(font_data_vaddr + 2u,  0x0020u);     // firstChar
    mem.write_u16(font_data_vaddr + 4u,  0x007Eu);     // lastChar
    mem.write_u16(font_data_vaddr + 6u,  0x003Fu);     // invalChar ('?')
    mem.write_u16(font_data_vaddr + 8u,  14u);         // ascent
    mem.write_u16(font_data_vaddr + 10u, 2u);          // descent
    mem.write_u16(font_data_vaddr + 12u, static_cast<uint16_t>(kCellWidth));
    mem.write_u16(font_data_vaddr + 14u, 20u);         // leading
    mem.write_u16(font_data_vaddr + 16u, static_cast<uint16_t>(kCellWidth));
    mem.write_u16(font_data_vaddr + 18u, static_cast<uint16_t>(kCellHeight));
    mem.write_u32(font_data_vaddr + 20u, kSheetBytes); // sheetSize
    mem.write_u16(font_data_vaddr + 24u, 0u);          // sheetFormat = GX_TF_I4
    mem.write_u16(font_data_vaddr + 26u, 16u);         // sheetColumn
    mem.write_u16(font_data_vaddr + 28u, 8u);          // sheetRow
    mem.write_u16(font_data_vaddr + 30u, static_cast<uint16_t>(kSheetWidth));
    mem.write_u16(font_data_vaddr + 32u, static_cast<uint16_t>(kSheetHeight));
    mem.write_u16(font_data_vaddr + 34u, static_cast<uint16_t>(kWidthTableOff));
    mem.write_u32(font_data_vaddr + 36u, kSheetOff);
    mem.write_u32(font_data_vaddr + 40u, kTotalBytes);

    // Build 95 ASCII glyphs into 24x16 cells using left-aligned EPX/Scale2x smoothing
    for (uint32_t idx = 0; idx < 95u; ++idx) {
        int min_x = 8;
        int max_x = -1;
        for (int sy = 0; sy < 8; ++sy) {
            uint8_t row = kOsFont8x8Basic[idx][sy];
            for (int sx = 0; sx < 8; ++sx) {
                if ((row & (0x80u >> sx)) != 0u) {
                    if (sx < min_x) min_x = sx;
                    if (sx > max_x) max_x = sx;
                }
            }
        }
        int shift_x = (max_x >= min_x) ? min_x : 0;
        uint8_t adv = (max_x >= min_x)
            ? static_cast<uint8_t>((max_x - min_x + 1) * 2 + 2)
            : 8u;
        if (adv > 18u) adv = 18u;
        mem.write_u8(font_data_vaddr + kWidthTableOff + idx, adv);

        auto sample = [&](int sx, int sy) -> uint8_t {
            int ox = sx + shift_x;
            if (ox < 0 || ox >= 8 || sy < 0 || sy >= 8) return 0u;
            return (kOsFont8x8Basic[idx][sy] & (0x80u >> ox)) ? 1u : 0u;
        };

        const uint32_t cell_x = (idx % 16u) * kCellWidth;
        const uint32_t cell_y = (idx / 16u) * kCellHeight;
        for (int sy = 0; sy < 8; ++sy) {
            for (int sx = 0; sx < 8; ++sx) {
                uint8_t p = sample(sx, sy);
                uint8_t a = sample(sx, sy - 1);
                uint8_t b = sample(sx + 1, sy);
                uint8_t c = sample(sx - 1, sy);
                uint8_t d = sample(sx, sy + 1);
                uint8_t tl = (c == a && c != d && a != b) ? a : p;
                uint8_t tr = (a == b && a != c && b != d) ? b : p;
                uint8_t bl = (d == c && d != b && c != a) ? c : p;
                uint8_t br = (b == d && b != a && d != c) ? d : p;
                const uint32_t px = cell_x + static_cast<uint32_t>(sx * 2);
                const uint32_t py = cell_y + static_cast<uint32_t>(sy * 2);
                osfont_write_i4_pixel(mem, sheet_vaddr, kSheetWidth, px,      py,      tl ? 0x0Fu : 0u);
                osfont_write_i4_pixel(mem, sheet_vaddr, kSheetWidth, px + 1u, py,      tr ? 0x0Fu : 0u);
                osfont_write_i4_pixel(mem, sheet_vaddr, kSheetWidth, px,      py + 1u, bl ? 0x0Fu : 0u);
                osfont_write_i4_pixel(mem, sheet_vaddr, kSheetWidth, px + 1u, py + 1u, br ? 0x0Fu : 0u);
            }
        }
    }

    g_osfont_header_vaddr = font_data_vaddr;
    g_osfont_sheet_vaddr  = sheet_vaddr;
    if (ctx.r[13] >= 0x80010000u && mem.is_valid_range(ctx.r[13] - 32768u, 4096u)) {
        mem.write_u32(ctx.r[13] - 29272u, font_data_vaddr);
        mem.write_u32(ctx.r[13] - 29268u, sheet_vaddr);
        mem.write_u16(ctx.r[13] - 31032u, 0u); // fontEncode = ANSI
    }
    return true;
}

static void osfont_resolve_char(Memory& mem, uint32_t font_header, uint8_t ch,
                                uint32_t& out_x, uint32_t& out_y, uint32_t& out_w) {
    if (ch < 0x20u || ch > 0x7Eu) {
        ch = 0x3Fu; // '?'
    }
    uint32_t idx = static_cast<uint32_t>(ch - 0x20u);
    out_x = (idx % 16u) * 24u;
    out_y = (idx / 16u) * 16u;
    out_w = (font_header != 0u && mem.is_valid_range(font_header + 0x40u + idx, 1))
        ? static_cast<uint32_t>(mem.read_u8(font_header + 0x40u + idx))
        : 12u;
}

static void hle_OSInitFont(PPCContext& ctx, Memory& mem) {
    ctx.r[3] = osfont_build_in_ram(ctx, mem, ctx.r[3]) ? 1u : 0u;
}

static void hle_OSLoadFont(PPCContext& ctx, Memory& mem) {
    ctx.r[3] = osfont_build_in_ram(ctx, mem, ctx.r[3]) ? 1u : 0u;
}

static void hle_OSGetFontTexture(PPCContext& ctx, Memory& mem) {
    uint32_t str_vaddr = ctx.r[3];
    uint32_t img_out   = ctx.r[4];
    uint32_t x_out     = ctx.r[5];
    uint32_t y_out     = ctx.r[6];
    uint32_t w_out     = ctx.r[7];

    if (str_vaddr == 0u || !mem.is_valid_range(str_vaddr, 1)) {
        if (img_out != 0u && mem.is_valid_range(img_out, 4)) mem.write_u32(img_out, 0u);
        if (x_out != 0u && mem.is_valid_range(x_out, 4)) mem.write_u32(x_out, 0u);
        if (y_out != 0u && mem.is_valid_range(y_out, 4)) mem.write_u32(y_out, 0u);
        if (w_out != 0u && mem.is_valid_range(w_out, 4)) mem.write_u32(w_out, 0u);
        ctx.r[3] = 0u;
        return;
    }

    if (g_osfont_header_vaddr == 0u) {
        osfont_build_in_ram(ctx, mem, 0x80C0C000u);
    }

    uint8_t ch = mem.read_u8(str_vaddr);
    if (ch == 0u) {
        if (img_out != 0u && mem.is_valid_range(img_out, 4)) mem.write_u32(img_out, g_osfont_sheet_vaddr);
        if (x_out != 0u && mem.is_valid_range(x_out, 4)) mem.write_u32(x_out, 0u);
        if (y_out != 0u && mem.is_valid_range(y_out, 4)) mem.write_u32(y_out, 0u);
        if (w_out != 0u && mem.is_valid_range(w_out, 4)) mem.write_u32(w_out, 0u);
        ctx.r[3] = str_vaddr;
        return;
    }

    uint32_t gx = 0u, gy = 0u, gw = 12u;
    osfont_resolve_char(mem, g_osfont_header_vaddr, ch, gx, gy, gw);
    if (img_out != 0u && mem.is_valid_range(img_out, 4)) mem.write_u32(img_out, g_osfont_sheet_vaddr);
    if (x_out != 0u && mem.is_valid_range(x_out, 4)) mem.write_u32(x_out, gx);
    if (y_out != 0u && mem.is_valid_range(y_out, 4)) mem.write_u32(y_out, gy);
    if (w_out != 0u && mem.is_valid_range(w_out, 4)) mem.write_u32(w_out, gw);
    ctx.r[3] = str_vaddr + 1u;
}

static void hle_OSGetFontWidth(PPCContext& ctx, Memory& mem) {
    uint32_t str_vaddr = ctx.r[3];
    uint32_t w_out     = ctx.r[4];
    if (str_vaddr == 0u || !mem.is_valid_range(str_vaddr, 1)) {
        if (w_out != 0u && mem.is_valid_range(w_out, 4)) mem.write_u32(w_out, 0u);
        ctx.r[3] = 0u;
        return;
    }
    if (g_osfont_header_vaddr == 0u) {
        osfont_build_in_ram(ctx, mem, 0x80C0C000u);
    }
    uint8_t ch = mem.read_u8(str_vaddr);
    if (ch == 0u) {
        if (w_out != 0u && mem.is_valid_range(w_out, 4)) mem.write_u32(w_out, 0u);
        ctx.r[3] = str_vaddr;
        return;
    }
    uint32_t gx = 0u, gy = 0u, gw = 12u;
    osfont_resolve_char(mem, g_osfont_header_vaddr, ch, gx, gy, gw);
    if (w_out != 0u && mem.is_valid_range(w_out, 4)) mem.write_u32(w_out, gw);
    ctx.r[3] = str_vaddr + 1u;
}

static void hle_OSGetFontTexel(PPCContext& ctx, Memory& mem) {
    uint32_t str_vaddr = ctx.r[3];
    uint32_t w_out     = ctx.r[7];
    if (str_vaddr == 0u || !mem.is_valid_range(str_vaddr, 1)) {
        if (w_out != 0u && mem.is_valid_range(w_out, 4)) mem.write_u32(w_out, 0u);
        ctx.r[3] = 0u;
        return;
    }
    if (g_osfont_header_vaddr == 0u) {
        osfont_build_in_ram(ctx, mem, 0x80C0C000u);
    }
    uint8_t ch = mem.read_u8(str_vaddr);
    if (ch == 0u) {
        if (w_out != 0u && mem.is_valid_range(w_out, 4)) mem.write_u32(w_out, 0u);
        ctx.r[3] = str_vaddr;
        return;
    }
    uint32_t gx = 0u, gy = 0u, gw = 12u;
    osfont_resolve_char(mem, g_osfont_header_vaddr, ch, gx, gy, gw);
    if (w_out != 0u && mem.is_valid_range(w_out, 4)) mem.write_u32(w_out, gw);
    ctx.r[3] = str_vaddr + 1u;
}

bool dispatch_recompiled_function(uint32_t target_vaddr, PPCContext& ctx, Memory& mem) {
    const bool trace_or_dbg = g_hle_call_trace || global_logger().should_log(LogLevel::Debug);
    struct DepthGuard {
        bool active;
        explicit DepthGuard(bool a) : active(a) { if (active) ++g_hle_call_depth; }
        ~DepthGuard() { if (active) --g_hle_call_depth; }
    } depth_guard(trace_or_dbg);
    if (trace_or_dbg) {
        ++g_hle_call_seq;
        const LogLevel lvl = (g_hle_call_depth <= 2) ? LogLevel::Debug : LogLevel::Trace;
        PN03_LOGF(lvl, "CALL", "#%llu d=%d 0x%08X (r3=0x%08X r4=0x%08X r5=0x%08X)",
                  static_cast<unsigned long long>(g_hle_call_seq),
                  g_hle_call_depth, target_vaddr, ctx.r[3], ctx.r[4], ctx.r[5]);
        if (g_hle_call_trace && (g_hle_call_seq <= 500 || (g_hle_call_seq % 1000) == 0)) {
            std::fprintf(stderr, "[CALL #%llu d=%d] 0x%08X (r3=0x%08X r4=0x%08X r5=0x%08X)\n",
                         static_cast<unsigned long long>(g_hle_call_seq),
                         g_hle_call_depth, target_vaddr, ctx.r[3], ctx.r[4], ctx.r[5]);
            std::fflush(stderr);
        }
    }
    // 0. Fast path for game addresses (< 0x800E3000): skip GX/VI, Audio, and 100+ SDK cases
    if (target_vaddr < 0x800E3000u) {
        switch (target_vaddr) {
            case 0x80073348u: { // Draw_cinesco(void)
                if (global_gx_3d_interface().config().remove_cinesco_bars) {
                    return true;
                }
                RecompFuncPtr fn = recomp::lookup_recompiled_function(target_vaddr);
                if (fn != nullptr) fn(ctx, mem);
                return true;
            }
            case 0x80077680u: // LzsDecode
                hle_LzsDecode(ctx, mem);
                return true;
            case 0x80081DC4u: { // EprintfBuffering(tagFONT&, char*)
                if (const auto* loc = LocalizationOverlay::active_instance()) {
                    loc->hook_eprintf_buffering(ctx, mem);
                }
                RecompFuncPtr fn = recomp::lookup_recompiled_function(target_vaddr);
                if (fn != nullptr) fn(ctx, mem);
                return true;
            }
            case 0x80081E70u: { // font_draw(char*, _GXColor&, x, y, w, h)
                if (const auto* loc = LocalizationOverlay::active_instance()) {
                    if (loc->hook_font_draw(ctx, mem)) {
                        return true;
                    }
                }
                RecompFuncPtr fn = recomp::lookup_recompiled_function(target_vaddr);
                if (fn != nullptr) fn(ctx, mem);
                return true;
            }
            case 0x8009F12Cu: // CMesCtrl::MesSetLanguage
                if (const auto* loc = LocalizationOverlay::active_instance()) {
                    loc->hook_mes_set_language(ctx, mem);
                } else {
                    mem.write_u32(ctx.r[3], 1u);
                    ctx.r[0] = 1u;
                }
                return true;
            case 0x8009F138u: // CMesCtrl::GetLanguage
                ctx.r[3] = mem.is_valid_range(ctx.r[3], 4u) ? mem.read_u32(ctx.r[3]) : 1u;
                if (ctx.r[3] > 5u) ctx.r[3] = 1u;
                return true;
            case 0x8009FDF0u: { // CMesWk::MesWorkTrans
                const uint32_t mes_wk = ctx.r[3];
                bool suppress_bitmap = false;
                if (const auto* loc = LocalizationOverlay::active_instance()) {
                    suppress_bitmap = loc->try_on_mes_work_trans(mes_wk, mem);
                }
                if (suppress_bitmap) {
                    ctx.r[3] = mes_wk;
                    dispatch_recompiled_function(0x8009FEB4u, ctx, mem);
                    const uint32_t flags = mem.read_u32(mes_wk + 40u);
                    if ((flags & 0x40000000u) != 0u) {
                        mem.write_u32(mes_wk + 0u, 0u);
                    }
                    return true;
                }
                RecompFuncPtr fn = recomp::lookup_recompiled_function(target_vaddr);
                if (fn != nullptr) fn(ctx, mem);
                return true;
            }
            case 0x800A00DCu: { // CMesWk::FontDraw
                if (const auto* loc = LocalizationOverlay::active_instance()) {
                    if (loc->try_on_mes_work_trans(ctx.r[3], mem)) {
                        return true;
                    }
                }
                RecompFuncPtr fn = recomp::lookup_recompiled_function(target_vaddr);
                if (fn != nullptr) fn(ctx, mem);
                return true;
            }
            default: {
                RecompFuncPtr fn = recomp::lookup_recompiled_function(target_vaddr);
                if (fn != nullptr) {
                    fn(ctx, mem);
                    return true;
                }
                PN03_LOGF(LogLevel::Warn, "HLE", "Unresolved target 0x%08X (r3=0x%08X r4=0x%08X)",
                          target_vaddr, ctx.r[3], ctx.r[4]);
                return false;
            }
        }
    }

    if (target_vaddr >= 0x8010C434u) {
        // 1. Route all VI* (0x8010C434..0x8010EBC4), GX* (0x8011C108..0x801275D0), & TEX* (0x801275FC..0x80127A50) calls
        if (target_vaddr <= 0x8010EBC4u ||
            (target_vaddr >= 0x8011C108u && target_vaddr <= 0x80127A50u)) {
            if (global_gx_3d_interface().dispatch_gx_vi_call(target_vaddr, ctx, mem)) {
                return true;
            }
        }

        // 2. Route Audio AI/AR/ARQ/AX/DSP boundaries to AudioAXInterface (leaving Capcom Snd_* 0x80136EEC..0x8013E59C recompiled)
        if ((target_vaddr >= 0x80111328u && target_vaddr <= 0x801142FCu) ||
            (target_vaddr >= 0x80151260u && target_vaddr <= 0x80160D44u)) {
            if (global_audio_ax_interface().dispatch_audio_call(target_vaddr, ctx, mem)) {
                return true;
            }
        }
    }

    // 3. Fast native HLE intercepts for OS / DVD / PAD / CARD / Math / C-Stdlib
    switch (target_vaddr) {
        case 0x800F17E8u: case 0x800F18C0u: case 0x800F18D0u: case 0x800F1944u: case 0x800F1970u: case 0x800F19A0u:
        case 0x800F19D0u: case 0x800F19FCu: case 0x800F1A80u: case 0x800F1AB4u:
        case 0x800F1B18u: case 0x800F1C24u: case 0x800F1DC8u: case 0x800F1E74u:
        case 0x800F1F2Cu: case 0x800F1F40u:
            return true; // __OSStopAudioSystem / DCEnable / Cache ops
        case 0x800F1A28u: // DCZeroRange
            hle_DCZeroRange(ctx, mem);
            return true;
        case 0x800F3828u: // OSGetFontEncode
            ctx.r[3] = 0u;
            return true;
        case 0x800F3A78u: // OSLoadFont
            hle_OSLoadFont(ctx, mem);
            return true;
        case 0x800F3DACu: // OSGetFontTexel
            hle_OSGetFontTexel(ctx, mem);
            return true;
        case 0x800F4460u: // OSInitFont
            hle_OSInitFont(ctx, mem);
            return true;
        case 0x800F4540u: // OSGetFontTexture
            hle_OSGetFontTexture(ctx, mem);
            return true;
        case 0x800F46E8u: // OSGetFontWidth
            hle_OSGetFontWidth(ctx, mem);
            return true;
        case 0x800F4874u: case 0x800F4C8Cu: case 0x800F4D14u: // __OSSetInterruptHandler / __OSMaskInterrupts / __OSUnmaskInterrupts
            ctx.r[3] = 1u;
            return true;
        case 0x800F7C68u: // OSGetSoundMode (0 = Stereo, 1 = Mono)
            ctx.r[3] = g_os_sound_mode;
            return true;
        case 0x800F7CE8u: // OSSetSoundMode(u32 mode)
            g_os_sound_mode = ctx.r[3] & 1u;
            return true;
        case 0x800F7DFCu: // OSSetProgressiveMode
            return true;
        case 0x800F7FCCu: // OSGetLanguage
            ctx.r[3] = 0u;
            return true;
        case 0x800FA758u: { // __OSGetSystemTime
            ctx.tb_ticks += 40500ull;
            ctx.r[3] = static_cast<uint32_t>(ctx.tb_ticks >> 32);
            ctx.r[4] = static_cast<uint32_t>(ctx.tb_ticks & 0xFFFFFFFFull);
            return true;
        }
        case 0x800F01C4u: case 0x800F0424u: case 0x800F048Cu: case 0x800F04FCu: case 0x800F0578u: // OSCreateAlarm / OSSetAlarm / OSCancelAlarm
            return true;
        case 0x800FB178u: case 0x800FB3C4u: // OSInitMutex / OSTryLockMutex
            ctx.r[3] = 1u;
            return true;
        case 0x800F5C04u: case 0x800F5C64u: case 0x800F5D2Cu: // OSInitMessageQueue / OSSendMessage / OSReceiveMessage
            ctx.r[3] = 1u;
            return true;
        // EXI hardware guards (Dolphin SDK EXI* returns BOOL TRUE=1 on success; 0 causes __OSReadROM / EXILock spin!)
        case 0x800FC228u: case 0x800FC4BCu: case 0x800FC6F8u: case 0x800FC778u:
        case 0x800FCAC8u: case 0x800FCBF4u: case 0x800FD288u: case 0x800FD37Cu:
        case 0x800FBE40u: case 0x800FC09Cu: case 0x800FC13Cu:
            ctx.r[3] = 1u;
            return true;
        case 0x800FD498u: // EXIGetID(chan, dev, id*)
            if (mem.is_valid_range(ctx.r[5], 4u)) mem.write_u32(ctx.r[5], 0u);
            ctx.r[3] = 1u;
            return true;
        // Exact MTX / VEC addresses from MEKA
        case 0x801000C0u: case 0x801000FCu: hle_PSMTXIdentity(ctx, mem); return true; // C_MTXIdentity / PSMTXIdentity
        case 0x80100128u: case 0x80100194u: hle_PSMTXCopy(ctx, mem);     return true; // C_MTXCopy / PSMTXCopy
        case 0x801001C8u: case 0x80100470u: hle_PSMTXConcat(ctx, mem);   return true; // C_MTXConcat / PSMTXConcat
        case 0x801006FCu: case 0x80100798u: hle_PSMTXTranspose(ctx, mem); return true; // C_MTXTranspose / PSMTXTranspose
        case 0x801007E8u: case 0x80100A94u: hle_PSMTXInverse(ctx, mem);   return true; // C_MTXInverse / PSMTXInverse
        case 0x80100B8Cu: case 0x80100DA8u: hle_PSMTXInvXpose(ctx, mem);  return true; // C_MTXInvXpose / PSMTXInvXpose
        case 0x80100E70u: case 0x80100EE0u: hle_PSMTXRotRad(ctx, mem);    return true; // C_MTXRotRad / PSMTXRotRad
        case 0x80100F50u: case 0x80101054u: hle_PSMTXRotTrig(ctx, mem);   return true; // C_MTXRotTrig / PSMTXRotTrig
        case 0x80101104u: case 0x801012CCu: hle_PSMTXRotAxisRad(ctx, mem);return true; // C_MTXRotAxisRad / PSMTXRotAxisRad
        case 0x8010133Cu: case 0x80101378u: hle_PSMTXTrans(ctx, mem);     return true; // C_MTXTrans / PSMTXTrans
        case 0x801013ACu: case 0x80101424u: hle_PSMTXTransApply(ctx, mem);return true; // C_MTXTransApply / PSMTXTransApply
        case 0x80101470u: case 0x801014A8u: hle_PSMTXScale(ctx, mem);     return true; // C_MTXScale / PSMTXScale
        case 0x801014D0u: case 0x80101564u: hle_PSMTXScaleApply(ctx, mem);return true; // C_MTXScaleApply / PSMTXScaleApply
        case 0x801015BCu: case 0x801016ACu: hle_PSMTXQuat(ctx, mem);      return true; // C_MTXQuat / PSMTXQuat
        case 0x801018C0u: hle_C_MTXLookAt(ctx, mem); return true;                      // C_MTXLookAt (exact!)
        case 0x80101C34u: case 0x80101CC8u: hle_PSMTXMultVec(ctx, mem);   return true; // C_MTXMultVec / PSMTXMultVec
        case 0x80101FACu: case 0x80102028u: hle_PSMTXMultVecSR(ctx, mem); return true; // C_MTXMultVecSR / PSMTXMultVecSR
        case 0x801022C0u: hle_C_MTXFrustum(ctx, mem); return true;                     // C_MTXFrustum
        case 0x8010235Cu: hle_C_MTXPerspectiveExact(ctx, mem); return true;            // C_MTXPerspective (exact!)
        case 0x8010242Cu: hle_C_MTXOrthoExact(ctx, mem); return true;                  // C_MTXOrtho (exact!)
        case 0x801038C0u: case 0x801038F4u: hle_PSVECAdd(ctx, mem);       return true; // C_VECAdd / PSVECAdd
        case 0x80103918u: case 0x8010394Cu: hle_PSVECSubtract(ctx, mem);  return true; // C_VECSubtract / PSVECSubtract
        case 0x80103970u: case 0x80103998u: hle_PSVECScale(ctx, mem);     return true; // C_VECScale / PSVECScale
        case 0x801039B4u: case 0x80103A7Cu: hle_PSVECNormalize(ctx, mem); return true; // C_VECNormalize / PSVECNormalize
        case 0x80103AC0u: case 0x80103AE4u: hle_PSVECSquareMag(ctx, mem); return true; // PSVECSquareMag
        case 0x80103AFCu: case 0x80103B90u: hle_PSVECMag(ctx, mem);       return true; // C_VECMag / PSVECMag
        case 0x80103BD4u: case 0x80103C04u: hle_PSVECDotProduct(ctx, mem); return true;// C_VECDotProduct / PSVECDotProduct
        case 0x80103C24u: case 0x80103C70u: hle_PSVECCrossProduct(ctx, mem); return true;// C_VECCrossProduct / PSVECCrossProduct
        case 0x80103E58u: case 0x80103E94u: hle_PSVECSquareDistance(ctx, mem); return true; // PSVECSquareDistance
        case 0x80103EBCu: case 0x80103F68u: hle_PSVECDistance(ctx, mem);  return true; // C_VECDistance / PSVECDistance
        // Exact DVD extras
        case 0x8010A2D0u: ctx.r[3] = 0x80000000u; return true; // DVDGetCurrentDiskID
        case 0x8010A2D8u: ctx.r[3] = 1u; return true;          // DVDCheckDisk
        case 0x801088C0u: ctx.r[3] = 1u; return true;          // DVDReadAbsAsyncPrio
        // Exact PAD / SI addresses from MEKA
        case 0x8010F228u: case 0x8010F33Cu: return true; // PADClamp / PADClampCircle
        case 0x8010FE10u: case 0x8010FF10u: case 0x80110014u:
        case 0x801105D8u: case 0x80110F80u: case 0x80110FE4u:
            ctx.r[3] = 1u; return true; // PADReset / PADRecalibrate / PADInit / PADSetSamplingRate / PADSync / PADSetAnalogMode
        case 0x8011022Cu: hle_PADRead(ctx, mem); return true; // PADRead (exact!)
        case 0x801105F8u: case 0x801106B0u: hle_PADControlMotor(ctx, mem); return true; // PADControlAllMotors / PADControlMotor (exact!)
        case 0x80110F0Cu: ctx.r[3] = (ctx.r[3] == 0u) ? 0u : static_cast<uint32_t>(-1); return true; // PADGetType
        case 0x800FF04Cu: case 0x800FF0F0u: case 0x800FF18Cu:
        case 0x800FF2CCu: case 0x800FF41Cu: case 0x800FF898u: case 0x800FFA5Cu:
            ctx.r[3] = 0x09000000u; return true; // SI_TYPE_GC for SIGetType / SI*
        // Exact C stdlib & IEEE math outside 0x800E3000..0x800E8F00
        case 0x8014CB80u: hle_memcmp(ctx, mem); return true;  // memcmp
        case 0x8014CC10u: hle_strncpy(ctx, mem); return true; // strncpy
        case 0x8014BA30u: set_fp_return(ctx, (ctx.f[2] != 0.0) ? std::fmod(ctx.f[1], ctx.f[2]) : 0.0); return true; // fmod
        case 0x8014BDBCu: set_fp_return(ctx, (ctx.f[1] > 0.0) ? std::log10(ctx.f[1]) : 0.0); return true; // log10
        case 0x8014BEE8u: set_fp_return(ctx, std::pow(ctx.f[1], ctx.f[2])); return true; // pow
        case 0x8014C700u: set_fp_return(ctx, (ctx.f[1] > 0.0) ? std::log(ctx.f[1]) : 0.0); return true; // log
        case 0x8014C990u: ctx.r[3] = static_cast<uint32_t>(std::tolower(static_cast<int>(ctx.r[3] & 0xFFu))); return true; // tolower

        // Math library HLE (0x800E300C..0x800E6A88)
        case 0x800E300Cu: case 0x800E4298u: set_fp_return(ctx, (ctx.f[1] > 0.0) ? std::sqrt(ctx.f[1]) : 0.0); return true;
        case 0x800E3270u: case 0x800E45B4u: set_fp_return(ctx, std::cos(ctx.f[1])); return true;
        case 0x800E3350u: case 0x800E46B4u: set_fp_return(ctx, std::sin(ctx.f[1])); return true;
        case 0x800E3430u: case 0x800E4790u: set_fp_return(ctx, std::tan(ctx.f[1])); return true;
        case 0x800E34B4u: set_fp_return(ctx, std::acos(std::clamp(ctx.f[1], -1.0, 1.0))); return true;
        case 0x800E3704u: set_fp_return(ctx, std::asin(std::clamp(ctx.f[1], -1.0, 1.0))); return true;
        case 0x800E3930u: set_fp_return(ctx, std::atan2(ctx.f[1], ctx.f[2])); return true;
        case 0x800E3B68u: set_fp_return(ctx, std::pow(ctx.f[1], ctx.f[2])); return true;
        case 0x800E43A4u: set_fp_return(ctx, std::atan(ctx.f[1])); return true;
        case 0x800E4690u: case 0x800E508Cu: set_fp_return(ctx, std::fabs(ctx.f[1])); return true;
        case 0x800E57D0u: set_fp_return(ctx, std::copysign(ctx.f[1], ctx.f[2])); return true;
        case 0x800E6090u: case 0x800E6A88u: set_fp_return(ctx, std::floor(ctx.f[1])); return true;

        // C String & Stdlib HLE
        case 0x800E6DA0u: hle_sprintf_r(ctx, mem); return true;
        case 0x800E6E74u: hle_sprintf(ctx, mem);   return true;
        case 0x800E7F1Cu: hle_vsprintf(ctx, mem);  return true;
        case 0x800E7F78u: hle_vsnprintf(ctx, mem); return true;
        case 0x800E88CCu: hle_memcpy(ctx, mem);  return true;
        case 0x800E8970u: hle_memmove(ctx, mem); return true;
        case 0x800E8A5Cu: hle_memset(ctx, mem);  return true;
        case 0x800E8AF0u: case 0x801281ACu: hle_strcat(ctx, mem);  return true;
        case 0x800E8B80u: hle_strchr(ctx, mem);  return true;
        case 0x800E8C1Cu: case 0x80128240u: hle_strcmp(ctx, mem);  return true;
        case 0x800E8CC4u: case 0x80128224u: hle_strcpy(ctx, mem);  return true;
        case 0x800E8D48u: case 0x80128290u: hle_strlen(ctx, mem);  return true;
        case 0x800E8DB4u: hle_strncmp(ctx, mem); return true;
        case 0x800E8E94u: hle_strrchr(ctx, mem); return true;

        // OS / Arena / Multi-Heap / Cache / Interrupts / Threads / Time
        case 0x800EF76Cu: return true; // OSInit
        case 0x800F0B58u: hle_OSAllocFromHeap(ctx, mem); return true;
        case 0x800F0ED8u: hle_OSFreeToHeap(ctx, mem);    return true;
        case 0x800F0F54u: hle_OSSetCurrentHeap(ctx, mem);return true;
        case 0x800F0F64u: hle_OSInitAlloc(ctx, mem);     return true;
        case 0x800F0FD4u: hle_OSCreateHeap(ctx, mem);    return true;
        case 0x800F1040u: hle_OSDestroyHeap(ctx, mem);   return true;
        case 0x800F10B4u: hle_OSCheckHeap(ctx, mem);     return true;
        case 0x800F15C0u: hle_OSGetArenaHi(ctx, mem);    return true;
        case 0x800F15C8u: hle_OSGetArenaLo(ctx, mem);    return true;
        case 0x800F15D0u: hle_OSSetArenaHi(ctx, mem);    return true;
        case 0x800F15D8u: hle_OSSetArenaLo(ctx, mem);    return true;
        case 0x800F2D80u: hle_OSReport(ctx, mem); return true; // OSReport
        case 0x800F2E20u: hle_OSPanic(ctx, mem); return true;  // OSPanic
        case 0x800F4828u: ctx.r[3] = 1u; return true;    // OSDisableInterrupts
        case 0x800F483Cu: ctx.r[3] = 1u; return true;    // OSEnableInterrupts
        case 0x800F4850u: ctx.r[3] = 1u; return true;    // OSRestoreInterrupts
        case 0x800F7D8Cu: ctx.r[3] = 1u; return true;    // OSGetProgressiveMode (1 = Progressive)
        case 0x800F8420u: hle_OSInitSemaphore(ctx, mem);     return true;
        case 0x800F8478u: hle_OSWaitSemaphore(ctx, mem);     return true;
        case 0x800F84E8u: hle_OSTryWaitSemaphore(ctx, mem);  return true;
        case 0x800F853Cu: hle_OSSignalSemaphore(ctx, mem);   return true;
        case 0x800F859Cu: hle_OSGetSemaphoreCount(ctx, mem); return true;
        case 0x800F87F8u: return true;                       // OSInitThreadQueue
        case 0x800F8808u: ctx.r[3] = g_active_thread_vaddr; return true; // OSGetCurrentThread
        case 0x800F8904u: case 0x800F8944u: ctx.r[3] = 1u; return true;  // OSDisable/EnableScheduler
        case 0x800F8F74u: flush_pending_hle_callbacks(ctx, mem); return true; // OSYieldThread
        case 0x800F8FB0u: hle_OSCreateThread(ctx, mem);      return true;
        case 0x800F9198u: hle_OSExitThread(ctx, mem);        return true;
        case 0x800F927Cu: hle_OSCancelThread(ctx, mem);      return true;
        case 0x800F9618u: hle_OSResumeThread(ctx, mem);      return true;
        case 0x800F98A0u: ctx.r[3] = 1u; return true;        // OSSuspendThread
        case 0x800F9A10u: hle_OSSleepThread(ctx, mem);       return true;
        case 0x800F9AFCu: hle_OSWakeupThread(ctx, mem);      return true;
        case 0x800FA58Cu: hle_OSClearStack(ctx, mem);        return true;
        case 0x800FA6A0u:
            ctx.tb_ticks += 40500ull;
            ctx.r[3] = static_cast<uint32_t>(ctx.tb_ticks >> 32);
            ctx.r[4] = static_cast<uint32_t>(ctx.tb_ticks & 0xFFFFFFFFull);
            return true;
        case 0x800FA6B8u:
            ctx.tb_ticks += 40500ull;
            ctx.r[3] = static_cast<uint32_t>(ctx.tb_ticks & 0xFFFFFFFFull);
            return true;
        case 0x800FAB38u:
            hle_OSTicksToCalendarTime(ctx, mem);
            return true;
        case 0x800FAD3Cu:
            hle_OSCalendarTimeToTicks(ctx, mem);
            return true;

        // DVD* HLE
        case 0x80105948u: hle_DVDConvertPathToEntrynum(ctx, mem); return true;
        case 0x80105C3Cu: hle_DVDFastOpen(ctx, mem);              return true;
        case 0x80105CB0u: hle_DVDOpen(ctx, mem);                  return true;
        case 0x80105D78u: hle_DVDClose(ctx, mem);                 return true;
        case 0x801061ACu: hle_DVDReadAsyncPrio(ctx, mem);         return true;
        case 0x8010629Cu: hle_DVDReadPrio(ctx, mem);              return true;
        case 0x801063D8u: case 0x801064A0u: ctx.r[3] = 1u;        return true; // DVDSeek
        case 0x80106570u: case 0x80109BA0u: case 0x80109BECu:
            flush_pending_hle_callbacks(ctx, mem);
            ctx.r[3] = 0u; // DVD_STATE_END
            return true;
        case 0x80106A6Cu: case 0x80109C98u: case 0x80109D34u:
        case 0x80109FB0u: case 0x8010AE54u:
            ctx.r[3] = 1u;
            return true;

        // VI adjusting exact entries
        case 0x8010EC00u: case 0x8010EEC8u: return true; // __VISetAdjustingValues / __VIGetAdjustingValues

        // Complete Dolphin SDK Memory Card (CARD*) HLE (exact entry points)
        case 0x80115508u: hle_CARDInit(ctx, mem); return true;
        case 0x801157C8u: hle_CARDGetResultCode(ctx, mem); return true;
        case 0x801157F8u: hle_CARDFreeBlocks(ctx, mem); return true;
        case 0x80115948u: { // CARDGetEncoding(chan, u16* encode)
            const int32_t chan = static_cast<int32_t>(ctx.r[3]);
            std::lock_guard<std::mutex> lk(g_card_mtx);
            const int32_t res = card_validate_channel(chan, false);
            if (res == kCardResultReady && ctx.r[4] >= kGcRamBase && mem.is_valid_range(ctx.r[4], 2u)) {
                mem.write_u16(ctx.r[4], 0u); // CARD_ENCODE_ANSI
            }
            ctx.r[3] = static_cast<uint32_t>(res);
            return true;
        }
        case 0x801159D0u: { // CARDGetMemSize(chan, u16* size)
            const int32_t chan = static_cast<int32_t>(ctx.r[3]);
            std::lock_guard<std::mutex> lk(g_card_mtx);
            const int32_t res = card_validate_channel(chan, false);
            if (res == kCardResultReady && ctx.r[4] >= kGcRamBase && mem.is_valid_range(ctx.r[4], 2u)) {
                mem.write_u16(ctx.r[4], static_cast<uint16_t>(kCardMemSizeMb));
            }
            ctx.r[3] = static_cast<uint32_t>(res);
            return true;
        }
        case 0x80115A54u: { // CARDGetSectorSize(chan, u32* size)
            const int32_t chan = static_cast<int32_t>(ctx.r[3]);
            std::lock_guard<std::mutex> lk(g_card_mtx);
            const int32_t res = card_validate_channel(chan, false);
            if (res == kCardResultReady && ctx.r[4] >= kGcRamBase && mem.is_valid_range(ctx.r[4], 4u)) {
                mem.write_u32(ctx.r[4], kCardSectorSize);
            }
            ctx.r[3] = static_cast<uint32_t>(res);
            return true;
        }
        case 0x80116BACu: hle_CARDCheck(ctx, mem, true,  true);  return true; // CARDCheckExAsync
        case 0x8011713Cu: hle_CARDCheck(ctx, mem, false, true);  return true; // CARDCheckAsync
        case 0x80117164u: hle_CARDCheck(ctx, mem, true,  false); return true; // CARDCheckEx
        case 0x801171C0u: hle_CARDCheck(ctx, mem, false, false); return true; // CARDCheck
        case 0x80117334u: hle_CARDProbe(ctx, mem);   return true;
        case 0x8011736Cu: hle_CARDProbeEx(ctx, mem); return true;
        case 0x80117A30u: hle_CARDMount(ctx, mem, true);  return true; // CARDMountAsync
        case 0x80117BD0u: hle_CARDMount(ctx, mem, false); return true; // CARDMount
        case 0x80117CB4u: hle_CARDUnmount(ctx, mem);      return true;
        case 0x80118544u: hle_CARDFormat(ctx, mem, true);  return true; // CARDFormatAsync
        case 0x8011858Cu: hle_CARDFormat(ctx, mem, false); return true; // CARDFormat
        case 0x80118860u: hle_CARDOpen(ctx, mem, true);  return true; // CARDFastOpen
        case 0x801189C0u: hle_CARDOpen(ctx, mem, false); return true; // CARDOpen
        case 0x80118B38u: hle_CARDClose(ctx, mem);       return true;
        case 0x80118CC4u: hle_CARDCreate(ctx, mem, true);  return true; // CARDCreateAsync
        case 0x80118EE4u: hle_CARDCreate(ctx, mem, false); return true; // CARDCreate
        case 0x80119214u: hle_CARDRead(ctx, mem, true);    return true; // CARDReadAsync
        case 0x8011935Cu: hle_CARDRead(ctx, mem, false);   return true; // CARDRead
        case 0x801193A4u: ctx.r[3] = 0u; return true; // CARDCancel
        case 0x80119650u: hle_CARDWrite(ctx, mem, true);   return true; // CARDWriteAsync
        case 0x80119764u: hle_CARDWrite(ctx, mem, false);  return true; // CARDWrite
        case 0x80119850u: hle_CARDDelete(ctx, mem, true,  true);  return true; // CARDFastDeleteAsync
        case 0x8011997Cu: hle_CARDDelete(ctx, mem, true,  false); return true; // CARDFastDelete
        case 0x801199C4u: hle_CARDDelete(ctx, mem, false, true);  return true; // CARDDeleteAsync
        case 0x80119AD4u: hle_CARDDelete(ctx, mem, false, false); return true; // CARDDelete
        case 0x80119D14u: hle_CARDGetStatus(ctx, mem);           return true;
        case 0x80119E40u: hle_CARDSetStatus(ctx, mem, true);     return true; // CARDSetStatusAsync
        case 0x80119FB4u: hle_CARDSetStatus(ctx, mem, false);    return true; // CARDSetStatus
        case 0x8011A014u: { // CARDGetSerialNo(chan, u64* serialNo)
            const int32_t chan = static_cast<int32_t>(ctx.r[3]);
            std::lock_guard<std::mutex> lk(g_card_mtx);
            const int32_t res = card_validate_channel(chan, true);
            if (res == kCardResultReady && ctx.r[4] >= kGcRamBase && mem.is_valid_range(ctx.r[4], 8u)) {
                mem.write_u32(ctx.r[4] + 0u, 0x504E3033u);
                mem.write_u32(ctx.r[4] + 4u, 0x43415244u);
            }
            ctx.r[3] = static_cast<uint32_t>(res);
            return true;
        }
        case 0x8011BAF0u: { // CARDGetXferredBytes(chan)
            const int32_t chan = static_cast<int32_t>(ctx.r[3]);
            std::lock_guard<std::mutex> lk(g_card_mtx);
            if (chan < 0 || chan >= 2) { ctx.r[3] = 0u; return true; }
            ctx.r[3] = g_card_slots[chan].last_xfer_bytes;
            return true;
        }

        default: {
            RecompFuncPtr fn = recomp::lookup_recompiled_function(target_vaddr);
            if (fn != nullptr) {
                fn(ctx, mem);
                return true;
            }
            break;
        }
    }
    PN03_LOGF(LogLevel::Warn, "HLE", "Unresolved target 0x%08X (r3=0x%08X r4=0x%08X)",
              target_vaddr, ctx.r[3], ctx.r[4]);
    return false;
}

} // namespace pn03

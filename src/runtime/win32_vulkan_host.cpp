#include "pn03_vulkan_host.hpp"
#include "pn03_vulkan_minimal.hpp"
#include "pn03_vulkan_shaders.hpp"
#include "pn03_host_common.hpp"
#include "pn03_logger.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

namespace pn03 {

static_assert(sizeof(GXVertex) == 48u, "GXVertex size must match SPIR-V input stride");
static_assert(offsetof(GXVertex, pos) == 0u, "GXVertex::pos offset mismatch");
static_assert(offsetof(GXVertex, color0) == 24u, "GXVertex::color0 offset mismatch");
static_assert(offsetof(GXVertex, uv0) == 40u, "GXVertex::uv0 offset mismatch");
static_assert(sizeof(GXSceneConstantsCPU) == 192u, "GXSceneConstantsCPU size must match SPIR-V UBO");
static_assert(sizeof(FxaaConstantsCPU) == 32u, "FxaaConstantsCPU size must match SPIR-V UBO");

namespace {

constexpr uint32_t kMaxFramesInFlight        = 2u;
constexpr size_t   kGxUboStride              = 256u; // Spec max minUniformBufferOffsetAlignment <= 256
constexpr size_t   kMaxGxUboSlotsPerFrame    = 8192u;
constexpr uint32_t kDescPoolChunkSets        = 4096u;
constexpr size_t   kMaxCachedGcTextures      = 1024u;
constexpr size_t   kMaxCachedGcTextureBytes  = 256u * 1024u * 1024u;
constexpr size_t   kMaxCachedTextTextures    = 256u;
constexpr size_t   kMaxCachedDescSets        = 8192u;

struct StagingBufferRec {
    vk::VkBuffer       buf = nullptr;
    vk::VkDeviceMemory mem = nullptr;
};

struct CachedTexture {
    vk::VkImage        img             = nullptr;
    vk::VkDeviceMemory mem             = nullptr;
    vk::VkImageView    view            = nullptr;
    uint32_t           w               = 0u;
    uint32_t           h               = 0u;
    size_t             byte_size       = 0u;
    uint64_t           last_used_frame = 0u;
};

struct OvDrawItem {
    vk::VkDescriptorSet desc_set = nullptr;
    uint32_t            idx_off  = 0u;
};

struct PendingImageUpload {
    vk::VkImage        img = nullptr;
    vk::VkBuffer       staging_buf = nullptr;
    vk::VkDeviceMemory staging_mem = nullptr;
    uint32_t           w = 0u;
    uint32_t           h = 0u;
};

struct TexDescKey {
    uint64_t view0 = 0u;
    uint64_t view1 = 0u;
    uint32_t samp0 = 0u;
    uint32_t samp1 = 0u;

    bool operator==(const TexDescKey& o) const noexcept {
        return view0 == o.view0 && view1 == o.view1 && samp0 == o.samp0 && samp1 == o.samp1;
    }
};

struct TexDescKeyHash {
    size_t operator()(const TexDescKey& k) const noexcept {
        uint64_t h = k.view0 * 11400714819323198485ULL;
        h ^= k.view1 + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
        h ^= (static_cast<uint64_t>(k.samp0) << 16) | static_cast<uint64_t>(k.samp1);
        h ^= h >> 30;
        h *= 0xbf58476d1ce4e5b9ULL;
        h ^= h >> 27;
        return static_cast<size_t>(h);
    }
};

struct FrameSlot {
    vk::VkFence         in_flight_fence     = nullptr;
    vk::VkSemaphore     image_available_sem = nullptr;
    vk::VkCommandBuffer cmd_buf             = nullptr;

    vk::VkBuffer       dyn_vb        = nullptr;
    vk::VkDeviceMemory dyn_vb_mem    = nullptr;
    void*              dyn_vb_mapped = nullptr;
    size_t             dyn_vb_bytes  = 0u;

    vk::VkBuffer       dyn_ib        = nullptr;
    vk::VkDeviceMemory dyn_ib_mem    = nullptr;
    void*              dyn_ib_mapped = nullptr;
    size_t             dyn_ib_bytes  = 0u;

    vk::VkBuffer       fxaa_ubo        = nullptr;
    vk::VkDeviceMemory fxaa_ubo_mem    = nullptr;
    void*              fxaa_ubo_mapped = nullptr;
    vk::VkDescriptorSet fxaa_desc_set  = nullptr;

    std::vector<StagingBufferRec> staging_garbage;
    std::vector<CachedTexture>    retired_textures;
};

vk::VkFlags sample_count_to_vk(uint32_t count) noexcept {
    switch (count) {
        case 8u: return vk::VK_SAMPLE_COUNT_8_BIT;
        case 4u: return vk::VK_SAMPLE_COUNT_4_BIT;
        case 2u: return vk::VK_SAMPLE_COUNT_2_BIT;
        default: return vk::VK_SAMPLE_COUNT_1_BIT;
    }
}

uint32_t resolve_requested_msaa(AntiAliasingMode mode) noexcept {
    switch (mode) {
        case AntiAliasingMode::MSAA_2x: return 2u;
        case AntiAliasingMode::MSAA_4x: return 4u;
        case AntiAliasingMode::MSAA_8x: return 8u;
        default: return 1u;
    }
}

#ifdef _WIN32
LRESULT CALLBACK PN03VulkanWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    auto* host = reinterpret_cast<Win32VulkanHost*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    switch (msg) {
        case WM_CLOSE:
            if (host) host->mark_close_requested();
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            if (host) host->mark_close_requested();
            return 0;
        case WM_SIZE:
            if (host && wParam != SIZE_MINIMIZED) {
                const uint32_t nw = LOWORD(lParam);
                const uint32_t nh = HIWORD(lParam);
                if (nw > 0u && nh > 0u) {
                    host->handle_window_resize(nw, nh);
                }
            }
            return 0;
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE && (GetKeyState(VK_SHIFT) & 0x8000) != 0) {
                if (host) host->mark_close_requested();
                DestroyWindow(hwnd);
                return 0;
            }
            break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}
#endif

} // namespace

struct Win32VulkanHost::Impl {
    vk::VkDynamicDispatch               vk{};
    vk::VkInstance                      instance       = nullptr;
    vk::VkPhysicalDevice                phys_dev       = nullptr;
    vk::VkDevice                        device         = nullptr;
    vk::VkQueue                         graphics_queue = nullptr;
    uint32_t                            queue_family   = 0u;
    vk::VkSurfaceKHR                    surface        = nullptr;
    vk::VkPhysicalDeviceMemoryProperties mem_props{};
    bool                                aniso_supported = false;

    vk::VkCommandPool                   cmd_pool       = nullptr;
    vk::VkCommandBuffer                 one_time_cmd   = nullptr;
    vk::VkSwapchainKHR                  swapchain      = nullptr;
    vk::VkFormat                        swapchain_fmt  = vk::VK_FORMAT_B8G8R8A8_UNORM;
    bool                                swapchain_bgra = true;
    bool                                swapchain_transfer_src = false;
    std::vector<vk::VkImage>            swapchain_images;
    std::vector<vk::VkImageView>        swapchain_views;
    std::vector<vk::VkFramebuffer>      swapchain_fbs;
    std::vector<vk::VkSemaphore>        render_finished_sems;
    vk::VkRenderPass                    present_render_pass = nullptr;
    vk::VkRenderPass                    capture_render_pass = nullptr;

    // Offscreen EFB + Depth
    vk::VkFormat                        depth_fmt      = vk::VK_FORMAT_D32_SFLOAT;
    vk::VkFlags                         depth_aspect   = vk::VK_IMAGE_ASPECT_DEPTH_BIT;
    vk::VkRenderPass                    efb_render_pass = nullptr;
    vk::VkFramebuffer                   efb_fb         = nullptr;
    vk::VkImage                         efb_msaa_img   = nullptr;
    vk::VkDeviceMemory                  efb_msaa_mem   = nullptr;
    vk::VkImageView                     efb_msaa_view  = nullptr;
    vk::VkImage                         efb_depth_img  = nullptr;
    vk::VkDeviceMemory                  efb_depth_mem  = nullptr;
    vk::VkImageView                     efb_depth_view = nullptr;
    vk::VkImage                         efb_resolved_img  = nullptr;
    vk::VkDeviceMemory                  efb_resolved_mem  = nullptr;
    vk::VkImageView                     efb_resolved_view = nullptr;

    // Shader Modules
    vk::VkShaderModule                  sm_gx_vs   = nullptr;
    vk::VkShaderModule                  sm_gx_fs   = nullptr;
    vk::VkShaderModule                  sm_fxaa_vs = nullptr;
    vk::VkShaderModule                  sm_blit_fs = nullptr;
    vk::VkShaderModule                  sm_fxaa_fs = nullptr;

    // Layouts & Descriptor Pools
    vk::VkDescriptorSetLayout           gx_dsl         = nullptr;
    vk::VkPipelineLayout                gx_pl          = nullptr;
    vk::VkDescriptorSetLayout           fxaa_dsl       = nullptr;
    vk::VkPipelineLayout                fxaa_pl        = nullptr;
    vk::VkDescriptorPool                fxaa_desc_pool = nullptr;
    std::vector<vk::VkDescriptorPool>   gx_desc_pools;

    // Pipelines
    // [cull 0..2][depth 0..2 (none, ro, rw)][blend 0..2 (opaque, alpha, add)]
    vk::VkPipeline                      gx_pipelines[3][3][3]{};
    vk::VkPipeline                      overlay_pipeline = nullptr;
    vk::VkPipeline                      fxaa_pipeline    = nullptr;
    vk::VkPipeline                      blit_pipeline    = nullptr;

    // Global dynamic GX UBO shared across frames via [frame * kMaxGxUboSlotsPerFrame] offsets
    vk::VkBuffer                        gx_ubo_buf    = nullptr;
    vk::VkDeviceMemory                  gx_ubo_mem    = nullptr;
    void*                               gx_ubo_mapped = nullptr;

    // Samplers & Texture Caches
    vk::VkSampler                       samplers[9]{};
    vk::VkSampler                       sampler_linear_clamp = nullptr;
    CachedTexture                       default_white_tex{};
    std::unordered_map<uint64_t, CachedTexture>        tex_cache;
    size_t                                             tex_cache_bytes  = 0u;
    std::unordered_map<std::string, CachedTexture>     text_cache;
    std::unordered_map<TexDescKey, vk::VkDescriptorSet, TexDescKeyHash> tex_desc_cache;
    uint64_t                                           cache_frame_tick = 1u;

    // Per-frame synchronization & streaming buffers
    std::array<FrameSlot, kMaxFramesInFlight> frames{};
    uint32_t                            frame_cursor           = 0u;
    uint32_t                            last_submitted_slot    = 0u;
    uint32_t                            active_swapchain_image = 0u;
    bool                                frame_submitted        = false;
    bool                                has_ever_submitted     = false;
    std::vector<OvDrawItem>             last_ov_items;
    uint32_t                            last_ov_ubo_dyn_off    = 0u;
    HostViewportRect                    last_out_rect{};

    // Helpers
    uint32_t find_memory_type(uint32_t type_bits, vk::VkFlags required_props) const noexcept {
        for (uint32_t i = 0u; i < mem_props.memoryTypeCount; ++i) {
            if ((type_bits & (1u << i)) != 0u &&
                (mem_props.memoryTypes[i].propertyFlags & required_props) == required_props) {
                return i;
            }
        }
        return ~0u;
    }

    bool create_buffer(
        size_t size,
        vk::VkFlags usage,
        vk::VkFlags required_mem,
        vk::VkBuffer& out_buf,
        vk::VkDeviceMemory& out_mem
    ) {
        vk::VkBufferCreateInfo bci{};
        bci.sType       = vk::VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bci.size        = size;
        bci.usage       = usage;
        bci.sharingMode = vk::VK_SHARING_MODE_EXCLUSIVE;
        if (vk.vkCreateBuffer(device, &bci, nullptr, &out_buf) != vk::VK_SUCCESS || !out_buf) {
            return false;
        }
        vk::VkMemoryRequirements req{};
        vk.vkGetBufferMemoryRequirements(device, out_buf, &req);
        const uint32_t mem_idx = find_memory_type(req.memoryTypeBits, required_mem);
        if (mem_idx == ~0u) {
            vk.vkDestroyBuffer(device, out_buf, nullptr);
            out_buf = nullptr;
            return false;
        }
        vk::VkMemoryAllocateInfo mai{};
        mai.sType           = vk::VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        mai.allocationSize  = req.size;
        mai.memoryTypeIndex = mem_idx;
        if (vk.vkAllocateMemory(device, &mai, nullptr, &out_mem) != vk::VK_SUCCESS || !out_mem) {
            vk.vkDestroyBuffer(device, out_buf, nullptr);
            out_buf = nullptr;
            return false;
        }
        if (vk.vkBindBufferMemory(device, out_buf, out_mem, 0) != vk::VK_SUCCESS) {
            vk.vkDestroyBuffer(device, out_buf, nullptr);
            vk.vkFreeMemory(device, out_mem, nullptr);
            out_buf = nullptr;
            out_mem = nullptr;
            return false;
        }
        return true;
    }

    void destroy_buffer(vk::VkBuffer& buf, vk::VkDeviceMemory& mem, void** mapped = nullptr) {
        if (mapped && *mapped && mem) {
            vk.vkUnmapMemory(device, mem);
            *mapped = nullptr;
        }
        if (buf) {
            vk.vkDestroyBuffer(device, buf, nullptr);
            buf = nullptr;
        }
        if (mem) {
            vk.vkFreeMemory(device, mem, nullptr);
            mem = nullptr;
        }
    }

    bool ensure_frame_dyn_buffers(FrameSlot& slot, size_t req_vb_bytes, size_t req_ib_bytes) {
        const size_t min_vb = 262144u * sizeof(GXVertex);
        const size_t max_vb = kHostMaxDynamicVertices * sizeof(GXVertex);
        const size_t target_vb = std::clamp((std::max)(req_vb_bytes, min_vb), min_vb, max_vb);
        if (!slot.dyn_vb || slot.dyn_vb_bytes < req_vb_bytes) {
            const size_t alloc_vb = (std::max)(target_vb, slot.dyn_vb_bytes);
            if (slot.dyn_vb && slot.dyn_vb_bytes >= alloc_vb) {
                // Already big enough
            } else {
                destroy_buffer(slot.dyn_vb, slot.dyn_vb_mem, &slot.dyn_vb_mapped);
                if (!create_buffer(
                        alloc_vb,
                        vk::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                        vk::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | vk::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                        slot.dyn_vb,
                        slot.dyn_vb_mem)) {
                    return false;
                }
                if (vk.vkMapMemory(device, slot.dyn_vb_mem, 0, vk::VK_WHOLE_SIZE, 0, &slot.dyn_vb_mapped) != vk::VK_SUCCESS) {
                    return false;
                }
                slot.dyn_vb_bytes = alloc_vb;
            }
        }

        const size_t min_ib = 786432u * sizeof(uint32_t);
        const size_t max_ib = kHostMaxDynamicIndices * sizeof(uint32_t);
        const size_t target_ib = std::clamp((std::max)(req_ib_bytes, min_ib), min_ib, max_ib);
        if (!slot.dyn_ib || slot.dyn_ib_bytes < req_ib_bytes) {
            const size_t alloc_ib = (std::max)(target_ib, slot.dyn_ib_bytes);
            destroy_buffer(slot.dyn_ib, slot.dyn_ib_mem, &slot.dyn_ib_mapped);
            if (!create_buffer(
                    alloc_ib,
                    vk::VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                    vk::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | vk::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                    slot.dyn_ib,
                    slot.dyn_ib_mem)) {
                return false;
            }
            if (vk.vkMapMemory(device, slot.dyn_ib_mem, 0, vk::VK_WHOLE_SIZE, 0, &slot.dyn_ib_mapped) != vk::VK_SUCCESS) {
                return false;
            }
            slot.dyn_ib_bytes = alloc_ib;
        }
        return true;
    }

    void free_staging_garbage(FrameSlot& slot) {
        for (auto& g : slot.staging_garbage) {
            destroy_buffer(g.buf, g.mem);
        }
        slot.staging_garbage.clear();
        for (auto& t : slot.retired_textures) {
            destroy_image(t.img, t.mem, t.view);
        }
        slot.retired_textures.clear();
    }

    void erase_desc_cache_for_view(vk::VkImageView view) {
        if (!view) return;
        const uint64_t v = reinterpret_cast<uint64_t>(view);
        for (auto it = tex_desc_cache.begin(); it != tex_desc_cache.end(); ) {
            if (it->first.view0 == v || it->first.view1 == v) {
                it = tex_desc_cache.erase(it);
            } else {
                ++it;
            }
        }
    }

    void recycle_descriptor_pools_if_needed() {
        if (tex_desc_cache.size() < kMaxCachedDescSets && gx_desc_pools.size() <= 2u) {
            return;
        }
        vk.vkDeviceWaitIdle(device);
        for (auto& f : frames) {
            free_staging_garbage(f);
        }
        last_ov_items.clear();
        tex_desc_cache.clear();
        if (!gx_desc_pools.empty()) {
            if (vk.vkResetDescriptorPool) {
                vk.vkResetDescriptorPool(device, gx_desc_pools[0], 0u);
            }
            for (size_t i = 1u; i < gx_desc_pools.size(); ++i) {
                if (gx_desc_pools[i]) {
                    vk.vkDestroyDescriptorPool(device, gx_desc_pools[i], nullptr);
                }
            }
            gx_desc_pools.resize(1u);
        }
    }

    void recover_after_aborted_acquire(FrameSlot& slot) {
        vk.vkDeviceWaitIdle(device);
        if (slot.image_available_sem) {
            vk.vkDestroySemaphore(device, slot.image_available_sem, nullptr);
            slot.image_available_sem = nullptr;
        }
        vk::VkSemaphoreCreateInfo semci{};
        semci.sType = vk::VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        vk.vkCreateSemaphore(device, &semci, nullptr, &slot.image_available_sem);
    }

    bool create_image_2d(
        uint32_t w,
        uint32_t h,
        vk::VkFormat fmt,
        vk::VkFlags samples,
        vk::VkFlags usage,
        vk::VkFlags mem_flags,
        vk::VkImage& out_img,
        vk::VkDeviceMemory& out_mem
    ) {
        vk::VkImageCreateInfo ici{};
        ici.sType         = vk::VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        ici.imageType     = vk::VK_IMAGE_TYPE_2D;
        ici.format        = fmt;
        ici.extent        = {w, h, 1u};
        ici.mipLevels     = 1u;
        ici.arrayLayers   = 1u;
        ici.samples       = samples;
        ici.tiling        = vk::VK_IMAGE_TILING_OPTIMAL;
        ici.usage         = usage;
        ici.sharingMode   = vk::VK_SHARING_MODE_EXCLUSIVE;
        ici.initialLayout = vk::VK_IMAGE_LAYOUT_UNDEFINED;
        if (vk.vkCreateImage(device, &ici, nullptr, &out_img) != vk::VK_SUCCESS || !out_img) {
            return false;
        }
        vk::VkMemoryRequirements req{};
        vk.vkGetImageMemoryRequirements(device, out_img, &req);
        const uint32_t mem_idx = find_memory_type(req.memoryTypeBits, mem_flags);
        if (mem_idx == ~0u) {
            vk.vkDestroyImage(device, out_img, nullptr);
            out_img = nullptr;
            return false;
        }
        vk::VkMemoryAllocateInfo mai{};
        mai.sType           = vk::VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        mai.allocationSize  = req.size;
        mai.memoryTypeIndex = mem_idx;
        if (vk.vkAllocateMemory(device, &mai, nullptr, &out_mem) != vk::VK_SUCCESS || !out_mem) {
            vk.vkDestroyImage(device, out_img, nullptr);
            out_img = nullptr;
            return false;
        }
        if (vk.vkBindImageMemory(device, out_img, out_mem, 0) != vk::VK_SUCCESS) {
            vk.vkDestroyImage(device, out_img, nullptr);
            vk.vkFreeMemory(device, out_mem, nullptr);
            out_img = nullptr;
            out_mem = nullptr;
            return false;
        }
        return true;
    }

    vk::VkImageView create_image_view_2d(vk::VkImage img, vk::VkFormat fmt, vk::VkFlags aspect) {
        vk::VkImageViewCreateInfo ivci{};
        ivci.sType                           = vk::VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        ivci.image                           = img;
        ivci.viewType                        = vk::VK_IMAGE_VIEW_TYPE_2D;
        ivci.format                          = fmt;
        ivci.subresourceRange.aspectMask     = aspect;
        ivci.subresourceRange.baseMipLevel   = 0u;
        ivci.subresourceRange.levelCount     = 1u;
        ivci.subresourceRange.baseArrayLayer = 0u;
        ivci.subresourceRange.layerCount     = 1u;
        vk::VkImageView view = nullptr;
        if (vk.vkCreateImageView(device, &ivci, nullptr, &view) != vk::VK_SUCCESS) {
            return nullptr;
        }
        return view;
    }

    void destroy_image(vk::VkImage& img, vk::VkDeviceMemory& mem, vk::VkImageView& view) {
        if (view) { vk.vkDestroyImageView(device, view, nullptr); view = nullptr; }
        if (img)  { vk.vkDestroyImage(device, img, nullptr);       img  = nullptr; }
        if (mem)  { vk.vkFreeMemory(device, mem, nullptr);         mem  = nullptr; }
    }

    void cmd_barrier_image(
        vk::VkCommandBuffer cmd,
        vk::VkImage img,
        vk::VkFlags aspect,
        vk::VkImageLayout old_layout,
        vk::VkImageLayout new_layout,
        vk::VkFlags src_access,
        vk::VkFlags dst_access,
        vk::VkFlags src_stage,
        vk::VkFlags dst_stage
    ) {
        vk::VkImageMemoryBarrier b{};
        b.sType                           = vk::VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        b.srcAccessMask                   = src_access;
        b.dstAccessMask                   = dst_access;
        b.oldLayout                       = old_layout;
        b.newLayout                       = new_layout;
        b.srcQueueFamilyIndex             = vk::VK_QUEUE_FAMILY_IGNORED;
        b.dstQueueFamilyIndex             = vk::VK_QUEUE_FAMILY_IGNORED;
        b.image                           = img;
        b.subresourceRange.aspectMask     = aspect;
        b.subresourceRange.baseMipLevel   = 0u;
        b.subresourceRange.levelCount     = 1u;
        b.subresourceRange.baseArrayLayer = 0u;
        b.subresourceRange.layerCount     = 1u;
        vk.vkCmdPipelineBarrier(cmd, src_stage, dst_stage, 0u, 0u, nullptr, 0u, nullptr, 1u, &b);
    }

    bool stage_texture_rgba8(
        uint32_t w,
        uint32_t h,
        const uint8_t* rgba,
        CachedTexture& out_tex,
        std::vector<PendingImageUpload>& pending
    ) {
        if (w == 0u || h == 0u || !rgba) return false;
        const size_t byte_len = static_cast<size_t>(w) * h * 4u;

        vk::VkBuffer staging_buf = nullptr;
        vk::VkDeviceMemory staging_mem = nullptr;
        if (!create_buffer(
                byte_len,
                vk::VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                vk::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | vk::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                staging_buf,
                staging_mem)) {
            return false;
        }
        void* mapped = nullptr;
        if (vk.vkMapMemory(device, staging_mem, 0, byte_len, 0, &mapped) != vk::VK_SUCCESS || !mapped) {
            destroy_buffer(staging_buf, staging_mem);
            return false;
        }
        std::memcpy(mapped, rgba, byte_len);
        vk.vkUnmapMemory(device, staging_mem);

        if (!create_image_2d(
                w, h,
                vk::VK_FORMAT_R8G8B8A8_UNORM,
                vk::VK_SAMPLE_COUNT_1_BIT,
                vk::VK_IMAGE_USAGE_TRANSFER_DST_BIT | vk::VK_IMAGE_USAGE_SAMPLED_BIT,
                vk::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                out_tex.img,
                out_tex.mem)) {
            destroy_buffer(staging_buf, staging_mem);
            return false;
        }
        out_tex.view = create_image_view_2d(out_tex.img, vk::VK_FORMAT_R8G8B8A8_UNORM, vk::VK_IMAGE_ASPECT_COLOR_BIT);
        if (!out_tex.view) {
            destroy_image(out_tex.img, out_tex.mem, out_tex.view);
            destroy_buffer(staging_buf, staging_mem);
            return false;
        }
        out_tex.w               = w;
        out_tex.h               = h;
        out_tex.byte_size       = byte_len;
        out_tex.last_used_frame = cache_frame_tick;
        pending.push_back({out_tex.img, staging_buf, staging_mem, w, h});
        return true;
    }

    void record_pending_uploads(vk::VkCommandBuffer cmd, std::vector<PendingImageUpload>& pending, FrameSlot& slot) {
        for (const auto& up : pending) {
            cmd_barrier_image(
                cmd, up.img, vk::VK_IMAGE_ASPECT_COLOR_BIT,
                vk::VK_IMAGE_LAYOUT_UNDEFINED,
                vk::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                0u, vk::VK_ACCESS_TRANSFER_WRITE_BIT,
                vk::VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                vk::VK_PIPELINE_STAGE_TRANSFER_BIT);

            vk::VkBufferImageCopy region{};
            region.imageSubresource.aspectMask = vk::VK_IMAGE_ASPECT_COLOR_BIT;
            region.imageSubresource.layerCount = 1u;
            region.imageExtent                 = {up.w, up.h, 1u};
            vk.vkCmdCopyBufferToImage(cmd, up.staging_buf, up.img, vk::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1u, &region);

            cmd_barrier_image(
                cmd, up.img, vk::VK_IMAGE_ASPECT_COLOR_BIT,
                vk::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                vk::VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
                vk::VK_ACCESS_TRANSFER_WRITE_BIT, vk::VK_ACCESS_SHADER_READ_BIT,
                vk::VK_PIPELINE_STAGE_TRANSFER_BIT,
                vk::VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);

            slot.staging_garbage.push_back({up.staging_buf, up.staging_mem});
        }
        pending.clear();
    }

    template <typename Fn>
    bool submit_one_time_commands(Fn&& fn) {
        if (!one_time_cmd) {
            vk::VkCommandBufferAllocateInfo cbai{};
            cbai.sType              = vk::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            cbai.commandPool        = cmd_pool;
            cbai.level              = 0u;
            cbai.commandBufferCount = 1u;
            if (vk.vkAllocateCommandBuffers(device, &cbai, &one_time_cmd) != vk::VK_SUCCESS || !one_time_cmd) {
                return false;
            }
        }
        vk.vkResetCommandBuffer(one_time_cmd, 0u);
        vk::VkCommandBufferBeginInfo bi{};
        bi.sType = vk::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        bi.flags = vk::VK_COMMAND_BUFFER_USAGE_ONE_TIME_BIT;
        vk.vkBeginCommandBuffer(one_time_cmd, &bi);
        fn(one_time_cmd);
        vk.vkEndCommandBuffer(one_time_cmd);

        vk::VkSubmitInfo si{};
        si.sType              = vk::VK_STRUCTURE_TYPE_SUBMIT_INFO;
        si.commandBufferCount = 1u;
        si.pCommandBuffers    = &one_time_cmd;
        const bool ok = (vk.vkQueueSubmit(graphics_queue, 1u, &si, nullptr) == vk::VK_SUCCESS);
        vk.vkQueueWaitIdle(graphics_queue);
        return ok;
    }

    vk::VkShaderModule create_shader_module(const uint32_t* words, size_t word_count) {
        vk::VkShaderModuleCreateInfo smci{};
        smci.sType    = vk::VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        smci.codeSize = word_count * sizeof(uint32_t);
        smci.pCode    = words;
        vk::VkShaderModule sm = nullptr;
        if (vk.vkCreateShaderModule(device, &smci, nullptr, &sm) != vk::VK_SUCCESS) {
            return nullptr;
        }
        return sm;
    }

    bool allocate_gx_descriptor_pool() {
        vk::VkDescriptorPoolSize pool_sizes[2]{};
        pool_sizes[0] = {vk::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, kDescPoolChunkSets};
        pool_sizes[1] = {vk::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, kDescPoolChunkSets * 2u};
        vk::VkDescriptorPoolCreateInfo dpci{};
        dpci.sType         = vk::VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        dpci.maxSets       = kDescPoolChunkSets;
        dpci.poolSizeCount = 2u;
        dpci.pPoolSizes    = pool_sizes;
        vk::VkDescriptorPool pool = nullptr;
        if (vk.vkCreateDescriptorPool(device, &dpci, nullptr, &pool) != vk::VK_SUCCESS || !pool) {
            return false;
        }
        gx_desc_pools.push_back(pool);
        return true;
    }

    vk::VkDescriptorSet get_or_create_gx_desc_set(
        vk::VkImageView view0,
        uint32_t samp0_idx,
        vk::VkImageView view1,
        uint32_t samp1_idx
    ) {
        if (!view0) view0 = default_white_tex.view;
        if (!view1) view1 = default_white_tex.view;
        const uint32_t s0 = (samp0_idx < 9u && samplers[samp0_idx]) ? samp0_idx : 4u;
        const uint32_t s1 = (samp1_idx < 9u && samplers[samp1_idx]) ? samp1_idx : 4u;
        const TexDescKey key{
            reinterpret_cast<uint64_t>(view0),
            reinterpret_cast<uint64_t>(view1),
            s0,
            s1
        };
        auto it = tex_desc_cache.find(key);
        if (it != tex_desc_cache.end()) {
            return it->second;
        }

        if (gx_desc_pools.empty() && !allocate_gx_descriptor_pool()) {
            return nullptr;
        }
        vk::VkDescriptorSetAllocateInfo dsai{};
        dsai.sType              = vk::VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        dsai.descriptorPool     = gx_desc_pools.back();
        dsai.descriptorSetCount = 1u;
        dsai.pSetLayouts        = &gx_dsl;
        vk::VkDescriptorSet ds = nullptr;
        if (vk.vkAllocateDescriptorSets(device, &dsai, &ds) != vk::VK_SUCCESS) {
            if (!allocate_gx_descriptor_pool()) {
                return nullptr;
            }
            dsai.descriptorPool = gx_desc_pools.back();
            if (vk.vkAllocateDescriptorSets(device, &dsai, &ds) != vk::VK_SUCCESS || !ds) {
                return nullptr;
            }
        }

        vk::VkDescriptorBufferInfo buf_info{};
        buf_info.buffer = gx_ubo_buf;
        buf_info.offset = 0u;
        buf_info.range  = sizeof(GXSceneConstantsCPU);

        vk::VkDescriptorImageInfo img0{};
        img0.sampler     = samplers[s0] ? samplers[s0] : sampler_linear_clamp;
        img0.imageView   = view0;
        img0.imageLayout = vk::VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

        vk::VkDescriptorImageInfo img1{};
        img1.sampler     = samplers[s1] ? samplers[s1] : sampler_linear_clamp;
        img1.imageView   = view1;
        img1.imageLayout = vk::VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

        vk::VkWriteDescriptorSet writes[3]{};
        writes[0].sType           = vk::VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writes[0].dstSet          = ds;
        writes[0].dstBinding      = 0u;
        writes[0].descriptorCount = 1u;
        writes[0].descriptorType  = vk::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
        writes[0].pBufferInfo     = &buf_info;

        writes[1].sType           = vk::VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writes[1].dstSet          = ds;
        writes[1].dstBinding      = 1u;
        writes[1].descriptorCount = 1u;
        writes[1].descriptorType  = vk::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        writes[1].pImageInfo      = &img0;

        writes[2].sType           = vk::VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writes[2].dstSet          = ds;
        writes[2].dstBinding      = 2u;
        writes[2].descriptorCount = 1u;
        writes[2].descriptorType  = vk::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        writes[2].pImageInfo      = &img1;

        vk.vkUpdateDescriptorSets(device, 3u, writes, 0u, nullptr);
        tex_desc_cache[key] = ds;
        return ds;
    }

    vk::VkImageView get_or_create_gc_texture_view(
        const Memory& mem,
        const GX3DInterface& gx,
        const GXBoundTexture& tex,
        const GXTlutSlot& tlut,
        std::vector<PendingImageUpload>& pending
    ) {
        if (tex.width == 0u || tex.height == 0u || tex.data_vaddr < kGcRamBase) {
            return default_white_tex.view;
        }
        const uint64_t key =
            (static_cast<uint64_t>(tex.data_vaddr) << 32) ^
            (static_cast<uint64_t>(tlut.data_vaddr & 0xFFFFFu) << 12) ^
            (static_cast<uint64_t>(tex.width) << 16) ^
            static_cast<uint64_t>(tex.height) ^
            (static_cast<uint64_t>(tex.format & 0xFu) << 28);
        auto it = tex_cache.find(key);
        if (it != tex_cache.end()) {
            it->second.last_used_frame = cache_frame_tick;
            return it->second.view;
        }
        std::vector<uint8_t> rgba = gx.decode_gc_texture_to_rgba8(mem, tex, &tlut);
        const size_t new_bytes = static_cast<size_t>(tex.width) * tex.height * 4u;
        if (rgba.size() != new_bytes) {
            return default_white_tex.view;
        }

        auto& cur_slot = frames[frame_cursor % kMaxFramesInFlight];
        while (!tex_cache.empty() &&
               (tex_cache.size() >= kMaxCachedGcTextures || tex_cache_bytes + new_bytes > kMaxCachedGcTextureBytes)) {
            auto oldest_it = tex_cache.end();
            uint64_t oldest_frame = ~0ULL;
            for (auto cit = tex_cache.begin(); cit != tex_cache.end(); ++cit) {
                if (cit->second.last_used_frame < cache_frame_tick && cit->second.last_used_frame < oldest_frame) {
                    oldest_frame = cit->second.last_used_frame;
                    oldest_it    = cit;
                }
            }
            if (oldest_it == tex_cache.end()) {
                break; // All cached textures are actively referenced by the current frame
            }
            if (tex_cache_bytes >= oldest_it->second.byte_size) {
                tex_cache_bytes -= oldest_it->second.byte_size;
            } else {
                tex_cache_bytes = 0u;
            }
            erase_desc_cache_for_view(oldest_it->second.view);
            cur_slot.retired_textures.push_back(oldest_it->second);
            tex_cache.erase(oldest_it);
        }

        CachedTexture ct{};
        if (!stage_texture_rgba8(tex.width, tex.height, rgba.data(), ct, pending)) {
            return default_white_tex.view;
        }
        tex_cache_bytes += ct.byte_size;
        tex_cache[key] = ct;
        return ct.view;
    }

    vk::VkImageView get_or_create_text_view(
        const std::string& utf8_text,
        int& out_w,
        int& out_h,
        std::vector<PendingImageUpload>& pending
    ) {
        auto it = text_cache.find(utf8_text);
        if (it != text_cache.end()) {
            it->second.last_used_frame = cache_frame_tick;
            out_w = static_cast<int>(it->second.w);
            out_h = static_cast<int>(it->second.h);
            return it->second.view;
        }
        if (utf8_text.empty()) return nullptr;
#ifdef _WIN32
        int bw = 0, bh = 0;
        std::vector<uint8_t> rgba;
        if (!rasterize_utf8_text_rgba8(utf8_text, bw, bh, rgba)) {
            return nullptr;
        }

        auto& cur_slot = frames[frame_cursor % kMaxFramesInFlight];
        while (!text_cache.empty() && text_cache.size() >= kMaxCachedTextTextures) {
            auto oldest_it = text_cache.end();
            uint64_t oldest_frame = ~0ULL;
            for (auto cit = text_cache.begin(); cit != text_cache.end(); ++cit) {
                if (cit->second.last_used_frame < cache_frame_tick && cit->second.last_used_frame < oldest_frame) {
                    oldest_frame = cit->second.last_used_frame;
                    oldest_it    = cit;
                }
            }
            if (oldest_it == text_cache.end()) {
                break;
            }
            erase_desc_cache_for_view(oldest_it->second.view);
            cur_slot.retired_textures.push_back(oldest_it->second);
            text_cache.erase(oldest_it);
        }

        CachedTexture ct{};
        if (!stage_texture_rgba8(static_cast<uint32_t>(bw), static_cast<uint32_t>(bh), rgba.data(), ct, pending)) {
            return nullptr;
        }
        text_cache[utf8_text] = ct;
        out_w = bw;
        out_h = bh;
        return ct.view;
#else
        (void)out_w; (void)out_h; (void)pending;
        return nullptr;
#endif
    }

    vk::VkPipeline create_gx_pipeline(
        vk::VkRenderPass rp,
        vk::VkFlags samples,
        uint32_t cull_idx,
        uint32_t depth_idx,
        uint32_t blend_idx
    ) {
        vk::VkPipelineShaderStageCreateInfo stages[2]{};
        stages[0].sType  = vk::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stages[0].stage  = vk::VK_SHADER_STAGE_VERTEX_BIT;
        stages[0].module = sm_gx_vs;
        stages[0].pName  = "main";
        stages[1].sType  = vk::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stages[1].stage  = vk::VK_SHADER_STAGE_FRAGMENT_BIT;
        stages[1].module = sm_gx_fs;
        stages[1].pName  = "main";

        vk::VkVertexInputBindingDescription vbd{};
        vbd.binding   = 0u;
        vbd.stride    = sizeof(GXVertex);
        vbd.inputRate = vk::VK_VERTEX_INPUT_RATE_VERTEX;

        vk::VkVertexInputAttributeDescription attrs[3]{};
        attrs[0] = {0u, 0u, vk::VK_FORMAT_R32G32B32_SFLOAT,    static_cast<uint32_t>(offsetof(GXVertex, pos))};
        attrs[1] = {2u, 0u, vk::VK_FORMAT_R32G32B32A32_SFLOAT, static_cast<uint32_t>(offsetof(GXVertex, color0))};
        attrs[2] = {3u, 0u, vk::VK_FORMAT_R32G32_SFLOAT,       static_cast<uint32_t>(offsetof(GXVertex, uv0))};

        vk::VkPipelineVertexInputStateCreateInfo vi{};
        vi.sType                           = vk::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vi.vertexBindingDescriptionCount   = 1u;
        vi.pVertexBindingDescriptions      = &vbd;
        vi.vertexAttributeDescriptionCount = 3u;
        vi.pVertexAttributeDescriptions    = attrs;

        vk::VkPipelineInputAssemblyStateCreateInfo ia{};
        ia.sType    = vk::VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        ia.topology = vk::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

        vk::VkPipelineViewportStateCreateInfo vp{};
        vp.sType         = vk::VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        vp.viewportCount = 1u;
        vp.scissorCount  = 1u;

        vk::VkPipelineRasterizationStateCreateInfo rs{};
        rs.sType       = vk::VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rs.polygonMode = vk::VK_POLYGON_MODE_FILL;
        rs.cullMode    = (cull_idx == 1u) ? vk::VK_CULL_MODE_FRONT_BIT :
                         (cull_idx == 2u) ? vk::VK_CULL_MODE_BACK_BIT  : vk::VK_CULL_MODE_NONE;
        rs.frontFace   = vk::VK_FRONT_FACE_CLOCKWISE;
        rs.lineWidth   = 1.0f;

        vk::VkPipelineMultisampleStateCreateInfo ms{};
        ms.sType                = vk::VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        ms.rasterizationSamples = samples;

        vk::VkPipelineDepthStencilStateCreateInfo ds{};
        ds.sType            = vk::VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        ds.depthTestEnable  = (depth_idx > 0u) ? vk::VK_TRUE : vk::VK_FALSE;
        ds.depthWriteEnable = (depth_idx == 2u) ? vk::VK_TRUE : vk::VK_FALSE;
        ds.depthCompareOp   = vk::VK_COMPARE_OP_LESS_OR_EQUAL;

        vk::VkPipelineColorBlendAttachmentState cba{};
        cba.colorWriteMask      = vk::VK_COLOR_COMPONENT_ALL;
        cba.blendEnable         = (blend_idx > 0u) ? vk::VK_TRUE : vk::VK_FALSE;
        cba.srcColorBlendFactor = vk::VK_BLEND_FACTOR_SRC_ALPHA;
        cba.dstColorBlendFactor = (blend_idx == 2u) ? vk::VK_BLEND_FACTOR_ONE : vk::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        cba.colorBlendOp        = vk::VK_BLEND_OP_ADD;
        cba.srcAlphaBlendFactor = vk::VK_BLEND_FACTOR_ONE;
        cba.dstAlphaBlendFactor = vk::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
        cba.alphaBlendOp        = vk::VK_BLEND_OP_ADD;

        vk::VkPipelineColorBlendStateCreateInfo cb{};
        cb.sType           = vk::VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        cb.attachmentCount = 1u;
        cb.pAttachments    = &cba;

        const vk::VkDynamicState dyn_states[2] = {vk::VK_DYNAMIC_STATE_VIEWPORT, vk::VK_DYNAMIC_STATE_SCISSOR};
        vk::VkPipelineDynamicStateCreateInfo dyn{};
        dyn.sType             = vk::VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dyn.dynamicStateCount = 2u;
        dyn.pDynamicStates    = dyn_states;

        vk::VkGraphicsPipelineCreateInfo gpci{};
        gpci.sType               = vk::VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        gpci.stageCount          = 2u;
        gpci.pStages             = stages;
        gpci.pVertexInputState   = &vi;
        gpci.pInputAssemblyState = &ia;
        gpci.pViewportState      = &vp;
        gpci.pRasterizationState = &rs;
        gpci.pMultisampleState   = &ms;
        gpci.pDepthStencilState  = &ds;
        gpci.pColorBlendState    = &cb;
        gpci.pDynamicState       = &dyn;
        gpci.layout              = gx_pl;
        gpci.renderPass          = rp;
        gpci.subpass             = 0u;
        gpci.basePipelineIndex   = -1;

        vk::VkPipeline pipe = nullptr;
        if (vk.vkCreateGraphicsPipelines(device, nullptr, 1u, &gpci, nullptr, &pipe) != vk::VK_SUCCESS) {
            return nullptr;
        }
        return pipe;
    }

    vk::VkPipeline get_or_create_gx_pipeline(
        uint32_t msaa_samples,
        uint32_t cull_idx,
        uint32_t depth_idx,
        uint32_t blend_idx
    ) {
        const uint32_t c = (cull_idx <= 2u) ? cull_idx : 0u;
        const uint32_t d = (depth_idx <= 2u) ? depth_idx : 1u;
        const uint32_t b = (blend_idx <= 2u) ? blend_idx : 1u;
        if (!gx_pipelines[c][d][b]) {
            gx_pipelines[c][d][b] = create_gx_pipeline(
                efb_render_pass, sample_count_to_vk(msaa_samples), c, d, b);
        }
        return gx_pipelines[c][d][b];
    }

    vk::VkPipeline create_fullscreen_pipeline(vk::VkShaderModule fs_mod) {
        vk::VkPipelineShaderStageCreateInfo stages[2]{};
        stages[0].sType  = vk::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stages[0].stage  = vk::VK_SHADER_STAGE_VERTEX_BIT;
        stages[0].module = sm_fxaa_vs;
        stages[0].pName  = "main";
        stages[1].sType  = vk::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        stages[1].stage  = vk::VK_SHADER_STAGE_FRAGMENT_BIT;
        stages[1].module = fs_mod;
        stages[1].pName  = "main";

        vk::VkPipelineVertexInputStateCreateInfo vi{};
        vi.sType = vk::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        vk::VkPipelineInputAssemblyStateCreateInfo ia{};
        ia.sType    = vk::VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        ia.topology = vk::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

        vk::VkPipelineViewportStateCreateInfo vp{};
        vp.sType         = vk::VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        vp.viewportCount = 1u;
        vp.scissorCount  = 1u;

        vk::VkPipelineRasterizationStateCreateInfo rs{};
        rs.sType       = vk::VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rs.polygonMode = vk::VK_POLYGON_MODE_FILL;
        rs.cullMode    = vk::VK_CULL_MODE_NONE;
        rs.frontFace   = vk::VK_FRONT_FACE_CLOCKWISE;
        rs.lineWidth   = 1.0f;

        vk::VkPipelineMultisampleStateCreateInfo ms{};
        ms.sType                = vk::VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        ms.rasterizationSamples = vk::VK_SAMPLE_COUNT_1_BIT;

        vk::VkPipelineDepthStencilStateCreateInfo ds{};
        ds.sType          = vk::VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        ds.depthCompareOp = vk::VK_COMPARE_OP_ALWAYS;

        vk::VkPipelineColorBlendAttachmentState cba{};
        cba.colorWriteMask = vk::VK_COLOR_COMPONENT_ALL;
        vk::VkPipelineColorBlendStateCreateInfo cb{};
        cb.sType           = vk::VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        cb.attachmentCount = 1u;
        cb.pAttachments    = &cba;

        const vk::VkDynamicState dyn_states[2] = {vk::VK_DYNAMIC_STATE_VIEWPORT, vk::VK_DYNAMIC_STATE_SCISSOR};
        vk::VkPipelineDynamicStateCreateInfo dyn{};
        dyn.sType             = vk::VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dyn.dynamicStateCount = 2u;
        dyn.pDynamicStates    = dyn_states;

        vk::VkGraphicsPipelineCreateInfo gpci{};
        gpci.sType               = vk::VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        gpci.stageCount          = 2u;
        gpci.pStages             = stages;
        gpci.pVertexInputState   = &vi;
        gpci.pInputAssemblyState = &ia;
        gpci.pViewportState      = &vp;
        gpci.pRasterizationState = &rs;
        gpci.pMultisampleState   = &ms;
        gpci.pDepthStencilState  = &ds;
        gpci.pColorBlendState    = &cb;
        gpci.pDynamicState       = &dyn;
        gpci.layout              = fxaa_pl;
        gpci.renderPass          = present_render_pass;
        gpci.subpass             = 0u;
        gpci.basePipelineIndex   = -1;

        vk::VkPipeline pipe = nullptr;
        if (vk.vkCreateGraphicsPipelines(device, nullptr, 1u, &gpci, nullptr, &pipe) != vk::VK_SUCCESS) {
            return nullptr;
        }
        return pipe;
    }

    void update_fxaa_descriptor_sets() {
        if (!efb_resolved_view || !sampler_linear_clamp) return;
        for (uint32_t i = 0u; i < kMaxFramesInFlight; ++i) {
            if (!frames[i].fxaa_desc_set || !frames[i].fxaa_ubo) continue;
            vk::VkDescriptorBufferInfo bi{frames[i].fxaa_ubo, 0u, sizeof(FxaaConstantsCPU)};
            vk::VkDescriptorImageInfo ii{
                sampler_linear_clamp, efb_resolved_view, vk::VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL};
            vk::VkWriteDescriptorSet writes[2]{};
            writes[0].sType           = vk::VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            writes[0].dstSet          = frames[i].fxaa_desc_set;
            writes[0].dstBinding      = 0u;
            writes[0].descriptorCount = 1u;
            writes[0].descriptorType  = vk::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            writes[0].pBufferInfo     = &bi;

            writes[1].sType           = vk::VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            writes[1].dstSet          = frames[i].fxaa_desc_set;
            writes[1].dstBinding      = 1u;
            writes[1].descriptorCount = 1u;
            writes[1].descriptorType  = vk::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            writes[1].pImageInfo      = &ii;
            vk.vkUpdateDescriptorSets(device, 2u, writes, 0u, nullptr);
        }
    }

    void destroy_gx_pipelines() {
        for (uint32_t c = 0; c < 3u; ++c) {
            for (uint32_t d = 0; d < 3u; ++d) {
                for (uint32_t b = 0; b < 3u; ++b) {
                    if (gx_pipelines[c][d][b]) {
                        vk.vkDestroyPipeline(device, gx_pipelines[c][d][b], nullptr);
                        gx_pipelines[c][d][b] = nullptr;
                    }
                }
            }
        }
    }
};

Win32VulkanHost::Win32VulkanHost(RuntimeConfig& cfg) : cfg_(cfg), impl_(new Impl()) {}

Win32VulkanHost::~Win32VulkanHost() {
    if (!impl_) return;
#ifdef _WIN32
    if (impl_->device) {
        impl_->vk.vkDeviceWaitIdle(impl_->device);

        for (auto& kv : impl_->tex_cache) {
            impl_->destroy_image(kv.second.img, kv.second.mem, kv.second.view);
        }
        impl_->tex_cache.clear();
        for (auto& kv : impl_->text_cache) {
            impl_->destroy_image(kv.second.img, kv.second.mem, kv.second.view);
        }
        impl_->text_cache.clear();
        impl_->destroy_image(
            impl_->default_white_tex.img,
            impl_->default_white_tex.mem,
            impl_->default_white_tex.view);

        impl_->destroy_gx_pipelines();
        if (impl_->overlay_pipeline) { impl_->vk.vkDestroyPipeline(impl_->device, impl_->overlay_pipeline, nullptr); impl_->overlay_pipeline = nullptr; }
        if (impl_->fxaa_pipeline)    { impl_->vk.vkDestroyPipeline(impl_->device, impl_->fxaa_pipeline, nullptr);    impl_->fxaa_pipeline    = nullptr; }
        if (impl_->blit_pipeline)    { impl_->vk.vkDestroyPipeline(impl_->device, impl_->blit_pipeline, nullptr);    impl_->blit_pipeline    = nullptr; }

        destroy_offscreen_efb();
        destroy_swapchain_and_views();

        for (auto& f : impl_->frames) {
            impl_->free_staging_garbage(f);
            impl_->destroy_buffer(f.dyn_vb, f.dyn_vb_mem, &f.dyn_vb_mapped);
            impl_->destroy_buffer(f.dyn_ib, f.dyn_ib_mem, &f.dyn_ib_mapped);
            impl_->destroy_buffer(f.fxaa_ubo, f.fxaa_ubo_mem, &f.fxaa_ubo_mapped);
            if (f.image_available_sem) { impl_->vk.vkDestroySemaphore(impl_->device, f.image_available_sem, nullptr); f.image_available_sem = nullptr; }
            if (f.in_flight_fence)     { impl_->vk.vkDestroyFence(impl_->device, f.in_flight_fence, nullptr);         f.in_flight_fence     = nullptr; }
        }
        impl_->destroy_buffer(impl_->gx_ubo_buf, impl_->gx_ubo_mem, &impl_->gx_ubo_mapped);

        for (uint32_t i = 0; i < 9u; ++i) {
            if (impl_->samplers[i]) { impl_->vk.vkDestroySampler(impl_->device, impl_->samplers[i], nullptr); impl_->samplers[i] = nullptr; }
        }
        if (impl_->sampler_linear_clamp) {
            impl_->vk.vkDestroySampler(impl_->device, impl_->sampler_linear_clamp, nullptr);
            impl_->sampler_linear_clamp = nullptr;
        }

        for (auto dp : impl_->gx_desc_pools) {
            if (dp) impl_->vk.vkDestroyDescriptorPool(impl_->device, dp, nullptr);
        }
        impl_->gx_desc_pools.clear();
        impl_->tex_desc_cache.clear();
        if (impl_->fxaa_desc_pool) { impl_->vk.vkDestroyDescriptorPool(impl_->device, impl_->fxaa_desc_pool, nullptr); impl_->fxaa_desc_pool = nullptr; }

        if (impl_->gx_pl)    { impl_->vk.vkDestroyPipelineLayout(impl_->device, impl_->gx_pl, nullptr);          impl_->gx_pl    = nullptr; }
        if (impl_->fxaa_pl)  { impl_->vk.vkDestroyPipelineLayout(impl_->device, impl_->fxaa_pl, nullptr);        impl_->fxaa_pl  = nullptr; }
        if (impl_->gx_dsl)   { impl_->vk.vkDestroyDescriptorSetLayout(impl_->device, impl_->gx_dsl, nullptr);    impl_->gx_dsl   = nullptr; }
        if (impl_->fxaa_dsl) { impl_->vk.vkDestroyDescriptorSetLayout(impl_->device, impl_->fxaa_dsl, nullptr);  impl_->fxaa_dsl = nullptr; }

        if (impl_->sm_gx_vs)   { impl_->vk.vkDestroyShaderModule(impl_->device, impl_->sm_gx_vs, nullptr);   impl_->sm_gx_vs   = nullptr; }
        if (impl_->sm_gx_fs)   { impl_->vk.vkDestroyShaderModule(impl_->device, impl_->sm_gx_fs, nullptr);   impl_->sm_gx_fs   = nullptr; }
        if (impl_->sm_fxaa_vs) { impl_->vk.vkDestroyShaderModule(impl_->device, impl_->sm_fxaa_vs, nullptr); impl_->sm_fxaa_vs = nullptr; }
        if (impl_->sm_blit_fs) { impl_->vk.vkDestroyShaderModule(impl_->device, impl_->sm_blit_fs, nullptr); impl_->sm_blit_fs = nullptr; }
        if (impl_->sm_fxaa_fs) { impl_->vk.vkDestroyShaderModule(impl_->device, impl_->sm_fxaa_fs, nullptr); impl_->sm_fxaa_fs = nullptr; }

        if (impl_->cmd_pool) { impl_->vk.vkDestroyCommandPool(impl_->device, impl_->cmd_pool, nullptr); impl_->cmd_pool = nullptr; }
        impl_->vk.vkDestroyDevice(impl_->device, nullptr);
        impl_->device = nullptr;
    }
    if (impl_->instance) {
        if (impl_->surface && impl_->vk.vkDestroySurfaceKHR) {
            impl_->vk.vkDestroySurfaceKHR(impl_->instance, impl_->surface, nullptr);
            impl_->surface = nullptr;
        }
        impl_->vk.vkDestroyInstance(impl_->instance, nullptr);
        impl_->instance = nullptr;
    }
    impl_->vk.unload();
    if (hwnd_) {
        HWND hwnd = static_cast<HWND>(hwnd_);
        hwnd_ = nullptr;
        if (IsWindow(hwnd)) {
            DestroyWindow(hwnd);
        }
    }
#endif
    delete impl_;
    impl_ = nullptr;
}

void Win32VulkanHost::enable_process_dpi_awareness() {
    enable_host_dpi_awareness();
}

bool Win32VulkanHost::show_prelaunch_settings_window() {
#ifdef _WIN32
    return show_iso_picker_if_empty(cfg_);
#else
    return true;
#endif
}

bool Win32VulkanHost::pump_messages() {
#ifdef _WIN32
    std::string stop_reason;
    if (!pump_win32_window_messages(static_cast<HWND>(hwnd_), close_requested_, &stop_reason)) {
        if (!stop_reason.empty()) {
            PN03_LOG(LogLevel::Info, "VULKAN", stop_reason);
        }
        return false;
    }
#endif
    return true;
}

void Win32VulkanHost::handle_window_resize(uint32_t width, uint32_t height) {
    if (!initialized_ || !impl_ || width == 0u || height == 0u) return;
    if (impl_->swapchain != nullptr && width == swapchain_width_ && height == swapchain_height_) return;
    recreate_swapchain_for_resize(width, height);
}

void Win32VulkanHost::destroy_swapchain_and_views() {
    if (!impl_ || !impl_->device) return;
    impl_->frame_submitted    = false;
    impl_->has_ever_submitted = false;
    for (auto fb : impl_->swapchain_fbs) {
        if (fb) impl_->vk.vkDestroyFramebuffer(impl_->device, fb, nullptr);
    }
    impl_->swapchain_fbs.clear();
    for (auto iv : impl_->swapchain_views) {
        if (iv) impl_->vk.vkDestroyImageView(impl_->device, iv, nullptr);
    }
    impl_->swapchain_views.clear();
    impl_->swapchain_images.clear();
    for (auto sem : impl_->render_finished_sems) {
        if (sem) impl_->vk.vkDestroySemaphore(impl_->device, sem, nullptr);
    }
    impl_->render_finished_sems.clear();

    if (impl_->overlay_pipeline) { impl_->vk.vkDestroyPipeline(impl_->device, impl_->overlay_pipeline, nullptr); impl_->overlay_pipeline = nullptr; }
    if (impl_->fxaa_pipeline)    { impl_->vk.vkDestroyPipeline(impl_->device, impl_->fxaa_pipeline, nullptr);    impl_->fxaa_pipeline    = nullptr; }
    if (impl_->blit_pipeline)    { impl_->vk.vkDestroyPipeline(impl_->device, impl_->blit_pipeline, nullptr);    impl_->blit_pipeline    = nullptr; }
    if (impl_->capture_render_pass) {
        impl_->vk.vkDestroyRenderPass(impl_->device, impl_->capture_render_pass, nullptr);
        impl_->capture_render_pass = nullptr;
    }
    if (impl_->present_render_pass) {
        impl_->vk.vkDestroyRenderPass(impl_->device, impl_->present_render_pass, nullptr);
        impl_->present_render_pass = nullptr;
    }
    if (impl_->swapchain) {
        impl_->vk.vkDestroySwapchainKHR(impl_->device, impl_->swapchain, nullptr);
        impl_->swapchain = nullptr;
    }
}

bool Win32VulkanHost::create_swapchain_and_views(std::string& err_msg) {
    vk::VkSurfaceCapabilitiesKHR caps{};
    if (impl_->vk.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(impl_->phys_dev, impl_->surface, &caps) != vk::VK_SUCCESS) {
        err_msg = "vkGetPhysicalDeviceSurfaceCapabilitiesKHR failed.";
        return false;
    }
    if (caps.maxImageExtent.width == 0u || caps.maxImageExtent.height == 0u ||
        (caps.currentExtent.width != 0xFFFFFFFFu && (caps.currentExtent.width == 0u || caps.currentExtent.height == 0u))) {
        err_msg = "Swapchain surface extent is 0x0 (window minimized).";
        return false;
    }

    uint32_t fmt_count = 0u;
    impl_->vk.vkGetPhysicalDeviceSurfaceFormatsKHR(impl_->phys_dev, impl_->surface, &fmt_count, nullptr);
    std::vector<vk::VkSurfaceFormatKHR> formats(fmt_count);
    if (fmt_count > 0u) {
        impl_->vk.vkGetPhysicalDeviceSurfaceFormatsKHR(impl_->phys_dev, impl_->surface, &fmt_count, formats.data());
    }
    vk::VkSurfaceFormatKHR chosen_fmt{vk::VK_FORMAT_B8G8R8A8_UNORM, vk::VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
    if (!formats.empty()) {
        chosen_fmt = formats[0];
        for (const auto& f : formats) {
            if (f.colorSpace == vk::VK_COLOR_SPACE_SRGB_NONLINEAR_KHR &&
                (f.format == vk::VK_FORMAT_B8G8R8A8_UNORM || f.format == vk::VK_FORMAT_R8G8B8A8_UNORM)) {
                chosen_fmt = f;
                break;
            }
        }
    }
    impl_->swapchain_fmt  = chosen_fmt.format;
    impl_->swapchain_bgra = (chosen_fmt.format == vk::VK_FORMAT_B8G8R8A8_UNORM);

    uint32_t pm_count = 0u;
    impl_->vk.vkGetPhysicalDeviceSurfacePresentModesKHR(impl_->phys_dev, impl_->surface, &pm_count, nullptr);
    std::vector<vk::VkPresentModeKHR> modes(pm_count);
    if (pm_count > 0u) {
        impl_->vk.vkGetPhysicalDeviceSurfacePresentModesKHR(impl_->phys_dev, impl_->surface, &pm_count, modes.data());
    }
    vk::VkPresentModeKHR chosen_pm = vk::VK_PRESENT_MODE_FIFO_KHR;
    const bool use_fifo = (cfg_.vsync && !cfg_.limit_fps_60);
    if (!use_fifo) {
        for (auto m : modes) {
            if (m == vk::VK_PRESENT_MODE_IMMEDIATE_KHR) {
                chosen_pm = m;
                break;
            }
            if (m == vk::VK_PRESENT_MODE_MAILBOX_KHR) {
                chosen_pm = m;
            }
        }
    }

    vk::VkExtent2D extent{swapchain_width_, swapchain_height_};
    if (caps.currentExtent.width != 0xFFFFFFFFu && caps.currentExtent.height != 0xFFFFFFFFu &&
        caps.currentExtent.width > 0u && caps.currentExtent.height > 0u) {
        extent = caps.currentExtent;
    } else {
        extent.width  = std::clamp(extent.width,  (std::max)(1u, caps.minImageExtent.width),  (std::max)(1u, caps.maxImageExtent.width));
        extent.height = std::clamp(extent.height, (std::max)(1u, caps.minImageExtent.height), (std::max)(1u, caps.maxImageExtent.height));
    }
    swapchain_width_  = extent.width;
    swapchain_height_ = extent.height;

    uint32_t min_imgs = (std::max)(2u, caps.minImageCount);
    if (caps.maxImageCount > 0u && min_imgs > caps.maxImageCount) {
        min_imgs = caps.maxImageCount;
    }
    vk::VkFlags img_usage = vk::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    if ((caps.supportedUsageFlags & vk::VK_IMAGE_USAGE_TRANSFER_SRC_BIT) != 0u) {
        img_usage |= vk::VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        impl_->swapchain_transfer_src = true;
    } else {
        impl_->swapchain_transfer_src = false;
    }

    vk::VkSwapchainCreateInfoKHR sci{};
    sci.sType            = vk::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    sci.surface          = impl_->surface;
    sci.minImageCount    = min_imgs;
    sci.imageFormat      = chosen_fmt.format;
    sci.imageColorSpace  = chosen_fmt.colorSpace;
    sci.imageExtent      = extent;
    sci.imageArrayLayers = 1u;
    sci.imageUsage       = img_usage;
    sci.imageSharingMode = vk::VK_SHARING_MODE_EXCLUSIVE;
    sci.preTransform     = caps.currentTransform;
    sci.compositeAlpha   = vk::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    sci.presentMode      = chosen_pm;
    sci.clipped          = vk::VK_TRUE;

    if (impl_->vk.vkCreateSwapchainKHR(impl_->device, &sci, nullptr, &impl_->swapchain) != vk::VK_SUCCESS ||
        !impl_->swapchain) {
        err_msg = "vkCreateSwapchainKHR failed.";
        return false;
    }

    uint32_t sc_count = 0u;
    impl_->vk.vkGetSwapchainImagesKHR(impl_->device, impl_->swapchain, &sc_count, nullptr);
    impl_->swapchain_images.resize(sc_count);
    if (sc_count == 0u ||
        impl_->vk.vkGetSwapchainImagesKHR(impl_->device, impl_->swapchain, &sc_count, impl_->swapchain_images.data()) != vk::VK_SUCCESS) {
        err_msg = "vkGetSwapchainImagesKHR failed.";
        return false;
    }

    impl_->swapchain_views.resize(sc_count, nullptr);
    impl_->render_finished_sems.resize(sc_count, nullptr);
    for (uint32_t i = 0u; i < sc_count; ++i) {
        impl_->swapchain_views[i] = impl_->create_image_view_2d(
            impl_->swapchain_images[i], impl_->swapchain_fmt, vk::VK_IMAGE_ASPECT_COLOR_BIT);
        vk::VkSemaphoreCreateInfo semci{};
        semci.sType = vk::VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        if (!impl_->swapchain_views[i] ||
            impl_->vk.vkCreateSemaphore(impl_->device, &semci, nullptr, &impl_->render_finished_sems[i]) != vk::VK_SUCCESS) {
            err_msg = "Failed to create swapchain image view or semaphore.";
            return false;
        }
    }

    // Present RenderPass: clear swapchain to black, run FXAA/Blit + overlays, leave in PRESENT_SRC_KHR
    vk::VkAttachmentDescription att{};
    att.format         = impl_->swapchain_fmt;
    att.samples        = vk::VK_SAMPLE_COUNT_1_BIT;
    att.loadOp         = vk::VK_ATTACHMENT_LOAD_OP_CLEAR;
    att.storeOp        = vk::VK_ATTACHMENT_STORE_OP_STORE;
    att.stencilLoadOp  = vk::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    att.stencilStoreOp = vk::VK_ATTACHMENT_STORE_OP_DONT_CARE;
    att.initialLayout  = vk::VK_IMAGE_LAYOUT_UNDEFINED;
    att.finalLayout    = vk::VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    vk::VkAttachmentReference color_ref{0u, vk::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    vk::VkSubpassDescription sp{};
    sp.colorAttachmentCount = 1u;
    sp.pColorAttachments    = &color_ref;

    vk::VkSubpassDependency dep{};
    dep.srcSubpass    = vk::VK_SUBPASS_EXTERNAL;
    dep.dstSubpass    = 0u;
    dep.srcStageMask  = vk::VK_PIPELINE_STAGE_COLOR_ATT_OUT_BIT;
    dep.dstStageMask  = vk::VK_PIPELINE_STAGE_COLOR_ATT_OUT_BIT;
    dep.dstAccessMask = vk::VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    vk::VkRenderPassCreateInfo rpci{};
    rpci.sType           = vk::VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    rpci.attachmentCount = 1u;
    rpci.pAttachments    = &att;
    rpci.subpassCount    = 1u;
    rpci.pSubpasses      = &sp;
    rpci.dependencyCount = 1u;
    rpci.pDependencies   = &dep;
    if (impl_->vk.vkCreateRenderPass(impl_->device, &rpci, nullptr, &impl_->present_render_pass) != vk::VK_SUCCESS ||
        !impl_->present_render_pass) {
        err_msg = "vkCreateRenderPass (present) failed.";
        return false;
    }

    att.finalLayout = vk::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    if (impl_->vk.vkCreateRenderPass(impl_->device, &rpci, nullptr, &impl_->capture_render_pass) != vk::VK_SUCCESS ||
        !impl_->capture_render_pass) {
        err_msg = "vkCreateRenderPass (capture) failed.";
        return false;
    }

    impl_->swapchain_fbs.resize(sc_count, nullptr);
    for (uint32_t i = 0u; i < sc_count; ++i) {
        vk::VkFramebufferCreateInfo fbci{};
        fbci.sType           = vk::VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        fbci.renderPass      = impl_->present_render_pass;
        fbci.attachmentCount = 1u;
        fbci.pAttachments    = &impl_->swapchain_views[i];
        fbci.width           = swapchain_width_;
        fbci.height          = swapchain_height_;
        fbci.layers          = 1u;
        if (impl_->vk.vkCreateFramebuffer(impl_->device, &fbci, nullptr, &impl_->swapchain_fbs[i]) != vk::VK_SUCCESS) {
            err_msg = "vkCreateFramebuffer (swapchain) failed.";
            return false;
        }
    }

    impl_->blit_pipeline    = impl_->create_fullscreen_pipeline(impl_->sm_blit_fs);
    impl_->fxaa_pipeline    = impl_->create_fullscreen_pipeline(impl_->sm_fxaa_fs);
    impl_->overlay_pipeline = impl_->create_gx_pipeline(
        impl_->present_render_pass, vk::VK_SAMPLE_COUNT_1_BIT, 0u, 0u, 1u);
    if (!impl_->blit_pipeline || !impl_->fxaa_pipeline || !impl_->overlay_pipeline) {
        err_msg = "Failed to create present pipelines (blit/fxaa/overlay).";
        return false;
    }
    return true;
}

void Win32VulkanHost::destroy_offscreen_efb() {
    if (!impl_ || !impl_->device) return;
    impl_->destroy_gx_pipelines();
    if (impl_->efb_fb) { impl_->vk.vkDestroyFramebuffer(impl_->device, impl_->efb_fb, nullptr); impl_->efb_fb = nullptr; }
    if (impl_->efb_render_pass) { impl_->vk.vkDestroyRenderPass(impl_->device, impl_->efb_render_pass, nullptr); impl_->efb_render_pass = nullptr; }
    impl_->destroy_image(impl_->efb_msaa_img, impl_->efb_msaa_mem, impl_->efb_msaa_view);
    impl_->destroy_image(impl_->efb_depth_img, impl_->efb_depth_mem, impl_->efb_depth_view);
    impl_->destroy_image(impl_->efb_resolved_img, impl_->efb_resolved_mem, impl_->efb_resolved_view);
}

bool Win32VulkanHost::create_offscreen_efb_and_postprocess(std::string& err_msg) {
    compute_efb_dimensions(cfg_, swapchain_height_, efb_width_, efb_height_);

    // Select depth format (prefer pure D32_SFLOAT to keep a single aspect bit)
    impl_->depth_fmt    = vk::VK_FORMAT_D32_SFLOAT;
    impl_->depth_aspect = vk::VK_IMAGE_ASPECT_DEPTH_BIT;
    const vk::VkFormat candidates[3] = {
        vk::VK_FORMAT_D32_SFLOAT,
        vk::VK_FORMAT_D24_UNORM_S8_UINT,
        vk::VK_FORMAT_D32_SFLOAT_S8_UINT
    };
    for (vk::VkFormat cand : candidates) {
        vk::VkFormatProperties fp{};
        impl_->vk.vkGetPhysicalDeviceFormatProperties(impl_->phys_dev, cand, &fp);
        if ((fp.optimalTilingFeatures & vk::VK_FORMAT_FEATURE_DEPTH_STENCIL_ATT_BIT) != 0u) {
            impl_->depth_fmt = cand;
            break;
        }
    }

    uint32_t req_samples = resolve_requested_msaa(cfg_.msaa_mode);
    vk::VkImageFormatProperties color_ifp{};
    vk::VkImageFormatProperties depth_ifp{};
    impl_->vk.vkGetPhysicalDeviceImageFormatProperties(
        impl_->phys_dev, vk::VK_FORMAT_R8G8B8A8_UNORM, vk::VK_IMAGE_TYPE_2D,
        vk::VK_IMAGE_TILING_OPTIMAL, vk::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, 0u, &color_ifp);
    impl_->vk.vkGetPhysicalDeviceImageFormatProperties(
        impl_->phys_dev, impl_->depth_fmt, vk::VK_IMAGE_TYPE_2D,
        vk::VK_IMAGE_TILING_OPTIMAL, vk::VK_IMAGE_USAGE_DEPTH_STENCIL_ATT_BIT, 0u, &depth_ifp);
    const vk::VkFlags supported_samples = color_ifp.sampleCounts & depth_ifp.sampleCounts;
    while (req_samples > 1u && (supported_samples & sample_count_to_vk(req_samples)) == 0u) {
        req_samples /= 2u;
    }
    efb_msaa_samples_ = (std::max)(1u, req_samples);
    const vk::VkFlags vk_samples = sample_count_to_vk(efb_msaa_samples_);

    if (!impl_->create_image_2d(
            efb_width_, efb_height_,
            vk::VK_FORMAT_R8G8B8A8_UNORM,
            vk::VK_SAMPLE_COUNT_1_BIT,
            vk::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | vk::VK_IMAGE_USAGE_SAMPLED_BIT | vk::VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
            vk::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            impl_->efb_resolved_img,
            impl_->efb_resolved_mem)) {
        err_msg = "Failed to create EFB resolved image.";
        return false;
    }
    impl_->efb_resolved_view = impl_->create_image_view_2d(
        impl_->efb_resolved_img, vk::VK_FORMAT_R8G8B8A8_UNORM, vk::VK_IMAGE_ASPECT_COLOR_BIT);

    if (!impl_->create_image_2d(
            efb_width_, efb_height_,
            impl_->depth_fmt,
            vk_samples,
            vk::VK_IMAGE_USAGE_DEPTH_STENCIL_ATT_BIT,
            vk::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            impl_->efb_depth_img,
            impl_->efb_depth_mem)) {
        err_msg = "Failed to create EFB depth image.";
        return false;
    }
    impl_->efb_depth_view = impl_->create_image_view_2d(
        impl_->efb_depth_img, impl_->depth_fmt, impl_->depth_aspect);

    if (efb_msaa_samples_ > 1u) {
        if (!impl_->create_image_2d(
                efb_width_, efb_height_,
                vk::VK_FORMAT_R8G8B8A8_UNORM,
                vk_samples,
                vk::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
                vk::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                impl_->efb_msaa_img,
                impl_->efb_msaa_mem)) {
            err_msg = "Failed to create EFB MSAA color image.";
            return false;
        }
        impl_->efb_msaa_view = impl_->create_image_view_2d(
            impl_->efb_msaa_img, vk::VK_FORMAT_R8G8B8A8_UNORM, vk::VK_IMAGE_ASPECT_COLOR_BIT);
    }

    if (!impl_->efb_resolved_view || !impl_->efb_depth_view || (efb_msaa_samples_ > 1u && !impl_->efb_msaa_view)) {
        err_msg = "Failed to create EFB image views.";
        return false;
    }

    vk::VkAttachmentDescription atts[3]{};
    uint32_t att_count = 2u;
    vk::VkImageView fb_views[3]{};
    vk::VkAttachmentReference color_ref{0u, vk::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    vk::VkAttachmentReference depth_ref{1u, vk::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};
    vk::VkAttachmentReference resolve_ref{2u, vk::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};

    if (efb_msaa_samples_ > 1u) {
        att_count = 3u;
        atts[0].format         = vk::VK_FORMAT_R8G8B8A8_UNORM;
        atts[0].samples        = vk_samples;
        atts[0].loadOp         = vk::VK_ATTACHMENT_LOAD_OP_CLEAR;
        atts[0].storeOp        = vk::VK_ATTACHMENT_STORE_OP_DONT_CARE;
        atts[0].stencilLoadOp  = vk::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        atts[0].stencilStoreOp = vk::VK_ATTACHMENT_STORE_OP_DONT_CARE;
        atts[0].initialLayout  = vk::VK_IMAGE_LAYOUT_UNDEFINED;
        atts[0].finalLayout    = vk::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        atts[1].format         = impl_->depth_fmt;
        atts[1].samples        = vk_samples;
        atts[1].loadOp         = vk::VK_ATTACHMENT_LOAD_OP_CLEAR;
        atts[1].storeOp        = vk::VK_ATTACHMENT_STORE_OP_DONT_CARE;
        atts[1].stencilLoadOp  = vk::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        atts[1].stencilStoreOp = vk::VK_ATTACHMENT_STORE_OP_DONT_CARE;
        atts[1].initialLayout  = vk::VK_IMAGE_LAYOUT_UNDEFINED;
        atts[1].finalLayout    = vk::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        atts[2].format         = vk::VK_FORMAT_R8G8B8A8_UNORM;
        atts[2].samples        = vk::VK_SAMPLE_COUNT_1_BIT;
        atts[2].loadOp         = vk::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        atts[2].storeOp        = vk::VK_ATTACHMENT_STORE_OP_STORE;
        atts[2].stencilLoadOp  = vk::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        atts[2].stencilStoreOp = vk::VK_ATTACHMENT_STORE_OP_DONT_CARE;
        atts[2].initialLayout  = vk::VK_IMAGE_LAYOUT_UNDEFINED;
        atts[2].finalLayout    = vk::VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

        fb_views[0] = impl_->efb_msaa_view;
        fb_views[1] = impl_->efb_depth_view;
        fb_views[2] = impl_->efb_resolved_view;
    } else {
        atts[0].format         = vk::VK_FORMAT_R8G8B8A8_UNORM;
        atts[0].samples        = vk::VK_SAMPLE_COUNT_1_BIT;
        atts[0].loadOp         = vk::VK_ATTACHMENT_LOAD_OP_CLEAR;
        atts[0].storeOp        = vk::VK_ATTACHMENT_STORE_OP_STORE;
        atts[0].stencilLoadOp  = vk::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        atts[0].stencilStoreOp = vk::VK_ATTACHMENT_STORE_OP_DONT_CARE;
        atts[0].initialLayout  = vk::VK_IMAGE_LAYOUT_UNDEFINED;
        atts[0].finalLayout    = vk::VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

        atts[1].format         = impl_->depth_fmt;
        atts[1].samples        = vk::VK_SAMPLE_COUNT_1_BIT;
        atts[1].loadOp         = vk::VK_ATTACHMENT_LOAD_OP_CLEAR;
        atts[1].storeOp        = vk::VK_ATTACHMENT_STORE_OP_DONT_CARE;
        atts[1].stencilLoadOp  = vk::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        atts[1].stencilStoreOp = vk::VK_ATTACHMENT_STORE_OP_DONT_CARE;
        atts[1].initialLayout  = vk::VK_IMAGE_LAYOUT_UNDEFINED;
        atts[1].finalLayout    = vk::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        fb_views[0] = impl_->efb_resolved_view;
        fb_views[1] = impl_->efb_depth_view;
    }

    vk::VkSubpassDescription sp{};
    sp.colorAttachmentCount    = 1u;
    sp.pColorAttachments       = &color_ref;
    sp.pResolveAttachments     = (efb_msaa_samples_ > 1u) ? &resolve_ref : nullptr;
    sp.pDepthStencilAttachment = &depth_ref;

    vk::VkSubpassDependency deps[2]{};
    deps[0].srcSubpass    = vk::VK_SUBPASS_EXTERNAL;
    deps[0].dstSubpass    = 0u;
    deps[0].srcStageMask  = vk::VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | vk::VK_PIPELINE_STAGE_COLOR_ATT_OUT_BIT;
    deps[0].dstStageMask  = vk::VK_PIPELINE_STAGE_COLOR_ATT_OUT_BIT | vk::VK_PIPELINE_STAGE_EARLY_FRAG_BIT;
    deps[0].srcAccessMask = vk::VK_ACCESS_SHADER_READ_BIT;
    deps[0].dstAccessMask = vk::VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | vk::VK_ACCESS_DEPTH_STENCIL_ATT_WRITE_BIT;

    deps[1].srcSubpass    = 0u;
    deps[1].dstSubpass    = vk::VK_SUBPASS_EXTERNAL;
    deps[1].srcStageMask  = vk::VK_PIPELINE_STAGE_COLOR_ATT_OUT_BIT;
    deps[1].dstStageMask  = vk::VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    deps[1].srcAccessMask = vk::VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    deps[1].dstAccessMask = vk::VK_ACCESS_SHADER_READ_BIT;

    vk::VkRenderPassCreateInfo rpci{};
    rpci.sType           = vk::VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    rpci.attachmentCount = att_count;
    rpci.pAttachments    = atts;
    rpci.subpassCount    = 1u;
    rpci.pSubpasses      = &sp;
    rpci.dependencyCount = 2u;
    rpci.pDependencies   = deps;
    if (impl_->vk.vkCreateRenderPass(impl_->device, &rpci, nullptr, &impl_->efb_render_pass) != vk::VK_SUCCESS ||
        !impl_->efb_render_pass) {
        err_msg = "vkCreateRenderPass (EFB) failed.";
        return false;
    }

    vk::VkFramebufferCreateInfo fbci{};
    fbci.sType           = vk::VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fbci.renderPass      = impl_->efb_render_pass;
    fbci.attachmentCount = att_count;
    fbci.pAttachments    = fb_views;
    fbci.width           = efb_width_;
    fbci.height          = efb_height_;
    fbci.layers          = 1u;
    if (impl_->vk.vkCreateFramebuffer(impl_->device, &fbci, nullptr, &impl_->efb_fb) != vk::VK_SUCCESS ||
        !impl_->efb_fb) {
        err_msg = "vkCreateFramebuffer (EFB) failed.";
        return false;
    }

    impl_->update_fxaa_descriptor_sets();
    return true;
}

bool Win32VulkanHost::recreate_swapchain_for_resize(uint32_t width, uint32_t height) {
    if (!impl_ || !impl_->device || !impl_->surface || width == 0u || height == 0u) return false;
#ifdef _WIN32
    if (hwnd_ && IsIconic(static_cast<HWND>(hwnd_))) {
        return false;
    }
#endif
    vk::VkSurfaceCapabilitiesKHR caps{};
    if (impl_->vk.vkGetPhysicalDeviceSurfaceCapabilitiesKHR(impl_->phys_dev, impl_->surface, &caps) != vk::VK_SUCCESS) {
        return false;
    }
    if (caps.maxImageExtent.width == 0u || caps.maxImageExtent.height == 0u ||
        (caps.currentExtent.width != 0xFFFFFFFFu && (caps.currentExtent.width == 0u || caps.currentExtent.height == 0u))) {
        return false;
    }
    impl_->vk.vkDeviceWaitIdle(impl_->device);
    destroy_swapchain_and_views();
    swapchain_width_  = width;
    swapchain_height_ = height;
    std::string err_msg;
    if (!create_swapchain_and_views(err_msg)) {
        PN03_LOGF(LogLevel::Error, "VULKAN", "Swapchain recreate failed: %s", err_msg.c_str());
        return false;
    }
    uint32_t new_efb_w = 0u, new_efb_h = 0u;
    compute_efb_dimensions(cfg_, swapchain_height_, new_efb_w, new_efb_h);
    if (new_efb_w != efb_width_ || new_efb_h != efb_height_) {
        destroy_offscreen_efb();
        if (!create_offscreen_efb_and_postprocess(err_msg)) {
            PN03_LOGF(LogLevel::Error, "VULKAN", "EFB resize recreate failed: %s", err_msg.c_str());
            return false;
        }
    }
    return true;
}

bool Win32VulkanHost::create_render_window_and_vulkan(std::string& err_msg, bool hidden_window) {
#ifdef _WIN32
    hidden_window_   = hidden_window;
    close_requested_ = false;

    uint32_t sc_w = cfg_.render_width;
    uint32_t sc_h = cfg_.render_height;
    HWND hwnd = create_pn03_win32_window(
        cfg_, hidden_window, L"PN03_Vulkan_WndClass", PN03VulkanWndProc, this, sc_w, sc_h);
    if (!hwnd) {
        err_msg = "Failed to create Win32 window for Vulkan.";
        return false;
    }
    hwnd_             = hwnd;
    swapchain_width_  = sc_w;
    swapchain_height_ = sc_h;

    if (!impl_->vk.load_loader()) {
        err_msg = "Failed to load vulkan-1.dll (Vulkan runtime not installed).";
        return false;
    }

    const char* inst_exts[2] = {"VK_KHR_surface", "VK_KHR_win32_surface"};
    vk::VkApplicationInfo app{};
    app.sType              = vk::VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app.pApplicationName   = "PN03_WinPort";
    app.applicationVersion = 1u;
    app.pEngineName        = "PN03_GX_VK";
    app.engineVersion      = 1u;
    app.apiVersion         = PN03_VK_API_VERSION_1_3;

    vk::VkInstanceCreateInfo ici{};
    ici.sType                   = vk::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    ici.pApplicationInfo        = &app;
    ici.enabledExtensionCount   = 2u;
    ici.ppEnabledExtensionNames = inst_exts;

    if (impl_->vk.vkCreateInstance(&ici, nullptr, &impl_->instance) != vk::VK_SUCCESS) {
        app.apiVersion = PN03_VK_API_VERSION_1_0;
        if (impl_->vk.vkCreateInstance(&ici, nullptr, &impl_->instance) != vk::VK_SUCCESS || !impl_->instance) {
            err_msg = "vkCreateInstance failed.";
            return false;
        }
    }
    if (!impl_->vk.load_instance_procs(impl_->instance)) {
        err_msg = "Failed to load Vulkan KHR instance functions.";
        return false;
    }

    vk::VkWin32SurfaceCreateInfoKHR wsci{};
    wsci.sType     = vk::VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    wsci.hinstance = GetModuleHandleW(nullptr);
    wsci.hwnd      = hwnd;
    if (impl_->vk.vkCreateWin32SurfaceKHR(impl_->instance, &wsci, nullptr, &impl_->surface) != vk::VK_SUCCESS ||
        !impl_->surface) {
        err_msg = "vkCreateWin32SurfaceKHR failed.";
        return false;
    }

    uint32_t pd_count = 0u;
    impl_->vk.vkEnumeratePhysicalDevices(impl_->instance, &pd_count, nullptr);
    if (pd_count == 0u) {
        err_msg = "No Vulkan physical devices available.";
        return false;
    }
    std::vector<vk::VkPhysicalDevice> pds(pd_count);
    impl_->vk.vkEnumeratePhysicalDevices(impl_->instance, &pd_count, pds.data());

    int best_score = -1;
    uint32_t best_qf = 0u;
    vk::VkPhysicalDevice best_pd = nullptr;
    vk::VkPhysicalDevicePropertiesHeader best_props{};

    for (auto pd : pds) {
        vk::VkPhysicalDevicePropertiesHeader props{};
        impl_->vk.vkGetPhysicalDeviceProperties(pd, &props);

        uint32_t qf_count = 0u;
        impl_->vk.vkGetPhysicalDeviceQueueFamilyProperties(pd, &qf_count, nullptr);
        std::vector<vk::VkQueueFamilyProperties> qfs(qf_count);
        impl_->vk.vkGetPhysicalDeviceQueueFamilyProperties(pd, &qf_count, qfs.data());

        for (uint32_t q = 0u; q < qf_count; ++q) {
            if ((qfs[q].queueFlags & vk::VK_QUEUE_GRAPHICS_BIT) == 0u) continue;
            vk::VkBool32 present_ok = vk::VK_FALSE;
            impl_->vk.vkGetPhysicalDeviceSurfaceSupportKHR(pd, q, impl_->surface, &present_ok);
            if (!present_ok) continue;

            int score = 10;
            if (props.deviceType == 2u) score += 100;      // discrete GPU
            else if (props.deviceType == 1u) score += 50;  // integrated GPU
            if (props.apiVersion >= PN03_VK_API_VERSION_1_3) score += 20;
            if (score > best_score) {
                best_score = score;
                best_qf    = q;
                best_pd    = pd;
                best_props = props;
            }
            break;
        }
    }
    if (!best_pd) {
        err_msg = "No Vulkan GPU supporting both graphics and Win32 surface present.";
        return false;
    }
    impl_->phys_dev     = best_pd;
    impl_->queue_family = best_qf;
    adapter_name_       = best_props.deviceName;
    vk_api_version_     = best_props.apiVersion;
    impl_->vk.vkGetPhysicalDeviceMemoryProperties(best_pd, &impl_->mem_props);

    vk::VkPhysicalDeviceFeatures dev_feats{};
    impl_->vk.vkGetPhysicalDeviceFeatures(best_pd, &dev_feats);
    impl_->aniso_supported = (dev_feats.features[19] != vk::VK_FALSE);
    vk::VkPhysicalDeviceFeatures enabled_feats{};
    if (impl_->aniso_supported) {
        enabled_feats.features[19] = vk::VK_TRUE;
    }

    const float queue_prio = 1.0f;
    vk::VkDeviceQueueCreateInfo dqci{};
    dqci.sType            = vk::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    dqci.queueFamilyIndex = best_qf;
    dqci.queueCount       = 1u;
    dqci.pQueuePriorities = &queue_prio;

    const char* dev_exts[1] = {"VK_KHR_swapchain"};
    vk::VkDeviceCreateInfo dci{};
    dci.sType                   = vk::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    dci.queueCreateInfoCount    = 1u;
    dci.pQueueCreateInfos       = &dqci;
    dci.enabledExtensionCount   = 1u;
    dci.ppEnabledExtensionNames = dev_exts;
    dci.pEnabledFeatures        = &enabled_feats;

    if (impl_->vk.vkCreateDevice(best_pd, &dci, nullptr, &impl_->device) != vk::VK_SUCCESS || !impl_->device) {
        err_msg = "vkCreateDevice failed.";
        return false;
    }
    if (!impl_->vk.load_device_procs(impl_->device)) {
        err_msg = "Failed to load Vulkan device functions.";
        return false;
    }
    impl_->vk.vkGetDeviceQueue(impl_->device, best_qf, 0u, &impl_->graphics_queue);

    // Command pool + per-frame command buffers & sync
    vk::VkCommandPoolCreateInfo cpci{};
    cpci.sType            = vk::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    cpci.flags            = vk::VK_COMMAND_POOL_CREATE_RESET_CB_BIT;
    cpci.queueFamilyIndex = best_qf;
    if (impl_->vk.vkCreateCommandPool(impl_->device, &cpci, nullptr, &impl_->cmd_pool) != vk::VK_SUCCESS ||
        !impl_->cmd_pool) {
        err_msg = "vkCreateCommandPool failed.";
        return false;
    }

    // Descriptor set layouts & pipeline layouts
    vk::VkDescriptorSetLayoutBinding gx_bindings[3]{};
    gx_bindings[0] = {0u, vk::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1u,
                      vk::VK_SHADER_STAGE_VERTEX_BIT | vk::VK_SHADER_STAGE_FRAGMENT_BIT, nullptr};
    gx_bindings[1] = {1u, vk::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1u, vk::VK_SHADER_STAGE_FRAGMENT_BIT, nullptr};
    gx_bindings[2] = {2u, vk::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1u, vk::VK_SHADER_STAGE_FRAGMENT_BIT, nullptr};
    vk::VkDescriptorSetLayoutCreateInfo gx_dslci{};
    gx_dslci.sType        = vk::VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    gx_dslci.bindingCount = 3u;
    gx_dslci.pBindings    = gx_bindings;
    if (impl_->vk.vkCreateDescriptorSetLayout(impl_->device, &gx_dslci, nullptr, &impl_->gx_dsl) != vk::VK_SUCCESS) {
        err_msg = "vkCreateDescriptorSetLayout (GX) failed.";
        return false;
    }
    vk::VkPipelineLayoutCreateInfo gx_plci{};
    gx_plci.sType          = vk::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    gx_plci.setLayoutCount = 1u;
    gx_plci.pSetLayouts    = &impl_->gx_dsl;
    if (impl_->vk.vkCreatePipelineLayout(impl_->device, &gx_plci, nullptr, &impl_->gx_pl) != vk::VK_SUCCESS) {
        err_msg = "vkCreatePipelineLayout (GX) failed.";
        return false;
    }

    vk::VkDescriptorSetLayoutBinding fx_bindings[2]{};
    fx_bindings[0] = {0u, vk::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1u, vk::VK_SHADER_STAGE_FRAGMENT_BIT, nullptr};
    fx_bindings[1] = {1u, vk::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1u, vk::VK_SHADER_STAGE_FRAGMENT_BIT, nullptr};
    vk::VkDescriptorSetLayoutCreateInfo fx_dslci{};
    fx_dslci.sType        = vk::VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    fx_dslci.bindingCount = 2u;
    fx_dslci.pBindings    = fx_bindings;
    if (impl_->vk.vkCreateDescriptorSetLayout(impl_->device, &fx_dslci, nullptr, &impl_->fxaa_dsl) != vk::VK_SUCCESS) {
        err_msg = "vkCreateDescriptorSetLayout (FXAA) failed.";
        return false;
    }
    vk::VkPipelineLayoutCreateInfo fx_plci{};
    fx_plci.sType          = vk::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    fx_plci.setLayoutCount = 1u;
    fx_plci.pSetLayouts    = &impl_->fxaa_dsl;
    if (impl_->vk.vkCreatePipelineLayout(impl_->device, &fx_plci, nullptr, &impl_->fxaa_pl) != vk::VK_SUCCESS) {
        err_msg = "vkCreatePipelineLayout (FXAA) failed.";
        return false;
    }

    // Shader modules
    impl_->sm_gx_vs   = impl_->create_shader_module(vk_shaders::kGxTevVertSpv,  sizeof(vk_shaders::kGxTevVertSpv)  / 4u);
    impl_->sm_gx_fs   = impl_->create_shader_module(vk_shaders::kGxTevFragSpv,  sizeof(vk_shaders::kGxTevFragSpv)  / 4u);
    impl_->sm_fxaa_vs = impl_->create_shader_module(vk_shaders::kFxaaVertSpv,   sizeof(vk_shaders::kFxaaVertSpv)   / 4u);
    impl_->sm_blit_fs = impl_->create_shader_module(vk_shaders::kBlitFragSpv,   sizeof(vk_shaders::kBlitFragSpv)   / 4u);
    impl_->sm_fxaa_fs = impl_->create_shader_module(vk_shaders::kFxaaFragSpv,   sizeof(vk_shaders::kFxaaFragSpv)   / 4u);
    if (!impl_->sm_gx_vs || !impl_->sm_gx_fs || !impl_->sm_fxaa_vs || !impl_->sm_blit_fs || !impl_->sm_fxaa_fs) {
        err_msg = "Failed to create embedded SPIR-V shader modules.";
        return false;
    }

    // Samplers
    static constexpr vk::VkSamplerAddressMode kVkAddr[3] = {
        vk::VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
        vk::VK_SAMPLER_ADDRESS_MODE_REPEAT,
        vk::VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT
    };
    const bool use_aniso = impl_->aniso_supported && (cfg_.anisotropic_filtering > 1u);
    for (uint32_t ws = 0u; ws < 3u; ++ws) {
        for (uint32_t wt = 0u; wt < 3u; ++wt) {
            vk::VkSamplerCreateInfo sci{};
            sci.sType            = vk::VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
            sci.magFilter        = vk::VK_FILTER_LINEAR;
            sci.minFilter        = vk::VK_FILTER_LINEAR;
            sci.mipmapMode       = vk::VK_SAMPLER_MIPMAP_MODE_LINEAR;
            sci.addressModeU     = kVkAddr[ws];
            sci.addressModeV     = kVkAddr[wt];
            sci.addressModeW     = vk::VK_SAMPLER_ADDRESS_MODE_REPEAT;
            sci.anisotropyEnable = use_aniso ? vk::VK_TRUE : vk::VK_FALSE;
            sci.maxAnisotropy    = use_aniso ? static_cast<float>(std::clamp(cfg_.anisotropic_filtering, 1u, 16u)) : 1.0f;
            sci.maxLod           = 16.0f;
            impl_->vk.vkCreateSampler(impl_->device, &sci, nullptr, &impl_->samplers[ws * 3u + wt]);
        }
    }
    vk::VkSamplerCreateInfo lsci{};
    lsci.sType        = vk::VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    lsci.magFilter    = vk::VK_FILTER_LINEAR;
    lsci.minFilter    = vk::VK_FILTER_LINEAR;
    lsci.mipmapMode   = vk::VK_SAMPLER_MIPMAP_MODE_LINEAR;
    lsci.addressModeU = vk::VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    lsci.addressModeV = vk::VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    lsci.addressModeW = vk::VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    lsci.maxLod       = 16.0f;
    impl_->vk.vkCreateSampler(impl_->device, &lsci, nullptr, &impl_->sampler_linear_clamp);

    // Persistent dynamic GX UBO buffer (kMaxFramesInFlight * kMaxGxUboSlotsPerFrame * 256 bytes = 4 MB)
    const size_t total_gx_ubo_bytes = kMaxFramesInFlight * kMaxGxUboSlotsPerFrame * kGxUboStride;
    if (!impl_->create_buffer(
            total_gx_ubo_bytes,
            vk::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            vk::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | vk::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            impl_->gx_ubo_buf,
            impl_->gx_ubo_mem) ||
        impl_->vk.vkMapMemory(impl_->device, impl_->gx_ubo_mem, 0, vk::VK_WHOLE_SIZE, 0, &impl_->gx_ubo_mapped) != vk::VK_SUCCESS) {
        err_msg = "Failed to allocate/map Vulkan GX uniform buffer.";
        return false;
    }

    // FXAA descriptor pool & per-frame slots
    vk::VkDescriptorPoolSize fx_ps[2]{
        {vk::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, kMaxFramesInFlight},
        {vk::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, kMaxFramesInFlight}
    };
    vk::VkDescriptorPoolCreateInfo fx_dpci{};
    fx_dpci.sType         = vk::VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    fx_dpci.maxSets       = kMaxFramesInFlight;
    fx_dpci.poolSizeCount = 2u;
    fx_dpci.pPoolSizes    = fx_ps;
    if (impl_->vk.vkCreateDescriptorPool(impl_->device, &fx_dpci, nullptr, &impl_->fxaa_desc_pool) != vk::VK_SUCCESS) {
        err_msg = "vkCreateDescriptorPool (FXAA) failed.";
        return false;
    }

    for (uint32_t i = 0u; i < kMaxFramesInFlight; ++i) {
        auto& f = impl_->frames[i];
        vk::VkFenceCreateInfo fci{vk::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, nullptr, vk::VK_FENCE_CREATE_SIGNALED_BIT};
        vk::VkSemaphoreCreateInfo sci{vk::VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, nullptr, 0u};
        vk::VkCommandBufferAllocateInfo cbai{vk::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, nullptr, impl_->cmd_pool, 0u, 1u};
        if (impl_->vk.vkCreateFence(impl_->device, &fci, nullptr, &f.in_flight_fence) != vk::VK_SUCCESS ||
            impl_->vk.vkCreateSemaphore(impl_->device, &sci, nullptr, &f.image_available_sem) != vk::VK_SUCCESS ||
            impl_->vk.vkAllocateCommandBuffers(impl_->device, &cbai, &f.cmd_buf) != vk::VK_SUCCESS) {
            err_msg = "Failed to create per-frame Vulkan sync/command objects.";
            return false;
        }
        if (!impl_->create_buffer(
                sizeof(FxaaConstantsCPU),
                vk::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                vk::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | vk::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                f.fxaa_ubo,
                f.fxaa_ubo_mem) ||
            impl_->vk.vkMapMemory(impl_->device, f.fxaa_ubo_mem, 0, vk::VK_WHOLE_SIZE, 0, &f.fxaa_ubo_mapped) != vk::VK_SUCCESS) {
            err_msg = "Failed to allocate/map FXAA uniform buffer.";
            return false;
        }
        vk::VkDescriptorSetAllocateInfo dsai{
            vk::VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO, nullptr, impl_->fxaa_desc_pool, 1u, &impl_->fxaa_dsl};
        if (impl_->vk.vkAllocateDescriptorSets(impl_->device, &dsai, &f.fxaa_desc_set) != vk::VK_SUCCESS) {
            err_msg = "Failed to allocate FXAA descriptor set.";
            return false;
        }
    }

    // 1x1 white fallback texture (uploaded immediately)
    const uint32_t white_px = 0xFFFFFFFFu;
    std::vector<PendingImageUpload> init_uploads;
    if (!impl_->stage_texture_rgba8(1u, 1u, reinterpret_cast<const uint8_t*>(&white_px), impl_->default_white_tex, init_uploads)) {
        err_msg = "Failed to create default white Vulkan texture.";
        return false;
    }
    impl_->submit_one_time_commands([&](vk::VkCommandBuffer cmd) {
        impl_->record_pending_uploads(cmd, init_uploads, impl_->frames[0]);
    });
    impl_->free_staging_garbage(impl_->frames[0]);

    if (!create_swapchain_and_views(err_msg) || !create_offscreen_efb_and_postprocess(err_msg)) {
        return false;
    }

    initialized_ = true;
    PN03_LOGF(LogLevel::Info, "VULKAN",
              "Initialized Vulkan %u.%u.%u on '%s' (swapchain=%ux%u, EFB=%ux%u, MSAA=%ux, FXAA=%s)",
              (vk_api_version_ >> 22) & 0x7Fu, (vk_api_version_ >> 12) & 0x3FFu, vk_api_version_ & 0xFFFu,
              adapter_name_.c_str(), swapchain_width_, swapchain_height_,
              efb_width_, efb_height_, efb_msaa_samples_,
              (cfg_.enable_fxaa || cfg_.msaa_mode == AntiAliasingMode::FXAA) ? "ON" : "OFF");
    return true;
#else
    err_msg = "Vulkan Win32 host requires Windows.";
    return false;
#endif
}

void Win32VulkanHost::begin_vulkan_frame(float clear_r, float clear_g, float clear_b) {
    batches_rendered_this_frame_ = false;
    if (impl_) {
        impl_->frame_submitted = false;
    }
    pending_clear_color_[0] = clear_r;
    pending_clear_color_[1] = clear_g;
    pending_clear_color_[2] = clear_b;
    pending_clear_color_[3] = 1.0f;
}

void Win32VulkanHost::submit_empty_clear_frame_if_needed() {
    if (!impl_ || !initialized_ || impl_->frame_submitted) return;
    render_gx_internal(Memory::active_instance(), global_gx_3d_interface());
}

void Win32VulkanHost::render_gx_draw_batches(const Memory& mem, GX3DInterface& gx) {
    render_gx_internal(&mem, gx);
}

void Win32VulkanHost::render_gx_internal(const Memory* mem, GX3DInterface& gx) {
    const auto& verts    = gx.vertices();
    const auto& indices  = gx.indices();
    const auto& batches  = gx.draw_batches();
    const auto& overlays = gx.overlay_texts();
    last_rendered_batches_   = batches.size();
    last_rendered_triangles_ = indices.size() / 3u;

    if (!initialized_ || !impl_ || !impl_->device || swapchain_width_ == 0u || swapchain_height_ == 0u) {
        return;
    }
#ifdef _WIN32
    if (hwnd_ && IsIconic(static_cast<HWND>(hwnd_))) {
        return;
    }
#endif
    if (!impl_->swapchain) {
        if (!recreate_swapchain_for_resize(swapchain_width_, swapchain_height_) || !impl_->swapchain) {
            return;
        }
    }
    if (impl_->frame_submitted) {
        return;
    }

    last_disp_gamma_ = gx.disp_copy_gamma();
    const uint16_t* dsrc = gx.disp_copy_src();
    const float src_x = static_cast<float>(dsrc[0]);
    const float src_y = static_cast<float>(dsrc[1]);
    const float src_w = static_cast<float>((std::max)(16u, static_cast<uint32_t>(dsrc[2])));
    const float src_h = static_cast<float>((std::max)(16u, static_cast<uint32_t>(dsrc[3])));

    const uint32_t fi = impl_->frame_cursor % kMaxFramesInFlight;
    auto& slot = impl_->frames[fi];

    impl_->vk.vkWaitForFences(impl_->device, 1u, &slot.in_flight_fence, vk::VK_TRUE, ~0ULL);
    impl_->free_staging_garbage(slot);
    ++impl_->cache_frame_tick;
    impl_->recycle_descriptor_pools_if_needed();

    const bool has_batches = (mem != nullptr) && !verts.empty() && !indices.empty() && !batches.empty();
    const size_t gx_v_count = has_batches ? (std::min)(verts.size(), kHostMaxDynamicVertices) : 0u;
    const size_t gx_i_count = has_batches ? (std::min)(indices.size(), kHostMaxDynamicIndices) : 0u;
    const size_t max_ov_v   = overlays.size() * 8u;
    const size_t max_ov_i   = overlays.size() * 12u;
    const size_t pre_total_v = (std::min)(gx_v_count + max_ov_v, kHostMaxDynamicVertices);
    const size_t pre_total_i = (std::min)(gx_i_count + max_ov_i, kHostMaxDynamicIndices);
    if (!impl_->ensure_frame_dyn_buffers(slot, pre_total_v * sizeof(GXVertex), pre_total_i * sizeof(uint32_t))) {
        return;
    }

    uint32_t img_idx = 0u;
    vk::VkResult acq = impl_->vk.vkAcquireNextImageKHR(
        impl_->device, impl_->swapchain, ~0ULL, slot.image_available_sem, nullptr, &img_idx);
    if (acq == vk::VK_ERROR_OUT_OF_DATE_KHR) {
        if (!recreate_swapchain_for_resize(swapchain_width_, swapchain_height_) || !impl_->swapchain) return;
        acq = impl_->vk.vkAcquireNextImageKHR(
            impl_->device, impl_->swapchain, ~0ULL, slot.image_available_sem, nullptr, &img_idx);
    }
    if (acq != vk::VK_SUCCESS && acq != vk::VK_SUBOPTIMAL_KHR) {
        return;
    }

    // Prepare dynamic uploads + cached descriptor sets + UBOs outside render passes
    std::vector<PendingImageUpload> pending_uploads;
    std::vector<GXVertex>   ov_verts;
    std::vector<uint32_t>   ov_indices;
    std::vector<OvDrawItem> ov_items;

    const HostViewportRect out_rect = compute_output_viewport_rect(cfg_.aspect_ratio, swapchain_width_, swapchain_height_);
    if (!overlays.empty()) {
        ov_verts.reserve(overlays.size() * 8u);
        ov_indices.reserve(overlays.size() * 12u);
        ov_items.reserve(overlays.size() * 2u);

        auto push_quad = [&](vk::VkDescriptorSet ds, float x, float y, float w, float h,
                             float r, float g, float b, float a) {
            if (gx_v_count + ov_verts.size() + 4u > kHostMaxDynamicVertices ||
                gx_i_count + ov_indices.size() + 6u > kHostMaxDynamicIndices) {
                return;
            }
            const uint32_t vbase = static_cast<uint32_t>(gx_v_count + ov_verts.size());
            const uint32_t ibase = static_cast<uint32_t>(gx_i_count + ov_indices.size());
            ov_verts.push_back({{x,     y,     0.1f}, {0, 0, 1}, {r, g, b, a}, {0.0f, 0.0f}});
            ov_verts.push_back({{x + w, y,     0.1f}, {0, 0, 1}, {r, g, b, a}, {1.0f, 0.0f}});
            ov_verts.push_back({{x + w, y + h, 0.1f}, {0, 0, 1}, {r, g, b, a}, {1.0f, 1.0f}});
            ov_verts.push_back({{x,     y + h, 0.1f}, {0, 0, 1}, {r, g, b, a}, {0.0f, 1.0f}});
            ov_indices.push_back(vbase + 0u); ov_indices.push_back(vbase + 1u); ov_indices.push_back(vbase + 2u);
            ov_indices.push_back(vbase + 0u); ov_indices.push_back(vbase + 2u); ov_indices.push_back(vbase + 3u);
            ov_items.push_back({ds, ibase});
        };

        for (const auto& item : overlays) {
            int tw = 0, th = 0;
            vk::VkImageView tv = impl_->get_or_create_text_view(item.text, tw, th, pending_uploads);
            if (!tv || tw <= 0 || th <= 0) continue;
            vk::VkDescriptorSet ds = impl_->get_or_create_gx_desc_set(tv, 0u, impl_->default_white_tex.view, 4u);
            if (!ds) continue;
            const float w  = static_cast<float>(tw) * item.scale;
            const float h  = static_cast<float>(th) * item.scale;
            const float ix = (std::min)(item.x, src_x + (std::max)(4.0f, src_w - w - 28.0f));
            const float iy = (std::min)(item.y, src_y + (std::max)(4.0f, src_h - h - 4.0f));
            const float r  = ((item.rgba >> 24) & 0xFFu) / 255.0f;
            const float g  = ((item.rgba >> 16) & 0xFFu) / 255.0f;
            const float b  = ((item.rgba >> 8)  & 0xFFu) / 255.0f;
            const float a  = (item.rgba & 0xFFu) / 255.0f;
            push_quad(ds, ix + 1.0f, iy + 1.0f, w, h, 0.0f, 0.0f, 0.0f, a * 0.85f);
            push_quad(ds, ix, iy, w, h, r, g, b, a);
        }
    }

    if (gx_v_count > 0u) {
        std::memcpy(slot.dyn_vb_mapped, verts.data(), gx_v_count * sizeof(GXVertex));
    }
    if (!ov_verts.empty()) {
        std::memcpy(static_cast<uint8_t*>(slot.dyn_vb_mapped) + gx_v_count * sizeof(GXVertex),
                    ov_verts.data(), ov_verts.size() * sizeof(GXVertex));
    }
    if (gx_i_count > 0u) {
        std::memcpy(slot.dyn_ib_mapped, indices.data(), gx_i_count * sizeof(uint32_t));
    }
    if (!ov_indices.empty()) {
        std::memcpy(static_cast<uint8_t*>(slot.dyn_ib_mapped) + gx_i_count * sizeof(uint32_t),
                    ov_indices.data(), ov_indices.size() * sizeof(uint32_t));
    }

    // Prepare batch draw commands + UBO slots before command buffer recording
    struct PreparedBatch {
        vk::VkPipeline      pipe = nullptr;
        vk::VkDescriptorSet desc = nullptr;
        uint32_t            ubo_dyn_off = 0u;
        vk::VkViewport      vp{};
        vk::VkRect2D        sc{};
        uint32_t            index_count  = 0u;
        uint32_t            index_offset = 0u;
    };
    std::vector<PreparedBatch> prepared_batches;
    const size_t frame_ubo_base_slot = fi * kMaxGxUboSlotsPerFrame;
    size_t ubo_slot_cursor = 0u;
    bool has_prev_cdata = false;
    GXSceneConstantsCPU prev_cdata{};
    uint32_t last_ubo_dyn_off = static_cast<uint32_t>(frame_ubo_base_slot * kGxUboStride);

    if (has_batches) {
        prepared_batches.reserve(batches.size());
        for (const auto& batch : batches) {
            if (batch.index_offset + batch.index_count > gx_i_count) break;
            if (batch.cull_mode == 3u) continue;

            const bool full_efb = should_ortho_batch_fill_efb(
                batch, verts.data(), gx_v_count, indices.data(), gx_i_count,
                src_x, src_y, src_w, src_h);
            const HostViewportRect eb = compute_2d_ortho_efb_bounds(efb_width_, efb_height_, full_efb);
            const float sx = eb.width  / src_w;
            const float sy = eb.height / src_h;

            const float vp_x = eb.x + (batch.viewport[0] - src_x) * sx;
            const float vp_y = eb.y + (batch.viewport[1] - src_y) * sy;
            const float vp_w = (std::max)(1.0f, (batch.viewport[2] > 0.0f) ? (batch.viewport[2] * sx) : eb.width);
            const float vp_h = (std::max)(1.0f, (batch.viewport[3] > 0.0f) ? (batch.viewport[3] * sy) : eb.height);
            float min_d = std::clamp(batch.viewport[4], 0.0f, 1.0f);
            float max_d = std::clamp(batch.viewport[5], min_d, 1.0f);
            if (max_d <= min_d) { min_d = 0.0f; max_d = 1.0f; }

            vk::VkViewport bvp{vp_x, vp_y + vp_h, vp_w, -vp_h, min_d, max_d};

            const int32_t sc_x = static_cast<int32_t>(batch.scissor[0]) - static_cast<int32_t>(dsrc[0]);
            const int32_t sc_y = static_cast<int32_t>(batch.scissor[1]) - static_cast<int32_t>(dsrc[1]);
            const uint32_t raw_sw = (batch.scissor[2] > 0u) ? batch.scissor[2] : static_cast<uint32_t>(src_w);
            const uint32_t raw_sh = (batch.scissor[3] > 0u) ? batch.scissor[3] : static_cast<uint32_t>(src_h);
            const int32_t sl = static_cast<int32_t>(std::clamp(
                eb.x + static_cast<float>(sc_x) * sx, 0.0f, static_cast<float>(efb_width_)));
            const int32_t st = static_cast<int32_t>(std::clamp(
                eb.y + static_cast<float>(sc_y) * sy, 0.0f, static_cast<float>(efb_height_)));
            const int32_t sr = static_cast<int32_t>(std::clamp(
                eb.x + static_cast<float>(sc_x + static_cast<int32_t>(raw_sw)) * sx + 0.5f,
                static_cast<float>(sl), static_cast<float>(efb_width_)));
            const int32_t sb = static_cast<int32_t>(std::clamp(
                eb.y + static_cast<float>(sc_y + static_cast<int32_t>(raw_sh)) * sy + 0.5f,
                static_cast<float>(st), static_cast<float>(efb_height_)));
            vk::VkRect2D bsc{{sl, st}, {static_cast<uint32_t>((std::max)(0, sr - sl)), static_cast<uint32_t>((std::max)(0, sb - st))}};

            GXSceneConstantsCPU cdata{};
            std::memcpy(cdata.uProjection, batch.proj_mtx, sizeof(cdata.uProjection));
            if (std::fabs(cdata.uProjection[0][0] - 1.0f) < 1e-4f && std::fabs(cdata.uProjection[1][1] - 1.0f) < 1e-4f) {
                fill_ortho_rect(cdata.uProjection, src_x, src_y, src_w, src_h);
            }
            cdata.uModelView[0][0] = cdata.uModelView[1][1] = cdata.uModelView[2][2] = cdata.uModelView[3][3] = 1.0f;
            std::memcpy(cdata.uTevColor0, batch.tev_color, sizeof(cdata.uTevColor0));
            cdata.uKonstColor[0] = cdata.uKonstColor[1] = cdata.uKonstColor[2] = cdata.uKonstColor[3] = 1.0f;
            cdata.uViewportSize[0] = static_cast<float>(efb_width_);
            cdata.uViewportSize[1] = static_cast<float>(efb_height_);
            cdata.uEnableAlphaTest = 0u;
            cdata.uAlphaRef        = 0.01f;
            cdata.uTevMode         = batch.tev_mode;
            cdata.uTevScale        = batch.tev_scale;
            cdata.uStage1Mode      = batch.has_stage1_tex ? batch.stage1_op : 0u;

            uint32_t dyn_off = last_ubo_dyn_off;
            if (!has_prev_cdata || std::memcmp(&prev_cdata, &cdata, sizeof(cdata)) != 0) {
                if (ubo_slot_cursor + 1u < kMaxGxUboSlotsPerFrame) {
                    const size_t abs_slot = frame_ubo_base_slot + ubo_slot_cursor++;
                    dyn_off = static_cast<uint32_t>(abs_slot * kGxUboStride);
                    std::memcpy(static_cast<uint8_t*>(impl_->gx_ubo_mapped) + dyn_off, &cdata, sizeof(cdata));
                    prev_cdata = cdata;
                    has_prev_cdata = true;
                    last_ubo_dyn_off = dyn_off;
                }
            }

            uint32_t s0_idx = 4u;
            vk::VkImageView v0 = impl_->default_white_tex.view;
            if (batch.has_texture) {
                const uint32_t ws = (batch.texture.wrap_s <= 2u) ? batch.texture.wrap_s : 1u;
                const uint32_t wt = (batch.texture.wrap_t <= 2u) ? batch.texture.wrap_t : 1u;
                s0_idx = ws * 3u + wt;
                v0 = impl_->get_or_create_gc_texture_view(*mem, gx, batch.texture, batch.tlut, pending_uploads);
            }

            uint32_t s1_idx = 4u;
            vk::VkImageView v1 = impl_->default_white_tex.view;
            if (batch.has_stage1_tex) {
                const uint32_t ws1 = (batch.stage1_texture.wrap_s <= 2u) ? batch.stage1_texture.wrap_s : 1u;
                const uint32_t wt1 = (batch.stage1_texture.wrap_t <= 2u) ? batch.stage1_texture.wrap_t : 1u;
                s1_idx = ws1 * 3u + wt1;
                v1 = impl_->get_or_create_gc_texture_view(*mem, gx, batch.stage1_texture, batch.stage1_tlut, pending_uploads);
            }

            vk::VkDescriptorSet ds = impl_->get_or_create_gx_desc_set(v0, s0_idx, v1, s1_idx);
            const uint32_t cull_idx  = (batch.cull_mode == 1u || batch.cull_mode == 2u) ? batch.cull_mode : 0u;
            const uint32_t depth_idx = !batch.z_enable ? 0u : (batch.z_write ? 2u : 1u);
            const uint32_t blend_idx = (batch.blend_type == 0u) ? 0u :
                                       ((batch.blend_type == 1u && batch.blend_dst == 1u) ? 2u : 1u);
            vk::VkPipeline pipe = impl_->get_or_create_gx_pipeline(efb_msaa_samples_, cull_idx, depth_idx, blend_idx);
            if (!pipe || !ds) continue;

            prepared_batches.push_back({pipe, ds, dyn_off, bvp, bsc, batch.index_count, batch.index_offset});
        }
    }

    uint32_t ov_ubo_dyn_off = 0u;
    if (!ov_items.empty()) {
        const size_t ov_slot = frame_ubo_base_slot + (std::min)(ubo_slot_cursor, kMaxGxUboSlotsPerFrame - 1u);
        ov_ubo_dyn_off = static_cast<uint32_t>(ov_slot * kGxUboStride);
        GXSceneConstantsCPU oc{};
        fill_centered_43_overlay_ortho_rect(
            oc.uProjection, src_x, src_y, src_w, src_h, out_rect.width, out_rect.height);
        oc.uModelView[0][0] = oc.uModelView[1][1] = oc.uModelView[2][2] = oc.uModelView[3][3] = 1.0f;
        oc.uTevColor0[0] = oc.uTevColor0[1] = oc.uTevColor0[2] = oc.uTevColor0[3] = 1.0f;
        oc.uKonstColor[0] = oc.uKonstColor[1] = oc.uKonstColor[2] = oc.uKonstColor[3] = 1.0f;
        oc.uViewportSize[0] = out_rect.width;
        oc.uViewportSize[1] = out_rect.height;
        oc.uTevMode         = 0u;
        oc.uTevScale        = 1.0f;
        std::memcpy(static_cast<uint8_t*>(impl_->gx_ubo_mapped) + ov_ubo_dyn_off, &oc, sizeof(oc));
    }

    FxaaConstantsCPU fc{};
    fc.uInvScreenSize[0] = 1.0f / static_cast<float>((std::max)(1u, efb_width_));
    fc.uInvScreenSize[1] = 1.0f / static_cast<float>((std::max)(1u, efb_height_));
    fc.uSubpixQuality    = fxaa_subpix_quality();
    fc.uEdgeThreshold    = fxaa_edge_threshold();
    fc.uBrightness       = std::clamp(cfg_.brightness, 0.50f, 2.00f);
    fc.uGamma            = resolve_disp_gamma_value(last_disp_gamma_);
    std::memcpy(slot.fxaa_ubo_mapped, &fc, sizeof(fc));

    // Record command buffer
    vk::VkCommandBuffer cmd = slot.cmd_buf;
    impl_->vk.vkResetCommandBuffer(cmd, 0u);
    vk::VkCommandBufferBeginInfo cbbi{};
    cbbi.sType = vk::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cbbi.flags = vk::VK_COMMAND_BUFFER_USAGE_ONE_TIME_BIT;
    if (impl_->vk.vkBeginCommandBuffer(cmd, &cbbi) != vk::VK_SUCCESS) {
        impl_->recover_after_aborted_acquire(slot);
        recreate_swapchain_for_resize(swapchain_width_, swapchain_height_);
        return;
    }

    if (!pending_uploads.empty()) {
        impl_->record_pending_uploads(cmd, pending_uploads, slot);
    }

    // Pass 1: Offscreen EFB (MSAA + Resolve -> SHADER_READ_ONLY_OPTIMAL)
    const auto& gc_clr = gx.clear_rgba();
    vk::VkClearValue efb_clears[2]{};
    efb_clears[0].color.float32[0] = gc_clr[0] ? (gc_clr[0] / 255.0f) : pending_clear_color_[0];
    efb_clears[0].color.float32[1] = gc_clr[1] ? (gc_clr[1] / 255.0f) : pending_clear_color_[1];
    efb_clears[0].color.float32[2] = gc_clr[2] ? (gc_clr[2] / 255.0f) : pending_clear_color_[2];
    efb_clears[0].color.float32[3] = 1.0f;
    efb_clears[1].depthStencil     = {1.0f, 0u};

    vk::VkRenderPassBeginInfo efb_rpbi{};
    efb_rpbi.sType           = vk::VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    efb_rpbi.renderPass      = impl_->efb_render_pass;
    efb_rpbi.framebuffer     = impl_->efb_fb;
    efb_rpbi.renderArea      = {{0, 0}, {efb_width_, efb_height_}};
    efb_rpbi.clearValueCount = 2u;
    efb_rpbi.pClearValues    = efb_clears;
    impl_->vk.vkCmdBeginRenderPass(cmd, &efb_rpbi, vk::VK_SUBPASS_CONTENTS_INLINE);

    if (!prepared_batches.empty()) {
        const vk::VkDeviceSize vb_off = 0u;
        impl_->vk.vkCmdBindVertexBuffers(cmd, 0u, 1u, &slot.dyn_vb, &vb_off);
        impl_->vk.vkCmdBindIndexBuffer(cmd, slot.dyn_ib, 0u, vk::VK_INDEX_TYPE_UINT32);

        vk::VkPipeline prev_pipe = nullptr;
        bool has_prev_vp = false;
        vk::VkViewport prev_vp{};
        bool has_prev_sc = false;
        vk::VkRect2D prev_sc{};

        for (const auto& pb : prepared_batches) {
            if (pb.pipe != prev_pipe) {
                prev_pipe = pb.pipe;
                impl_->vk.vkCmdBindPipeline(cmd, 0u, pb.pipe);
            }
            if (!has_prev_vp || std::memcmp(&prev_vp, &pb.vp, sizeof(pb.vp)) != 0) {
                prev_vp = pb.vp;
                has_prev_vp = true;
                impl_->vk.vkCmdSetViewport(cmd, 0u, 1u, &pb.vp);
            }
            if (!has_prev_sc || std::memcmp(&prev_sc, &pb.sc, sizeof(pb.sc)) != 0) {
                prev_sc = pb.sc;
                has_prev_sc = true;
                impl_->vk.vkCmdSetScissor(cmd, 0u, 1u, &pb.sc);
            }
            impl_->vk.vkCmdBindDescriptorSets(
                cmd, 0u, impl_->gx_pl, 0u, 1u, &pb.desc, 1u, &pb.ubo_dyn_off);
            impl_->vk.vkCmdDrawIndexed(cmd, pb.index_count, 1u, pb.index_offset, 0, 0u);
        }
    }
    impl_->vk.vkCmdEndRenderPass(cmd);

    // Pass 2: FXAA/Blit + GDI Overlays directly onto Swapchain (ends in PRESENT_SRC_KHR)
    vk::VkClearValue sc_clear{};
    sc_clear.color.float32[3] = 1.0f;
    vk::VkRenderPassBeginInfo sc_rpbi{};
    sc_rpbi.sType           = vk::VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    sc_rpbi.renderPass      = impl_->present_render_pass;
    sc_rpbi.framebuffer     = impl_->swapchain_fbs[img_idx];
    sc_rpbi.renderArea      = {{0, 0}, {swapchain_width_, swapchain_height_}};
    sc_rpbi.clearValueCount = 1u;
    sc_rpbi.pClearValues    = &sc_clear;
    impl_->vk.vkCmdBeginRenderPass(cmd, &sc_rpbi, vk::VK_SUBPASS_CONTENTS_INLINE);

    vk::VkViewport out_vp{
        out_rect.x, out_rect.y + out_rect.height,
        out_rect.width, -out_rect.height,
        0.0f, 1.0f
    };
    vk::VkRect2D full_sc{{0, 0}, {swapchain_width_, swapchain_height_}};
    impl_->vk.vkCmdSetViewport(cmd, 0u, 1u, &out_vp);
    impl_->vk.vkCmdSetScissor(cmd, 0u, 1u, &full_sc);

    const bool use_fxaa = (cfg_.enable_fxaa || cfg_.msaa_mode == AntiAliasingMode::FXAA);
    impl_->vk.vkCmdBindPipeline(cmd, 0u, use_fxaa ? impl_->fxaa_pipeline : impl_->blit_pipeline);
    impl_->vk.vkCmdBindDescriptorSets(cmd, 0u, impl_->fxaa_pl, 0u, 1u, &slot.fxaa_desc_set, 0u, nullptr);
    impl_->vk.vkCmdDraw(cmd, 3u, 1u, 0u, 0u);

    if (!ov_items.empty()) {
        const vk::VkDeviceSize vb_off = 0u;
        impl_->vk.vkCmdBindPipeline(cmd, 0u, impl_->overlay_pipeline);
        impl_->vk.vkCmdBindVertexBuffers(cmd, 0u, 1u, &slot.dyn_vb, &vb_off);
        impl_->vk.vkCmdBindIndexBuffer(cmd, slot.dyn_ib, 0u, vk::VK_INDEX_TYPE_UINT32);
        for (const auto& oi : ov_items) {
            impl_->vk.vkCmdBindDescriptorSets(
                cmd, 0u, impl_->gx_pl, 0u, 1u, &oi.desc_set, 1u, &ov_ubo_dyn_off);
            impl_->vk.vkCmdDrawIndexed(cmd, 6u, 1u, oi.idx_off, 0, 0u);
        }
    }
    impl_->vk.vkCmdEndRenderPass(cmd);

    if (impl_->vk.vkEndCommandBuffer(cmd) != vk::VK_SUCCESS) {
        impl_->recover_after_aborted_acquire(slot);
        recreate_swapchain_for_resize(swapchain_width_, swapchain_height_);
        return;
    }

    impl_->vk.vkResetFences(impl_->device, 1u, &slot.in_flight_fence);
    const vk::VkFlags wait_stage = vk::VK_PIPELINE_STAGE_COLOR_ATT_OUT_BIT;
    vk::VkSemaphore signal_sem = impl_->render_finished_sems[img_idx];
    vk::VkSubmitInfo si{};
    si.sType                = vk::VK_STRUCTURE_TYPE_SUBMIT_INFO;
    si.waitSemaphoreCount   = 1u;
    si.pWaitSemaphores      = &slot.image_available_sem;
    si.pWaitDstStageMask    = &wait_stage;
    si.commandBufferCount   = 1u;
    si.pCommandBuffers      = &cmd;
    si.signalSemaphoreCount = 1u;
    si.pSignalSemaphores    = &signal_sem;
    if (impl_->vk.vkQueueSubmit(impl_->graphics_queue, 1u, &si, slot.in_flight_fence) != vk::VK_SUCCESS) {
        impl_->recover_after_aborted_acquire(slot);
        recreate_swapchain_for_resize(swapchain_width_, swapchain_height_);
        return;
    }

    impl_->last_submitted_slot    = fi;
    impl_->active_swapchain_image = img_idx;
    impl_->frame_submitted        = true;
    impl_->has_ever_submitted     = true;
    impl_->last_ov_items          = std::move(ov_items);
    impl_->last_ov_ubo_dyn_off    = ov_ubo_dyn_off;
    impl_->last_out_rect          = out_rect;
    batches_rendered_this_frame_  = true;
    ++impl_->frame_cursor;
}

void Win32VulkanHost::flush_vulkan() {
    submit_empty_clear_frame_if_needed();
}

void Win32VulkanHost::end_vulkan_frame_and_present() {
    if (!initialized_ || !impl_ || !impl_->swapchain) return;
    if (!impl_->frame_submitted) {
        submit_empty_clear_frame_if_needed();
    }
    if (!impl_->frame_submitted) return;

    vk::VkSemaphore wait_sem = impl_->render_finished_sems[impl_->active_swapchain_image];
    vk::VkPresentInfoKHR pi{};
    pi.sType              = vk::VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    pi.waitSemaphoreCount = 1u;
    pi.pWaitSemaphores    = &wait_sem;
    pi.swapchainCount     = 1u;
    pi.pSwapchains        = &impl_->swapchain;
    pi.pImageIndices      = &impl_->active_swapchain_image;

    const vk::VkResult pr = impl_->vk.vkQueuePresentKHR(impl_->graphics_queue, &pi);
    impl_->frame_submitted = false;
    if (pr == vk::VK_ERROR_OUT_OF_DATE_KHR || pr == vk::VK_SUBOPTIMAL_KHR) {
        recreate_swapchain_for_resize(swapchain_width_, swapchain_height_);
    }
}

bool Win32VulkanHost::dump_framebuffer_bmp(const std::string& path) {
    if (!initialized_ || !impl_ || !impl_->device || !impl_->capture_render_pass ||
        swapchain_width_ == 0u || swapchain_height_ == 0u) {
        return false;
    }
    if (!impl_->frame_submitted && !impl_->has_ever_submitted) {
        submit_empty_clear_frame_if_needed();
    }
    if (!impl_->has_ever_submitted) {
        return false;
    }

    impl_->vk.vkQueueWaitIdle(impl_->graphics_queue);

    // Render Pass 2 (FXAA/Blit from efb_resolved_view + overlays) into a dedicated TRANSFER_SRC offscreen
    // image so readback never accesses a presented swapchain image or depends on swapchain_transfer_src.
    vk::VkImage        cap_img  = nullptr;
    vk::VkDeviceMemory cap_mem  = nullptr;
    vk::VkImageView    cap_view = nullptr;
    vk::VkFramebuffer  cap_fb   = nullptr;
    if (!impl_->create_image_2d(
            swapchain_width_, swapchain_height_,
            impl_->swapchain_fmt,
            vk::VK_SAMPLE_COUNT_1_BIT,
            vk::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | vk::VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
            vk::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            cap_img, cap_mem)) {
        return false;
    }
    cap_view = impl_->create_image_view_2d(cap_img, impl_->swapchain_fmt, vk::VK_IMAGE_ASPECT_COLOR_BIT);
    if (!cap_view) {
        impl_->destroy_image(cap_img, cap_mem, cap_view);
        return false;
    }

    vk::VkFramebufferCreateInfo fbci{};
    fbci.sType           = vk::VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fbci.renderPass      = impl_->capture_render_pass;
    fbci.attachmentCount = 1u;
    fbci.pAttachments    = &cap_view;
    fbci.width           = swapchain_width_;
    fbci.height          = swapchain_height_;
    fbci.layers          = 1u;
    if (impl_->vk.vkCreateFramebuffer(impl_->device, &fbci, nullptr, &cap_fb) != vk::VK_SUCCESS || !cap_fb) {
        impl_->destroy_image(cap_img, cap_mem, cap_view);
        return false;
    }

    const size_t pitch = static_cast<size_t>(swapchain_width_) * 4u;
    const size_t bytes = pitch * swapchain_height_;
    vk::VkBuffer readback_buf = nullptr;
    vk::VkDeviceMemory readback_mem = nullptr;
    if (!impl_->create_buffer(
            bytes,
            vk::VK_BUFFER_USAGE_TRANSFER_DST_BIT,
            vk::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | vk::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            readback_buf,
            readback_mem)) {
        impl_->vk.vkDestroyFramebuffer(impl_->device, cap_fb, nullptr);
        impl_->destroy_image(cap_img, cap_mem, cap_view);
        return false;
    }

    auto& slot = impl_->frames[impl_->last_submitted_slot % kMaxFramesInFlight];
    const HostViewportRect out_rect = (impl_->last_out_rect.width > 0.0f && impl_->last_out_rect.height > 0.0f)
        ? impl_->last_out_rect
        : compute_output_viewport_rect(cfg_.aspect_ratio, swapchain_width_, swapchain_height_);

    const bool cmd_ok = impl_->submit_one_time_commands([&](vk::VkCommandBuffer cmd) {
        vk::VkClearValue sc_clear{};
        sc_clear.color.float32[3] = 1.0f;
        vk::VkRenderPassBeginInfo sc_rpbi{};
        sc_rpbi.sType           = vk::VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        sc_rpbi.renderPass      = impl_->capture_render_pass;
        sc_rpbi.framebuffer     = cap_fb;
        sc_rpbi.renderArea      = {{0, 0}, {swapchain_width_, swapchain_height_}};
        sc_rpbi.clearValueCount = 1u;
        sc_rpbi.pClearValues    = &sc_clear;
        impl_->vk.vkCmdBeginRenderPass(cmd, &sc_rpbi, vk::VK_SUBPASS_CONTENTS_INLINE);

        vk::VkViewport out_vp{
            out_rect.x, out_rect.y + out_rect.height,
            out_rect.width, -out_rect.height,
            0.0f, 1.0f
        };
        vk::VkRect2D full_sc{{0, 0}, {swapchain_width_, swapchain_height_}};
        impl_->vk.vkCmdSetViewport(cmd, 0u, 1u, &out_vp);
        impl_->vk.vkCmdSetScissor(cmd, 0u, 1u, &full_sc);

        const bool use_fxaa = (cfg_.enable_fxaa || cfg_.msaa_mode == AntiAliasingMode::FXAA);
        impl_->vk.vkCmdBindPipeline(cmd, 0u, use_fxaa ? impl_->fxaa_pipeline : impl_->blit_pipeline);
        impl_->vk.vkCmdBindDescriptorSets(cmd, 0u, impl_->fxaa_pl, 0u, 1u, &slot.fxaa_desc_set, 0u, nullptr);
        impl_->vk.vkCmdDraw(cmd, 3u, 1u, 0u, 0u);

        if (!impl_->last_ov_items.empty() && slot.dyn_vb && slot.dyn_ib) {
            const vk::VkDeviceSize vb_off = 0u;
            impl_->vk.vkCmdBindPipeline(cmd, 0u, impl_->overlay_pipeline);
            impl_->vk.vkCmdBindVertexBuffers(cmd, 0u, 1u, &slot.dyn_vb, &vb_off);
            impl_->vk.vkCmdBindIndexBuffer(cmd, slot.dyn_ib, 0u, vk::VK_INDEX_TYPE_UINT32);
            for (const auto& oi : impl_->last_ov_items) {
                impl_->vk.vkCmdBindDescriptorSets(
                    cmd, 0u, impl_->gx_pl, 0u, 1u, &oi.desc_set, 1u, &impl_->last_ov_ubo_dyn_off);
                impl_->vk.vkCmdDrawIndexed(cmd, 6u, 1u, oi.idx_off, 0, 0u);
            }
        }
        impl_->vk.vkCmdEndRenderPass(cmd);

        impl_->cmd_barrier_image(
            cmd, cap_img, vk::VK_IMAGE_ASPECT_COLOR_BIT,
            vk::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
            vk::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
            vk::VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            vk::VK_ACCESS_TRANSFER_READ_BIT,
            vk::VK_PIPELINE_STAGE_COLOR_ATT_OUT_BIT,
            vk::VK_PIPELINE_STAGE_TRANSFER_BIT);

        vk::VkBufferImageCopy region{};
        region.imageSubresource.aspectMask = vk::VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.layerCount = 1u;
        region.imageExtent                 = {swapchain_width_, swapchain_height_, 1u};
        impl_->vk.vkCmdCopyImageToBuffer(
            cmd, cap_img, vk::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, readback_buf, 1u, &region);
    });

    bool ok = false;
    if (cmd_ok) {
        void* mapped = nullptr;
        if (impl_->vk.vkMapMemory(impl_->device, readback_mem, 0, bytes, 0, &mapped) == vk::VK_SUCCESS && mapped) {
            ok = write_bmp24_from_rgba8(
                path,
                swapchain_width_,
                swapchain_height_,
                static_cast<const uint8_t*>(mapped),
                pitch,
                impl_->swapchain_bgra);
            impl_->vk.vkUnmapMemory(impl_->device, readback_mem);
        }
    }
    impl_->destroy_buffer(readback_buf, readback_mem);
    impl_->vk.vkDestroyFramebuffer(impl_->device, cap_fb, nullptr);
    impl_->destroy_image(cap_img, cap_mem, cap_view);
    return ok;
}

} // namespace pn03

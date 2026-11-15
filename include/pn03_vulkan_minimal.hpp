#pragma once

// Self-contained Vulkan 1.3 + Win32 surface C ABI minimal declarations and
// dynamic vulkan-1.dll loader (zero external Vulkan SDK headers/libs required).

#include <cstddef>
#include <cstdint>
#include <cstring>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

#ifndef VKAPI_CALL
#ifdef _WIN32
#define VKAPI_CALL __stdcall
#else
#define VKAPI_CALL
#endif
#endif

#define PN03_VK_MAKE_API_VERSION(variant, major, minor, patch) \
    ((static_cast<uint32_t>(variant) << 29) | (static_cast<uint32_t>(major) << 22) | \
     (static_cast<uint32_t>(minor) << 12) | static_cast<uint32_t>(patch))

#define PN03_VK_API_VERSION_1_0 PN03_VK_MAKE_API_VERSION(0, 1, 0, 0)
#define PN03_VK_API_VERSION_1_3 PN03_VK_MAKE_API_VERSION(0, 1, 3, 0)

#if defined(__LP64__) || defined(_WIN64) || defined(__x86_64__) || defined(_M_X64)
#define PN03_VK_DEFINE_HANDLE(name) struct name##_T; using name = name##_T*;
#define PN03_VK_DEFINE_ND_HANDLE(name) struct name##_T; using name = name##_T*;
#else
#define PN03_VK_DEFINE_HANDLE(name) struct name##_T; using name = name##_T*;
#define PN03_VK_DEFINE_ND_HANDLE(name) using name = uint64_t;
#endif

namespace pn03::vk {

using VkBool32     = uint32_t;
using VkFlags      = uint32_t;
using VkDeviceSize = uint64_t;
using VkSampleMask = uint32_t;
using VkResult     = int32_t;

constexpr VkBool32     VK_FALSE         = 0u;
constexpr VkBool32     VK_TRUE          = 1u;
constexpr uint64_t     VK_WHOLE_SIZE    = ~0ULL;
constexpr uint32_t     VK_QUEUE_FAMILY_IGNORED = ~0u;
constexpr uint32_t     VK_SUBPASS_EXTERNAL     = ~0u;

constexpr VkResult VK_SUCCESS           = 0;
constexpr VkResult VK_SUBOPTIMAL_KHR    = 1000001003;
constexpr VkResult VK_ERROR_OUT_OF_DATE_KHR = -1000001004;

PN03_VK_DEFINE_HANDLE(VkInstance)
PN03_VK_DEFINE_HANDLE(VkPhysicalDevice)
PN03_VK_DEFINE_HANDLE(VkDevice)
PN03_VK_DEFINE_HANDLE(VkQueue)
PN03_VK_DEFINE_HANDLE(VkCommandBuffer)

PN03_VK_DEFINE_ND_HANDLE(VkSurfaceKHR)
PN03_VK_DEFINE_ND_HANDLE(VkSwapchainKHR)
PN03_VK_DEFINE_ND_HANDLE(VkSemaphore)
PN03_VK_DEFINE_ND_HANDLE(VkFence)
PN03_VK_DEFINE_ND_HANDLE(VkDeviceMemory)
PN03_VK_DEFINE_ND_HANDLE(VkBuffer)
PN03_VK_DEFINE_ND_HANDLE(VkImage)
PN03_VK_DEFINE_ND_HANDLE(VkImageView)
PN03_VK_DEFINE_ND_HANDLE(VkSampler)
PN03_VK_DEFINE_ND_HANDLE(VkShaderModule)
PN03_VK_DEFINE_ND_HANDLE(VkDescriptorSetLayout)
PN03_VK_DEFINE_ND_HANDLE(VkDescriptorPool)
PN03_VK_DEFINE_ND_HANDLE(VkDescriptorSet)
PN03_VK_DEFINE_ND_HANDLE(VkPipelineLayout)
PN03_VK_DEFINE_ND_HANDLE(VkRenderPass)
PN03_VK_DEFINE_ND_HANDLE(VkFramebuffer)
PN03_VK_DEFINE_ND_HANDLE(VkPipelineCache)
PN03_VK_DEFINE_ND_HANDLE(VkPipeline)
PN03_VK_DEFINE_ND_HANDLE(VkCommandPool)

enum VkStructureType : uint32_t {
    VK_STRUCTURE_TYPE_APPLICATION_INFO                         = 0,
    VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO                     = 1,
    VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO                 = 2,
    VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO                       = 3,
    VK_STRUCTURE_TYPE_SUBMIT_INFO                              = 4,
    VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO                     = 5,
    VK_STRUCTURE_TYPE_FENCE_CREATE_INFO                        = 8,
    VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO                    = 9,
    VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO                       = 12,
    VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO                        = 14,
    VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO                   = 15,
    VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO                = 16,
    VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO        = 18,
    VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO  = 19,
    VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO= 20,
    VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO      = 22,
    VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO = 23,
    VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO   = 24,
    VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO = 25,
    VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO   = 26,
    VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO       = 27,
    VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO            = 28,
    VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO              = 30,
    VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO                      = 31,
    VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO        = 32,
    VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO              = 33,
    VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO             = 34,
    VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET                     = 35,
    VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO                  = 37,
    VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO                  = 38,
    VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO                 = 39,
    VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO             = 40,
    VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO                = 42,
    VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO                   = 43,
    VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER                     = 45,
    VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR                = 1000001000,
    VK_STRUCTURE_TYPE_PRESENT_INFO_KHR                         = 1000001001,
    VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR            = 1000009000,
};

enum VkFormat : uint32_t {
    VK_FORMAT_UNDEFINED           = 0,
    VK_FORMAT_R8G8B8A8_UNORM      = 37,
    VK_FORMAT_B8G8R8A8_UNORM      = 44,
    VK_FORMAT_R32G32_SFLOAT       = 103,
    VK_FORMAT_R32G32B32_SFLOAT    = 106,
    VK_FORMAT_R32G32B32A32_SFLOAT = 109,
    VK_FORMAT_D32_SFLOAT          = 126,
    VK_FORMAT_D24_UNORM_S8_UINT   = 129,
    VK_FORMAT_D32_SFLOAT_S8_UINT  = 130,
};

enum VkColorSpaceKHR : uint32_t {
    VK_COLOR_SPACE_SRGB_NONLINEAR_KHR = 0,
};

enum VkPresentModeKHR : uint32_t {
    VK_PRESENT_MODE_IMMEDIATE_KHR = 0,
    VK_PRESENT_MODE_MAILBOX_KHR   = 1,
    VK_PRESENT_MODE_FIFO_KHR      = 2,
};

enum VkImageType : uint32_t {
    VK_IMAGE_TYPE_2D = 1,
};

enum VkImageViewType : uint32_t {
    VK_IMAGE_VIEW_TYPE_2D = 1,
};

enum VkImageTiling : uint32_t {
    VK_IMAGE_TILING_OPTIMAL = 0,
    VK_IMAGE_TILING_LINEAR  = 1,
};

enum VkImageLayout : uint32_t {
    VK_IMAGE_LAYOUT_UNDEFINED                        = 0,
    VK_IMAGE_LAYOUT_GENERAL                          = 1,
    VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL         = 2,
    VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL = 3,
    VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL         = 5,
    VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL             = 6,
    VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL             = 7,
    VK_IMAGE_LAYOUT_PRESENT_SRC_KHR                  = 1000001002,
};

enum VkAttachmentLoadOp : uint32_t {
    VK_ATTACHMENT_LOAD_OP_LOAD      = 0,
    VK_ATTACHMENT_LOAD_OP_CLEAR     = 1,
    VK_ATTACHMENT_LOAD_OP_DONT_CARE = 2,
};

enum VkAttachmentStoreOp : uint32_t {
    VK_ATTACHMENT_STORE_OP_STORE     = 0,
    VK_ATTACHMENT_STORE_OP_DONT_CARE = 1,
};

enum VkPrimitiveTopology : uint32_t {
    VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST = 3,
};

enum VkPolygonMode : uint32_t {
    VK_POLYGON_MODE_FILL = 0,
};

enum VkFrontFace : uint32_t {
    VK_FRONT_FACE_COUNTER_CLOCKWISE = 0,
    VK_FRONT_FACE_CLOCKWISE         = 1,
};

enum VkCompareOp : uint32_t {
    VK_COMPARE_OP_NEVER            = 0,
    VK_COMPARE_OP_LESS             = 1,
    VK_COMPARE_OP_EQUAL            = 2,
    VK_COMPARE_OP_LESS_OR_EQUAL    = 3,
    VK_COMPARE_OP_GREATER          = 4,
    VK_COMPARE_OP_NOT_EQUAL        = 5,
    VK_COMPARE_OP_GREATER_OR_EQUAL = 6,
    VK_COMPARE_OP_ALWAYS           = 7,
};

enum VkBlendFactor : uint32_t {
    VK_BLEND_FACTOR_ZERO                = 0,
    VK_BLEND_FACTOR_ONE                 = 1,
    VK_BLEND_FACTOR_SRC_ALPHA           = 6,
    VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA = 7,
};

enum VkBlendOp : uint32_t {
    VK_BLEND_OP_ADD = 0,
};

enum VkDynamicState : uint32_t {
    VK_DYNAMIC_STATE_VIEWPORT = 0,
    VK_DYNAMIC_STATE_SCISSOR  = 1,
};

enum VkDescriptorType : uint32_t {
    VK_DESCRIPTOR_TYPE_SAMPLER                = 0,
    VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER = 1,
    VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER         = 6,
    VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC = 8,
};

enum VkFilter : uint32_t {
    VK_FILTER_NEAREST = 0,
    VK_FILTER_LINEAR  = 1,
};

enum VkSamplerMipmapMode : uint32_t {
    VK_SAMPLER_MIPMAP_MODE_NEAREST = 0,
    VK_SAMPLER_MIPMAP_MODE_LINEAR  = 1,
};

enum VkSamplerAddressMode : uint32_t {
    VK_SAMPLER_ADDRESS_MODE_REPEAT          = 0,
    VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT = 1,
    VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE   = 2,
};

enum VkVertexInputRate : uint32_t {
    VK_VERTEX_INPUT_RATE_VERTEX = 0,
};

enum VkSubpassContents : uint32_t {
    VK_SUBPASS_CONTENTS_INLINE = 0,
};

enum VkSharingMode : uint32_t {
    VK_SHARING_MODE_EXCLUSIVE = 0,
};

enum VkIndexType : uint32_t {
    VK_INDEX_TYPE_UINT32 = 1,
};

// Flag bitmasks
constexpr VkFlags VK_QUEUE_GRAPHICS_BIT                 = 0x00000001u;
constexpr VkFlags VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT   = 0x00000001u;
constexpr VkFlags VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT   = 0x00000002u;
constexpr VkFlags VK_MEMORY_PROPERTY_HOST_COHERENT_BIT  = 0x00000004u;
constexpr VkFlags VK_BUFFER_USAGE_TRANSFER_SRC_BIT      = 0x00000001u;
constexpr VkFlags VK_BUFFER_USAGE_TRANSFER_DST_BIT      = 0x00000002u;
constexpr VkFlags VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT    = 0x00000010u;
constexpr VkFlags VK_BUFFER_USAGE_INDEX_BUFFER_BIT      = 0x00000040u;
constexpr VkFlags VK_BUFFER_USAGE_VERTEX_BUFFER_BIT     = 0x00000080u;
constexpr VkFlags VK_IMAGE_USAGE_TRANSFER_SRC_BIT       = 0x00000001u;
constexpr VkFlags VK_IMAGE_USAGE_TRANSFER_DST_BIT       = 0x00000002u;
constexpr VkFlags VK_IMAGE_USAGE_SAMPLED_BIT            = 0x00000004u;
constexpr VkFlags VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT   = 0x00000010u;
constexpr VkFlags VK_IMAGE_USAGE_DEPTH_STENCIL_ATT_BIT  = 0x00000020u;
constexpr VkFlags VK_IMAGE_ASPECT_COLOR_BIT             = 0x00000001u;
constexpr VkFlags VK_IMAGE_ASPECT_DEPTH_BIT             = 0x00000002u;
constexpr VkFlags VK_IMAGE_ASPECT_STENCIL_BIT           = 0x00000004u;
constexpr VkFlags VK_FORMAT_FEATURE_DEPTH_STENCIL_ATT_BIT = 0x00000200u;
constexpr VkFlags VK_SHADER_STAGE_VERTEX_BIT            = 0x00000001u;
constexpr VkFlags VK_SHADER_STAGE_FRAGMENT_BIT          = 0x00000010u;
constexpr VkFlags VK_CULL_MODE_NONE                     = 0x00000000u;
constexpr VkFlags VK_CULL_MODE_FRONT_BIT                = 0x00000001u;
constexpr VkFlags VK_CULL_MODE_BACK_BIT                 = 0x00000002u;
constexpr VkFlags VK_SAMPLE_COUNT_1_BIT                 = 0x00000001u;
constexpr VkFlags VK_SAMPLE_COUNT_2_BIT                 = 0x00000002u;
constexpr VkFlags VK_SAMPLE_COUNT_4_BIT                 = 0x00000004u;
constexpr VkFlags VK_SAMPLE_COUNT_8_BIT                 = 0x00000008u;
constexpr VkFlags VK_COLOR_COMPONENT_ALL                = 0x0000000Fu;
constexpr VkFlags VK_FENCE_CREATE_SIGNALED_BIT          = 0x00000001u;
constexpr VkFlags VK_COMMAND_POOL_CREATE_RESET_CB_BIT   = 0x00000002u;
constexpr VkFlags VK_COMMAND_BUFFER_USAGE_ONE_TIME_BIT  = 0x00000001u;
constexpr VkFlags VK_DESCRIPTOR_POOL_CREATE_FREE_SET_BIT= 0x00000001u;
constexpr VkFlags VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR     = 0x00000001u;
constexpr VkFlags VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT     = 0x00000001u;
constexpr VkFlags VK_PIPELINE_STAGE_VERTEX_INPUT_BIT    = 0x00000004u;
constexpr VkFlags VK_PIPELINE_STAGE_EARLY_FRAG_BIT      = 0x00000100u;
constexpr VkFlags VK_PIPELINE_STAGE_COLOR_ATT_OUT_BIT   = 0x00000400u;
constexpr VkFlags VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT = 0x00000080u;
constexpr VkFlags VK_PIPELINE_STAGE_TRANSFER_BIT        = 0x00001000u;
constexpr VkFlags VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT  = 0x00002000u;
constexpr VkFlags VK_PIPELINE_STAGE_HOST_BIT            = 0x00004000u;
constexpr VkFlags VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT    = 0x00008000u;
constexpr VkFlags VK_ACCESS_SHADER_READ_BIT             = 0x00000020u;
constexpr VkFlags VK_ACCESS_COLOR_ATTACHMENT_READ_BIT   = 0x00000080u;
constexpr VkFlags VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT  = 0x00000100u;
constexpr VkFlags VK_ACCESS_DEPTH_STENCIL_ATT_WRITE_BIT = 0x00000400u;
constexpr VkFlags VK_ACCESS_TRANSFER_READ_BIT           = 0x00000800u;
constexpr VkFlags VK_ACCESS_TRANSFER_WRITE_BIT          = 0x00001000u;
constexpr VkFlags VK_ACCESS_HOST_READ_BIT               = 0x00002000u;

struct VkExtent2D {
    uint32_t width;
    uint32_t height;
};

struct VkExtent3D {
    uint32_t width;
    uint32_t height;
    uint32_t depth;
};

struct VkOffset2D {
    int32_t x;
    int32_t y;
};

struct VkOffset3D {
    int32_t x;
    int32_t y;
    int32_t z;
};

struct VkRect2D {
    VkOffset2D offset;
    VkExtent2D extent;
};

struct VkViewport {
    float x;
    float y;
    float width;
    float height;
    float minDepth;
    float maxDepth;
};

struct VkApplicationInfo {
    VkStructureType sType;
    const void*     pNext;
    const char*     pApplicationName;
    uint32_t        applicationVersion;
    const char*     pEngineName;
    uint32_t        engineVersion;
    uint32_t        apiVersion;
};

struct VkInstanceCreateInfo {
    VkStructureType    sType;
    const void*        pNext;
    VkFlags            flags;
    const VkApplicationInfo* pApplicationInfo;
    uint32_t           enabledLayerCount;
    const char* const* ppEnabledLayerNames;
    uint32_t           enabledExtensionCount;
    const char* const* ppEnabledExtensionNames;
};

struct VkPhysicalDevicePropertiesHeader {
    uint32_t apiVersion;
    uint32_t driverVersion;
    uint32_t vendorID;
    uint32_t deviceID;
    uint32_t deviceType;
    char     deviceName[256];
    uint8_t  pipelineCacheUUID[16];
    uint8_t  limitsAndSparsePadding[1024];
};

struct VkPhysicalDeviceFeatures {
    VkBool32 features[55]; // samplerAnisotropy is index 19
};

struct VkFormatProperties {
    VkFlags linearTilingFeatures;
    VkFlags optimalTilingFeatures;
    VkFlags bufferFeatures;
};

struct VkImageFormatProperties {
    VkExtent3D   maxExtent;
    uint32_t     maxMipLevels;
    uint32_t     maxArrayLayers;
    VkFlags      sampleCounts;
    VkDeviceSize maxResourceSize;
};

struct VkQueueFamilyProperties {
    VkFlags    queueFlags;
    uint32_t   queueCount;
    uint32_t   timestampValidBits;
    VkExtent3D minImageTransferGranularity;
};

struct VkMemoryType {
    VkFlags  propertyFlags;
    uint32_t heapIndex;
};

struct VkMemoryHeap {
    VkDeviceSize size;
    VkFlags      flags;
};

struct VkPhysicalDeviceMemoryProperties {
    uint32_t     memoryTypeCount;
    VkMemoryType memoryTypes[32];
    uint32_t     memoryHeapCount;
    VkMemoryHeap memoryHeaps[16];
};

struct VkMemoryRequirements {
    VkDeviceSize size;
    VkDeviceSize alignment;
    uint32_t     memoryTypeBits;
};

struct VkDeviceQueueCreateInfo {
    VkStructureType sType;
    const void*     pNext;
    VkFlags         flags;
    uint32_t        queueFamilyIndex;
    uint32_t        queueCount;
    const float*    pQueuePriorities;
};

struct VkDeviceCreateInfo {
    VkStructureType                 sType;
    const void*                     pNext;
    VkFlags                         flags;
    uint32_t                        queueCreateInfoCount;
    const VkDeviceQueueCreateInfo*  pQueueCreateInfos;
    uint32_t                        enabledLayerCount;
    const char* const*              ppEnabledLayerNames;
    uint32_t                        enabledExtensionCount;
    const char* const*              ppEnabledExtensionNames;
    const VkPhysicalDeviceFeatures* pEnabledFeatures;
};

struct VkWin32SurfaceCreateInfoKHR {
    VkStructureType sType;
    const void*     pNext;
    VkFlags         flags;
    void*           hinstance;
    void*           hwnd;
};

struct VkSurfaceCapabilitiesKHR {
    uint32_t   minImageCount;
    uint32_t   maxImageCount;
    VkExtent2D currentExtent;
    VkExtent2D minImageExtent;
    VkExtent2D maxImageExtent;
    uint32_t   maxImageArrayLayers;
    VkFlags    supportedTransforms;
    VkFlags    currentTransform;
    VkFlags    supportedCompositeAlpha;
    VkFlags    supportedUsageFlags;
};

struct VkSurfaceFormatKHR {
    VkFormat        format;
    VkColorSpaceKHR colorSpace;
};

struct VkSwapchainCreateInfoKHR {
    VkStructureType  sType;
    const void*      pNext;
    VkFlags          flags;
    VkSurfaceKHR     surface;
    uint32_t         minImageCount;
    VkFormat         imageFormat;
    VkColorSpaceKHR  imageColorSpace;
    VkExtent2D       imageExtent;
    uint32_t         imageArrayLayers;
    VkFlags          imageUsage;
    VkSharingMode    imageSharingMode;
    uint32_t         queueFamilyIndexCount;
    const uint32_t*  pQueueFamilyIndices;
    VkFlags          preTransform;
    VkFlags          compositeAlpha;
    VkPresentModeKHR presentMode;
    VkBool32         clipped;
    VkSwapchainKHR   oldSwapchain;
};

struct VkPresentInfoKHR {
    VkStructureType       sType;
    const void*           pNext;
    uint32_t              waitSemaphoreCount;
    const VkSemaphore*    pWaitSemaphores;
    uint32_t              swapchainCount;
    const VkSwapchainKHR* pSwapchains;
    const uint32_t*       pImageIndices;
    VkResult*             pResults;
};

struct VkBufferCreateInfo {
    VkStructureType sType;
    const void*     pNext;
    VkFlags         flags;
    VkDeviceSize    size;
    VkFlags         usage;
    VkSharingMode   sharingMode;
    uint32_t        queueFamilyIndexCount;
    const uint32_t* pQueueFamilyIndices;
};

struct VkMemoryAllocateInfo {
    VkStructureType sType;
    const void*     pNext;
    VkDeviceSize    allocationSize;
    uint32_t        memoryTypeIndex;
};

struct VkImageCreateInfo {
    VkStructureType sType;
    const void*     pNext;
    VkFlags         flags;
    VkImageType     imageType;
    VkFormat        format;
    VkExtent3D      extent;
    uint32_t        mipLevels;
    uint32_t        arrayLayers;
    VkFlags         samples;
    VkImageTiling   tiling;
    VkFlags         usage;
    VkSharingMode   sharingMode;
    uint32_t        queueFamilyIndexCount;
    const uint32_t* pQueueFamilyIndices;
    VkImageLayout   initialLayout;
};

struct VkComponentMapping {
    uint32_t r;
    uint32_t g;
    uint32_t b;
    uint32_t a;
};

struct VkImageSubresourceRange {
    VkFlags  aspectMask;
    uint32_t baseMipLevel;
    uint32_t levelCount;
    uint32_t baseArrayLayer;
    uint32_t layerCount;
};

struct VkImageViewCreateInfo {
    VkStructureType         sType;
    const void*             pNext;
    VkFlags                 flags;
    VkImage                 image;
    VkImageViewType         viewType;
    VkFormat                format;
    VkComponentMapping      components;
    VkImageSubresourceRange subresourceRange;
};

struct VkImageSubresourceLayers {
    VkFlags  aspectMask;
    uint32_t mipLevel;
    uint32_t baseArrayLayer;
    uint32_t layerCount;
};

struct VkBufferImageCopy {
    VkDeviceSize             bufferOffset;
    uint32_t                 bufferRowLength;
    uint32_t                 bufferImageHeight;
    VkImageSubresourceLayers imageSubresource;
    VkOffset3D               imageOffset;
    VkExtent3D               imageExtent;
};

struct VkImageMemoryBarrier {
    VkStructureType         sType;
    const void*             pNext;
    VkFlags                 srcAccessMask;
    VkFlags                 dstAccessMask;
    VkImageLayout           oldLayout;
    VkImageLayout           newLayout;
    uint32_t                srcQueueFamilyIndex;
    uint32_t                dstQueueFamilyIndex;
    VkImage                 image;
    VkImageSubresourceRange subresourceRange;
};

struct VkSamplerCreateInfo {
    VkStructureType      sType;
    const void*          pNext;
    VkFlags              flags;
    VkFilter             magFilter;
    VkFilter             minFilter;
    VkSamplerMipmapMode  mipmapMode;
    VkSamplerAddressMode addressModeU;
    VkSamplerAddressMode addressModeV;
    VkSamplerAddressMode addressModeW;
    float                mipLodBias;
    VkBool32             anisotropyEnable;
    float                maxAnisotropy;
    VkBool32             compareEnable;
    VkCompareOp          compareOp;
    float                minLod;
    float                maxLod;
    uint32_t             borderColor;
    VkBool32             unnormalizedCoordinates;
};

struct VkShaderModuleCreateInfo {
    VkStructureType sType;
    const void*     pNext;
    VkFlags         flags;
    size_t          codeSize;
    const uint32_t* pCode;
};

struct VkDescriptorSetLayoutBinding {
    uint32_t         binding;
    VkDescriptorType descriptorType;
    uint32_t         descriptorCount;
    VkFlags          stageFlags;
    const VkSampler* pImmutableSamplers;
};

struct VkDescriptorSetLayoutCreateInfo {
    VkStructureType                     sType;
    const void*                         pNext;
    VkFlags                             flags;
    uint32_t                            bindingCount;
    const VkDescriptorSetLayoutBinding* pBindings;
};

struct VkDescriptorPoolSize {
    VkDescriptorType type;
    uint32_t         descriptorCount;
};

struct VkDescriptorPoolCreateInfo {
    VkStructureType             sType;
    const void*                 pNext;
    VkFlags                     flags;
    uint32_t                    maxSets;
    uint32_t                    poolSizeCount;
    const VkDescriptorPoolSize* pPoolSizes;
};

struct VkDescriptorSetAllocateInfo {
    VkStructureType              sType;
    const void*                  pNext;
    VkDescriptorPool             descriptorPool;
    uint32_t                     descriptorSetCount;
    const VkDescriptorSetLayout* pSetLayouts;
};

struct VkDescriptorImageInfo {
    VkSampler     sampler;
    VkImageView   imageView;
    VkImageLayout imageLayout;
};

struct VkDescriptorBufferInfo {
    VkBuffer     buffer;
    VkDeviceSize offset;
    VkDeviceSize range;
};

struct VkWriteDescriptorSet {
    VkStructureType               sType;
    const void*                   pNext;
    VkDescriptorSet               dstSet;
    uint32_t                      dstBinding;
    uint32_t                      dstArrayElement;
    uint32_t                      descriptorCount;
    VkDescriptorType              descriptorType;
    const VkDescriptorImageInfo*  pImageInfo;
    const VkDescriptorBufferInfo* pBufferInfo;
    const void*                   pTexelBufferView;
};

struct VkPipelineLayoutCreateInfo {
    VkStructureType              sType;
    const void*                  pNext;
    VkFlags                      flags;
    uint32_t                     setLayoutCount;
    const VkDescriptorSetLayout* pSetLayouts;
    uint32_t                     pushConstantRangeCount;
    const void*                  pPushConstantRanges;
};

struct VkAttachmentDescription {
    VkFlags             flags;
    VkFormat            format;
    VkFlags             samples;
    VkAttachmentLoadOp  loadOp;
    VkAttachmentStoreOp storeOp;
    VkAttachmentLoadOp  stencilLoadOp;
    VkAttachmentStoreOp stencilStoreOp;
    VkImageLayout       initialLayout;
    VkImageLayout       finalLayout;
};

struct VkAttachmentReference {
    uint32_t      attachment;
    VkImageLayout layout;
};

struct VkSubpassDescription {
    VkFlags                      flags;
    uint32_t                     pipelineBindPoint;
    uint32_t                     inputAttachmentCount;
    const VkAttachmentReference* pInputAttachments;
    uint32_t                     colorAttachmentCount;
    const VkAttachmentReference* pColorAttachments;
    const VkAttachmentReference* pResolveAttachments;
    const VkAttachmentReference* pDepthStencilAttachment;
    uint32_t                     preserveAttachmentCount;
    const uint32_t*              pPreserveAttachments;
};

struct VkSubpassDependency {
    uint32_t srcSubpass;
    uint32_t dstSubpass;
    VkFlags  srcStageMask;
    VkFlags  dstStageMask;
    VkFlags  srcAccessMask;
    VkFlags  dstAccessMask;
    VkFlags  dependencyFlags;
};

struct VkRenderPassCreateInfo {
    VkStructureType                sType;
    const void*                    pNext;
    VkFlags                        flags;
    uint32_t                       attachmentCount;
    const VkAttachmentDescription* pAttachments;
    uint32_t                       subpassCount;
    const VkSubpassDescription*    pSubpasses;
    uint32_t                       dependencyCount;
    const VkSubpassDependency*     pDependencies;
};

struct VkFramebufferCreateInfo {
    VkStructureType    sType;
    const void*        pNext;
    VkFlags            flags;
    VkRenderPass       renderPass;
    uint32_t           attachmentCount;
    const VkImageView* pAttachments;
    uint32_t           width;
    uint32_t           height;
    uint32_t           layers;
};

struct VkPipelineShaderStageCreateInfo {
    VkStructureType sType;
    const void*     pNext;
    VkFlags         flags;
    VkFlags         stage;
    VkShaderModule  module;
    const char*     pName;
    const void*     pSpecializationInfo;
};

struct VkVertexInputBindingDescription {
    uint32_t          binding;
    uint32_t          stride;
    VkVertexInputRate inputRate;
};

struct VkVertexInputAttributeDescription {
    uint32_t location;
    uint32_t binding;
    VkFormat format;
    uint32_t offset;
};

struct VkPipelineVertexInputStateCreateInfo {
    VkStructureType                          sType;
    const void*                              pNext;
    VkFlags                                  flags;
    uint32_t                                 vertexBindingDescriptionCount;
    const VkVertexInputBindingDescription*   pVertexBindingDescriptions;
    uint32_t                                 vertexAttributeDescriptionCount;
    const VkVertexInputAttributeDescription* pVertexAttributeDescriptions;
};

struct VkPipelineInputAssemblyStateCreateInfo {
    VkStructureType     sType;
    const void*         pNext;
    VkFlags             flags;
    VkPrimitiveTopology topology;
    VkBool32            primitiveRestartEnable;
};

struct VkPipelineViewportStateCreateInfo {
    VkStructureType   sType;
    const void*       pNext;
    VkFlags           flags;
    uint32_t          viewportCount;
    const VkViewport* pViewports;
    uint32_t          scissorCount;
    const VkRect2D*   pScissors;
};

struct VkPipelineRasterizationStateCreateInfo {
    VkStructureType sType;
    const void*     pNext;
    VkFlags         flags;
    VkBool32        depthClampEnable;
    VkBool32        rasterizerDiscardEnable;
    VkPolygonMode   polygonMode;
    VkFlags         cullMode;
    VkFrontFace     frontFace;
    VkBool32        depthBiasEnable;
    float           depthBiasConstantFactor;
    float           depthBiasClamp;
    float           depthBiasSlopeFactor;
    float           lineWidth;
};

struct VkPipelineMultisampleStateCreateInfo {
    VkStructureType     sType;
    const void*         pNext;
    VkFlags             flags;
    VkFlags             rasterizationSamples;
    VkBool32            sampleShadingEnable;
    float               minSampleShading;
    const VkSampleMask* pSampleMask;
    VkBool32            alphaToCoverageEnable;
    VkBool32            alphaToOneEnable;
};

struct VkStencilOpState {
    uint32_t    failOp;
    uint32_t    passOp;
    uint32_t    depthFailOp;
    VkCompareOp compareOp;
    uint32_t    compareMask;
    uint32_t    writeMask;
    uint32_t    reference;
};

struct VkPipelineDepthStencilStateCreateInfo {
    VkStructureType  sType;
    const void*      pNext;
    VkFlags          flags;
    VkBool32         depthTestEnable;
    VkBool32         depthWriteEnable;
    VkCompareOp      depthCompareOp;
    VkBool32         depthBoundsTestEnable;
    VkBool32         stencilTestEnable;
    VkStencilOpState front;
    VkStencilOpState back;
    float            minDepthBounds;
    float            maxDepthBounds;
};

struct VkPipelineColorBlendAttachmentState {
    VkBool32      blendEnable;
    VkBlendFactor srcColorBlendFactor;
    VkBlendFactor dstColorBlendFactor;
    VkBlendOp     colorBlendOp;
    VkBlendFactor srcAlphaBlendFactor;
    VkBlendFactor dstAlphaBlendFactor;
    VkBlendOp     alphaBlendOp;
    VkFlags       colorWriteMask;
};

struct VkPipelineColorBlendStateCreateInfo {
    VkStructureType                            sType;
    const void*                                pNext;
    VkFlags                                    flags;
    VkBool32                                   logicOpEnable;
    uint32_t                                   logicOp;
    uint32_t                                   attachmentCount;
    const VkPipelineColorBlendAttachmentState* pAttachments;
    float                                      blendConstants[4];
};

struct VkPipelineDynamicStateCreateInfo {
    VkStructureType       sType;
    const void*           pNext;
    VkFlags               flags;
    uint32_t              dynamicStateCount;
    const VkDynamicState* pDynamicStates;
};

struct VkGraphicsPipelineCreateInfo {
    VkStructureType                               sType;
    const void*                                   pNext;
    VkFlags                                       flags;
    uint32_t                                      stageCount;
    const VkPipelineShaderStageCreateInfo*        pStages;
    const VkPipelineVertexInputStateCreateInfo*   pVertexInputState;
    const VkPipelineInputAssemblyStateCreateInfo* pInputAssemblyState;
    const void*                                   pTessellationState;
    const VkPipelineViewportStateCreateInfo*      pViewportState;
    const VkPipelineRasterizationStateCreateInfo* pRasterizationState;
    const VkPipelineMultisampleStateCreateInfo*   pMultisampleState;
    const VkPipelineDepthStencilStateCreateInfo*  pDepthStencilState;
    const VkPipelineColorBlendStateCreateInfo*    pColorBlendState;
    const VkPipelineDynamicStateCreateInfo*       pDynamicState;
    VkPipelineLayout                              layout;
    VkRenderPass                                  renderPass;
    uint32_t                                      subpass;
    VkPipeline                                    basePipelineHandle;
    int32_t                                       basePipelineIndex;
};

union VkClearColorValue {
    float    float32[4];
    int32_t  int32[4];
    uint32_t uint32[4];
};

struct VkClearDepthStencilValue {
    float    depth;
    uint32_t stencil;
};

union VkClearValue {
    VkClearColorValue        color;
    VkClearDepthStencilValue depthStencil;
};

struct VkRenderPassBeginInfo {
    VkStructureType   sType;
    const void*       pNext;
    VkRenderPass      renderPass;
    VkFramebuffer     framebuffer;
    VkRect2D          renderArea;
    uint32_t          clearValueCount;
    const VkClearValue* pClearValues;
};

struct VkCommandPoolCreateInfo {
    VkStructureType sType;
    const void*     pNext;
    VkFlags         flags;
    uint32_t        queueFamilyIndex;
};

struct VkCommandBufferAllocateInfo {
    VkStructureType sType;
    const void*     pNext;
    VkCommandPool   commandPool;
    uint32_t        level;
    uint32_t        commandBufferCount;
};

struct VkCommandBufferBeginInfo {
    VkStructureType sType;
    const void*     pNext;
    VkFlags         flags;
    const void*     pInheritanceInfo;
};

struct VkSemaphoreCreateInfo {
    VkStructureType sType;
    const void*     pNext;
    VkFlags         flags;
};

struct VkFenceCreateInfo {
    VkStructureType sType;
    const void*     pNext;
    VkFlags         flags;
};

struct VkSubmitInfo {
    VkStructureType        sType;
    const void*            pNext;
    uint32_t               waitSemaphoreCount;
    const VkSemaphore*     pWaitSemaphores;
    const VkFlags*         pWaitDstStageMask;
    uint32_t               commandBufferCount;
    const VkCommandBuffer* pCommandBuffers;
    uint32_t               signalSemaphoreCount;
    const VkSemaphore*     pSignalSemaphores;
};

struct VkBufferCopy {
    VkDeviceSize srcOffset;
    VkDeviceSize dstOffset;
    VkDeviceSize size;
};

struct VkImageCopy {
    VkImageSubresourceLayers srcSubresource;
    VkOffset3D               srcOffset;
    VkImageSubresourceLayers dstSubresource;
    VkOffset3D               dstOffset;
    VkExtent3D               extent;
};

struct VkDynamicDispatch {
#ifdef _WIN32
    HMODULE dll = nullptr;
#else
    void*   dll = nullptr;
#endif
    void* (VKAPI_CALL* vkGetInstanceProcAddr)(VkInstance, const char*) = nullptr;
    void* (VKAPI_CALL* vkGetDeviceProcAddr)(VkDevice, const char*) = nullptr;
    VkResult (VKAPI_CALL* vkCreateInstance)(const VkInstanceCreateInfo*, const void*, VkInstance*) = nullptr;
    void (VKAPI_CALL* vkDestroyInstance)(VkInstance, const void*) = nullptr;
    VkResult (VKAPI_CALL* vkEnumeratePhysicalDevices)(VkInstance, uint32_t*, VkPhysicalDevice*) = nullptr;
    void (VKAPI_CALL* vkGetPhysicalDeviceProperties)(VkPhysicalDevice, VkPhysicalDevicePropertiesHeader*) = nullptr;
    void (VKAPI_CALL* vkGetPhysicalDeviceFeatures)(VkPhysicalDevice, VkPhysicalDeviceFeatures*) = nullptr;
    void (VKAPI_CALL* vkGetPhysicalDeviceFormatProperties)(VkPhysicalDevice, VkFormat, VkFormatProperties*) = nullptr;
    VkResult (VKAPI_CALL* vkGetPhysicalDeviceImageFormatProperties)(VkPhysicalDevice, VkFormat, VkImageType, VkImageTiling, VkFlags, VkFlags, VkImageFormatProperties*) = nullptr;
    void (VKAPI_CALL* vkGetPhysicalDeviceQueueFamilyProperties)(VkPhysicalDevice, uint32_t*, VkQueueFamilyProperties*) = nullptr;
    void (VKAPI_CALL* vkGetPhysicalDeviceMemoryProperties)(VkPhysicalDevice, VkPhysicalDeviceMemoryProperties*) = nullptr;
    VkResult (VKAPI_CALL* vkCreateDevice)(VkPhysicalDevice, const VkDeviceCreateInfo*, const void*, VkDevice*) = nullptr;
    void (VKAPI_CALL* vkDestroyDevice)(VkDevice, const void*) = nullptr;

    // Instance KHR surface
    VkResult (VKAPI_CALL* vkCreateWin32SurfaceKHR)(VkInstance, const VkWin32SurfaceCreateInfoKHR*, const void*, VkSurfaceKHR*) = nullptr;
    void (VKAPI_CALL* vkDestroySurfaceKHR)(VkInstance, VkSurfaceKHR, const void*) = nullptr;
    VkResult (VKAPI_CALL* vkGetPhysicalDeviceSurfaceSupportKHR)(VkPhysicalDevice, uint32_t, VkSurfaceKHR, VkBool32*) = nullptr;
    VkResult (VKAPI_CALL* vkGetPhysicalDeviceSurfaceCapabilitiesKHR)(VkPhysicalDevice, VkSurfaceKHR, VkSurfaceCapabilitiesKHR*) = nullptr;
    VkResult (VKAPI_CALL* vkGetPhysicalDeviceSurfaceFormatsKHR)(VkPhysicalDevice, VkSurfaceKHR, uint32_t*, VkSurfaceFormatKHR*) = nullptr;
    VkResult (VKAPI_CALL* vkGetPhysicalDeviceSurfacePresentModesKHR)(VkPhysicalDevice, VkSurfaceKHR, uint32_t*, VkPresentModeKHR*) = nullptr;

    // Device procs
    void (VKAPI_CALL* vkGetDeviceQueue)(VkDevice, uint32_t, uint32_t, VkQueue*) = nullptr;
    VkResult (VKAPI_CALL* vkDeviceWaitIdle)(VkDevice) = nullptr;
    VkResult (VKAPI_CALL* vkCreateSwapchainKHR)(VkDevice, const VkSwapchainCreateInfoKHR*, const void*, VkSwapchainKHR*) = nullptr;
    void (VKAPI_CALL* vkDestroySwapchainKHR)(VkDevice, VkSwapchainKHR, const void*) = nullptr;
    VkResult (VKAPI_CALL* vkGetSwapchainImagesKHR)(VkDevice, VkSwapchainKHR, uint32_t*, VkImage*) = nullptr;
    VkResult (VKAPI_CALL* vkAcquireNextImageKHR)(VkDevice, VkSwapchainKHR, uint64_t, VkSemaphore, VkFence, uint32_t*) = nullptr;
    VkResult (VKAPI_CALL* vkQueuePresentKHR)(VkQueue, const VkPresentInfoKHR*) = nullptr;

    VkResult (VKAPI_CALL* vkAllocateMemory)(VkDevice, const VkMemoryAllocateInfo*, const void*, VkDeviceMemory*) = nullptr;
    void (VKAPI_CALL* vkFreeMemory)(VkDevice, VkDeviceMemory, const void*) = nullptr;
    VkResult (VKAPI_CALL* vkMapMemory)(VkDevice, VkDeviceMemory, VkDeviceSize, VkDeviceSize, VkFlags, void**) = nullptr;
    void (VKAPI_CALL* vkUnmapMemory)(VkDevice, VkDeviceMemory) = nullptr;

    VkResult (VKAPI_CALL* vkCreateBuffer)(VkDevice, const VkBufferCreateInfo*, const void*, VkBuffer*) = nullptr;
    void (VKAPI_CALL* vkDestroyBuffer)(VkDevice, VkBuffer, const void*) = nullptr;
    void (VKAPI_CALL* vkGetBufferMemoryRequirements)(VkDevice, VkBuffer, VkMemoryRequirements*) = nullptr;
    VkResult (VKAPI_CALL* vkBindBufferMemory)(VkDevice, VkBuffer, VkDeviceMemory, VkDeviceSize) = nullptr;

    VkResult (VKAPI_CALL* vkCreateImage)(VkDevice, const VkImageCreateInfo*, const void*, VkImage*) = nullptr;
    void (VKAPI_CALL* vkDestroyImage)(VkDevice, VkImage, const void*) = nullptr;
    void (VKAPI_CALL* vkGetImageMemoryRequirements)(VkDevice, VkImage, VkMemoryRequirements*) = nullptr;
    VkResult (VKAPI_CALL* vkBindImageMemory)(VkDevice, VkImage, VkDeviceMemory, VkDeviceSize) = nullptr;
    VkResult (VKAPI_CALL* vkCreateImageView)(VkDevice, const VkImageViewCreateInfo*, const void*, VkImageView*) = nullptr;
    void (VKAPI_CALL* vkDestroyImageView)(VkDevice, VkImageView, const void*) = nullptr;
    VkResult (VKAPI_CALL* vkCreateSampler)(VkDevice, const VkSamplerCreateInfo*, const void*, VkSampler*) = nullptr;
    void (VKAPI_CALL* vkDestroySampler)(VkDevice, VkSampler, const void*) = nullptr;

    VkResult (VKAPI_CALL* vkCreateShaderModule)(VkDevice, const VkShaderModuleCreateInfo*, const void*, VkShaderModule*) = nullptr;
    void (VKAPI_CALL* vkDestroyShaderModule)(VkDevice, VkShaderModule, const void*) = nullptr;
    VkResult (VKAPI_CALL* vkCreateDescriptorSetLayout)(VkDevice, const VkDescriptorSetLayoutCreateInfo*, const void*, VkDescriptorSetLayout*) = nullptr;
    void (VKAPI_CALL* vkDestroyDescriptorSetLayout)(VkDevice, VkDescriptorSetLayout, const void*) = nullptr;
    VkResult (VKAPI_CALL* vkCreateDescriptorPool)(VkDevice, const VkDescriptorPoolCreateInfo*, const void*, VkDescriptorPool*) = nullptr;
    void (VKAPI_CALL* vkDestroyDescriptorPool)(VkDevice, VkDescriptorPool, const void*) = nullptr;
    VkResult (VKAPI_CALL* vkResetDescriptorPool)(VkDevice, VkDescriptorPool, VkFlags) = nullptr;
    VkResult (VKAPI_CALL* vkAllocateDescriptorSets)(VkDevice, const VkDescriptorSetAllocateInfo*, VkDescriptorSet*) = nullptr;
    void (VKAPI_CALL* vkUpdateDescriptorSets)(VkDevice, uint32_t, const VkWriteDescriptorSet*, uint32_t, const void*) = nullptr;
    VkResult (VKAPI_CALL* vkCreatePipelineLayout)(VkDevice, const VkPipelineLayoutCreateInfo*, const void*, VkPipelineLayout*) = nullptr;
    void (VKAPI_CALL* vkDestroyPipelineLayout)(VkDevice, VkPipelineLayout, const void*) = nullptr;
    VkResult (VKAPI_CALL* vkCreateRenderPass)(VkDevice, const VkRenderPassCreateInfo*, const void*, VkRenderPass*) = nullptr;
    void (VKAPI_CALL* vkDestroyRenderPass)(VkDevice, VkRenderPass, const void*) = nullptr;
    VkResult (VKAPI_CALL* vkCreateFramebuffer)(VkDevice, const VkFramebufferCreateInfo*, const void*, VkFramebuffer*) = nullptr;
    void (VKAPI_CALL* vkDestroyFramebuffer)(VkDevice, VkFramebuffer, const void*) = nullptr;
    VkResult (VKAPI_CALL* vkCreateGraphicsPipelines)(VkDevice, VkPipelineCache, uint32_t, const VkGraphicsPipelineCreateInfo*, const void*, VkPipeline*) = nullptr;
    void (VKAPI_CALL* vkDestroyPipeline)(VkDevice, VkPipeline, const void*) = nullptr;

    VkResult (VKAPI_CALL* vkCreateCommandPool)(VkDevice, const VkCommandPoolCreateInfo*, const void*, VkCommandPool*) = nullptr;
    void (VKAPI_CALL* vkDestroyCommandPool)(VkDevice, VkCommandPool, const void*) = nullptr;
    VkResult (VKAPI_CALL* vkAllocateCommandBuffers)(VkDevice, const VkCommandBufferAllocateInfo*, VkCommandBuffer*) = nullptr;
    VkResult (VKAPI_CALL* vkResetCommandBuffer)(VkCommandBuffer, VkFlags) = nullptr;
    VkResult (VKAPI_CALL* vkBeginCommandBuffer)(VkCommandBuffer, const VkCommandBufferBeginInfo*) = nullptr;
    VkResult (VKAPI_CALL* vkEndCommandBuffer)(VkCommandBuffer) = nullptr;

    VkResult (VKAPI_CALL* vkCreateSemaphore)(VkDevice, const VkSemaphoreCreateInfo*, const void*, VkSemaphore*) = nullptr;
    void (VKAPI_CALL* vkDestroySemaphore)(VkDevice, VkSemaphore, const void*) = nullptr;
    VkResult (VKAPI_CALL* vkCreateFence)(VkDevice, const VkFenceCreateInfo*, const void*, VkFence*) = nullptr;
    void (VKAPI_CALL* vkDestroyFence)(VkDevice, VkFence, const void*) = nullptr;
    VkResult (VKAPI_CALL* vkWaitForFences)(VkDevice, uint32_t, const VkFence*, VkBool32, uint64_t) = nullptr;
    VkResult (VKAPI_CALL* vkResetFences)(VkDevice, uint32_t, const VkFence*) = nullptr;
    VkResult (VKAPI_CALL* vkQueueSubmit)(VkQueue, uint32_t, const VkSubmitInfo*, VkFence) = nullptr;
    VkResult (VKAPI_CALL* vkQueueWaitIdle)(VkQueue) = nullptr;

    void (VKAPI_CALL* vkCmdBeginRenderPass)(VkCommandBuffer, const VkRenderPassBeginInfo*, VkSubpassContents) = nullptr;
    void (VKAPI_CALL* vkCmdEndRenderPass)(VkCommandBuffer) = nullptr;
    void (VKAPI_CALL* vkCmdBindPipeline)(VkCommandBuffer, uint32_t, VkPipeline) = nullptr;
    void (VKAPI_CALL* vkCmdSetViewport)(VkCommandBuffer, uint32_t, uint32_t, const VkViewport*) = nullptr;
    void (VKAPI_CALL* vkCmdSetScissor)(VkCommandBuffer, uint32_t, uint32_t, const VkRect2D*) = nullptr;
    void (VKAPI_CALL* vkCmdBindDescriptorSets)(VkCommandBuffer, uint32_t, VkPipelineLayout, uint32_t, uint32_t, const VkDescriptorSet*, uint32_t, const uint32_t*) = nullptr;
    void (VKAPI_CALL* vkCmdBindVertexBuffers)(VkCommandBuffer, uint32_t, uint32_t, const VkBuffer*, const VkDeviceSize*) = nullptr;
    void (VKAPI_CALL* vkCmdBindIndexBuffer)(VkCommandBuffer, VkBuffer, VkDeviceSize, VkIndexType) = nullptr;
    void (VKAPI_CALL* vkCmdDraw)(VkCommandBuffer, uint32_t, uint32_t, uint32_t, uint32_t) = nullptr;
    void (VKAPI_CALL* vkCmdDrawIndexed)(VkCommandBuffer, uint32_t, uint32_t, uint32_t, int32_t, uint32_t) = nullptr;
    void (VKAPI_CALL* vkCmdPipelineBarrier)(VkCommandBuffer, VkFlags, VkFlags, VkFlags, uint32_t, const void*, uint32_t, const void*, uint32_t, const VkImageMemoryBarrier*) = nullptr;
    void (VKAPI_CALL* vkCmdCopyBuffer)(VkCommandBuffer, VkBuffer, VkBuffer, uint32_t, const VkBufferCopy*) = nullptr;
    void (VKAPI_CALL* vkCmdCopyBufferToImage)(VkCommandBuffer, VkBuffer, VkImage, VkImageLayout, uint32_t, const VkBufferImageCopy*) = nullptr;
    void (VKAPI_CALL* vkCmdCopyImageToBuffer)(VkCommandBuffer, VkImage, VkImageLayout, VkBuffer, uint32_t, const VkBufferImageCopy*) = nullptr;
    void (VKAPI_CALL* vkCmdCopyImage)(VkCommandBuffer, VkImage, VkImageLayout, VkImage, VkImageLayout, uint32_t, const VkImageCopy*) = nullptr;

    template <typename Fn>
    static bool load_proc(Fn& out, void* raw_ptr) noexcept {
        out = reinterpret_cast<Fn>(raw_ptr);
        return out != nullptr;
    }

    bool load_loader() noexcept {
#ifdef _WIN32
        if (!dll) {
            dll = LoadLibraryW(L"vulkan-1.dll");
        }
        if (!dll) return false;
        auto get_sym = [&](const char* name) -> void* {
            return reinterpret_cast<void*>(GetProcAddress(dll, name));
        };
        bool ok = true;
        ok &= load_proc(vkGetInstanceProcAddr, get_sym("vkGetInstanceProcAddr"));
        ok &= load_proc(vkGetDeviceProcAddr, get_sym("vkGetDeviceProcAddr"));
        ok &= load_proc(vkCreateInstance, get_sym("vkCreateInstance"));
        ok &= load_proc(vkDestroyInstance, get_sym("vkDestroyInstance"));
        ok &= load_proc(vkEnumeratePhysicalDevices, get_sym("vkEnumeratePhysicalDevices"));
        ok &= load_proc(vkGetPhysicalDeviceProperties, get_sym("vkGetPhysicalDeviceProperties"));
        ok &= load_proc(vkGetPhysicalDeviceFeatures, get_sym("vkGetPhysicalDeviceFeatures"));
        ok &= load_proc(vkGetPhysicalDeviceFormatProperties, get_sym("vkGetPhysicalDeviceFormatProperties"));
        ok &= load_proc(vkGetPhysicalDeviceImageFormatProperties, get_sym("vkGetPhysicalDeviceImageFormatProperties"));
        ok &= load_proc(vkGetPhysicalDeviceQueueFamilyProperties, get_sym("vkGetPhysicalDeviceQueueFamilyProperties"));
        ok &= load_proc(vkGetPhysicalDeviceMemoryProperties, get_sym("vkGetPhysicalDeviceMemoryProperties"));
        ok &= load_proc(vkCreateDevice, get_sym("vkCreateDevice"));
        ok &= load_proc(vkDestroyDevice, get_sym("vkDestroyDevice"));
        return ok;
#else
        return false;
#endif
    }

    bool load_instance_procs(VkInstance instance) noexcept {
        if (!vkGetInstanceProcAddr || !instance) return false;
        auto g = [&](const char* name) -> void* { return vkGetInstanceProcAddr(instance, name); };
        bool ok = true;
        ok &= load_proc(vkCreateWin32SurfaceKHR, g("vkCreateWin32SurfaceKHR"));
        ok &= load_proc(vkDestroySurfaceKHR, g("vkDestroySurfaceKHR"));
        ok &= load_proc(vkGetPhysicalDeviceSurfaceSupportKHR, g("vkGetPhysicalDeviceSurfaceSupportKHR"));
        ok &= load_proc(vkGetPhysicalDeviceSurfaceCapabilitiesKHR, g("vkGetPhysicalDeviceSurfaceCapabilitiesKHR"));
        ok &= load_proc(vkGetPhysicalDeviceSurfaceFormatsKHR, g("vkGetPhysicalDeviceSurfaceFormatsKHR"));
        ok &= load_proc(vkGetPhysicalDeviceSurfacePresentModesKHR, g("vkGetPhysicalDeviceSurfacePresentModesKHR"));
        return ok;
    }

    bool load_device_procs(VkDevice device) noexcept {
        if (!vkGetDeviceProcAddr || !device) return false;
        auto g = [&](const char* name) -> void* { return vkGetDeviceProcAddr(device, name); };
        bool ok = true;
        ok &= load_proc(vkGetDeviceQueue, g("vkGetDeviceQueue"));
        ok &= load_proc(vkDeviceWaitIdle, g("vkDeviceWaitIdle"));
        ok &= load_proc(vkCreateSwapchainKHR, g("vkCreateSwapchainKHR"));
        ok &= load_proc(vkDestroySwapchainKHR, g("vkDestroySwapchainKHR"));
        ok &= load_proc(vkGetSwapchainImagesKHR, g("vkGetSwapchainImagesKHR"));
        ok &= load_proc(vkAcquireNextImageKHR, g("vkAcquireNextImageKHR"));
        ok &= load_proc(vkQueuePresentKHR, g("vkQueuePresentKHR"));
        ok &= load_proc(vkAllocateMemory, g("vkAllocateMemory"));
        ok &= load_proc(vkFreeMemory, g("vkFreeMemory"));
        ok &= load_proc(vkMapMemory, g("vkMapMemory"));
        ok &= load_proc(vkUnmapMemory, g("vkUnmapMemory"));
        ok &= load_proc(vkCreateBuffer, g("vkCreateBuffer"));
        ok &= load_proc(vkDestroyBuffer, g("vkDestroyBuffer"));
        ok &= load_proc(vkGetBufferMemoryRequirements, g("vkGetBufferMemoryRequirements"));
        ok &= load_proc(vkBindBufferMemory, g("vkBindBufferMemory"));
        ok &= load_proc(vkCreateImage, g("vkCreateImage"));
        ok &= load_proc(vkDestroyImage, g("vkDestroyImage"));
        ok &= load_proc(vkGetImageMemoryRequirements, g("vkGetImageMemoryRequirements"));
        ok &= load_proc(vkBindImageMemory, g("vkBindImageMemory"));
        ok &= load_proc(vkCreateImageView, g("vkCreateImageView"));
        ok &= load_proc(vkDestroyImageView, g("vkDestroyImageView"));
        ok &= load_proc(vkCreateSampler, g("vkCreateSampler"));
        ok &= load_proc(vkDestroySampler, g("vkDestroySampler"));
        ok &= load_proc(vkCreateShaderModule, g("vkCreateShaderModule"));
        ok &= load_proc(vkDestroyShaderModule, g("vkDestroyShaderModule"));
        ok &= load_proc(vkCreateDescriptorSetLayout, g("vkCreateDescriptorSetLayout"));
        ok &= load_proc(vkDestroyDescriptorSetLayout, g("vkDestroyDescriptorSetLayout"));
        ok &= load_proc(vkCreateDescriptorPool, g("vkCreateDescriptorPool"));
        ok &= load_proc(vkDestroyDescriptorPool, g("vkDestroyDescriptorPool"));
        ok &= load_proc(vkResetDescriptorPool, g("vkResetDescriptorPool"));
        ok &= load_proc(vkAllocateDescriptorSets, g("vkAllocateDescriptorSets"));
        ok &= load_proc(vkUpdateDescriptorSets, g("vkUpdateDescriptorSets"));
        ok &= load_proc(vkCreatePipelineLayout, g("vkCreatePipelineLayout"));
        ok &= load_proc(vkDestroyPipelineLayout, g("vkDestroyPipelineLayout"));
        ok &= load_proc(vkCreateRenderPass, g("vkCreateRenderPass"));
        ok &= load_proc(vkDestroyRenderPass, g("vkDestroyRenderPass"));
        ok &= load_proc(vkCreateFramebuffer, g("vkCreateFramebuffer"));
        ok &= load_proc(vkDestroyFramebuffer, g("vkDestroyFramebuffer"));
        ok &= load_proc(vkCreateGraphicsPipelines, g("vkCreateGraphicsPipelines"));
        ok &= load_proc(vkDestroyPipeline, g("vkDestroyPipeline"));
        ok &= load_proc(vkCreateCommandPool, g("vkCreateCommandPool"));
        ok &= load_proc(vkDestroyCommandPool, g("vkDestroyCommandPool"));
        ok &= load_proc(vkAllocateCommandBuffers, g("vkAllocateCommandBuffers"));
        ok &= load_proc(vkResetCommandBuffer, g("vkResetCommandBuffer"));
        ok &= load_proc(vkBeginCommandBuffer, g("vkBeginCommandBuffer"));
        ok &= load_proc(vkEndCommandBuffer, g("vkEndCommandBuffer"));
        ok &= load_proc(vkCreateSemaphore, g("vkCreateSemaphore"));
        ok &= load_proc(vkDestroySemaphore, g("vkDestroySemaphore"));
        ok &= load_proc(vkCreateFence, g("vkCreateFence"));
        ok &= load_proc(vkDestroyFence, g("vkDestroyFence"));
        ok &= load_proc(vkWaitForFences, g("vkWaitForFences"));
        ok &= load_proc(vkResetFences, g("vkResetFences"));
        ok &= load_proc(vkQueueSubmit, g("vkQueueSubmit"));
        ok &= load_proc(vkQueueWaitIdle, g("vkQueueWaitIdle"));
        ok &= load_proc(vkCmdBeginRenderPass, g("vkCmdBeginRenderPass"));
        ok &= load_proc(vkCmdEndRenderPass, g("vkCmdEndRenderPass"));
        ok &= load_proc(vkCmdBindPipeline, g("vkCmdBindPipeline"));
        ok &= load_proc(vkCmdSetViewport, g("vkCmdSetViewport"));
        ok &= load_proc(vkCmdSetScissor, g("vkCmdSetScissor"));
        ok &= load_proc(vkCmdBindDescriptorSets, g("vkCmdBindDescriptorSets"));
        ok &= load_proc(vkCmdBindVertexBuffers, g("vkCmdBindVertexBuffers"));
        ok &= load_proc(vkCmdBindIndexBuffer, g("vkCmdBindIndexBuffer"));
        ok &= load_proc(vkCmdDraw, g("vkCmdDraw"));
        ok &= load_proc(vkCmdDrawIndexed, g("vkCmdDrawIndexed"));
        ok &= load_proc(vkCmdPipelineBarrier, g("vkCmdPipelineBarrier"));
        ok &= load_proc(vkCmdCopyBuffer, g("vkCmdCopyBuffer"));
        ok &= load_proc(vkCmdCopyBufferToImage, g("vkCmdCopyBufferToImage"));
        ok &= load_proc(vkCmdCopyImageToBuffer, g("vkCmdCopyImageToBuffer"));
        ok &= load_proc(vkCmdCopyImage, g("vkCmdCopyImage"));
        return ok;
    }

    void unload() noexcept {
#ifdef _WIN32
        if (dll) {
            FreeLibrary(dll);
            dll = nullptr;
        }
#endif
    }
};

} // namespace pn03::vk

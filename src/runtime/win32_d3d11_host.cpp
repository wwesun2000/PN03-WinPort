#include "pn03_d3d11_host.hpp"
#include "pn03_host_common.hpp"
#include "pn03_logger.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <vector>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <commdlg.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#endif

namespace pn03 {

static const char* kGxTevHlsl = R"HLSL(
// GameCube GX TEV Hardware Stage Emulation Shader (Direct3D 11 Shader Model 5.0)
cbuffer GXSceneConstants : register(b0) {
    row_major float4x4 uProjection;
    row_major float4x4 uModelView;
    float4   uTevColor0;
    float4   uKonstColor;
    float2   uViewportSize;
    uint     uEnableAlphaTest;
    float    uAlphaRef;
    uint     uTevMode;
    float    uTevScale;
    uint     uStage1Mode;
    float    uPad0;
};

struct VSInput {
    float3 position : POSITION;
    float3 normal   : NORMAL;
    float4 color0   : COLOR0;
    float2 uv0      : TEXCOORD0;
};

struct PSInput {
    float4 position : SV_POSITION;
    float4 color0   : COLOR0;
    float2 uv0      : TEXCOORD0;
};

Texture2D    uTex0    : register(t0);
SamplerState uSampler : register(s0);
Texture2D    uTex1    : register(t1);
SamplerState uSampler1 : register(s1);

PSInput VSMain(VSInput input) {
    PSInput o;
    float4 viewPos = mul(uModelView, float4(input.position, 1.0f));
    float4 clipPos = mul(uProjection, viewPos);
    clipPos.z = clipPos.z + clipPos.w;
    o.position = clipPos;
    o.color0 = input.color0;
    o.uv0 = input.uv0;
    return o;
}

float4 PSMain(PSInput input) : SV_TARGET {
    float4 outColor;
    if (uTevMode == 4u) {
        outColor = input.color0;
    } else if (uTevMode == 7u) {
        outColor = uTevColor0;
    } else {
        float4 texColor = uTex0.Sample(uSampler, input.uv0);
        if (uTevMode == 3u) {
            outColor = texColor;
        } else if (uTevMode == 1u) {
            outColor = float4(lerp(input.color0.rgb, texColor.rgb, texColor.a), input.color0.a);
        } else if (uTevMode == 2u) {
            outColor = float4(lerp(input.color0.rgb, float3(1.0f, 1.0f, 1.0f), texColor.rgb), input.color0.a * texColor.a);
        } else if (uTevMode == 5u) {
            outColor = texColor * uTevColor0;
        } else if (uTevMode == 6u) {
            outColor = float4(lerp(input.color0.rgb, uTevColor0.rgb, texColor.rgb), input.color0.a * texColor.a);
        } else {
            outColor = texColor * input.color0;
        }
    }
    if (uStage1Mode != 0u) {
        float4 tex1 = uTex1.Sample(uSampler1, input.uv0);
        if (uStage1Mode == 1u) {
            outColor.a *= tex1.a;
        } else if (uStage1Mode == 2u) {
            outColor *= tex1;
        } else {
            outColor.rgb *= tex1.rgb;
        }
    }
    outColor.rgb *= uTevScale;
    if (uEnableAlphaTest && outColor.a < uAlphaRef) {
        discard;
    }
    return outColor;
}
)HLSL";

static const char* kFxaaPostHlsl = R"HLSL(
// Fast Approximate Anti-Aliasing (FXAA 3.11 Console/PC Quality Pass) for P.N.03 HD Port
Texture2D    uSceneTex : register(t0);
SamplerState uLinear   : register(s0);

cbuffer FxaaConstants : register(b0) {
    float2 uInvScreenSize;
    float  uSubpixQuality;
    float  uEdgeThreshold;
    float  uBrightness;
    float  uGamma;
    float2 uPad;
};

struct FxaaVSOut {
    float4 pos : SV_POSITION;
    float2 uv  : TEXCOORD0;
};

FxaaVSOut VSFullscreenQuad(uint vid : SV_VertexID) {
    FxaaVSOut o;
    float2 uv = float2((vid << 1) & 2, vid & 2);
    o.pos = float4(uv.x * 2.0f - 1.0f, 1.0f - uv.y * 2.0f, 0.0f, 1.0f);
    o.uv  = uv;
    return o;
}

float3 ApplyDisplayGrade(float3 rgb) {
    float3 graded = saturate(rgb);
    if (abs(uGamma - 1.0f) > 0.001f) {
        graded = pow(max(graded, float3(0.0f, 0.0f, 0.0f)), 1.0f / max(uGamma, 0.25f));
    }
    return saturate(graded * uBrightness);
}

float4 PSBlitMain(float4 pos : SV_POSITION, float2 uv : TEXCOORD0) : SV_TARGET {
    return float4(ApplyDisplayGrade(uSceneTex.Sample(uLinear, uv).rgb), 1.0);
}

float4 PSFxaaMain(float4 pos : SV_POSITION, float2 uv : TEXCOORD0) : SV_TARGET {
    float3 rgbM  = uSceneTex.Sample(uLinear, uv).rgb;
    float3 rgbNW = uSceneTex.Sample(uLinear, uv + float2(-1.0, -1.0) * uInvScreenSize).rgb;
    float3 rgbNE = uSceneTex.Sample(uLinear, uv + float2( 1.0, -1.0) * uInvScreenSize).rgb;
    float3 rgbSW = uSceneTex.Sample(uLinear, uv + float2(-1.0,  1.0) * uInvScreenSize).rgb;
    float3 rgbSE = uSceneTex.Sample(uLinear, uv + float2( 1.0,  1.0) * uInvScreenSize).rgb;
    float3 lumaWeights = float3(0.299, 0.587, 0.114);
    float lumaM  = dot(rgbM,  lumaWeights);
    float lumaNW = dot(rgbNW, lumaWeights);
    float lumaNE = dot(rgbNE, lumaWeights);
    float lumaSW = dot(rgbSW, lumaWeights);
    float lumaSE = dot(rgbSE, lumaWeights);
    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));
    if ((lumaMax - lumaMin) < max(0.0312, lumaMax * uEdgeThreshold)) {
        return float4(ApplyDisplayGrade(rgbM), 1.0);
    }
    float2 dir = float2(-((lumaNW + lumaNE) - (lumaSW + lumaSE)),
                         ((lumaNW + lumaSW) - (lumaNE + lumaSE)));
    float dirReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) * (0.25 * (1.0 / 8.0)), 1.0 / 128.0);
    float rcpDirMin = 1.0 / (min(abs(dir.x), abs(dir.y)) + dirReduce);
    dir = clamp(dir * rcpDirMin, float2(-8.0, -8.0), float2(8.0, 8.0)) * uInvScreenSize;
    float3 rgbA = 0.5 * (uSceneTex.Sample(uLinear, uv + dir * (1.0/3.0 - 0.5)).rgb +
                         uSceneTex.Sample(uLinear, uv + dir * (2.0/3.0 - 0.5)).rgb);
    float3 rgbB = rgbA * 0.5 + 0.25 * (uSceneTex.Sample(uLinear, uv + dir * -0.5).rgb +
                                       uSceneTex.Sample(uLinear, uv + dir *  0.5).rgb);
    float lumaB = dot(rgbB, lumaWeights);
    float3 outRgb = ((lumaB < lumaMin) || (lumaB > lumaMax)) ? rgbA : rgbB;
    outRgb = lerp(rgbM, outRgb, saturate(uSubpixQuality));
    return float4(ApplyDisplayGrade(outRgb), 1.0);
}
)HLSL";

const char* Win32D3D11Host::gx_tev_hlsl_source() {
    return kGxTevHlsl;
}

const char* Win32D3D11Host::fxaa_post_hlsl_source() {
    return kFxaaPostHlsl;
}

Win32D3D11Host::~Win32D3D11Host() {
#ifdef _WIN32
    for (auto& kv : tex_srv_cache_) {
        if (kv.second) static_cast<ID3D11ShaderResourceView*>(kv.second)->Release();
    }
    for (auto& kv : text_srv_cache_) {
        if (kv.second) static_cast<ID3D11ShaderResourceView*>(kv.second)->Release();
    }
    if (rs_fullscreen_)        static_cast<ID3D11RasterizerState*>(rs_fullscreen_)->Release();
    if (rs_cull_back_)         static_cast<ID3D11RasterizerState*>(rs_cull_back_)->Release();
    if (rs_cull_front_)        static_cast<ID3D11RasterizerState*>(rs_cull_front_)->Release();
    if (rs_cull_none_)         static_cast<ID3D11RasterizerState*>(rs_cull_none_)->Release();
    if (dss_depth_none_)       static_cast<ID3D11DepthStencilState*>(dss_depth_none_)->Release();
    if (dss_depth_ro_)         static_cast<ID3D11DepthStencilState*>(dss_depth_ro_)->Release();
    if (dss_depth_rw_)         static_cast<ID3D11DepthStencilState*>(dss_depth_rw_)->Release();
    if (blend_additive_)       static_cast<ID3D11BlendState*>(blend_additive_)->Release();
    if (blend_alpha_)          static_cast<ID3D11BlendState*>(blend_alpha_)->Release();
    if (blend_opaque_)         static_cast<ID3D11BlendState*>(blend_opaque_)->Release();
    if (sampler_linear_clamp_) static_cast<ID3D11SamplerState*>(sampler_linear_clamp_)->Release();
    for (void*& s : samplers_) {
        if (s) {
            if (s == sampler_aniso_) sampler_aniso_ = nullptr;
            static_cast<ID3D11SamplerState*>(s)->Release();
            s = nullptr;
        }
    }
    if (sampler_aniso_)        static_cast<ID3D11SamplerState*>(sampler_aniso_)->Release();
    if (default_white_srv_)    static_cast<ID3D11ShaderResourceView*>(default_white_srv_)->Release();
    if (fxaa_cb_)              static_cast<ID3D11Buffer*>(fxaa_cb_)->Release();
    if (blit_ps_)              static_cast<ID3D11PixelShader*>(blit_ps_)->Release();
    if (fxaa_ps_)              static_cast<ID3D11PixelShader*>(fxaa_ps_)->Release();
    if (fxaa_vs_)              static_cast<ID3D11VertexShader*>(fxaa_vs_)->Release();
    if (scene_cb_)             static_cast<ID3D11Buffer*>(scene_cb_)->Release();
    if (dynamic_ib_)           static_cast<ID3D11Buffer*>(dynamic_ib_)->Release();
    if (dynamic_vb_)           static_cast<ID3D11Buffer*>(dynamic_vb_)->Release();
    if (input_layout_)         static_cast<ID3D11InputLayout*>(input_layout_)->Release();
    if (ps_)                   static_cast<ID3D11PixelShader*>(ps_)->Release();
    if (vs_)                   static_cast<ID3D11VertexShader*>(vs_)->Release();
    if (efb_resolved_srv_)     static_cast<ID3D11ShaderResourceView*>(efb_resolved_srv_)->Release();
    if (efb_resolved_tex_)     static_cast<ID3D11Texture2D*>(efb_resolved_tex_)->Release();
    if (msaa_dsv_)             static_cast<ID3D11DepthStencilView*>(msaa_dsv_)->Release();
    if (msaa_rtv_)             static_cast<ID3D11RenderTargetView*>(msaa_rtv_)->Release();
    if (efb_depth_tex_)        static_cast<ID3D11Texture2D*>(efb_depth_tex_)->Release();
    if (efb_color_tex_)        static_cast<ID3D11Texture2D*>(efb_color_tex_)->Release();
    if (swapchain_rtv_)        static_cast<ID3D11RenderTargetView*>(swapchain_rtv_)->Release();
    if (swap_chain_)           static_cast<IDXGISwapChain*>(swap_chain_)->Release();
    if (d3d_context_)       static_cast<ID3D11DeviceContext*>(d3d_context_)->Release();
    if (d3d_device_)        static_cast<ID3D11Device*>(d3d_device_)->Release();
#endif
}

bool Win32D3D11Host::show_prelaunch_settings_window() {
#ifdef _WIN32
    return show_iso_picker_if_empty(cfg_);
#else
    return true;
#endif
}

#ifdef _WIN32
static LRESULT CALLBACK PN03D3D11WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    auto* host = reinterpret_cast<Win32D3D11Host*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
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

void Win32D3D11Host::enable_process_dpi_awareness() {
    enable_host_dpi_awareness();
}

void Win32D3D11Host::handle_window_resize(uint32_t width, uint32_t height) {
#ifdef _WIN32
    if (!swap_chain_ || !d3d_device_ || !d3d_context_ || width == 0u || height == 0u) return;
    if (width == swapchain_width_ && height == swapchain_height_) return;
    auto* dev = static_cast<ID3D11Device*>(d3d_device_);
    auto* ctx = static_cast<ID3D11DeviceContext*>(d3d_context_);
    auto* sc  = static_cast<IDXGISwapChain*>(swap_chain_);

    ID3D11RenderTargetView* null_rtv = nullptr;
    ctx->OMSetRenderTargets(1, &null_rtv, nullptr);
    if (swapchain_rtv_) {
        static_cast<ID3D11RenderTargetView*>(swapchain_rtv_)->Release();
        swapchain_rtv_ = nullptr;
    }
    if (SUCCEEDED(sc->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0))) {
        ID3D11Texture2D* back_buf = nullptr;
        if (SUCCEEDED(sc->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&back_buf))) && back_buf) {
            ID3D11RenderTargetView* rtv = nullptr;
            if (SUCCEEDED(dev->CreateRenderTargetView(back_buf, nullptr, &rtv)) && rtv) {
                swapchain_rtv_ = rtv;
            }
            D3D11_TEXTURE2D_DESC bd{};
            back_buf->GetDesc(&bd);
            swapchain_width_  = bd.Width;
            swapchain_height_ = bd.Height;
            back_buf->Release();
        }
    }
#else
    (void)width;
    (void)height;
#endif
}

bool Win32D3D11Host::create_render_window_and_d3d11(std::string& err_msg, bool hidden_window) {
    (void)err_msg;
#ifdef _WIN32
    close_requested_ = false;
    uint32_t sc_w = cfg_.render_width;
    uint32_t sc_h = cfg_.render_height;
    HWND hwnd = create_pn03_win32_window(
        cfg_, hidden_window, L"PN03_WinPort_WndClass", PN03D3D11WndProc, this, sc_w, sc_h);
    if (!hwnd) {
        err_msg = "Failed to create Win32 window.";
        return false;
    }
    hwnd_ = hwnd;

    DXGI_SWAP_CHAIN_DESC sd{};
    sd.BufferCount                        = 2;
    sd.BufferDesc.Width                   = (std::max)(1u, sc_w);
    sd.BufferDesc.Height                  = (std::max)(1u, sc_h);
    sd.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator   = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow                       = hwnd;
    sd.SampleDesc.Count                   = 1;
    sd.SampleDesc.Quality                 = 0;
    sd.Windowed                           = (cfg_.window_mode != WindowMode::ExclusiveFullscreen);

    D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_11_0;
    ID3D11Device* dev = nullptr;
    ID3D11DeviceContext* ctx = nullptr;
    IDXGISwapChain* sc = nullptr;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        &feature_level, 1, D3D11_SDK_VERSION,
        &sd, &sc, &dev, nullptr, &ctx
    );
    if (FAILED(hr)) {
        hr = D3D11CreateDeviceAndSwapChain(
            nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0,
            &feature_level, 1, D3D11_SDK_VERSION,
            &sd, &sc, &dev, nullptr, &ctx
        );
    }
    if (FAILED(hr)) {
        err_msg = "D3D11CreateDeviceAndSwapChain failed.";
        return false;
    }
    d3d_device_  = dev;
    d3d_context_ = ctx;
    swap_chain_  = sc;

    ID3D11Texture2D* back_buf = nullptr;
    if (SUCCEEDED(sc->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&back_buf)))) {
        ID3D11RenderTargetView* rtv = nullptr;
        dev->CreateRenderTargetView(back_buf, nullptr, &rtv);
        D3D11_TEXTURE2D_DESC bd{};
        back_buf->GetDesc(&bd);
        swapchain_width_  = (std::max)(1u, static_cast<uint32_t>(bd.Width));
        swapchain_height_ = (std::max)(1u, static_cast<uint32_t>(bd.Height));
        back_buf->Release();
        swapchain_rtv_ = rtv;
    }

    if (!create_offscreen_efb_and_fxaa(err_msg)) {
        return false;
    }

    // Compile kGxTevHlsl Vertex & Pixel Shaders
    ID3DBlob* vs_blob = nullptr;
    ID3DBlob* ps_blob = nullptr;
    ID3DBlob* err_blob = nullptr;
    if (SUCCEEDED(D3DCompile(kGxTevHlsl, std::strlen(kGxTevHlsl), "GXTev.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", 0, 0, &vs_blob, &err_blob))) {
        ID3D11VertexShader* vs = nullptr;
        dev->CreateVertexShader(vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), nullptr, &vs);
        vs_ = vs;

        D3D11_INPUT_ELEMENT_DESC ied[] = {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0},
        };
        ID3D11InputLayout* il = nullptr;
        dev->CreateInputLayout(ied, 4, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &il);
        input_layout_ = il;
        vs_blob->Release();
    }
    if (err_blob) { err_blob->Release(); err_blob = nullptr; }

    if (SUCCEEDED(D3DCompile(kGxTevHlsl, std::strlen(kGxTevHlsl), "GXTev.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", 0, 0, &ps_blob, &err_blob))) {
        ID3D11PixelShader* ps = nullptr;
        dev->CreatePixelShader(ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), nullptr, &ps);
        ps_ = ps;
        ps_blob->Release();
    }
    if (err_blob) { err_blob->Release(); err_blob = nullptr; }

    // Create Dynamic Vertex Buffer, Dynamic Index Buffer, and Scene Constant Buffer
    D3D11_BUFFER_DESC vbd{};
    vbd.ByteWidth      = static_cast<UINT>(kHostMaxDynamicVertices * sizeof(GXVertex));
    vbd.Usage          = D3D11_USAGE_DYNAMIC;
    vbd.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    ID3D11Buffer* vb = nullptr;
    dev->CreateBuffer(&vbd, nullptr, &vb);
    dynamic_vb_ = vb;

    D3D11_BUFFER_DESC ibd{};
    ibd.ByteWidth      = static_cast<UINT>(kHostMaxDynamicIndices * sizeof(uint32_t));
    ibd.Usage          = D3D11_USAGE_DYNAMIC;
    ibd.BindFlags      = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    ID3D11Buffer* ib = nullptr;
    dev->CreateBuffer(&ibd, nullptr, &ib);
    dynamic_ib_ = ib;

    D3D11_BUFFER_DESC cbd{};
    cbd.ByteWidth      = static_cast<UINT>((sizeof(GXSceneConstantsCPU) + 15u) & ~15u);
    cbd.Usage          = D3D11_USAGE_DEFAULT;
    cbd.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
    ID3D11Buffer* cb = nullptr;
    dev->CreateBuffer(&cbd, nullptr, &cb);
    scene_cb_ = cb;

    // Create 1x1 Default White Texture SRV (used when a GX draw batch has no bound texture)
    uint32_t white_px = 0xFFFFFFFFu;
    D3D11_TEXTURE2D_DESC wtd{};
    wtd.Width            = 1;
    wtd.Height           = 1;
    wtd.MipLevels        = 1;
    wtd.ArraySize        = 1;
    wtd.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
    wtd.SampleDesc.Count = 1;
    wtd.Usage            = D3D11_USAGE_IMMUTABLE;
    wtd.BindFlags        = D3D11_BIND_SHADER_RESOURCE;
    D3D11_SUBRESOURCE_DATA wsd{};
    wsd.pSysMem          = &white_px;
    wsd.SysMemPitch      = 4;
    ID3D11Texture2D* wtex = nullptr;
    if (SUCCEEDED(dev->CreateTexture2D(&wtd, &wsd, &wtex))) {
        ID3D11ShaderResourceView* wsrv = nullptr;
        dev->CreateShaderResourceView(wtex, nullptr, &wsrv);
        wtex->Release();
        default_white_srv_ = wsrv;
    }

    // Create Anisotropic Sampler State
    static constexpr D3D11_TEXTURE_ADDRESS_MODE kAddrModes[3] = {
        D3D11_TEXTURE_ADDRESS_CLAMP,
        D3D11_TEXTURE_ADDRESS_WRAP,
        D3D11_TEXTURE_ADDRESS_MIRROR
    };
    for (uint32_t ws = 0; ws < 3u; ++ws) {
        for (uint32_t wt = 0; wt < 3u; ++wt) {
            D3D11_SAMPLER_DESC samp{};
            samp.Filter         = (cfg_.anisotropic_filtering > 1) ? D3D11_FILTER_ANISOTROPIC : D3D11_FILTER_MIN_MAG_MIP_LINEAR;
            samp.AddressU       = kAddrModes[ws];
            samp.AddressV       = kAddrModes[wt];
            samp.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
            samp.MaxAnisotropy  = std::clamp(cfg_.anisotropic_filtering, 1u, 16u);
            samp.ComparisonFunc = D3D11_COMPARISON_NEVER;
            samp.MaxLOD         = D3D11_FLOAT32_MAX;
            ID3D11SamplerState* ss = nullptr;
            dev->CreateSamplerState(&samp, &ss);
            samplers_[ws * 3u + wt] = ss;
        }
    }
    sampler_aniso_ = samplers_[1u * 3u + 1u];

    // Create Opaque, Alpha, and Additive Blend States
    D3D11_BLEND_DESC bd{};
    bd.RenderTarget[0].BlendEnable           = FALSE;
    bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    ID3D11BlendState* bs_opaque = nullptr;
    dev->CreateBlendState(&bd, &bs_opaque);
    blend_opaque_ = bs_opaque;

    bd.RenderTarget[0].BlendEnable           = TRUE;
    bd.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
    bd.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
    bd.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
    bd.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_INV_SRC_ALPHA;
    bd.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
    ID3D11BlendState* bs_alpha = nullptr;
    dev->CreateBlendState(&bd, &bs_alpha);
    blend_alpha_ = bs_alpha;

    bd.RenderTarget[0].DestBlend             = D3D11_BLEND_ONE;
    ID3D11BlendState* bs_add = nullptr;
    dev->CreateBlendState(&bd, &bs_add);
    blend_additive_ = bs_add;

    // Create Depth-Stencil States (RW, RO, Disabled for 2D UI)
    D3D11_DEPTH_STENCIL_DESC dssd{};
    dssd.DepthEnable    = TRUE;
    dssd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dssd.DepthFunc      = D3D11_COMPARISON_LESS_EQUAL;
    ID3D11DepthStencilState* dss_rw = nullptr;
    dev->CreateDepthStencilState(&dssd, &dss_rw);
    dss_depth_rw_ = dss_rw;

    dssd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    ID3D11DepthStencilState* dss_ro = nullptr;
    dev->CreateDepthStencilState(&dssd, &dss_ro);
    dss_depth_ro_ = dss_ro;

    dssd.DepthEnable    = FALSE;
    ID3D11DepthStencilState* dss_none = nullptr;
    dev->CreateDepthStencilState(&dssd, &dss_none);
    dss_depth_none_ = dss_none;

    // Create Rasterizer States (ScissorEnable=TRUE for GX batches, ScissorEnable=FALSE for fullscreen resolve/overlays)
    D3D11_RASTERIZER_DESC rsd{};
    rsd.FillMode              = D3D11_FILL_SOLID;
    rsd.CullMode              = D3D11_CULL_NONE;
    rsd.FrontCounterClockwise = FALSE;
    rsd.DepthClipEnable       = TRUE;
    rsd.ScissorEnable         = TRUE;
    rsd.MultisampleEnable     = TRUE;
    ID3D11RasterizerState* rs = nullptr;
    dev->CreateRasterizerState(&rsd, &rs);
    rs_cull_none_ = rs;

    rsd.CullMode = D3D11_CULL_FRONT;
    rs = nullptr;
    dev->CreateRasterizerState(&rsd, &rs);
    rs_cull_front_ = rs;

    rsd.CullMode = D3D11_CULL_BACK;
    rs = nullptr;
    dev->CreateRasterizerState(&rsd, &rs);
    rs_cull_back_ = rs;

    rsd.CullMode          = D3D11_CULL_NONE;
    rsd.ScissorEnable     = FALSE;
    rsd.MultisampleEnable = FALSE;
    rs = nullptr;
    dev->CreateRasterizerState(&rsd, &rs);
    rs_fullscreen_ = rs;
#endif
    initialized_ = true;
    return true;
}

#ifdef _WIN32
static D3D11_VIEWPORT compute_output_viewport(AspectRatioMode mode, uint32_t target_w, uint32_t target_h) {
    const HostViewportRect r = compute_output_viewport_rect(mode, target_w, target_h);
    D3D11_VIEWPORT vp{};
    vp.TopLeftX = r.x;
    vp.TopLeftY = r.y;
    vp.Width    = r.width;
    vp.Height   = r.height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    return vp;
}

bool Win32D3D11Host::create_offscreen_efb_and_fxaa(std::string& err_msg) {
    auto* dev = static_cast<ID3D11Device*>(d3d_device_);
    if (!dev) return false;

    const uint32_t scale = (std::max)(1u, (std::min)(6u, cfg_.internal_scale_factor));
    compute_efb_dimensions(cfg_, swapchain_height_, efb_width_, efb_height_);

    UINT requested_msaa = (cfg_.msaa_mode == AntiAliasingMode::FXAA || cfg_.msaa_mode == AntiAliasingMode::Off)
                              ? 1u
                              : static_cast<UINT>(cfg_.msaa_mode);
    if (requested_msaa == 0u) requested_msaa = 1u;
    UINT chosen_msaa = 1u;
    for (UINT s = requested_msaa; s >= 2u; s >>= 1u) {
        UINT q_col = 0, q_dsv = 0;
        if (SUCCEEDED(dev->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, s, &q_col)) && q_col > 0 &&
            SUCCEEDED(dev->CheckMultisampleQualityLevels(DXGI_FORMAT_D24_UNORM_S8_UINT, s, &q_dsv)) && q_dsv > 0) {
            chosen_msaa = s;
            break;
        }
    }
    efb_msaa_samples_ = chosen_msaa;

    D3D11_TEXTURE2D_DESC ctd{};
    ctd.Width              = efb_width_;
    ctd.Height             = efb_height_;
    ctd.MipLevels          = 1;
    ctd.ArraySize          = 1;
    ctd.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
    ctd.SampleDesc.Count   = chosen_msaa;
    ctd.SampleDesc.Quality = 0;
    ctd.Usage              = D3D11_USAGE_DEFAULT;
    ctd.BindFlags          = D3D11_BIND_RENDER_TARGET | ((chosen_msaa == 1u) ? D3D11_BIND_SHADER_RESOURCE : 0u);

    ID3D11Texture2D* color_tex = nullptr;
    if (FAILED(dev->CreateTexture2D(&ctd, nullptr, &color_tex)) || !color_tex) {
        if (chosen_msaa > 1u) {
            chosen_msaa = 1u;
            efb_msaa_samples_ = 1u;
            ctd.SampleDesc.Count = 1u;
            ctd.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
            dev->CreateTexture2D(&ctd, nullptr, &color_tex);
        }
    }
    if (!color_tex) {
        err_msg = "Failed to create offscreen EFB color target.";
        return false;
    }
    efb_color_tex_ = color_tex;
    ID3D11RenderTargetView* efb_rtv = nullptr;
    if (FAILED(dev->CreateRenderTargetView(color_tex, nullptr, &efb_rtv))) {
        err_msg = "Failed to create EFB RenderTargetView.";
        return false;
    }
    msaa_rtv_ = efb_rtv;

    D3D11_TEXTURE2D_DESC dsd{};
    dsd.Width              = efb_width_;
    dsd.Height             = efb_height_;
    dsd.MipLevels          = 1;
    dsd.ArraySize          = 1;
    dsd.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsd.SampleDesc.Count   = chosen_msaa;
    dsd.SampleDesc.Quality = 0;
    dsd.Usage              = D3D11_USAGE_DEFAULT;
    dsd.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
    ID3D11Texture2D* depth_tex = nullptr;
    if (SUCCEEDED(dev->CreateTexture2D(&dsd, nullptr, &depth_tex)) && depth_tex) {
        efb_depth_tex_ = depth_tex;
        ID3D11DepthStencilView* dsv = nullptr;
        dev->CreateDepthStencilView(depth_tex, nullptr, &dsv);
        msaa_dsv_ = dsv;
    }

    ID3D11Texture2D* srv_source_tex = color_tex;
    if (chosen_msaa > 1u) {
        D3D11_TEXTURE2D_DESC rtd = ctd;
        rtd.SampleDesc.Count   = 1u;
        rtd.SampleDesc.Quality = 0u;
        rtd.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
        ID3D11Texture2D* res_tex = nullptr;
        if (SUCCEEDED(dev->CreateTexture2D(&rtd, nullptr, &res_tex)) && res_tex) {
            efb_resolved_tex_ = res_tex;
            srv_source_tex    = res_tex;
        }
    }
    ID3D11ShaderResourceView* res_srv = nullptr;
    dev->CreateShaderResourceView(srv_source_tex, nullptr, &res_srv);
    efb_resolved_srv_ = res_srv;

    ID3DBlob* vs_blob = nullptr;
    ID3DBlob* ps_blob = nullptr;
    ID3DBlob* blit_blob = nullptr;
    ID3DBlob* err_blob = nullptr;
    if (SUCCEEDED(D3DCompile(kFxaaPostHlsl, std::strlen(kFxaaPostHlsl), "FXAAPost.hlsl", nullptr, nullptr, "VSFullscreenQuad", "vs_5_0", 0, 0, &vs_blob, &err_blob))) {
        ID3D11VertexShader* fvs = nullptr;
        dev->CreateVertexShader(vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), nullptr, &fvs);
        fxaa_vs_ = fvs;
        vs_blob->Release();
    }
    if (err_blob) { err_blob->Release(); err_blob = nullptr; }

    if (SUCCEEDED(D3DCompile(kFxaaPostHlsl, std::strlen(kFxaaPostHlsl), "FXAAPost.hlsl", nullptr, nullptr, "PSFxaaMain", "ps_5_0", 0, 0, &ps_blob, &err_blob))) {
        ID3D11PixelShader* fps = nullptr;
        dev->CreatePixelShader(ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), nullptr, &fps);
        fxaa_ps_ = fps;
        ps_blob->Release();
    }
    if (err_blob) { err_blob->Release(); err_blob = nullptr; }

    if (SUCCEEDED(D3DCompile(kFxaaPostHlsl, std::strlen(kFxaaPostHlsl), "FXAAPost.hlsl", nullptr, nullptr, "PSBlitMain", "ps_5_0", 0, 0, &blit_blob, &err_blob))) {
        ID3D11PixelShader* bps = nullptr;
        dev->CreatePixelShader(blit_blob->GetBufferPointer(), blit_blob->GetBufferSize(), nullptr, &bps);
        blit_ps_ = bps;
        blit_blob->Release();
    }
    if (err_blob) { err_blob->Release(); err_blob = nullptr; }

    D3D11_BUFFER_DESC fcbd{};
    fcbd.ByteWidth = sizeof(FxaaConstantsCPU);
    fcbd.Usage     = D3D11_USAGE_DEFAULT;
    fcbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    ID3D11Buffer* fcb = nullptr;
    dev->CreateBuffer(&fcbd, nullptr, &fcb);
    fxaa_cb_ = fcb;

    D3D11_SAMPLER_DESC lsd{};
    lsd.Filter         = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    lsd.AddressU       = D3D11_TEXTURE_ADDRESS_CLAMP;
    lsd.AddressV       = D3D11_TEXTURE_ADDRESS_CLAMP;
    lsd.AddressW       = D3D11_TEXTURE_ADDRESS_CLAMP;
    lsd.ComparisonFunc = D3D11_COMPARISON_NEVER;
    lsd.MaxLOD         = D3D11_FLOAT32_MAX;
    ID3D11SamplerState* lss = nullptr;
    dev->CreateSamplerState(&lsd, &lss);
    sampler_linear_clamp_ = lss;

    PN03_LOGF(LogLevel::Info, "D3D11", "Offscreen EFB=%ux%u (%ux internal, MSAA=%ux, FXAA=%s) -> Swapchain=%ux%u",
              efb_width_, efb_height_, scale, efb_msaa_samples_,
              (cfg_.enable_fxaa || cfg_.msaa_mode == AntiAliasingMode::FXAA) ? "ON" : "OFF",
              swapchain_width_, swapchain_height_);
    return true;
}
#endif

bool Win32D3D11Host::pump_messages() {
#ifdef _WIN32
    std::string stop_reason;
    if (!pump_win32_window_messages(static_cast<HWND>(hwnd_), close_requested_, &stop_reason)) {
        if (!stop_reason.empty()) {
            PN03_LOG(LogLevel::Info, "D3D11", stop_reason);
        }
        return false;
    }
#endif
    return true;
}

void Win32D3D11Host::begin_d3d11_frame(float clear_r, float clear_g, float clear_b) {
    (void)clear_r; (void)clear_g; (void)clear_b;
    batches_rendered_this_frame_ = false;
#ifdef _WIN32
    if (d3d_context_) {
        auto* ctx = static_cast<ID3D11DeviceContext*>(d3d_context_);
        ID3D11ShaderResourceView* null_srv = nullptr;
        ctx->PSSetShaderResources(0, 1, &null_srv);

        if (swapchain_rtv_) {
            const float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};
            ctx->ClearRenderTargetView(static_cast<ID3D11RenderTargetView*>(swapchain_rtv_), black);
        }
        if (msaa_rtv_) {
            auto* rtv = static_cast<ID3D11RenderTargetView*>(msaa_rtv_);
            auto* dsv = static_cast<ID3D11DepthStencilView*>(msaa_dsv_);
            const auto& gc_clr = global_gx_3d_interface().clear_rgba();
            const float color[4] = {
                gc_clr[0] ? (gc_clr[0] / 255.0f) : clear_r,
                gc_clr[1] ? (gc_clr[1] / 255.0f) : clear_g,
                gc_clr[2] ? (gc_clr[2] / 255.0f) : clear_b,
                1.0f
            };
            ctx->OMSetRenderTargets(1, &rtv, dsv);
            ctx->ClearRenderTargetView(rtv, color);
            if (dsv) {
                ctx->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
            }
        }
    }
#endif
}

#ifdef _WIN32
void* Win32D3D11Host::get_or_create_texture_srv(
    const Memory& mem,
    const GX3DInterface& gx,
    const GXBoundTexture& tex,
    const GXTlutSlot& tlut
) {
    if (!d3d_device_ || tex.width == 0 || tex.height == 0 || tex.data_vaddr < kGcRamBase) {
        return default_white_srv_;
    }
    uint64_t key = (static_cast<uint64_t>(tex.data_vaddr) << 32) ^
                   (static_cast<uint64_t>(tlut.data_vaddr & 0xFFFFFu) << 12) ^
                   (static_cast<uint64_t>(tex.width) << 16) ^
                   static_cast<uint64_t>(tex.height) ^
                   (static_cast<uint64_t>(tex.format & 0xFu) << 28);
    auto it = tex_srv_cache_.find(key);
    if (it != tex_srv_cache_.end()) {
        tex_srv_lru_[key] = ++cache_lru_tick_;
        return it->second;
    }

    std::vector<uint8_t> rgba = gx.decode_gc_texture_to_rgba8(mem, tex, &tlut);
    if (rgba.size() != static_cast<size_t>(tex.width) * tex.height * 4u) {
        return default_white_srv_;
    }

    constexpr size_t kMaxD3D11CachedTextures = 1024u;
    if (tex_srv_cache_.size() >= kMaxD3D11CachedTextures) {
        auto oldest_it = tex_srv_cache_.begin();
        uint64_t oldest_tick = ~0ULL;
        for (auto cit = tex_srv_cache_.begin(); cit != tex_srv_cache_.end(); ++cit) {
            const uint64_t t = tex_srv_lru_[cit->first];
            if (t < oldest_tick) {
                oldest_tick = t;
                oldest_it = cit;
            }
        }
        if (oldest_it != tex_srv_cache_.end()) {
            if (oldest_it->second) {
                static_cast<ID3D11ShaderResourceView*>(oldest_it->second)->Release();
            }
            tex_srv_lru_.erase(oldest_it->first);
            tex_srv_cache_.erase(oldest_it);
        }
    }

    auto* dev = static_cast<ID3D11Device*>(d3d_device_);
    D3D11_TEXTURE2D_DESC td{};
    td.Width            = tex.width;
    td.Height           = tex.height;
    td.MipLevels        = 1;
    td.ArraySize        = 1;
    td.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
    td.SampleDesc.Count = 1;
    td.Usage            = D3D11_USAGE_IMMUTABLE;
    td.BindFlags        = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA srd{};
    srd.pSysMem     = rgba.data();
    srd.SysMemPitch = static_cast<UINT>(tex.width * 4u);

    ID3D11Texture2D* d3d_tex = nullptr;
    if (FAILED(dev->CreateTexture2D(&td, &srd, &d3d_tex))) {
        return default_white_srv_;
    }
    ID3D11ShaderResourceView* srv = nullptr;
    dev->CreateShaderResourceView(d3d_tex, nullptr, &srv);
    d3d_tex->Release();
    if (!srv) return default_white_srv_;

    tex_srv_cache_[key] = srv;
    tex_srv_lru_[key]   = ++cache_lru_tick_;
    return srv;
}

void* Win32D3D11Host::get_or_create_text_srv(const std::string& utf8_text, int& out_w, int& out_h) {
    auto it = text_srv_cache_.find(utf8_text);
    if (it != text_srv_cache_.end()) {
        text_srv_lru_[utf8_text] = ++cache_lru_tick_;
        auto sz = text_size_cache_[utf8_text];
        out_w = sz.first;
        out_h = sz.second;
        return it->second;
    }
    if (!d3d_device_ || utf8_text.empty()) return nullptr;

    int bmp_w = 0, bmp_h = 0;
    std::vector<uint8_t> rgba;
    if (!rasterize_utf8_text_rgba8(utf8_text, bmp_w, bmp_h, rgba)) {
        return nullptr;
    }

    constexpr size_t kMaxD3D11CachedTexts = 256u;
    if (text_srv_cache_.size() >= kMaxD3D11CachedTexts) {
        auto oldest_it = text_srv_cache_.begin();
        uint64_t oldest_tick = ~0ULL;
        for (auto cit = text_srv_cache_.begin(); cit != text_srv_cache_.end(); ++cit) {
            const uint64_t t = text_srv_lru_[cit->first];
            if (t < oldest_tick) {
                oldest_tick = t;
                oldest_it = cit;
            }
        }
        if (oldest_it != text_srv_cache_.end()) {
            if (oldest_it->second) {
                static_cast<ID3D11ShaderResourceView*>(oldest_it->second)->Release();
            }
            text_srv_lru_.erase(oldest_it->first);
            text_size_cache_.erase(oldest_it->first);
            text_srv_cache_.erase(oldest_it);
        }
    }

    auto* dev = static_cast<ID3D11Device*>(d3d_device_);
    D3D11_TEXTURE2D_DESC td{};
    td.Width            = static_cast<UINT>(bmp_w);
    td.Height           = static_cast<UINT>(bmp_h);
    td.MipLevels        = 1;
    td.ArraySize        = 1;
    td.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
    td.SampleDesc.Count = 1;
    td.Usage            = D3D11_USAGE_IMMUTABLE;
    td.BindFlags        = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA srd{};
    srd.pSysMem     = rgba.data();
    srd.SysMemPitch = static_cast<UINT>(bmp_w * 4);

    ID3D11Texture2D* tex = nullptr;
    if (FAILED(dev->CreateTexture2D(&td, &srd, &tex))) return nullptr;
    ID3D11ShaderResourceView* srv = nullptr;
    dev->CreateShaderResourceView(tex, nullptr, &srv);
    tex->Release();
    if (!srv) return nullptr;

    text_srv_cache_[utf8_text]  = srv;
    text_srv_lru_[utf8_text]    = ++cache_lru_tick_;
    text_size_cache_[utf8_text] = {bmp_w, bmp_h};
    out_w = bmp_w;
    out_h = bmp_h;
    return srv;
}
#endif

#ifdef _WIN32
void Win32D3D11Host::resolve_and_postprocess_to_swapchain() {
    if (!d3d_context_ || !swapchain_rtv_ || !efb_resolved_srv_ || !fxaa_vs_ || !blit_ps_) {
        return;
    }
    auto* ctx = static_cast<ID3D11DeviceContext*>(d3d_context_);
    ID3D11ShaderResourceView* null_srv = nullptr;
    ID3D11RenderTargetView*   null_rtv = nullptr;
    ctx->PSSetShaderResources(0, 1, &null_srv);
    ctx->OMSetRenderTargets(1, &null_rtv, nullptr);

    if (efb_msaa_samples_ > 1u && efb_resolved_tex_ && efb_color_tex_) {
        ctx->ResolveSubresource(
            static_cast<ID3D11Resource*>(efb_resolved_tex_), 0,
            static_cast<ID3D11Resource*>(efb_color_tex_), 0,
            DXGI_FORMAT_R8G8B8A8_UNORM
        );
    }

    auto* out_rtv = static_cast<ID3D11RenderTargetView*>(swapchain_rtv_);
    ctx->OMSetRenderTargets(1, &out_rtv, nullptr);

    const D3D11_VIEWPORT out_vp = compute_output_viewport(cfg_.aspect_ratio, swapchain_width_, swapchain_height_);
    ctx->RSSetViewports(1, &out_vp);
    if (rs_fullscreen_) {
        ctx->RSSetState(static_cast<ID3D11RasterizerState*>(rs_fullscreen_));
    }

    const float blend_factor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    if (blend_opaque_)   ctx->OMSetBlendState(static_cast<ID3D11BlendState*>(blend_opaque_), blend_factor, 0xFFFFFFFFu);
    if (dss_depth_none_) ctx->OMSetDepthStencilState(static_cast<ID3D11DepthStencilState*>(dss_depth_none_), 0);

    const bool use_fxaa = (cfg_.enable_fxaa || cfg_.msaa_mode == AntiAliasingMode::FXAA) && (fxaa_ps_ != nullptr);
    auto* fcb = static_cast<ID3D11Buffer*>(fxaa_cb_);
    if (fcb) {
        FxaaConstantsCPU fc{};
        fc.uInvScreenSize[0] = 1.0f / static_cast<float>((std::max)(1u, efb_width_));
        fc.uInvScreenSize[1] = 1.0f / static_cast<float>((std::max)(1u, efb_height_));
        fc.uSubpixQuality    = fxaa_subpix_quality();
        fc.uEdgeThreshold    = fxaa_edge_threshold();
        fc.uBrightness       = std::clamp(cfg_.brightness, 0.50f, 2.00f);
        fc.uGamma            = resolve_disp_gamma_value(last_disp_gamma_);
        ctx->UpdateSubresource(fcb, 0, nullptr, &fc, 0, 0);
        ctx->PSSetConstantBuffers(0, 1, &fcb);
    }

    auto* srv = static_cast<ID3D11ShaderResourceView*>(efb_resolved_srv_);
    auto* ss  = static_cast<ID3D11SamplerState*>(sampler_linear_clamp_ ? sampler_linear_clamp_ : sampler_aniso_);
    ctx->IASetInputLayout(nullptr);
    ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ctx->VSSetShader(static_cast<ID3D11VertexShader*>(fxaa_vs_), nullptr, 0);
    ctx->PSSetShader(static_cast<ID3D11PixelShader*>(use_fxaa ? fxaa_ps_ : blit_ps_), nullptr, 0);
    ctx->PSSetShaderResources(0, 1, &srv);
    if (ss) ctx->PSSetSamplers(0, 1, &ss);
    ctx->Draw(3u, 0u);
    ctx->PSSetShaderResources(0, 1, &null_srv);
}

void Win32D3D11Host::render_overlay_texts_to_swapchain(const GX3DInterface& gx) {
    const auto& overlays = gx.overlay_texts();
    if (overlays.empty() || !d3d_context_ || !swapchain_rtv_ || !vs_ || !ps_ || !input_layout_ || !dynamic_vb_ || !dynamic_ib_ || !scene_cb_) {
        return;
    }

    std::vector<GXVertex> ov_verts;
    std::vector<uint32_t> ov_indices;
    struct OvDrawItem { void* srv; uint32_t idx_off; };
    std::vector<OvDrawItem> ov_items;
    ov_verts.reserve(overlays.size() * 8u);
    ov_indices.reserve(overlays.size() * 12u);
    ov_items.reserve(overlays.size() * 2u);

    auto push_quad = [&](void* tsrv, float x, float y, float w, float h, float r, float g, float b, float a) {
        if (ov_verts.size() + 4u > kHostMaxDynamicVertices || ov_indices.size() + 6u > kHostMaxDynamicIndices) return;
        const uint32_t vbase = static_cast<uint32_t>(ov_verts.size());
        const uint32_t ibase = static_cast<uint32_t>(ov_indices.size());
        ov_verts.push_back({{x,     y,     0.1f}, {0, 0, 1}, {r, g, b, a}, {0.0f, 0.0f}});
        ov_verts.push_back({{x + w, y,     0.1f}, {0, 0, 1}, {r, g, b, a}, {1.0f, 0.0f}});
        ov_verts.push_back({{x + w, y + h, 0.1f}, {0, 0, 1}, {r, g, b, a}, {1.0f, 1.0f}});
        ov_verts.push_back({{x,     y + h, 0.1f}, {0, 0, 1}, {r, g, b, a}, {0.0f, 1.0f}});
        ov_indices.push_back(vbase + 0u); ov_indices.push_back(vbase + 1u); ov_indices.push_back(vbase + 2u);
        ov_indices.push_back(vbase + 0u); ov_indices.push_back(vbase + 2u); ov_indices.push_back(vbase + 3u);
        ov_items.push_back({tsrv, ibase});
    };

    const uint16_t* dsrc = gx.disp_copy_src();
    const float src_x = static_cast<float>(dsrc[0]);
    const float src_y = static_cast<float>(dsrc[1]);
    const float src_w = static_cast<float>((std::max)(16u, static_cast<uint32_t>(dsrc[2])));
    const float src_h = static_cast<float>((std::max)(16u, static_cast<uint32_t>(dsrc[3])));

    for (const auto& item : overlays) {
        int tw = 0, th = 0;
        void* tsrv = get_or_create_text_srv(item.text, tw, th);
        if (!tsrv || tw <= 0 || th <= 0) continue;
        const float w = static_cast<float>(tw) * item.scale;
        const float h = static_cast<float>(th) * item.scale;
        const float ix = (std::min)(item.x, src_x + (std::max)(4.0f, src_w - w - 28.0f));
        const float iy = (std::min)(item.y, src_y + (std::max)(4.0f, src_h - h - 4.0f));
        const float r = ((item.rgba >> 24) & 0xFFu) / 255.0f;
        const float g = ((item.rgba >> 16) & 0xFFu) / 255.0f;
        const float b = ((item.rgba >> 8) & 0xFFu) / 255.0f;
        const float a = (item.rgba & 0xFFu) / 255.0f;
        push_quad(tsrv, ix + 1.0f, iy + 1.0f, w, h, 0.0f, 0.0f, 0.0f, a * 0.85f);
        push_quad(tsrv, ix, iy, w, h, r, g, b, a);
    }
    if (ov_items.empty()) return;

    auto* ctx = static_cast<ID3D11DeviceContext*>(d3d_context_);
    D3D11_MAPPED_SUBRESOURCE ov_map{};
    if (SUCCEEDED(ctx->Map(static_cast<ID3D11Buffer*>(dynamic_vb_), 0, D3D11_MAP_WRITE_DISCARD, 0, &ov_map))) {
        std::memcpy(ov_map.pData, ov_verts.data(), ov_verts.size() * sizeof(GXVertex));
        ctx->Unmap(static_cast<ID3D11Buffer*>(dynamic_vb_), 0);
    }
    if (SUCCEEDED(ctx->Map(static_cast<ID3D11Buffer*>(dynamic_ib_), 0, D3D11_MAP_WRITE_DISCARD, 0, &ov_map))) {
        std::memcpy(ov_map.pData, ov_indices.data(), ov_indices.size() * sizeof(uint32_t));
        ctx->Unmap(static_cast<ID3D11Buffer*>(dynamic_ib_), 0);
    }

    auto* out_rtv = static_cast<ID3D11RenderTargetView*>(swapchain_rtv_);
    ctx->OMSetRenderTargets(1, &out_rtv, nullptr);
    const D3D11_VIEWPORT out_vp = compute_output_viewport(cfg_.aspect_ratio, swapchain_width_, swapchain_height_);
    ctx->RSSetViewports(1, &out_vp);
    if (rs_fullscreen_) {
        ctx->RSSetState(static_cast<ID3D11RasterizerState*>(rs_fullscreen_));
    }

    UINT stride = sizeof(GXVertex);
    UINT offset = 0;
    auto* vb = static_cast<ID3D11Buffer*>(dynamic_vb_);
    auto* ib = static_cast<ID3D11Buffer*>(dynamic_ib_);
    auto* cb = static_cast<ID3D11Buffer*>(scene_cb_);
    ctx->IASetInputLayout(static_cast<ID3D11InputLayout*>(input_layout_));
    ctx->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
    ctx->IASetIndexBuffer(ib, DXGI_FORMAT_R32_UINT, 0);
    ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ctx->VSSetShader(static_cast<ID3D11VertexShader*>(vs_), nullptr, 0);
    ctx->VSSetConstantBuffers(0, 1, &cb);
    ctx->PSSetShader(static_cast<ID3D11PixelShader*>(ps_), nullptr, 0);
    ctx->PSSetConstantBuffers(0, 1, &cb);

    GXSceneConstantsCPU cdata{};
    fill_centered_43_overlay_ortho_rect(
        cdata.uProjection, src_x, src_y, src_w, src_h, out_vp.Width, out_vp.Height);
    cdata.uModelView[0][0] = cdata.uModelView[1][1] = cdata.uModelView[2][2] = cdata.uModelView[3][3] = 1.0f;
    cdata.uTevColor0[0] = cdata.uTevColor0[1] = cdata.uTevColor0[2] = cdata.uTevColor0[3] = 1.0f;
    cdata.uKonstColor[0] = cdata.uKonstColor[1] = cdata.uKonstColor[2] = cdata.uKonstColor[3] = 1.0f;
    cdata.uViewportSize[0] = out_vp.Width;
    cdata.uViewportSize[1] = out_vp.Height;
    cdata.uTevMode         = 0u;
    cdata.uTevScale        = 1.0f;
    ctx->UpdateSubresource(cb, 0, nullptr, &cdata, 0, 0);

    if (auto* ss = static_cast<ID3D11SamplerState*>(sampler_linear_clamp_ ? sampler_linear_clamp_ : samplers_[0])) {
        ctx->PSSetSamplers(0, 1, &ss);
    }
    const float blend_factor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    ctx->OMSetBlendState(static_cast<ID3D11BlendState*>(blend_alpha_), blend_factor, 0xFFFFFFFFu);
    ctx->OMSetDepthStencilState(static_cast<ID3D11DepthStencilState*>(dss_depth_none_), 0);
    for (const auto& oi : ov_items) {
        auto* srv = static_cast<ID3D11ShaderResourceView*>(oi.srv);
        ctx->PSSetShaderResources(0, 1, &srv);
        ctx->DrawIndexed(6u, oi.idx_off, 0);
    }
}
#endif

void Win32D3D11Host::render_gx_draw_batches(const Memory& mem, GX3DInterface& gx) {
    (void)mem;
    const auto& verts    = gx.vertices();
    const auto& indices  = gx.indices();
    const auto& batches  = gx.draw_batches();
    const auto& overlays = gx.overlay_texts();
    last_rendered_batches_   = batches.size();
    last_rendered_triangles_ = indices.size() / 3u;

#ifdef _WIN32
    if (!d3d_context_ || !vs_ || !ps_ || !input_layout_ || !dynamic_vb_ || !dynamic_ib_ || !scene_cb_) {
        return;
    }
    const bool has_batches = !verts.empty() && !indices.empty() && !batches.empty();
    auto* ctx = static_cast<ID3D11DeviceContext*>(d3d_context_);
    last_disp_gamma_ = gx.disp_copy_gamma();
    const uint16_t* dsrc = gx.disp_copy_src();
    const float src_x = static_cast<float>(dsrc[0]);
    const float src_y = static_cast<float>(dsrc[1]);
    const float src_w = static_cast<float>((std::max)(16u, static_cast<uint32_t>(dsrc[2])));
    const float src_h = static_cast<float>((std::max)(16u, static_cast<uint32_t>(dsrc[3])));

    // 1. Render 3D/2D GameCube GX batches into offscreen internal-resolution MSAA EFB
    if (has_batches && msaa_rtv_) {
        ID3D11ShaderResourceView* null_srvs[2] = {nullptr, nullptr};
        ctx->PSSetShaderResources(0, 2, null_srvs);
        auto* efb_rtv = static_cast<ID3D11RenderTargetView*>(msaa_rtv_);
        auto* efb_dsv = static_cast<ID3D11DepthStencilView*>(msaa_dsv_);
        ctx->OMSetRenderTargets(1, &efb_rtv, efb_dsv);

        D3D11_MAPPED_SUBRESOURCE mapped{};
        const size_t v_count = (std::min)(verts.size(), kHostMaxDynamicVertices);
        if (SUCCEEDED(ctx->Map(static_cast<ID3D11Buffer*>(dynamic_vb_), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped))) {
            std::memcpy(mapped.pData, verts.data(), v_count * sizeof(GXVertex));
            ctx->Unmap(static_cast<ID3D11Buffer*>(dynamic_vb_), 0);
        }
        const size_t i_count = (std::min)(indices.size(), kHostMaxDynamicIndices);
        if (SUCCEEDED(ctx->Map(static_cast<ID3D11Buffer*>(dynamic_ib_), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped))) {
            std::memcpy(mapped.pData, indices.data(), i_count * sizeof(uint32_t));
            ctx->Unmap(static_cast<ID3D11Buffer*>(dynamic_ib_), 0);
        }

        UINT stride = sizeof(GXVertex);
        UINT offset = 0;
        auto* vb = static_cast<ID3D11Buffer*>(dynamic_vb_);
        auto* ib = static_cast<ID3D11Buffer*>(dynamic_ib_);
        auto* cb = static_cast<ID3D11Buffer*>(scene_cb_);
        uint32_t cur_samp_idx  = 4u;
        uint32_t cur_samp1_idx = 0xFFFFFFFFu;
        auto* ss = static_cast<ID3D11SamplerState*>(samplers_[cur_samp_idx] ? samplers_[cur_samp_idx] : sampler_aniso_);

        ctx->IASetInputLayout(static_cast<ID3D11InputLayout*>(input_layout_));
        ctx->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
        ctx->IASetIndexBuffer(ib, DXGI_FORMAT_R32_UINT, 0);
        ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        ctx->VSSetShader(static_cast<ID3D11VertexShader*>(vs_), nullptr, 0);
        ctx->VSSetConstantBuffers(0, 1, &cb);
        ctx->PSSetShader(static_cast<ID3D11PixelShader*>(ps_), nullptr, 0);
        ctx->PSSetConstantBuffers(0, 1, &cb);
        ctx->PSSetSamplers(0, 1, &ss);

        const float blend_factor[4] = {0.0f, 0.0f, 0.0f, 0.0f};

        void* prev_rs    = nullptr;
        void* prev_blend = nullptr;
        void* prev_dss   = nullptr;
        void* prev_srv0  = nullptr;
        void* prev_srv1  = nullptr;
        bool has_prev_vp = false;
        D3D11_VIEWPORT prev_vp{};
        bool has_prev_sc = false;
        D3D11_RECT prev_sc{};
        bool has_prev_cb = false;
        GXSceneConstantsCPU prev_cdata{};

        for (const auto& batch : batches) {
            if (batch.index_offset + batch.index_count > i_count) break;
            if (batch.cull_mode == 3u) continue; // GX_CULL_ALL

            const bool full_efb = should_ortho_batch_fill_efb(
                batch, verts.data(), v_count, indices.data(), i_count,
                src_x, src_y, src_w, src_h);
            const HostViewportRect eb = compute_2d_ortho_efb_bounds(efb_width_, efb_height_, full_efb);
            const float sx = eb.width  / src_w;
            const float sy = eb.height / src_h;

            void* rs_ptr = rs_cull_none_;
            if (batch.cull_mode == 1u && rs_cull_front_) rs_ptr = rs_cull_front_;
            else if (batch.cull_mode == 2u && rs_cull_back_) rs_ptr = rs_cull_back_;
            if (rs_ptr != prev_rs) {
                prev_rs = rs_ptr;
                ctx->RSSetState(static_cast<ID3D11RasterizerState*>(rs_ptr));
            }

            D3D11_VIEWPORT bvp{};
            bvp.TopLeftX = eb.x + (batch.viewport[0] - src_x) * sx;
            bvp.TopLeftY = eb.y + (batch.viewport[1] - src_y) * sy;
            bvp.Width    = (batch.viewport[2] > 0.0f) ? (batch.viewport[2] * sx) : eb.width;
            bvp.Height   = (batch.viewport[3] > 0.0f) ? (batch.viewport[3] * sy) : eb.height;
            bvp.MinDepth = std::clamp(batch.viewport[4], 0.0f, 1.0f);
            bvp.MaxDepth = std::clamp(batch.viewport[5], bvp.MinDepth, 1.0f);
            if (bvp.MaxDepth <= bvp.MinDepth) { bvp.MinDepth = 0.0f; bvp.MaxDepth = 1.0f; }
            if (!has_prev_vp || std::memcmp(&prev_vp, &bvp, sizeof(bvp)) != 0) {
                prev_vp = bvp;
                has_prev_vp = true;
                ctx->RSSetViewports(1, &bvp);
            }

            const int32_t sc_x = static_cast<int32_t>(batch.scissor[0]) - static_cast<int32_t>(dsrc[0]);
            const int32_t sc_y = static_cast<int32_t>(batch.scissor[1]) - static_cast<int32_t>(dsrc[1]);
            const uint32_t raw_sw = (batch.scissor[2] > 0u) ? batch.scissor[2] : static_cast<uint32_t>(src_w);
            const uint32_t raw_sh = (batch.scissor[3] > 0u) ? batch.scissor[3] : static_cast<uint32_t>(src_h);
            D3D11_RECT srect{};
            srect.left   = static_cast<LONG>(std::clamp(eb.x + static_cast<float>(sc_x) * sx, 0.0f, static_cast<float>(efb_width_)));
            srect.top    = static_cast<LONG>(std::clamp(eb.y + static_cast<float>(sc_y) * sy, 0.0f, static_cast<float>(efb_height_)));
            srect.right  = static_cast<LONG>(std::clamp(eb.x + static_cast<float>(sc_x + static_cast<int32_t>(raw_sw)) * sx + 0.5f, static_cast<float>(srect.left), static_cast<float>(efb_width_)));
            srect.bottom = static_cast<LONG>(std::clamp(eb.y + static_cast<float>(sc_y + static_cast<int32_t>(raw_sh)) * sy + 0.5f, static_cast<float>(srect.top), static_cast<float>(efb_height_)));
            if (!has_prev_sc || std::memcmp(&prev_sc, &srect, sizeof(srect)) != 0) {
                prev_sc = srect;
                has_prev_sc = true;
                ctx->RSSetScissorRects(1, &srect);
            }

            if (batch.has_texture) {
                const uint32_t ws = (batch.texture.wrap_s <= 2u) ? batch.texture.wrap_s : 1u;
                const uint32_t wt = (batch.texture.wrap_t <= 2u) ? batch.texture.wrap_t : 1u;
                const uint32_t sidx = ws * 3u + wt;
                if (sidx != cur_samp_idx && samplers_[sidx]) {
                    cur_samp_idx = sidx;
                    auto* bss = static_cast<ID3D11SamplerState*>(samplers_[sidx]);
                    ctx->PSSetSamplers(0, 1, &bss);
                }
            }

            GXSceneConstantsCPU cdata{};
            std::memcpy(cdata.uProjection, batch.proj_mtx, sizeof(cdata.uProjection));
            if (std::fabs(cdata.uProjection[0][0] - 1.0f) < 1e-4f && std::fabs(cdata.uProjection[1][1] - 1.0f) < 1e-4f) {
                fill_ortho_rect(cdata.uProjection, src_x, src_y, src_w, src_h);
            }
            std::memset(cdata.uModelView, 0, sizeof(cdata.uModelView));
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
            if (!has_prev_cb || std::memcmp(&prev_cdata, &cdata, sizeof(cdata)) != 0) {
                prev_cdata = cdata;
                has_prev_cb = true;
                ctx->UpdateSubresource(cb, 0, nullptr, &cdata, 0, 0);
            }

            void* srv_raw = default_white_srv_;
            if (batch.has_texture) {
                srv_raw = get_or_create_texture_srv(mem, gx, batch.texture, batch.tlut);
            }
            if (srv_raw != prev_srv0) {
                prev_srv0 = srv_raw;
                auto* srv = static_cast<ID3D11ShaderResourceView*>(srv_raw);
                ctx->PSSetShaderResources(0, 1, &srv);
            }

            if (batch.has_stage1_tex) {
                const uint32_t ws1 = (batch.stage1_texture.wrap_s <= 2u) ? batch.stage1_texture.wrap_s : 1u;
                const uint32_t wt1 = (batch.stage1_texture.wrap_t <= 2u) ? batch.stage1_texture.wrap_t : 1u;
                const uint32_t sidx1 = ws1 * 3u + wt1;
                if (sidx1 != cur_samp1_idx) {
                    cur_samp1_idx = sidx1;
                    auto* bss1 = static_cast<ID3D11SamplerState*>(samplers_[sidx1] ? samplers_[sidx1] : sampler_aniso_);
                    ctx->PSSetSamplers(1, 1, &bss1);
                }
                void* srv1_raw = get_or_create_texture_srv(mem, gx, batch.stage1_texture, batch.stage1_tlut);
                if (srv1_raw != prev_srv1) {
                    prev_srv1 = srv1_raw;
                    auto* srv1 = static_cast<ID3D11ShaderResourceView*>(srv1_raw);
                    ctx->PSSetShaderResources(1, 1, &srv1);
                }
            }

            void* blend_ptr = blend_alpha_;
            if (batch.blend_type == 0u) {
                blend_ptr = blend_opaque_;
            } else if (batch.blend_type == 1u && batch.blend_dst == 1u) {
                blend_ptr = blend_additive_;
            }
            if (blend_ptr != prev_blend) {
                prev_blend = blend_ptr;
                ctx->OMSetBlendState(static_cast<ID3D11BlendState*>(blend_ptr), blend_factor, 0xFFFFFFFFu);
            }

            void* dss_ptr = dss_depth_ro_;
            if (!batch.z_enable) {
                dss_ptr = dss_depth_none_;
            } else if (batch.z_write) {
                dss_ptr = dss_depth_rw_;
            }
            if (dss_ptr != prev_dss) {
                prev_dss = dss_ptr;
                ctx->OMSetDepthStencilState(static_cast<ID3D11DepthStencilState*>(dss_ptr), 0);
            }

            ctx->DrawIndexed(batch.index_count, batch.index_offset, 0);
        }
    }

    // 2. Resolve MSAA EFB & run FXAA/aspect-corrected copy into swapchain backbuffer
    resolve_and_postprocess_to_swapchain();

    // 3. Render localized HUD / subtitle overlay text quads crisply AFTER FXAA
    if (!overlays.empty()) {
        render_overlay_texts_to_swapchain(gx);
    }
    batches_rendered_this_frame_ = true;
#endif
}

void Win32D3D11Host::ensure_frame_batches_rendered() {
    if (batches_rendered_this_frame_) {
        return;
    }
    if (Memory::active_instance() != nullptr) {
        render_gx_draw_batches(*Memory::active_instance(), global_gx_3d_interface());
    } else {
#ifdef _WIN32
        resolve_and_postprocess_to_swapchain();
        render_overlay_texts_to_swapchain(global_gx_3d_interface());
#endif
        batches_rendered_this_frame_ = true;
    }
}

void Win32D3D11Host::flush_d3d11() {
    ensure_frame_batches_rendered();
#ifdef _WIN32
    if (d3d_context_) {
        static_cast<ID3D11DeviceContext*>(d3d_context_)->Flush();
    }
#endif
}

void Win32D3D11Host::end_d3d11_frame_and_present() {
    ensure_frame_batches_rendered();
#ifdef _WIN32
    if (swap_chain_) {
        // When the 59.94Hz software pacer is active, it paces frame boundaries directly;
        // avoid SyncInterval=1 blocking on 60/144Hz VBlank to prevent beat-frequency hitches.
        const UINT sync_interval = (cfg_.vsync && !cfg_.limit_fps_60) ? 1u : 0u;
        static_cast<IDXGISwapChain*>(swap_chain_)->Present(sync_interval, 0);
    }
#endif
}

bool Win32D3D11Host::dump_framebuffer_bmp(const std::string& path) {
#ifdef _WIN32
    if (!d3d_device_ || !d3d_context_ || !swap_chain_) return false;
    auto* dev = static_cast<ID3D11Device*>(d3d_device_);
    auto* ctx = static_cast<ID3D11DeviceContext*>(d3d_context_);
    auto* sc  = static_cast<IDXGISwapChain*>(swap_chain_);

    ID3D11Texture2D* back_buf = nullptr;
    if (FAILED(sc->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&back_buf))) || !back_buf) {
        return false;
    }

    D3D11_TEXTURE2D_DESC desc{};
    back_buf->GetDesc(&desc);

    ID3D11Texture2D* src_tex = back_buf;
    ID3D11Texture2D* resolve_tex = nullptr;
    if (desc.SampleDesc.Count > 1) {
        D3D11_TEXTURE2D_DESC rdesc = desc;
        rdesc.SampleDesc.Count = 1;
        rdesc.SampleDesc.Quality = 0;
        rdesc.Usage = D3D11_USAGE_DEFAULT;
        rdesc.BindFlags = 0;
        if (FAILED(dev->CreateTexture2D(&rdesc, nullptr, &resolve_tex)) || !resolve_tex) {
            back_buf->Release();
            return false;
        }
        ctx->ResolveSubresource(resolve_tex, 0, back_buf, 0, desc.Format);
        src_tex = resolve_tex;
    }

    D3D11_TEXTURE2D_DESC sdesc = desc;
    sdesc.SampleDesc.Count = 1;
    sdesc.SampleDesc.Quality = 0;
    sdesc.Usage = D3D11_USAGE_STAGING;
    sdesc.BindFlags = 0;
    sdesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    sdesc.MiscFlags = 0;

    ID3D11Texture2D* staging = nullptr;
    if (FAILED(dev->CreateTexture2D(&sdesc, nullptr, &staging)) || !staging) {
        if (resolve_tex) resolve_tex->Release();
        back_buf->Release();
        return false;
    }
    ctx->CopyResource(staging, src_tex);

    D3D11_MAPPED_SUBRESOURCE mapped{};
    bool ok = false;
    if (SUCCEEDED(ctx->Map(staging, 0, D3D11_MAP_READ, 0, &mapped))) {
        ok = write_bmp24_from_rgba8(
            path,
            sdesc.Width,
            sdesc.Height,
            static_cast<const uint8_t*>(mapped.pData),
            mapped.RowPitch,
            false);
        ctx->Unmap(staging, 0);
    }

    staging->Release();
    if (resolve_tex) resolve_tex->Release();
    back_buf->Release();
    return ok;
#else
    (void)path;
    return false;
#endif
}

} // namespace pn03

#include "pn03_runtime.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <filesystem>
#include <mutex>
#include <vector>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif
#include <windows.h>
#include <mmsystem.h>
#include <Xinput.h>
#include <dinput.h>
#pragma comment(lib, "Xinput.lib")
#endif

namespace pn03 {

static PadXInputBridge* g_active_pad_bridge = nullptr;

void PadXInputBridge::set_active_instance(PadXInputBridge* bridge) {
    g_active_pad_bridge = bridge;
}

PadXInputBridge* PadXInputBridge::active_instance() {
    return g_active_pad_bridge;
}

int8_t PadXInputBridge::apply_deadzone_and_clamp(float v, float deadzone) {
    if (std::fabs(v) < deadzone) return 0;
    float sign = (v >= 0.0f) ? 1.0f : -1.0f;
    float norm = (std::fabs(v) - deadzone) / (1.0f - deadzone);
    norm = std::clamp(norm, 0.0f, 1.0f);
    int val = static_cast<int>(std::round(sign * norm * 100.0f));
    return static_cast<int8_t>(std::clamp(val, -100, 100));
}

#ifndef XINPUT_GAMEPAD_GUIDE
#define XINPUT_GAMEPAD_GUIDE 0x0400
#endif

#ifdef _WIN32
namespace {

static std::mutex g_pad_backend_mutex;

void decode_pov_hat(DWORD pov, XboxInputState& st) {
    if (LOWORD(pov) == 0xFFFFu || pov >= 36000u) return;
    if (pov <= 4500u || pov >= 31500u) st.dpad_up = true;
    if (pov >= 4500u && pov <= 13500u) st.dpad_right = true;
    if (pov >= 13500u && pov <= 22500u) st.dpad_down = true;
    if (pov >= 22500u && pov <= 31500u) st.dpad_left = true;
}

// --- Optional Runtime SDL2.dll Backend (Supports DS4, DualSense, Switch, Proton/Steam Input, evdev/hidraw) ---
struct SDL2Api {
    using SDL_GameController = struct OpaqueSDLGameController;
    using FnInitSubSystem  = int (*)(uint32_t);
    using FnSetHint        = int (*)(const char*, const char*);
    using FnNumJoysticks   = int (*)();
    using FnIsGameCtrl     = int (*)(int);
    using FnCtrlOpen       = SDL_GameController* (*)(int);
    using FnCtrlClose      = void (*)(SDL_GameController*);
    using FnCtrlAttached   = int (*)(SDL_GameController*);
    using FnCtrlUpdate     = void (*)();
    using FnCtrlGetBtn     = uint8_t (*)(SDL_GameController*, int);
    using FnCtrlGetAxis    = int16_t (*)(SDL_GameController*, int);
    using FnCtrlRumble     = int (*)(SDL_GameController*, uint16_t, uint16_t, uint32_t);

    HMODULE         mod         = nullptr;
    bool            probed      = false;
    bool            ready       = false;
    FnInitSubSystem pInitSub    = nullptr;
    FnSetHint       pSetHint    = nullptr;
    FnNumJoysticks  pNumJoy     = nullptr;
    FnIsGameCtrl    pIsCtrl     = nullptr;
    FnCtrlOpen      pOpen       = nullptr;
    FnCtrlClose     pClose      = nullptr;
    FnCtrlAttached  pAttached   = nullptr;
    FnCtrlUpdate    pUpdate     = nullptr;
    FnCtrlGetBtn    pGetBtn     = nullptr;
    FnCtrlGetAxis   pGetAxis    = nullptr;
    FnCtrlRumble    pRumble     = nullptr;
    SDL_GameController* handle  = nullptr;
    int             opened_idx  = -1;

    static SDL2Api& instance() {
        static SDL2Api s;
        return s;
    }

    bool ensure_loaded() {
        if (probed) return ready;
        probed = true;

        mod = GetModuleHandleW(L"SDL2.dll");
        if (!mod) mod = LoadLibraryW(L"SDL2.dll");
        if (!mod) {
            wchar_t exe_buf[MAX_PATH] = {0};
            if (GetModuleFileNameW(nullptr, exe_buf, MAX_PATH) > 0) {
                std::filesystem::path dir = std::filesystem::path(exe_buf).parent_path();
                for (const auto& cand : {dir / L"SDL2.dll", dir.parent_path() / L"SDL2.dll"}) {
                    std::error_code ec;
                    if (std::filesystem::exists(cand, ec)) {
                        mod = LoadLibraryW(cand.c_str());
                        if (mod) break;
                    }
                }
            }
        }
        if (!mod) return false;

        pInitSub  = reinterpret_cast<FnInitSubSystem>(GetProcAddress(mod, "SDL_InitSubSystem"));
        pSetHint  = reinterpret_cast<FnSetHint>(GetProcAddress(mod, "SDL_SetHint"));
        pNumJoy   = reinterpret_cast<FnNumJoysticks>(GetProcAddress(mod, "SDL_NumJoysticks"));
        pIsCtrl   = reinterpret_cast<FnIsGameCtrl>(GetProcAddress(mod, "SDL_IsGameController"));
        pOpen     = reinterpret_cast<FnCtrlOpen>(GetProcAddress(mod, "SDL_GameControllerOpen"));
        pClose    = reinterpret_cast<FnCtrlClose>(GetProcAddress(mod, "SDL_GameControllerClose"));
        pAttached = reinterpret_cast<FnCtrlAttached>(GetProcAddress(mod, "SDL_GameControllerGetAttached"));
        pUpdate   = reinterpret_cast<FnCtrlUpdate>(GetProcAddress(mod, "SDL_GameControllerUpdate"));
        pGetBtn   = reinterpret_cast<FnCtrlGetBtn>(GetProcAddress(mod, "SDL_GameControllerGetButton"));
        pGetAxis  = reinterpret_cast<FnCtrlGetAxis>(GetProcAddress(mod, "SDL_GameControllerGetAxis"));
        pRumble   = reinterpret_cast<FnCtrlRumble>(GetProcAddress(mod, "SDL_GameControllerRumble"));

        if (!pInitSub || !pNumJoy || !pIsCtrl || !pOpen || !pAttached || !pUpdate || !pGetBtn || !pGetAxis) {
            return false;
        }
        if (pSetHint) {
            pSetHint("SDL_JOYSTICK_ALLOW_BACKGROUND_EVENTS", "1");
            pSetHint("SDL_JOYSTICK_HIDAPI", "1");
            pSetHint("SDL_JOYSTICK_HIDAPI_PS4", "1");
            pSetHint("SDL_JOYSTICK_HIDAPI_PS5", "1");
            pSetHint("SDL_JOYSTICK_HIDAPI_SWITCH", "1");
            pSetHint("SDL_GAMECONTROLLER_ALLOW_STEAM_VIRTUAL_GAMEPAD", "1");
        }
        // SDL_INIT_JOYSTICK (0x200) | SDL_INIT_GAMECONTROLLER (0x2000)
        if (pInitSub(0x2200u) != 0) {
            return false;
        }
        ready = true;
        return true;
    }

    bool poll(int preferred_index, XboxInputState& out) {
        if (!ensure_loaded()) return false;
        pUpdate();

        if (handle && !pAttached(handle)) {
            if (pClose) pClose(handle);
            handle = nullptr;
            opened_idx = -1;
        }
        const int num = pNumJoy();
        if (!handle && num > 0) {
            if (preferred_index >= 0 && preferred_index < num && pIsCtrl(preferred_index)) {
                handle = pOpen(preferred_index);
                if (handle) opened_idx = preferred_index;
            }
            if (!handle) {
                for (int i = 0; i < num; ++i) {
                    if (pIsCtrl(i)) {
                        handle = pOpen(i);
                        if (handle) { opened_idx = i; break; }
                    }
                }
            }
        }
        if (!handle || !pAttached(handle)) return false;

        out.connected  = true;
        out.btn_a      = (pGetBtn(handle, 0) != 0);  // SDL_CONTROLLER_BUTTON_A
        out.btn_b      = (pGetBtn(handle, 1) != 0);  // B
        out.btn_x      = (pGetBtn(handle, 2) != 0);  // X
        out.btn_y      = (pGetBtn(handle, 3) != 0);  // Y
        out.btn_back   = (pGetBtn(handle, 4) != 0);  // BACK / Share
        out.btn_guide  = (pGetBtn(handle, 5) != 0);  // GUIDE / PS
        out.btn_start  = (pGetBtn(handle, 6) != 0);  // START / Options
        out.btn_ls     = (pGetBtn(handle, 7) != 0);  // LEFTSTICK
        out.btn_rs     = (pGetBtn(handle, 8) != 0);  // RIGHTSTICK
        out.btn_lb     = (pGetBtn(handle, 9) != 0);  // LEFTSHOULDER
        out.btn_rb     = (pGetBtn(handle, 10) != 0); // RIGHTSHOULDER
        out.dpad_up    = (pGetBtn(handle, 11) != 0); // DPAD_UP
        out.dpad_down  = (pGetBtn(handle, 12) != 0); // DPAD_DOWN
        out.dpad_left  = (pGetBtn(handle, 13) != 0); // DPAD_LEFT
        out.dpad_right = (pGetBtn(handle, 14) != 0); // DPAD_RIGHT

        // SDL Y axes are negative-up; GameCube & XInput expect positive-up.
        out.left_stick_x  =  static_cast<float>(pGetAxis(handle, 0)) / 32768.0f;
        out.left_stick_y  = -static_cast<float>(pGetAxis(handle, 1)) / 32768.0f;
        out.right_stick_x =  static_cast<float>(pGetAxis(handle, 2)) / 32768.0f;
        out.right_stick_y = -static_cast<float>(pGetAxis(handle, 3)) / 32768.0f;
        out.left_trigger  = std::clamp(static_cast<float>(pGetAxis(handle, 4)) / 32767.0f, 0.0f, 1.0f);
        out.right_trigger = std::clamp(static_cast<float>(pGetAxis(handle, 5)) / 32767.0f, 0.0f, 1.0f);
        return true;
    }

    void rumble(float scaled_strength) {
        if (ready && handle && pRumble && pAttached(handle)) {
            const uint16_t motor = static_cast<uint16_t>(std::clamp(scaled_strength, 0.0f, 1.0f) * 65535.0f);
            pRumble(handle, motor, motor, motor > 0 ? 500u : 0u);
        }
    }
};

// --- Dynamic XInput Backend (ordinal 100 Guide support + XInputGetState fallback, scans 0..3) ---
struct XInputDynamic {
    using FnGetStateEx = DWORD(WINAPI*)(DWORD, XINPUT_STATE*);
    using FnSetState   = DWORD(WINAPI*)(DWORD, XINPUT_VIBRATION*);

    bool         probed     = false;
    FnGetStateEx pGetState  = nullptr;
    FnSetState   pSetState  = nullptr;
    DWORD        active_idx = 0u;

    static XInputDynamic& instance() {
        static XInputDynamic s;
        return s;
    }

    void ensure_loaded() {
        if (probed) return;
        probed = true;
        const wchar_t* dlls[] = {L"xinput1_4.dll", L"xinput1_3.dll", L"xinput9_1_0.dll"};
        for (const wchar_t* name : dlls) {
            HMODULE mod = LoadLibraryW(name);
            if (!mod) continue;
            if (!pGetState) {
                pGetState = reinterpret_cast<FnGetStateEx>(GetProcAddress(mod, MAKEINTRESOURCEA(100)));
                if (!pGetState) {
                    pGetState = reinterpret_cast<FnGetStateEx>(GetProcAddress(mod, "XInputGetState"));
                }
            }
            if (!pSetState) {
                pSetState = reinterpret_cast<FnSetState>(GetProcAddress(mod, "XInputSetState"));
            }
            if (pGetState && pSetState) break;
        }
        if (!pGetState) pGetState = XInputGetState;
        if (!pSetState) pSetState = XInputSetState;
    }

    bool poll(int preferred_idx, XboxInputState& st) {
        ensure_loaded();
        XINPUT_STATE xst{};
        DWORD chosen = static_cast<DWORD>(std::clamp(preferred_idx, 0, 3));
        DWORD res = pGetState(chosen, &xst);
        if (res != ERROR_SUCCESS) {
            for (DWORD slot = 0; slot < 4u; ++slot) {
                if (slot == chosen) continue;
                if (pGetState(slot, &xst) == ERROR_SUCCESS) {
                    chosen = slot;
                    res = ERROR_SUCCESS;
                    break;
                }
            }
        }
        if (res != ERROR_SUCCESS) return false;

        active_idx    = chosen;
        st.connected  = true;
        const WORD w  = xst.Gamepad.wButtons;
        st.btn_a      = (w & XINPUT_GAMEPAD_A) != 0;
        st.btn_b      = (w & XINPUT_GAMEPAD_B) != 0;
        st.btn_x      = (w & XINPUT_GAMEPAD_X) != 0;
        st.btn_y      = (w & XINPUT_GAMEPAD_Y) != 0;
        st.btn_start  = (w & XINPUT_GAMEPAD_START) != 0;
        st.btn_back   = (w & XINPUT_GAMEPAD_BACK) != 0;
        st.btn_lb     = (w & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0;
        st.btn_rb     = (w & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;
        st.btn_guide  = (w & XINPUT_GAMEPAD_GUIDE) != 0;
        st.btn_ls     = (w & XINPUT_GAMEPAD_LEFT_THUMB) != 0;
        st.btn_rs     = (w & XINPUT_GAMEPAD_RIGHT_THUMB) != 0;
        st.dpad_up    = (w & XINPUT_GAMEPAD_DPAD_UP) != 0;
        st.dpad_down  = (w & XINPUT_GAMEPAD_DPAD_DOWN) != 0;
        st.dpad_left  = (w & XINPUT_GAMEPAD_DPAD_LEFT) != 0;
        st.dpad_right = (w & XINPUT_GAMEPAD_DPAD_RIGHT) != 0;

        st.left_stick_x  = static_cast<float>(xst.Gamepad.sThumbLX) / 32768.0f;
        st.left_stick_y  = static_cast<float>(xst.Gamepad.sThumbLY) / 32768.0f;
        st.right_stick_x = static_cast<float>(xst.Gamepad.sThumbRX) / 32768.0f;
        st.right_stick_y = static_cast<float>(xst.Gamepad.sThumbRY) / 32768.0f;
        st.left_trigger  = static_cast<float>(xst.Gamepad.bLeftTrigger) / 255.0f;
        st.right_trigger = static_cast<float>(xst.Gamepad.bRightTrigger) / 255.0f;
        return true;
    }

    void rumble(int preferred_idx, float scaled_strength) {
        ensure_loaded();
        XINPUT_VIBRATION vib{};
        const WORD motor = static_cast<WORD>(std::clamp(scaled_strength, 0.0f, 1.0f) * 65535.0f);
        vib.wLeftMotorSpeed  = motor;
        vib.wRightMotorSpeed = motor;
        const DWORD slot = (active_idx < 4u) ? active_idx : static_cast<DWORD>(std::clamp(preferred_idx, 0, 3));
        pSetState(slot, &vib);
    }
};

// --- Dynamic DirectInput8 Backend (No dinput8.lib/dxguid.lib needed; covers DS4/DualSense & Wine HID) ---
constexpr GUID PN03_IID_IDirectInput8W = {0xBF798031u, 0x483Au, 0x4DA2u, {0xAA, 0x99, 0x5D, 0x64, 0xED, 0x36, 0x97, 0x00}};
constexpr GUID PN03_GUID_XAxis         = {0xA36D02E0u, 0xC9F3u, 0x11CFu, {0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00}};
constexpr GUID PN03_GUID_YAxis         = {0xA36D02E1u, 0xC9F3u, 0x11CFu, {0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00}};
constexpr GUID PN03_GUID_ZAxis         = {0xA36D02E2u, 0xC9F3u, 0x11CFu, {0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00}};
constexpr GUID PN03_GUID_RxAxis        = {0xA36D02F4u, 0xC9F3u, 0x11CFu, {0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00}};
constexpr GUID PN03_GUID_RyAxis        = {0xA36D02F5u, 0xC9F3u, 0x11CFu, {0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00}};
constexpr GUID PN03_GUID_RzAxis        = {0xA36D02E3u, 0xC9F3u, 0x11CFu, {0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00}};
constexpr GUID PN03_GUID_Slider        = {0xA36D02E4u, 0xC9F3u, 0x11CFu, {0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00}};
constexpr GUID PN03_GUID_POV           = {0xA36D02F2u, 0xC9F3u, 0x11CFu, {0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00}};

#ifndef DIDFT_OPTIONAL
#define DIDFT_OPTIONAL 0x80000000u
#endif

const DIDATAFORMAT& get_pn03_dijoystate_format() {
    static DIOBJECTDATAFORMAT objs[] = {
        {&PN03_GUID_XAxis,  offsetof(DIJOYSTATE, lX),           DIDFT_AXIS | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, DIDOI_ASPECTPOSITION},
        {&PN03_GUID_YAxis,  offsetof(DIJOYSTATE, lY),           DIDFT_AXIS | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, DIDOI_ASPECTPOSITION},
        {&PN03_GUID_ZAxis,  offsetof(DIJOYSTATE, lZ),           DIDFT_AXIS | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, DIDOI_ASPECTPOSITION},
        {&PN03_GUID_RxAxis, offsetof(DIJOYSTATE, lRx),          DIDFT_AXIS | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, DIDOI_ASPECTPOSITION},
        {&PN03_GUID_RyAxis, offsetof(DIJOYSTATE, lRy),          DIDFT_AXIS | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, DIDOI_ASPECTPOSITION},
        {&PN03_GUID_RzAxis, offsetof(DIJOYSTATE, lRz),          DIDFT_AXIS | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, DIDOI_ASPECTPOSITION},
        {&PN03_GUID_Slider, offsetof(DIJOYSTATE, rglSlider[0]), DIDFT_AXIS | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, DIDOI_ASPECTPOSITION},
        {&PN03_GUID_Slider, offsetof(DIJOYSTATE, rglSlider[1]), DIDFT_AXIS | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, DIDOI_ASPECTPOSITION},
        {&PN03_GUID_POV,    offsetof(DIJOYSTATE, rgdwPOV[0]),   DIDFT_POV  | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0u},
        {nullptr,           offsetof(DIJOYSTATE, rgbButtons[0]),  DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0u},
        {nullptr,           offsetof(DIJOYSTATE, rgbButtons[1]),  DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0u},
        {nullptr,           offsetof(DIJOYSTATE, rgbButtons[2]),  DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0u},
        {nullptr,           offsetof(DIJOYSTATE, rgbButtons[3]),  DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0u},
        {nullptr,           offsetof(DIJOYSTATE, rgbButtons[4]),  DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0u},
        {nullptr,           offsetof(DIJOYSTATE, rgbButtons[5]),  DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0u},
        {nullptr,           offsetof(DIJOYSTATE, rgbButtons[6]),  DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0u},
        {nullptr,           offsetof(DIJOYSTATE, rgbButtons[7]),  DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0u},
        {nullptr,           offsetof(DIJOYSTATE, rgbButtons[8]),  DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0u},
        {nullptr,           offsetof(DIJOYSTATE, rgbButtons[9]),  DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0u},
        {nullptr,           offsetof(DIJOYSTATE, rgbButtons[10]), DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0u},
        {nullptr,           offsetof(DIJOYSTATE, rgbButtons[11]), DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0u},
        {nullptr,           offsetof(DIJOYSTATE, rgbButtons[12]), DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0u},
        {nullptr,           offsetof(DIJOYSTATE, rgbButtons[13]), DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0u}
    };
    static const DIDATAFORMAT fmt = {
        sizeof(DIDATAFORMAT),
        sizeof(DIOBJECTDATAFORMAT),
        DIDF_ABSAXIS,
        sizeof(DIJOYSTATE),
        static_cast<DWORD>(sizeof(objs) / sizeof(objs[0])),
        objs
    };
    return fmt;
}

class DInputDynamic {
public:
    struct DevSlot {
        IDirectInputDevice8W* dev     = nullptr;
        uint16_t              vid     = 0;
        uint16_t              pid     = 0;
        bool                  is_sony = false;
    };

    static DInputDynamic& instance() {
        static DInputDynamic s;
        return s;
    }

    ~DInputDynamic() { release_all(); }

    bool poll(int preferred_idx, XboxInputState& st, bool& out_is_sony) {
        if (!ensure_init()) return false;
        const ULONGLONG now = GetTickCount64();
        if (devices_.empty() && (last_enum_ms_ == 0u || now - last_enum_ms_ >= 1500u)) {
            enumerate_devices(now);
        }
        if (devices_.empty()) return false;

        int start = std::clamp(preferred_idx, 0, static_cast<int>(devices_.size()) - 1);
        for (int pass = 0; pass < static_cast<int>(devices_.size()); ++pass) {
            const size_t idx = static_cast<size_t>((start + pass) % static_cast<int>(devices_.size()));
            DevSlot& slot = devices_[idx];
            if (!slot.dev) continue;

            HRESULT hr = slot.dev->Poll();
            if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED) {
                slot.dev->Acquire();
                hr = slot.dev->Poll();
            }
            DIJOYSTATE js{};
            if (FAILED(hr) || FAILED(slot.dev->GetDeviceState(sizeof(js), &js))) {
                continue;
            }

            st.connected = true;
            out_is_sony = slot.is_sony;
            const auto btn = [&](size_t bi) { return bi < 32u && (js.rgbButtons[bi] & 0x80u) != 0; };

            st.left_stick_x =  std::clamp(static_cast<float>(js.lX) / 32768.0f, -1.0f, 1.0f);
            st.left_stick_y = -std::clamp(static_cast<float>(js.lY) / 32768.0f, -1.0f, 1.0f);

            // Detect Sony DS4/DualSense raw USB HID layout (Z/Rz=RStick, Rx/Ry=L2/R2) vs generic HID (Rx/Ry or Z/Rz=RStick)
            const bool sony_raw_axes = slot.is_sony ||
                                       (js.lRx <= -20000 && js.lRy <= -20000 &&
                                        std::abs(js.lZ) < 18000 && std::abs(js.lRz) < 18000);
            if (slot.is_sony && sony_raw_axes) {
                st.btn_x      = btn(0);  // Square
                st.btn_a      = btn(1);  // Cross
                st.btn_b      = btn(2);  // Circle
                st.btn_y      = btn(3);  // Triangle
                st.btn_lb     = btn(4);  // L1
                st.btn_rb     = btn(5);  // R1
                st.btn_back   = btn(8);  // Share
                st.btn_start  = btn(9);  // Options
                st.btn_ls     = btn(10); // L3
                st.btn_rs     = btn(11); // R3
                st.btn_guide  = btn(12); // PS Button
                st.right_stick_x =  std::clamp(static_cast<float>(js.lZ)  / 32768.0f, -1.0f, 1.0f);
                st.right_stick_y = -std::clamp(static_cast<float>(js.lRz) / 32768.0f, -1.0f, 1.0f);
                float lt_norm = std::clamp((static_cast<float>(js.lRx) + 32768.0f) / 65535.0f, 0.0f, 1.0f);
                float rt_norm = std::clamp((static_cast<float>(js.lRy) + 32768.0f) / 65535.0f, 0.0f, 1.0f);
                if (btn(6) && lt_norm < 0.05f) lt_norm = 1.0f;
                if (btn(7) && rt_norm < 0.05f) rt_norm = 1.0f;
                st.left_trigger  = lt_norm;
                st.right_trigger = rt_norm;
            } else {
                st.btn_a      = btn(0);
                st.btn_b      = btn(1);
                st.btn_x      = btn(2);
                st.btn_y      = btn(3);
                st.btn_lb     = btn(4);
                st.btn_rb     = btn(5);
                st.btn_back   = btn(6);
                st.btn_start  = btn(7);
                st.btn_ls     = btn(8);
                st.btn_rs     = btn(9);
                st.btn_guide  = btn(10) || btn(12);
                const bool use_rx_ry = (std::abs(js.lRx) < 28000 && std::abs(js.lRy) < 28000 &&
                                        (js.lRx != 0 || js.lRy != 0));
                if (use_rx_ry) {
                    st.right_stick_x =  std::clamp(static_cast<float>(js.lRx) / 32768.0f, -1.0f, 1.0f);
                    st.right_stick_y = -std::clamp(static_cast<float>(js.lRy) / 32768.0f, -1.0f, 1.0f);
                    if (js.lZ > 1024) st.left_trigger = std::clamp(static_cast<float>(js.lZ) / 32768.0f, 0.0f, 1.0f);
                    else if (js.lZ < -1024) st.right_trigger = std::clamp(static_cast<float>(-js.lZ) / 32768.0f, 0.0f, 1.0f);
                } else {
                    st.right_stick_x =  std::clamp(static_cast<float>(js.lZ)  / 32768.0f, -1.0f, 1.0f);
                    st.right_stick_y = -std::clamp(static_cast<float>(js.lRz) / 32768.0f, -1.0f, 1.0f);
                }
            }
            decode_pov_hat(js.rgdwPOV[0], st);
            return true;
        }
        return false;
    }

private:
    bool ensure_init() {
        if (di8_) return true;
        if (failed_) return false;
        mod_ = LoadLibraryW(L"dinput8.dll");
        if (!mod_) { failed_ = true; return false; }
        using FnDI8Create = HRESULT(WINAPI*)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
        auto fn = reinterpret_cast<FnDI8Create>(GetProcAddress(mod_, "DirectInput8Create"));
        if (!fn) { failed_ = true; return false; }
        if (FAILED(fn(GetModuleHandleW(nullptr), DIRECTINPUT_VERSION, PN03_IID_IDirectInput8W,
                      reinterpret_cast<void**>(&di8_), nullptr)) || !di8_) {
            failed_ = true;
            return false;
        }
        return true;
    }

    static BOOL CALLBACK enum_cb(LPCDIDEVICEINSTANCEW inst, LPVOID ref) {
        auto* self = static_cast<DInputDynamic*>(ref);
        if (!inst || !self || !self->di8_) return DIENUM_STOP;
        IDirectInputDevice8W* dev = nullptr;
        if (FAILED(self->di8_->CreateDevice(inst->guidInstance, &dev, nullptr)) || !dev) {
            return DIENUM_CONTINUE;
        }
        if (FAILED(dev->SetDataFormat(&get_pn03_dijoystate_format()))) {
            dev->Release();
            return DIENUM_CONTINUE;
        }
        dev->SetCooperativeLevel(nullptr, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
        DIPROPRANGE diprg{};
        diprg.diph.dwSize       = sizeof(DIPROPRANGE);
        diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
        diprg.diph.dwHow        = DIPH_DEVICE;
        diprg.diph.dwObj        = 0;
        diprg.lMin              = -32768;
        diprg.lMax              =  32767;
        dev->SetProperty(DIPROP_RANGE, &diprg.diph);
        dev->Acquire();

        DevSlot slot{};
        slot.dev     = dev;
        slot.vid     = static_cast<uint16_t>(inst->guidProduct.Data1 & 0xFFFFu);
        slot.pid     = static_cast<uint16_t>((inst->guidProduct.Data1 >> 16) & 0xFFFFu);
        slot.is_sony = (slot.vid == 0x054Cu);
        self->devices_.push_back(slot);
        return (self->devices_.size() < 4u) ? DIENUM_CONTINUE : DIENUM_STOP;
    }

    void enumerate_devices(ULONGLONG now) {
        release_devices();
        last_enum_ms_ = now;
        if (di8_) {
            di8_->EnumDevices(DI8DEVCLASS_GAMECTRL, enum_cb, this, DIEDFL_ATTACHEDONLY);
        }
    }

    void release_devices() {
        for (auto& d : devices_) {
            if (d.dev) {
                d.dev->Unacquire();
                d.dev->Release();
            }
        }
        devices_.clear();
    }

    void release_all() {
        release_devices();
        if (di8_) { di8_->Release(); di8_ = nullptr; }
    }

    HMODULE               mod_          = nullptr;
    IDirectInput8W*       di8_          = nullptr;
    bool                  failed_       = false;
    ULONGLONG             last_enum_ms_ = 0;
    std::vector<DevSlot>  devices_;
};

// --- WinMM Fallback (`winmm.lib`, always present on Windows & Wine/Proton) ---
bool poll_winmm_joystick(int preferred_idx, XboxInputState& st, bool& out_is_sony) {
    const UINT max_devs = (std::min)(16u, joyGetNumDevs());
    for (UINT pass = 0; pass < max_devs; ++pass) {
        const UINT id = (static_cast<UINT>(std::max(0, preferred_idx)) + pass) % (std::max)(1u, max_devs);
        JOYINFOEX ji{};
        ji.dwSize  = sizeof(ji);
        ji.dwFlags = JOY_RETURNALL;
        if (joyGetPosEx(id, &ji) != JOYERR_NOERROR) continue;

        JOYCAPSW caps{};
        const bool has_caps = (joyGetDevCapsW(id, &caps, sizeof(caps)) == MMSYSERR_NOERROR);
        const bool is_sony  = has_caps && (caps.wMid == 0x054Cu);
        out_is_sony         = is_sony;

        auto norm_signed = [](DWORD val, DWORD mn, DWORD mx) -> float {
            if (mx <= mn) return (static_cast<float>(val) - 32767.5f) / 32767.5f;
            return std::clamp(((static_cast<float>(val - mn) / static_cast<float>(mx - mn)) * 2.0f) - 1.0f, -1.0f, 1.0f);
        };
        auto norm_trig = [](DWORD val, DWORD mn, DWORD mx) -> float {
            if (mx <= mn) return std::clamp(static_cast<float>(val) / 65535.0f, 0.0f, 1.0f);
            return std::clamp(static_cast<float>(val - mn) / static_cast<float>(mx - mn), 0.0f, 1.0f);
        };

        st.connected     = true;
        st.left_stick_x  =  norm_signed(ji.dwXpos, has_caps ? caps.wXmin : 0u, has_caps ? caps.wXmax : 65535u);
        st.left_stick_y  = -norm_signed(ji.dwYpos, has_caps ? caps.wYmin : 0u, has_caps ? caps.wYmax : 65535u);
        if (is_sony) {
            st.btn_x      = (ji.dwButtons & (1u << 0)) != 0;
            st.btn_a      = (ji.dwButtons & (1u << 1)) != 0;
            st.btn_b      = (ji.dwButtons & (1u << 2)) != 0;
            st.btn_y      = (ji.dwButtons & (1u << 3)) != 0;
            st.btn_lb     = (ji.dwButtons & (1u << 4)) != 0;
            st.btn_rb     = (ji.dwButtons & (1u << 5)) != 0;
            st.btn_back   = (ji.dwButtons & (1u << 8)) != 0;
            st.btn_start  = (ji.dwButtons & (1u << 9)) != 0;
            st.btn_ls     = (ji.dwButtons & (1u << 10)) != 0;
            st.btn_rs     = (ji.dwButtons & (1u << 11)) != 0;
            st.btn_guide  = (ji.dwButtons & (1u << 12)) != 0;
            st.right_stick_x =  norm_signed(ji.dwZpos, has_caps ? caps.wZmin : 0u, has_caps ? caps.wZmax : 65535u);
            st.right_stick_y = -norm_signed(ji.dwRpos, has_caps ? caps.wRmin : 0u, has_caps ? caps.wRmax : 65535u);
            st.left_trigger  = norm_trig(ji.dwUpos, has_caps ? caps.wUmin : 0u, has_caps ? caps.wUmax : 65535u);
            st.right_trigger = norm_trig(ji.dwVpos, has_caps ? caps.wVmin : 0u, has_caps ? caps.wVmax : 65535u);
        } else {
            st.btn_a      = (ji.dwButtons & (1u << 0)) != 0;
            st.btn_b      = (ji.dwButtons & (1u << 1)) != 0;
            st.btn_x      = (ji.dwButtons & (1u << 2)) != 0;
            st.btn_y      = (ji.dwButtons & (1u << 3)) != 0;
            st.btn_lb     = (ji.dwButtons & (1u << 4)) != 0;
            st.btn_rb     = (ji.dwButtons & (1u << 5)) != 0;
            st.btn_back   = (ji.dwButtons & (1u << 6)) != 0;
            st.btn_start  = (ji.dwButtons & (1u << 7)) != 0;
            st.btn_ls     = (ji.dwButtons & (1u << 8)) != 0;
            st.btn_rs     = (ji.dwButtons & (1u << 9)) != 0;
            st.btn_guide  = (ji.dwButtons & (1u << 10)) != 0 || (ji.dwButtons & (1u << 12)) != 0;
            st.right_stick_x =  norm_signed(ji.dwUpos, has_caps ? caps.wUmin : 0u, has_caps ? caps.wUmax : 65535u);
            st.right_stick_y = -norm_signed(ji.dwVpos, has_caps ? caps.wVmin : 0u, has_caps ? caps.wVmax : 65535u);
        }
        decode_pov_hat(ji.dwPOV, st);
        return true;
    }
    return false;
}

} // namespace
#endif // _WIN32

static bool is_our_process_foreground() {
#ifdef _WIN32
    HWND fg = GetForegroundWindow();
    if (!fg) return true;
    DWORD pid = 0;
    GetWindowThreadProcessId(fg, &pid);
    return pid == GetCurrentProcessId();
#else
    return false;
#endif
}

static bool eval_xbox_input_source(const XboxInputState& xstate, int src, float trig_thresh) {
    switch (static_cast<XboxInputSource>(src)) {
        case XboxInputSource::BtnA:      return xstate.btn_a;
        case XboxInputSource::BtnB:      return xstate.btn_b;
        case XboxInputSource::BtnX:      return xstate.btn_x;
        case XboxInputSource::BtnY:      return xstate.btn_y;
        case XboxInputSource::BtnLB:     return xstate.btn_lb;
        case XboxInputSource::BtnRB:     return xstate.btn_rb;
        case XboxInputSource::TriggerLT: return xstate.left_trigger  >= trig_thresh;
        case XboxInputSource::TriggerRT: return xstate.right_trigger >= trig_thresh;
        case XboxInputSource::BtnBack:   return xstate.btn_back;
        case XboxInputSource::BtnStart:  return xstate.btn_start;
        case XboxInputSource::BtnGuide:  return xstate.btn_guide;
        case XboxInputSource::BtnLStick: return xstate.btn_ls;
        case XboxInputSource::BtnRStick: return xstate.btn_rs;
        case XboxInputSource::DpadUp:    return xstate.dpad_up;
        case XboxInputSource::DpadDown:  return xstate.dpad_down;
        case XboxInputSource::DpadLeft:  return xstate.dpad_left;
        case XboxInputSource::DpadRight: return xstate.dpad_right;
        case XboxInputSource::None:
        default:                         return false;
    }
}

static float analog_trigger_for_source(const XboxInputState& xstate, int src, bool active) {
    if (static_cast<XboxInputSource>(src) == XboxInputSource::TriggerLT) {
        return std::clamp(xstate.left_trigger, 0.0f, 1.0f);
    }
    if (static_cast<XboxInputSource>(src) == XboxInputSource::TriggerRT) {
        return std::clamp(xstate.right_trigger, 0.0f, 1.0f);
    }
    return active ? 1.0f : 0.0f;
}

static void apply_pc_keyboard_to_gc_pad(GcPadStatus& pad) {
#ifdef _WIN32
    if (!is_our_process_foreground()) return;
    auto key = [](int vk) -> bool { return (GetAsyncKeyState(vk) & 0x8000) != 0; };

    if (key(VK_RETURN) || key(VK_ESCAPE)) pad.button |= PAD_BUTTON_START;
    if (key('Z') || key(VK_SPACE))        pad.button |= PAD_BUTTON_A;
    if (key('X') || key(VK_LSHIFT))       pad.button |= PAD_BUTTON_B;
    if (key('C') || key('H'))             pad.button |= PAD_BUTTON_X;
    if (key('V') || key('Y'))             pad.button |= PAD_BUTTON_Y;
    if (key('Q') || key('1')) { pad.button |= PAD_TRIGGER_L; pad.triggerLeft  = 255; }
    if (key('E') || key('3')) { pad.button |= PAD_TRIGGER_R; pad.triggerRight = 255; }
    if (key(VK_TAB) || key('R'))          pad.button |= PAD_TRIGGER_Z;

    if (key(VK_UP))    pad.button |= PAD_BUTTON_UP;
    if (key(VK_DOWN))  pad.button |= PAD_BUTTON_DOWN;
    if (key(VK_LEFT))  pad.button |= PAD_BUTTON_LEFT;
    if (key(VK_RIGHT)) pad.button |= PAD_BUTTON_RIGHT;

    int sx = static_cast<int>(pad.stickX);
    int sy = static_cast<int>(pad.stickY);
    if (key('A')) sx -= 100;
    if (key('D')) sx += 100;
    if (key('W')) sy += 100;
    if (key('S')) sy -= 100;
    pad.stickX = static_cast<int8_t>(std::clamp(sx, -100, 100));
    pad.stickY = static_cast<int8_t>(std::clamp(sy, -100, 100));

    int cx = static_cast<int>(pad.substickX);
    int cy = static_cast<int>(pad.substickY);
    if (key('J')) cx -= 100;
    if (key('L')) cx += 100;
    if (key('I')) cy += 100;
    if (key('K')) cy -= 100;
    pad.substickX = static_cast<int8_t>(std::clamp(cx, -100, 100));
    pad.substickY = static_cast<int8_t>(std::clamp(cy, -100, 100));
#else
    (void)pad;
#endif
}

XboxInputState PadXInputBridge::poll_any_controller(const RuntimeConfig& cfg, std::string* out_backend) {
    XboxInputState st;
    if (!cfg.enable_xinput) {
        if (out_backend) *out_backend = "Disabled";
        return st;
    }
#ifdef _WIN32
    std::lock_guard<std::mutex> lock(g_pad_backend_mutex);
    if (SDL2Api::instance().poll(cfg.controller_index, st)) {
        if (out_backend) *out_backend = "SDL2";
        return st;
    }
    if (XInputDynamic::instance().poll(cfg.controller_index, st)) {
        if (out_backend) *out_backend = "XInput";
        return st;
    }
    bool is_sony = false;
    if (DInputDynamic::instance().poll(cfg.controller_index, st, is_sony)) {
        if (out_backend) *out_backend = is_sony ? "DirectInput (DS4/PS)" : "DirectInput8";
        return st;
    }
    if (poll_winmm_joystick(cfg.controller_index, st, is_sony)) {
        if (out_backend) *out_backend = is_sony ? "WinMM (DS4/PS)" : "WinMM";
        return st;
    }
#else
    (void)cfg;
#endif
    if (out_backend) *out_backend = "Keyboard";
    return st;
}

void PadXInputBridge::set_any_controller_rumble(const RuntimeConfig& cfg, float strength) {
#ifdef _WIN32
    if (!cfg.enable_xinput) return;
    std::lock_guard<std::mutex> lock(g_pad_backend_mutex);
    const float scaled = cfg.enable_vibration ? std::clamp(strength * cfg.vibration_strength, 0.0f, 1.0f) : 0.0f;
    SDL2Api::instance().rumble(scaled);
    XInputDynamic::instance().rumble(cfg.controller_index, scaled);
#else
    (void)cfg; (void)strength;
#endif
}

XboxInputState PadXInputBridge::poll_xbox_controller() const {
    return poll_any_controller(cfg_);
}

GcPadStatus PadXInputBridge::translate_to_gc_pad(const XboxInputState& xstate) const {
    GcPadStatus pad{};
    if (!xstate.connected) {
        pad.err = -1;
        return pad;
    }
    pad.err = 0;

    uint16_t btns = 0;
    if (xstate.dpad_left)  btns |= PAD_BUTTON_LEFT;
    if (xstate.dpad_right) btns |= PAD_BUTTON_RIGHT;
    if (xstate.dpad_down)  btns |= PAD_BUTTON_DOWN;
    if (xstate.dpad_up)    btns |= PAD_BUTTON_UP;

    const float th = cfg_.trigger_threshold;
    const bool gc_a     = eval_xbox_input_source(xstate, cfg_.bind_gc_a, th);
    const bool gc_b     = eval_xbox_input_source(xstate, cfg_.bind_gc_b, th);
    const bool gc_x     = eval_xbox_input_source(xstate, cfg_.bind_gc_x, th);
    const bool gc_y     = eval_xbox_input_source(xstate, cfg_.bind_gc_y, th);
    const bool gc_l     = eval_xbox_input_source(xstate, cfg_.bind_gc_l, th);
    const bool gc_r     = eval_xbox_input_source(xstate, cfg_.bind_gc_r, th);
    const bool gc_z     = eval_xbox_input_source(xstate, cfg_.bind_gc_z, th);
    const bool gc_start = eval_xbox_input_source(xstate, cfg_.bind_gc_start, th);

    if (gc_a)     btns |= PAD_BUTTON_A;
    if (gc_b)     btns |= PAD_BUTTON_B;
    if (gc_x)     btns |= PAD_BUTTON_X;
    if (gc_y)     btns |= PAD_BUTTON_Y;
    if (gc_z)     btns |= PAD_TRIGGER_Z;
    if (gc_start) btns |= PAD_BUTTON_START;

    // Preserve secondary View(Back)->Z convenience when View/Back isn't assigned to another slot
    const int kBackSrc = static_cast<int>(XboxInputSource::BtnBack);
    if (cfg_.bind_gc_z == static_cast<int>(XboxInputSource::BtnRB) &&
        cfg_.bind_gc_a != kBackSrc && cfg_.bind_gc_b != kBackSrc &&
        cfg_.bind_gc_x != kBackSrc && cfg_.bind_gc_y != kBackSrc &&
        cfg_.bind_gc_l != kBackSrc && cfg_.bind_gc_r != kBackSrc &&
        cfg_.bind_gc_start != kBackSrc && xstate.btn_back) {
        btns |= PAD_TRIGGER_Z;
    }

    float lt = analog_trigger_for_source(xstate, cfg_.bind_gc_l, gc_l);
    float rt = analog_trigger_for_source(xstate, cfg_.bind_gc_r, gc_r);
    if (gc_l && lt < th) lt = 1.0f;
    if (gc_r && rt < th) rt = 1.0f;

    // Dedicated Center Xbox [X] (Guide / Nexus) button target
    if (xstate.btn_guide) {
        switch (static_cast<GuideActionTarget>(cfg_.bind_guide_target)) {
            case GuideActionTarget::GcStart: btns |= PAD_BUTTON_START; break;
            case GuideActionTarget::GcZ:     btns |= PAD_TRIGGER_Z;    break;
            case GuideActionTarget::GcY:     btns |= PAD_BUTTON_Y;     break;
            case GuideActionTarget::GcX:     btns |= PAD_BUTTON_X;     break;
            case GuideActionTarget::GcL:     btns |= PAD_TRIGGER_L; lt = 1.0f; break;
            case GuideActionTarget::GcR:     btns |= PAD_TRIGGER_R; rt = 1.0f; break;
            case GuideActionTarget::GcA:     btns |= PAD_BUTTON_A;     break;
            case GuideActionTarget::GcB:     btns |= PAD_BUTTON_B;     break;
            case GuideActionTarget::Disabled:
            default: break;
        }
    }

    pad.triggerLeft  = static_cast<uint8_t>(std::round(lt * 255.0f));
    pad.triggerRight = static_cast<uint8_t>(std::round(rt * 255.0f));
    if (gc_l || lt >= th) btns |= PAD_TRIGGER_L;
    if (gc_r || rt >= th) btns |= PAD_TRIGGER_R;

    pad.button    = btns;
    pad.stickX    = apply_deadzone_and_clamp(xstate.left_stick_x, cfg_.left_stick_deadzone);
    pad.stickY    = apply_deadzone_and_clamp(xstate.left_stick_y, cfg_.left_stick_deadzone);
    pad.substickX = apply_deadzone_and_clamp(xstate.right_stick_x, cfg_.right_stick_deadzone);
    pad.substickY = apply_deadzone_and_clamp(xstate.right_stick_y, cfg_.right_stick_deadzone);
    return pad;
}

void PadXInputBridge::write_pad_status_to_addr(Memory& mem, uint32_t dest_vaddr, const XboxInputState* override_state) {
    if (!mem.is_valid_range(dest_vaddr, 48u)) return;
    const XboxInputState* eff_ov = override_state ? override_state : active_override_;
    XboxInputState xst = eff_ov ? *eff_ov : poll_xbox_controller();
    GcPadStatus pad0 = translate_to_gc_pad(xst);
    if (!eff_ov) {
        apply_pc_keyboard_to_gc_pad(pad0);
        // Keep GC Channel 0 connected via keyboard fallback even without physical gamepad hardware.
        if (pad0.err != 0) pad0.err = 0;
    }

    mem.write_u16(dest_vaddr + 0, pad0.button);
    mem.write_u8(dest_vaddr + 2, static_cast<uint8_t>(pad0.stickX));
    mem.write_u8(dest_vaddr + 3, static_cast<uint8_t>(pad0.stickY));
    mem.write_u8(dest_vaddr + 4, static_cast<uint8_t>(pad0.substickX));
    mem.write_u8(dest_vaddr + 5, static_cast<uint8_t>(pad0.substickY));
    mem.write_u8(dest_vaddr + 6, pad0.triggerLeft);
    mem.write_u8(dest_vaddr + 7, pad0.triggerRight);
    mem.write_u8(dest_vaddr + 8, pad0.analogA);
    mem.write_u8(dest_vaddr + 9, pad0.analogB);
    mem.write_u8(dest_vaddr + 10, static_cast<uint8_t>(pad0.err));
    mem.write_u8(dest_vaddr + 11, 0);

    for (uint32_t ch = 1; ch < 4; ++ch) {
        uint32_t b = dest_vaddr + ch * 12u;
        mem.write_u32(b + 0, 0u);
        mem.write_u32(b + 4, 0u);
        mem.write_u16(b + 8, 0u);
        mem.write_u8(b + 10, static_cast<uint8_t>(-1)); // PAD_ERR_NO_CONTROLLER
        mem.write_u8(b + 11, 0u);
    }
}

void PadXInputBridge::update_memory_pad_status(Memory& mem, const XboxInputState* override_state) {
    active_override_ = override_state;
    write_pad_status_to_addr(mem, recomp::sym_addr::kPadData, override_state);
    uint16_t btns = mem.read_u16(recomp::sym_addr::kPadData);
    mem.write_u16(recomp::sym_addr::kJoyStruct, btns);
    mem.write_u16(recomp::sym_addr::kKeyStruct, btns);
    mem.write_u32(0x8026E7C0u, 0x80000000u);
}

void PadXInputBridge::set_rumble(uint32_t command, float intensity) {
    rumble_active_ = (cfg_.enable_vibration && command == 1 && intensity > 0.0f);
    set_any_controller_rumble(cfg_, rumble_active_ ? intensity : 0.0f);
}

} // namespace pn03

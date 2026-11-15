#include "pn03_runtime.hpp"
#include <algorithm>
#include <cmath>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
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

static DWORD query_xinput_state_with_guide(DWORD user_index, XINPUT_STATE* out_state) {
#ifdef _WIN32
    using FnXInputGetStateEx = DWORD(WINAPI*)(DWORD, XINPUT_STATE*);
    static FnXInputGetStateEx s_fn_ex = []() -> FnXInputGetStateEx {
        const wchar_t* dlls[] = {L"xinput1_4.dll", L"xinput1_3.dll", L"xinput9_1_0.dll"};
        for (const wchar_t* name : dlls) {
            HMODULE mod = LoadLibraryW(name);
            if (mod) {
                auto p = reinterpret_cast<FnXInputGetStateEx>(GetProcAddress(mod, MAKEINTRESOURCEA(100)));
                if (p) return p;
            }
        }
        return nullptr;
    }();
    if (s_fn_ex) return s_fn_ex(user_index, out_state);
    return XInputGetState(user_index, out_state);
#else
    (void)user_index; (void)out_state;
    return 1167u;
#endif
}

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

XboxInputState PadXInputBridge::poll_xbox_controller() const {
    XboxInputState st;
#ifdef _WIN32
    if (!cfg_.enable_xinput) return st;
    XINPUT_STATE xst{};
    DWORD res = query_xinput_state_with_guide(static_cast<DWORD>(cfg_.controller_index), &xst);
    if (res != ERROR_SUCCESS) {
        st.connected = true;
        return st;
    }
    st.connected  = true;
    WORD w        = xst.Gamepad.wButtons;
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
#endif
    return st;
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
#ifdef _WIN32
    if (!cfg_.enable_xinput) return;
    XINPUT_VIBRATION vib{};
    if (rumble_active_) {
        float scaled = std::clamp(intensity * cfg_.vibration_strength, 0.0f, 1.0f);
        WORD motor = static_cast<WORD>(scaled * 65535.0f);
        vib.wLeftMotorSpeed  = motor;
        vib.wRightMotorSpeed = motor;
    }
    XInputSetState(static_cast<DWORD>(cfg_.controller_index), &vib);
#endif
}

} // namespace pn03

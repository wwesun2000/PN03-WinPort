# P.N.03 (GPNE08) — Windows Native Static Recompilation Port (`pn03-winport`)

[English](README.md) | [简体中文](README.zh-CN.md)

A **native Windows x64 C++20 static recompilation port** and **Dolphin SDK High-Level Emulation (HLE)** runtime for Capcom's Nintendo GameCube third-person shooter ***P.N.03*** (USA `GPNE08`, Rev.00, internal codename `MEKA`).

> **Zero Copyrighted Assets Notice**: This repository contains **zero** copyrighted disc images, `main.dol` binaries, console BIOS/IPL ROMs, or proprietary audio/visual game assets. To play, you must supply your own legally obtained *P.N.03* (`GPNE08`) `.iso` / `.gcm` / `.nkit.iso` image or extracted disc directory (`sys/boot.bin`, `sys/fst.bin`, `files/`).

---

## Key Features & Enhancements

### 1. Native Windows Static Recompilation (No Traditional CPU Emulator)
- **6,353 PowerPC 750CXe Functions Statically Recompiled to C++20**: Game code across 9 modular subsystems (`src/decompiled/subsystems/`) and `Tools.rel` (`src/decompiled/tools_rel_decompiled.cpp`) compiles straight to native x64 machine code via MSVC / CMake.
- **Custom Dolphin SDK HLE**: Implements OS threads/alarms/memory, DVD streaming, ARAM DMA, GX graphics FIFO (`0xCC008000`), PAD controller input, VI video timing, and `CARD*` virtual Memory Card saving (`saves/`).
- **Direct ISO Streaming & `LzsDecode`**: `IsoStreamReader` streams assets on demand from `.iso` / `.gcm` (or extracted disc folders) with bit-exact `.lze` decompression.

### 2. Dual Graphics Backends (Vulkan 1.3 & Direct3D 11) + Visual Enhancements
- **Native Vulkan 1.3 & Direct3D 11**: Choose between **Vulkan 1.3** (`src/runtime/win32_vulkan_host.cpp`) and **Direct3D 11** (`src/runtime/win32_d3d11_host.cpp`) at launch or in the GUI launcher.
- **Native `1x` to `6x` EFB Scaling**: Choose from **Native 480p / 720p / 1080p (`1x Native EFB`)** for integrated GPUs (Intel HD, Steam Deck / Proton) up to **2x–6x (4K)** internal scaling (`internal_scale_factor`).
- **Crisp Anti-Aliasing & Texture Filtering**: Supports **`2x / 4x / 8x MSAA`**, optional **FXAA** post-processing pass, texture cache expansion (`2048` entries), and up to **16x Anisotropic Filtering**.
- **Clean Picture Controls**: Bypasses GameCube `GXSetCopyFilter` 480i deflicker blur (`disable_copy_deflicker`), optionally removes cinema letterbox bars (`remove_cinesco_bars`), adjusts display brightness/gamma (`0.50`–`2.00`), and supports Windowed, Borderless Fullscreen, and Exclusive Fullscreen modes.

### 3. True 16:9 / 21:9 Widescreen + Unstretched 4:3 HUD
- **True Expanded 3D Camera Frustum**: Select **Original (4:3)**, **Widescreen (16:9)**, or **Ultrawide (21:9)** (`aspect_ratio`). Horizontal 3D geometry and FOV expand natively without stretching Vanessa or enemies.
- **Aspect-Locked 2D HUD & Portraits**: 2D menus, battle HUD bars, and communication screens remain cleanly proportioned and centered so UI elements never distort in widescreen.

### 4. Multi-Language Support (All 6 Disc Languages Unlocked) + HD Simplified Chinese (`zh_CN`)
- **All Built-In Languages Unlocked on USA `GPNE08` ISO**: Select **English**, **Japanese (`日本語`)**, **German (`Deutsch`)**, **French (`Français`)**, **Spanish (`Español`)**, or **Italian (`Italiano`)** directly in the launcher using your **USA `GPNE08`** disc — `LocalizationOverlay::resolve_localized_asset_path` automatically unlocks the hidden `/id/spa`, `/id/fra`, `/id/ger`, `/id/ita`, `/id/` (Japanese), and `/etc/*_{s,f,g,i}` assets already bundled inside the USA ISO, alongside external non-destructive **Simplified Chinese (`zh_CN`)** (`assets/locales/zh_CN.json`, 401 verified entries).
- **HD Chinese Overlay & Proper Dialogue Paging**:
  - Hooks `CMesWk::MesWorkTrans` and `CMesWk::FontDraw` to render crisp anti-aliased **Microsoft YaHei** HD UTF-8 text instead of low-res bitmap glyphs.
  - Properly segments multi-page (`0x0004`) communication scripts so only the currently active page renders at a time.
  - Includes CJK width-aware word wrapping (`wrap_comm_text`), kinsoku punctuation rules, and safe comm-box layout clamping (`layout_dialogue`) so dialogue never clips or overlaps character portraits.

### 5. Locked 59.94Hz NTSC Frame Pacing & Audio AX/ADPCM HLE
- **Dolphin-Style Frame Limiter**: High-precision QPC **59.94Hz / 29.97Hz** cadence control (`limit_fps_60`) and VI retrace synchronization prevent gameplay speed-ups on 120Hz/144Hz/240Hz monitors.
- **Native XAudio2 + DSP/ADPCM Mixer**: Features 4-bit GameCube ADPCM decoding & interpolation, `AXPBADPCMLOOP` loop state handling, `SND_STR` ARAM ring-buffer wrapping, and 5ms subframe callback flushing (`flush_pending_hle_callbacks`) for stable BGM and SFX playback.

### 6. Universal Controller Stack (SDL2 / XInput / DirectInput8 / WinMM), Cheat Toggles & Cyber Launcher
- **Cyberpunk Pre-Launch GUI & Reliable Persistence**: Configure resolution, backend (Vulkan 1.3 / D3D11), aspect ratio, MSAA/FXAA, language, cheat toggles, audio volume, and controls visually before booting. Automatically resolves `config/pn03_settings.json` relative to the executable and persists changes immediately on edit, close, or launch (even when launching `PN03_WinPort.exe` directly or via Proton/Wine).
- **Universal Controller Support (Windows & Linux/Proton)**: Automatically cascades across optional **`SDL2.dll`** (drop beside `.exe` if desired), **XInput** (`1.4` / `1.3` / `9.1.0`, scanning slots `0..3` with Guide `[X]` support), **DirectInput 8** (built-in DualShock 4 / DualSense Sony HID + generic HID mapping), and **WinMM** (`joyGetPosEx`), plus Type A/B/C/D presets, custom per-button mapping, analog deadzones, trigger thresholds, and dual-motor rumble.
- **Built-In Opt-In Cheat Toggles (Off by Default)**: Optional launcher switches for **Inf Shield HP**, **Inf Energy / Unlimited Energy Drive**, **9.99M Shop Credits**, and **All 11 Suits + Max Upgrades**.
- **Virtual Memory Card & Rotating Logs**: Automatically saves/loads GameCube Memory Card data under `saves/` and records bounded rotating runtime logs under `logs/`.

---

## Quick Start (Using Precompiled Binaries)

Precompiled Windows x64 binaries are provided in [`release/`](release/):
- `release/PN03_WinPort.exe` — Main Windows port + Cyber Launcher
- `release/pn03_cpp_tests.exe` — C++20 runtime & static recompilation test runner
- `release/Launch_PN03.bat` — Convenience launcher script

### Step-by-Step Usage
1. **Clone or download** this repository on Windows 10/11 (x64).
2. **Place your own *P.N.03* (`GPNE08`) game image** (`.iso`, `.gcm`, or `.nkit.iso`) in the repository root folder (or inside `release/`, or select it via the launcher's Browse button).
3. **Launch the game**:
   - Double-click **`release\Launch_PN03.bat`**, or run from the repository root:
     ```bat
     release\PN03_WinPort.exe
     ```
4. **Configure & Play**:
   - In the Cyber Launcher window, pick your ISO (if not auto-detected), choose **Vulkan 1.3** or **Direct3D 11**, **16:9 Widescreen**, resolution (`1920x1080` or higher), **4x MSAA + FXAA**, and language (**English** / **Simplified Chinese** / etc.), then click **LAUNCH**.

### Useful Command-Line Options
```bat
:: Launch directly with a specific ISO and Vulkan 1.3 backend
release\PN03_WinPort.exe --iso "D:\Games\P.N. 03 (USA).iso" --backend vulkan

:: Launch with Direct3D 11 backend and custom config file
release\PN03_WinPort.exe --backend d3d11 --config config\pn03_settings.json

:: Run headless self-test against your ISO (verifies FST, .ctors, zh_CN, dispatch)
release\PN03_WinPort.exe --self-test --iso "D:\Games\P.N. 03 (USA).iso"

:: Skip launcher GUI and boot straight into the game (with current settings)
release\PN03_WinPort.exe --no-gui --iso "D:\Games\P.N. 03 (USA).iso"
```

Other flags: `--frames N`, `--auto-start`, `--dump-frame <path.bmp>`, `--no-vsync`, `--no-limit`, `--trace`, `--log-level <level>`.

---

## Controls

### Xbox Controller (XInput — Default Type A)
- **Left Stick**: Move Vanessa / Navigate menus
- **A / B / X / Y / LT / RT / RB / Start**: Mapped to GameCube **A / B / X / Y / L / R / Z / Start** (customizable with Type A/B/C/D presets & custom bindings in the launcher)
- **Xbox Guide Button**: Mapped by default to GameCube **Start** (configurable)
- **Rumble**: Dual-motor vibration supported

### PC Keyboard
| Action | Key(s) | GameCube Input |
| :--- | :--- | :--- |
| Move | `W` `A` `S` `D` | Control Stick |
| Camera / C-Stick | `I` `J` `K` `L` | C-Stick |
| D-Pad | `Arrow Keys` | D-Pad |
| Confirm / Shoot / Jump | `Z` or `Space` | `A` |
| Back / Dodge | `X` or `Left Shift` | `B` |
| Barrier / Action | `C` or `H` | `X` |
| Energy Drive | `V` or `Y` | `Y` |
| Lock-On / Turn Left | `Q` or `1` | `L` Trigger |
| Quick-Turn / Boost | `E` or `3` | `R` Trigger |
| Status / Z | `Tab` or `R` | `Z` |
| Pause / Start | `Enter` or `Esc` | `Start` |
| Force Exit Window | `Shift + Esc` or `Alt + F4` | Window Close |

---

## Building from Source (Windows)

### Requirements
- Windows 10 / 11 (x64)
- **Visual Studio 2022** (or Build Tools 2022 with C++20 desktop workload)
- **CMake 3.20+** (optional; `scripts\build_windows_port.bat` automatically falls back to direct `cl.exe` + `link.exe` using `vcvars64.bat` if `cmake` is not on `PATH`)
- **Python 3.10+** (optional, for running `tests\test_pn03_suite.py` and dictionary checks)

### Build & Verify
```bat
:: 1. Build Release binaries -> build\Release\PN03_WinPort.exe & pn03_cpp_tests.exe
scripts\build_windows_port.bat

:: 2. Run all 28 C++20 runtime & static recompilation unit tests
build\Release\pn03_cpp_tests.exe "D:\Games\P.N. 03 (USA).iso"

:: 3. Verify Simplified Chinese localization dictionary (401 entries)
python tools\pn03_loc_tool.py --verify-dict assets\locales\zh_CN.json

:: 4. Run full Python E2E verification suite (8 tests; requires root .iso/.gcm)
python tests\test_pn03_suite.py -v
```

---

## Repository Structure

```text
.
├── release/                     # Precompiled Windows x64 executables & Launch_PN03.bat
├── config/
│   └── pn03_settings.json       # Default launcher & engine settings
├── assets/
│   ├── locales/zh_CN.json       # External Simplified Chinese translation dictionary (401 entries)
│   └── ui/                      # Launcher UI assets (no copyrighted game binaries)
├── include/                     # C++20 headers (PPC context, GX, Vulkan/D3D11, Audio, Config)
├── src/
│   ├── launcher/                # Main entry point & Win32 Cyber Launcher GUI
│   ├── runtime/                 # Dolphin SDK HLE, Vulkan 1.3, D3D11, XAudio2, XInput, zh_CN overlay
│   └── decompiled/              # Statically recompiled subsystems (6,353 functions + Tools.rel)
├── re_data/                     # Symbol, FST, vtable, REL & BNR JSON metadata manifests
├── tools/                       # Static lifting scripts, shader generator & localization validator
├── scripts/                     # Build & Ghidra headless helper scripts
└── tests/                       # C++20 (28 tests) & Python E2E (8 tests) verification suites
```

---

## Why `PN03-WinPort` vs Traditional Emulators?

| Feature | `PN03-WinPort` (Native Static Recompilation) | Generic GameCube Emulator |
| :--- | :--- | :--- |
| **Execution** | 6,353 PowerPC functions compiled natively to x64 C++20 | Dynamic JIT translation + emulator shell overhead |
| **Graphics API** | Native **Vulkan 1.3** & **Direct3D 11** tailored specifically for P.N.03 GX | General-purpose multi-game backend |
| **Widescreen** | Native 3D frustum widening + aspect-locked unstretched 2D HUD/portraits | Per-game Gecko/AR hacks that often stretch UI or cull side geometry |
| **HD Chinese (`zh_CN`)** | Built-in non-destructive Microsoft YaHei HD overlay + `0x0004` paging & line wrap | Requires external texture packs or modified ISOs |
| **Setup** | Prebuilt standalone Win64 `.exe` + Cyber Launcher + auto ISO scan | Requires full emulator installation & manual per-game tuning |

---

## Troubleshooting & FAQ

- **"No ISO or extracted sys/ path configured"**: Place your `P.N.03` (`GPNE08`) `.iso` / `.gcm` / `.nkit.iso` in the repository root (or inside `release/`), or click **Browse** in the Cyber Launcher.
- **"Unsupported Game ID: GPNP08" / Playing in Spanish / Euro Languages / Japanese**: Because all 6,353 statically recompiled functions bind to the USA `GPNE08` `main.dol` memory map, European PAL (`GPNP08`) discs are not directly compatible. However, your **USA `GPNE08` ISO already contains full Spanish, French, German, Italian, English, and Japanese assets** — simply pick your preferred language in the Cyber Launcher (`Español (/id/spa)`, etc.) with a `GPNE08` ISO!
- **Playing on Integrated GPUs / Linux Proton**: Select **`1280x720 HD (1x Native EFB - iGPU)`** or **`640x480 480p (1x Native EFB - Fastest)`** with AA `Off` or `FXAA` for smoother outdoor framerates. DualShock 4 and generic controllers are supported automatically via DirectInput8/WinMM or by placing an optional Windows x64 `SDL2.dll` next to `PN03_WinPort.exe`.
- **Vulkan launch fails on older GPU drivers**: Switch the Graphics Backend in the Cyber Launcher to **Direct3D 11**, or run `release\PN03_WinPort.exe --backend d3d11`.
- **Save files location**: Virtual GameCube Memory Card saves are stored automatically inside `saves/` (`pn03_card_a.sav` etc.).
- **Runtime diagnostics**: Logs rotate automatically inside `logs/` (`pn03_runtime.log`) with bounded disk usage.

---

## Disclaimer

This project is an independent clean-room technical study and static recompilation port. All trademarks and game copyrights belong to Capcom Co., Ltd. No copyrighted Nintendo or Capcom ROMs, ISOs, or BIOS files are distributed in this repository.

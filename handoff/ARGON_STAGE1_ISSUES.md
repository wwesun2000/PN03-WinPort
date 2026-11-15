# P.N.03 (GPNE08 / MEKA) — Stage 1 Local Build Report & Web-Argon Problem Handoff

## 1. Local Environment Status (VERIFIED ON WINDOWS x64)
- **ISO / ELF / UI Assets**:
  - Auto-detected GameCube disc image in root: `P.N. 03 (USA).nkit.iso` (`GPNE08`, 700 FST files, `main.dol` offset `0x0001EC00`, `fst_off=0x001A3C00`, `Tools.rel` 52,492 bytes).
  - Generated symbol-rich 32-bit PowerPC ELF: `build/pn03_main_with_syms.elf` (`tools/dol_to_elf.py`, 8,221 symbols).
  - Decoded `opening.bnr` (96x32 RGB5A3) to `assets/ui/pn03_banner_96x32.bmp` and `assets/ui/pn03_icon_32x32.bmp` (`tools/extract_banner_icon.py`), integrated into Win32 launcher & D3D11 window icon.
- **Native MSVC x64 Compilation & Linking**:
  - Compiled all 9 lifted subsystems (`src/decompiled/subsystems/subsys_01..09.cpp`, 6,246 `main.dol` functions), `tools_rel_decompiled.cpp` (94 functions), `indirect_call_table.cpp` (6,340 entries), `function_table_registry.cpp`, runtime, launcher, and tests cleanly with MSVC `cl.exe` (`14.44.35207` x64, `/std:c++20 /utf-8 /bigobj`).
  - Added `__builtin_clz` MSVC shim (`std::countl_zero`) in `include/pn03_ppc_context.hpp`, `NOMINMAX` guard in `src/runtime/audio_ax_hle.cpp`, safe DXGI 1x/WARP fallback + `WM_CLOSE` handling in `src/runtime/win32_d3d11_host.cpp`, UTF-16 language combo + full UI state save in `src/launcher/win32_cyber_launcher.cpp`, `--self-test` / `--no-gui` CLI flags in `src/launcher/launcher_main.cpp`, and direct `cl.exe`/`link.exe` fallback in `scripts/build_windows_port.bat`.
  - REA PE import check (`rea_rea::inspect_pe_imports`) confirmed `build/Release/PN03_WinPort.exe` (`pe32-plus`, `amd64`, 7 DLLs, 143 imports: `XINPUT1_4.dll`, `d3d11.dll`, `ole32.dll`, `COMDLG32.dll`, `USER32.dll`, `GDI32.dll`, `KERNEL32.dll`).
- **Verification Results**:
  - `build/Release/pn03_cpp_tests.exe`: **8/8 PASSED**.
  - `build/Release/PN03_WinPort.exe --self-test`: **PASSED** (GPNE08, 700 FST entries, `opening.bnr`, `zh_CN` 58 entries, `dispatch_recompiled_function(0x8009C58C)`).
  - `build/Release/PN03_WinPort.exe --no-gui --frames 10` (`live` mode): **PASSED** (10 HD frames at 1920x1080).
  - `unittest discover -s tests -p "test_*.py"`: **4/4 OK**.
- **Localization Reverse Engineering Fix**:
  - Discovered Capcom `.dat` containers (`[u32 chunk_count, u32 offsets...]`) store TPL textures (`0x0020AF30`), layout tables (`0x12280000`), and **16-bit glyph-indexed text chunks (`0xF05ADF3E`)**. Updated `tools/pn03_loc_tool.py` (`inspect`, `export-csv`, `import-csv`, `compile-json`, placeholder checks), cleanly extracting **275 real messages** from `/id/eng/*.dat` (vs 30,165 binary noise matches previously) into `assets/locales/zh_CN_translation_sheet.csv` (333 rows total).

---

## 2. Unresolved Technical Problems for Web Argon (5 Workstreams)

Notice this repository compiles and passes synthetic/unit checks, **but does NOT yet execute the real P.N.03 game loop or render 3D frames from lifted PPC code**. Please help implement the following 5 modules/fixes cleanly (respecting `.antigravity/rules.md`: zero copyrighted binary files, preserve locked module APIs):

### Workstream A [CRITICAL]: Lift & Emulate the 791 Silent-No-Op `exec_raw` Instructions
- **Where**: `tools/extract_and_decompile.py`, `include/pn03_ppc_context.hpp` (lines 330-343), `handoff/exec_raw_inventory.json`.
- **Root Cause**:
  - Across `src/decompiled/subsystems/subsys_02..09.cpp` and `tools_rel_decompiled.cpp`, **791 instructions** fell back to `ctx.exec_raw(pc, insn)`.
  - `PPCContext::exec_raw` ONLY implements primary opcodes `20, 21, 23` (`rlwimi`, `rlwinm`, `rlwnm`). Every single one of the **791 `exec_raw` calls** is currently a **silent no-op**!
- **Observed Opcode Breakdown (from `handoff/exec_raw_inventory.json`)**:
  - `op=4, xo=28` (213 sites): Gekko Paired-Single `ps_msub`
  - `op=4, xo=30` (133 sites): Gekko Paired-Single `ps_nmadd`
  - `op=31, xo=284` (94 sites): `eqv`
  - `op=31, xo=202` (81 sites): `addze`
  - `op=31, xo=83` (28 sites) & `xo=146` (21 sites): `mfmsr` / `mtmsr` (critical sections & OS interrupt masking!)
  - `op=31, xo=598` (26 sites) & `op=19, xo=50` (13 sites): `sync` / `rfi`
  - `op=31, xo=983` (26 sites): `stfiwx` (float-to-int store — heavily used in GC math/rendering!)
  - `op=31, xo=343` (21 sites): `lhax`
  - `op=63, xo=26` (20 sites): `frsqrte` (inverse sqrt estimate — physics/camera/lighting!)
  - `op=31, xo=1014` (14 sites): **`dcbz`** (clears 32-byte RAM cacheline to zero; skipping this leaves structs uninitialized!)
  - `op=31, xo=55` (12 sites) & `xo=183` (8 sites): `lwzux` / `stwux`
- **Deliverable**: Implement ALL missing opcodes in `PPCContext::exec_raw` (immediate fix) AND add clean C++ lifting in `tools/extract_and_decompile.py`.

### Workstream B [CRITICAL]: Wire Real Recompiled Boot & Frame Loop in `src/launcher/launcher_main.cpp`
- **Where**: `src/launcher/launcher_main.cpp`, `src/decompiled_hl/main_hl.cpp`, `src/runtime/dolphin_sdk_hle.cpp`, `src/runtime/iso_reader.cpp`.
- **Root Cause**:
  - Currently `WinPortApplication::run_frames()` runs a synthetic loop (`begin_frame`, `update_memory_pad_status`, increments `pG + 29184`, `mix_stereo_frame`) and never invokes `main_8009C4DC` (`main.obj`), `__main` (`0x800ED768` / `.ctors`), `systemStartInit` (`0x8009C5B8`), `systemRestartInit` (`0x8009C65C`), `TaskExec(0, &Title_task)` (`0x800A1B08`), or the per-frame `Scheduler` (`0x800A18E4`) / `Render` (`0x800D9D10`) / `Trans` (`0x800D91CC`) pipeline seen in `src/decompiled_hl/main_hl.cpp`.
- **Specific Challenges to Solve**:
  1. `main` (`0x8009C4DC`) contains an infinite `while` loop (`label_8009C510`). On Windows we must pump Win32 messages & yield on `VIWaitForRetrace` / `Render_done` (`0x8009D3CC`) or break `main()` into `(init_once + step_one_frame)` so the D3D11 event loop stays responsive at 60 FPS.
  2. Wire HLE callbacks: `VISetPostRetraceCallback` (`postVSyncCallback` @ `0x8009C58C`), `DVDOpen` / `DVDReadPrio` / async callbacks inside `dolphin_sdk_hle.cpp` backed directly by the open `IsoStreamReader`!
  3. Wire XInput pad state (`pad_xinput.cpp`) into the exact RAM addresses read by `PadRead` (`0x800ACC2C`, inspect `src/decompiled_hl/pad_hl.cpp` & `re_data/meka_symbols_full.json`).

### Workstream C [CRITICAL]: Connect `GX3DInterface` Capture to Real Direct3D 11 Draw Calls, Textures & Shaders
- **Where**: `src/runtime/gx_3d_interface.cpp`, `include/pn03_gx_3d_interface.hpp`, `src/runtime/win32_d3d11_host.cpp`.
- **Root Cause**:
  - `Win32D3D11Host` defines HLSL source strings (`kGxTevHlsl`, `kFxaaPostHlsl`), but **never compiles them (`D3DCompile`)** and **never creates input layouts, vertex/index buffers, constant buffers, depth-stencil buffers, or texture SRVs**; `begin_d3d11_frame` only clears the backbuffer and presents a solid color.
  - Meanwhile, `GX3DInterface` (`src/runtime/gx_3d_interface.cpp`) parses GX matrix/viewport/blend/TEV calls and accumulates vertices via `GXBegin`, without emitting typed draw batches to D3D11 or decoding GameCube textures bound by `GXLoadTexObj`.
- **Deliverable**:
  1. Complete `GX3DInterface` vertex attribute decoding (`GXVtxFmt` / `GXPosition*`, `GXNormal*`, `GXColor*`, `GXTexCoord*`) + GX FIFO/DisplayList execution (`GXCallDisplayList`).
  2. Decode bound GameCube texture formats (`I4`, `I8`, `IA4`, `IA8`, `RGB565`, `RGB5A3`, `RGBA8`, `CMPR/DXT1`, CI4/CI8 with TLUT `tlut_slots_`) from emulated 24MB RAM into `ID3D11Texture2D` + `ID3D11ShaderResourceView` cache (with 16x AF sampler).
  3. Compile `kGxTevHlsl` (and expand `FXAA` post-pass + MSAA render target) in `Win32D3D11Host`, submit real indexed/non-indexed triangle batches per frame (`Quads -> Triangles` already partially handled).

### Workstream D [HIGH]: Translate Remaining 275 `0xF05ADF3E` ISO Strings & Render HD Chinese Font (`CMesWk`)
- **Where**: `assets/locales/zh_CN_translation_sheet.csv`, `assets/locales/zh_CN.json`, `src/runtime/localization_zh.cpp`, `src/decompiled_hl/mes_hl.cpp`.
- **Context**:
  - `tools/pn03_loc_tool.py` now extracts the **275 authentic English UI/briefing/item messages** stored in `/id/eng/*.dat` (`0xF05ADF3E` UTF-16BE glyph-index chunks).
- **Deliverable**:
  1. Translate the 275 empty `translation_zh_CN` rows in `assets/locales/zh_CN_translation_sheet.csv` into Simplified Chinese (preserving control tags `<0a>`, `<0b>`, `<07>`, `<08>`, `\n`), then import via `python tools/pn03_loc_tool.py import-csv`.
  2. Map `CMesCtrl::MesInit` (`0x8009F0A4`), `CMesCtrl::CreateFont` (`0x8009F384`), and `CMesWk` draw routines in `src/decompiled_hl/mes_hl.cpp` so strings rendered by `CMesCtrl` look up UTF-8 Chinese text via `LocalizationOverlay` and draw crisp HD Chinese glyphs onto D3D11 (using DirectWrite / GDI glyph bitmap upload to dynamic atlas texture, falling back to Windows `Microsoft YaHei UI` if `assets/locales/moji_zh_hd.ttf` is absent).

### Workstream E [MEDIUM]: `.ctors` Initialization & `Tools.rel` Live Overlay Verification
- **Where**: `re_data/vtables_and_ctors.json`, `src/decompiled_hl/main_hl.cpp` (`__main` @ `0x800ED768`), `src/decompiled/tools_rel_decompiled.cpp`.
- **Deliverable**:
  - Verify all 48 global constructors in `.ctors` execute cleanly before `main()`, confirm indirect/virtual calls (`150` vtables in `indirect_call_table.cpp`) resolve without missing entries, and test executing `Tools.rel` `_prolog` when `load_tools_rel_debug` is true.

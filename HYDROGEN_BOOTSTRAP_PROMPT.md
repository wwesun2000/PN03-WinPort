# 本地 Antigravity (Hydrogen) 一步到位启动提示词 (`HYDROGEN_BOOTSTRAP_PROMPT.md`)

将以下提示词直接复制粘贴到本地 Google Antigravity IDE (Hydrogen) 对话框中即可一键完成剩余收尾工作：

```markdown
@workspace 我已将云端 Argon 完成的《P.N.03 (GPNE08) Windows 原生静态重编译与高清汉化工程交接包 v2.2》解压到当前工作区根目录，并且**已将原版《P.N.03 (GPNE08)》的 `.iso` 游戏镜像文件直接放在了当前项目根目录下**。

### 一、阅读顺序与项目背景
请先按顺序阅读根目录下的交接文档：
1. `README.md`（目录清单与快速启动命令）
2. `ARCHITECTURE.md`（系统架构与 Argon 已锁定模块表）
3. `INTERFACE_CONTRACTS.md`（24MB 内存映射、`MEKA.sym` 关键 Hook 地址与 `config/pn03_settings.json` Schema）
4. `HYDROGEN_TASKS.md`（本地执行清单 `LOCAL-01` ~ `LOCAL-04`）

### 二、你可以直接借助和调用的工具矩阵（内置脚本 + 本地外部工具）

#### A. 项目内置逆向、转译与资源工具 (`tools/` & `ghidra_scripts/` & `scripts/`)
1. **`python tools/dol_to_elf.py`（支持自动扫描项目根目录 `.iso`）**：
   - 直接不带参数运行 `python tools/dol_to_elf.py`（或传 `--iso <文件名.iso>`），它会自动扫描项目根目录下的 `.iso`/`.gcm`，校验 `0xC2339F3D` 魔数，直接从 ISO 内部提取 `sys/main.dol`（偏移 `0x0001EC00`）与 `/MEKA.sym`（9,530 个符号），一步合成为含 8,221 个全局符号的标准 32-bit Big-Endian PowerPC ELF (`build/pn03_main_with_syms.elf`)，让 Ghidra 免装任何第三方插件即可直接加载。
2. **`ghidra_scripts/ImportMekaSymAndDecompile.py` + `scripts/run_ghidra_headless.bat`**：
   - 供本地 Ghidra 无头模式（`analyzeHeadless.bat`）调用，自动设置 PowerPC 小数据区基址寄存器 `r13 (_SDA_BASE_) = 0x80275BE0` 与 `r2 (_SDA2_BASE_) = 0x80285BE0`，注入全部 `MEKA.sym` 函数签名，并调用 `DecompInterface` 批量导出 895 个 `.obj` 的 AST 级 C++ 源码至 `src/ghidra_decompiled/`。
3. **`python tools/pn03_loc_tool.py`（ISO 文本提取与汉化词典工具）**：
   - 运行 `python tools/pn03_loc_tool.py --extract-iso <根目录下的.iso> --out assets/locales/zh_CN_template.json` 可直接从项目根目录的 `.iso` 中扫描 `/id/eng/iddata_e.dat`、`lobby_e.dat`、`equip_ck_e.dat`、`trialrank_e.dat` 提取全量英文词条模板；运行 `--verify-dict assets/locales/zh_CN.json` 可校验外置 UTF-8 简体中文词典。
4. **`python tools/extract_and_decompile.py` & `python tools/lift_all_game_units.py` & `python tools/ppc_ast_decompiler.py`**：
   - 已在云端为你生成了 `src/decompiled/subsystems/subsys_01..09.cpp`（`main.dol` 全部 6,246 个函数 100% 零截断 C++20 源码）、`src/decompiled/tools_rel_decompiled.cpp`（`Tools.rel` 94 个重定位函数）、`src/decompiled/indirect_call_table.cpp`（覆盖全部 6,340 个函数的 $O(\log N)$ 二分查找虚函数/间接调用分发器）以及 `src/decompiled_hl/*.cpp`（14 个核心模块的高可读 AST 伪代码）。如需调整转译规则可随时重跑这三个脚本。
5. **`assets/ui/pn03_launcher_ui.html` & `src/launcher/win32_cyber_launcher.cpp`**：
   - 按 Y2K 科幻机甲参考图 1:1 制作的三栏式图形启动配置器（含 Web 交互版与原生 Win32 GUI 弹窗版）。

#### B. 本地外部逆向、编译与图形调试工具（请主动检测并调用）
1. **Ghidra (10.4+ / 11.x) 无头引擎或 REA (`rea-agents`) MCP**：
   - 检测环境变量 `GHIDRA_INSTALL_DIR` 或本地常见路径（如 `C:\ghidra_*`、`D:\ghidra_*`）调用 `support\analyzeHeadless.bat` 导入 `build/pn03_main_with_syms.elf`。
   - 若本地配置了 `rea-agents` MCP（或运行 `npx rea-agents setup`），可直接调用 `open_binary`、`analyze_function`、`pseudocode` 对特定函数进行深度交互式反编译。
2. **CMake (3.20+) + Visual Studio 2022 (MSVC / Clang-CL) + Windows SDK**：
   - 调用 `scripts/build_windows_port.bat` 或 `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release --parallel`，自动编译全部 6,340 个重编译函数并与 `d3d11.lib`、`dxgi.lib`、`xinput.lib`、`xaudio2.lib` 链接生成 `PN03_WinPort.exe` 和 `pn03_cpp_tests.exe`。
3. **RenderDoc / Visual Studio Graphics Diagnostics / Dolphin Emulator (Debug)**：
   - 在联调 `Win32D3D11Host` 与 `GX3DInterface`（270 个 GX/VI 3D 接口、4K/8xMSAA+FXAA、16:9 宽屏正交修正）时，可借助 RenderDoc 抓取 D3D11 帧，或对照 Dolphin Debug 模式的寄存器状态。

### 三、你的执行指令（一次性连续执行到底）
请不要停顿询问，直接依次执行以下步骤直至全部验收通过：
1. **自动发现根目录 ISO 并合成带符号 ELF (`LOCAL-01`)**：
   - 在当前项目根目录查找 `.iso`/`.gcm` 文件，运行 `python tools/dol_to_elf.py --iso <发现的.iso文件> build/pn03_main_with_syms.elf`。
   - 若本地检测到 Ghidra，运行 `analyzeHeadless` 配合 `ghidra_scripts/ImportMekaSymAndDecompile.py` 导出 Ghidra AST 伪代码至 `src/ghidra_decompiled/`。
   - 运行 `python tools/pn03_loc_tool.py --extract-iso <发现的.iso文件> --out assets/locales/zh_CN_extracted.json` 从 ISO 中提取全量原始英文文本表，并校验 `assets/locales/zh_CN.json`。
2. **编译 Windows 原生可执行程序与测试套件 (`LOCAL-02`)**：
   - 运行 `scripts/build_windows_port.bat`（或 CMake Release 构建）编译生成 `PN03_WinPort.exe` 与 `pn03_cpp_tests.exe`。
3. **运行全量 8 项 C++20 单元测试 (`LOCAL-03`)**：
   - 运行 `pn03_cpp_tests.exe` 确认内存模型、`LzsDecode` 解压、`GX3DInterface` 270 函数路由与 RGB5A3 解码、`AudioAXInterface` ADPCM 解码与 `OSAlloc` 堆、`PadXInputBridge` 手柄映射、`CARD` 存档持久化、6,340 函数间接调用分发与简体中文 Overlay 全部 8/8 通过。
4. **绑定项目根目录下的 ISO 并启动实机运行 (`LOCAL-04`)**：
   - 将 `config/pn03_settings.json` 中的 `"runtime_mode"` 设为 `"live"`，`"iso_path"` 设为项目根目录下的 `.iso` 文件名（主程序本身也已内置自动扫描项目根目录 `.iso` 的逻辑），启动 `PN03_WinPort.exe` 完成实机验收并向我汇报结果。
```

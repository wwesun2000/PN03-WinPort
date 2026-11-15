# 本地 Antigravity (Hydrogen) 收尾任务清单 (`HYDROGEN_TASKS.md`)

> **重要说明**：云端 Argon 已完成 90% 以上的逆向解析（`MEKA.sym` 9,530 符号、`fst.bin` 700 文件、`Tools.rel` 24 段）、全量 3,891 个命名游戏业务函数的 PowerPC-to-C++ 静态转译（`src/decompiled/`）、核心 HLE 运行时（`IsoStreamReader`、`LzsDecode`、`GXHighResRenderer`、`PadXInputBridge`、`LocalizationOverlay`）及 C++/Python 单元测试验证。本地 Hydrogen 只需按顺序执行以下 4 个纯本地任务即可完成编译与交付。

---

## `LOCAL-01`：合成带符号 PowerPC32 ELF 并运行本地 Ghidra Headless 导出 AST 级伪代码

* **前置条件**：本地已安装 Python 3.10+、Java 17/21+ 与 Ghidra 10.4 / 11.x，且已准备好解压后的 `PN03` 核心目录（含 `sys/main.dol` 与 `MEKA.sym`）或完整 `P.N.03.iso`。
* **执行命令**：
  ```bat
  REM 1. 将 main.dol 与 MEKA.sym 合成为标准 PowerPC32 Big-Endian ELF (含 8,221 个全局符号)
  python tools\dol_to_elf.py "<PATH_TO_PN03_DIR>\sys\main.dol" "<PATH_TO_PN03_DIR>\MEKA.sym" "build\pn03_main_with_syms.elf"

  REM 2. 调用 Ghidra 无头模式运行 ImportMekaSymAndDecompile.py 批量导出 AST 级 C++ 源码
  scripts\run_ghidra_headless.bat "<PATH_TO_GHIDRA_DIR>" "<PATH_TO_PN03_DIR>"
  ```
* **验收标准**：`build\pn03_main_with_syms.elf` 生成成功（约 1.93 MB），且 `src\ghidra_decompiled\` 目录下生成按 `.obj` 单元分类的 Ghidra 反编译 `.cpp` 文件。

---

## `LOCAL-02`：使用本地 CMake + MSVC 编译 Windows 原生可执行程序与测试套件

* **前置条件**：Windows 10/11 x64，已安装 Visual Studio 2022（含 C++ 桌面开发工作负载与 Windows SDK）及 CMake 3.20+。
* **执行命令**：
  ```bat
  scripts\build_windows_port.bat
  ```
* **验收标准**：`build\Release\PN03_WinPort.exe` 与 `build\Release\pn03_cpp_tests.exe` 编译成功且零报错。

---

## `LOCAL-03`：运行本地 C++20 与 Python 端到端测试套件

* **执行命令**：
  ```bat
  build\Release\pn03_cpp_tests.exe "<PATH_TO_PN03_DIR>"
  python tools\pn03_loc_tool.py --verify-dict assets\locales\zh_CN.json
  ```
* **验收标准**：`pn03_cpp_tests.exe` 输出 `ALL C++20 RUNTIME & STATIC RECOMPILATION TESTS PASSED (6/6)!`，且 `pn03_loc_tool.py` 校验 `"valid": true`。

---

## `LOCAL-04`：切换 `live` 模式并挂载原版 `P.N.03.iso` 启动验证

* **执行命令**：
  1. 更新 `config/pn03_settings.json` 中的 `"runtime_mode": "live"`，并将 `"iso_path"` 指向本地合法拥有的 `P.N.03 (GPNE08).iso`（或留空以在启动时弹出 Windows 原生文件选择框）。
  2. 运行主程序：
     ```bat
     build\Release\PN03_WinPort.exe --config config\pn03_settings.json
     ```
* **验收标准**：程序成功校验 `GPNE08` 光盘头与 700 个 FST 文件、加载 `main.dol` 与 `module/Tools.rel`、激活 1080p/4K 16:9 宽屏参数、识别 Xbox 手柄输入并输出简体中文汉化文本。

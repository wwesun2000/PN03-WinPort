# P.N.03 (GPNE08) — Windows 原生静态重编译与高清增强移植版 (`pn03-winport`)

[English](README.md) | [简体中文](README.zh-CN.md)

本项目是面向 Capcom GameCube 经典动作射击游戏 ***《P.N.03》（美版 `GPNE08` Rev.00，内部代号 `MEKA`）*** 的 **Windows x64 原生 C++20 静态重编译（Static Recompilation）+ Dolphin SDK 高层模拟（HLE）** 移植工程。

> **合规声明（零版权素材）**：本仓库**不包含任何** `.iso` / `.gcm` 光盘镜像、原版 `main.dol` 二进制、主机 `BIOS/IPL` 固件或任何版权音画素材。游玩时需由用户自行提供合法转储的 *P.N.03*（`GPNE08`）镜像（支持 `.iso`、`.gcm`、未压缩 `.nkit.iso` 或包含 `sys/boot.bin` + `sys/fst.bin` + `files/` 的解包目录）。

---

## 核心优势与特性亮点

### 1. 原生静态重编译引擎（无需传统模拟器实时解释）
- **6,353 个 PowerPC 750CXe 函数全量转译为 C++20**：将主程序 9 大游戏子系统（`src/decompiled/subsystems/`）与调试模块 `Tools.rel`（`src/decompiled/tools_rel_decompiled.cpp`）直接编译为原生 Windows x64 机器码运行。
- **完整 Dolphin SDK HLE 运行时**：内置 OS 线程/定时器/内存管理、DVD 异步读取、ARAM DMA、GX 图形 FIFO（`0xCC008000`）、手柄轮询、VI 场同步与 `CARD*` 虚拟记忆卡存档（保存在 `saves/` 目录）。
- **零拷贝 ISO 流式读取与精准解压**：通过 `IsoStreamReader` 直接按需从原版光盘镜像流式读取文件，并实现位级精确的 `LzsDecode`（`.lze`）实时解压。

### 2. 双现代 3D 图形后端（Vulkan 1.3 + Direct3D 11）与全套画质增强
- **双后端无缝切换**：支持原生 **Vulkan 1.3**（`src/runtime/win32_vulkan_host.cpp`）与 **Direct3D 11**（`src/runtime/win32_d3d11_host.cpp`），可在启动器界面或命令行自由切换。
- **真高清与超采样缩放**：原生支持 `1920x1080`、2K、4K 等高分辨率输出，支持可调内部 EFB 倍率（`internal_scale_factor`）。
- **硬件抗锯齿与纹理增强**：支持 **`2x / 4x / 8x MSAA`** 多重采样抗锯齿 + 可选 **FXAA** 后处理抗锯齿 + 最高 **16x 各向异性过滤**。
- **清透画面调校**：可关闭原版 480i 隔行去闪烁模糊滤波（`disable_copy_deflicker`）、移除电影上下黑边（`remove_cinesco_bars`）、自定义亮度伽马增益（`brightness`: `0.50`–`2.00`），并支持窗口化、无边框全屏与独占全屏。

### 3. 真 16:9 / 21:9 宽屏视场 + 不拉伸 HUD
- **水平真宽屏视场扩展**：支持 **原始 4:3**、**真宽屏 16:9** 与 **超宽屏 21:9**（`aspect_ratio`），直接扩展 3D 透视视锥与相机横向视野，人物、场景与特效**绝不横向拉扁**。
- **UI/HUD 比例锁定与居中**：游戏内血条、菜单、暂停界面与通讯立绘保持原版比例居中显示，兼顾宽屏沉浸感与界面清晰度。

### 4. 多语言支持 + 外置无损高清简体中文汉化（`zh_CN`）
- **多语言切换**：支持原版 **英语**、**日语**、**德语**、**法语**、**西班牙语**、**意大利语**，以及外置无损 **简体中文（`zh_CN`）** 覆盖层（[assets/locales/zh_CN.json](assets/locales/zh_CN.json)，涵盖菜单、战衣、能量驱动及通讯剧情共 401 条校验词条）。
- **高清中文字库与通讯框精修排版**：
  - 通过钩子接管 `CMesWk::MesWorkTrans` 与 `CMesWk::FontDraw`，使用 **Microsoft YaHei（微软雅黑）** 抗锯齿高清矢量位图渲染中文，告别原版点阵模糊字体。
  - **多页剧情严格分页**：精准识别脚本中的 `0x0004` 翻页标记，逐页显示当前对话，不会一次性把后续页面全部堆叠到屏幕上。
  - **自动折行与安全边界防遮挡**：内置中英文宽度感知折行（`wrap_comm_text`）、中文避头尾标点规则与通讯框安全区钳位（`layout_dialogue`），避免右侧文字被裁切或压住角色头像与 `CLIENT >>> VANESSA` 面板。

### 5. 锁定 59.94Hz 帧率节奏 & 原生 XAudio2 / ADPCM 音频修复
- **高刷新率防加速锁帧**：采用 Dolphin 风格高精度 QPC **59.94Hz / 29.97Hz** 锁帧器（`limit_fps_60`）并同步限制 VI 等待计数（`pG+284`），确保在 120Hz/144Hz/240Hz 显示器上游戏动作与节奏维持原汁原味。
- **稳定 BGM/音效流式混音**：基于 Windows **XAudio2** 实现 4-bit GameCube ADPCM 硬件级插值解码、`AXPBADPCMLOOP` 循环状态衔接、`SND_STR` ARAM 环形缓冲即时回绕及每 5ms DSP 子帧回调冲刷（`flush_pending_hle_callbacks`），解决游戏中途长时流式 BGM 停播与音频卡顿问题。

### 6. 原生 Xbox 手柄 / 键鼠操控 & 赛博风格可视化启动器
- **赛博风格启动器（Cyber Launcher）**：开机前可视化调节后端（Vulkan / D3D11）、分辨率、宽屏比例、MSAA/FXAA、语言、音量与按键预设，并自动保存至 `config/pn03_settings.json`。
- **手柄即插即用**：支持 XInput Xbox 手柄（含 Type A/B/C/D 预设、全按键自定义映射、Xbox `[X]` Guide 键映射、死区/扳机阈值调节与双马达震动），同时提供完整 PC 键鼠映射。
- **自动记忆卡存档与滚动日志**：自动维护虚拟记忆卡存档（`saves/`）及体积可控的轮转运行日志（`logs/`）。

---

## 快速上手（直接使用预编译可执行文件）

本仓库 [`release/`](release/) 目录已直接打包编译好的 Windows x64 可执行程序：
- `release/PN03_WinPort.exe` — 主程序与可视化启动器
- `release/pn03_cpp_tests.exe` — C++20 运行时与重编译自检测试程序
- `release/Launch_PN03.bat` — 一键启动脚本

### 使用步骤
1. **下载或克隆仓库** 到 Windows 10 / 11 (x64) 电脑。
2. **放入你自己的 *P.N.03*（`GPNE08`）镜像**：将 `.iso` / `.gcm` / `.nkit.iso` 文件放到仓库根目录（或 `release/` 目录内，或在启动器界面中点击浏览手动选择）。
3. **启动游戏**：
   - 直接双击 **`release\Launch_PN03.bat`**，或在仓库根目录运行：
     ```bat
     release\PN03_WinPort.exe
     ```
4. **配置并进入游戏**：
   - 在弹出的启动器窗口中确认 ISO 路径，选择 **Vulkan 1.3** 或 **Direct3D 11**、**16:9 宽屏**、目标分辨率（如 `1920x1080`）、**4x MSAA + FXAA** 及语言（**简体中文** / **English** / 其他），点击 **LAUNCH** 即可开始游玩。

### 常用命令行参数
```bat
:: 指定 ISO 并以 Vulkan 1.3 后端启动
release\PN03_WinPort.exe --iso "D:\Games\P.N. 03 (USA).iso" --backend vulkan

:: 指定 Direct3D 11 后端与配置文件启动
release\PN03_WinPort.exe --backend d3d11 --config config\pn03_settings.json

:: 跳过启动器 GUI 直接运行游戏
release\PN03_WinPort.exe --no-gui --iso "D:\Games\P.N. 03 (USA).iso"

:: 运行内置自检（校验 FST、静态构造 .ctors、zh_CN 词典及调度器）
release\PN03_WinPort.exe --self-test --iso "D:\Games\P.N. 03 (USA).iso"
```

其他常用参数：`--frames N`、`--auto-start`、`--dump-frame <path.bmp>`、`--no-vsync`、`--no-limit`、`--trace`、`--log-level <level>`。

---

## 操作按键说明

### Xbox 手柄（XInput — 默认 Type A）
- **左摇杆**：移动角色 / 菜单选择
- **A / B / X / Y / LT / RT / RB / Start**：对应 GameCube **A / B / X / Y / L / R / Z / Start**（支持启动器内切换 Type A/B/C/D 或逐键自定义）
- **Xbox 西瓜 Guide 键**：默认映射为 GameCube **Start**（可自定义修改）
- **震动**：支持双马达 XInput 力反馈震动

### 电脑键盘默认映射
| 游戏动作 | 键盘按键 | 对应 GameCube 按键 |
| :--- | :--- | :--- |
| 移动角色 | `W` `A` `S` `D` | 主摇杆 (Control Stick) |
| 视角 / 副摇杆 | `I` `J` `K` `L` | C 摇杆 (C-Stick) |
| 十字方向键 | `方向键 (↑↓←→)` | 十字键 (D-Pad) |
| 确认 / 射击 / 跳跃 | `Z` 或 `Space` | `A` |
| 返回 / 闪避 | `X` 或 `Left Shift` | `B` |
| 护盾 / 特殊动作 | `C` 或 `H` | `X` |
| 必杀能量驱动 (Energy Drive) | `V` 或 `Y` | `Y` |
| 锁定 / 左转 | `Q` 或 `1` | `L` 扳机 |
| 快速转身 / 推进 | `E` 或 `3` | `R` 扳机 |
| 状态栏 / Z 键 | `Tab` 或 `R` | `Z` |
| 暂停 / 菜单 | `Enter` 或 `Esc` | `Start` |
| 强制退出窗口 | `Shift + Esc` 或 `Alt + F4` | 关闭游戏窗口 |

---

## 从源码自行编译（Windows）

### 环境要求
- Windows 10 / 11 (x64)
- **Visual Studio 2022**（或 Build Tools 2022，需安装 C++20 桌面开发工具链）
- **CMake 3.20+**（可选；若未配置 `cmake` 到 `PATH`，`scripts\build_windows_port.bat` 会自动调用 `vcvars64.bat` 使用 `cl.exe` + `link.exe` 直接构建）
- **Python 3.10+**（可选，用于运行 Python 集成测试与词典校验）

### 一键编译与测试验证
```bat
:: 1. 编译 Release 版本 -> 输出到 build\Release\PN03_WinPort.exe 与 pn03_cpp_tests.exe
scripts\build_windows_port.bat

:: 2. 运行全部 27 项 C++20 运行时与重编译单元测试
build\Release\pn03_cpp_tests.exe "D:\Games\P.N. 03 (USA).iso"

:: 3. 校验简体中文汉化词典完整性（401 条翻译）
python tools\pn03_loc_tool.py --verify-dict assets\locales\zh_CN.json

:: 4. 运行 Python 端到端回归测试套件（共 8 项，需在根目录放置镜像）
python tests\test_pn03_suite.py -v
```

---

## 目录结构

```text
.
├── release/                     # 预编译 Windows x64 可执行文件与 Launch_PN03.bat
├── config/
│   └── pn03_settings.json       # 默认启动器与引擎配置文件
├── assets/
│   ├── locales/zh_CN.json       # 外置简体中文汉化词典（401 条校验翻译）
│   └── ui/                      # 启动器 UI 美术素材（不含任何游戏本体资源）
├── include/                     # C++20 核心头文件（PPC 上下文、GX、Vulkan/D3D11、音频、配置）
├── src/
│   ├── launcher/                # 主程序入口与 Win32 赛博启动器界面
│   ├── runtime/                 # Dolphin HLE、Vulkan 1.3、D3D11、XAudio2、XInput、中文覆层
│   └── decompiled/              # 静态重编译 9 大游戏子系统（6,353 个函数 + Tools.rel）
├── re_data/                     # 符号表、FST 文件清单、虚表与 BNR JSON 元数据
├── tools/                       # 静态转译工具、Vulkan Shader 生成器与汉化词典校验脚本
├── scripts/                     # 编译脚本与 Ghidra 辅助脚本
└── tests/                       # C++20（27 项）与 Python（8 项）完整自动化测试套件
```

---

## 相比传统模拟器（如 Dolphin）的优势

| 对比维度 | `PN03-WinPort`（原生静态重编译移植版） | 通用 GameCube 模拟器 |
| :--- | :--- | :--- |
| **运行机制** | 6,353 个 PowerPC 函数静态转译为原生 Windows x64 C++20 机器码 | 实时 JIT 动态翻译 + 完整模拟器框架开销 |
| **图形管线** | 为 *P.N.03* GX 管线深度定制的原生 **Vulkan 1.3** 与 **Direct3D 11** 双后端 | 面向数百款游戏的通用模拟前端 |
| **宽屏体验** | 原生 3D 横向视锥扩展 + 2D HUD / 血条 / 通讯立绘严格锁定原比例不拉伸 | 通用宽屏补丁常导致 UI 拉扁或两侧模型剔除异常 |
| **高清中文汉化** | 外置无损微软雅黑高清覆层 + 精准 `0x0004` 分页 + 智能折行防遮挡 | 需改写 ISO 文件或加载复杂外部纹理包 |
| **开箱即用** | 提供预编译单文件 Win64 `.exe` + 赛博启动器 + 自动扫描当前目录镜像 | 需单独安装模拟器并手动调试各项兼容选项 |

---

## 常见问题（FAQ）

- **提示未找到 ISO 路径**：将你的 *P.N.03*（`GPNE08`）`.iso` / `.gcm` / `.nkit.iso` 文件放到仓库根目录（或 `release/` 目录），也可以直接在启动器窗口点击浏览选择。
- **旧显卡驱动下 Vulkan 启动失败**：在启动器将图形后端切换为 **Direct3D 11**，或命令行加上 `--backend d3d11`。
- **存档保存在哪里**：游戏记忆卡存档自动以虚拟文件形式保存在 `saves/` 目录（如 `pn03_card_a.sav`）。
- **如何排查运行问题**：运行日志自动滚动保存在 `logs/` 目录中，并限制最大文件数与总磁盘占用。

---

## 免责声明

本项目为纯技术学习与干净室静态重编译研究工程。游戏原版商标与版权均归 Capcom Co., Ltd. 所有；本仓库严禁且不会包含任何受版权保护的任天堂或 Capcom ROM、ISO 或 BIOS 文件。

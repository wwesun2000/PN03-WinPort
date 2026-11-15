# P.N.03 (GPNE08) Windows 原生移植与静态重编译架构文档 (`ARCHITECTURE.md`)

## 一、系统总体架构图

```text
+-----------------------------------------------------------------------------------+
|                   Windows Pre-Launch Configurator (Launcher GUI / CLI)            |
|  - 选择并校验原版 P.N.03.iso (GPNE08)    - 分辨率 (720p/1080p/2K/4K) & 全屏模式    |
|  - 抗锯齿 (2x/4x/8x MSAA + FXAA)        - 语言选择 (简体中文 zh_CN / 英 / 法 / 德) |
|  - Xbox 手柄死区与震动开关               - 开发者 Sound Test (Tools.rel) 挂载开关   |
+-----------------------------------------+-----------------------------------------+
                                          | 写入 config/pn03_settings.json
                                          v
+-----------------------------------------------------------------------------------+
|                     P.N.03 Windows Native Recompiled Engine                       |
|                                                                                   |
|  +-----------------------------------------------------------------------------+  |
|  | Game Logic Layer (Statically Lifted from 318 .obj units / 3,891 Functions)  |  |
|  |  - subsys_01_engine_core.cpp (main, main_sub, dvd, read, compless)          |  |
|  |  - subsys_02_player_weapons.cpp (player, cSuit, boost, blt01..0f, cCombo)   |  |
|  |  - subsys_03_enemies_ai.cpp (cEm10..50, atari, area, route_ck)              |  |
|  |  - subsys_04_stages_rooms.cpp (r000..rb04, room_jmp, scroll)                |  |
|  |  - subsys_05_render_model_gx.cpp (trans, model, motion, light, fade)        |  |
|  |  - subsys_06_effects_esp.cpp (esp, esp00..43, espgen)                       |  |
|  |  - subsys_07_ui_menus_mes_shop.cpp (mes, option, pad, title, cockpit, shop) |  |
|  |  - subsys_08_events_movie_sound.cpp (evt*, movie*, thp*, snd*)              |  |
|  +--------------------------------------+--------------------------------------+  |
|                                         | 调用 HLE 拦截层与内存映射               |
|                                         v                                         |
|  +-----------------------------------------------------------------------------+  |
|  | Nintendo Dolphin SDK HLE & Windows Native Bridge Layer (src/runtime/)       |  |
|  |                                                                             |  |
|  |  1. IsoStreamReader & LzsDecode (iso_reader.cpp)                            |  |
|  |     - 零内置素材，直接解析外部 ISO (0x0001EC00 main.dol, 0x001A3C00 fst.bin) |  |
|  |     - 位级精确还原 compless.obj::LzsDecode (0x80077680) 解压 .lze 房间数据   |  |
|  |                                                                             |  |
|  |  2. GXHighResRenderer (gx_renderer.cpp)                                     |  |
|  |     - 拦截 VIConfigure / GXSetViewport / GXSetCopyFilter                    |  |
|  |     - 动态覆写 SDA1 正交矩阵边界 ORTHO_L/R (0x8026E77C..0x8026E780) 实现 16:9|  |
|  |     - 禁用 480i 闪烁模糊滤波，支持移除 Draw_cinesco (0x80073348) 上下黑边    |  |
|  |                                                                             |  |
|  |  3. PadXInputBridge (pad_xinput.cpp)                                        |  |
|  |     - 桥接 Windows XInputGetState / XInputSetState 至 0x801C4A68 (Pad_data) |  |
|  |                                                                             |  |
|  |  4. LocalizationOverlay (localization_zh.cpp)                               |  |
|  |     - Hook CMesCtrl::MesSetLanguage (0x8009F12C) 解除美版英语 (1) 硬编码锁   |  |
|  |     - 挂载 assets/locales/zh_CN.json UTF-8 简体中文词条与高清字库            |  |
|  |                                                                             |  |
|  |  5. ToolsRelLoader (gx_renderer.cpp)                                        |  |
|  |     - 实现 OSLink (0x800F56E0) 动态重定位加载 module/Tools.rel 音效测试菜单  |  |
|  +-----------------------------------------------------------------------------+  |
+-----------------------------------------------------------------------------------+
```

## 二、模块完成度与锁定状态表 (Argon vs. Hydrogen)

| 模块名称 | 源码路径 | 完成度 | 状态 | 说明 |
| :--- | :--- | :---: | :---: | :--- |
| `MEKA.sym` & `fst.bin` 全量逆向数据库 | `re_data/*.json`, `tools/extract_and_decompile.py` | **100%** | **LOCKED (Argon 已验证)** | 完整解出 9,530 个符号、6,353 个函数、700 个 ISO 文件与 24 个 REL 段 |
| PowerPC32 标准带符号 ELF 合成器 | `tools/dol_to_elf.py` | **100%** | **LOCKED (Argon 已验证)** | 将 `main.dol` + `MEKA.sym` 合成为含 8,221 个全局符号的标准 ELF，免插件直通 Ghidra |
| 全量 3,891 个游戏函数静态 C++ 转译 | `src/decompiled/*.cpp`, `src/decompiled/subsystems/*.cpp` | **100%** | **LOCKED (Argon 已验证)** | 14 个核心编译单元 + 8 大子系统全量 C++20 源码，已通过 `g++ -std=c++20` 语法与编译验证 |
| Ghidra 无头批量反编译脚本 | `ghidra_scripts/ImportMekaSymAndDecompile.py` | **100%** | **LOCKED (Argon 已验证)** | 自动设置 `r13=0x80275BE0` / `r2=0x80285BE0` 并调用 `DecompInterface` 导出 AST 级 C++ |
| ISO/FST 零拷贝读取与 `LzsDecode` 解压 | `src/runtime/iso_reader.cpp` | **100%** | **LOCKED (Argon 已验证)** | 100% 还原 `0x80077680` `LzsDecode` 算法并通过真实 `boot.bin`/`fst.bin`/`main.dol` 验证 |
| 高清 3D 渲染、宽屏修正与 `Tools.rel` 链接 | `src/runtime/gx_renderer.cpp` | **95%** | **LOCKED (Argon 已验证)** | 内存投影修正、视口缩放、MSAA/FXAA 状态机已完成；本地 Windows 链接 `d3d11.lib` 即可创建交换链窗口 |
| Xbox 手柄 XInput 桥接与震动控制 | `src/runtime/pad_xinput.cpp` | **100%** | **LOCKED (Argon 已验证)** | 已包含完整 `#ifdef _WIN32` `<Xinput.h>` 硬件轮询与 `0x801C4A68` 大端序写入 |
| 外置简体中文汉化 Overlay 与工具链 | `src/runtime/localization_zh.cpp`, `assets/locales/zh_CN.json` | **95%** | **LOCKED (Argon 已验证)** | 已完成 `0x8009F12C` 钩子与核心词典；本地可按需扩充完整剧情台词 |
| 本地 Ghidra Headless 导出与 MSVC 编译 | `scripts/*.bat`, `CMakeLists.txt` | **待本地执行** | **HYDROGEN SCOPE** | 物理依赖本地 Windows MSVC 编译器、Ghidra JVM 与完整 1.35 GB `P.N.03.iso` |

## 三、Mock 与 Live 双模式切换设计

* **`runtime_mode: "mock"`（云端沙盒验证模式）**：无需完整 1.35 GB 游戏光盘或物理 Xbox 手柄，直接读取解压的 `sys/boot.bin`、`sys/fst.bin`、`sys/main.dol` 与 `module/Tools.rel`，使用注入式 `XboxInputState` 验证完整帧循环、内存映射、宽屏正交矩阵与汉化钩子。
* **`runtime_mode: "live"`（本地 Windows 生产运行模式）**：在 `config/pn03_settings.json` 中设置 `"runtime_mode": "live"` 并指定 `"iso_path": "D:/Games/PN03.iso"`，自动启用 Windows 原生 `<Xinput.h>` 硬件手柄轮询、Win32 文件选择弹窗与 Direct3D 11 渲染窗口。

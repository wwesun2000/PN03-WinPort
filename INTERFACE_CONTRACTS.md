# P.N.03 (GPNE08) 内存映射、符号契约与配置接口规范 (`INTERFACE_CONTRACTS.md`)

## 一、`main.dol` 24MB 1T-SRAM 内存段与寄存器契约

| 段名 / 寄存器 | 虚拟地址范围 / 固定值 | 文件偏移 (`main.dol`) | 大小 (Bytes) | 对应 `MEKA.sym` 段标志与说明 |
| :--- | :--- | :--- | ---: | :--- |
| `Entry Point (__start)` | `0x80003100` | `0x000100` | — | 启动入口，初始化 `r1`、`r2`、`r13` 并清零 BSS |
| `r1 (Initial SP)` | `0x802808A0` | — | — | 主线程初始栈顶指针 |
| `r13 (_SDA_BASE_)` | `0x80275BE0` | — | — | Small Data Area 1 基址（寻址 `.sdata` 与 `.sbss`） |
| `r2 (_SDA2_BASE_)` | `0x80285BE0` | — | — | Small Data Area 2 基址（寻址 `.sdata2` 只读常量） |
| `Text[0]` (`.init`) | `0x80003100..0x800034C0` | `0x000100` | `960` | 底层硬件与寄存器初始化桩 |
| `Text[1]` (`.text`) | `0x800034C0..0x80162200` | `0x0004C0` | `1,436,992` | `sec_id=0x00`：共 **6,353 个函数**（3,891 游戏 `.obj` + 2,361 SDK `.o`） |
| `Data[0]` (`.ctors`/`.dtors`)| `0x80162200..0x801622E0` | `0x15F200` | `224` | C++ 全局静态构造与析构函数指针数组 |
| `Data[1]` (`.rodata`) | `0x801622E0..0x80170380` | `0x15F2E0` | `57,504` | `sec_id=0x03`：541 个只读常量、字符串与 C++ 虚函数表 (`vtable`) |
| `Data[2]` (`.data`) | `0x80170380..0x80185BA0` | `0x16D380` | `88,096` | `sec_id=0x04`：839 个已初始化全局变量 |
| `.bss` (Main BSS) | `0x80185BA0..0x8026DBE0` | — | `950,336` | `sec_id=0x05`：375 个大型全局结构（含 `Global`、`Joy`、`Key`、`Pad_data`） |
| `Data[3]` (`.sdata`) | `0x8026DBE0..0x8026E6A0` | `0x182BA0` | `2,752` | `sec_id=0x06`：309 个 `r13` 相对寻址短数据变量 |
| `.sbss` (Small BSS) | `0x8026E6A0..0x8026EF40` | — | `2,208` | `sec_id=0x07`：485 个 `r13` 相对寻址短 BSS 变量（含 `pG`、`ORTHO_*`） |
| `Data[4]` (`.sdata2`) | `0x8026EF40..0x802708A0` | `0x183660` | `6,496` | `sec_id=0x08`：628 个 `r2` 相对寻址浮点与常量字面量 |

## 二、五大改造目标核心 Hook 点与全局变量契约

| 改造目标 | 符号名称 (`MEKA.sym`) | 所属单元 | 虚拟地址 | 契约说明 |
| :--- | :--- | :--- | :--- | :--- |
| 主循环调度 | `main` | `main.obj` | `0x8009C4DC` | 初始化 `pG` (`0x8026E754`) 指向 `Global` (`0x801959C0`)，驱动每帧渲染与输入 |
| 3D 渲染与抗锯齿 | `Render_init(void)` | `main_sub.obj` | `0x8009D098` | 配置视口、裁剪框与 EFB 拷贝滤波；由 `GXHighResRenderer` 接管缩放至 1080p/4K |
| 16:9 宽屏正交边界 | `ORTHO_T / B / L / R` | `main.obj` | `0x8026E774..0x8026E780` | 原始 4:3 为 `L=0.0f, R=640.0f`；16:9 宽屏覆写为 `L=-106.67f, R=746.67f` |
| 上下黑边控制 | `Draw_cinesco(void)` | `cinesco.obj` | `0x80073348` | 当 `remove_cinesco_bars=true` 时直接跳过绘制上下遮幅黑边 |
| 语言锁定解除 | `CMesCtrl::MesSetLanguage` | `mes.obj` | `0x8009F12C` | 原版硬编码 `li r0, 1; stw r0, 0(r3); blr`；Hook 后写入配置语言（`6` = 简体中文） |
| 字库与文本渲染 | `CMesWk::FontDraw` | `mes.obj` | `0x800A00DC` | 拦截 `tagMSG_QUE` 消息队列，优先从 `LocalizationOverlay` 查询 UTF-8 中文文本 |
| Xbox 手柄状态输入 | `PadRead(void)` / `Pad_data` | `pad.obj` | `0x800ACC2C` / `0x801C4A68` | `PadXInputBridge` 将 XInput 状态转译为大端序 `PADStatus[4]` 写入 `0x801C4A68` |
| 手柄震动反馈 | `VibControl(void)` | `pad.obj` | `0x800AD160` | 将震动强度 `Vib_level` (`0x8026DD40`) 映射至 `XInputSetState` 双马达 |
| ISO 文件流式读取 | `DvdReadReqMain` | `dvd.obj` | `0x8007B744` | 由 `IsoStreamReader` 根据 `fst.bin` 偏移直接从外部 `.iso` 异步/同步读取 |
| `.lze` 房间解压 | `LzsDecode(uchar*, uchar*)` | `compless.obj` | `0x80077680` | 12 字节头 (`[0]:解压大小, [4]:比特流长度`) + 混合 8/13 位滑动窗口 LZSS 解压 |
| 调试菜单模块加载 | `OSLink` | `OSLink.o` | `0x800F56E0` | `ToolsRelLoader` 将 `/module/Tools.rel` 重定位映射至 `0x80300000` |

## 三、`config/pn03_settings.json` 配置文件 Schema

```json
{
  "runtime_mode": "live",
  "iso_path": "D:/Games/PN03_GPNE08.iso",
  "locale_overlay_path": "assets/locales/zh_CN.json",
  "save_dir": "saves",
  "backend": 0,
  "render_width": 1920,
  "render_height": 1080,
  "internal_scale_factor": 3,
  "window_mode": 1,
  "msaa_mode": 4,
  "enable_fxaa": true,
  "anisotropic_filtering": 16,
  "aspect_ratio": 1,
  "remove_cinesco_bars": true,
  "disable_copy_deflicker": true,
  "vsync": true,
  "language": 6,
  "enable_hd_chinese_font": true,
  "enable_xinput": true,
  "controller_index": 0,
  "control_scheme_preset": 0,
  "left_stick_deadzone": 0.15,
  "right_stick_deadzone": 0.15,
  "trigger_threshold": 0.35,
  "enable_vibration": true,
  "vibration_strength": 1.0,
  "load_tools_rel_debug": true,
  "skip_launcher_gui": false
}
```

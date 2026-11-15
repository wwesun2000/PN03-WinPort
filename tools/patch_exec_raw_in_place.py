#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
In-Place Static Recompiler Patcher for Workstreams A & B (P.N.03 GPNE08)
========================================================================
Scans all C++ files under `src/decompiled/` (including `subsystems/subsys_01..09.cpp`
and `tools_rel_decompiled.cpp`) and:
1. Lifts every `ctx.exec_raw(0x...u, 0x...u);` call across all 41 (op, xo) pairs
   into native C++20 statements.
2. Upgrades `srawi` and `sraw` statements to `ctx.srawi_op(...)` / `ctx.sraw_op(...)`
   so PowerPC `XER[CA]` carry state is accurately updated prior to `addze` / `subfze`.
3. Routes direct `bl` calls to Dolphin SDK functions (`0x800E3000..0x80162200`) and
   engine HLE hooks (`0x800734B8`, `0x80077680`, `0x8009F12C`, `0x8009F138`, `0x8009FDF0`)
   through `ctx.call_indirect(0x80xxxxxxu, mem)` so `dispatch_recompiled_function`
   intercepts them in both monolithic and split subsystem builds.
"""

import glob
import os
import re
import sys
from typing import Tuple

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

HLE_ENGINE_HOOK_ADDRS = {
    0x800734B8,  # Draw_cinesco
    0x8007B514,  # DvdReadProc
    0x80077680,  # LzsDecode
    0x8009F12C,  # CMesCtrl::MesSetLanguage
    0x8009F138,  # CMesCtrl::GetLanguage
    0x8009FDF0,  # CMesWk::MesWorkTrans
}


def should_route_via_hle(target_vaddr: int) -> bool:
    return (0x800E3000 <= target_vaddr <= 0x80162200) or (target_vaddr in HLE_ENGINE_HOOK_ADDRS)


def lift_raw_insn(pc: int, insn: int) -> Tuple[str, str]:
    """Lifts a 32-bit PowerPC/Gekko instruction word to (cpp_stmt, comment)."""
    if insn == 0:
        return "// padding 0x00000000", "word 0x00000000"

    op = (insn >> 26) & 0x3F
    rd = (insn >> 21) & 0x1F
    ra = (insn >> 16) & 0x1F
    rb = (insn >> 11) & 0x1F
    rc = (insn >> 6) & 0x1F
    xo10 = (insn >> 1) & 0x3FF
    xo5 = (insn >> 1) & 0x1F
    rc_b = bool(insn & 1)
    ra_expr = "0u" if ra == 0 else f"ctx.r[{ra}]"

    if op == 4:
        if xo10 == 1014:  # dcbz_l
            return (
                f"{{ uint32_t _ea = ({ra_expr} + ctx.r[{rb}]) & ~31u; if (mem.is_valid_range(_ea, 32)) std::memset(mem.translate(_ea, 32), 0, 32); }}",
                f"dcbz_l r{ra}, r{rb}",
            )
        if xo10 in (0, 32):  # ps_cmpu0 / ps_cmpo0
            crf = rd >> 2
            mnem = "ps_cmpu0" if xo10 == 0 else "ps_cmpo0"
            return (
                f"ctx.cmp_f64({crf}, static_cast<double>(ctx.ps0[{ra}]), static_cast<double>(ctx.ps0[{rb}]));",
                f"{mnem} cr{crf}, f{ra}, f{rb}",
            )
        if xo10 in (64, 96):  # ps_cmpu1 / ps_cmpo1
            crf = rd >> 2
            mnem = "ps_cmpu1" if xo10 == 64 else "ps_cmpo1"
            return (
                f"ctx.cmp_f64({crf}, static_cast<double>(ctx.ps1[{ra}]), static_cast<double>(ctx.ps1[{rb}]));",
                f"{mnem} cr{crf}, f{ra}, f{rb}",
            )
        if xo5 == 28:  # ps_msub
            return (
                f"{{ float _r0 = ctx.ps0[{ra}] * ctx.ps0[{rc}] - ctx.ps0[{rb}]; float _r1 = ctx.ps1[{ra}] * ctx.ps1[{rc}] - ctx.ps1[{rb}]; ctx.ps0[{rd}] = _r0; ctx.ps1[{rd}] = _r1; ctx.f[{rd}] = _r0; }}",
                f"ps_msub f{rd}, f{ra}, f{rc}, f{rb}",
            )
        if xo5 == 30:  # ps_nmadd
            return (
                f"{{ float _r0 = -(ctx.ps0[{ra}] * ctx.ps0[{rc}] + ctx.ps0[{rb}]); float _r1 = -(ctx.ps1[{ra}] * ctx.ps1[{rc}] + ctx.ps1[{rb}]); ctx.ps0[{rd}] = _r0; ctx.ps1[{rd}] = _r1; ctx.f[{rd}] = _r0; }}",
                f"ps_nmadd f{rd}, f{ra}, f{rc}, f{rb}",
            )
        if xo5 == 31:  # ps_nmsub
            return (
                f"{{ float _r0 = -(ctx.ps0[{ra}] * ctx.ps0[{rc}] - ctx.ps0[{rb}]); float _r1 = -(ctx.ps1[{ra}] * ctx.ps1[{rc}] - ctx.ps1[{rb}]); ctx.ps0[{rd}] = _r0; ctx.ps1[{rd}] = _r1; ctx.f[{rd}] = _r0; }}",
                f"ps_nmsub f{rd}, f{ra}, f{rc}, f{rb}",
            )
        if xo5 == 23:  # ps_sel
            return (
                f"{{ float _r0 = (ctx.ps0[{ra}] >= 0.0f) ? ctx.ps0[{rc}] : ctx.ps0[{rb}]; float _r1 = (ctx.ps1[{ra}] >= 0.0f) ? ctx.ps1[{rc}] : ctx.ps1[{rb}]; ctx.ps0[{rd}] = _r0; ctx.ps1[{rd}] = _r1; ctx.f[{rd}] = _r0; }}",
                f"ps_sel f{rd}, f{ra}, f{rc}, f{rb}",
            )
        if xo5 == 18:  # ps_div
            return (
                f"ctx.ps0[{rd}] = (ctx.ps0[{rb}] != 0.0f) ? (ctx.ps0[{ra}] / ctx.ps0[{rb}]) : 0.0f; ctx.ps1[{rd}] = (ctx.ps1[{rb}] != 0.0f) ? (ctx.ps1[{ra}] / ctx.ps1[{rb}]) : 0.0f; ctx.f[{rd}] = ctx.ps0[{rd}];",
                f"ps_div f{rd}, f{ra}, f{rb}",
            )
        if xo5 == 24:  # ps_res
            return (
                f"ctx.ps0[{rd}] = (ctx.ps0[{rb}] != 0.0f) ? (1.0f / ctx.ps0[{rb}]) : 0.0f; ctx.ps1[{rd}] = (ctx.ps1[{rb}] != 0.0f) ? (1.0f / ctx.ps1[{rb}]) : 0.0f; ctx.f[{rd}] = ctx.ps0[{rd}];",
                f"ps_res f{rd}, f{rb}",
            )
        if xo5 == 26:  # ps_rsqrte
            return (
                f"ctx.ps0[{rd}] = (ctx.ps0[{rb}] > 0.0f) ? (1.0f / std::sqrt(ctx.ps0[{rb}])) : 0.0f; ctx.ps1[{rd}] = (ctx.ps1[{rb}] > 0.0f) ? (1.0f / std::sqrt(ctx.ps1[{rb}])) : 0.0f; ctx.f[{rd}] = ctx.ps0[{rd}];",
                f"ps_rsqrte f{rd}, f{rb}",
            )
        if xo10 == 264:  # ps_abs
            return (
                f"ctx.ps0[{rd}] = std::fabs(ctx.ps0[{rb}]); ctx.ps1[{rd}] = std::fabs(ctx.ps1[{rb}]); ctx.f[{rd}] = ctx.ps0[{rd}];",
                f"ps_abs f{rd}, f{rb}",
            )
        if xo10 == 136:  # ps_nabs
            return (
                f"ctx.ps0[{rd}] = -std::fabs(ctx.ps0[{rb}]); ctx.ps1[{rd}] = -std::fabs(ctx.ps1[{rb}]); ctx.f[{rd}] = ctx.ps0[{rd}];",
                f"ps_nabs f{rd}, f{rb}",
            )

    elif op == 17:  # sc
        return "// sc", "sc"

    elif op == 19:
        if xo10 == 50:  # rfi
            return "return;", "rfi"

    elif op == 31:
        rc_suffix = f" ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[{rd}]), 0);" if rc_b else ""
        rc_ra_suffix = f" ctx.cmp_s32(0, static_cast<int32_t>(ctx.r[{ra}]), 0);" if rc_b else ""
        if xo10 == 284:  # eqv
            return f"ctx.r[{ra}] = ~(ctx.r[{rd}] ^ ctx.r[{rb}]);{rc_ra_suffix}", f"eqv r{ra}, r{rd}, r{rb}"
        if xo10 == 476:  # nand
            return f"ctx.r[{ra}] = ~(ctx.r[{rd}] & ctx.r[{rb}]);{rc_ra_suffix}", f"nand r{ra}, r{rd}, r{rb}"
        if xo10 == 412:  # orc
            return f"ctx.r[{ra}] = ctx.r[{rd}] | ~ctx.r[{rb}];{rc_ra_suffix}", f"orc r{ra}, r{rd}, r{rb}"
        if xo10 == 202:  # addze
            return (
                f"{{ uint64_t _s = static_cast<uint64_t>(ctx.r[{ra}]) + (ctx.get_ca() ? 1ull : 0ull); ctx.r[{rd}] = static_cast<uint32_t>(_s); ctx.set_ca(_s > 0xFFFFFFFFull); }}{rc_suffix}",
                f"addze r{rd}, r{ra}",
            )
        if xo10 == 200:  # subfze
            return (
                f"{{ uint64_t _s = static_cast<uint64_t>(~ctx.r[{ra}]) + (ctx.get_ca() ? 1ull : 0ull); ctx.r[{rd}] = static_cast<uint32_t>(_s); ctx.set_ca(_s > 0xFFFFFFFFull); }}{rc_suffix}",
                f"subfze r{rd}, r{ra}",
            )
        if xo10 == 83:  # mfmsr
            return f"ctx.r[{rd}] = ctx.msr;", f"mfmsr r{rd}"
        if xo10 == 146:  # mtmsr
            return f"ctx.msr = ctx.r[{rd}];", f"mtmsr r{rd}"
        if xo10 == 371:  # mftb
            tbr = (rb << 5) | ra
            if tbr == 269:
                return f"ctx.tb_ticks += 4050ull; ctx.r[{rd}] = static_cast<uint32_t>(ctx.tb_ticks >> 32);", f"mftbu r{rd}"
            return f"ctx.tb_ticks += 4050ull; ctx.r[{rd}] = static_cast<uint32_t>(ctx.tb_ticks & 0xFFFFFFFFull);", f"mftb r{rd}"
        if xo10 == 512:  # mcrxr
            crf = rd >> 2
            return f"ctx.cr[{crf}] = static_cast<uint8_t>((ctx.xer >> 28) & 0xFu); ctx.xer &= ~0xF0000000u;", f"mcrxr cr{crf}"
        if xo10 == 983:  # stfiwx
            return (
                f"{{ uint64_t _u = 0; std::memcpy(&_u, &ctx.f[{rd}], 8); mem.write_u32({ra_expr} + ctx.r[{rb}], static_cast<uint32_t>(_u)); }}",
                f"stfiwx f{rd}, r{ra}, r{rb}",
            )
        if xo10 == 343:  # lhax
            return (
                f"ctx.r[{rd}] = static_cast<uint32_t>(static_cast<int32_t>(mem.read_s16({ra_expr} + ctx.r[{rb}])));",
                f"lhax r{rd}, r{ra}, r{rb}",
            )
        if xo10 == 55:  # lwzux
            return (
                f"ctx.r[{ra}] += ctx.r[{rb}]; ctx.r[{rd}] = mem.read_u32(ctx.r[{ra}]);",
                f"lwzux r{rd}, r{ra}, r{rb}",
            )
        if xo10 == 183:  # stwux
            return (
                f"ctx.r[{ra}] += ctx.r[{rb}]; mem.write_u32(ctx.r[{ra}], ctx.r[{rd}]);",
                f"stwux r{rd}, r{ra}, r{rb}",
            )
        if xo10 == 311:  # lhzux
            return (
                f"ctx.r[{ra}] += ctx.r[{rb}]; ctx.r[{rd}] = mem.read_u16(ctx.r[{ra}]);",
                f"lhzux r{rd}, r{ra}, r{rb}",
            )
        if xo10 == 534:  # lwbrx
            return (
                f"ctx.r[{rd}] = bswap32(mem.read_u32({ra_expr} + ctx.r[{rb}]));",
                f"lwbrx r{rd}, r{ra}, r{rb}",
            )
        if xo10 == 790:  # lhbrx
            return (
                f"ctx.r[{rd}] = bswap16(mem.read_u16({ra_expr} + ctx.r[{rb}]));",
                f"lhbrx r{rd}, r{ra}, r{rb}",
            )
        if xo10 == 662:  # stwbrx
            return (
                f"mem.write_u32({ra_expr} + ctx.r[{rb}], bswap32(ctx.r[{rd}]));",
                f"stwbrx r{rd}, r{ra}, r{rb}",
            )
        if xo10 == 918:  # sthbrx
            return (
                f"mem.write_u16({ra_expr} + ctx.r[{rb}], bswap16(static_cast<uint16_t>(ctx.r[{rd}])));",
                f"sthbrx r{rd}, r{ra}, r{rb}",
            )
        if xo10 == 1014:  # dcbz
            return (
                f"{{ uint32_t _ea = ({ra_expr} + ctx.r[{rb}]) & ~31u; if (mem.is_valid_range(_ea, 32)) std::memset(mem.translate(_ea, 32), 0, 32); }}",
                f"dcbz r{ra}, r{rb}",
            )
        if xo10 in (598, 854, 54, 86, 278, 246, 470, 982):
            mnem_map = {598: "sync", 854: "eieio", 54: "dcbst", 86: "dcbf", 278: "dcbt", 246: "dcbtst", 470: "dcbi", 982: "icbi"}
            m = mnem_map[xo10]
            return f"// {m}", m

    elif op == 59:
        if xo5 == 24:  # fres
            return (
                f"{{ float _v = (ctx.f[{rb}] != 0.0) ? static_cast<float>(1.0 / ctx.f[{rb}]) : 0.0f; ctx.f[{rd}] = _v; ctx.ps0[{rd}] = ctx.ps1[{rd}] = _v; }}",
                f"fres f{rd}, f{rb}",
            )

    elif op == 63:
        if xo10 == 583:  # mffs
            return (
                f"{{ uint64_t _u = ctx.fpscr; std::memcpy(&ctx.f[{rd}], &_u, 8); }}",
                f"mffs f{rd}",
            )
        if xo10 == 711:  # mtfsf
            fm = (insn >> 17) & 0xFF
            return (
                f"{{ uint64_t _u = 0; std::memcpy(&_u, &ctx.f[{rb}], 8); ctx.fpscr = static_cast<uint32_t>(_u); }}",
                f"mtfsf 0x{fm:02X}, f{rb}",
            )
        if xo10 == 70:  # mtfsb0
            return f"ctx.fpscr &= ~(1u << (31u - {rd}u));", f"mtfsb0 {rd}"
        if xo10 == 38:  # mtfsb1
            return f"ctx.fpscr |= (1u << (31u - {rd}u));", f"mtfsb1 {rd}"
        if xo5 == 26:  # frsqrte
            return (
                f"{{ double _v = (ctx.f[{rb}] > 0.0) ? (1.0 / std::sqrt(ctx.f[{rb}])) : 0.0; ctx.f[{rd}] = _v; ctx.ps0[{rd}] = ctx.ps1[{rd}] = static_cast<float>(_v); }}",
                f"frsqrte f{rd}, f{rb}",
            )
        if xo5 == 30:  # fnmadd
            return (
                f"ctx.f[{rd}] = -(ctx.f[{ra}] * ctx.f[{rc}] + ctx.f[{rb}]); ctx.ps0[{rd}] = static_cast<float>(ctx.f[{rd}]);",
                f"fnmadd f{rd}, f{ra}, f{rc}, f{rb}",
            )
        if xo5 == 31:  # fnmsub
            return (
                f"ctx.f[{rd}] = -(ctx.f[{ra}] * ctx.f[{rc}] - ctx.f[{rb}]); ctx.ps0[{rd}] = static_cast<float>(ctx.f[{rd}]);",
                f"fnmsub f{rd}, f{ra}, f{rc}, f{rb}",
            )
        if xo5 == 23:  # fsel
            return (
                f"ctx.f[{rd}] = (ctx.f[{ra}] >= 0.0) ? ctx.f[{rc}] : ctx.f[{rb}]; ctx.ps0[{rd}] = static_cast<float>(ctx.f[{rd}]);",
                f"fsel f{rd}, f{ra}, f{rc}, f{rb}",
            )

    return f"ctx.exec_raw(0x{pc:08X}u, 0x{insn:08X}u, &mem);", f"raw 0x{insn:08X}"


EXEC_RAW_RE = re.compile(
    r"^(\s*/\* 0x([0-9A-Fa-f]{8}) \*/ )ctx\.exec_raw\(0x([0-9A-Fa-f]{8})u,\s*0x([0-9A-Fa-f]{8})u\);\s*//.*$"
)
SRAWI_RE = re.compile(
    r"^(\s*/\* 0x[0-9A-Fa-f]{8} \*/ )ctx\.r\[(\d+)\] = static_cast<uint32_t>\(static_cast<int32_t>\(ctx\.r\[(\d+)\]\)\s*>>\s*(\d+)\);\s*// srawi r\d+, r\d+, \d+$"
)
SRAW_RE = re.compile(
    r"^(\s*/\* 0x[0-9A-Fa-f]{8} \*/ )ctx\.r\[(\d+)\] = static_cast<uint32_t>\(static_cast<int32_t>\(ctx\.r\[(\d+)\]\)\s*>>\s*\(ctx\.r\[(\d+)\]\s*&\s*31u\)\);\s*// sraw r\d+, r\d+, r\d+$"
)
DIRECT_CALL_RE = re.compile(
    r"^(\s*/\* 0x[0-9A-Fa-f]{8} \*/ )([A-Za-z0-9_]+_([0-9A-Fa-f]{8}))\(ctx,\s*mem\);(.*)$"
)


def patch_file(filepath: str) -> Tuple[int, int, int]:
    with open(filepath, "r", encoding="utf-8") as f:
        lines = f.readlines()

    lifted_count = 0
    sraw_count = 0
    hle_routed_count = 0
    out_lines = []
    for line in lines:
        m_raw = EXEC_RAW_RE.match(line)
        if m_raw:
            prefix = m_raw.group(1)
            pc = int(m_raw.group(3), 16)
            insn = int(m_raw.group(4), 16)
            stmt, comment = lift_raw_insn(pc, insn)
            out_lines.append(f"{prefix}{stmt} // {comment}\n")
            lifted_count += 1
            continue

        m_srawi = SRAWI_RE.match(line)
        if m_srawi:
            prefix, ra, rd, sh = m_srawi.group(1), m_srawi.group(2), m_srawi.group(3), m_srawi.group(4)
            out_lines.append(f"{prefix}ctx.r[{ra}] = ctx.srawi_op(ctx.r[{rd}], {sh}u, false); // srawi r{ra}, r{rd}, {sh}\n")
            sraw_count += 1
            continue

        m_sraw = SRAW_RE.match(line)
        if m_sraw:
            prefix, ra, rd, rb = m_sraw.group(1), m_sraw.group(2), m_sraw.group(3), m_sraw.group(4)
            out_lines.append(f"{prefix}ctx.r[{ra}] = ctx.sraw_op(ctx.r[{rd}], ctx.r[{rb}], false); // sraw r{ra}, r{rd}, r{rb}\n")
            sraw_count += 1
            continue

        m_call = DIRECT_CALL_RE.match(line)
        if m_call:
            prefix, sym_name, hex_va, tail = m_call.group(1), m_call.group(2), m_call.group(3), m_call.group(4)
            target_va = int(hex_va, 16)
            if should_route_via_hle(target_va):
                out_lines.append(f"{prefix}ctx.call_indirect(0x{target_va:08X}u, mem);{tail}\n")
                hle_routed_count += 1
                continue

        out_lines.append(line)

    if lifted_count > 0 or sraw_count > 0 or hle_routed_count > 0:
        with open(filepath, "w", encoding="utf-8") as f:
            f.writelines(out_lines)
    return lifted_count, sraw_count, hle_routed_count


def main() -> int:
    target_dir = sys.argv[1] if len(sys.argv) > 1 else os.path.join(PROJECT_ROOT, "src", "decompiled")
    cpp_files = sorted(glob.glob(os.path.join(target_dir, "**", "*.cpp"), recursive=True))
    total_lifted = 0
    total_sraw = 0
    total_routed = 0
    for path in cpp_files:
        if os.path.basename(path) == "indirect_call_table.cpp":
            continue
        l_cnt, s_cnt, r_cnt = patch_file(path)
        total_lifted += l_cnt
        total_sraw += s_cnt
        total_routed += r_cnt
        print(
            f"[patch_exec_raw_in_place] {os.path.relpath(path, PROJECT_ROOT)}: "
            f"lifted {l_cnt} exec_raw, upgraded {s_cnt} srawi/sraw, routed {r_cnt} SDK/HLE calls"
        )
    print(
        f"[patch_exec_raw_in_place] TOTAL: lifted {total_lifted} exec_raw, "
        f"upgraded {total_sraw} srawi/sraw, routed {total_routed} SDK/HLE calls across {len(cpp_files)} files."
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

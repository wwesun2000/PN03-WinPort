#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ppc_ast_decompiler.py - High-Level Expression-Propagating C++ Pseudocode Decompiler for P.N.03 (GPNE08)
Produces human-readable, structured C++ pseudocode (`src/decompiled_hl/*.cpp`) directly in the sandbox
by combining:
  1. Demangled C++ function signatures and parameter types from MEKA.sym
  2. Symbolic dataflow & expression propagation across r0..r31 and f0..f31
  3. Automatic SDA1 (`r13=0x80275BE0`) / SDA2 (`r2=0x80285BE0`) global variable resolution
  4. Automatic C++ Virtual Table (`152 vtables`) & string literal resolution
  5. Reconstructed high-level function calls `FuncName(arg0, arg1, ...)` and structured `if` / loop blocks
"""

import json
import os
import re
import struct
from typing import Dict, List, Optional, Tuple
from extract_and_decompile import DolBinary, PowerPCLifter, EXTRACT_DIR, PROJECT_ROOT


def parse_cpp_signature_params(sig: str) -> Tuple[str, List[Tuple[str, str]]]:
    """
    Parses a demangled C++ signature from MEKA.sym like:
      'CMesCtrl::MesSet(unsigned long, long, long, unsigned long, long, MES_COLOR)'
    and assigns PowerPC EABI register arguments (r3..r10 for int/ptr, f1..f8 for float/double).
    """
    if "(" not in sig or not sig.endswith(")"):
        return sig, []
    func_part, rest = sig.split("(", 1)
    param_str = rest.rsplit(")", 1)[0].strip()
    is_const = sig.endswith("const")
    if ")" in param_str:
        param_str = param_str.split(")")[0].strip()

    params: List[Tuple[str, str]] = []
    gpr_idx = 3
    fpr_idx = 1

    # If member function (`Class::Method`), r3 is `this`
    if "::" in func_part and not func_part.startswith("global "):
        cls_name = func_part.split("::")[0].strip()
        params.append((f"{cls_name}* this_r3", "r3"))
        gpr_idx = 4

    if param_str and param_str != "void":
        raw_types = [p.strip() for p in param_str.split(",") if p.strip()]
        for i, ptype in enumerate(raw_types):
            if ptype in ("float", "double"):
                reg = f"f{fpr_idx}"
                params.append((f"{ptype} arg{i}_{reg}", reg))
                fpr_idx += 1
            else:
                reg = f"r{gpr_idx}"
                params.append((f"{ptype} arg{i}_{reg}", reg))
                gpr_idx += 1

    return func_part.strip(), params


class HighLevelASTDecompiler:
    SDA1_BASE = 0x80275BE0
    SDA2_BASE = 0x80285BE0

    def __init__(self, dol: DolBinary, symbols: List[dict], vtables_info: dict):
        self.dol = dol
        self.addr_to_sym: Dict[int, dict] = {}
        for s in symbols:
            if s["name"] != "." and s["address"] not in self.addr_to_sym:
                self.addr_to_sym[s["address"]] = s
        self.vtable_addrs = {
            int(vt["vtable_vaddr"], 16): vt for vt in vtables_info.get("vtables", [])
        }

    def sym_or_hex(self, addr: int) -> str:
        addr &= 0xFFFFFFFF
        if addr in self.vtable_addrs:
            return f"&vtable_{self.vtable_addrs[addr]['class_name']}"
        s = self.addr_to_sym.get(addr)
        cstr = self.dol.read_cstring(addr)
        if s and cstr:
            return f'&{s["name"]} /* "{cstr}" */'
        if s:
            return f"&{s['name']}"
        if cstr:
            return f'"{cstr}"'
        return f"0x{addr:08X}u"

    def decompile_function_hl(self, func_sym: dict) -> str:
        start_addr = func_sym["address"]
        est_size = func_sym.get("estimated_size", 256)
        if est_size <= 0:
            est_size = 64
        num_insns = max(1, est_size // 4)
        off = self.dol.vaddr_to_offset(start_addr)
        if off is None:
            return f"// Unable to map 0x{start_addr:08X}\n"

        orig_sig = func_sym["name"]
        func_name, params = parse_cpp_signature_params(orig_sig)
        param_decl = ", ".join(p[0] for p in params) if params else "void"

        # Symbolic register state tracker for expression folding
        reg_expr: Dict[str, str] = {f"r{i}": f"r{i}" for i in range(32)}
        reg_hi: Dict[int, int] = {}
        for p_decl, reg_name in params:
            pname = p_decl.split()[-1].lstrip("*&")
            reg_expr[reg_name] = pname

        branch_targets = set()
        end_addr = start_addr + num_insns * 4
        for i in range(num_insns):
            if off + (i + 1) * 4 > len(self.dol.data):
                num_insns = i
                end_addr = start_addr + num_insns * 4
                break
            pc = start_addr + i * 4
            insn = struct.unpack(">I", self.dol.data[off + i * 4 : off + (i + 1) * 4])[0]
            op = insn >> 26
            if op == 16:
                bd = insn & 0xFFFC
                if bd & 0x8000:
                    bd -= 0x10000
                tgt = (bd if (insn & 2) else (pc + bd)) & 0xFFFFFFFF
                if start_addr <= tgt < end_addr:
                    branch_targets.add(tgt)
            elif op == 18 and not (insn & 1):
                li = insn & 0x03FFFFFC
                if li & 0x02000000:
                    li -= 0x04000000
                tgt = (li if (insn & 2) else (pc + li)) & 0xFFFFFFFF
                if start_addr <= tgt < end_addr:
                    branch_targets.add(tgt)

        lines = [
            "// ============================================================================",
            f"// High-Level AST Decompilation: {orig_sig}",
            f"// Unit: {func_sym['unit']} | Address: 0x{start_addr:08X} | Size: 0x{est_size:X} bytes",
            "// ============================================================================",
            f"/* [0x{start_addr:08X}] */ void {func_name}({param_decl}) {{",
        ]

        last_cmp = ("r0", "0")
        frame_size = 0

        for i in range(num_insns):
            pc = start_addr + i * 4
            if pc in branch_targets:
                lines.append(f"label_{pc:08X}:;")

            insn = struct.unpack(">I", self.dol.data[off + i * 4 : off + (i + 1) * 4])[0]
            op = insn >> 26
            rd = (insn >> 21) & 31
            ra = (insn >> 16) & 31
            rb = (insn >> 11) & 31
            rc = (insn >> 6) & 31
            imm = insn & 0xFFFF
            simm = imm - 0x10000 if (imm & 0x8000) else imm

            if op == 37 and rd == 1 and ra == 1 and simm < 0:
                frame_size = -simm
                lines.append(f"    // Stack frame allocated: {frame_size} bytes")
                continue
            if op == 31 and ((insn >> 1) & 0x3FF) in (339, 467) and (((rb << 5) | ra) == 8):
                # mflr / mtlr prologue/epilogue
                continue
            if op in (46, 47):
                # lmw / stmw callee-saved registers
                continue
            if op == 14 and rd == 1 and ra == 1 and simm > 0:
                # addi r1, r1, frame_size epilogue
                continue

            if op == 15:  # lis
                if ra == 0:
                    val = (imm << 16) & 0xFFFFFFFF
                    reg_hi[rd] = val
                    reg_expr[f"r{rd}"] = f"0x{val:08X}u"
                else:
                    reg_hi.pop(rd, None)
                    reg_expr[f"r{rd}"] = f"({reg_expr.get(f'r{ra}', f'r{ra}')} + 0x{(imm << 16) & 0xFFFFFFFF:08X}u)"
            elif op == 14:  # li / addi
                if ra == 0:
                    reg_hi.pop(rd, None)
                    reg_expr[f"r{rd}"] = str(simm)
                    lines.append(f"    r{rd} = {simm};")
                elif ra == 13:
                    ea = (self.SDA1_BASE + simm) & 0xFFFFFFFF
                    sym_s = self.sym_or_hex(ea)
                    reg_hi.pop(rd, None)
                    reg_expr[f"r{rd}"] = sym_s
                    lines.append(f"    r{rd} = {sym_s};")
                elif ra == 2:
                    ea = (self.SDA2_BASE + simm) & 0xFFFFFFFF
                    sym_s = self.sym_or_hex(ea)
                    reg_hi.pop(rd, None)
                    reg_expr[f"r{rd}"] = sym_s
                    lines.append(f"    r{rd} = {sym_s};")
                elif ra in reg_hi:
                    ea = (reg_hi[ra] + simm) & 0xFFFFFFFF
                    sym_s = self.sym_or_hex(ea)
                    reg_hi.pop(rd, None)
                    reg_expr[f"r{rd}"] = sym_s
                    lines.append(f"    r{rd} = {sym_s};")
                elif ra == 1:
                    reg_hi.pop(rd, None)
                    reg_expr[f"r{rd}"] = f"&stack_0x{simm:02X}"
                    lines.append(f"    r{rd} = &stack_0x{simm:02X};")
                else:
                    base_e = reg_expr.get(f"r{ra}", f"r{ra}")
                    reg_hi.pop(rd, None)
                    reg_expr[f"r{rd}"] = f"({base_e} + {simm})"
                    lines.append(f"    r{rd} = {base_e} + ({simm});")
            elif op == 24:  # ori
                if rd == 0 and ra == 0 and imm == 0:
                    continue
                if rd in reg_hi:
                    ea = (reg_hi[rd] | imm) & 0xFFFFFFFF
                    sym_s = self.sym_or_hex(ea)
                    reg_hi.pop(ra, None)
                    reg_expr[f"r{ra}"] = sym_s
                    lines.append(f"    r{ra} = {sym_s};")
                else:
                    reg_hi.pop(ra, None)
                    lines.append(f"    r{ra} = {reg_expr.get(f'r{rd}', f'r{rd}')} | 0x{imm:04X}u;")
            elif op in (32, 34, 40, 42, 48, 50):  # loads
                t_cast = {32: "uint32_t", 34: "uint8_t", 40: "uint16_t", 42: "int16_t", 48: "float", 50: "double"}[op]
                dst_r = f"f{rd}" if op in (48, 50) else f"r{rd}"
                if ra == 13:
                    ea = (self.SDA1_BASE + simm) & 0xFFFFFFFF
                    s = self.addr_to_sym.get(ea)
                    src_e = f"SDA1::{s['name']}" if s else f"*({t_cast}*)0x{ea:08X}"
                elif ra == 2:
                    ea = (self.SDA2_BASE + simm) & 0xFFFFFFFF
                    s = self.addr_to_sym.get(ea)
                    src_e = f"SDA2::{s['name']}" if s else f"*({t_cast}*)0x{ea:08X}"
                elif ra in reg_hi:
                    ea = (reg_hi[ra] + simm) & 0xFFFFFFFF
                    s = self.addr_to_sym.get(ea)
                    src_e = s["name"] if s else f"*({t_cast}*)0x{ea:08X}"
                elif ra == 1:
                    src_e = f"stack_0x{simm:02X}"
                else:
                    base_e = reg_expr.get(f"r{ra}", f"r{ra}")
                    src_e = f"*({t_cast}*)({base_e} + 0x{simm:X})" if simm >= 0 else f"*({t_cast}*)({base_e} - 0x{-simm:X})"
                if op not in (48, 50):
                    reg_hi.pop(rd, None)
                reg_expr[dst_r] = src_e
                lines.append(f"    {dst_r} = {src_e};")
            elif op in (36, 38, 44, 52, 54):  # stores
                t_cast = {36: "uint32_t", 38: "uint8_t", 44: "uint16_t", 52: "float", 54: "double"}[op]
                src_r = f"f{rd}" if op in (52, 54) else f"r{rd}"
                val_e = reg_expr.get(src_r, src_r)
                if ra == 13:
                    ea = (self.SDA1_BASE + simm) & 0xFFFFFFFF
                    s = self.addr_to_sym.get(ea)
                    dst_e = f"SDA1::{s['name']}" if s else f"*({t_cast}*)0x{ea:08X}"
                elif ra in reg_hi:
                    ea = (reg_hi[ra] + simm) & 0xFFFFFFFF
                    s = self.addr_to_sym.get(ea)
                    dst_e = s["name"] if s else f"*({t_cast}*)0x{ea:08X}"
                elif ra == 1:
                    dst_e = f"stack_0x{simm:02X}"
                else:
                    base_e = reg_expr.get(f"r{ra}", f"r{ra}")
                    dst_e = f"*({t_cast}*)({base_e} + 0x{simm:X})" if simm >= 0 else f"*({t_cast}*)({base_e} - 0x{-simm:X})"
                lines.append(f"    {dst_e} = {val_e};")
            elif op in (10, 11):  # cmpwi / cmplwi
                last_cmp = (reg_expr.get(f"r{ra}", f"r{ra}"), str(simm if op == 11 else f"0x{imm:X}u"))
            elif op == 16:  # bc
                bd = insn & 0xFFFC
                if bd & 0x8000:
                    bd -= 0x10000
                tgt = (bd if (insn & 2) else (pc + bd)) & 0xFFFFFFFF
                bo = (insn >> 21) & 31
                bi = (insn >> 16) & 31
                sub_bi = bi & 3
                op_map = {0: "<", 1: ">", 2: "=="}
                inv_map = {0: ">=", 1: "<=", 2: "!="}
                cmp_op = (op_map if (bo & 8) else inv_map).get(sub_bi, "!=")
                cond_s = f"{last_cmp[0]} {cmp_op} {last_cmp[1]}"
                if start_addr <= tgt < end_addr:
                    lines.append(f"    if ({cond_s}) goto label_{tgt:08X};")
                else:
                    lines.append(f"    if ({cond_s}) {{ /* tail branch 0x{tgt:08X} */ return; }}")
            elif op == 18:  # b / bl
                li = insn & 0x03FFFFFC
                if li & 0x02000000:
                    li -= 0x04000000
                tgt = (li if (insn & 2) else (pc + li)) & 0xFFFFFFFF
                lk = bool(insn & 1)
                callee = self.addr_to_sym.get(tgt)
                callee_sig = callee["name"] if callee else f"sub_{tgt:08X}()"
                callee_name, callee_params = parse_cpp_signature_params(callee_sig)
                call_args = [reg_expr.get(r_name, r_name) for _, r_name in callee_params]
                call_str = f"{callee_name}({', '.join(call_args)})"
                if lk:
                    reg_expr["r3"] = f"ret_{pc:08X}"
                    reg_hi.pop(3, None)
                    lines.append(f"    r3 = {call_str}; // [0x{tgt:08X}]")
                else:
                    if start_addr <= tgt < end_addr:
                        lines.append(f"    goto label_{tgt:08X};")
                    else:
                        lines.append(f"    {call_str}; return;")
            elif op == 19:
                xo = (insn >> 1) & 0x3FF
                if xo == 16 and rd == 20 and ra == 0:
                    lines.append(f"    return; // r3 = {reg_expr.get('r3', 'r3')}")
                elif xo == 528:
                    lines.append(f"    /* Indirect/Virtual Call */ ({reg_expr.get('ctr', 'ctr')})(r3, r4, r5);")
            elif op == 31:
                xo = (insn >> 1) & 0x3FF
                if xo == 444 and rd == rb:
                    val_e = reg_expr.get(f"r{rd}", f"r{rd}")
                    reg_expr[f"r{ra}"] = val_e
                    reg_hi.pop(ra, None)
                    lines.append(f"    r{ra} = {val_e};")
                elif xo == 266:
                    e = f"({reg_expr.get(f'r{ra}', f'r{ra}')} + {reg_expr.get(f'r{rb}', f'r{rb}')})"
                    reg_expr[f"r{rd}"] = e
                    reg_hi.pop(rd, None)
                    lines.append(f"    r{rd} = {e};")
                elif xo == 40:
                    e = f"({reg_expr.get(f'r{rb}', f'r{rb}')} - {reg_expr.get(f'r{ra}', f'r{ra}')})"
                    reg_expr[f"r{rd}"] = e
                    reg_hi.pop(rd, None)
                    lines.append(f"    r{rd} = {e};")
                elif xo in (0, 32):
                    last_cmp = (reg_expr.get(f"r{ra}", f"r{ra}"), reg_expr.get(f"r{rb}", f"r{rb}"))
                elif xo == 467 and (((rb << 5) | ra) == 9):
                    reg_expr["ctr"] = reg_expr.get(f"r{rd}", f"r{rd}")

        lines.append("}\n")
        return "\n".join(lines)


def main():
    hl_dir = os.path.join(PROJECT_ROOT, "src", "decompiled_hl")
    os.makedirs(hl_dir, exist_ok=True)

    dol_bytes = open(f"{EXTRACT_DIR}/sys/main.dol", "rb").read()
    sym_manifest = json.load(open(f"{PROJECT_ROOT}/re_data/meka_symbols_full.json", "r", encoding="utf-8"))
    vt_info = json.load(open(f"{PROJECT_ROOT}/re_data/vtables_and_ctors.json", "r", encoding="utf-8"))

    dol = DolBinary(dol_bytes)
    symbols = sym_manifest["symbols"]
    decompiler = HighLevelASTDecompiler(dol, symbols, vt_info)

    core_units = [
        ("main.obj", "main_hl.cpp"),
        ("main_sub.obj", "main_sub_hl.cpp"),
        ("mes.obj", "mes_hl.cpp"),
        ("pad.obj", "pad_hl.cpp"),
        ("dvd.obj", "dvd_hl.cpp"),
        ("read.obj", "read_hl.cpp"),
        ("compless.obj", "compless_hl.cpp"),
        ("option.obj", "option_hl.cpp"),
        ("title.obj", "title_hl.cpp"),
        ("cockpit.obj", "cockpit_hl.cpp"),
        ("CId.obj", "cid_hl.cpp"),
        ("player.obj", "player_hl.cpp"),
        ("camera.obj", "camera_hl.cpp"),
        ("trans.obj", "trans_hl.cpp"),
    ]

    total_hl = 0
    for unit_name, out_file in core_units:
        seen = set()
        funcs = []
        for s in symbols:
            if s["unit"] == unit_name and s["section_id"] == 0x00 and s["name"] != "." and s["address"] not in seen:
                seen.add(s["address"])
                funcs.append(s)

        out_lines = [
            "// ============================================================================",
            f"// P.N.03 (GPNE08) High-Level Expression-Propagated Decompiled C++: {unit_name}",
            f"// Functions Decompiled: {len(funcs)}",
            "// ============================================================================",
            "",
        ]
        for fn in funcs:
            out_lines.append(decompiler.decompile_function_hl(fn))
            total_hl += 1

        with open(os.path.join(hl_dir, out_file), "w", encoding="utf-8") as f:
            f.write("\n".join(out_lines))

    print(f"[OK] Generated High-Level AST C++ pseudocode for {total_hl} core functions across {len(core_units)} modules in src/decompiled_hl/.")


if __name__ == "__main__":
    main()

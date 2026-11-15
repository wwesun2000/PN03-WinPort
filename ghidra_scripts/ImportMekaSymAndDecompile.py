# -*- coding: utf-8 -*-
# @category GameCube.PN03
# @runtime Jython
"""
ImportMekaSymAndDecompile.py - Ghidra Headless Post-Script for P.N.03 (GPNE08 / MEKA)

Works with either:
  1. The pre-converted ELF32-ppc-be (`pn03_main_with_syms.elf` produced by `tools/dol_to_elf.py`), OR
  2. Raw `sys/main.dol` + `MEKA.sym` imported into Ghidra (`PowerPC:BE:32:Gekko_Broadway` or `PowerPC:BE:32:default`).

Responsibilities:
  1. Sets PowerPC Small Data Area base registers across the entire program:
       - r13 (_SDA_BASE_)  = 0x80275BE0
       - r2  (_SDA2_BASE_) = 0x80285BE0
  2. Applies all 9,530 symbols from `MEKA.sym` (if not already present via ELF .symtab),
     creating functions at all 6,353 .text addresses and labels at all .rodata/.data/.bss/.sdata/.sbss/.sdata2 addresses.
  3. Initializes Ghidra's DecompInterface and batch-decompiles all game compilation units (.obj)
     into structured C/C++ files under `src/ghidra_decompiled/<unit_name>.cpp`.
"""

import json
import os
import re
import struct

try:
    from ghidra.app.decompiler import DecompInterface, DecompileOptions
    from ghidra.program.model.address import AddressSet
    from ghidra.program.model.lang import RegisterValue
    from ghidra.program.model.symbol import SourceType
    from ghidra.util.task import ConsoleTaskMonitor
    import java.math.BigInteger as BigInteger
    IN_GHIDRA = True
except ImportError:
    IN_GHIDRA = False


SDA1_BASE = 0x80275BE0
SDA2_BASE = 0x80285BE0


def sanitize_filename(unit_name):
    base = re.sub(r"[^A-Za-z0-9_.-]", "_", unit_name)
    if base.endswith(".obj"):
        base = base[:-4] + "_ghidra.cpp"
    elif base.endswith(".o"):
        base = base[:-2] + "_sdk_ghidra.cpp"
    else:
        base = base + "_ghidra.cpp"
    return base


def configure_sda_registers(program, monitor):
    """Sets r13 = 0x80275BE0 and r2 = 0x80285BE0 across all initialized memory blocks."""
    ctx = program.getProgramContext()
    r13 = ctx.getRegister("r13")
    r2 = ctx.getRegister("r2")
    mem = program.getMemory()
    min_addr = mem.getMinAddress()
    max_addr = mem.getMaxAddress()
    if r13 is not None:
        val13 = RegisterValue(r13, BigInteger.valueOf(SDA1_BASE))
        ctx.setRegisterValue(min_addr, max_addr, val13)
    if r2 is not None:
        val2 = RegisterValue(r2, BigInteger.valueOf(SDA2_BASE))
        ctx.setRegisterValue(min_addr, max_addr, val2)
    println("[PN03-Ghidra] Configured r13 (_SDA_BASE_) = 0x%08X, r2 (_SDA2_BASE_) = 0x%08X" % (SDA1_BASE, SDA2_BASE))


def apply_meka_symbols(program, sym_json_path, monitor):
    """Applies symbols from re_data/meka_symbols_full.json to the current Ghidra program."""
    if not os.path.exists(sym_json_path):
        println("[PN03-Ghidra] Symbol JSON not found at %s; relying on ELF .symtab." % sym_json_path)
        return {}

    with open(sym_json_path, "r") as f:
        manifest = json.load(f)

    sym_tab = program.getSymbolTable()
    listing = program.getListing()
    addr_factory = program.getAddressFactory().getDefaultAddressSpace()

    unit_to_funcs = {}
    created_funcs = 0
    created_labels = 0

    for s in manifest.get("symbols", []):
        if monitor.isCancelled():
            break
        name = s.get("name", "")
        if not name or name == "." or name.startswith("@"):
            continue
        addr_int = int(s["address"])
        gh_addr = addr_factory.getAddress(addr_int)
        clean_name = re.sub(r"[^A-Za-z0-9_::~]", "_", name.split("(")[0].strip())
        if not clean_name:
            clean_name = "sym_%08X" % addr_int

        if s.get("section_id") == 0x00:
            func = listing.getFunctionAt(gh_addr)
            if func is None:
                func = createFunction(gh_addr, clean_name)
                created_funcs += 1
            else:
                func.setName(clean_name, SourceType.IMPORTED)
            if func is not None:
                func.setComment("Original Signature: %s\nCompilation Unit: %s" % (name, s.get("unit", "")))
            unit = s.get("unit", "global.obj")
            unit_to_funcs.setdefault(unit, []).append((addr_int, name, gh_addr))
        else:
            sym_tab.createLabel(gh_addr, clean_name, SourceType.IMPORTED)
            created_labels += 1

    println("[PN03-Ghidra] Applied %d functions and %d data/BSS labels from MEKA.sym." % (created_funcs, created_labels))
    return unit_to_funcs


def batch_decompile_units(program, unit_to_funcs, out_dir, monitor):
    """Exports decompiled C/C++ pseudocode per compilation unit (.obj) using Ghidra DecompInterface."""
    if not os.path.exists(out_dir):
        os.makedirs(out_dir)

    ifc = DecompInterface()
    opts = DecompileOptions()
    ifc.setOptions(opts)
    ifc.openProgram(program)

    listing = program.getListing()
    exported_units = 0
    exported_funcs = 0

    for unit_name, func_list in sorted(unit_to_funcs.items()):
        if not unit_name.endswith(".obj"):
            continue
        out_path = os.path.join(out_dir, sanitize_filename(unit_name))
        lines = [
            "// ============================================================================",
            "// Ghidra Headless Decompilation Output for P.N.03 (GPNE08)",
            "// Compilation Unit: %s (%d functions)" % (unit_name, len(func_list)),
            "// ============================================================================",
            '#include "pn03_types.hpp"',
            '#include "pn03_symbols.hpp"',
            "",
        ]
        for addr_int, orig_sig, gh_addr in sorted(func_list, key=lambda x: x[0]):
            if monitor.isCancelled():
                break
            func = listing.getFunctionAt(gh_addr)
            if func is None:
                continue
            res = ifc.decompileFunction(func, 30, monitor)
            lines.append("// [0x%08X] %s" % (addr_int, orig_sig))
            if res and res.decompileCompleted():
                c_code = res.getDecompiledFunction().getC()
                lines.append(c_code)
                exported_funcs += 1
            else:
                lines.append("// Decompilation fallback stub for 0x%08X" % addr_int)
        with open(out_path, "w") as out_f:
            out_f.write("\n".join(lines))
        exported_units += 1

    ifc.dispose()
    println("[PN03-Ghidra] Exported %d decompiled functions across %d .obj files to %s" % (exported_funcs, exported_units, out_dir))


def run_in_ghidra():
    monitor = ConsoleTaskMonitor()
    args = getScriptArgs()
    sym_json = args[0] if len(args) > 0 else "re_data/meka_symbols_full.json"
    out_dir = args[1] if len(args) > 1 else "src/ghidra_decompiled"

    configure_sda_registers(currentProgram, monitor)
    unit_to_funcs = apply_meka_symbols(currentProgram, sym_json, monitor)
    if unit_to_funcs:
        batch_decompile_units(currentProgram, unit_to_funcs, out_dir, monitor)


if IN_GHIDRA:
    run_in_ghidra()

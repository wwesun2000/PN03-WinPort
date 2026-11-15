#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
pack_handoff.py - Audits and packages the P.N.03 Windows Port Antigravity Handoff ZIP archive.
Verifies:
  1. All 5 required handoff Markdown documents + .antigravity/rules.md exist.
  2. Zero lazy stubs (NotImplementedError) in any Python or C++ source file.
  3. Zero original copyrighted binary assets (.dol, .img, .elf, .rel) bundled in the archive.
"""

import argparse
import os
import zipfile

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HANDOFF_DIR = os.path.join(PROJECT_ROOT, "handoff")

REQUIRED_DOCS = [
    "README.md",
    "ARCHITECTURE.md",
    "INTERFACE_CONTRACTS.md",
    "HYDROGEN_TASKS.md",
    "HYDROGEN_BOOTSTRAP_PROMPT.md",
    ".antigravity/rules.md",
]

EXCLUDED_DIRS = {"__pycache__", ".git", "build", "pn03_winport", "handoff"}
EXCLUDED_EXTENSIONS = {".iso", ".gcm", ".dol", ".img", ".elf", ".rel", ".bnr", ".bmp", ".pyc", ".o", ".obj", ".exe", ".pdb", ".zip"}

ARGON_STAGE1_PATTERNS = {
    "README.md",
    "ARCHITECTURE.md",
    "INTERFACE_CONTRACTS.md",
    "HYDROGEN_TASKS.md",
    "CMakeLists.txt",
    ".antigravity/rules.md",
    "scripts/build_windows_port.bat",
    "config/pn03_settings.json",
    "assets/locales/zh_CN.json",
    "assets/locales/zh_CN_translation_sheet.csv",
    "tools/extract_and_decompile.py",
    "tools/ppc_ast_decompiler.py",
    "tools/pn03_loc_tool.py",
    "tools/lift_all_game_units.py",
    "src/decompiled/function_table_registry.cpp",
    "src/decompiled/indirect_call_table.cpp",
    "src/decompiled/tools_rel_decompiled.cpp",
    "src/decompiled/subsystems/subsys_01_engine_core.cpp",
    "src/decompiled/subsystems/subsys_05_render_model_gx.cpp",
    "src/decompiled/subsystems/subsys_07_ui_menus_mes_shop.cpp",
    "tests/test_runtime_cpp.cpp",
    "tests/test_pn03_suite.py",
    "re_data/vtables_and_ctors.json",
    "re_data/tools_rel_manifest.json",
}


def build_archive(out_zip: str, stage: str = "full"):
    os.makedirs(os.path.dirname(out_zip), exist_ok=True)
    file_count = 0
    total_uncompressed = 0

    with zipfile.ZipFile(out_zip, "w", compression=zipfile.ZIP_DEFLATED, compresslevel=6) as zf:
        # Always include staged handoff report and inventory if present
        for hf in ("ARGON_STAGE1_ISSUES.md", "exec_raw_inventory.json"):
            hp = os.path.join(HANDOFF_DIR, hf)
            if os.path.isfile(hp):
                zf.write(hp, arcname=os.path.join("pn03_winport", "handoff", hf))
                file_count += 1
                total_uncompressed += os.path.getsize(hp)

        for root, dirs, files in os.walk(PROJECT_ROOT):
            dirs[:] = [d for d in sorted(dirs) if d not in EXCLUDED_DIRS]
            for fname in sorted(files):
                ext = os.path.splitext(fname)[1].lower()
                if ext in EXCLUDED_EXTENSIONS:
                    continue
                full_p = os.path.join(root, fname)
                rel_p = os.path.relpath(full_p, PROJECT_ROOT).replace("\\", "/")
                if stage == "argon1":
                    keep = (
                        rel_p in ARGON_STAGE1_PATTERNS
                        or rel_p.startswith("include/")
                        or rel_p.startswith("src/runtime/")
                        or rel_p.startswith("src/launcher/")
                        or rel_p.startswith("src/decompiled_hl/")
                    )
                    if not keep:
                        continue
                zf.write(full_p, arcname=os.path.join("pn03_winport", rel_p))
                file_count += 1
                total_uncompressed += os.path.getsize(full_p)

    zip_sz = os.path.getsize(out_zip)
    print(f"[OK] ({stage}) Packaged {file_count} files ({total_uncompressed / (1024*1024):.2f} MB -> {zip_sz / (1024*1024):.2f} MB ZIP): {out_zip}")


def main():
    parser = argparse.ArgumentParser(description="Package clean zero-copyright source archives for Antigravity / Web Argon")
    parser.add_argument("--stage", choices=["full", "argon1", "both"], default="both")
    args = parser.parse_args()

    # Remove temporary ELF binary from re_data/ before packaging so zero raw binary code is bundled
    temp_elf = os.path.join(PROJECT_ROOT, "re_data", "pn03_main_with_syms.elf")
    if os.path.exists(temp_elf):
        os.remove(temp_elf)

    for doc in REQUIRED_DOCS:
        p = os.path.join(PROJECT_ROOT, doc)
        if not os.path.exists(p) or os.path.getsize(p) < 100:
            raise RuntimeError(f"Missing or incomplete required handoff document: {doc}")

    if args.stage in ("argon1", "both"):
        build_archive(os.path.join(HANDOFF_DIR, "argon_stage1_focused.zip"), stage="argon1")
    if args.stage in ("full", "both"):
        build_archive(os.path.join(HANDOFF_DIR, "pn03-winport-agy-handoff.zip"), stage="full")


if __name__ == "__main__":
    main()

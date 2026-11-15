#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
dol_to_elf.py - Converts GameCube sys/main.dol + SN Systems MEKA.sym into a standard
32-bit Big-Endian PowerPC ELF (EM_PPC = 20) with complete Program Headers (PT_LOAD),
Section Headers (.init, .text, .ctors, .rodata, .data, .bss, .sdata, .sbss, .sdata2),
and a populated ELF .symtab / .strtab containing all 8,221 named symbols.

Supports 3 input modes:
  1. Auto-detect `.iso` / `.gcm` placed in the project root directory (`python tools/dol_to_elf.py`)
  2. Explicit `.iso` / `.gcm` path (`python tools/dol_to_elf.py --iso PN03.iso`)
  3. Extracted `sys/main.dol` + `MEKA.sym` paths (`python tools/dol_to_elf.py main.dol MEKA.sym out.elf`)
"""

import glob
import os
import struct
import sys
from typing import Optional, Tuple

EI_MAG = b"\x7fELF"
ELFCLASS32 = 1
ELFDATA2MSB = 2
EV_CURRENT = 1
ET_EXEC = 2
EM_PPC = 20

PT_LOAD = 1
PF_X = 1
PF_W = 2
PF_R = 4

SHT_NULL = 0
SHT_PROGBITS = 1
SHT_SYMTAB = 2
SHT_STRTAB = 3
SHT_NOBITS = 8

SHF_WRITE = 1
SHF_ALLOC = 2
SHF_EXECINSTR = 4

STB_LOCAL = 0
STB_GLOBAL = 1
STT_NOTYPE = 0
STT_OBJECT = 1
STT_FUNC = 2


def extract_dol_and_sym_from_iso(iso_path: str) -> Tuple[bytes, bytes]:
    """Directly extracts sys/main.dol and /MEKA.sym from a GameCube ISO/GCM image."""
    with open(iso_path, "rb") as f:
        boot = f.read(0x440)
        magic = struct.unpack(">I", boot[0x1C:0x20])[0]
        if magic != 0xC2339F3D:
            raise ValueError(f"Invalid GameCube ISO magic 0x{magic:08X} in {iso_path}")
        dol_off, fst_off, fst_sz = struct.unpack(">III", boot[0x420:0x42C])

        # Read DOL header to determine total DOL size
        f.seek(dol_off)
        dol_hdr = f.read(0x100)
        offs = struct.unpack(">18I", dol_hdr[0x00:0x48])
        szs  = struct.unpack(">18I", dol_hdr[0x90:0xD8])
        dol_total_sz = max((o + s for o, s in zip(offs, szs) if s > 0), default=0x100)
        f.seek(dol_off)
        dol_bytes = f.read(dol_total_sz)

        # Parse FST to locate /MEKA.sym
        f.seek(fst_off)
        fst = f.read(fst_sz)
        num_entries = struct.unpack(">I", fst[8:12])[0]
        str_off = num_entries * 12
        sym_bytes = b""
        for idx in range(1, num_entries):
            ent = fst[idx * 12 : (idx + 1) * 12]
            if ent[0] == 0:
                name_off = struct.unpack(">I", b"\x00" + ent[1:4])[0]
                file_off, file_sz = struct.unpack(">II", ent[4:12])
                name = fst[str_off + name_off :].split(b"\x00")[0].decode("ascii", "replace")
                if name.lower() == "meka.sym":
                    f.seek(file_off)
                    sym_bytes = f.read(file_sz)
                    break

    if not sym_bytes:
        raise RuntimeError(f"Could not find MEKA.sym inside ISO FST of {iso_path}")
    return dol_bytes, sym_bytes


def build_elf_from_dol_and_sym(dol_bytes: bytes, sym_bytes: bytes, out_elf_path: str) -> dict:
    text_off = struct.unpack(">7I", dol_bytes[0x00:0x1C])
    data_off = struct.unpack(">11I", dol_bytes[0x1C:0x48])
    text_addr = struct.unpack(">7I", dol_bytes[0x48:0x64])
    data_addr = struct.unpack(">11I", dol_bytes[0x64:0x90])
    text_size = struct.unpack(">7I", dol_bytes[0x90:0xAC])
    data_size = struct.unpack(">11I", dol_bytes[0xAC:0xD8])
    bss_addr, bss_size, entry_point = struct.unpack(">III", dol_bytes[0xD8:0xE4])

    sections_spec = [
        (".init", SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR, text_addr[0], dol_bytes[text_off[0] : text_off[0] + text_size[0]], text_size[0], PF_R | PF_X),
        (".text", SHT_PROGBITS, SHF_ALLOC | SHF_EXECINSTR, text_addr[1], dol_bytes[text_off[1] : text_off[1] + text_size[1]], text_size[1], PF_R | PF_X),
        (".ctors", SHT_PROGBITS, SHF_ALLOC | SHF_WRITE, data_addr[0], dol_bytes[data_off[0] : data_off[0] + data_size[0]], data_size[0], PF_R | PF_W),
        (".rodata", SHT_PROGBITS, SHF_ALLOC, data_addr[1], dol_bytes[data_off[1] : data_off[1] + data_size[1]], data_size[1], PF_R),
        (".data", SHT_PROGBITS, SHF_ALLOC | SHF_WRITE, data_addr[2], dol_bytes[data_off[2] : data_off[2] + data_size[2]], data_size[2], PF_R | PF_W),
        (".bss", SHT_NOBITS, SHF_ALLOC | SHF_WRITE, 0x80185BA0, b"", 0x8026DBE0 - 0x80185BA0, PF_R | PF_W),
        (".sdata", SHT_PROGBITS, SHF_ALLOC | SHF_WRITE, data_addr[3], dol_bytes[data_off[3] : data_off[3] + data_size[3]], data_size[3], PF_R | PF_W),
        (".sbss", SHT_NOBITS, SHF_ALLOC | SHF_WRITE, 0x8026E6A0, b"", 0x8026EF40 - 0x8026E6A0, PF_R | PF_W),
        (".sdata2", SHT_PROGBITS, SHF_ALLOC, data_addr[4], dol_bytes[data_off[4] : data_off[4] + data_size[4]], data_size[4], PF_R),
    ]

    sec_id_to_shndx = {
        0x00: 2,
        0x03: 4,
        0x04: 5,
        0x05: 6,
        0x06: 7,
        0x07: 8,
        0x08: 9,
    }

    sym_tab_off, obj_str_off, sym_str_off = struct.unpack(">III", sym_bytes[:12])
    num_syms = (obj_str_off - sym_tab_off) // 12
    raw_syms = []
    for i in range(num_syms):
        pos = sym_tab_off + i * 12
        addr, word2, name_off = struct.unpack(">III", sym_bytes[pos : pos + 12])
        sec_id = (word2 >> 8) & 0xFF
        name = sym_bytes[sym_str_off + name_off :].split(b"\x00")[0].decode("ascii", "replace")
        raw_syms.append((addr, sec_id, name))

    strtab = bytearray(b"\x00")
    symtab = bytearray(struct.pack(">IIIBBH", 0, 0, 0, 0, 0, 0))

    special_syms = [
        ("__start", entry_point, 4, STB_GLOBAL, STT_FUNC, 1),
        ("_SDA_BASE_", 0x80275BE0, 0, STB_GLOBAL, STT_OBJECT, 7),
        ("_SDA2_BASE_", 0x80285BE0, 0, STB_GLOBAL, STT_OBJECT, 9),
    ]
    for sname, saddr, ssize, sbind, stype, shndx in special_syms:
        name_idx = len(strtab)
        strtab.extend(sname.encode("ascii") + b"\x00")
        st_info = (sbind << 4) | (stype & 0xF)
        symtab.extend(struct.pack(">IIIBBH", name_idx, saddr, ssize, st_info, 0, shndx))

    named_count = 0
    for i, (addr, sec_id, name) in enumerate(raw_syms):
        if name == "." or name.startswith("@"):
            continue
        if i + 1 < len(raw_syms) and raw_syms[i + 1][1] == sec_id:
            sz = max(0, raw_syms[i + 1][0] - addr)
        else:
            sz = 4
        shndx = sec_id_to_shndx.get(sec_id, 2)
        stype = STT_FUNC if sec_id == 0x00 else STT_OBJECT
        st_info = (STB_GLOBAL << 4) | stype
        name_idx = len(strtab)
        strtab.extend(name.encode("ascii") + b"\x00")
        symtab.extend(struct.pack(">IIIBBH", name_idx, addr, sz, st_info, 0, shndx))
        named_count += 1

    shstrtab = bytearray(b"\x00")
    sh_name_offsets = {}
    for sname in [s[0] for s in sections_spec] + [".symtab", ".strtab", ".shstrtab"]:
        sh_name_offsets[sname] = len(shstrtab)
        shstrtab.extend(sname.encode("ascii") + b"\x00")

    ehdr_size = 52
    phdr_size = 32
    shdr_size = 40
    num_phdrs = len(sections_spec)
    num_shdrs = 1 + len(sections_spec) + 3

    cur_off = (ehdr_size + num_phdrs * phdr_size + 31) & ~31
    phdrs_bytes = bytearray()
    shdrs_bytes = bytearray(struct.pack(">10I", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0))
    body_chunks = []

    for sname, shtype, shflags, vaddr, raw_bytes, memsz, pflags in sections_spec:
        cur_off = (cur_off + 15) & ~15
        filesz = len(raw_bytes)
        phdrs_bytes.extend(
            struct.pack(">8I", PT_LOAD, cur_off if filesz > 0 else 0, vaddr, vaddr, filesz, memsz, pflags, 32)
        )
        shdrs_bytes.extend(
            struct.pack(">10I", sh_name_offsets[sname], shtype, shflags, vaddr, cur_off if filesz > 0 else 0, memsz, 0, 0, 16, 0)
        )
        if filesz > 0:
            body_chunks.append((cur_off, raw_bytes))
            cur_off += filesz

    cur_off = (cur_off + 15) & ~15
    symtab_off = cur_off
    body_chunks.append((symtab_off, bytes(symtab)))
    cur_off += len(symtab)

    cur_off = (cur_off + 15) & ~15
    strtab_off = cur_off
    body_chunks.append((strtab_off, bytes(strtab)))
    cur_off += len(strtab)

    cur_off = (cur_off + 15) & ~15
    shstrtab_off = cur_off
    body_chunks.append((shstrtab_off, bytes(shstrtab)))
    cur_off += len(shstrtab)

    shdrs_bytes.extend(struct.pack(">10I", sh_name_offsets[".symtab"], SHT_SYMTAB, 0, 0, symtab_off, len(symtab), 11, 1, 4, 16))
    shdrs_bytes.extend(struct.pack(">10I", sh_name_offsets[".strtab"], SHT_STRTAB, 0, 0, strtab_off, len(strtab), 0, 0, 1, 0))
    shdrs_bytes.extend(struct.pack(">10I", sh_name_offsets[".shstrtab"], SHT_STRTAB, 0, 0, shstrtab_off, len(shstrtab), 0, 0, 1, 0))

    shoff = (cur_off + 15) & ~15
    e_ident = struct.pack("4sBBBBB7s", EI_MAG, ELFCLASS32, ELFDATA2MSB, EV_CURRENT, 0, 0, b"\x00" * 7)
    ehdr = struct.pack(
        ">16sHHIIIIIHHHHHH",
        e_ident, ET_EXEC, EM_PPC, EV_CURRENT, entry_point, ehdr_size, shoff, 0,
        ehdr_size, phdr_size, num_phdrs, shdr_size, num_shdrs, num_shdrs - 1,
    )

    out_buf = bytearray(shoff + len(shdrs_bytes))
    out_buf[0:ehdr_size] = ehdr
    out_buf[ehdr_size : ehdr_size + len(phdrs_bytes)] = phdrs_bytes
    for chunk_off, chunk_data in body_chunks:
        out_buf[chunk_off : chunk_off + len(chunk_data)] = chunk_data
    out_buf[shoff : shoff + len(shdrs_bytes)] = shdrs_bytes

    os.makedirs(os.path.dirname(os.path.abspath(out_elf_path)), exist_ok=True)
    with open(out_elf_path, "wb") as f:
        f.write(out_buf)

    return {
        "elf_path": out_elf_path,
        "elf_size_bytes": len(out_buf),
        "entry_point": f"0x{entry_point:08X}",
        "exported_symbols": named_count + len(special_syms),
    }


def find_iso_in_project_root() -> Optional[str]:
    for pat in ("*.iso", "*.ISO", "*.gcm", "*.GCM"):
        matches = sorted(glob.glob(pat))
        if matches:
            return matches[0]
    return None


if __name__ == "__main__":
    out_p = "build/pn03_main_with_syms.elf"
    if len(sys.argv) >= 3 and sys.argv[1] == "--iso":
        iso_file = sys.argv[2]
        if len(sys.argv) >= 4:
            out_p = sys.argv[3]
        dol_b, sym_b = extract_dol_and_sym_from_iso(iso_file)
    elif len(sys.argv) >= 3 and os.path.exists(sys.argv[1]) and os.path.exists(sys.argv[2]):
        dol_b = open(sys.argv[1], "rb").read()
        sym_b = open(sys.argv[2], "rb").read()
        if len(sys.argv) >= 4:
            out_p = sys.argv[3]
    else:
        auto_iso = sys.argv[1] if (len(sys.argv) >= 2 and sys.argv[1].lower().endswith((".iso", ".gcm"))) else find_iso_in_project_root()
        if auto_iso and os.path.exists(auto_iso):
            print(f"[INFO] Auto-detected ISO in project directory: {auto_iso}")
            dol_b, sym_b = extract_dol_and_sym_from_iso(auto_iso)
        else:
            dol_p = "/tmp/pn03_extract/sys/main.dol"
            sym_p = "/tmp/pn03_extract/MEKA.sym"
            dol_b = open(dol_p, "rb").read()
            sym_b = open(sym_p, "rb").read()
    res = build_elf_from_dol_and_sym(dol_b, sym_b, out_p)
    print("[OK] Built standard PowerPC32 Big-Endian ELF with full symbols:", res)

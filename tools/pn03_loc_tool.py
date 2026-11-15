#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
pn03_loc_tool.py - P.N.03 (GPNE08) ISO Localization & TPL Font Texture Extractor / Inspector

Directly reads a user-supplied P.N.03 .iso/.gcm (or extracted directory) WITHOUT modifying
the original ISO, inspects /id/eng/iddata_e.dat, lobby_e.dat, equip_ck_e.dat, trialrank_e.dat,
and /etc/moji8.tpl, exports a complete translation template JSON, and validates `zh_CN.json`.
"""

import argparse
import csv
import glob
import json
import os
import re
import struct
from typing import Dict, List, Optional, Tuple

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_DICT_PATH = os.path.join(PROJECT_ROOT, "assets", "locales", "zh_CN.json")
DEFAULT_CSV_PATH = os.path.join(PROJECT_ROOT, "assets", "locales", "zh_CN_translation_sheet.csv")
PRINTF_RE = re.compile(r"%(?:[+\-#0 ]*)?(?:\*|\d+)?(?:\.(?:\*|\d+))?[diuoxXfFeEgGcsp%]")
TAG_RE = re.compile(r"<[0-9a-fA-F]{2,4}>")

TARGET_ENG_DATS = [
    "/id/eng/iddata_e.dat",
    "/id/eng/lobby_e.dat",
    "/id/eng/equip_ck_e.dat",
    "/id/eng/trialrank_e.dat",
]


def auto_discover_iso(root_dir: str = PROJECT_ROOT) -> Optional[str]:
    candidates: List[str] = []
    for pat in ("*.iso", "*.gcm", "*.ISO", "*.GCM"):
        candidates.extend(glob.glob(os.path.join(root_dir, pat)))
    candidates = sorted(set(candidates))
    return candidates[0] if candidates else None


def read_iso_paths(iso_or_dir: str, wanted_paths: List[str]) -> Dict[str, bytes]:
    """Reads multiple FST paths cleanly from an ISO/GCM/NKit-ISO or extracted directory."""
    wanted_norm = {"/" + p.lstrip("/").lower(): p for p in wanted_paths}
    out: Dict[str, bytes] = {}
    if os.path.isdir(iso_or_dir):
        for norm, orig in wanted_norm.items():
            p = os.path.join(iso_or_dir, orig.lstrip("/"))
            if os.path.isfile(p):
                with open(p, "rb") as f:
                    out[norm] = f.read()
        return out

    with open(iso_or_dir, "rb") as iso:
        boot = iso.read(0x440)
        if len(boot) < 0x440:
            return out
        fst_off, fst_sz = struct.unpack(">II", boot[0x424:0x42C])
        iso.seek(fst_off)
        fst = iso.read(fst_sz)
        num_entries = struct.unpack(">I", fst[8:12])[0]
        str_off = num_entries * 12
        stack = [(num_entries, "")]
        for idx in range(1, num_entries):
            while stack and idx >= stack[-1][0]:
                stack.pop()
            ent = fst[idx * 12 : (idx + 1) * 12]
            name_off = struct.unpack(">I", b"\x00" + ent[1:4])[0]
            off_or_p, sz_or_n = struct.unpack(">II", ent[4:12])
            name = fst[str_off + name_off :].split(b"\x00")[0].decode("ascii", "replace")
            path = stack[-1][1] + "/" + name
            if ent[0]:
                stack.append((sz_or_n, path))
            elif path.lower() in wanted_norm:
                iso.seek(off_or_p)
                out[path.lower()] = iso.read(sz_or_n)
    return out


def decode_moji_chunk(chunk_bytes: bytes) -> List[str]:
    """Decodes Capcom P.N.03 0xF05ADF3E UTF-16BE glyph-indexed message tables cleanly."""
    if len(chunk_bytes) < 8 or chunk_bytes[:4] != b"\xf0\x5a\xdf\x3e":
        return []
    cnt = struct.unpack(">I", chunk_bytes[4:8])[0]
    if cnt == 0 or cnt > 4096 or 8 + 4 * cnt > len(chunk_bytes):
        return []
    offs = struct.unpack(f">{cnt}I", chunk_bytes[8 : 8 + 4 * cnt])
    # Validate monotonic table offsets to reject binary/TPL false positives (e.g. trialrank_e.dat)
    min_off = 8 + 4 * cnt
    if any(o < min_off or o >= len(chunk_bytes) for o in offs):
        return []
    if any(offs[i] > offs[i + 1] for i in range(cnt - 1)):
        return []
    # Exact verified glyph table from P.N.03 (GPNE08) ISO .dat chunks:
    # 0x80=' ', 0x83..0x8C='0'..'9', 0xA7..0xC0='A'..'Z', 0xC1..0xDA='a'..'z', 0x0123='\''
    punct = {
        0x0080: " ",
        0x008D: ":",
        0x0090: "+",
        0x0091: "-",
        0x0092: "/",
        0x0094: ",",
        0x0095: ".",
        0x0098: "(",
        0x0099: ")",
        0x009A: "!",
        0x009B: "?",
        0x009C: "\"",
        0x009D: "\"",
        0x0123: "'",
    }
    messages: List[str] = []
    for i, off in enumerate(offs):
        end = offs[i + 1] if i + 1 < cnt else len(chunk_bytes)
        if off >= len(chunk_bytes) or end <= off:
            continue
        nwords = (end - off) // 2
        vals = struct.unpack(f">{nwords}H", chunk_bytes[off : off + nwords * 2])
        has_term = False
        chars: List[str] = []
        for v in vals:
            if v == 0x0001:
                has_term = True
                break
            if v in (0x0000, 0x0002):
                continue
            if v == 0x0003:
                chars.append("\n")
            elif 0x0083 <= v <= 0x008C:
                chars.append(chr(v - 0x0083 + ord("0")))
            elif 0x00A7 <= v <= 0x00C0:
                chars.append(chr(v - 0x00A7 + ord("A")))
            elif 0x00C1 <= v <= 0x00DA:
                chars.append(chr(v - 0x00C1 + ord("a")))
            elif v in punct:
                chars.append(punct[v])
            else:
                chars.append(f"<{v:02x}>")
        s = "".join(chars).strip()
        if s and has_term and any(ch.isalpha() for ch in s):
            messages.append(s)
    return messages


def parse_tpl_header(tpl_bytes: bytes) -> dict:
    """Parses Nintendo GameCube TPL (Texture Palette Library) header (magic 0x0020AF30)."""
    if len(tpl_bytes) < 12:
        return {"valid": False, "reason": "Buffer < 12 bytes"}
    magic, num_textures, hdr_sz = struct.unpack(">III", tpl_bytes[:12])
    if magic != 0x0020AF30:
        return {"valid": False, "magic": f"0x{magic:08X}"}
    textures = []
    for i in range(min(num_textures, 64)):
        tex_hdr_off, tlut_hdr_off = struct.unpack(">II", tpl_bytes[12 + i * 8 : 20 + i * 8])
        if tex_hdr_off + 36 <= len(tpl_bytes):
            height, width, fmt, data_off, wrap_s, wrap_t, min_f, mag_f = struct.unpack(
                ">HHIIIIII", tpl_bytes[tex_hdr_off : tex_hdr_off + 28]
            )
            textures.append(
                {
                    "index": i,
                    "width": width,
                    "height": height,
                    "format": fmt,
                    "data_offset": f"0x{data_off:06X}",
                    "tlut_offset": f"0x{tlut_hdr_off:06X}",
                }
            )
    return {
        "valid": True,
        "magic": "0x0020AF30",
        "num_textures": num_textures,
        "textures": textures,
    }


def extract_strings_from_dat(dat_bytes: bytes, min_len: int = 4) -> List[str]:
    """Extracts clean game message strings from Capcom .dat containers (0xF05ADF3E chunks)."""
    seen = set()
    out: List[str] = []
    if len(dat_bytes) >= 8:
        count = struct.unpack(">I", dat_bytes[:4])[0]
        if 1 <= count <= 2048 and 4 + 4 * (count + 1) <= len(dat_bytes):
            offs = struct.unpack(f">{count + 1}I", dat_bytes[4 : 4 + 4 * (count + 1)])
            if all(offs[i] <= offs[i + 1] <= len(dat_bytes) for i in range(count)):
                for i in range(count):
                    chunk = dat_bytes[offs[i] : offs[i + 1]]
                    if chunk[:4] == b"\xf0\x5a\xdf\x3e":
                        for s in decode_moji_chunk(chunk):
                            if len(s) >= min_len and s not in seen:
                                seen.add(s)
                                out.append(s)
                if out:
                    return out

    # Standalone 0xF05ADF3E buffer fallback
    if dat_bytes[:4] == b"\xf0\x5a\xdf\x3e":
        for s in decode_moji_chunk(dat_bytes):
            if len(s) >= min_len and s not in seen:
                seen.add(s)
                out.append(s)
        return out

    # Conservative ASCII scan ONLY when not a TPL texture container
    if dat_bytes[:4] != b"\x00\x20\xaf\x30":
        raw = re.findall(rb"[A-Za-z][A-Za-z0-9 \.,!?\'\-:/()]{%d,}\x00" % (min_len - 1), dat_bytes)
        for item in raw:
            s = item[:-1].decode("ascii", "ignore").strip()
            if len(s) >= min_len and s not in seen:
                seen.add(s)
                out.append(s)
    return out


def extract_template_from_iso(iso_or_dir: str, out_json: str) -> dict:
    """Scans /id/eng/*.dat from a user-supplied P.N.03 ISO or extracted dir and exports a translation template."""
    files_map = read_iso_paths(iso_or_dir, TARGET_ENG_DATS)
    extracted: Dict[str, str] = {}
    for norm in sorted(files_map.keys()):
        for s in extract_strings_from_dat(files_map[norm]):
            extracted[s] = ""

    payload = {
        "locale": "zh_CN",
        "game_id": "GPNE08",
        "scanned_dat_files": len(files_map),
        "entries": extracted,
    }
    os.makedirs(os.path.dirname(os.path.abspath(out_json)), exist_ok=True)
    with open(out_json, "w", encoding="utf-8") as f:
        json.dump(payload, f, indent=2, ensure_ascii=False)
    return {"scanned_files": len(files_map), "extracted_strings": len(extracted), "out_json": out_json}


def check_placeholder_safety(src: str, dst: str) -> Tuple[bool, str]:
    """Ensures printf specifiers (%d, %s, ...) and inline bytecode tags match safely."""
    if not dst:
        return True, "untranslated"
    src_fmt = PRINTF_RE.findall(src)
    dst_fmt = PRINTF_RE.findall(dst)
    if src_fmt != dst_fmt:
        return False, f"printf mismatch: expected {src_fmt}, got {dst_fmt}"
    src_tags = TAG_RE.findall(src)
    dst_tags = TAG_RE.findall(dst)
    if src_tags != dst_tags:
        return False, f"tag mismatch: expected {src_tags}, got {dst_tags}"
    return True, "ok"


def verify_zh_dictionary(json_path: str) -> dict:
    with open(json_path, "r", encoding="utf-8") as f:
        data = json.load(f)
    meta_keys = ("locale", "game_id", "font_atlas")
    id_entries = [k for k in data.keys() if k.startswith("0x")]
    str_entries = [k for k in data.keys() if not k.startswith("0x") and k not in meta_keys]
    bad_placeholders: List[dict] = []
    for k in str_entries:
        ok, msg = check_placeholder_safety(k, str(data[k]))
        if not ok:
            bad_placeholders.append({"key": k, "reason": msg})
    return {
        "valid": data.get("locale") == "zh_CN" and data.get("game_id") == "GPNE08" and not bad_placeholders,
        "locale": data.get("locale"),
        "id_entry_count": len(id_entries),
        "string_entry_count": len(str_entries),
        "total_translations": len(id_entries) + len(str_entries),
        "placeholder_errors": bad_placeholders,
    }


def cmd_inspect(iso_path: str, dict_path: str) -> dict:
    summary: dict = {"dictionary": verify_zh_dictionary(dict_path) if os.path.isfile(dict_path) else {"missing": dict_path}}
    target_iso = iso_path or auto_discover_iso() or ""
    if target_iso and os.path.exists(target_iso):
        paths = TARGET_ENG_DATS + ["/etc/moji8.tpl"]
        files_map = read_iso_paths(target_iso, paths)
        iso_info: dict = {"iso_path": target_iso, "dat_messages": {}, "moji8_tpl": None}
        total_msgs = 0
        for dat_p in TARGET_ENG_DATS:
            raw = files_map.get(dat_p.lower())
            if raw is not None:
                msgs = extract_strings_from_dat(raw)
                iso_info["dat_messages"][dat_p] = len(msgs)
                total_msgs += len(msgs)
        iso_info["total_dat_messages"] = total_msgs
        if "/etc/moji8.tpl" in files_map:
            iso_info["moji8_tpl"] = parse_tpl_header(files_map["/etc/moji8.tpl"])
        summary["iso_inspection"] = iso_info
    else:
        summary["iso_inspection"] = {"found": False}
    return summary


def cmd_export_csv(dict_path: str, csv_path: str, iso_path: str = "", include_iso: bool = True) -> dict:
    with open(dict_path, "r", encoding="utf-8") as f:
        data = json.load(f)
    rows: List[Tuple[str, str, str, str]] = []
    seen = set()
    for k, v in data.items():
        if k in ("locale", "game_id", "font_atlas"):
            continue
        kind = "id" if k.startswith("0x") else "text"
        rows.append((k, kind, k if kind == "text" else "", str(v)))
        seen.add(k)

    added_iso = 0
    if include_iso:
        target_iso = iso_path or auto_discover_iso() or ""
        if target_iso and os.path.exists(target_iso):
            files_map = read_iso_paths(target_iso, TARGET_ENG_DATS)
            for p in sorted(files_map.keys()):
                for s in extract_strings_from_dat(files_map[p]):
                    if s not in seen:
                        rows.append((s, f"iso:{p}", s, ""))
                        seen.add(s)
                        added_iso += 1

    os.makedirs(os.path.dirname(os.path.abspath(csv_path)), exist_ok=True)
    with open(csv_path, "w", encoding="utf-8-sig", newline="") as f:
        w = csv.writer(f)
        w.writerow(["key", "source_kind", "source_text", "translation_zh_CN"])
        w.writerows(rows)
    return {"csv_path": csv_path, "total_rows": len(rows), "existing_dict_rows": len(rows) - added_iso, "iso_untranslated_rows": added_iso}


def cmd_import_csv(csv_path: str, dict_path: str) -> dict:
    with open(dict_path, "r", encoding="utf-8") as f:
        data = json.load(f)
    updated = 0
    added = 0
    rejected = []
    with open(csv_path, "r", encoding="utf-8-sig", newline="") as f:
        reader = csv.DictReader(f)
        for row in reader:
            k = (row.get("key") or "").strip()
            tr = (row.get("translation_zh_CN") or "").strip()
            src = (row.get("source_text") or k).strip()
            if not k or not tr:
                continue
            ok, msg = check_placeholder_safety(src, tr)
            if not ok:
                rejected.append({"key": k, "reason": msg})
                continue
            if k in data:
                if data[k] != tr:
                    data[k] = tr
                    updated += 1
            else:
                data[k] = tr
                added += 1
    if rejected:
        raise ValueError(f"Placeholder validation failed on {len(rejected)} entries: {rejected[:5]}")
    with open(dict_path, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=2, ensure_ascii=False)
        f.write("\n")
    return {"dict_path": dict_path, "updated": updated, "added": added, "rejected": 0}


def cmd_compile_json(dict_path: str, out_json: str) -> dict:
    res = verify_zh_dictionary(dict_path)
    if not res["valid"]:
        raise ValueError(f"Dictionary validation failed: {res}")
    with open(dict_path, "r", encoding="utf-8") as f:
        data = json.load(f)
    os.makedirs(os.path.dirname(os.path.abspath(out_json)), exist_ok=True)
    with open(out_json, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=2, ensure_ascii=False)
        f.write("\n")
    res["compiled_out"] = out_json
    return res


def main():
    parser = argparse.ArgumentParser(description="P.N.03 Localization & Font Overlay Tool")
    parser.add_argument(
        "action",
        nargs="?",
        choices=["inspect", "export-csv", "import-csv", "compile-json"],
        help="Optional workflow subcommand",
    )
    parser.add_argument("--verify-dict", default=DEFAULT_DICT_PATH, help="Path to zh_CN.json")
    parser.add_argument("--extract-iso", default="", help="Path to P.N.03 .iso/.gcm or extracted dir")
    parser.add_argument("--iso", default="", help="Path to P.N.03 .iso/.gcm (auto-detected if omitted)")
    parser.add_argument("--csv", default=DEFAULT_CSV_PATH, help="Bilingual CSV translation sheet path")
    parser.add_argument("--out", default="", help="Output JSON path")
    args = parser.parse_args()

    if args.action == "inspect":
        res = cmd_inspect(args.iso or args.extract_iso, args.verify_dict)
        print("[OK] Localization Inspection:", json.dumps(res, indent=2, ensure_ascii=False))
    elif args.action == "export-csv":
        res = cmd_export_csv(args.verify_dict, args.csv, args.iso or args.extract_iso)
        print("[OK] CSV Exported:", json.dumps(res, ensure_ascii=False))
    elif args.action == "import-csv":
        res = cmd_import_csv(args.csv, args.verify_dict)
        print("[OK] CSV Imported:", json.dumps(res, ensure_ascii=False))
    elif args.action == "compile-json":
        res = cmd_compile_json(args.verify_dict, args.out or args.verify_dict)
        print("[OK] JSON Compiled:", json.dumps(res, ensure_ascii=False))
    elif args.extract_iso:
        out_path = args.out or os.path.join(PROJECT_ROOT, "assets", "locales", "zh_CN_template.json")
        ext_res = extract_template_from_iso(args.extract_iso, out_path)
        print("[OK] ISO Localization Extraction:", json.dumps(ext_res, ensure_ascii=False))
    else:
        res = verify_zh_dictionary(args.verify_dict)
        print("[OK] Localization Dictionary Check:", json.dumps(res, ensure_ascii=False))


if __name__ == "__main__":
    main()

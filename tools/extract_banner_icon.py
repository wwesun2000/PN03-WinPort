#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
extract_banner_icon.py - Decodes P.N.03 `opening.bnr` (GameCube BNR1 format):
  - Extracts 96x32 RGB5A3 4x4 tiled banner image (0x0020..0x1820, 6,144 bytes)
  - Extracts 6-language banner titles & descriptions (0x1820..0x1960)
  - Exports `re_data/opening_bnr_manifest.json` and optionally writes a 24-bit Windows `.bmp`
    banner when run locally against the user's ISO or extracted directory.
"""

import argparse
import glob
import hashlib
import json
import os
import struct
from typing import List, Optional, Tuple

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXTRACT_DIR = os.path.join(PROJECT_ROOT, "build", "extract")


def decode_rgb5a3_pixel(val: int) -> Tuple[int, int, int, int]:
    """Decodes a 16-bit GameCube RGB5A3 pixel into (R, G, B, A) 8-bit channels."""
    if val & 0x8000:
        # Opaque RGB555
        r = ((val >> 10) & 0x1F) * 255 // 31
        g = ((val >> 5) & 0x1F) * 255 // 31
        b = (val & 0x1F) * 255 // 31
        a = 255
    else:
        # Transparent A3RGB444
        a = ((val >> 12) & 0x07) * 255 // 7
        r = ((val >> 8) & 0x0F) * 255 // 15
        g = ((val >> 4) & 0x0F) * 255 // 15
        b = (val & 0x0F) * 255 // 15
    return r, g, b, a


def decode_bnr1(bnr_bytes: bytes) -> Tuple[dict, List[Tuple[int, int, int, int]]]:
    magic = bnr_bytes[:4].decode("ascii", "replace")
    # 96x32 image stored in 4x4 blocks (24 blocks wide x 8 blocks high)
    width, height = 96, 32
    pixels = [(0, 0, 0, 255)] * (width * height)
    pos = 0x20
    for by in range(0, height, 4):
        for bx in range(0, width, 4):
            for y in range(4):
                for x in range(4):
                    raw16 = struct.unpack(">H", bnr_bytes[pos : pos + 2])[0]
                    pos += 2
                    pixels[(by + y) * width + (bx + x)] = decode_rgb5a3_pixel(raw16)

    short_title = bnr_bytes[0x1820:0x1840].split(b"\x00")[0].decode("shift_jis", "replace")
    short_maker = bnr_bytes[0x1840:0x1860].split(b"\x00")[0].decode("shift_jis", "replace")
    long_title  = bnr_bytes[0x1860:0x18A0].split(b"\x00")[0].decode("shift_jis", "replace")
    long_maker  = bnr_bytes[0x18A0:0x18E0].split(b"\x00")[0].decode("shift_jis", "replace")
    description = bnr_bytes[0x18E0:0x1960].split(b"\x00")[0].decode("shift_jis", "replace")

    rgba_bytes = bytes(c for px in pixels for c in px)
    info = {
        "magic": magic,
        "file_size_bytes": len(bnr_bytes),
        "icon_width": width,
        "icon_height": height,
        "icon_encoding": "GameCube 4x4 Tiled RGB5A3 (0x0020..0x1820)",
        "decoded_rgba_sha256": hashlib.sha256(rgba_bytes).hexdigest(),
        "short_title": short_title,
        "short_maker": short_maker,
        "long_title": long_title,
        "long_maker": long_maker,
        "description": description,
    }
    return info, pixels


def auto_discover_iso(root_dir: str = PROJECT_ROOT) -> Optional[str]:
    patterns = ["*.iso", "*.gcm", "*.ISO", "*.GCM"]
    candidates: List[str] = []
    for pat in patterns:
        candidates.extend(glob.glob(os.path.join(root_dir, pat)))
    candidates = sorted(set(candidates))
    return candidates[0] if candidates else None


def read_file_from_iso(iso_path: str, target_fst_path: str = "/opening.bnr") -> bytes:
    """Reads a file cleanly from GameCube ISO/GCM/NKit-ISO via FST."""
    target_norm = "/" + target_fst_path.lstrip("/").lower()
    with open(iso_path, "rb") as iso:
        boot = iso.read(0x440)
        if len(boot) < 0x440:
            raise ValueError(f"ISO header truncated: {iso_path}")
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
            elif path.lower() == target_norm:
                iso.seek(off_or_p)
                return iso.read(sz_or_n)
    raise FileNotFoundError(f"{target_fst_path} not found in ISO: {iso_path}")


def write_bmp_24(path: str, width: int, height: int, rgba_pixels: List[Tuple[int, int, int, int]]) -> None:
    """Writes a standard top-down / standard bottom-up 24-bit Windows BMP (zero external deps)."""
    row_stride = (width * 3 + 3) & ~3
    pixel_data_size = row_stride * height
    file_size = 54 + pixel_data_size
    bmp_header = struct.pack("<2sIHHI", b"BM", file_size, 0, 0, 54)
    dib_header = struct.pack("<IIIHHIIIIII", 40, width, height, 1, 24, 0, pixel_data_size, 2835, 2835, 0, 0)
    rows = bytearray()
    pad = b"\x00" * (row_stride - width * 3)
    for y in range(height - 1, -1, -1):
        row = bytearray()
        for x in range(width):
            r, g, b, a = rgba_pixels[y * width + x]
            if a < 255:
                r = (r * a) // 255
                g = (g * a) // 255
                b = (b * a) // 255
            row.extend((b, g, r))
        rows.extend(row)
        rows.extend(pad)
    os.makedirs(os.path.dirname(os.path.abspath(path)), exist_ok=True)
    with open(path, "wb") as f:
        f.write(bmp_header + dib_header + rows)


def make_32x32_icon_from_96x32(rgba_pixels: List[Tuple[int, int, int, int]]) -> List[Tuple[int, int, int, int]]:
    """Generates a 32x32 icon by averaging each 3x1 horizontal triplet into a crisp 32x16 badge centered on 32x32 dark panel."""
    out = [(10, 15, 22, 255)] * (32 * 32)
    for dst_y in range(32):
        # Map 32x32 rows [8..23] -> 16 rows downsampled 2x vertically from 32 rows
        if 8 <= dst_y < 24:
            src_y0 = (dst_y - 8) * 2
            src_y1 = src_y0 + 1
            for dst_x in range(32):
                r_acc = g_acc = b_acc = 0
                for sy in (src_y0, src_y1):
                    for sx in (dst_x * 3, dst_x * 3 + 1, dst_x * 3 + 2):
                        r, g, b, a = rgba_pixels[sy * 96 + sx]
                        r_acc += (r * a) // 255
                        g_acc += (g * a) // 255
                        b_acc += (b * a) // 255
                out[dst_y * 32 + dst_x] = (r_acc // 6, g_acc // 6, b_acc // 6, 255)
    return out


def main():
    parser = argparse.ArgumentParser(description="Decode P.N.03 opening.bnr BNR1 icon and metadata")
    parser.add_argument("--iso", default="", help="Path to P.N.03 .iso/.gcm (auto-detected if omitted)")
    parser.add_argument("--bnr", default="", help="Optional path to extracted opening.bnr")
    parser.add_argument("--out-json", default=os.path.join(PROJECT_ROOT, "re_data", "opening_bnr_manifest.json"))
    parser.add_argument("--out-banner-bmp", default=os.path.join(PROJECT_ROOT, "assets", "ui", "pn03_banner_96x32.bmp"))
    parser.add_argument("--out-icon-bmp", default=os.path.join(PROJECT_ROOT, "assets", "ui", "pn03_icon_32x32.bmp"))
    args = parser.parse_args()

    bnr_bytes = None
    source_desc = ""
    if args.bnr and os.path.isfile(args.bnr):
        with open(args.bnr, "rb") as f:
            bnr_bytes = f.read()
        source_desc = args.bnr
    else:
        iso_path = args.iso if args.iso else auto_discover_iso()
        if not iso_path or not os.path.isfile(iso_path):
            raise FileNotFoundError("No opening.bnr or root .iso/.gcm image found.")
        bnr_bytes = read_file_from_iso(iso_path, "/opening.bnr")
        source_desc = f"{iso_path}::/opening.bnr"

    info, pixels = decode_bnr1(bnr_bytes)
    os.makedirs(os.path.dirname(os.path.abspath(args.out_json)), exist_ok=True)
    with open(args.out_json, "w", encoding="utf-8") as f:
        json.dump(info, f, indent=2, ensure_ascii=False)

    write_bmp_24(args.out_banner_bmp, 96, 32, pixels)
    icon_pixels = make_32x32_icon_from_96x32(pixels)
    write_bmp_24(args.out_icon_bmp, 32, 32, icon_pixels)

    print(f"[OK] Decoded opening.bnr from {source_desc} ({info['icon_width']}x{info['icon_height']} RGB5A3, sha256={info['decoded_rgba_sha256'][:16]}...)")
    print(f"[OK] Manifest -> {args.out_json}")
    print(f"[OK] Banner BMP -> {args.out_banner_bmp}")
    print(f"[OK] Icon BMP   -> {args.out_icon_bmp}")


if __name__ == "__main__":
    main()

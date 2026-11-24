#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
End-to-End Python Verification Suite for P.N.03 (GPNE08) Windows Port & Static Recompiler
"""

import glob
import json
import os
import subprocess
import sys
import unittest

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUILD_BIN_DIR = os.path.join(PROJECT_ROOT, "build", "Release")
EXE_EXT = ".exe" if os.name == "nt" else ""


def auto_discover_iso() -> str:
    candidates = []
    for pat in ("*.iso", "*.gcm", "*.ISO", "*.GCM"):
        candidates.extend(glob.glob(os.path.join(PROJECT_ROOT, pat)))
    candidates = sorted(set(candidates))
    return candidates[0] if candidates else ""


class TestPN03StaticRecompAndRuntime(unittest.TestCase):
    def test_01_manifests_symbols_vtables_and_bnr(self):
        sym_path = os.path.join(PROJECT_ROOT, "re_data", "meka_symbols_full.json")
        fst_path = os.path.join(PROJECT_ROOT, "re_data", "fst_manifest.json")
        rel_path = os.path.join(PROJECT_ROOT, "re_data", "tools_rel_manifest.json")
        vt_path  = os.path.join(PROJECT_ROOT, "re_data", "vtables_and_ctors.json")
        bnr_path = os.path.join(PROJECT_ROOT, "re_data", "opening_bnr_manifest.json")

        for p in (sym_path, fst_path, rel_path, vt_path, bnr_path):
            self.assertTrue(os.path.exists(p), f"Missing {p}")

        with open(sym_path, "r", encoding="utf-8") as f:
            sym = json.load(f)
        with open(fst_path, "r", encoding="utf-8") as f:
            fst = json.load(f)
        with open(rel_path, "r", encoding="utf-8") as f:
            rel = json.load(f)
        with open(vt_path, "r", encoding="utf-8") as f:
            vt = json.load(f)
        with open(bnr_path, "r", encoding="utf-8") as f:
            bnr = json.load(f)

        self.assertEqual(sym["game_id"], "GPNE08")
        self.assertEqual(sym["total_symbols"], 9530)
        self.assertEqual(sym["code_function_count"], 6353)
        self.assertEqual(fst["file_count"], 700)
        self.assertEqual(fst["directory_count"], 25)
        self.assertEqual(rel["num_sections"], 24)
        self.assertEqual(rel["main_dol_import_relocations_count"], 593)
        self.assertEqual(rel["internal_self_relocations_count"], 1499)
        self.assertEqual(vt["vtable_count"], 150)
        self.assertEqual(vt["ctor_count"], 48)
        self.assertEqual(bnr["magic"], "BNR1")
        self.assertEqual(bnr["icon_width"], 96)
        self.assertEqual(bnr["icon_height"], 32)

    def test_02_lifted_and_hl_decompiled_sources_exist(self):
        subsys_dir = os.path.join(PROJECT_ROOT, "src", "decompiled", "subsystems")
        files = sorted(os.listdir(subsys_dir))
        self.assertEqual(len(files), 9)
        for fname in files:
            self.assertTrue(os.path.getsize(os.path.join(subsys_dir, fname)) > 100_000)

        hl_dir = os.path.join(PROJECT_ROOT, "src", "decompiled_hl")
        hl_files = sorted(os.listdir(hl_dir))
        self.assertEqual(len(hl_files), 14)

        tools_rel_cpp = os.path.join(PROJECT_ROOT, "src", "decompiled", "tools_rel_decompiled.cpp")
        self.assertTrue(os.path.exists(tools_rel_cpp))
        self.assertTrue(os.path.getsize(tools_rel_cpp) > 100_000)

    def test_03_localization_dictionary(self):
        zh_path = os.path.join(PROJECT_ROOT, "assets", "locales", "zh_CN.json")
        with open(zh_path, "r", encoding="utf-8") as f:
            zh = json.load(f)
        self.assertEqual(zh["locale"], "zh_CN")
        self.assertEqual(zh["game_id"], "GPNE08")
        self.assertIn("PAPILLON SUIT", zh)

    def test_04_cpp_executable_and_test_runner(self):
        test_bin = os.path.join(BUILD_BIN_DIR, f"pn03_cpp_tests{EXE_EXT}")
        app_bin = os.path.join(BUILD_BIN_DIR, f"PN03_WinPort{EXE_EXT}")
        self.assertTrue(os.path.exists(test_bin), f"Missing {test_bin}")
        self.assertTrue(os.path.exists(app_bin), f"Missing {app_bin}")

        iso_path = auto_discover_iso()
        self.assertTrue(bool(iso_path) and os.path.exists(iso_path), f"Missing root ISO/GCM in {PROJECT_ROOT}")

        res_test = subprocess.run(
            [test_bin, iso_path], cwd=PROJECT_ROOT, capture_output=True, text=True, encoding="utf-8", check=True
        )
        self.assertIn("ALL C++20 RUNTIME & STATIC RECOMPILATION TESTS PASSED (28/28)!", res_test.stdout)

        res_self = subprocess.run(
            [app_bin, "--self-test", "--iso", iso_path],
            cwd=PROJECT_ROOT, capture_output=True, text=True, encoding="utf-8", check=True,
        )
        self.assertIn("Mounted Game ID: GPNE08", res_self.stdout)
        self.assertIn("static recomp dispatch OK", res_self.stdout)

        res_app = subprocess.run(
            [app_bin, "--no-gui", "--iso", iso_path, "--frames", "10"],
            cwd=PROJECT_ROOT, capture_output=True, text=True, encoding="utf-8", check=True,
        )
        self.assertIn("Mounted Game ID: GPNE08", res_app.stdout)
        self.assertIn("Executed 10 HD frames at 1920x1080", res_app.stdout)

    def test_05_debug_mcp_server_stdio(self):
        mcp_script = os.path.join(PROJECT_ROOT, "tools", "pn03_debug_mcp.py")
        self.assertTrue(os.path.exists(mcp_script), f"Missing {mcp_script}")

        requests = [
            {
                "jsonrpc": "2.0",
                "id": 1,
                "method": "initialize",
                "params": {"protocolVersion": "2024-11-05", "capabilities": {}, "clientInfo": {"name": "unittest", "version": "1.0"}},
            },
            {"jsonrpc": "2.0", "method": "notifications/initialized"},
            {"jsonrpc": "2.0", "id": 2, "method": "tools/list", "params": {}},
            {"jsonrpc": "2.0", "id": 3, "method": "tools/call", "params": {"name": "pn03_status", "arguments": {}}},
            {"jsonrpc": "2.0", "id": 4, "method": "tools/call", "params": {"name": "pn03_lookup_symbol", "arguments": {"query": "CalcSk1"}}},
        ]

        # Frame requests using Content-Length (LSP/MCP standard) and verify responses
        stdin_bytes = b""
        for req in requests:
            body = json.dumps(req, ensure_ascii=False).encode("utf-8")
            stdin_bytes += f"Content-Length: {len(body)}\r\n\r\n".encode("ascii") + body

        proc = subprocess.run(
            [sys.executable, mcp_script],
            cwd=PROJECT_ROOT,
            input=stdin_bytes,
            capture_output=True,
            timeout=30,
            check=True,
        )

        # Parse Content-Length framed JSON-RPC responses
        raw = proc.stdout
        pos = 0
        responses = {}
        while pos < len(raw):
            hdr_end = raw.find(b"\r\n\r\n", pos)
            self.assertNotEqual(hdr_end, -1, f"Malformed LSP header at offset {pos}: {raw[pos:pos+120]!r}")
            hdr = raw[pos:hdr_end].decode("ascii")
            clen = None
            for line in hdr.splitlines():
                if line.lower().startswith("content-length:"):
                    clen = int(line.split(":", 1)[1].strip())
            self.assertIsNotNone(clen, f"Missing Content-Length in {hdr!r}")
            body_start = hdr_end + 4
            body_end = body_start + clen
            msg = json.loads(raw[body_start:body_end].decode("utf-8"))
            responses[msg["id"]] = msg
            pos = body_end

        self.assertEqual(set(responses.keys()), {1, 2, 3, 4})
        self.assertEqual(responses[1]["result"]["serverInfo"]["name"], "pn03-debug")
        tool_names = {t["name"] for t in responses[2]["result"]["tools"]}
        self.assertTrue({"pn03_status", "pn03_read_logs", "pn03_build", "pn03_run_probe",
                         "pn03_lookup_symbol", "pn03_inspect_decompiled", "pn03_search_iso_fst",
                         "pn03_run_tests"}.issubset(tool_names))
        status_payload = json.loads(responses[3]["result"]["content"][0]["text"])
        self.assertIn("binaries", status_payload)
        self.assertTrue(status_payload["binaries"]["build/Release/PN03_WinPort.exe"]["exists"])
        sym_payload = json.loads(responses[4]["result"]["content"][0]["text"])
        self.assertGreaterEqual(len(sym_payload["registry_matches"]), 1)
        self.assertTrue(any("CalcSk1" in m["entry"] for m in sym_payload["registry_matches"]))

    def test_06_hle_entry_point_audit_zero_non_entry(self):
        import re

        sym_path = os.path.join(PROJECT_ROOT, "re_data", "meka_symbols_full.json")
        with open(sym_path, "r", encoding="utf-8") as f:
            sym_data = json.load(f)
        entries = {s["address"] for s in sym_data["symbols"] if s.get("section") == ".text"}
        self.assertGreater(len(entries), 6000)

        runtime_files = [
            os.path.join("src", "runtime", "gx_3d_interface.cpp"),
            os.path.join("src", "runtime", "audio_ax_hle.cpp"),
            os.path.join("src", "runtime", "dolphin_sdk_hle.cpp"),
        ]
        case_re = re.compile(r"case\s+(0x80[0-9A-Fa-f]{6})u?\s*:")
        for rel_path in runtime_files:
            full_path = os.path.join(PROJECT_ROOT, rel_path)
            with open(full_path, "r", encoding="utf-8") as f:
                src = f.read()
            non_entry = [
                hex(int(m, 16))
                for m in case_re.findall(src)
                if 0x800034C0 <= int(m, 16) < 0x80162200 and int(m, 16) not in entries
            ]
            self.assertEqual(non_entry, [], f"Non-entry HLE switch hooks found in {rel_path}: {non_entry}")

    def test_07_localization_dict_and_glyph_sanitization(self):
        import re

        zh_path = os.path.join(PROJECT_ROOT, "assets", "locales", "zh_CN.json")
        tool_path = os.path.join(PROJECT_ROOT, "tools", "pn03_loc_tool.py")
        csv_path = os.path.join(PROJECT_ROOT, "assets", "locales", "zh_CN_translation_sheet.csv")

        res = subprocess.run(
            [sys.executable, tool_path, "--verify-dict", zh_path],
            cwd=PROJECT_ROOT,
            capture_output=True,
            text=True,
            encoding="utf-8",
            check=True,
        )
        json_start = res.stdout.find("{")
        self.assertNotEqual(json_start, -1, res.stdout)
        verify_payload = json.loads(res.stdout[json_start:])
        self.assertTrue(verify_payload["valid"])
        self.assertEqual(verify_payload["placeholder_errors"], [])
        self.assertGreaterEqual(verify_payload["total_translations"], 380)

        with open(zh_path, "r", encoding="utf-8") as f:
            zh = json.load(f)
        self.assertIn("NEW GAME", zh)
        self.assertIn("PAPILLON SUIT", zh)
        leaks = [k for k in zh if re.search(r"<(84|94|9d)>", k, re.IGNORECASE)]
        self.assertEqual(leaks, [], f"Garbled glyph tag leaks found in zh_CN.json keys: {leaks}")
        self.assertTrue(os.path.exists(csv_path) and os.path.getsize(csv_path) > 1024)

    def test_08_vulkan_backend_e2e_frame_dump(self):
        import struct
        import tempfile

        app_bin = os.path.join(BUILD_BIN_DIR, f"PN03_WinPort{EXE_EXT}")
        iso_path = auto_discover_iso()
        self.assertTrue(os.path.exists(app_bin), f"Missing {app_bin}")
        self.assertTrue(bool(iso_path) and os.path.exists(iso_path), f"Missing root ISO/GCM in {PROJECT_ROOT}")

        with tempfile.TemporaryDirectory(prefix="pn03_vk_e2e_") as tmp_dir:
            dump_path = os.path.join(tmp_dir, "f150_vulkan.bmp")
            res = subprocess.run(
                [
                    app_bin,
                    "--backend", "vulkan",
                    "--no-gui",
                    "--auto-start",
                    "--no-limit",
                    "--iso", iso_path,
                    "--frames", "150",
                    "--dump-frame", dump_path,
                ],
                cwd=PROJECT_ROOT,
                capture_output=True,
                text=True,
                encoding="utf-8",
                timeout=120,
                check=True,
            )
            self.assertIn("Mounted Game ID: GPNE08", res.stdout)
            self.assertIn("Executed 150 HD frames", res.stdout)
            self.assertTrue(os.path.exists(dump_path), f"Missing dumped Vulkan BMP at {dump_path}")

            with open(dump_path, "rb") as f:
                data = f.read()
            self.assertGreater(len(data), 54)
            self.assertEqual(data[:2], b"BM")
            width, height = struct.unpack_from("<ii", data, 18)
            self.assertGreater(width, 0)
            self.assertNotEqual(height, 0)
            pixels = data[54:]
            # Confirm real framebuffer content was rendered rather than a blank uniform surface
            self.assertGreater(len(set(pixels[::97])), 3)


if __name__ == "__main__":
    unittest.main(verbosity=2)

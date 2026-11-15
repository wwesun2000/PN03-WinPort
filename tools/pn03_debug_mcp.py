#!/usr/bin/env python3
"""
P.N.03 (GPNE08) Windows Port Debug & Reverse-Engineering MCP Server (Stdio JSON-RPC 2.0).

Supports both newline-delimited JSON-RPC (MCP 2025-03-26 / Antigravity) and
Content-Length framed JSON-RPC over stdin/stdout so it works across all MCP hosts.
Zero third-party Python package dependencies (stdlib only).
"""

from __future__ import annotations

import json
import os
import re
import subprocess
import sys
import traceback
from pathlib import Path
from typing import Any

SERVER_INFO = {
    "name": "pn03-debug",
    "version": "1.0.0",
}
PROTOCOL_VERSIONS = ("2025-03-26", "2024-11-05")

REPO_ROOT = Path(__file__).resolve().parent.parent


def _resolve_repo_path(rel_or_abs: str) -> Path:
    p = Path(rel_or_abs)
    if not p.is_absolute():
        p = (REPO_ROOT / p).resolve()
    else:
        p = p.resolve()
    try:
        p.relative_to(REPO_ROOT.resolve())
    except ValueError as exc:
        raise ValueError(f"Path outside repository root: {rel_or_abs}") from exc
    return p


def _tool_pn03_status(_args: dict[str, Any]) -> dict[str, Any]:
    git_info: dict[str, Any] = {}
    try:
        branch = subprocess.check_output(
            ["git", "rev-parse", "--abbrev-ref", "HEAD"],
            cwd=REPO_ROOT, text=True, stderr=subprocess.STDOUT, timeout=5
        ).strip()
        head = subprocess.check_output(
            ["git", "log", "-1", "--oneline"],
            cwd=REPO_ROOT, text=True, stderr=subprocess.STDOUT, timeout=5
        ).strip()
        dirty_lines = subprocess.check_output(
            ["git", "status", "-s"],
            cwd=REPO_ROOT, text=True, stderr=subprocess.STDOUT, timeout=5
        ).splitlines()
        git_info = {
            "branch": branch,
            "head": head,
            "dirty_count": len(dirty_lines),
            "dirty_preview": dirty_lines[:30],
        }
    except Exception as e:
        git_info = {"error": str(e)}

    binaries = {}
    for rel in ("build/Release/PN03_WinPort.exe", "build/Release/pn03_cpp_tests.exe"):
        bp = REPO_ROOT / rel
        if bp.exists():
            st = bp.stat()
            binaries[rel] = {"exists": True, "size_bytes": st.st_size, "mtime": st.st_mtime}
        else:
            binaries[rel] = {"exists": False}

    cfg_path = REPO_ROOT / "config/pn03_settings.json"
    config_data: Any = {}
    if cfg_path.exists():
        try:
            config_data = json.loads(cfg_path.read_text(encoding="utf-8"))
        except Exception as e:
            config_data = {"parse_error": str(e)}

    log_dir = REPO_ROOT / str(config_data.get("log_dir", "logs") if isinstance(config_data, dict) else "logs")
    logs_info = []
    total_log_bytes = 0
    if log_dir.exists():
        for lp in sorted(log_dir.glob("*.log"), key=lambda p: p.stat().st_mtime, reverse=True):
            sz = lp.stat().st_size
            total_log_bytes += sz
            logs_info.append({"name": lp.name, "size_bytes": sz, "mtime": lp.stat().st_mtime})

    isos = [p.name for p in REPO_ROOT.iterdir() if p.is_file() and p.suffix.lower() in (".iso", ".gcm")]

    return {
        "repo_root": str(REPO_ROOT),
        "git": git_info,
        "binaries": binaries,
        "isos_in_root": isos,
        "config": config_data,
        "logs": {
            "dir": str(log_dir),
            "total_bytes": total_log_bytes,
            "file_count": len(logs_info),
            "files": logs_info[:20],
        },
    }


def _tool_pn03_read_logs(args: dict[str, Any]) -> dict[str, Any]:
    file_name = str(args.get("file", "pn03_runtime.log"))
    tail = max(1, min(int(args.get("tail", 120)), 2000))
    level_filter = str(args.get("level", "")).strip().upper()
    cat_filter = str(args.get("category", "")).strip().lower()
    pattern = str(args.get("pattern", "")).strip()
    frame_min = args.get("frame_min")
    frame_max = args.get("frame_max")

    cfg_log_dir = "logs"
    cfg_path = REPO_ROOT / "config/pn03_settings.json"
    if cfg_path.exists():
        try:
            cfg_log_dir = json.loads(cfg_path.read_text(encoding="utf-8")).get("log_dir", "logs")
        except Exception:
            pass

    target = _resolve_repo_path(str(Path(cfg_log_dir) / file_name))
    if not target.exists():
        return {"exists": False, "path": str(target), "lines": []}

    rx = re.compile(pattern, re.IGNORECASE) if pattern else None
    frame_rx = re.compile(r"\[f=(\d+)\]")

    matched: list[str] = []
    total_lines = 0
    with target.open("r", encoding="utf-8", errors="replace") as f:
        for line in f:
            total_lines += 1
            s = line.rstrip("\r\n")
            if level_filter and f"[{level_filter}" not in s.upper():
                continue
            if cat_filter and cat_filter not in s.lower():
                continue
            if frame_min is not None or frame_max is not None:
                m = frame_rx.search(s)
                if not m:
                    continue
                fr = int(m.group(1))
                if frame_min is not None and fr < int(frame_min):
                    continue
                if frame_max is not None and fr > int(frame_max):
                    continue
            if rx and not rx.search(s):
                continue
            matched.append(s)

    return {
        "exists": True,
        "path": str(target),
        "total_lines": total_lines,
        "matched_count": len(matched),
        "lines": matched[-tail:],
    }


def _tool_pn03_build(args: dict[str, Any]) -> dict[str, Any]:
    target = str(args.get("target", "all"))
    clean_config = bool(args.get("reconfigure", False))
    timeout_sec = max(10, min(int(args.get("timeout_sec", 240)), 600))

    sln_exists = (REPO_ROOT / "build/PN03_WinPort.sln").exists()
    if clean_config or not sln_exists:
        cmd = ["cmd", "/c", "scripts\\build_windows_port.bat"]
    else:
        vs_cmake = Path(r"C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe")
        cmake_bin = str(vs_cmake) if vs_cmake.exists() else "cmake"
        cmd = [cmake_bin, "--build", "build", "--config", "Release", "--parallel"]
        if target in ("PN03_WinPort", "pn03_cpp_tests"):
            cmd += ["--target", target]

    try:
        proc = subprocess.run(
            cmd, cwd=REPO_ROOT, capture_output=True, text=True,
            encoding="utf-8", errors="replace", timeout=timeout_sec
        )
        combined = (proc.stdout + "\n" + proc.stderr).splitlines()
        errors = [l for l in combined if "error " in l.lower() or "fatal error" in l.lower()]
        return {
            "returncode": proc.returncode,
            "success": proc.returncode == 0,
            "error_lines": errors[:50],
            "output_tail": combined[-60:],
        }
    except subprocess.TimeoutExpired as exc:
        return {
            "returncode": -1,
            "success": False,
            "timeout": True,
            "timeout_sec": timeout_sec,
            "output_tail": (exc.stdout or "").splitlines()[-40:] if isinstance(exc.stdout, str) else [],
        }


def _tool_pn03_run_probe(args: dict[str, Any]) -> dict[str, Any]:
    frames = max(1, min(int(args.get("frames", 60)), 50000))
    auto_start = bool(args.get("auto_start", False))
    trace = bool(args.get("trace", False))
    trace_from = args.get("trace_from")
    log_level = str(args.get("log_level", "info"))
    dump_frame = str(args.get("dump_frame", "")).strip()
    timeout_sec = max(2, min(int(args.get("timeout_sec", 15)), 120))

    exe = REPO_ROOT / "build/Release/PN03_WinPort.exe"
    if not exe.exists():
        return {"error": f"Executable not found: {exe}. Run pn03_build first."}

    cmd = [str(exe), "--no-gui", "--frames", str(frames), "--log-level", log_level]
    if auto_start:
        cmd.append("--auto-start")
    if trace:
        cmd.append("--trace")
    if trace_from is not None:
        cmd += ["--trace-from", str(int(trace_from))]
    if dump_frame:
        dp = _resolve_repo_path(dump_frame)
        cmd += ["--dump-frame", str(dp)]

    timed_out = False
    stdout_s = ""
    stderr_s = ""
    rc = -1
    try:
        proc = subprocess.run(
            cmd, cwd=REPO_ROOT, capture_output=True, text=True,
            encoding="utf-8", errors="replace", timeout=timeout_sec
        )
        rc = proc.returncode
        stdout_s = proc.stdout
        stderr_s = proc.stderr
    except subprocess.TimeoutExpired as exc:
        timed_out = True
        stdout_s = exc.stdout.decode("utf-8", "replace") if isinstance(exc.stdout, bytes) else (exc.stdout or "")
        stderr_s = exc.stderr.decode("utf-8", "replace") if isinstance(exc.stderr, bytes) else (exc.stderr or "")

    log_tail = _tool_pn03_read_logs({"tail": 80}).get("lines", [])
    return {
        "cmd": " ".join(cmd),
        "timed_out": timed_out,
        "returncode": rc,
        "stdout_tail": stdout_s.splitlines()[-40:],
        "stderr_tail": stderr_s.splitlines()[-60:],
        "log_tail": log_tail,
    }


def _tool_pn03_lookup_symbol(args: dict[str, Any]) -> dict[str, Any]:
    query = str(args.get("query", "")).strip()
    limit = max(1, min(int(args.get("limit", 30)), 200))
    find_callers = bool(args.get("find_callers", True))
    if not query:
        return {"error": "query is required"}

    reg_path = REPO_ROOT / "src/decompiled/function_table_registry.cpp"
    matches = []
    if reg_path.exists():
        q_low = query.lower()
        for idx, line in enumerate(reg_path.read_text(encoding="utf-8", errors="replace").splitlines(), 1):
            if q_low in line.lower():
                matches.append({"line": idx, "entry": line.strip()})
                if len(matches) >= limit:
                    break

    callers: list[str] = []
    hex_m = re.search(r"(?:0x)?(8[01][0-9a-fA-F]{6})", query)
    if find_callers and hex_m:
        addr_hex = hex_m.group(1).upper()
        for cpp in sorted((REPO_ROOT / "src/decompiled").rglob("*.cpp")):
            if cpp.name in ("function_table_registry.cpp", "indirect_call_table.cpp"):
                continue
            for idx, line in enumerate(cpp.read_text(encoding="utf-8", errors="replace").splitlines(), 1):
                if addr_hex in line.upper():
                    rel = cpp.relative_to(REPO_ROOT)
                    callers.append(f"{rel}:{idx}: {line.strip()[:120]}")
                    if len(callers) >= limit:
                        break
            if len(callers) >= limit:
                break

    return {"query": query, "registry_matches": matches, "callers": callers}


def _tool_pn03_inspect_decompiled(args: dict[str, Any]) -> dict[str, Any]:
    query = str(args.get("target", "")).strip()
    max_lines = max(10, min(int(args.get("max_lines", 140)), 400))
    if not query:
        return {"error": "target (hex address like 0x800C2EBC or symbol name) is required"}

    q_clean = query.lower().removeprefix("0x")
    hdr_rx = re.compile(r"^//\s*\[(0x[0-9A-Fa-f]{8})\]\s+(.*)$")
    search_files = sorted((REPO_ROOT / "src/decompiled/subsystems").glob("*.cpp"))
    search_files.append(REPO_ROOT / "src/decompiled/tools_rel_decompiled.cpp")

    for fp in search_files:
        if not fp.exists():
            continue
        lines = fp.read_text(encoding="utf-8", errors="replace").splitlines()
        for i, line in enumerate(lines):
            m = hdr_rx.match(line)
            if m and (q_clean == m.group(1).lower().removeprefix("0x") or query.lower() in m.group(2).lower()):
                end_idx = min(len(lines), i + max_lines)
                for j in range(i + 2, end_idx):
                    if lines[j].startswith("// [0x"):
                        end_idx = j
                        break
                return {
                    "file": str(fp.relative_to(REPO_ROOT)),
                    "start_line": i + 1,
                    "end_line": end_idx,
                    "header": line,
                    "code": "\n".join(f"{k + 1}: {lines[k]}" for k in range(i, end_idx)),
                }

    return {"found": False, "target": query}


def _tool_pn03_search_iso_fst(args: dict[str, Any]) -> dict[str, Any]:
    pattern = str(args.get("pattern", "")).strip().lower()
    limit = max(1, min(int(args.get("limit", 60)), 500))
    fst_path = REPO_ROOT / "re_data/fst_manifest.json"
    if not fst_path.exists():
        return {"error": "re_data/fst_manifest.json not found"}
    data = json.loads(fst_path.read_text(encoding="utf-8"))
    entries = data if isinstance(data, list) else data.get("entries", data.get("files", []))
    hits = []
    for e in entries:
        text = json.dumps(e, ensure_ascii=False).lower()
        if not pattern or pattern in text:
            hits.append(e)
            if len(hits) >= limit:
                break
    return {"total_entries": len(entries), "matched_shown": len(hits), "entries": hits}


def _tool_pn03_run_tests(args: dict[str, Any]) -> dict[str, Any]:
    suite = str(args.get("suite", "all"))
    py = sys.executable
    results: dict[str, Any] = {}

    def run_step(name: str, cmd: list[str], timeout_sec: int = 60) -> None:
        proc = subprocess.run(
            cmd, cwd=REPO_ROOT, capture_output=True, text=True,
            encoding="utf-8", errors="replace", timeout=timeout_sec
        )
        results[name] = {
            "returncode": proc.returncode,
            "passed": proc.returncode == 0,
            "stdout": proc.stdout.splitlines()[-40:],
            "stderr": proc.stderr.splitlines()[-30:],
        }

    if suite in ("all", "cpp"):
        run_step("pn03_cpp_tests", [str(REPO_ROOT / "build/Release/pn03_cpp_tests.exe")])
    if suite in ("all", "self_test"):
        run_step("winport_self_test", [str(REPO_ROOT / "build/Release/PN03_WinPort.exe"), "--self-test", "--no-gui"])
    if suite in ("all", "python"):
        run_step("python_unittest", [py, "-m", "unittest", "discover", "-s", "tests", "-p", "test_*.py", "-v"])
    if suite in ("all", "loc"):
        run_step("loc_verify_dict", [py, "tools/pn03_loc_tool.py", "--verify-dict", "assets/locales/zh_CN.json"])

    all_ok = bool(results) and all(v.get("passed", False) for v in results.values())
    return {"all_passed": all_ok, "results": results}


TOOLS_SPEC = [
    {
        "name": "pn03_status",
        "description": "Inspect PN03 repo git status, compiled binaries, mounted ISO, config, and rotating log files.",
        "inputSchema": {"type": "object", "properties": {}},
    },
    {
        "name": "pn03_read_logs",
        "description": "Tail or filter PN03 runtime rotating logs by level, category, regex pattern, or frame range.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "file": {"type": "string", "default": "pn03_runtime.log"},
                "tail": {"type": "integer", "default": 120},
                "level": {"type": "string", "description": "TRACE, DEBUG, INFO, WARN, ERROR"},
                "category": {"type": "string", "description": "OSReport, CALL, DVD, BOOT, HLE, D3D11, LAUNCHER"},
                "pattern": {"type": "string", "description": "Regex filter"},
                "frame_min": {"type": "integer"},
                "frame_max": {"type": "integer"},
            },
        },
    },
    {
        "name": "pn03_build",
        "description": "Build PN03 Windows x64 Release binaries (incremental CMake or full VS2022 bat).",
        "inputSchema": {
            "type": "object",
            "properties": {
                "target": {"type": "string", "enum": ["all", "PN03_WinPort", "pn03_cpp_tests"], "default": "all"},
                "reconfigure": {"type": "boolean", "default": False},
                "timeout_sec": {"type": "integer", "default": 240},
            },
        },
    },
    {
        "name": "pn03_run_probe",
        "description": "Run headless PN03_WinPort frame probe with timeout, optional auto-start/trace/dump-frame, returning stdout/stderr and rotating log tail.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "frames": {"type": "integer", "default": 60},
                "auto_start": {"type": "boolean", "default": False},
                "trace": {"type": "boolean", "default": False},
                "trace_from": {"type": "integer"},
                "log_level": {"type": "string", "default": "info"},
                "dump_frame": {"type": "string", "description": "Optional BMP output path inside repo, e.g. build/probe.bmp"},
                "timeout_sec": {"type": "integer", "default": 15},
            },
        },
    },
    {
        "name": "pn03_lookup_symbol",
        "description": "Look up GameCube MEKA symbol or PPC address in function_table_registry and locate callers.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "query": {"type": "string"},
                "limit": {"type": "integer", "default": 30},
                "find_callers": {"type": "boolean", "default": True},
            },
            "required": ["query"],
        },
    },
    {
        "name": "pn03_inspect_decompiled",
        "description": "Read a decompiled PPC function from src/decompiled/subsystems by hex address or symbol substring.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "target": {"type": "string"},
                "max_lines": {"type": "integer", "default": 140},
            },
            "required": ["target"],
        },
    },
    {
        "name": "pn03_search_iso_fst",
        "description": "Search GameCube FST manifest entries (stages, rooms, .lze, .rel, sounds) in re_data/fst_manifest.json.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "pattern": {"type": "string", "default": ""},
                "limit": {"type": "integer", "default": 60},
            },
        },
    },
    {
        "name": "pn03_run_tests",
        "description": "Run PN03 C++ unit tests, --self-test, Python unittests, or localization dictionary checks.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "suite": {"type": "string", "enum": ["all", "cpp", "self_test", "python", "loc"], "default": "all"},
            },
        },
    },
]

TOOL_DISPATCH = {
    "pn03_status": _tool_pn03_status,
    "pn03_read_logs": _tool_pn03_read_logs,
    "pn03_build": _tool_pn03_build,
    "pn03_run_probe": _tool_pn03_run_probe,
    "pn03_lookup_symbol": _tool_pn03_lookup_symbol,
    "pn03_inspect_decompiled": _tool_pn03_inspect_decompiled,
    "pn03_search_iso_fst": _tool_pn03_search_iso_fst,
    "pn03_run_tests": _tool_pn03_run_tests,
}


def _read_message(stream: Any) -> tuple[dict[str, Any] | None, str]:
    while True:
        first_line = stream.readline()
        if not first_line:
            return None, "ndjson"
        if first_line in (b"\r\n", b"\n"):
            continue
        if first_line.lower().startswith(b"content-length:"):
            length = int(first_line.split(b":", 1)[1].strip())
            while True:
                hdr = stream.readline()
                if not hdr or hdr in (b"\r\n", b"\n"):
                    break
            body = stream.read(length)
            return json.loads(body.decode("utf-8")), "lsp"
        return json.loads(first_line.decode("utf-8")), "ndjson"


def _write_message(stream: Any, payload: dict[str, Any], framing: str) -> None:
    encoded = json.dumps(payload, ensure_ascii=False).encode("utf-8")
    if framing == "lsp":
        header = f"Content-Length: {len(encoded)}\r\n\r\n".encode("ascii")
        stream.write(header + encoded)
    else:
        stream.write(encoded + b"\n")
    stream.flush()


def handle_request(req: dict[str, Any]) -> dict[str, Any] | None:
    method = req.get("method", "")
    req_id = req.get("id")
    params = req.get("params") or {}

    if method.startswith("notifications/"):
        return None

    if method == "initialize":
        client_ver = str(params.get("protocolVersion", PROTOCOL_VERSIONS[0]))
        proto = client_ver if client_ver in PROTOCOL_VERSIONS else PROTOCOL_VERSIONS[0]
        return {
            "jsonrpc": "2.0",
            "id": req_id,
            "result": {
                "protocolVersion": proto,
                "capabilities": {"tools": {"listChanged": False}},
                "serverInfo": SERVER_INFO,
            },
        }

    if method == "ping":
        return {"jsonrpc": "2.0", "id": req_id, "result": {}}

    if method == "tools/list":
        return {"jsonrpc": "2.0", "id": req_id, "result": {"tools": TOOLS_SPEC}}

    if method == "tools/call":
        name = str(params.get("name", ""))
        args = params.get("arguments") or {}
        fn = TOOL_DISPATCH.get(name)
        if not fn:
            return {
                "jsonrpc": "2.0",
                "id": req_id,
                "error": {"code": -32601, "message": f"Unknown tool: {name}"},
            }
        try:
            res = fn(args)
            return {
                "jsonrpc": "2.0",
                "id": req_id,
                "result": {
                    "content": [{"type": "text", "text": json.dumps(res, ensure_ascii=False, indent=2)}],
                    "isError": False,
                },
            }
        except Exception as exc:
            return {
                "jsonrpc": "2.0",
                "id": req_id,
                "result": {
                    "content": [{"type": "text", "text": f"Tool error: {exc}\n{traceback.format_exc()}"}],
                    "isError": True,
                },
            }

    if req_id is None:
        return None
    return {
        "jsonrpc": "2.0",
        "id": req_id,
        "error": {"code": -32601, "message": f"Method not supported: {method}"},
    }


def main() -> int:
    stdin_bin = sys.stdin.buffer
    stdout_bin = sys.stdout.buffer
    while True:
        try:
            req, framing = _read_message(stdin_bin)
        except Exception:
            break
        if req is None:
            break
        resp = handle_request(req)
        if resp is not None:
            _write_message(stdout_bin, resp, framing)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

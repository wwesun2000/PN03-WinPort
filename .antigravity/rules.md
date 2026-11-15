# Antigravity (Hydrogen) Local Execution Rules for `pn03-winport`

1. **Zero Built-in Copyrighted Assets**: Never commit or bundle `main.dol`, `apploader.img`, or ISO audio/texture/model files into the repository or release binaries. Always load them dynamically from the user-configured `iso_path` via `pn03::IsoStreamReader`.
2. **Preserve Locked Argon Modules**: Do not overwrite or stub out `src/runtime/iso_reader.cpp` (`LzsDecode`), `src/runtime/pad_xinput.cpp`, `src/runtime/gx_renderer.cpp`, `src/runtime/localization_zh.cpp`, `tools/dol_to_elf.py`, or `re_data/*.json`.
3. **Single-Pass Local Execution**: Execute `LOCAL-01` through `LOCAL-04` in `HYDROGEN_TASKS.md` sequentially without pausing for intermediate confirmation unless a local path (`GHIDRA_INSTALL_DIR` or `iso_path`) is missing and cannot be auto-detected.

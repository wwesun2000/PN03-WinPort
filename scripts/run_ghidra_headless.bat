@echo off
setlocal enabledelayedexpansion
REM ============================================================================
REM P.N.03 (GPNE08) Local Ghidra Headless Batch Decompiler Runner
REM Usage: scripts\run_ghidra_headless.bat <PATH_TO_GHIDRA_DIR> <PATH_TO_PN03_ISO_OR_EXTRACTED_DIR>
REM ============================================================================

set "GHIDRA_DIR=%~1"
set "SOURCE_PATH=%~2"

if "%GHIDRA_DIR%"=="" (
    if defined GHIDRA_INSTALL_DIR (
        set "GHIDRA_DIR=%GHIDRA_INSTALL_DIR%"
    ) else (
        echo [ERROR] Please provide GHIDRA_INSTALL_DIR or pass Ghidra directory as arg 1.
        exit /b 1
    )
)

if "%SOURCE_PATH%"=="" (
    echo [ERROR] Please pass path to unpacked PN03.zip directory or P.N.03.iso as arg 2.
    exit /b 1
)

echo [1/2] Building standard PowerPC32 ELF with 8,221 MEKA.sym symbols...
python tools\dol_to_elf.py "%SOURCE_PATH%\sys\main.dol" "%SOURCE_PATH%\MEKA.sym" "build\pn03_main_with_syms.elf"
if errorlevel 1 exit /b 1

if not exist "build\ghidra_proj" mkdir "build\ghidra_proj"

echo [2/2] Running Ghidra analyzeHeadless with ImportMekaSymAndDecompile.py...
call "%GHIDRA_DIR%\support\analyzeHeadless.bat" "build\ghidra_proj" "PN03_GPNE08" ^
    -import "build\pn03_main_with_syms.elf" ^
    -scriptPath "ghidra_scripts" ^
    -postScript ImportMekaSymAndDecompile.py "re_data\meka_symbols_full.json" "src\ghidra_decompiled" ^
    -overwrite

echo [OK] Ghidra headless decompilation finished. Output in src\ghidra_decompiled\

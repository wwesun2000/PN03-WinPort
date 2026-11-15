@echo off
setlocal enabledelayedexpansion
REM ============================================================================
REM P.N.03 (GPNE08) Windows Native Port CMake + MSVC Direct Build Script
REM ============================================================================

cd /d "%~dp0\.."

where cmake >nul 2>nul
if not errorlevel 1 (
    echo [1/2] Configuring CMake ^(Visual Studio / Release x64^)...
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    if errorlevel 1 exit /b 1

    echo [2/2] Building PN03_WinPort.exe and pn03_cpp_tests.exe...
    cmake --build build --config Release --parallel
    if errorlevel 1 exit /b 1

    echo [OK] Build complete! Run build\Release\pn03_cpp_tests.exe or build\Release\PN03_WinPort.exe
    exit /b 0
)

echo [INFO] cmake not found on PATH; falling back to direct MSVC cl.exe + link.exe x64 build...

set "VCVARS="
for %%E in (BuildTools Community Professional Enterprise) do (
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\2022\%%E\VC\Auxiliary\Build\vcvars64.bat" (
        set "VCVARS=C:\Program Files (x86)\Microsoft Visual Studio\2022\%%E\VC\Auxiliary\Build\vcvars64.bat"
        goto :found_vs
    )
    if exist "C:\Program Files\Microsoft Visual Studio\2022\%%E\VC\Auxiliary\Build\vcvars64.bat" (
        set "VCVARS=C:\Program Files\Microsoft Visual Studio\2022\%%E\VC\Auxiliary\Build\vcvars64.bat"
        goto :found_vs
    )
)

:found_vs
if "%VCVARS%"=="" (
    echo [ERR] Visual Studio 2022 vcvars64.bat not found!
    exit /b 1
)

call "%VCVARS%"
if errorlevel 1 exit /b 1

if not exist build\obj mkdir build\obj
if not exist build\Release mkdir build\Release

echo [1/3] Compiling runtime, launcher, tests, and decompiled subsystems...
cl /nologo /std:c++20 /EHsc /bigobj /utf-8 /DNOMINMAX /D_CRT_SECURE_NO_WARNINGS /O2 /MP /Iinclude /c ^
    src\launcher\launcher_main.cpp ^
    src\launcher\win32_cyber_launcher.cpp ^
    src\runtime\config.cpp ^
    src\runtime\pn03_logger.cpp ^
    src\runtime\iso_reader.cpp ^
    src\runtime\pad_xinput.cpp ^
    src\runtime\gx_renderer.cpp ^
    src\runtime\gx_3d_interface.cpp ^
    src\runtime\audio_ax_hle.cpp ^
    src\runtime\localization_zh.cpp ^
    src\runtime\dolphin_sdk_hle.cpp ^
    src\runtime\win32_d3d11_host.cpp ^
    src\runtime\win32_vulkan_host.cpp ^
    src\decompiled\function_table_registry.cpp ^
    src\decompiled\indirect_call_table.cpp ^
    src\decompiled\tools_rel_decompiled.cpp ^
    src\decompiled\subsystems\*.cpp ^
    tests\test_runtime_cpp.cpp ^
    /Fo:build\obj\
if errorlevel 1 exit /b 1

set "COMMON_OBJS=build\obj\config.obj build\obj\pn03_logger.obj build\obj\iso_reader.obj build\obj\pad_xinput.obj build\obj\gx_renderer.obj build\obj\gx_3d_interface.obj build\obj\audio_ax_hle.obj build\obj\localization_zh.obj build\obj\dolphin_sdk_hle.obj build\obj\win32_d3d11_host.obj build\obj\win32_vulkan_host.obj build\obj\win32_cyber_launcher.obj build\obj\function_table_registry.obj build\obj\indirect_call_table.obj build\obj\tools_rel_decompiled.obj build\obj\subsys_*.obj"
set "WIN_LIBS=xinput.lib d3d11.lib dxgi.lib d3dcompiler.lib xaudio2.lib ole32.lib comdlg32.lib user32.lib gdi32.lib gdiplus.lib dwmapi.lib msimg32.lib winmm.lib shell32.lib"

echo [2/3] Linking build\Release\PN03_WinPort.exe...
link /nologo /OUT:build\Release\PN03_WinPort.exe build\obj\launcher_main.obj %COMMON_OBJS% %WIN_LIBS%
if errorlevel 1 exit /b 1

echo [3/3] Linking build\Release\pn03_cpp_tests.exe...
link /nologo /OUT:build\Release\pn03_cpp_tests.exe build\obj\test_runtime_cpp.obj %COMMON_OBJS% %WIN_LIBS%
if errorlevel 1 exit /b 1

echo [OK] Build complete! Run build\Release\pn03_cpp_tests.exe or build\Release\PN03_WinPort.exe
exit /b 0

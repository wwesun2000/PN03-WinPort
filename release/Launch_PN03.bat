@echo off
setlocal
cd /d "%~dp0\.."

set "EXTRA_ARGS="
echo %* | findstr /I /C:"--iso" >nul
if errorlevel 1 (
    for %%F in ("release\*.iso" "release\*.gcm") do (
        set "EXTRA_ARGS=--iso "%%~fF""
        goto :run
    )
)

:run
"release\PN03_WinPort.exe" %EXTRA_ARGS% %*

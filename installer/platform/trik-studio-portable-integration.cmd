@echo off
setlocal

if /I "%~1"=="install" goto run
if /I "%~1"=="uninstall" goto run

echo Usage: %~nx0 install^|uninstall
exit /b 2

:run
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0trik-studio-portable-integration.ps1" -Action "%~1"
exit /b %errorlevel%

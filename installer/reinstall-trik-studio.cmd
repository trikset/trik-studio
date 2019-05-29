@echo off

if not "%~2" == "" (set TRIK_STUDIO_INSTALL_DIR=%~f2) else (set TRIK_STUDIO_INSTALL_DIR=%SYSTEMDRIVE%\TRIKStudio)

if not "%~1" == "" (set INSTALLER_EXE=%~f1 && goto endFindExe)
set n=0
for %%f in (%~dp0\trik-studio-*installer*.exe) do (set /a n+=1)
if %n% EQU 0 (echo Error! No one trik-studio-*installer*.exe && exit /b 1)
if %n% GTR 1 (echo Error! Too much installers: && (for %%f in (trik-studio-*installer*.exe) do echo %%f ) && exit /b 1)
for %%f in (%~dp0\trik-studio-*installer*.exe) do (set INSTALLER_EXE=%%f)
:endFindExe

echo Install %INSTALLER_EXE% to %TRIK_STUDIO_INSTALL_DIR%

if not exist %TRIK_STUDIO_INSTALL_DIR% goto endUninstall
if exist %TRIK_STUDIO_INSTALL_DIR%\maintenance.exe (echo Uninstall previous TRIK Studio... && %TRIK_STUDIO_INSTALL_DIR%\maintenance.exe --script %~dp0\trik_studio_uninstallscript.qs) else (echo Error! %TRIK_STUDIO_INSTALL_DIR% exists and has no maintenance tool && exit /b 1)
:waitFullUninstall
if exist %TRIK_STUDIO_INSTALL_DIR% goto waitFullUninstall
:endUninstall
echo Install new TRIK Studio...
%INSTALLER_EXE% --script %~dp0\trik_studio_installscript.qs

if %errorlevel% EQU 0 (echo Done) else (echo Installation Error)

@echo off

set inline=%*
set pause_command=pause
if "%inline%" == "" goto endSetPause
if not "%inline:--no-pause=%" == "%inline%" set pause_command=true
:endSetPause

if not "%~2" == "" (set TRIK_STUDIO_INSTALL_DIR=%~f2) else (set TRIK_STUDIO_INSTALL_DIR=%SYSTEMDRIVE%\TRIKStudio)

if not "%~1" == "" (set INSTALLER_EXE=%~f1 && goto endFindExe)
set n=0
for %%f in (%~dp0\trik-studio-*installer*.exe) do (set /a n+=1)
if %n% EQU 0 (
  echo Error! No files matching pattern trik-studio-*installer*.exe
  echo Use parameter to choose installer like this:
  echo %~f0 C:\your-path\your-trik-studio-installer.exe
  %pause_command%
  exit /b 1
)
if %n% GTR 1 (
  echo Error! Too many candidates:
  for %%f in (trik-studio-*installer*.exe) do echo %%f
  echo Remove obsolete installers from this directory or use parameter to choose exact one like this:
  echo %~f0 %~dp0\your-trik-studio-installer.exe
  %pause_command%
  exit /b 1
)
for %%f in (%~dp0\trik-studio-*installer*.exe) do (set INSTALLER_EXE=%%f)
:endFindExe

echo Install %INSTALLER_EXE% to %TRIK_STUDIO_INSTALL_DIR%

if not exist %TRIK_STUDIO_INSTALL_DIR% goto endUninstall
if exist %TRIK_STUDIO_INSTALL_DIR%\maintenance.exe (
  echo Uninstalling previous version of TRIK Studio. Please wait...
  %TRIK_STUDIO_INSTALL_DIR%\maintenance.exe --script %~dp0\trik_studio_uninstallscript.qs
) else (
  echo Error! %TRIK_STUDIO_INSTALL_DIR% exists and has no maintenance tool
  %pause_command%
  exit /b 1
)
:waitFullUninstall
if exist %TRIK_STUDIO_INSTALL_DIR% goto waitFullUninstall
:endUninstall
echo Installing new version of TRIK Studio. Please wait...
%INSTALLER_EXE% --script %~dp0\trik_studio_installscript.qs

if %errorlevel% EQU 0 (echo Done) else (echo Installation Error)

%pause_command%

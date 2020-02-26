REM  This script can be used to manage unattended/autonomous install
REM  Without any options (double click it or run from command line) it upgrades
REM  default local TRIK Studio installation.
REM  Options:
REM  --force            to skip version check
REM  --no-pause         to disable pause at the end of a script, useful for automation to close window after run
REM  --installer PATH   use another TRIK Studio installer binary
REM  --target-path PATH use this directory as a target installation path
@echo off

Setlocal EnableDelayedExpansion

set pause_command=pause
set check_version=true
set read_installer=false
set read_targetpath=false
set INSTALLER_EXE=
set TRIK_STUDIO_INSTALL_DIR=
set prev=
set selfCmd=%~f0
set selfDir=%~dp0
set TRIK_STDIO_UNINSTALL_SCRIPT=%~dp0\trik_studio_uninstallscript.qs

if not exist "%TRIK_STDIO_UNINSTALL_SCRIPT%" (
	echo No "%TRIK_STDIO_UNINSTALL_SCRIPT%" file. Archive might be broken.
	goto end
)

if "%*" == "" goto endReadInline
for %%t in (%*) do (
  set token=%%t
  if "%%t" == "--no-pause" (
    set pause_command=echo "------"
  ) else if "%%t" == "--force" (
    set check_version=false
  ) else if "%%t" == "--installer" (
    REM do nothing
  ) else if "%%t" == "--target-path" (
    REM do nothing
  ) else if "!prev!" == "--installer" (
	set INSTALLER_EXE=%%~ft
  ) else if "!prev!" == "--target-path" (
	set TRIK_STUDIO_INSTALL_DIR=%%~ft
  ) else (
    echo Unknown option: %%t
	goto end
  )
  set prev=%%t
)
:endReadInline

if "%TRIK_STUDIO_INSTALL_DIR%"=="" set TRIK_STUDIO_INSTALL_DIR=%SYSTEMDRIVE%\TRIKStudio

if not "%INSTALLER_EXE%"=="" goto endFindExe
set n=0
for %%f in ("%~dp0"\trik-studio-*installer*.exe) do (set /a n+=1)
if %n% EQU 0 (
  echo Error! No files matching pattern trik-studio-*installer*.exe
  echo Use parameter to choose installer like this:
  echo "%selfCmd:)=^)% --installer C:\your-path\your-trik-studio-installer.exe"
  %pause_command%
  exit /b 1
)
if %n% GTR 1 (
  echo Error! Too many candidates:
  for %%f in ("%~dp0"\trik-studio-*installer*.exe) do echo %%~nf
  echo Remove obsolete installers from this directory or use --installer:
  echo %selfCmd:)=^)% --installer %selfDir:)=^)%\your-trik-studio-installer.exe
  %pause_command%
  exit /b 1
)

for %%f in ("%~dp0"\trik-studio-*installer*.exe) do (set INSTALLER_EXE=%%f)
:endFindExe

if "%check_version%" == "true" if exist %TRIK_STUDIO_INSTALL_DIR%\maintenance.exe (
  for /f "delims=" %%v in ('findstr "<Version>.*</Version>" %TRIK_STUDIO_INSTALL_DIR%\maintenance.dat') do set old_version="%%v"
  for /f "delims=" %%v in ('findstr "<Version>.*</Version>" "%INSTALLER_EXE%"') do set new_version="%%v"
  if !old_version! == !new_version! (echo The same version is already installed. Use --force to skip version check. && goto end)
)

echo Installing %INSTALLER_EXE% to %TRIK_STUDIO_INSTALL_DIR% ...
if not exist %TRIK_STUDIO_INSTALL_DIR% goto endUninstall
if exist %TRIK_STUDIO_INSTALL_DIR%\maintenance.exe (
  echo Uninstalling previous version of TRIK Studio. Please wait...
  %TRIK_STUDIO_INSTALL_DIR%\maintenance.exe --script "%~dp0\%TRIK_STDIO_UNINSTALL_SCRIPT%"
) else (
  echo Error! %TRIK_STUDIO_INSTALL_DIR% exists and has no maintenance tool
  %pause_command%
  exit /b 1
)
:waitFullUninstall
if exist %TRIK_STUDIO_INSTALL_DIR% goto waitFullUninstall
:endUninstall
echo Installing new version of TRIK Studio. Please wait...
"%INSTALLER_EXE%" --script "%~dp0\trik_studio_installscript.qs"

if %errorlevel% EQU 0 (echo Done) else (echo Installation Error. See messages above.)
:end
%pause_command%

@echo off
setlocal EnableDelayedExpansion

set "TargetDir=%~dp0"
if "%TargetDir:~-1%"=="\" set "TargetDir=%TargetDir:~0,-1%"

set "AllUsers=false"
if /I "%~1"=="-AllUsers" set "AllUsers=%~2"
if /I "%~1"=="true" set "AllUsers=true"

if "%TargetDir%"=="" (
    echo TargetDir is empty 1>&2
    exit /b 1
)

set "extension=.qrs"
set "progId=qrs_auto_file"
set "description=TRIK Studio Project"
set "contentType=application/octet-stream"

set "vbs=%TargetDir%\trik-studio.vbs"
set "icon=%TargetDir%\trik-studio.ico"

set "command=C:\Windows\System32\wscript.exe //nologo //b // \"%vbs%\" \"%%1\""

if /I "%AllUsers%"=="true" (
    set "classes=HKLM\Software\Classes"
) else (
    set "classes=HKCU\Software\Classes"
)

set "regFile=%TEMP%\remove_userchoice_%RANDOM%.reg"
set "fileExts=HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\FileExts\.qrs"

> "%regFile%" echo Windows Registry Editor Version 5.00
>>"%regFile%" echo.
>>"%regFile%" echo [-%fileExts%\UserChoice]

regedit /s "%regFile%"
del "%regFile%" >nul 2>&1

rem === Register the .qrs extension ===
reg add "%classes%\%extension%" /ve /d "%progId%" /f >nul
reg add "%classes%\%extension%" /v "Content Type" /d "%contentType%" /f >nul

rem === Register the ProgId ===
reg add "%classes%\%progId%" /ve /d "%description%" /f >nul

rem === OpenWithProgIds ===
reg add "%classes%\%extension%\OpenWithProgIds" /v "%progId%" /d "" /f >nul

rem === Open command ===
reg add "%classes%\%progId%\shell\open\command" /ve /d "%command%" /f >nul

rem === Icon ===
reg add "%classes%\%progId%\DefaultIcon" /ve /d "%icon%" /f >nul

rem === Notify the shell that associations changed ===
rem Equivalent to SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_FLUSH, 0, 0)
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
  "Add-Type -TypeDefinition 'using System; using System.Runtime.InteropServices; public class ShellNotify { [DllImport(\"shell32.dll\")] public static extern void SHChangeNotify(uint wEventId, uint uFlags, IntPtr dwItem1, IntPtr dwItem2); }'; [ShellNotify]::SHChangeNotify(0x08000000, 0x1000, [IntPtr]::Zero, [IntPtr]::Zero)"

endlocal
exit /b 0
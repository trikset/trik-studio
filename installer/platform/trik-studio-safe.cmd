@ECHO OFF
SETLOCAL ENABLEEXTENSIONS
IF ERRORLEVEL 1 ECHO Failed to enable extensions
TITLE TRIK Studio Safe Mode
SET "PATH=%SystemRoot%;%SystemRoot%\system32"
PATH
%~dp0trik-studio.exe "%*"

@echo off
title TRIK Studio Safe Mode
FOR /f "usebackq tokens=1* delims=:" %%F IN (`where java 2^>NUL ^| findstr /n "^"`) DO @IF %%F == 1 ( ECHO(Using Java: "%%G" && SET JAVA_PATH=%%~dpG )
set PATH=%SystemRoot%;%SystemRoot%\system32;%JAVA_PATH%
%~dp0trik-studio.exe "%*"

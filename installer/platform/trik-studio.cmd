@echo off
title TRIK Studio Safe Mode
FOR /F "tokens=* USEBACKQ" %%F IN (`where java 2^>NUL`) DO (SET JAVA_PATH=%%~dpF)
set PATH=%SystemRoot%;%SystemRoot%\system32;%JAVA_PATH%
start "" %~dp0trik-studio.exe %*

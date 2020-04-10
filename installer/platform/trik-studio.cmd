setlocal enabledelayedexpansion enableextensions

FOR /F "tokens=* USEBACKQ" %%F IN (`where java`) DO (
SET JAVA_BIN=%%F
)
call :file_name_from_path JAVA_PATH "!JAVA_BIN!"
set PATH=%SystemRoot%;%SystemRoot%\system32;%JAVA_PATH%;

%~dp0\trik-studio
goto :eof
:file_name_from_path <resultVar> <pathVar>
(
    set "%~1=%~dp2"
    exit /b
)
:eof

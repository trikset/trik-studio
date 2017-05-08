@echo off

set CYGWIN_DIR=C:\cygwin64\bin
set OPENOCD_DIR=C:\cygwin64\install\openocd-0.10.0
set OPENOCD_BIN_DIR=%OPENOCD_DIR%\bin
set OPENOCD=openocd

set COMPILERS_DIR=C:\Program Files (x86)\GNU Tools ARM Embedded\5.4 2016q3\bin

rem TODO floods path, fix me!
set PATH=%PATH%;%CYGWIN_DIR%;%OPENOCD_BIN_DIR%;%COMPILERS_DIR%
rem set LIBRARIES="%~dp0"

rem small hack to receive output of cygpath
for /f %%i in ('cygpath -m "%~dp0"') do set LIBRARIES=%%i
echo Libraries: %LIBRARIES%

set MAKEFILE="%LIBRARIES%"/Makefile

rem the folder that contains this bat & makefile
echo Launch dir: "%~dp0"

rem the folder with the generated cpp
echo Current dir: "%CD%"

cd "%CD%"

rem set MAKE=make -f "%MAKEFILE%"
set MAKE_ARGS="LIBRARIES=%LIBRARIES%"
set GOAL=all program

make -f %MAKEFILE% %MAKE_ARGS% %GOAL%

rem set ERROR_LEVEL

echo done

rem exit 0
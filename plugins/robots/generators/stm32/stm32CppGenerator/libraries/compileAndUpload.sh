#!/bin/bash
# @echo off

export CYGWIN_DIR="C:\cygwin64\bin"
export OPENOCD_DIR="C:\cygwin64\install\openocd-0.10.0"
export OPENOCD_BIN_DIR="${OPENOCD_DIR}\bin"
export OPENOCD="openocd"

export COMPILERS_DIR="C:\Program Files (x86)\GNU Tools ARM Embedded\5.4 2016q3\bin"

# TODO floods path, fix me!
export PATH="${PATH}${CYGWIN_DIR}${OPENOCD_BIN_DIR}${COMPILERS_DIR}"
# set LIBRARIES="%~dp0"

# small hack to receive output of cygpath
for -f i in ['cygpath -m "${~dp0}"']; do export LIBRARIES="i"
# echo %LIBRARIES%

export MAKEFILE="${LIBRARIES}/Makefile"

# the folder that contains this bat & makefile
echo Launch dir: "${~dp0}"

# the folder with the generated cpp
echo Current dir: "${cd}"

cd "${cd}"

# set MAKE=make -f "%MAKEFILE%"
export MAKE_ARGS="LIBRARIES=${LIBRARIES}"
export GOAL="all program"

make -f "${MAKEFILE} ${MAKE_ARGS} ${GOAL}"

# set ERROR_LEVEL

echo done

# exit 0
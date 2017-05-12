#!/bin/bash
# @echo off

#export CYGWIN_DIR="C:\cygwin64\bin"
export OPENOCD_DIR="/home/osboxes/Downloads/openocd-0.10.0"
export OPENOCD_BIN_DIR="${OPENOCD_DIR}/bin"
echo OPENOCD_BIN_DIR: "$OPENOCD_BIN_DIR"
export OPENOCD="openocd"

export COMPILERS_DIR="/home/osboxes/Downloads/gcc-arm-none-eabi-5_4-2016q3/bin"
echo COMPILERS_DIR: "$COMPILERS_DIR"

# TODO floods path, fix me!
#export PATH="${PATH}${CYGWIN_DIR}${OPENOCD_BIN_DIR}${COMPILERS_DIR}"
export PATH=$OPENOCD_BIN_DIR:$COMPILERS_DIR:$PATH
echo PATH: $PATH
# set LIBRARIES="%~dp0"

export LIBRARIES=${0%/*}
echo LIBRARIES: "${LIBRARIES}"

# small hack to receive output of cygpath
#for i in `"$~dp0"`; do export LIBRARIES="$i";
# echo %LIBRARIES%

export MAKEFILE="${LIBRARIES}/Makefile"

# the folder that contains this bat & makefile
echo Launch dir: ${0%/*}

# the folder with the generated cpp
echo Current dir: "${PWD}"

cd "${PWD}"

# set MAKE=make -f "%MAKEFILE%"
export MAKE_ARGS="LIBRARIES=${LIBRARIES}"
export GOAL="all program"

make -f ${MAKEFILE} ${MAKE_ARGS} ${GOAL}
echo "make -f ${MAKEFILE} ${MAKE_ARGS} ${GOAL}"

# set ERROR_LEVEL

echo done

# exit 0

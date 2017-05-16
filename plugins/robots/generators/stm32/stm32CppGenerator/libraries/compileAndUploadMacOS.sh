#!/bin/sh

#export OPENOCD_DIR="/Users/me/Downloads/openocd-0.10.0"
#export OPENOCD_BIN_DIR="${OPENOCD_DIR}/bin"
#export OPENOCD_SCRIPTS_DIR="${OPENOCD_DIR}/scripts"

export OPENOCD_BIN_DIR=""
export OPENOCD="openocd"

export COMPILERS_DIR="/Users/me/Downloads/gcc-arm-none-eabi-6-2017-q1-update/bin"

export PATH=$COMPILERS_DIR:$OPENOCD_BIN_DIR:$PATH
launchctl setenv PATH $PATH

export LIBRARIES=${0%/*}
echo LIBRARIES: "${LIBRARIES}"

export MAKEFILE="${LIBRARIES}/Makefile"

# the folder with the generated cpp
echo Current dir: "${PWD}"

cd "${PWD}"

export MAKE_ARGS="LIBRARIES=${LIBRARIES}"

export GOAL="all program"

make -f ${MAKEFILE} ${MAKE_ARGS} ${GOAL}

echo done

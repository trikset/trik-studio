#!/bin/sh

export OPENOCD_DIR="/home/osboxes/Downloads/openocd-0.10.0"
export OPENOCD_BIN_DIR="${OPENOCD_DIR}/bin"
export OPENOCD_SCRIPTS_DIR="${OPENOCD_DIR}/scripts"
export OPENOCD="openocd"

export COMPILERS_DIR="/home/osboxes/Downloads/gcc-arm-none-eabi-5_4-2016q3/bin"

export PATH=$COMPILERS_DIR:$OPENOCD_BIN_DIR:$PATH

export LIBRARIES=${0%/*}

export MAKEFILE="${LIBRARIES}/Makefile"

# the folder that contains this bat & makefile
echo Launch dir: ${0%/*}

# the folder with the generated cpp
echo Current dir: "${PWD}"

cd "${PWD}"

export MAKE_ARGS="LIBRARIES=${LIBRARIES}"

export GOAL="all program"

make -f ${MAKEFILE} ${MAKE_ARGS} ${GOAL}

echo done

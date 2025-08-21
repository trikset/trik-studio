#!/bin/bash

set -xueo pipefail
export LANG=C
ccache -V && ccache -p
which g++
g++ --version
which qmake
qmake -query
ccache -sz
{ which python3 && python3 -V || true ; }
{ which python && python -V || true ; }
mkdir -p build && cd build
export PYTHON_DIR=$(python3.${TRIK_PYTHON3_VERSION_MINOR}-config --prefix)
rm -f .qmake.cache

pushd "$BUILD_DIR"
qmake -Wall PYTHON_VERSION=3.$TRIK_PYTHON3_VERSION_MINOR PYTHON_PATH=/usr CONFIG+=$CONFIG $QMAKE_EXTRA "$ROOT_DIR/$PROJECT.pro"
make -j $(nproc) qmake_all 2>&1 | tee -a build.log
ccache -s
if [ "$NEED_COMPILE_DATABASE" = "true" ]; then
  bear -- make -j $(nproc) all 2>&1 | tee -a build.log
else
  make -j $(nproc) all 2>&1 | tee -a build.log
fi
ccache -s
ls bin

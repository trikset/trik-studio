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
export PYTHON_DIR=$(python3.${TRIK_PYTHON3_VERSION_MINOR}-config --prefix)
export PKG_CONFIG_PATH="$PYTHON_DIR/lib/pkgconfig"
rm -f .qmake.cache
qmake -Wall PYTHON_VERSION=3.$TRIK_PYTHON3_VERSION_MINOR PYTHON_PATH=/usr CONFIG+=$CONFIG $QMAKE_EXTRA $PROJECT.pro
make -j $(nproc) qmake_all 2>&1 | tee -a build.log
ccache -s
make -j $(nproc) all 2>&1 | tee -a build.log
ccache -s
ls bin

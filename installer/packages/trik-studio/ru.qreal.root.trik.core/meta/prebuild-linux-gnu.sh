#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p $PWD/../data/lib
mkdir -p $PWD/../data/lib/plugins/editors
cp     $BIN_DIR/plugins/editors/libtrikMetamodel.so                                $PWD/../data/lib/plugins/editors
cp -pr $BIN_DIR/librobots-trik-qts-generator-library.so*                           $PWD/../data/lib/
cp -pr $BIN_DIR/librobots-trik-generator-base.so*                                  $PWD/../data/lib/
cp -pr $BIN_DIR/librobots-trik-kit.so*                                             $PWD/../data/lib/
cp -pr $BIN_DIR/librobots-trik-kit-interpreter-common.so*                          $PWD/../data/lib/
rsync -a "$BIN_DIR"/libtrikPythonQt{,_QtAll}-Qt*-Python*.so*                                        "$PWD"/../data/lib/
ldd $BIN_DIR/libtrikPythonQt_QtAll-Qt5*-Python3*.so.1.0  | grep python3 | cut -d ' ' -f 3 | head -n 1 | xargs cp -prvt $PWD/../data/lib/

rsync -a "$BIN_DIR"/libtrik*.so*                                                         "$PWD"/../data/lib/

cp     $BIN_DIR/system.{py,js} $BIN_DIR/2D-model                       		 $PWD/../data/bin/

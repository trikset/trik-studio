#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p $PWD/../data/lib
mkdir -p $PWD/../data/lib/plugins/editors
cp     $BIN_DIR/plugins/editors/libtrikMetamodel.so                                $PWD/../data/lib/plugins/editors
cp -pr $BIN_DIR/librobots-trik-kit.so*                                             $PWD/../data/lib/
cp -pr $BIN_DIR/librobots-trik-kit-interpreter-common.so*                          $PWD/../data/lib/

rsync -a "$BIN_DIR"/libtrik*.so*                                                         "$PWD"/../data/lib/

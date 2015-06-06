#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

cp     $INSTALLER_ROOT/licenses/Box2D-license*.txt

mkdir -p $PWD/../data/plugins/editors
mkdir -p $PWD/../data/plugins/tools
cp -r  $BIN_DIR/help                                                    $PWD/../data
cp -r  $BIN_DIR/images                                                  $PWD/../data

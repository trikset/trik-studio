#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p $PWD/../data/lib/
mkdir -p $PWD/../data/bin/

cp -pr $QT_DIR/lib/libQt5MultimediaWidgets.so*		$PWD/../data/lib/
cp -pr $QT_DIR/lib/libQt5OpenGL.so*					$PWD/../data/lib/
cp     $BIN_DIR/gamepad								$PWD/../data/bin/gamepad
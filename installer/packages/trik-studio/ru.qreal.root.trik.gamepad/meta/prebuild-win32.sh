#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

cp    "$QT_LIB"/Qt5MultimediaWidgets.dll  "$PWD"/../data
cp    "$QT_LIB"/bin/Qt5OpenGL.dll             "$PWD"/../data
cp    $BIN_DIR/gamepad.exe					$PWD/../data

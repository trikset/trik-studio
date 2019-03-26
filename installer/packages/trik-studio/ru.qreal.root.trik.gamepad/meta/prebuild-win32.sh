#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

cp    $QT_DIR/bin/Qt5MultimediaWidgets.dll  $PWD/../data
cp    $QT_DIR/bin/Qt5OpenGL.dll             $PWD/../data
cp    $BIN_DIR/gamepad.exe					$PWD/../data
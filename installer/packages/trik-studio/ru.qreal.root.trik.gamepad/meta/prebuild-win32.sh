#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

rsync -a "$QT_LIB"/Qt5MultimediaWidgets.dll  "$PWD"/../data
rsync -a "$QT_LIB"/Qt5OpenGL.dll             "$PWD"/../data
rsync -a "$BIN_DIR"/gamepad.exe					"$PWD"/../data

#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p "$PWD"/../data/lib/
mkdir -p "$PWD"/../data/bin/

rsync -a "$QT_LIB"/libQt5MultimediaWidgets.so*		"$PWD"/../data/lib/
rsync -a "$QT_LIB"/libQt5OpenGL.so*					"$PWD"/../data/lib/
rsync -a "$BIN_DIR"/gamepad								"$PWD"/../data/bin/gamepad

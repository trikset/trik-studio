#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p $PWD/../data/lib/
mkdir -p $PWD/../data/lib/plugins/tools/kitPlugins/
mkdir -p $PWD/../data/python-runtime/

cp    $BIN_DIR/librobots-trik-python-generator-library.so*                              $PWD/../data/lib/
cp    $BIN_DIR/plugins/tools/kitPlugins/librobots-trik-v62-python-generator.so            $PWD/../data/lib/plugins/tools/kitPlugins/

#Add Python runtime libraries

[ -r venv/bin/activate ] || python3.${TRIK_PYTHON3_VERSION_MINOR} -m venv venv
. venv/bin/activate
python3 -m pip install pyinstaller
pyinstaller --noconfirm --log-level DEBUG --onedir --name trik \
	--hidden-import math \
	--hidden-import random \
	--hidden-import sys \
	--hidden-import time \
 	$BIN_DIR/system.py
rsync -avR dist/trik/./{base_library.zip,lib-dynload/} "$PWD/../data/python-runtime"

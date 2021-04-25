#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source $INSTALLER_ROOT/utils/mac_utils.sh

mkdir -p "$BUNDLE_CONTENTS/Lib/"
mkdir -p "$BUNDLE_CONTENTS/python-runtime/"

cp -fpR   $BIN_DIR/librobots-trik-python-generator-library*.dylib                          "$BUNDLE_CONTENTS/Lib/"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-trik-python-generator-library.1.0.0.dylib"

mkdir -p "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins"
cp -f    $BIN_DIR/plugins/tools/kitPlugins/librobots-trik-v62-python-generator.dylib    "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/librobots-trik-v62-python-generator.dylib"

#Add Python runtime libraries

[ -r venv/bin/activate ] || python3.${TRIK_PYTHON3_VERSION_MINOR} -m venv venv
. venv/bin/activate
python3 -m pip install pyinstaller
pyinstaller --noconfirm --log-level DEBUG --onedir --name trik \
	--hidden-import math \
	--hidden-import random \
	--hidden-import sys \
	--hidden-import time \
	"$BIN_DIR/system.py"
rsync -avR dist/trik/./{base_library.zip,lib-dynload/} "$BUNDLE_CONTENTS/python-runtime"

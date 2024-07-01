#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p "$PWD/../data/lib/python-runtime"
mkdir -p "$PWD"/../data/lib/plugins/editors
rsync -a "$BIN_DIR"/plugins/editors/libtrikMetamodel.so                                "$PWD"/../data/lib/plugins/editors
rsync -a "$BIN_DIR"/librobots-trik-qts-generator-library.so*                           "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/librobots-trik-generator-base.so*                                  "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/librobots-trik-kit.so*                                             "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/librobots-trik-kit-interpreter-common.so*                          "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libtrikPythonQt{,_QtAll}-Qt*-Python*.so*                       "$PWD"/../data/lib/

rsync -a "$BIN_DIR"/libtrik*.so*                                                   "$PWD"/../data/lib/
rsync -a "$QT_LIB"/libQt5SerialPort.so*                                            "$PWD"/../data/lib/
rsync -a "$QT_LIB"/libQt5Concurrent.so*                                            "$PWD"/../data/lib/

rsync -a "$BIN_DIR"/{system.js,TRIK.py,2D-model,checkapp}            			"$PWD/../data/bin/"

#Add Python runtime libraries

[ -r venv/bin/activate ] || "python3.${TRIK_PYTHON3_VERSION_MINOR}" -m venv venv
. venv/bin/activate
python3 -m pip install -U pip
python3 -m pip install pyinstaller numpy

#PyInstaller provides all required modules
#So we need to handle this garbage of files later (below) with proper rsync
pyinstaller --clean --noconfirm --log-level DEBUG --debug noarchive --onedir --name trik \
	--hidden-import=math \
	--hidden-import=random \
	--hidden-import=sys \
	--hidden-import=time \
	--hidden-import=os \
	--hidden-import=types \
	--hidden-import=pip \
	--hidden-import=venv \
	--hidden-import=site \
	--hidden-import=numpy \
	"$BIN_DIR"/TRIK.py

deactivate # exit python's venv

rsync -avR --remove-source-files dist/trik/_internal/./*.so* "$PWD/../data/lib/"
# Remove before copying other files
rm dist/trik/trik
rsync -avRm --ignore-missing-args --delete --delete-after dist/trik/_internal/./* "$PWD/../data/lib/python-runtime"

#PythonQt requires for dlopen'ing
pushd "$PWD/../data/lib" && for f in libpython3.*.so.* ; do ln -svf "$f" "$(echo "$f" | cut -d . -f 1-3)" ; done ; popd

#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source "$INSTALLER_ROOT"/utils/mac_utils.sh

mkdir -p "$BUNDLE_CONTENTS/Lib/python-runtime"
mkdir -p "$BUNDLE_CONTENTS/Lib/plugins/editors"

rsync -a "$BIN_DIR"/plugins/editors/libtrikMetamodel.dylib                                "$BUNDLE_CONTENTS/Lib/plugins/editors/"
rsync -a "$BIN_DIR"/librobots-trik-qts-generator-library*.dylib                           "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/librobots-trik-generator-base*.dylib                                  "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/librobots-trik-kit*.dylib                                             "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/librobots-trik-kit-interpreter-common*.dylib                          "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libtrik*.dylib                                            	          "$BUNDLE_CONTENTS/Lib"

mkdir -p "$BUNDLE_CONTENTS/MacOS"
rsync -a "$BIN_DIR"/{system.js,TRIK.py}	                                                "$PWD/../data/"
rsync -a "$BIN_DIR"/{2D-model,checkapp}                                                  "$BUNDLE_CONTENTS/MacOS/"

copy_qt_lib QtSerialPort


[ -r venv/bin/activate ] || python3."${TRIK_PYTHON3_VERSION_MINOR}" -m venv venv
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

rsync -avR --remove-source-files dist/trik/_internal/./*.dylib "$BUNDLE_CONTENTS/Lib"
# Remove before copying other files
rm dist/trik/trik
rsync -avRm --delete --delete-after dist/trik/_internal/./* "$BUNDLE_CONTENTS/Lib/python-runtime"

#Add Python runtime libraries
PYTHON_LIBNAME=$("python3.${TRIK_PYTHON3_VERSION_MINOR}-config" --prefix)/Python
#rsync -a "$PYTHON_LIBNAME" "$BUNDLE_CONTENTS/Lib"
find "$BUNDLE_CONTENTS/Lib" -type f -name '*.dylib' -print0 | xargs -0n1 install_name_tool -change "$PYTHON_LIBNAME" @rpath/../Lib/python-runtime/Python

fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/editors/libtrikMetamodel.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-trik-qts-generator-library.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-trik-generator-base.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-trik-kit.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-trik-kit-interpreter-common.1.0.0.dylib"

export -f fix_dependencies
export -f fix_qreal_dependencies
find "$BUNDLE_CONTENTS/Lib" -depth 1 -name "libtrik*.*.*.*.dylib" -print0 | xargs -0 -n 1 -I {} bash -c 'fix_qreal_dependencies "{}"'

fix_qreal_dependencies "$BUNDLE_CONTENTS/MacOS/checkapp"
fix_qreal_dependencies "$BUNDLE_CONTENTS/MacOS/2D-model"

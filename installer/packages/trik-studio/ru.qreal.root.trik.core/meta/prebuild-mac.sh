#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source $INSTALLER_ROOT/utils/mac_utils.sh

mkdir -p "$BUNDLE_CONTENTS/Lib/plugins/editors"
cp  -f   $BIN_DIR/plugins/editors/libtrikMetamodel.dylib                                "$BUNDLE_CONTENTS/Lib/plugins/editors/"
cp -fpR $BIN_DIR/librobots-trik-qts-generator-library*.dylib                           "$BUNDLE_CONTENTS/Lib"
cp -fpR $BIN_DIR/librobots-trik-generator-base*.dylib                                  "$BUNDLE_CONTENTS/Lib"
cp -fpR $BIN_DIR/librobots-trik-kit*.dylib                                             "$BUNDLE_CONTENTS/Lib"
cp -fpR $BIN_DIR/librobots-trik-kit-interpreter-common*.dylib                          "$BUNDLE_CONTENTS/Lib"
cp -fpR $BIN_DIR/libtrik*.dylib                                            	          "$BUNDLE_CONTENTS/Lib"

PYTHON_LIBNAME=$(python3-config --prefix)/Python
cp -fpR "$PYTHON_LIBNAME" "$BUNDLE_CONTENTS/Lib"
find "$BUNDLE_CONTENTS/Lib" -name '*.dylib' -print0 | xargs -0n1 install_name_tool -change "$PYTHON_LIBNAME" @rpath/../Lib/Python


fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/editors/libtrikMetamodel.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-trik-qts-generator-library.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-trik-generator-base.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-trik-kit.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-trik-kit-interpreter-common.1.0.0.dylib"

export -f fix_dependencies
export -f fix_qreal_dependencies
find "$BUNDLE_CONTENTS/Lib" -depth 1 -name "libtrik*.dylib" -print0 | xargs -0 -n 1 -I {} bash -c 'fix_qreal_dependencies "{}"'
mkdir -p "$BUNDLE_CONTENTS/MacOS"
cp -pR $BIN_DIR/system.{py,js}                                                 "$PWD/../data/"
cp -fpR "$BIN_DIR/2D-model"                                                       "$BUNDLE_CONTENTS/MacOS/"
fix_qreal_dependencies "$BUNDLE_CONTENTS/MacOS/2D-model"


#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source $INSTALLER_ROOT/utils/mac_utils.sh

mkdir -p "$BUNDLE_CONTENTS/Lib/python-runtime"
mkdir -p "$BUNDLE_CONTENTS/Lib/plugins/editors"

cp  -f   $BIN_DIR/plugins/editors/libtrikMetamodel.dylib                                "$BUNDLE_CONTENTS/Lib/plugins/editors/"
cp -fpR $BIN_DIR/librobots-trik-kit*.dylib                                             "$BUNDLE_CONTENTS/Lib"
cp -fpR $BIN_DIR/librobots-trik-kit-interpreter-common*.dylib                          "$BUNDLE_CONTENTS/Lib"
cp -fpR $BIN_DIR/libtrik*.dylib                                            	          "$BUNDLE_CONTENTS/Lib"

fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/editors/libtrikMetamodel.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-trik-kit.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-trik-kit-interpreter-common.1.0.0.dylib"

export -f fix_dependencies
export -f fix_qreal_dependencies
find "$BUNDLE_CONTENTS/Lib" -depth 1 -name "libtrik*.*.*.*.dylib" -print0 | xargs -0 -n 1 -I {} bash -c 'fix_qreal_dependencies "{}"'

mkdir -p "$BUNDLE_CONTENTS/MacOS"
cp -fpR "$BIN_DIR"/{2D-model,checkapp}                                                  "$BUNDLE_CONTENTS/MacOS/"

fix_qreal_dependencies "$BUNDLE_CONTENTS/MacOS/checkapp"
fix_qreal_dependencies "$BUNDLE_CONTENTS/MacOS/2D-model"

#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source "$INSTALLER_ROOT"/utils/mac_utils.sh

mkdir -p "$BUNDLE_CONTENTS/Lib/plugins/editors/"
mkdir -p "$BUNDLE_CONTENTS/Lib/plugins/tools/"
mkdir -p "$BUNDLE_CONTENTS/MacOS"
mkdir -p "$BUNDLE_CONTENTS/Resources/"
rsync -a   "$BIN_DIR"/plugins/editors/librobotsMetamodel.dylib                   "$BUNDLE_CONTENTS/Lib/plugins/editors/"
rsync -a   "$BIN_DIR"/plugins/tools/librobots-plugin.dylib                       "$BUNDLE_CONTENTS/Lib/plugins/tools/"
rsync -a "$BIN_DIR"/librobots-interpreter-core*.dylib                          "$BUNDLE_CONTENTS/Lib/"
rsync -a "$BIN_DIR"/librobots-2d-model*.dylib                                  "$BUNDLE_CONTENTS/Lib/"
rsync -a "$BIN_DIR"/libtrikBox2D*.dylib                                            "$BUNDLE_CONTENTS/Lib/"
rsync -a "$BIN_DIR"/librobots-generator-base*.dylib                            "$BUNDLE_CONTENTS/Lib/"
rsync -a "$BIN_DIR"/librobots-kit-base*.dylib                                  "$BUNDLE_CONTENTS/Lib/"
rsync -a "$BIN_DIR"/librobots-utils*.dylib                                     "$BUNDLE_CONTENTS/Lib/"

copy_qt_lib QtMultimedia
copy_qt_lib QtNetwork


fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/editors/librobotsMetamodel.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/tools/librobots-plugin.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-interpreter-core.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-2d-model.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libtrikBox2D.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-generator-base.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-kit-base.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-utils.1.0.0.dylib"

# Cleaning up prebuild-common.sh results...
rm -rf "$PWD"/../data/plugins/
rm -rf "$BUNDLE_CONTENTS/Resources/help/"
rm -rf "$BUNDLE_CONTENTS/Resources/images/"
mv "$PWD"/../data/help "$BUNDLE_CONTENTS/Resources/"
mv "$PWD"/../data/images "$BUNDLE_CONTENTS/Resources/"
mv "$PWD"/../data/splashscreen.png "$BUNDLE_CONTENTS/MacOS/"
rsync -aR --remove-source-files "$(realpath "$PWD/../data")/./externalToolsConfig"                                "$BUNDLE_CONTENTS/MacOS/"

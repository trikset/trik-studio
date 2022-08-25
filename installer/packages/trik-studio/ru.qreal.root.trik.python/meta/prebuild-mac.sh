#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source "$INSTALLER_ROOT"/utils/mac_utils.sh

mkdir -p "$BUNDLE_CONTENTS/Lib/"

cp -fpR   "$BIN_DIR"/librobots-trik-python-generator-library*.dylib                          "$BUNDLE_CONTENTS/Lib/"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-trik-python-generator-library.1.0.0.dylib"

mkdir -p "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins"
cp -fp   "$BIN_DIR"/plugins/tools/kitPlugins/librobots-trik-v62-python-generator.dylib    "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/librobots-trik-v62-python-generator.dylib"

#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source "$INSTALLER_ROOT"/utils/mac_utils.sh


mkdir -p "$BUNDLE_CONTENTS/Lib/plugins/editors"
mkdir -p "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins"
rsync -a   "$BIN_DIR"/plugins/editors/libev3Metamodel.dylib                      "$BUNDLE_CONTENTS/Lib/plugins/editors/"
rsync -a   "$BIN_DIR"/plugins/tools/kitPlugins/librobots-ev3-interpreter.dylib   "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/"
rsync -a   "$BIN_DIR"/plugins/tools/kitPlugins/librobots-ev3-rbf-generator.dylib "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/"
rsync -a "$BIN_DIR"/librobots-ev3-kit*.dylib                                   "$BUNDLE_CONTENTS/Lib/"
rsync -a "$BIN_DIR"/librobots-ev3-generator-base*.dylib                        "$BUNDLE_CONTENTS/Lib/"
rsync -a "$BIN_DIR"/libusb-1.*.dylib                                           "$BUNDLE_CONTENTS/Lib/"

fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/editors/libev3Metamodel.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/librobots-ev3-interpreter.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/tools/kitplugins/librobots-ev3-rbf-generator.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-ev3-kit.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-ev3-generator-base.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libusb-1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libusb-1.0.dylib"

# Cleaning up prebuild-common.sh results...
rm -rf "$PWD"/../data/plugins/
#mv "$PWD"/../data/examples "$PWD"/../data/resources

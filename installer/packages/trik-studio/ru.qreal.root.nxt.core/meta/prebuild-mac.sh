#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source $INSTALLER_ROOT/utils/mac_utils.sh


mkdir -p "$BUNDLE_CONTENTS/Lib/plugins/editors/"
mkdir -p "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/"
cp -f    $BIN_DIR/plugins/editors/libnxtMetamodel.dylib                                      "$BUNDLE_CONTENTS/Lib/plugins/editors/"
cp -f    $BIN_DIR/plugins/tools/kitPlugins/librobots-nxt-interpreter.dylib                   "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/"
cp -f   $BIN_DIR/plugins/tools/kitPlugins/librobots-nxt-osek-c-generator.dylib              "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/"
cp -fpR $BIN_DIR/librobots-nxt-generator-base*.dylib                                        "$BUNDLE_CONTENTS/Lib"
cp -fpR $BIN_DIR/librobots-nxt-kit*.dylib                                                   "$BUNDLE_CONTENTS/Lib"
cp -fpR $BIN_DIR/libqextserialport*.dylib                                                   "$BUNDLE_CONTENTS/Lib"
cp -fpR "$BIN_DIR"/libusb-1.*.dylib                                                            "$BUNDLE_CONTENTS/Lib/"

fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/editors/libnxtMetamodel.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/librobots-nxt-interpreter.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/librobots-nxt-osek-c-generator.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-nxt-generator-base.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/librobots-nxt-kit.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqextserialport.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libusb-1.0.dylib"

# Cleaning up prebuild-common.sh results...
rm -rf $PWD/../data/plugins

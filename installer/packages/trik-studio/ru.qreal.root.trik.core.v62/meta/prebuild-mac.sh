#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source "$INSTALLER_ROOT"/utils/mac_utils.sh


mkdir -p "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins"
rsync -a    "$BIN_DIR"/plugins/tools/kitPlugins/librobots-trik-v62-interpreter.dylib              "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/"
rsync -a   "$BIN_DIR"/plugins/tools/kitPlugins/librobots-trik-v62-qts-generator.dylib            "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/"
# rsync -a     "$BIN_DIR"/plugins/tools/librobots-trik-v62-runtime-uploader-plugin.dylib             "$BUNDLE_CONTENTS/Lib/plugins/tools/"

fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/librobots-trik-v62-interpreter.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/tools/kitPlugins/librobots-trik-v62-qts-generator.dylib"
# fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/tools/librobots-trik-v62-runtime-uploader-plugin.dylib"

# Cleaning up prebuild-common.sh results...
rm -rf "$PWD"/../data/plugins/

#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p "$PWD"/../data/lib/plugins/editors/
mkdir -p "$PWD"/../data/lib/plugins/tools/
mkdir -p "$PWD"/../data/bin/
mkdir -p "$PWD"/../data/resources/

rsync -a "$QT_LIB"/libQt5Multimedia.so*		"$PWD"/../data/lib/
rsync -a "$QT_LIB"/libQt5Network.so*		"$PWD"/../data/lib/

rsync -a "$BIN_DIR"/plugins/editors/librobotsMetamodel.so                   "$PWD"/../data/lib/plugins/editors/
rsync -a "$BIN_DIR"/librobots-interpreter-core.so*                          "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/plugins/tools/librobots-plugin.so                       "$PWD"/../data/lib/plugins/tools/
rsync -a "$BIN_DIR"/librobots-2d-model.so*                                  "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libBox2D.so*                                            "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/librobots-generator-base.so*                            "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/librobots-kit-base.so*                                  "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/librobots-utils.so*                                     "$PWD"/../data/lib/
rsync -a --remove-source-files "$PWD"/../data/externalToolsConfig/                                 "$PWD"/../data/bin/externalToolsConfig/
rsync -a "$BIN_DIR/run_maze_generator.sh"                                 "$PWD/../data/bin/"

# Cleaning up prebuild-common.sh results...
rm -rf "$PWD"/../data/plugins/
rsync -a --remove-source-files "$PWD"/../data/help/ "$PWD"/../data/resources/help/
rsync -a --remove-source-files "$PWD"/../data/images/ "$PWD"/../data/resources/images/
mv "$PWD"/../data/splashscreen.png "$PWD"/../data/bin/

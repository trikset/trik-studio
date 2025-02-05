#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"


mkdir -p "$PWD"/../data/lib/plugins/editors/
mkdir -p "$PWD"/../data/lib/plugins/tools/kitPlugins/
rsync -a "$BIN_DIR"/plugins/editors/libnxtMetamodel.so                                  "$PWD"/../data/lib/plugins/editors/
rsync -a "$BIN_DIR"/plugins/tools/kitPlugins/librobots-nxt-interpreter.so            "$PWD"/../data/lib/plugins/tools/kitPlugins/
rsync -a "$BIN_DIR"/plugins/tools/kitPlugins/librobots-nxt-osek-c-generator.so       "$PWD"/../data/lib/plugins/tools/kitPlugins/
rsync -a "$BIN_DIR"/librobots-nxt-generator-base.so*                                 "$PWD"/../data/lib
rsync -a "$BIN_DIR"/librobots-nxt-kit.so*                                            "$PWD"/../data/lib

# Cleaning up prebuild-common.sh results...
rm -rf "$PWD"/../data/plugins

cd "$PWD/../data/lib/"
ln -svf libusb-1.0.so libusb-1.0.so.0

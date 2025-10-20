#!/bin/bash
set -eux

cd "$(dirname "$0")"

source utils.sh
install_lmsasm https://github.com/ev3dev/lmsasm/releases/download/v1.5.0/lmsasm-v1.5.0-linux-amd64.zip "$PWD/../data/bin/ev3-tools"

mkdir -p "$PWD"/../data/lib/plugins/editors
mkdir -p "$PWD"/../data/lib/plugins/tools/kitPlugins
rsync -a "$BIN_DIR"/plugins/editors/libev3Metamodel.so                      "$PWD"/../data/lib/plugins/editors/
rsync -a "$BIN_DIR"/plugins/tools/kitPlugins/librobots-ev3-interpreter.so   "$PWD"/../data/lib/plugins/tools/kitPlugins/
rsync -a "$BIN_DIR"/plugins/tools/kitPlugins/librobots-ev3-rbf-generator.so "$PWD"/../data/lib/plugins/tools/kitPlugins/
rsync -a "$BIN_DIR"/librobots-ev3-kit.so*                                   "$PWD"/../data/lib
rsync -a "$BIN_DIR"/librobots-ev3-generator-base.so*                        "$PWD"/../data/lib

cp -L  "$(pkg-config --variable=libdir libusb-1.0)/libusb-1.0.so"         "$PWD"/../data/lib/libusb-1.0.so

# Cleaning up prebuild-common.sh results...
rm -rf "$PWD"/../data/plugins/
mkdir -p "$PWD"/../data/resources/examples/

rsync -av --remove-source-files "$PWD"/../data/examples/ "$PWD"/../data/resources/examples/

cd "$PWD"/../data/lib/
ln -svf libusb-1.0.so libusb-1.0.so.0

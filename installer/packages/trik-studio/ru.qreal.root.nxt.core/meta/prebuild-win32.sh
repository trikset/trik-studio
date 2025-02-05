#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"


rsync -a "$BIN_DIR"/plugins/editors/nxtMetamodel.dll                             "$PWD"/../data/plugins/editors/
rsync -a "$BIN_DIR"/plugins/tools/kitPlugins/robots-nxt-interpreter.dll          "$PWD"/../data/plugins/tools/kitPlugins/
rsync -a "$BIN_DIR"/plugins/tools/kitPlugins/robots-nxt-osek-c-generator.dll     "$PWD"/../data/plugins/tools/kitPlugins/
rsync -a "$BIN_DIR"/robots-nxt-generator-base.dll                                "$PWD"/../data/
rsync -a "$BIN_DIR"/robots-nxt-kit.dll                                           "$PWD"/../data/
rsync -a "$BIN_DIR"/libusb-1.0.dll                                               "$PWD"/../data

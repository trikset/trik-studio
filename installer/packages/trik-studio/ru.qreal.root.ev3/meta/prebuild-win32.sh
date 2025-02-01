#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"


rsync -a "$BIN_DIR"/plugins/editors/ev3Metamodel.dll                      "$PWD"/../data/plugins/editors/
rsync -a "$BIN_DIR"/plugins/tools/kitPlugins/robots-ev3-interpreter.dll   "$PWD"/../data/plugins/tools/kitPlugins/
rsync -a "$BIN_DIR"/plugins/tools/kitPlugins/robots-ev3-rbf-generator.dll "$PWD"/../data/plugins/tools/kitPlugins/
rsync -a "$BIN_DIR"/robots-ev3-kit.dll                                    "$PWD"/../data
rsync -a "$BIN_DIR"/robots-ev3-generator-base.dll                         "$PWD"/../data
rsync -a "$BIN_DIR"/libusb-1.0.dll                                        "$PWD"/../data

#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

rsync -a "$INSTALLER_ROOT"/licenses/Box2D-license*.txt                      "$PWD"

mkdir -p "$PWD"/../data/plugins/editors
mkdir -p "$PWD"/../data/plugins/tools
rsync -a  "$BIN_DIR"/help                                                    "$PWD"/../data
rsync -a  "$BIN_DIR"/images                                                  "$PWD"/../data
rsync -a  "$BIN_DIR"/palettes                                                "$PWD"/../data
rsync -a  "$BIN_DIR"/externalToolsConfig                                     "$PWD"/../data
rsync -a "$BIN_DIR"/splashscreen.png                                        "$PWD"/../data

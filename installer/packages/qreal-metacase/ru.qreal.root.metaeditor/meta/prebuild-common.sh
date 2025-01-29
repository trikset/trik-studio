#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p "$PWD"/../data/plugins/editors
rsync -a  "$BIN_DIR"/help                                                    "$PWD"/../data
rsync -a "$BIN_DIR"/splashscreen.png                                        "$PWD"/../data

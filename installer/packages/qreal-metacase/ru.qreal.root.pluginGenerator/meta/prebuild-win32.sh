#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

rsync -a "$BIN_DIR"/plugins/tools/metaEditorSupport.dll                        "$PWD"/../data/plugins/tools/
rsync -a "$BIN_DIR"/qrmc.dll                                                   "$PWD"/../data/

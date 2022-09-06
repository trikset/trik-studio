#!/bin/bash
set -xueo pipefail

cd "$(dirname "$0")"

mkdir -p "$PWD"/../data/plugins/editors
rsync -a "$BIN_DIR"/plugins/editors/trikMetamodel.dll                                  "$PWD"/../data/plugins/editors/
rsync -a "$BIN_DIR"/robots-trik-kit.dll                                                "$PWD"/../data/
rsync -a "$BIN_DIR"/robots-trik-kit-interpreter-common.dll                             "$PWD"/../data/

rsync -a "$BIN_DIR"/{2D-model.exe,checkapp.exe}                    "$PWD/../data/"

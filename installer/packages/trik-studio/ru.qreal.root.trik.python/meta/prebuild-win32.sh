#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

cp    $BIN_DIR/robots-trik-python-generator-library.dll                              $PWD/../data/
cp    $BIN_DIR/plugins/tools/kitPlugins/robots-trik-v62-python-generator.dll         $PWD/../data/plugins/tools/kitPlugins/

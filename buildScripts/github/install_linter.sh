#!/bin/bash
set -euxo pipefail

SCRIPT_DIR="$(dirname "$(realpath "${BASH_SOURCE[0]}")")"
source "$SCRIPT_DIR/utilities.sh"

sudo apt-get update && sudo apt-get install -y --no-install-recommends vera++ 

modules=("qtscript" "qtwaylandcompositor")
archives=("qtbase" "qtmultimedia" "qtsvg" "qtscript" "qttools" "qtserialport" "qtimageformats" "icu" "qtwayland" "qtdeclarative" "qttranslations" "qtsvgwidgets" "qtxmlpatterns" "qtwebenginewidgets" "qtwebkit" "qtwebkitwidgets")
install_qt linux desktop "$TRIK_QT_VERSION" "$HOME/Qt" $modules $archives
QT_ROOT_DIR=$(ls -1d "$HOME"/Qt/$TRIK_QT_VERSION*/gcc_64 | head -n 1)
echo "$QT_ROOT_DIR/bin" >> $GITHUB_PATH
export PATH="$QT_ROOT_DIR/bin:$PATH"

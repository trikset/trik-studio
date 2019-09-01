#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source $INSTALLER_ROOT/utils/mac_utils.sh

mkdir -p "$BUNDLE_CONTENTS/Lib"
mkdir -p "$BUNDLE_CONTENTS/MacOS"

copy_qt_lib QtMultimediaWidgets
copy_qt_lib QtOpenGL

cp   $BIN_DIR/gamepad "$BUNDLE_CONTENTS/MacOS"


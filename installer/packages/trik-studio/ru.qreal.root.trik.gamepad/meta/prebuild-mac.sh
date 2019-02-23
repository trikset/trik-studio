#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source $INSTALLER_ROOT/utils/mac_utils.sh

mkdir -p "$BUNDLE_CONTENTS/Lib"
mkdir -p "$BUNDLE_CONTENTS/MacOS"

copy_qt_lib QtMultimediaWidgets

cd "$PWD/../data/gamepad-build"
$QT_DIR/bin/qmake -nocache CONFIG+=release
make -j4
mv gamepad "$BUNDLE_CONTENTS/MacOS"

#rm -rf gamepad-build

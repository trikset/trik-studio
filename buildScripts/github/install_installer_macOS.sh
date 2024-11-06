#!/bin/bash
set -euxo pipefail

sudo hdiutil attach "$INSTALLER_EXT_NAME"
sudo cp -rf "/Volumes/$INSTALLER_NAME/$INSTALLER_NAME.app" $GITHUB_WORKSPACE
sudo hdiutil detach /Volumes/"$INSTALLER_NAME"
./$INSTALLER_NAME.app/Contents/MacOS/$INSTALLER_NAME --verbose --script trik_studio_installscript.qs

BIN_DIR=/Applications/TRIKStudio/bin && echo "BIN_DIR=$BIN_DIR" >> $GITHUB_ENV
LIB_DIR=/Applications/TRIKStudio/lib && echo "LIB_DIR=$LIB_DIR" >> $GITHUB_ENV
APP_DIR=/Applications/TRIKStudio && echo "APP_DIR=$APP_DIR" >> $GITHUB_ENV

ls /Applications/TRIKStudio/
export DYLD_LIBRARY_PATH="$LIB_DIR"
"$BIN_DIR"/2D-model --version
"$BIN_DIR"/checkapp --version
"$BIN_DIR"/patcher --version
"$APP_DIR"/maintenance --version
"$APP_DIR"/trik-studio --version

ls "*.dylib" | xargs otool -L | grep "not found" || exit 0
exit 1

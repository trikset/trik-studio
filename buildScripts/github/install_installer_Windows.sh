#!/bin/bash
set -eux

./"$INSTALLER_NAME" --verbose --script trik_studio_installscript.qs --mco "$CONCURRENCY"
  
PREFIX="/C"

BIN_DIR="$PREFIX"/TRIKStudio && echo "BIN_DIR=$BIN_DIR" >> $GITHUB_ENV
LIB_DIR="$PREFIX"/TRIKStudio && echo "LIB_DIR=$LIB_DIR" >> $GITHUB_ENV
APP_DIR="$PREFIX"/TRIKStudio && echo "APP_DIR=$APP_DIR" >> $GITHUB_ENV

export LD_LIBRARY_PATH="$LIB_DIR"
"$BIN_DIR"/2D-model.exe --version
"$APP_DIR"/maintenance.exe --version
"$APP_DIR"/trik-studio.exe --version
"$BIN_DIR"/patcher.exe --version

cd "$LIB_DIR"

# Find dependencies that have not been packaged, but are still in the system
ls -- *.dll* | xargs ldd | grep -Ev "not found$" | grep dll | sed -e '/^[^\t]/ d' | sed -e 's/\t//' \
	| sed -e 's/.*=..//' | sed -e 's/ (0.*)//' | grep -Ev "(System|SYSTEM)32.*dll.*" \ 
	| grep -Ev "$LD_LIBRARY_PATH"

ls -- *.dll* | xargs ldd | grep "not found" || exit 0
exit 1

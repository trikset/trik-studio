#!/bin/bash -x
# Usage: build-trik-studio.sh <path-to-qt> <path-to-qt-installer-framework> [<path-to-build-dir>]. See build-installer.sh for more info.

set -o nounset
set -o errexit

build_dir=
[ -z ${3+x} ] || build_dir=$(realpath $3)

SCRIPT_DIR=$(dirname "$0")

[ $OSTYPE == "linux-gnu" ] && EXCLUDE="-e ru.qreal.root.associations" || EXCLUDE=
grep -q "darwin" <<< $OSTYPE && EXCLUDE="-e ru.qreal.root.nxt.tools,ru.qreal.root.associations" || :
grep -q "darwin" <<< $OSTYPE && export PRODUCT_DISPLAYED_NAME="TRIK Studio" || :
chmod +x "$SCRIPT_DIR/build-installer.sh" && "$SCRIPT_DIR/build-installer.sh" "$1" "$2" trik-studio "$build_dir"

#!/bin/bash
# Usage: build-trik-studio-pioneer.sh <path-to-qt> <path-to-qt-installer-framework> [<path-to-build-dir>]. See build-installer.sh for more info.

set -euo pipefail

build_dir=
[ -z ${3+x} ] || build_dir=$(readlink -f $3)

cd "$(dirname "$0")"

[ $OSTYPE == "linux-gnu" ] && EXCLUDE="-e ru.qreal.root.associations" || EXCLUDE=
grep -q "darwin" <<< $OSTYPE && EXCLUDE="-e ru.qreal.root.associations" || :
grep -q "darwin" <<< $OSTYPE && export PRODUCT_DISPLAYED_NAME="TRIK Studio PIONEER" || :
chmod +x $PWD/build-installer.sh && $PWD/build-installer.sh $1 $2 trik-studio-pioneer $build_dir

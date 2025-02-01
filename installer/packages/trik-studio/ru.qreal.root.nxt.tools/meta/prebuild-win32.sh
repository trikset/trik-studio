#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source "$INSTALLER_ROOT"/utils/common_utils.sh

cd "$PWD"/../data

rsync -aR "$INSTALLER_ROOT"/./nxt-tools .
dos2unix nxt-tools/compile.sh
rm -rf bin

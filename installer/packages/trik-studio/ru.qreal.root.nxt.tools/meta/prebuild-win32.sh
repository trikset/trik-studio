#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source "$INSTALLER_ROOT"/utils/common_utils.sh

cd "$PWD"/../data

rsync -aR "$INSTALLER_ROOT"/./nxt-tools .
dos2unix nxt-tools/compile.sh
rm -rf bin
install_lmsasm https://github.com/ev3dev/lmsasm/releases/download/v1.5.0/lmsasm-v1.5.0-windows-amd64.zip .

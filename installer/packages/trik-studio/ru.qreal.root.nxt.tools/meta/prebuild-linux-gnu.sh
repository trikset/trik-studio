#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source "$INSTALLER_ROOT"/utils/common_utils.sh
mkdir "$PWD"/../data/bin
cd "$PWD"/../data/bin
rsync -a "$INSTALLER_ROOT"/nxt-tools  ./

install_lmsasm https://github.com/ev3dev/lmsasm/releases/download/v1.5.0/lmsasm-v1.5.0-linux-amd64.zip "$INSTALLER_ROOT"/ev3-tools


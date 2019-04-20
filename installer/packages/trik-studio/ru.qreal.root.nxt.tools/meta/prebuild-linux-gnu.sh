#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source $INSTALLER_ROOT/utils/common_utils.sh
mkdir $PWD/../data/bin
cd $PWD/../data/bin
cp -rf $INSTALLER_ROOT/nxt-tools/linux/nxt-tools -t .

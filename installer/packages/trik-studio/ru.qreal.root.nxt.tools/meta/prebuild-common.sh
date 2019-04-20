#!/bin/bash
set -o nounset
set -o errexit

source $INSTALLER_ROOT/utils/common_utils.sh

cd "$(dirname "$0")"
rm -rf ../data
mkdir -p $PWD/../data/

if [ ! -d $INSTALLER_ROOT/nxt-tools ]
then
  git submodule update --init --recursive $INSTALLER_ROOT/nxt-tools
fi
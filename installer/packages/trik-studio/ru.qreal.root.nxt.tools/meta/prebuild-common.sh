#!/bin/bash
set -o nounset
set -o errexit

source $INSTALLER_ROOT/utils/common_utils.sh

cd "$(dirname "$0")"
rm -rf ../data
mkdir -p $PWD/../data/

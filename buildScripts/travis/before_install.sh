#!/bin/bash
set -euxo pipefail
case $TRAVIS_OS_NAME in
  osx)
#    brew update
    ;;
  linux)
    docker pull trikset/linux-builder
   ;;
  *) exit 1 ;;
esac

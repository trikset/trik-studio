#!/bin/bash
set -euxo pipefail
$EXECUTOR env CCACHE_CONFIGPATH="$CCACHE_CONFIGPATH" ccache -s
case $TRAVIS_OS_NAME in
  osx)
    ;;
  linux)
    docker stop builder
    ;;
  *) exit 1 ;;
esac

#!/bin/bash
set -euxo pipefail
case $TRAVIS_OS_NAME in
  osx)
  ;;
  linux)
    docker pull trikset/linux-builder
    docker run -d -v $HOME:$HOME:rw -w `pwd` --name builder trikset/linux-builder Xvfb :0
  ;;
  *) exit 1 ;;
esac

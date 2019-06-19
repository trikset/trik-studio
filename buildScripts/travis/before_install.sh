#!/bin/bash
set -euxo pipefail
case $TRAVIS_OS_NAME in
  osx)
      brew bundle install && brew bundle check --verbose || brew update && brew bundle install && brew bundle check --verbose
    ;;
  linux)
    docker pull trikset/linux-builder
   ;;
  *) exit 1 ;;
esac

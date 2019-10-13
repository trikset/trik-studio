#!/bin/bash
set -euxo pipefail

rm -f build.log

case $TRAVIS_OS_NAME in
  osx)
    [ -d "$TRIK_QT/5.12.5" ] || plugins/robots/thirdparty/trikRuntime/trikRuntime/scripts/install_qt_mac.sh "$TRIK_QT" >> build.log 2>&1 & QT_INSTALLER_PID=$!
    export HOMEBREW_NO_AUTO_UPDATE=1
    brew tap "hudochenkov/sshpass"
    brew install ccache coreutils libusb pkg-config gnu-sed sshpass
    wait $QT_INSTALLER_PID
    ;;
  linux)
    docker pull trikset/linux-builder
    docker run -d -v $HOME:$HOME:rw -w `pwd` --name builder trikset/linux-builder Xvfb :0
    ;;
  *) exit 1 ;;
esac

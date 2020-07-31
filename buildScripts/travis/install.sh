#!/bin/bash
set -euxo pipefail

rm -f build.log

case $TRAVIS_OS_NAME in
  osx)
#    [ -d "$TRIK_QT/5.12.7" ] || plugins/robots/thirdparty/trikRuntime/trikRuntime/scripts/install_qt_mac.sh "$TRIK_QT" >> build.log 2>&1 & QT_INSTALLER_PID=$!
    export HOMEBREW_NO_INSTALL_CLEANUP=1
    export HOMEBREW_NO_AUTO_UPDATE=1
    brew tap "hudochenkov/sshpass"
    TRIK_BREW_PACKAGES="ccache coreutils libusb pkg-config gnu-sed sshpass qt p7zip"
    for pkg in $TRIK_BREW_PACKAGES ; do
      p="${pkg##*/}"
      p="${p%.*}"
      brew install "$pkg" || brew upgrade "$pkg" || brew link --force "$pkg" || echo "Failed to install/upgrade $pkg"
    done
#    brew install $TRIK_BREW_PACKAGES || brew upgrade $TRIK_BREW_PACKAGES
#    wait $QT_INSTALLER_PID
#    echo "FINISHED Qt installation"
#    find $TRIK_QT/5.12.7 -name qmake -perm +111 -type f -or -type l
    [ -d $HOME/qtifw ] || env TRIK_QT_INSTALL_DIR=$HOME/qtifw buildScripts/travis/install_qtifw_mac.sh
    ;;
  linux)
    docker pull trikset/linux-builder
    docker run -d -v $HOME:$HOME:rw -w `pwd` --name builder trikset/linux-builder Xvfb :0
    ;;
  *) exit 1 ;;
esac

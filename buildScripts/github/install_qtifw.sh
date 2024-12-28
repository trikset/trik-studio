#!/bin/bash
set -xueo pipefail

TRIK_QTIFW_INSTALL_DIR=${TRIK_QTIFW_INSTALL_DIR:-$HOME/TRIK_QtIfw}
SCRIPT_DIR=$(dirname ${BASH_SOURCE[0]})
QTIFW_VERSION=${QTIFW_VERSION:-4.6.1}

case "`uname`" in
  Darwin)
    D=/tmp/qtifw-installer.dmg
    test -r "$D" || curl -L -o "$D" "http://download.qt-project.org/official_releases/qt-installer-framework/$QTIFW_VERSION/QtInstallerFramework-macOS-x64-${QTIFW_VERSION}.dmg"
    P=$(hdiutil attach "$D" -noverify -noautofsck | grep -o '/Volumes/.*$')
    I=$(find "$P" -type f -perm +1 -path '*Contents/MacOS/*' -print | head -n 1 )
    env TRIK_QT_INSTALL_DIR="$TRIK_QTIFW_INSTALL_DIR" "$I" --verbose --no-force-installations --show-virtual-components --script "$SCRIPT_DIR/../../plugins/robots/thirdparty/trikRuntime/trikRuntime/docker/qt_scriptinstall.qs"
   du -csh "$TRIK_QTIFW_INSTALL_DIR"/* | sort -h
    ;;
  Linux)
    curl --output qtifw.zip "https://dl.trikset.com/.qtifw/qtifw-4.0.zip"
    7za x -o"$HOME" qtifw.zip
    echo "QTIFWBIN=$TRIK_QTIFW_INSTALL_DIR/bin"  >> $GITHUB_ENV
    ;;
  *) exit 1 ;;
esac

#remove garbage. No way to deselect this in installer script.
rm -rf "$TRIK_QTIFW_INSTALL_DIR"/{doc,examples,Uninstaller.app,Uninstaller.dat}

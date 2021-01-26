#!/bin/bash -x
TRIK_QT_INSTALL_DIR=${TRIK_QT_INSTALL_DIR:-$HOME/TRIK_QtIfw}
SCRIPT_DIR=$(dirname ${BASH_SOURCE[0]})
set -ueo pipefail
QTIFW_VERSION=4.0.1
D=/tmp/qtifw-installer.dmg
test -r "$D" || curl -L -o "$D" "http://download.qt-project.org/official_releases/qt-installer-framework/$QTIFW_VERSION/QtInstallerFramework-mac-x64.dmg"
P=$(hdiutil attach "$D" -noverify -noautofsck | grep -o '/Volumes/.*$')
I=$(find "$P" -type f -perm +1 -path '*Contents/MacOS/*' -print | head -n 1 )
env TRIK_QT_INSTALL_DIR="$TRIK_QT_INSTALL_DIR" "$I" --verbose --no-force-installations --show-virtual-components --script "$SCRIPT_DIR/../../plugins/robots/thirdparty/trikRuntime/trikRuntime/docker/qt_scriptinstall.qs"

#remove garbage. No way to deselect this in installer script.
rm -rf "$TRIK_QT_INSTALL_DIR"/{doc,examples,Uninstaller.app,Uninstaller.dat}

du -csh "$TRIK_QT_INSTALL_DIR"/* | sort -h

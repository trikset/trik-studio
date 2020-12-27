#!/bin/bash
    set -euo pipefail
    export HOMEBREW_NO_INSTALL_CLEANUP=1
    export HOMEBREW_NO_AUTO_UPDATE=1
    brew tap "hudochenkov/sshpass"
    TRIK_BREW_PACKAGES="ccache coreutils libusb pkg-config gnu-sed sshpass qt p7zip"
    for pkg in $TRIK_BREW_PACKAGES ; do
      p="${pkg##*/}"
      p="${p%.*}"
      brew install "$pkg" || brew upgrade "$pkg" || brew link --force "$pkg" || echo "Failed to install/upgrade $pkg"
    done
    [ -d $HOME/qtifw ] || env TRIK_QT_INSTALL_DIR="$HOME/qtifw" "$(dirname $(realpath ${BASH_SOURCE[0]}))"/install_qtifw_mac.sh

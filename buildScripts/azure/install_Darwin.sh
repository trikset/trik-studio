#!/bin/bash
    set -euo pipefail
    export HOMEBREW_NO_INSTALL_CLEANUP=1
    export HOMEBREW_NO_AUTO_UPDATE=1
    brew tap "hudochenkov/sshpass"
    TRIK_BREW_PACKAGES="ccache coreutils libusb pkg-config gnu-sed sshpass p7zip python@3.${TRIK_PYTHON3_VERSION_MINOR}"
    for pkg in $TRIK_BREW_PACKAGES ; do
      p="${pkg##*/}"
      p="${p%.*}"
      brew install "$pkg" || brew upgrade "$pkg" || brew link --force "$pkg" || echo "Failed to install/upgrade $pkg"
    done
    TRIK_PYTHON=python3.${TRIK_PYTHON3_VERSION_MINOR}
    "$TRIK_PYTHON" -m pip install -U pip
    "$TRIK_PYTHON" -m pip install aqtinstall
    "$TRIK_PYTHON" -m aqt install-qt -m qtscript -O "$HOME/Qt" mac desktop "${TRIK_QT_VERSION}"
    [ -d $HOME/qtifw ] || env TRIK_QT_INSTALL_DIR="$HOME/qtifw" "$(dirname $(realpath ${BASH_SOURCE[0]}))"/install_qtifw_mac.sh
    # Force SDK version compatible with Qt 5.12
    system_profiler -json SPDeveloperToolsDataType | jq '.SPDeveloperToolsDataType[].spdevtools_path' || :
    sudo xcode-select -s /Applications/Xcode_13.1.app/Contents/Develope
    xcodebuild -showsdks
    xcrun -sdk macosx --show-sdk-path

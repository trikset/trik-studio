#!/bin/bash
set -euxo pipefail
BUILD_INSTALLER=${BUILD_INSTALLER:-true}
TRIK_QT_VERSION=${TRIK_QT_VERSION:-5.15}
XCODE_VERSION=${XCODE_VERSION:-15.3}
SCRIPT_DIR="$(dirname "$(realpath "${BASH_SOURCE[0]}")")"

source "$SCRIPT_DIR/utilities.sh"

case "$(uname)" in
  Darwin)
    export HOMEBREW_NO_INSTALL_CLEANUP=1
    export HOMEBREW_NO_AUTO_UPDATE=1
    TRIK_PYTHON3_VERSION_PATCH=${TRIK_PYTHON3_VERSION_PATCH:-0}
    brew tap "hudochenkov/sshpass"
    TRIK_BREW_PACKAGES="ccache coreutils pkg-config gnu-sed sshpass p7zip"
    for pkg in $TRIK_BREW_PACKAGES ; do
      p="${pkg##*/}"
      p="${p%.*}"
      brew install --quiet "$pkg" || brew upgrade "$pkg" || brew link --force "$pkg" || echo "Failed to install/upgrade $pkg"
    done
    modules=("qtscript")
    
    PYTHON_VERSION="3.${TRIK_PYTHON3_VERSION_MINOR}.$TRIK_PYTHON3_VERSION_PATCH"
    PYTHON_INSTALLER_NAME="python-$PYTHON_VERSION-macos11.pkg"
    PYTHON_DOWNLOAD_URL="https://www.python.org/ftp/python/$PYTHON_VERSION/${PYTHON_INSTALLER_NAME}"
    curl -o "/tmp/${PYTHON_INSTALLER_NAME}" "${PYTHON_DOWNLOAD_URL}"
    sudo installer -pkg "/tmp/${PYTHON_INSTALLER_NAME}" -target /

    MACPORTS_PKG="MacPorts-2.11.6-14-Sonoma.pkg"
    MACPORTS_URL="https://github.com/macports/macports-base/releases/download/v2.11.6/${MACPORTS_PKG}"
    curl -L --fail --output "${MACPORTS_PKG}" "${MACPORTS_URL}"
    sudo installer -pkg "${MACPORTS_PKG}" -target /
    export PATH="/opt/local/bin:$PATH"
    sudo port selfupdate
    sudo port install libusb +universal

    install_qt mac desktop "${TRIK_QT_VERSION}" "$HOME/Qt" $modules
    sudo xcode-select -s /Applications/Xcode_${XCODE_VERSION}.app/Contents/Developer
    xcodebuild -showsdks
    xcrun -sdk macosx --show-sdk-path
    ;;
  Linux)
    ID=$(grep '^ID=' /etc/os-release | cut -d'=' -f2)
    
    if [ "$ID" = "altlinux" ]; then
      sudo apt-get update && sudo apt-get install -y gcc-c++ curl xz p7zip-standalone rsync libusb-devel \
      libudev-devel libGL-devel libGLX-mesa python3-dev zlib-devel make ccache python3-module-pip time \
      qt5-multimedia-devel qt5-svg-devel qt5-script-devel qt5-tools qt5-serialport-devel
    elif [ "$ID" = "ubuntu" ]; then
      sudo apt-get update && sudo apt-get install -y --no-install-recommends ccache curl libusb-1.0-0-dev \
      make qtscript5-dev qttools5-dev-tools qtmultimedia5-dev libqt5serialport5-dev libqt5svg5-dev \
      libudev-dev "$TRIK_PYTHON"-dev qtbase5-private-dev qtwayland5 libqscintilla2-qt5-dev libquazip5-dev libbox2d-dev
    elif [[ "$ID" = "rocky" || "$ID" = '"rocky"' ]]; then
      GCC_VERSION=${GCC_VERSION:-13}
      sudo yum update -y &&  sudo yum install -y --setopt=install_weak_deps=False epel-release
      sudo yum install --allowerasing -y --setopt=install_weak_deps=False sudo which libusbx-devel curl \
      wget make gcc-toolset-"$GCC_VERSION"-{gcc-c++,libasan-devel,libubsan-devel,gdb} git-core ccache \
      zlib-devel rsync "$TRIK_PYTHON"-{devel,pip,urllib3} mesa-libGL-devel systemd-devel fontconfig p7zip xz time findutils
  
      #no desire to enumerate all required libraries for QtIFw
      # pulseaudio-libs-glib2 to run TS and 2D-model even with `minimal` platform
      sudo yum install -y --setopt=install_weak_deps=False pulseaudio-libs-glib2 libxkbcommon-x11 qt5-qtbase-gui  libwayland-{server,client,cursor}

      echo $INSTALL_INSTALLER_ENVIRONMENT
      if [ "$INSTALL_INSTALLER_ENVIRONMENT" != "true" ]; then
        sudo yum install -y --setopt=install_weak_deps=False qt5-qtscript-devel qt5-qttools-devel qt5-qtmultimedia-devel qt5-qtserialport-devel \
        qt5-qtsvg-devel qt5-qtbase-devel qt5-qtbase-private-devel qt5-qtwayland
      else
        sudo yum install -y --setopt=install_weak_deps=False libX11-xcb libXext libxkbcommon-x11 fontconfig freetype libXrender
        #libQt5WaylandCompositor.so.5.15: libQt5Quick.so.5 libQt5Qml.so.5 libQt5QmlModels.so.5 
        modules=("qtscript" "qtwaylandcompositor")
        archives=("qtbase" "qtmultimedia" "qtsvg" "qtscript" "qttools" "qtserialport" "qtimageformats" "icu" "qtwayland" "qtdeclarative" "qttranslations")
        install_qt linux desktop "$TRIK_QT_VERSION" "$HOME/Qt" $modules $archives
        QT_ROOT_DIR=$(ls -1d "$HOME"/Qt/$TRIK_QT_VERSION*/gcc_64 | head -n 1)
        echo "$QT_ROOT_DIR/bin" >> $GITHUB_PATH
      fi
      echo "source scl_source enable gcc-toolset-$GCC_VERSION" >> ~/.bash_profile
    fi
    ;;
  *) exit 1 ;;
esac

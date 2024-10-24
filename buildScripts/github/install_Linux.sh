#!/bin/bash
set -euxo pipefail

ID=$(grep '^ID=' /etc/os-release | cut -d'=' -f2)
BUILD_INSTALLER=${BUILD_INSTALLER:-false}
GCC_VERSION=${GCC_VERSION:-13}
TRIK_PYTHON="python3.${TRIK_PYTHON3_VERSION_MINOR}"

if [ "$ID" = "altlinux" ]; then
  apt-get update && apt-get install -y gcc-c++ curl xz p7zip-standalone rsync libusb-devel \
  libudev-devel libGL-devel libGLX-mesa python3-dev zlib-devel make ccache python3-module-pip time \
  qt5-multimedia-devel qt5-svg-devel qt5-script-devel qt5-tools qt5-serialport-devel
elif [ "$ID" = "ubuntu" ]; then
  sudo apt-get update && sudo apt-get install -y --no-install-recommends \
  ccache curl libusb-1.0-0-dev make qtscript5-dev qttools5-dev-tools qtmultimedia5-dev libqt5serialport5-dev libqt5svg5-dev \
  libudev-dev python3.${TRIK_PYTHON3_VERSION_MINOR}-dev qtbase5-private-dev qtwayland5
elif [[ "$ID" = "rocky" || "$ID" = '"rocky"' ]]; then
  yum update -y && yum install -y epel-release
  yum install --allowerasing -y sudo which libusbx-devel curl wget make gcc-toolset-"$GCC_VERSION"-{gcc-c++,libasan-devel,libubsan-devel,gdb} \
  git-core ccache zlib-devel rsync "$TRIK_PYTHON"-{devel,pip,urllib3} mesa-libGL-devel systemd-devel fontconfig p7zip xz time
  yum install -y libxkbcommon-x11 qt5-qtbase-gui #no desire to enumerate all required libraries for QtIFw
  yum install -y pulseaudio-libs-glib2 # to run TS and 2D-model even with `minimal` platform
  yum install -y qt5-qtscript-devel qt5-qttools-devel qt5-qtmultimedia-devel qt5-qtserialport-devel qt5-qtsvg-devel qt5-qtbase-devel qt5-qtbase-private-devel \
  qt5-qtwayland-devel
  echo "source scl_source enable gcc-toolset-$GCC_VERSION" >> ~/.bash_profile
fi

if [ "$BUILD_INSTALLER" = "true" ]; then
  "$TRIK_PYTHON" -m pip install -U pip
  "$TRIK_PYTHON" -m pip install aqtinstall
  "$TRIK_PYTHON" -m aqt install-tool -O $PWD/Qt linux desktop tools_ifw
fi

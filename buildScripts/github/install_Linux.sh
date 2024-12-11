#!/bin/bash
set -euxo pipefail

ID=$(grep '^ID=' /etc/os-release | cut -d'=' -f2)
GCC_VERSION=${GCC_VERSION:-13}

if [ "$ID" = "altlinux" ]; then
  sudo apt-get update && sudo apt-get install -y gcc-c++ curl xz p7zip-standalone rsync libusb-devel \
  libudev-devel libGL-devel libGLX-mesa python3-dev zlib-devel make ccache python3-module-pip time \
  qt5-multimedia-devel qt5-svg-devel qt5-script-devel qt5-tools qt5-serialport-devel
elif [ "$ID" = "ubuntu" ]; then
  sudo apt-get update && sudo apt-get install -y --no-install-recommends \
  ccache curl libusb-1.0-0-dev make qtscript5-dev qttools5-dev-tools qtmultimedia5-dev libqt5serialport5-dev libqt5svg5-dev \
  libudev-dev python3-dev qtbase5-private-dev qtwayland5
elif [[ "$ID" = "rocky" || "$ID" = '"rocky"' ]]; then
  sudo yum update -y &&  sudo yum install -y --setopt=install_weak_deps=False epel-release
  sudo yum install --allowerasing -y --setopt=install_weak_deps=False sudo which libusbx-devel curl wget make gcc-toolset-"$GCC_VERSION"-{gcc-c++,libasan-devel,libubsan-devel,gdb} \
  git-core ccache zlib-devel rsync python3.${TRIK_PYTHON3_VERSION_MINOR}-{devel,pip,urllib3} mesa-libGL-devel systemd-devel fontconfig p7zip xz time
  sudo yum install -y --setopt=install_weak_deps=False libxkbcommon-x11 qt5-qtbase-gui #no desire to enumerate all required libraries for QtIFw
  sudo yum install -y --setopt=install_weak_deps=False pulseaudio-libs-glib2 # to run TS and 2D-model even with `minimal` platform
  sudo yum install -y --setopt=install_weak_deps=False qt5-qtscript-devel qt5-qttools-devel qt5-qtmultimedia-devel qt5-qtserialport-devel qt5-qtsvg-devel qt5-qtbase-devel qt5-qtbase-private-devel \
  qt5-qtwayland
  echo "source scl_source enable gcc-toolset-$GCC_VERSION" >> ~/.bash_profile
fi

#!/bin/bash
set -euxo pipefail

ID=$(grep '^ID=' /etc/os-release | cut -d'=' -f2)

if [ "$ID" = "altlinux" ]; then
    apt-get update && apt-get install -y gcc-c++ curl xz p7zip-standalone rsync libusb-devel \
    libudev-devel libGL-devel libGLX-mesa python3-dev zlib-devel make ccache python3-module-pip time \
    rsync qt5-multimedia-devel qt5-svg-devel qt5-script-devel qt5-tools qt5-serialport-devel
else
    docker pull trikset/linux-builder
    docker run --cap-add SYS_PTRACE -d -v $HOME:$HOME:rw -w `pwd` --name builder trikset/linux-builder Xvfb :0
    docker exec builder git config --global --add safe.directory '*'
fi

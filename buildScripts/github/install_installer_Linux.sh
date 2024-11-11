#!/bin/bash
set -eux

ID=$(grep '^ID=' /etc/os-release | cut -d'=' -f2)

if [ "$ID" = "altlinux" ]; then
  sudo apt-get update && sudo apt-get install -y libxkbcommon-x11 libX11 fontconfig libxcbutil-icccm \
  libxcbutil-image libdbus libxcbutil-keysyms libxcb-render-util
elif [ "$ID" = "ubuntu" ]; then
  sudo apt-get update && sudo apt-get install -y --no-install-recommends libxkbcommon-x11-0 libxcb-icccm4 libxcb-image0 \
  libxcb-keysyms1 libxcb-randr0 libxcb-render-util0 libxcb-sync1 libxcb-xfixes0 \
  libxcb-shape0 libx11-xcb1 libfreetype6 libfontconfig1 libdbus-1-3
elif [ "$ID" = "arch" ]; then
  sudo pacman -Sy && sudo pacman -S libxkbcommon-x11 xcb-util-wm xcb-util-image xcb-util-keysyms xcb-util-renderutil fontconfig libx11 --noconfirm
elif [[ "$ID" = "rocky" || "$ID" = '"rocky"' ]]; then
  sudo yum update -y && sudo yum install -y --setopt=install_weak_deps=False libxkbcommon-x11 xcb-util-wm libX11 xcb-util-image \
  dbus-libs xcb-util-keysyms xcb-util-renderutil fontconfig libX11-xcb
fi

INSTALLER_NAME="$INSTALLER_NAME.run"
chmod +x "$INSTALLER_NAME"

# Default value --- 0
./"$INSTALLER_NAME" --verbose --script trik_studio_installscript.qs --platform minimal --mco "$CONCURRENCY"
  
PREFIX=/opt
if [ "$ID" = "ubuntu" ]; then
  PREFIX="$HOME"
fi

BIN_DIR="$PREFIX"/TRIKStudio/bin && echo "BIN_DIR=$BIN_DIR" >> $GITHUB_ENV
LIB_DIR="$PREFIX"/TRIKStudio/lib && echo "LIB_DIR=$LIB_DIR" >> $GITHUB_ENV
APP_DIR="$PREFIX"/TRIKStudio && echo "APP_DIR=$APP_DIR" >> $GITHUB_ENV

export QT_QPA_PLATFORM=minimal
export LD_LIBRARY_PATH="$LIB_DIR"
"$BIN_DIR"/2D-model --version
"$APP_DIR"/maintenance --version
"$APP_DIR"/trik-studio --version
"$BIN_DIR"/patcher --version

cd "$LIB_DIR"

# Find dependencies that have not been packaged, but are still in the system
ls -- *.so* | xargs ldd | grep -Ev "not found$" | grep so | sed -e '/^[^\t]/ d' | sed -e 's/\t//' \
         | sed -e 's/.*=..//' | sed -e 's/ (0.*)//' | grep -Ev "lib(c|dl|m|pthread|rt)\.so.*" \
         | grep -Ev "$LD_LIBRARY_PATH" | grep -Ev "ld|linux-vdso"

ls -- *.so* | xargs ldd | grep "not found" || exit 0
exit 1

#!/bin/bash
set -euxo pipefail

GCC_VERSION=${GCC_VERSION:-13}

TRIK_PYTHON="python3.${TRIK_PYTHON3_VERSION_MINOR}"
TRIK_QT_VERSION=${TRIK_QT_VERSION:-5.15}

yum update -y && yum install -y epel-release
yum install --allowerasing -y sudo which libusbx-devel curl wget make gcc-toolset-"$GCC_VERSION"-{gcc-c++,libasan-devel,libubsan-devel,gdb} \
git-core ccache zlib-devel rsync "$TRIK_PYTHON"-{devel,pip,urllib3} mesa-libGL-devel systemd-devel fontconfig p7zip xz time
yum install -y libxkbcommon-x11 qt5-qtbase-gui
yum install -y pulseaudio-libs-glib2
echo "source scl_source enable gcc-toolset-$GCC_VERSION" >> ~/.bash_profile

"$TRIK_PYTHON" -m pip install -U pip
"$TRIK_PYTHON" -m pip install aqtinstall
"$TRIK_PYTHON" -m aqt install-qt linux desktop "$TRIK_QT_VERSION" -O /Qt -m qtscript --archives qtbase qtmultimedia qtsvg qtscript qttools qtserialport qtimageformats icu qtwayland
            
QT_ROOT_DIR=$(ls -1d /Qt/$TRIK_QT_VERSION*/gcc_64 | head -n 1)
echo "$QT_ROOT_DIR/bin" >> $GITHUB_PATH
            
if [ "$BUILD_INSTALLER" = "true" ]; then
  "$TRIK_PYTHON" -m pip install -U pip
  "$TRIK_PYTHON" -m pip install aqtinstall
  "$TRIK_PYTHON" -m aqt install-tool -O /Qt linux desktop tools_ifw
fi

#!/bin/bash
set -euxo pipefail

GCC_VERSION=${GCC_VERSION:-13}

TRIK_PYTHON="python3.${TRIK_PYTHON3_VERSION_MINOR}"
TRIK_QT_VERSION=${TRIK_QT_VERSION:-5.15}

sudo yum update -y && sudo yum install -y --setopt=install_weak_deps=False epel-release
sudo yum install --allowerasing -y --setopt=install_weak_deps=False which libusbx-devel curl wget make gcc-toolset-"$GCC_VERSION"-{gcc-c++,libasan-devel,libubsan-devel,gdb} \
git-core ccache zlib-devel rsync "$TRIK_PYTHON"-{devel,pip,urllib3} mesa-libGL-devel systemd-devel fontconfig p7zip xz time findutils
sudo yum install -y --setopt=install_weak_deps=False pulseaudio-libs-glib2 qt5-qtbase-gui libwayland-{server,client,cursor} libxkbcommon-x11
echo "source scl_source enable gcc-toolset-$GCC_VERSION" >> ~/.bash_profile

"$TRIK_PYTHON" -m venv venv
. ./venv/bin/activate
"$TRIK_PYTHON" -m pip install -U pip
"$TRIK_PYTHON" -m pip install aqtinstall
"$TRIK_PYTHON" -m aqt install-qt linux desktop "$TRIK_QT_VERSION" -O "$HOME"/Qt -m qtscript qtwaylandcompositor --archives qtbase qtmultimedia qtsvg qtscript \
qttools qtserialport qtimageformats icu qtwayland qtdeclarative 

#libQt5WaylandCompositor.so.5.15: libQt5Quick.so.5 libQt5Qml.so.5 libQt5QmlModels.so.5 

QT_ROOT_DIR=$(ls -1d "$HOME"/Qt/$TRIK_QT_VERSION*/gcc_64 | head -n 1)
echo "$QT_ROOT_DIR/bin" >> $GITHUB_PATH

if [ "$BUILD_INSTALLER" = "true" ]; then
  "$TRIK_PYTHON" -m aqt install-tool -O "$HOME"/Qt linux desktop tools_ifw
fi
deactivate

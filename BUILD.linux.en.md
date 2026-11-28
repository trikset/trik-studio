# Building TRIK Studio on Linux

These instructions cover Ubuntu 22.04, the Linux distribution used by the project's CI build. Other distributions need equivalent Qt 5 and system development packages.

## Install dependencies

```bash
sudo apt update
sudo apt install build-essential ccache git pkg-config \
  qt5-qmake qtbase5-dev qtbase5-dev-tools qtbase5-private-dev \
  qtscript5-dev qttools5-dev-tools qtmultimedia5-dev \
  libqt5serialport5-dev libqt5svg5-dev qtwayland5 \
  libqscintilla2-qt5-dev libquazip5-dev \
  libusb-1.0-0-dev libudev-dev zlib1g-dev python3.10-dev
```

Check that Qt 5 and Python 3.10 are available:

```bash
qmake -v
python3.10 --version
```

## Get the source

```bash
git clone --recurse-submodules https://github.com/trikset/trik-studio.git
cd trik-studio
```

## Configure and build

Run qmake from a separate build directory:

```bash
mkdir build
cd build
qmake ../studio.pro \
  PYTHON_VERSION=3.10 \
  PYTHON_PATH=/usr \
  CONFIG+=release \
  CONFIG+=noPch \
  CONFIG+=no-sanitizers \
  CONFIG+=use_system_qscintilla2 \
  CONFIG+=use_system_quazip
make -j"$(nproc)" qmake_all
make -j"$(nproc)"
```

The application is built as `build/bin/trik-studio`.

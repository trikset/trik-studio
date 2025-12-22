#!/bin/bash
set -euxo pipefail
TRIK_PYTHON3_VERSION_MINOR=${TRIK_PYTHON3_VERSION_MINOR:-11}
TRIK_PYTHON=python3.${TRIK_PYTHON3_VERSION_MINOR}

install_qt(){
  # Usage: install_qt <os> <platform-type> <qt-version> <path-to-install-qt> <modules> <archives>
  # TODO: add <addittional-options>
  "$TRIK_PYTHON" -m venv venv
  . ./venv/bin/activate
  "$TRIK_PYTHON" -m pip install -U pip
  "$TRIK_PYTHON" -m pip install aqtinstall
  if [ -z "${6+x}" ]; then
    "$TRIK_PYTHON" -m aqt install-qt "$1" "$2" "$3" -O "$4" -m "${modules[@]}"
  else
    "$TRIK_PYTHON" -m aqt install-qt "$1" "$2" "$3" -O "$4" -m "${modules[@]}" --archives "${archives[@]}"
  fi
  if [ "$BUILD_INSTALLER" = "true" ]; then
    [ -d $HOME/qtifw ] || env TRIK_QTIFW_INSTALL_DIR="$HOME/qtifw" "$(dirname $(realpath ${BASH_SOURCE[0]}))"/install_qtifw.sh
  fi
  deactivate
}

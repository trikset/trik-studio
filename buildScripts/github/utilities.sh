#!/usr/bin/env bash
set -euxo pipefail
TRIK_PYTHON3_VERSION_MINOR=${TRIK_PYTHON3_VERSION_MINOR:-11}
TRIK_PYTHON=python3.${TRIK_PYTHON3_VERSION_MINOR}

get_array_by_name() {
  # Bash expansion (works on 3.2+ for macOS too)

  #Check for output var to be declared before call as an array
  if ! declare -p get_array_by_name_result 2>/dev/null | grep -q ' -a '; then
    echo "Error: 'get_array_by_name_result' variable must be declared as an array before calling get_array_by_name." >&2
    return 1
  fi
  local name="${1:-}"
  # Check that referenced by name one is defined as an array
  if declare -p "$name" 2>/dev/null | grep -q ' -a '; then
    local ref="${name}[@]"
    get_array_by_name_result=("${!ref}")
  else
    get_array_by_name_result=()
    echo "Error: '$name' is not a defined indexed array." >&2
    return 1
  fi
}


install_qt(){
  # Usage: install_qt <os> <platform-type> <qt-version> <path-to-install-qt> <modules> <archives>
  # TODO: add <addittional-options>
  "$TRIK_PYTHON" -m venv venv
  . ./venv/bin/activate
  "$TRIK_PYTHON" -m pip install -U pip
  "$TRIK_PYTHON" -m pip install aqtinstall
  local -a cmd=("$TRIK_PYTHON" -m aqt install-qt "$1" "$2" "$3" -O "$4")


  local -a get_array_by_name_result=() #declare before call
  [[ -n "$5:-" ]] && get_array_by_name "${5}" && (( ${#get_array_by_name_result[@]} > 0 )) && cmd+=("-m" "${get_array_by_name_result[@]}")
  [[ -n "$6:-" ]] && get_array_by_name "${6}" && (( ${#get_array_by_name_result[@]} > 0 )) && cmd+=("--archives" "${get_array_by_name_result[@]}")

  "${cmd[@]}"

  if [ "$BUILD_INSTALLER" = "true" ]; then
    [ -d $HOME/qtifw ] || env TRIK_QTIFW_INSTALL_DIR="$HOME/qtifw" "$(dirname $(realpath ${BASH_SOURCE[0]}))"/install_qtifw.sh
  fi
  deactivate
  rm -rf venv
}

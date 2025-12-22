#!/bin/bash
set -xuevo pipefail
TRIK_LINTER_OK=true
if which vera++ >/dev/null 2>&1 ; then buildScripts/github/runVera++.sh || TRIK_LINTER_OK=false ; fi

TRIK_STUDIO_DIR=$(pwd)
TRIK_CONFIGURE_DIR=$(mktemp -d)
pushd "$TRIK_CONFIGURE_DIR"
qmake -r CONFIG+=autolupdate "$TRIK_STUDIO_DIR" || TRIK_LINTER_OK=false
popd

buildScripts/github/checkStatus.sh || TRIK_LINTER_OK=false
"$TRIK_LINTER_OK"

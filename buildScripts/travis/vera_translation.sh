#!/bin/bash
set -xuevo pipefail
TRIK_LINTER_OK=true
if which vera++ >/dev/null 2>&1 ; then buildScripts/travis/runVera++.sh || TRIK_LINTER_OK=false ; fi
LUPDATE=lupdate
which lupdate-pro >/dev/null 2>&1 && LUPDATE=lupdate-pro
$LUPDATE studio.pro plugins/robots/editor/*/translations.pro || TRIK_LINTER_OK=false
buildScripts/travis/checkStatus.sh || TRIK_LINTER_OK=false
"$TRIK_LINTER_OK"

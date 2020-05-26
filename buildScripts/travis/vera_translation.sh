#!/bin/bash
set -xuevo pipefail
TRIK_LINTER_OK=true
$EXECUTOR buildScripts/travis/runVera++.sh || TRIK_LINTER_OK=false
$EXECUTOR bash -lic 'lupdate studio.pro plugins/robots/editor/*/translations.pro' && $EXECUTOR buildScripts/travis/checkStatus.sh || TRIK_LINTER_OK=false

"$TRIK_LINTER_OK" || :

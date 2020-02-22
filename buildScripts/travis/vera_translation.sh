#!/bin/bash
set -xuevo pipefail
TRIK_LINTER_OK=true
$EXECUTOR buildScripts/travis/runVera++.sh || TRIK_LINTER_OK=false
git_diff=$( { git diff --diff-filter=d --name-only "${TRAVIS_COMMIT_RANGE}" || true ; } \
  | xargs -r file -i | sed -e "s|\(.*\):.*text/x-c.*|\1|g" -e "/:/d")
[[ -z "${git_diff}" ]] || $EXECUTOR bash -lic 'vera++ --error --root buildScripts/vera++ --profile strict' <<< "$git_diff" || TRIK_LINTER_OK=false

$EXECUTOR bash -lic 'lupdate studio.pro plugins/robots/editor/*/translations.pro' && $EXECUTOR buildScripts/travis/checkStatus.sh || TRIK_LINTER_OK=false

"$TRIK_LINTER_OK"

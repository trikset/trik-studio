#!/bin/bash
set -xueo pipefail
BUILDSCRIPTS=$(realpath $(dirname $(realpath "${BASH_SOURCE[0]}"))/..)
tclsh "$BUILDSCRIPTS"/vera++/generatePaths.tcl
vera++ --error -p allRules --root "$BUILDSCRIPTS"/vera++ < "$BUILDSCRIPTS"/vera++/params

git_diff=$( { git diff --diff-filter=d --name-only "${COMMIT_RANGE}" || true ; } \
  | xargs -r file -i | sed -e "s|\(.*\):.*text/x-c.*|\1|g" -e "/:/d")
  [[ -z "${git_diff}" ]] || vera++ --error --root "$BUILDSCRIPTS"/vera++ --profile strict <<< "$git_diff"

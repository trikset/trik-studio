#!/bin/bash
# Returns zero status code only if commit contains only IGNORED_FILES
set -xueo pipefail
IGNORED_FILES='*.md .cirrus.yml appveyor.yml buildScripts/docker/*'
COMMIT_FILES=$(git diff --name-only ${TRAVIS_COMMIT_RANGE} || true)
for f in ${COMMIT_FILES:-"_UNDEFINED_FOR_TAGS_"} ; do
  ! ( for pattern in $IGNORED_FILES ; do [[ $f != $pattern ]] || exit 1 ; done ) || exit 1
done

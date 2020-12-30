#!/bin/bash
set -xueo pipefail
BUILDSCRIPTS=$(realpath $(dirname $(realpath "${BASH_SOURCE[0]}"))/..)
tclsh "$BUILDSCRIPTS"/vera++/generatePaths.tcl
vera++ --error -p allRules --root "$BUILDSCRIPTS"/vera++ < "$BUILDSCRIPTS"/vera++/params
if [ -z "${COMMIT_RANGE+x}" ]
then
	if [ -n "${TRAVIS_COMMIT_RANGE+x}" ]
	then
		COMMIT_RANGE="${TRAVIS_COMMIT_RANGE}"
	elif [ -n "${CIRCLE_COMPARE_URL+x}" ]
	then
		COMMIT_RANGE=$(echo "${CIRCLE_COMPARE_URL}" | cut -d/ -f7)
		if [[ $COMMIT_RANGE != *"..."* ]]; then
			COMMIT_RANGE="${COMMIT_RANGE}...${COMMIT_RANGE}"
		fi
	else
		COMMIT_RANGE="upstream/master...HEAD"
	fi
fi
git_diff=$( { git diff --diff-filter=d --name-only "${COMMIT_RANGE}" || true ; } \
  | xargs -r file -i | sed -e "s|\(.*\):.*text/x-c.*|\1|g" -e "/:/d")
  [[ -z "${git_diff}" ]] || vera++ --error --root "$BUILDSCRIPTS"/vera++ --profile strict <<< "$git_diff"


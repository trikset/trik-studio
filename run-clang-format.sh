#!/bin/bash
set -xeuo pipefail

VERSION=$(clang-format${1+-$1} --version \
    | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+')

echo -e "20.0.0\n$VERSION" | sort -CV || {
    echo "clang-format >= 20.0.0 required"
    exit 1
}

IGNORED_DIRS=(
    "./plugins/robots/thirdparty"
    "./qrgui/thirdparty"
    "./buildScripts"
    "./thirdparty"
    "./installer"
)

IGNORE_CMD=""

for DIR in "${IGNORED_DIRS[@]}"; do
    IGNORE_CMD+=" -path $DIR -o"
done

IGNORE_CMD=${IGNORE_CMD% -o}

find . \( $IGNORE_CMD \) -prune -o -name '*.cpp' -print0 -o -name '*.h' -print0 | xargs -0 clang-format${1+-$1} --style=file -i

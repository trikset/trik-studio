#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p "$PWD"/../data/translations
ls "$QT_TRANSLATIONS"

rsync -avR "$BIN_DIR"/translations/./* "$PWD"/../data/translations/

#Cannot handle complex paths, to be ported to NULL-terminated strings later
for code in $(find "$PWD"/../data/translations -maxdepth 1 -type d -name '??' -exec basename -a {} + ) ; do
   ls -1d "$QT_TRANSLATIONS"/*${code}.qm
done | rsync -v --files-from=- "$PWD"/../data/translations/

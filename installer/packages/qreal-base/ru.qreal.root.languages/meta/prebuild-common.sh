#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p "$PWD"/../data/translations
rsync -avR "$BIN_DIR"/translations/./* "$PWD"/../data/translations/

#Cannot handle complex paths, to be ported to NULL-terminated strings later
TS_LANGUAGES=$(find "$PWD"/../data/translations -maxdepth 1 -type d -name '??' -exec basename -a {} +)
echo --- Transfer Qt translations for '(' $TS_LANGUAGES ')' from "$QT_TRANSLATIONS" --
for code in $TS_LANGUAGES ; do
   ls -1d "$QT_TRANSLATIONS"/*_${code}.qm
done | xargs basename -a | LANG=C.UTF-8 sort | tee /dev/stderr | rsync -q --files-from=- "$QT_TRANSLATIONS"/ "$PWD"/../data/translations/

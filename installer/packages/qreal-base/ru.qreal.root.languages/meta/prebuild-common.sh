#!/bin/bash
set -o nounset
set -o errexit
set -o pipefail

cd "$(dirname "$0")"

mkdir -p "$PWD"/../data/translations
rsync -avR "$BIN_DIR"/translations/./* "$PWD"/../data/translations/

# Qt does not provide system translations for Vietnamese (vi) yet. Keep vi in the
# list so it starts working automatically when *_vi.qm files appear, but skip it
# while there are no such files.

#Cannot handle complex paths, to be ported to NULL-terminated strings later
TS_LANGUAGES=$(find "$PWD"/../data/translations -maxdepth 1 -type d -name '??' -exec basename -a {} +)
echo --- Transfer Qt translations for '(' $TS_LANGUAGES ')' from "$QT_TRANSLATIONS" --
for code in $TS_LANGUAGES ; do
   if [ "$code" = "vi" ] && ! compgen -G "$QT_TRANSLATIONS/*_vi.qm" > /dev/null ; then
      continue
   fi
   ls -1d "$QT_TRANSLATIONS"/*_${code}.qm
done | xargs basename -a | LANG=C.UTF-8 sort | while IFS= read -r file ; do
   printf '%s\n' "$file" >&2
   printf '%s\n' "$file"
done | rsync -q --files-from=- "$QT_TRANSLATIONS"/ "$PWD"/../data/translations/

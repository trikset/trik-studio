#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p "$PWD"/../data/translations
rsync -a "$BIN_DIR"/translations/fr "$PWD"/../data/translations
ls "$QT_TRANSLATIONS"
rsync -a "$QT_TRANSLATIONS"/*fr.qm "$PWD"/../data/translations

#!/bin/bash -x
TRIK_STUDIO_INSTALL_DIR=${TRIK_STUDIO_INSTALL_DIR:-$HOME/TRIKStudio}
SCRIPT_DIR=$(dirname ${BASH_SOURCE[0]})
set -ueo pipefail
TRIK_STUDIO_INSTALLER=${TRIK_STUDIO_INSTALLER:-/tmp/trik-studio-installer.dmg}
test -r "$TRIK_STUDIO_INSTALLER" || curl -L -o "$TRIK_STUDIO_INSTALLER" https://dl.trikset.com/ts/fresh/installer/trik-studio-installer-mac-master.dmg
P=$(hdiutil attach "$TRIK_STUDIO_INSTALLER" -noverify -noautofsck | grep -o '/Volumes/.*$')
I=$(find "$P" -type f -perm +1 -path '*Contents/MacOS/*' -print | head -n 1 )
if [ -d "$TRIK_STUDIO_INSTALL_DIR" ]; then
  echo "ERROR: folder exists, uninstall, please, $TRIK_STUDIO_INSTALL_DIR"
else
  env TRIK_STUDIO_INSTALL_DIR="$TRIK_STUDIO_INSTALL_DIR" "$I" --verbose --show-virtual-components --script "$SCRIPT_DIR/trik_studio_installscript.qs"
fi

#!/bin/bash
set -xueo pipefail

cd "$(dirname "$0")"

mkdir -p $PWD/../data/plugins/editors
cp    $BIN_DIR/plugins/editors/trikMetamodel.dll                                  $PWD/../data/plugins/editors/
cp    $BIN_DIR/robots-trik-qts-generator-library.dll                              $PWD/../data/
cp    $BIN_DIR/robots-trik-generator-base.dll                                     $PWD/../data/
cp    $BIN_DIR/robots-trik-kit.dll                                                $PWD/../data/
cp    $BIN_DIR/robots-trik-kit-interpreter-common.dll                             $PWD/../data/

cp    "$BIN_DIR"/trikPythonQt*.dll                                                "$PWD"/../data/
cp    $BIN_DIR/trikControl.dll                                                    $PWD/../data/
cp    $BIN_DIR/trikScriptRunner.dll                                               $PWD/../data/
cp    $BIN_DIR/trikHal.dll                                                        $PWD/../data/
cp    $BIN_DIR/trikKernel.dll                                                     $PWD/../data/
cp    $BIN_DIR/trikNetwork.dll                                                    $PWD/../data/
cp    $BIN_DIR/python3*.dll                                                       $PWD/../data/
cp    $BIN_DIR/vcruntime*.dll                                                     $PWD/../data/

cp    "$BIN_DIR"/{system.js,TRIK.py,2D-model.exe,checkapp.exe}                    "$PWD/../data/"

winscp_ver=5.17.10
putty_ver=0.75
cache_dir="$(cygpath $APPDATA)"/$PRODUCT/installer_cache
mkdir -p "$cache_dir"
cd "$cache_dir"

# may be need anouther check about all winscp/putty files
if [ ! -d PuTTY_$putty_ver ]
then
# download putty
putty_server="https://the.earth.li/~sgtatham/putty/$putty_ver/"
mkdir -p PuTTY_$putty_ver

for file in putty puttygen pageant
do
  curl -L -s -o PuTTY_$putty_ver/$file.exe $putty_server/w32/$file.exe &
done
curl -L -s -o PuTTY_$putty_ver/putty.chm $putty_server/putty.chm &
# end of download putty
fi

if [ ! -d winscp_$winscp_ver ]
then
# download winscp
winscp_zip="https://sourceforge.net/projects/winscp/files/WinSCP/$winscp_ver/WinSCP-$winscp_ver-Portable.zip"

curl -v -L -s -o winscp.zip $winscp_zip
unzip -o winscp.zip -d winscp_$winscp_ver
rm -f winscp.zip
# end of download winscp
fi

WAIT_EXIT_CODE=0
wait || WAIT_EXIT_CODE=$?
if (( $WAIT_EXIT_CODE != 0 && $WAIT_EXIT_CODE != 127 )) ; then ( exit $W ) ; fi

cd "$(dirname "$0")"/../data
cp -r "$cache_dir"/winscp_$winscp_ver winscp
cp -r "$cache_dir"/PuTTY_$putty_ver winscp/PuTTY
cp -f winscp/license.txt "$(dirname "$0")"/WinScp-license.txt

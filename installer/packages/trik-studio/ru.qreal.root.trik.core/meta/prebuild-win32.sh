#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p $PWD/../data/plugins/editors
cp    $BIN_DIR/plugins/editors/trikMetamodel.dll                                  $PWD/../data/plugins/editors/
cp    $BIN_DIR/robots-trik-qts-generator-library.dll                              $PWD/../data/
cp    $BIN_DIR/robots-trik-generator-base.dll                                     $PWD/../data/
cp    $BIN_DIR/robots-trik-kit.dll                                                $PWD/../data/
cp    $BIN_DIR/robots-trik-kit-interpreter-common.dll                             $PWD/../data/

cp    $BIN_DIR/qslog.dll                                                          $PWD/../data/
cp    $BIN_DIR/PythonQt*.dll                                                      $PWD/../data/
cp    $BIN_DIR/trikControl.dll                                                    $PWD/../data/
cp    $BIN_DIR/trikScriptRunner.dll                                               $PWD/../data/
cp    $BIN_DIR/trikHal.dll                                                        $PWD/../data/
cp    $BIN_DIR/trikKernel.dll                                                     $PWD/../data/
cp    $BIN_DIR/trikNetwork.dll                                                    $PWD/../data/
cp    $BIN_DIR/python3*.dll                                                       $PWD/../data/
cp    $BIN_DIR/vcruntime*.dll                                                     $PWD/../data/

cp    $BIN_DIR/system.js                                                          $PWD/../data/bin/
cp    $BIN_DIR/system.py                                                          $PWD/../data/bin/

winscp_ver=5.15
putty_ver=0.71
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

curl -L -s -o winscp.zip $winscp_zip
unzip -o winscp.zip -d winscp_$winscp_ver
rm -f winscp.zip
# end of download winscp
fi

wait

cd "$(dirname "$0")"/../data
cp -r "$cache_dir"/winscp_$winscp_ver winscp
cp -r "$cache_dir"/PuTTY_$putty_ver winscp/PuTTY
cp -f winscp/license.txt "$(dirname "$0")"/WinScp-license.txt

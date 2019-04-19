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

# download putty and winscp
cache_dir=$(cygpath -m $APPDATA | xargs cygpath)/$PRODUCT/installer_cache
putty_server="https://the.earth.li/~sgtatham/putty/0.71/"
winscp_file="https://sourceforge.net/projects/winscp/files/WinSCP/5.15/WinSCP-5.15-Portable.zip"
mkdir -p $cache_dir/winscp/PuTTY

for file in putty puttygen pageant
do
  curl -L -s -o $cache_dir/winscp/PuTTY/$file.exe $putty_server/w32/$file.exe &
done
curl -L -s -o $cache_dir/winscp/PuTTY/putty.chm $putty_server/putty.chm &

curl -L -s -o $cache_dir/winscp.zip https://sourceforge.net/projects/winscp/files/WinSCP/5.15/WinSCP-5.15-Portable.zip
unzip -o $cache_dir/winscp.zip -d $cache_dir/winscp
rm -f $cache_dir/winscp.zip
wait
# end of download

cd "$(dirname "$0")"/../data
cp -r $cache_dir/winscp .
cp -f winscp/license.txt "$(dirname "$0")"/WinScp-license.txt

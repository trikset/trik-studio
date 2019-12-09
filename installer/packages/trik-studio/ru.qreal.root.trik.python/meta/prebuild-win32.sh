#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

cp    $BIN_DIR/robots-trik-python-generator-library.dll                              $PWD/../data/
cp    $BIN_DIR/plugins/tools/kitPlugins/robots-trik-v62-python-generator.dll         $PWD/../data/plugins/tools/kitPlugins/

unix_path=$BIN_DIR/python3.dll
win_path="$(cygpath -w $unix_path)"
python_ver=$(powershell -command "(Get-Item $win_path).VersionInfo.ProductVersion")
cache_dir="$(cygpath $APPDATA)"/$PRODUCT/installer_cache
if [ -z $(file -b $BIN_DIR/trik-studio | grep -Eo "^PE32 ") ] ; then PY_BIT=amd64 ; else PY_BIT=win32 ; fi
mkdir -p "$cache_dir"
cd "$cache_dir"

if [ ! -d PYTHON_$python_ver ]
then
# download python
echo Download python ver $python_ver
python_zip="https://www.python.org/ftp/python/$python_ver/python-$python_ver-embed-$PY_BIT.zip"

curl -L -s -o python.zip $python_zip
unzip -o python.zip -d PYTHON_$python_ver
rm -f python.zip
# end of download python
fi

cd "$(dirname "$0")"/../data
cp -r "$cache_dir"/PYTHON_$python_ver/python*.zip .

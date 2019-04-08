#!/bin/bash -x
# Copyright 2015 CyberTech Labs Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set -o nounset
set -o errexit

function check_qmake_version {

#	echo Here
	make -f <(echo -e "-include $1/Makefile\ncheck_qmake_version: FORCE\n\t@echo \${QMAKE}") check_qmake_version
}

function show_help {
	echo "Usage: $(basename $0) [QREAL_DIR [FIELDS_DIR EXAMPLES_DIR TASKS_DIR INPUTS_DIR] ]"
	echo -e "QREAL_DIR\t-\tPath to QReal sources root"
	echo "                    Defaults to \"../..\""
	echo -e "FIELDS_DIR\t-\tPath to directory with prepared fields."
	echo "                                   Defaults to \"$$PWD/fields/fields\""
	echo -e "EXAMPLES_DIR\t-\tPath to examples dir"
	echo "                                     Defaults to \"$$PWD/solutions\""
	echo -e "TASKS_DIR\t-\tPath to folder with saves with tasks."
	echo "                                  Defaults to \"$$PWD/tasks\""
	echo -e "INPUTS_DIR\t-\tPath to directory with with inputs."
	echo "                                  Defaults to \"$$PWD/inputs>.\""
	echo "Example: ./$(basename $0) ~/Qt/5.7 ~/stepic-examples"
	exit 0
}

[ "$*" == "--help" ] && show_help || :

pushd "$(dirname "$0")"

if [ "$#" -ge 1 ]; then
	qRealDir=$(readlink -f $1)
else
	qRealDir=$(readlink -f ../..)
fi

QMAKE=$(check_qmake_version $qRealDir)
echo "Using qmake: $QMAKE"
QT_HOST_DATA=$($QMAKE -query QT_HOST_DATA)
QT_INSTALL_PLUGINS=$($QMAKE -query QT_INSTALL_PLUGINS)
QT_INSTALL_LIBS=$($QMAKE -query QT_INSTALL_LIBS)
QT_HOST_LIBS=$($QMAKE -query QT_HOST_LIBS)

qtDir=$(readlink -f $QT_HOST_DATA)
qtDirForPlugins=$(readlink -f $QT_INSTALL_PLUGINS)
qtDirLib=$(readlink -f $QT_INSTALL_LIBS)
hostDirLib=$(readlink -f $QT_HOST_LIBS)

export LD_LIBRARY_PATH=$hostDirLib:$qtDirLib:${LD_LIBRARY_PATH:-}

COPY="cp -rfP"
NEED_QT_LIBS=true

fieldsDir=$(readlink -f ${2:-$PWD/fields})
examplesDir=$(readlink -f ${3:-$PWD/solutions})
tasksDir=$(readlink -f ${4:-$PWD/tasks})
inputsDir=$(readlink -f ${5:-$PWD/inputs})

rm -rf trikStudio-checker
mkdir -p trikStudio-checker/bin
pushd trikStudio-checker/bin

copy_required_libs() {
	# simple function to copy all "libXXX.so*" dependencies for ELF executable
	set -ueo pipefail
	set +x
	local targetLibsDir=$1
	shift
	local binaries="$@"
	local libs=$(env LD_LIBRARY_PATH=$targetLibsDir:$LD_LIBRARY_PATH ldd $binaries \
		| grep so | sed -e '/^[^\t]/ d' | sed -e 's/\t//' | sed -e 's/.*=..//' | sed -e 's/ (0.*)//' \
		| xargs realpath -L -s | sort -u | grep -Ev "^$(realpath -e $targetLibsDir)|linux-vdso|^/lib/|^/lib64/")
	local rsync="rsync -av"
	
	for lib in ${libs}; do rsync="$rsync ${lib}*" ; done
	$rsync ${targetLibsDir}
}

if $NEED_QT_LIBS ; then
    ${COPY} $qtDirForPlugins/iconengines .

    mkdir -p imageformats
    ${COPY} $qtDirForPlugins/imageformats/libqsvg.so imageformats/

    mkdir -p platforms
    ${COPY} $qtDirForPlugins/platforms/libqminimal.so platforms/
fi

# Copying QReal libraries
rsync -av $qRealDir/bin/release/changelog.txt \
$qRealDir/bin/release/libqrgraph.so* \
$qRealDir/bin/release/libqrgui-brand-manager.so* \
$qRealDir/bin/release/libqrgui-controller.so* \
$qRealDir/bin/release/libqrgui-dialogs.so* \
$qRealDir/bin/release/libqrgui-editor.so* \
$qRealDir/bin/release/libqrgui-facade.so* \
$qRealDir/bin/release/libqrgui-meta-meta-model.so* \
$qRealDir/bin/release/libqrgui-models.so* \
$qRealDir/bin/release/libqrgui-mouse-gestures.so* \
$qRealDir/bin/release/libqrgui-plugin-manager.so* \
$qRealDir/bin/release/libqrgui-preferences-dialog.so* \
$qRealDir/bin/release/libqrgui-text-editor.so* \
$qRealDir/bin/release/libqrgui-thirdparty.so* \
$qRealDir/bin/release/libqrgui-tool-plugin-interface.so* \
$qRealDir/bin/release/libqrkernel.so* \
$qRealDir/bin/release/libqrrepo.so* \
$qRealDir/bin/release/libqrtext.so* \
$qRealDir/bin/release/libqrutils.so* \
$qRealDir/bin/release/libqscintilla2.so* \
$qRealDir/bin/release/libqslog.so* \
$qRealDir/bin/release/libqrtext.so* .

# Copying TRIKStudio plugins
rsync -av $qRealDir/bin/release/libqextserialport.so* \
$qRealDir/bin/release/librobots-2d-model.so* \
$qRealDir/bin/release/librobots-interpreter-core.so* \
$qRealDir/bin/release/librobots-trik-kit-interpreter-common.so* \
$qRealDir/bin/release/librobots-kit-base.so* \
$qRealDir/bin/release/librobots-trik-kit.so* \
$qRealDir/bin/release/librobots-utils.so* \
$qRealDir/bin/release/libPythonQt*.so* \
$qRealDir/bin/release/libBox2D.so* .


rsync -avR $qRealDir/bin/release/./translations/ru/*.qm \
	$qRealDir/bin/release/./translations/ru/plugins/robots/	\
	./

rsync -avR $qRealDir/bin/release/./plugins/editors/* $qRealDir/bin/release/./plugins/tools/librobots-plugin.so \
	$qRealDir/bin/release/./plugins/tools/kitPlugins/librobots-trik-v6-interpreter.so \
	$qRealDir/bin/release/./plugins/tools/kitPlugins/librobots-trik-v62-interpreter.so \
	./

# Copying TRIKRuntime dependencies
rsync -avR $qRealDir/bin/release/./libtrik*.so* \
	$qRealDir/bin/release/./*.js \
	$qRealDir/bin/release/./*.py \
	./

# Copying checker itself
cp -fP $qRealDir/bin/release/2D-model .
cp -fP $qRealDir/bin/release/patcher .
cp -fP $qRealDir/bin/release/check-solution.sh .

#Now copy all the denendencies for all the executables into single target folder
copy_required_libs . $(find . -type f -executable)

cd ..
cp -fP $qRealDir/bin/release/checker.sh .

# Copying fields, examples and tasks
cp -r $fieldsDir ./fields
cp -r $examplesDir ./examples
cp -r $tasksDir ./tasks

#It saves few megabytes.
find . -type f -executable | xargs strip -sv || : 

# Packing
popd

rm -f trik_checker.tar.xz
time { tar c trikStudio-checker | xz -z3ecvT 0 > trik_checker.tar.xz ; }

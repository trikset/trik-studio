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

[[ $(uname -s) == Linux ]] || exit 42

function check_qmake_version {

#	echo Here
	make -f <(echo -e "-include $1/Makefile\ncheck_qmake_version: FORCE\n\t@echo \${QMAKE}") check_qmake_version
}

function show_help {
	echo "Usage: $(basename $0) [QREAL_DIR [FIELDS_DIR EXAMPLES_DIR TASKS_DIR INPUTS_DIR] ]"
	echo -e "QREAL_DIR\t-\tPath to QReal sources root"
	echo "                    Defaults to $(dirname "$0")"
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


if [ "$#" -ge 1 ]; then
	qRealDir=$(realpath $1)
else
	qRealDir=$(realpath "$(dirname "$0")")
fi

pushd $qRealDir

QMAKE=$(check_qmake_version $qRealDir/..)
echo "Using qmake: $QMAKE"
QT_HOST_DATA=$($QMAKE -query QT_HOST_DATA)
QT_INSTALL_PLUGINS=$($QMAKE -query QT_INSTALL_PLUGINS)
QT_INSTALL_LIBS=$($QMAKE -query QT_INSTALL_LIBS)
QT_HOST_LIBS=$($QMAKE -query QT_HOST_LIBS)

qtDir=$(realpath $QT_HOST_DATA)
qtDirForPlugins=$(realpath $QT_INSTALL_PLUGINS)
qtDirLib=$(realpath $QT_INSTALL_LIBS)
hostDirLib=$(realpath $QT_HOST_LIBS)

export LD_LIBRARY_PATH=$hostDirLib:$qtDirLib:${LD_LIBRARY_PATH:-}

COPY="cp -rfP"
NEED_QT_LIBS=true

fieldsDir=$(realpath ${2:-$PWD/fields})
examplesDir=$(realpath ${3:-$PWD/solutions})
tasksDir=$(realpath ${4:-$PWD/tasks})
inputsDir=$(realpath ${5:-$PWD/inputs})

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
    ${COPY} $qtDirForPlugins/imageformats/libq{svg,jpeg}.so imageformats/

    mkdir -p platforms
    ${COPY} $qtDirForPlugins/platforms/libqminimal.so platforms/
fi

# Copying QReal libraries
rsync -av $qRealDir/changelog.txt \
$qRealDir/libqrgraph.so* \
$qRealDir/libqrgui-brand-manager.so* \
$qRealDir/libqrgui-controller.so* \
$qRealDir/libqrgui-dialogs.so* \
$qRealDir/libqrgui-editor.so* \
$qRealDir/libqrgui-facade.so* \
$qRealDir/libqrgui-meta-meta-model.so* \
$qRealDir/libqrgui-models.so* \
$qRealDir/libqrgui-mouse-gestures.so* \
$qRealDir/libqrgui-plugin-manager.so* \
$qRealDir/libqrgui-preferences-dialog.so* \
$qRealDir/libqrgui-text-editor.so* \
$qRealDir/libqrgui-thirdparty.so* \
$qRealDir/libqrgui-tool-plugin-interface.so* \
$qRealDir/libqrkernel.so* \
$qRealDir/libqrrepo.so* \
$qRealDir/libqrtext.so* \
$qRealDir/libqrutils.so* \
$qRealDir/libtrikqscintilla2.so* \
$qRealDir/libqrtext.so* .

# Copying TRIKStudio plugins
rsync -av $qRealDir/librobots-2d-model.so* \
$qRealDir/librobots-interpreter-core.so* \
$qRealDir/librobots-trik-kit-interpreter-common.so* \
$qRealDir/librobots-kit-base.so* \
$qRealDir/librobots-trik-kit.so* \
$qRealDir/librobots-utils.so* \
$qRealDir/libBox2D.so* .

rsync -av $qRealDir/librobots-ev3-kit.so* \
$qRealDir/librobots-utils.so* \
$qRealDir/librobots-kit-base.so* \
.

rsync -av $qRealDir/librobots-nxt-kit.so* .

rsync -avR $qRealDir/./translations/ru/*.qm \
	$qRealDir/./translations/ru/plugins/robots/	\
	./

rsync -avR $qRealDir/./plugins/editors/* $qRealDir/./plugins/tools/librobots-plugin.so \
	$qRealDir/./plugins/tools/kitPlugins/librobots-*-interpreter.so \
	./

# Copying TRIKRuntime dependencies
rsync -avR $qRealDir/./libtrik*.so* \
	$qRealDir/./*.js \
	$qRealDir/./*.py \
	./

# Copying checker itself
cp -fP $qRealDir/2D-model .
cp -fP $qRealDir/patcher .
cp -fP $qRealDir/check-solution.sh .

#Now copy all the denendencies for all the executables into single target folder
copy_required_libs . $(find . -type f -executable -o -name '*.so' )

cd ..
cp -fP $qRealDir/checker.sh .

# Copying fields, examples and tasks
cp -r $fieldsDir ./fields || :
cp -r $examplesDir ./examples || :
cp -r $tasksDir ./tasks || :

#It saves few megabytes.
find . -type f -executable | xargs strip -sv || : 

# Packing
popd

if [[ -z "${TRIK_SKIP_CHECKER_ARCHIVE+x}" ]] ; then
   rm -f trik_checker.tar.xz
   time { tar c trikStudio-checker | xz -z3ecvT 0 > trik_checker.tar.xz ; }
fi

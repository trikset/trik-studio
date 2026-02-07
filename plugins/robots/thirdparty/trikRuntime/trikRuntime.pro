# Copyright 2016 QReal Research Group
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

TEMPLATE = subdirs
include(../../../../global.pri)

CONFIG += trik_not_brick
cache(CONFIG, set)

SUBDIRS += \
	trikKernel \
	trikNetwork \
	trikControl \
	trikHal \
	trikCommunicator \
	trikScriptRunner \
	mlx90640-library \
#	translations \

EXTERNAL_SETTINGS = $$PWD/trikRuntimeExternal.pri
cache(EXTERNAL_SETTINGS, set stash super)

trikRuntime_use_local_qslog {
    SUBDIRS += trikRuntimeQsLog
    trikRuntimeQsLog.file = $$PWD/trikRuntime/qslog/QsLogSharedLibrary.pro
    EXTERNAL_SETTINGS =
    cache(EXTERNAL_SETTINGS, set stash super)
    trikKernel.depends = trikRuntimeQsLog
}

tests {
	SUBDIRS *= tests
	tests.depends = trikScriptRunner trikCommunicator trikKernel
	tests.subdir = $$PWD/trikRuntime/tests
}

!trik_nopython {
    SUBDIRS += PythonQt
    trikScriptRunner.depends += PythonQt
    PythonQt.subdir = $$PWD/trikRuntime/PythonQt
}
trikScriptRunner.subdir = $$PWD/trikRuntime/trikScriptRunner
trikCommunicator.subdir = $$PWD/trikRuntime/trikCommunicator
trikKernel.subdir = $$PWD/trikRuntime/trikKernel
trikNetwork.subdir = $$PWD/trikRuntime/trikNetwork
trikControl.subdir = $$PWD/trikRuntime/trikControl
translations.subdir = $$PWD/trikRuntime/translations
trikHal.subdir = $$PWD/trikRuntime/trikHal
mlx90640-library.subdir = $$PWD/trikRuntime/mlx90640-library

trikControl.depends = trikKernel trikHal mlx90640-library
trikNetwork.depends = trikKernel
trikScriptRunner.depends += trikControl trikKernel trikNetwork
trikHal.depends = trikKernel
trikCommunicator.depends = trikScriptRunner
OTHER_FILES += trikRuntime/trikRuntime.pro

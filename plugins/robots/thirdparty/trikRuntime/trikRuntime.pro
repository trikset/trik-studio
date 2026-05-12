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
CONFIG += exclude_init_internal_types
cache(CONFIG, set)

SUBDIRS += \
	trikKernel \
	trikNetwork \
	trikControl \
	trikCommunicator \
	trikScriptRunner \
#	translations \

EXTERNAL_SETTINGS = $$PWD/trikRuntimeExternal.pri

trikRuntime_use_local_qslog {
    SUBDIRS += trikRuntimeQsLog
    trikRuntimeQsLog.file = $$PWD/trikRuntime/qslog/QsLogSharedLibrary.pro
    EXTERNAL_SETTINGS =
    trikKernel.depends = trikRuntimeQsLog
}

cache(EXTERNAL_SETTINGS, set stash super)

!trik_nopython {
    SUBDIRS += PythonQt
    trikScriptRunner.depends += PythonQt
    PythonQt.subdir = $$PWD/trikRuntime/PythonQt
}
trikScriptRunner.subdir = $$PWD/trikRuntime/trikScriptRunner
trikCommunicator.subdir = $$PWD/trikRuntime/trikCommunicator
trikKernel.subdir = $$PWD/trikRuntime/trikKernel
trikNetwork.subdir = $$PWD/trikRuntime/trikNetwork
trikControl.file = $$PWD/trikControl.pri
translations.subdir = $$PWD/trikRuntime/translations

trikControl.depends = trikKernel
trikNetwork.depends = trikKernel
trikScriptRunner.depends += trikControl trikKernel trikNetwork
trikCommunicator.depends = trikScriptRunner
OTHER_FILES += trikRuntime/trikRuntime.pro

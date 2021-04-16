# Copyright 2007-2015 QReal Research Group
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

include(../global.pri)

QMAKE_LRELEASE_FLAGS = -nounfinished -removeidentical
TRANSLATIONS = $$files($$PWD/*.ts, true)
OTHER_FILES = $$TRANSLATIONS

#TODO: Migrate to 'CONFIG+=lrelease' feature
# Obsolete but working...
TRANSLATIONS_DIR=$$system_quote($$GLOBAL_DESTDIR/translations/)
win32:TRANSLATIONS_DIR=$$system(cygpath -u $$TRANSLATIONS_DIR)
SHELL_PWD=$$PWD
win32:SHELL_PWD=$$system(cygpath -u $$SHELL_PWD)
system(bash -c $$system_quote(find $$shell_quote($$SHELL_PWD) -name '*.ts' -print0 | xargs -0 $$[QT_HOST_BINS/get]/lrelease $$QMAKE_LRELEASE_FLAGS ))
system(bash -c $$system_quote(find $$shell_quote($$SHELL_PWD/./) -name '*.qm' -print0 | rsync -avRi --remove-source-files --files-from=- --from0 / $$TRANSLATIONS_DIR))
system(bash -c $$system_quote(rsync -vrdmR  --include='*/' --include='*.ini' --exclude='*' ./ $$TRANSLATIONS_DIR))

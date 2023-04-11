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

win32:if(!build_pass|isEmpty(BUILDS)) {
	system(cmd /C "DEL /s *.qm")
	system(cmd /C "for /R %G in (*.ts) do lrelease -nounfinished -removeidentical %G")
        !silent:verboseXCOPY=/f
        system(cmd.exe /C "xcopy $$system_quote(*.qm) $$system_quote($$system_path($$GLOBAL_DESTDIR/translations/)) /s /e /y /i $$verboseXCOPY")
}

unix:if(!build_pass|isEmpty(BUILDS)) {
        system(mkdir -p $$system_quote($$GLOBAL_DESTDIR/translations/); find $$system_quote($$PWD/) -name '*.qm' -delete)
        system(find $$system_quote($$PWD) -name '*.ts' -print0 | xargs -0 $$[QT_HOST_BINS]/lrelease -nounfinished -removeidentical)
        system(find $$system_quote($$PWD/./) -name '*.qm' -print0 | rsync -avRi --remove-source-files --files-from=- --from0 / $$system_quote($$GLOBAL_DESTDIR/translations/))
}

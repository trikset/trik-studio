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


win32 {
	system(cmd /C "DEL /s *.qm")
	system(cmd /C "for /R %G in (*.ts) do lrelease -nounfinished -removeidentical %G")
	system(cmd /C "xcopy *.qm \"$$GLOBAL_DESTDIR\\translations\\\" /s /e /y")
}

unix {
	system(mkdir -p $$GLOBAL_DESTDIR/translations/; find $$PWD/ -name '*.qm' -delete)
	system(find $$PWD -name '*.ts' -print0 | xargs -0 $$[QT_INSTALL_BINS]/lrelease -nounfinished -removeidentical)
	system(find $$PWD/./ -name '*.qm' -print0 | rsync -avRi --remove-source-files --files-from=- --from0 / $$GLOBAL_DESTDIR/translations/)
}

#!/usr/bin/tclsh

# Copyright 2013-2014 Vladimir Nazarenko and Cybertech Labs Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Checks if lines in the source does not end with spaces

proc checkTabs { fileName } {
  set lineCount 1
  foreach line [getAllLines $fileName] {
    if {![regexp -nocase {[^ \t]+$|^$} $line]} {
      report $fileName $lineCount "Line ends with spaces"
    }

    incr lineCount
  }
}

foreach fileName [getSourceFileNames] {
  checkTabs $fileName
}

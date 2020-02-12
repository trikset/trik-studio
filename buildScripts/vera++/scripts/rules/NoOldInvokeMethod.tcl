# Copyright 2020 Cybertech Labs Ltd.
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

proc NoOldInvokeMethod { fileName } {
  set lineCount 1
  set allLines [getAllLines $file Name]
  for {set x 0} {$x < [llength $allLines]} {incr x} {
    set line [lindex $allLines $x]
    if { [regexp {invokeMethod} $line] } {
      if { [regexp {Q_ARG} $line]  || [regexp {Q_RETURN_ARG} $line] } {
        report $fileName $lineCount "Passing method name as a literal string is forbidden, 
        use Functor signature instead"
      } elseif {![regexp {;$} $line]} {
        set line [lindex $allLines [$x + 1]]
        if { [regexp {Q_ARG} $line]  || [regexp {Q_RETURN_ARG} $line] } {
          report $fileName $lineCount "Passing method name as a literal string is forbidden, 
          use Functor signature instead"
        }
      }
    }
    incr lineCount
  }
}

foreach fileName [getSourceFileNames] {
  NoOldInvokeMethod $fileName
}

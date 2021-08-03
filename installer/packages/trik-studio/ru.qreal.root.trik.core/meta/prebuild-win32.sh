#!/bin/bash
set -xueo pipefail

cd "$(dirname "$0")"

mkdir -p $PWD/../data/plugins/editors
cp    $BIN_DIR/plugins/editors/trikMetamodel.dll                                  $PWD/../data/plugins/editors/
#cp    $BIN_DIR/robots-trik-qts-generator-library.dll                              $PWD/../data/
#cp    $BIN_DIR/robots-trik-generator-base.dll                                     $PWD/../data/
cp    $BIN_DIR/robots-trik-kit.dll                                                $PWD/../data/
cp    $BIN_DIR/robots-trik-kit-interpreter-common.dll                             $PWD/../data/

#cp    $BIN_DIR/PythonQt*.dll                                                      $PWD/../data/
#cp    $BIN_DIR/trikControl.dll                                                    $PWD/../data/
#cp    $BIN_DIR/trikScriptRunner.dll                                               $PWD/../data/
#cp    $BIN_DIR/trikHal.dll                                                        $PWD/../data/
#cp    $BIN_DIR/trikKernel.dll                                                     $PWD/../data/
#cp    $BIN_DIR/trikNetwork.dll                                                    $PWD/../data/
#cp    $BIN_DIR/python3*.dll                                                       $PWD/../data/
#cp    $BIN_DIR/vcruntime*.dll                                                     $PWD/../data/

#cp    "$BIN_DIR/system.js"                                                          "$PWD/../data/"
#cp    "$BIN_DIR/system.py"                                                          "$PWD/../data/"
cp    "$BIN_DIR/2D-model.exe"                                                       "$PWD/../data/"
cp    "$BIN_DIR/checkapp.exe"                                                       "$PWD/../data/"

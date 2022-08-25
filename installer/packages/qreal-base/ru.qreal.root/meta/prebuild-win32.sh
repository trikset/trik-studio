#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"


cp    "$BIN_DIR"/qrkernel.dll                                         "$PWD"/../data
cp    "$BIN_DIR"/qrgraph.dll                                          "$PWD"/../data
cp    "$BIN_DIR"/zlib1.dll                                            "$PWD"/../data
cp    "$BIN_DIR"/qrrepo.dll                                           "$PWD"/../data
cp    "$BIN_DIR"/qrutils.dll                                          "$PWD"/../data
cp    "$BIN_DIR"/qrtext.dll                                           "$PWD"/../data
cp    "$BIN_DIR"/qscintilla2.dll                                      "$PWD"/../data
cp    "$BIN_DIR"/trikQsLog.dll                                        "$PWD"/../data
cp    "$BIN_DIR"/qrgui-brand-manager.dll                              "$PWD"/../data
cp    "$BIN_DIR"/qrgui-controller.dll                                 "$PWD"/../data
cp    "$BIN_DIR"/qrgui-dialogs.dll                                    "$PWD"/../data
cp    "$BIN_DIR"/qrgui-editor.dll                                     "$PWD"/../data
cp    "$BIN_DIR"/qrgui-hotkey-manager.dll                             "$PWD"/../data
cp    "$BIN_DIR"/qrgui-models.dll                                     "$PWD"/../data
cp    "$BIN_DIR"/qrgui-mouse-gestures.dll                             "$PWD"/../data
cp    "$BIN_DIR"/qrgui-plugin-manager.dll                             "$PWD"/../data
cp    "$BIN_DIR"/qrgui-meta-meta-model.dll                            "$PWD"/../data
cp    "$BIN_DIR"/qrgui-preferences-dialog.dll                         "$PWD"/../data
cp    "$BIN_DIR"/qrgui-text-editor.dll                                "$PWD"/../data
cp    "$BIN_DIR"/qrgui-thirdparty.dll                                 "$PWD"/../data
cp    "$BIN_DIR"/qrgui-tool-plugin-interface.dll                      "$PWD"/../data
cp    "$BIN_DIR"/qrgui-facade.dll                                     "$PWD"/../data
cp    "$BIN_DIR/patcher.exe"                                          "$PWD/../data"
cp    "$BIN_DIR/checkapp.exe"                                         "$PWD/../data"
cp    "$BIN_DIR"/trik-studio.exe                                      "$PWD/../data/$PRODUCT.exe"
cp    "$INSTALLER_ROOT/platform/$PRODUCT.cmd"                         "$PWD"/../data/
cp    "$INSTALLER_ROOT/platform/$PRODUCT.vbs"                         "$PWD/../data/"
cp    "$INSTALLER_ROOT/images/trik-studio.ico"                        "$PWD/../data/"
cp    "$BIN_DIR"/plugins/tools/updatesChecker.dll                     "$PWD"/../data/plugins/tools/
cp    "$BIN_DIR"/plugins/tools/subprogramsImporterExporter.dll        "$PWD"/../data/plugins/tools/


cp    "$QT_LIB"/Qt5Core.dll                                       "$PWD"/../data
cp    "$QT_LIB"/Qt5Gui.dll                                        "$PWD"/../data
cp    "$QT_LIB"/Qt5PrintSupport.dll                               "$PWD"/../data
cp    "$QT_LIB"/Qt5Svg.dll                                        "$PWD"/../data
cp    "$QT_LIB"/Qt5Widgets.dll                                    "$PWD"/../data
cp    "$QT_LIB"/Qt5Xml.dll                                        "$PWD"/../data
cp    "$QT_LIB"/Qt5Script.dll                                     "$PWD"/../data
cp    "$QT_LIB"/Qt5Test.dll                                       "$PWD"/../data
cp    "$QT_LIB"/Qt5Concurrent.dll                                 "$PWD"/../data
cp    "$QT_LIB"/libgcc_s_*-1.dll                                  "$PWD"/../data
cp    "$QT_LIB"/libwinpthread-1.dll                               "$PWD"/../data
cp    "$QT_LIB"/libstdc++-6.dll                                   "$PWD"/../data

cp    "$QT_LIB"/../plugins/platforms/q{windows,offscreen,minimal}.dll                        "$PWD"/../data/platforms
cp    "$QT_LIB"/../plugins/imageformats/qsvg.dll                         "$PWD"/../data/imageformats
cp    "$QT_LIB"/../plugins/imageformats/qjpeg.dll                        "$PWD"/../data/imageformats
cp    "$QT_LIB"/../plugins/iconengines/qsvgicon.dll                      "$PWD"/../data/iconengines

#!/bin/bash
set -o nounset
set -o errexit
set -x
cd "$(dirname "$0")"


rsync -a "$BIN_DIR"/qrkernel.dll                                         "$PWD"/../data
rsync -a "$BIN_DIR"/qrgraph.dll                                          "$PWD"/../data
rsync -a "$BIN_DIR"/zlib1.dll                                            "$PWD"/../data
rsync -a "$BIN_DIR"/qrrepo.dll                                           "$PWD"/../data
rsync -a "$BIN_DIR"/qrutils.dll                                          "$PWD"/../data
rsync -a "$BIN_DIR"/qrtext.dll                                           "$PWD"/../data
rsync -a "$BIN_DIR"/trikqscintilla2.dll                                  "$PWD"/../data
rsync -a "$BIN_DIR"/trikQsLog.dll                                        "$PWD"/../data
rsync -a "$BIN_DIR"/trikRuntimeQsLog.dll                                 "$PWD"/../data
rsync -a "$BIN_DIR"/qrgui-brand-manager.dll                              "$PWD"/../data
rsync -a "$BIN_DIR"/qrgui-controller.dll                                 "$PWD"/../data
rsync -a "$BIN_DIR"/qrgui-dialogs.dll                                    "$PWD"/../data
rsync -a "$BIN_DIR"/qrgui-editor.dll                                     "$PWD"/../data
rsync -a "$BIN_DIR"/qrgui-hotkey-manager.dll                             "$PWD"/../data
rsync -a "$BIN_DIR"/qrgui-models.dll                                     "$PWD"/../data
rsync -a "$BIN_DIR"/qrgui-mouse-gestures.dll                             "$PWD"/../data
rsync -a "$BIN_DIR"/qrgui-plugin-manager.dll                             "$PWD"/../data
rsync -a "$BIN_DIR"/qrgui-meta-meta-model.dll                            "$PWD"/../data
rsync -a "$BIN_DIR"/qrgui-preferences-dialog.dll                         "$PWD"/../data
rsync -a "$BIN_DIR"/qrgui-text-editor.dll                                "$PWD"/../data
rsync -a "$BIN_DIR"/qrgui-thirdparty.dll                                 "$PWD"/../data
rsync -a "$BIN_DIR"/qrgui-tool-plugin-interface.dll                      "$PWD"/../data
rsync -a "$BIN_DIR"/qrgui-facade.dll                                     "$PWD"/../data
rsync -a "$BIN_DIR/patcher.exe"                                          "$PWD/../data"
rsync -a "$BIN_DIR/checkapp.exe"                                         "$PWD/../data"
rsync -a "$BIN_DIR"/trik-studio.exe                                      "$PWD/../data/$PRODUCT.exe"
rsync -a "$INSTALLER_ROOT/platform/$PRODUCT.cmd"                         "$PWD"/../data/
rsync -a "$INSTALLER_ROOT/platform/$PRODUCT.vbs"                         "$PWD/../data/"
rsync -a "$INSTALLER_ROOT/images/trik-studio.ico"                        "$PWD/../data/"
rsync -a "$BIN_DIR"/plugins/tools/updatesChecker.dll                     "$PWD"/../data/plugins/tools/
rsync -a "$BIN_DIR"/plugins/tools/subprogramsImporterExporter.dll        "$PWD"/../data/plugins/tools/


rsync -a "$QT_LIB"/Qt5Core.dll                                       "$PWD"/../data
rsync -a "$QT_LIB"/Qt5Gui.dll                                        "$PWD"/../data
rsync -a "$QT_LIB"/Qt5PrintSupport.dll                               "$PWD"/../data
rsync -a "$QT_LIB"/Qt5Svg.dll                                        "$PWD"/../data
rsync -a "$QT_LIB"/Qt5Widgets.dll                                    "$PWD"/../data
rsync -a "$QT_LIB"/Qt5Xml.dll                                        "$PWD"/../data
rsync -a "$QT_LIB"/Qt5Script.dll                                     "$PWD"/../data
rsync -a "$QT_LIB"/Qt5Test.dll                                       "$PWD"/../data
rsync -a "$QT_LIB"/Qt5Concurrent.dll                                 "$PWD"/../data
where \$path:lib{gcc_s_,winpthread-,stdc\+\+-}\*\.dll \
	| dos2unix \
	| xargs -rd \\n cygpath -au \
	| rsync -a --no-relative --files-from=- / "$PWD"/../data

rsync -a "$QT_LIB"/../plugins/platforms/q{windows,offscreen,minimal}.dll                        "$PWD"/../data/platforms
rsync -a "$QT_LIB"/../plugins/imageformats/qsvg.dll                         "$PWD"/../data/imageformats
rsync -a "$QT_LIB"/../plugins/imageformats/qjpeg.dll                        "$PWD"/../data/imageformats
rsync -a "$QT_LIB"/../plugins/iconengines/qsvgicon.dll                      "$PWD"/../data/iconengines

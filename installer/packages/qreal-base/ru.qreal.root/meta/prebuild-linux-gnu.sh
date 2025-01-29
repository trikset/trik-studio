#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source "$INSTALLER_ROOT"/utils/linux-gnu_utils.sh

mkdir -p "$PWD"/../data/bin/
mkdir -p "$PWD"/../data/resources/
mkdir -p "$PWD"/../data/bin/platforms/
mkdir -p "$PWD"/../data/bin/imageformats/
mkdir -p "$PWD"/../data/bin/iconengines/
mkdir -p "$PWD"/../data/lib/plugins/tools/

rsync -a "$INSTALLER_ROOT"/platform/"$PRODUCT"                              "$PWD"/../data/
rsync -a "$INSTALLER_ROOT/platform/$PRODUCT-linux-gnu-platform.config"      "$PWD"/../data/bin/platform.config || :

rsync -a "$BIN_DIR"/libqrkernel.so*                                         "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrgraph.so*                                          "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrrepo.so*                                           "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrutils.so*                                          "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrtext.so*                                           "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libtrikqscintilla2.so*                                  "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libtrikQsLog.so*                                        "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrgui-brand-manager.so*                              "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrgui-controller.so*                                 "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrgui-dialogs.so*                                    "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrgui-editor.so*                                     "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrgui-hotkey-manager.so*                             "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrgui-models.so*                                     "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrgui-mouse-gestures.so*                             "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrgui-plugin-manager.so*                             "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrgui-meta-meta-model.so*                            "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrgui-preferences-dialog.so*                         "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrgui-text-editor.so*                                "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrgui-thirdparty.so*                                 "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrgui-tool-plugin-interface.so*                      "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/libqrgui-facade.so*                                     "$PWD"/../data/lib/
rsync -a "$BIN_DIR"/patcher                                                 "$PWD"/../data/bin/
rsync -a "$BIN_DIR"/trik-studio                                             "$PWD/../data/bin/${PRODUCT}.bin"
rsync -a "$BIN_DIR"/plugins/tools/libupdatesChecker.so                      "$PWD"/../data/lib/plugins/tools/
rsync -a "$BIN_DIR"/plugins/tools/libsubprogramsImporterExporter.so         "$PWD"/../data/lib/plugins/tools/

rsync -a "$QT_LIB"/libQt5Core.so*                                       "$PWD"/../data/lib/
rsync -a "$QT_LIB"/libQt5DBus.so*                                       "$PWD"/../data/lib/
rsync -a "$QT_LIB"/libQt5Gui.so*                                        "$PWD"/../data/lib/
rsync -a "$QT_LIB"/libQt5PrintSupport.so*                               "$PWD"/../data/lib/
rsync -a "$QT_LIB"/libQt5Svg.so*                                        "$PWD"/../data/lib/
rsync -a "$QT_LIB"/libQt5Widgets.so*                                    "$PWD"/../data/lib/
rsync -a "$QT_LIB"/libQt5Xml.so*                                        "$PWD"/../data/lib/
rsync -a "$QT_LIB"/libQt5Script.so*                                     "$PWD"/../data/lib/
rsync -a "$QT_LIB"/libQt5Test.so*                                       "$PWD"/../data/lib/
rsync -a "$QT_LIB"/libQt5XcbQpa.so*                                     "$PWD"/../data/lib/
rsync -a "$QT_LIB"/libQt5WaylandC{lient,ompositor}.so*                  "$PWD"/../data/lib/
rsync -a "$QT_LIB"/libQt5Concurrent.so*                                 "$PWD"/../data/lib/

rsync -avR "$QT_PLUGINS"/./{platforms,imageformats,iconengines,wayland-*}/lib*.so                             "$PWD"/../data/bin/

mv     "$PWD"/../data/acknowledgements.txt                                "$PWD"/../data/resources/
mv     "$PWD"/../data/changelog.txt                                       "$PWD"/../data/resources/

# Cleaning up prebuild-common.sh results...
rm -rf "$PWD"/../data/imageformats/
rm -rf "$PWD"/../data/iconengines/
rm -rf "$PWD"/../data/platforms/
rm -rf "$PWD"/../data/plugins/

add_required_libs "$PWD/../data/bin" "$PWD/../data/lib"
add_required_libs "$PWD/../data/lib"

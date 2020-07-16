#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"
source "$INSTALLER_ROOT"/utils/linux-gnu_utils.sh

mkdir -p $PWD/../data/bin/
mkdir -p $PWD/../data/resources/
mkdir -p $PWD/../data/bin/platforms/
mkdir -p $PWD/../data/bin/imageformats/
mkdir -p $PWD/../data/bin/iconengines/
mkdir -p $PWD/../data/lib/plugins/tools/

cp     $INSTALLER_ROOT/platform/$PRODUCT                                $PWD/../data/
cp     $INSTALLER_ROOT/platform/$PRODUCT-linux-gnu-platform.config      $PWD/../data/bin/platform.config || :

cp -pr $BIN_DIR/libqrkernel.so*                                         $PWD/../data/lib/
cp -pr $BIN_DIR/libqrgraph.so*                                          $PWD/../data/lib/
cp -pr $BIN_DIR/libqrrepo.so*                                           $PWD/../data/lib/
cp -pr $BIN_DIR/libqrutils.so*                                          $PWD/../data/lib/
cp -pr $BIN_DIR/libqrtext.so*                                           $PWD/../data/lib/
cp -pr $BIN_DIR/libqscintilla2.so*                                      $PWD/../data/lib/
cp -pr $BIN_DIR/libqslog.so*                                            $PWD/../data/lib/
cp -pr $BIN_DIR/libqrgui-brand-manager.so*                              $PWD/../data/lib/
cp -pr $BIN_DIR/libqrgui-controller.so*                                 $PWD/../data/lib/
cp -pr $BIN_DIR/libqrgui-dialogs.so*                                    $PWD/../data/lib/
cp -pr $BIN_DIR/libqrgui-editor.so*                                     $PWD/../data/lib/
cp -pr $BIN_DIR/libqrgui-hotkey-manager.so*                             $PWD/../data/lib/
cp -pr $BIN_DIR/libqrgui-models.so*                                     $PWD/../data/lib/
cp -pr $BIN_DIR/libqrgui-mouse-gestures.so*                             $PWD/../data/lib/
cp -pr $BIN_DIR/libqrgui-plugin-manager.so*                             $PWD/../data/lib/
cp -pr $BIN_DIR/libqrgui-meta-meta-model.so*                            $PWD/../data/lib/
cp -pr $BIN_DIR/libqrgui-preferences-dialog.so*                         $PWD/../data/lib/
cp -pr $BIN_DIR/libqrgui-text-editor.so*                                $PWD/../data/lib/
cp -pr $BIN_DIR/libqrgui-thirdparty.so*                                 $PWD/../data/lib/
cp -pr $BIN_DIR/libqrgui-tool-plugin-interface.so*                      $PWD/../data/lib/
cp -pr $BIN_DIR/libqrgui-facade.so*                                     $PWD/../data/lib/
cp     $BIN_DIR/patcher                                                 $PWD/../data/bin/
cp     $BIN_DIR/trik-studio                                             $PWD/../data/bin/$PRODUCT
cp     $BIN_DIR/plugins/tools/libupdatesChecker.so                      $PWD/../data/lib/plugins/tools/
cp     $BIN_DIR/plugins/tools/libsubprogramsImporterExporter.so            $PWD/../data/lib/plugins/tools/


cp -pr $QT_DIR/lib/libQt5Core.so*                                       $PWD/../data/lib/
cp -pr $QT_DIR/lib/libQt5DBus.so*                                       $PWD/../data/lib/
cp -pr $QT_DIR/lib/libQt5Gui.so*                                        $PWD/../data/lib/
cp -pr $QT_DIR/lib/libQt5PrintSupport.so*                               $PWD/../data/lib/
cp -pr $QT_DIR/lib/libQt5Svg.so*                                        $PWD/../data/lib/
cp -pr $QT_DIR/lib/libQt5Widgets.so*                                    $PWD/../data/lib/
cp -pr $QT_DIR/lib/libQt5Xml.so*                                        $PWD/../data/lib/
cp -pr $QT_DIR/lib/libQt5Script.so*                                     $PWD/../data/lib/
cp -pr $QT_DIR/lib/libQt5Test.so*                                       $PWD/../data/lib/
cp -pr $QT_DIR/lib/libQt5XcbQpa.so*                                     $PWD/../data/lib/
#rsync -avR --copy-unsafe-links "/usr/lib/$(uname -i)-linux-gnu"/./lib{stdc++,icudata,icui18n,icuuc,png12}.so* "$PWD/../data/lib/"
#Take them from Qt if exist
#rsync -avR "$QT_DIR"/lib/./libicu{data,i18n,uc}.so*                                 "$PWD/../data/lib/" || :

cp     $QT_DIR/plugins/platforms/libq{xcb,minimal,offscreen}.so                             $PWD/../data/bin/platforms/
cp     $QT_DIR/plugins/imageformats/libqsvg.so                          $PWD/../data/bin/imageformats/
cp     $QT_DIR/plugins/imageformats/libqjpeg.so                         $PWD/../data/bin/imageformats/
cp     $QT_DIR/plugins/iconengines/libqsvgicon.so                       $PWD/../data/bin/iconengines/

#rsync -av /lib/$(uname -i)-linux-gnu/libc.so*                               $PWD/../data/lib/
#rsync -av /lib/$(uname -i)-linux-gnu/libc-2.*.so*                               $PWD/../data/lib/


mv     $PWD/../data/acknowledgements.txt                                $PWD/../data/resources/
mv     $PWD/../data/changelog.txt                                       $PWD/../data/resources/

# Cleaning up prebuild-common.sh results...
rm -rf $PWD/../data/imageformats/
rm -rf $PWD/../data/iconengines/
rm -rf $PWD/../data/platforms/
rm -rf $PWD/../data/plugins/

add_required_libs "$PWD/../data/bin" "$PWD/../data/lib"
add_required_libs "$PWD/../data/lib"

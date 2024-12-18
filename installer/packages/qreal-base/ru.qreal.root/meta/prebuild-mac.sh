#!/bin/bash
set -o nounset
set -o errexit
cd "$(dirname "$0")"
source "$INSTALLER_ROOT"/utils/mac_utils.sh

rm -rf "$PWD/../data/$PRODUCT_DISPLAYED_NAME.app"
rsync -a "$BIN_DIR"/trik-studio.app/                                        "$PWD/../data/$PRODUCT_DISPLAYED_NAME.app/"
rsync -a    "$INSTALLER_ROOT/platform/qt.conf"				    "$BUNDLE_CONTENTS/Resources/qt.conf"
rsync -a    "$INSTALLER_ROOT/platform/$PRODUCT-mac-platform.config"            "$BUNDLE_CONTENTS/MacOS/platform.config"
mkdir -p "$BUNDLE_CONTENTS/Lib/plugins/tools"

rsync -a "$BIN_DIR"/libqrkernel*.dylib                                        "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrgraph*.dylib                                         "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrrepo*.dylib                                          "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR/patcher"                                                   "$BUNDLE_CONTENTS/MacOS/"
rsync -a "$BIN_DIR"/libqrutils*.dylib                                         "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrtext*.dylib                                          "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libtrikqscintilla2*.dylib                                 "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libtrikQsLog*.dylib                                       "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrgui-brand-manager*.dylib                             "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrgui-controller*.dylib                                "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrgui-dialogs*.dylib                                   "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrgui-editor*.dylib                                    "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrgui-hotkey-manager*.dylib                            "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrgui-models*.dylib                                    "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrgui-mouse-gestures*.dylib                            "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrgui-plugin-manager*.dylib                            "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrgui-meta-meta-model*.dylib                           "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrgui-preferences-dialog*.dylib                        "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrgui-text-editor*.dylib                               "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrgui-thirdparty*.dylib                                "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrgui-tool-plugin-interface*.dylib                     "$BUNDLE_CONTENTS/Lib"
rsync -a "$BIN_DIR"/libqrgui-facade*.dylib                                    "$BUNDLE_CONTENTS/Lib"
rsync -a   "$BIN_DIR"/plugins/tools/libupdatesChecker.dylib                     "$BUNDLE_CONTENTS/Lib/plugins/tools"
rsync -a   "$BIN_DIR"/plugins/tools/libsubprogramsImporterExporter.dylib           "$BUNDLE_CONTENTS/Lib/plugins/tools"


fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrkernel.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrgraph.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrrepo.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrutils.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrtext.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libtrikqscintilla2.15.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libtrikQsLog.2.1.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrgui-brand-manager.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrgui-controller.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrgui-dialogs.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrgui-editor.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrgui-hotkey-manager.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrgui-mouse-gestures.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrgui-models.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrgui-plugin-manager.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrgui-meta-meta-model.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrgui-preferences-dialog.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrgui-text-editor.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrgui-thirdparty.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrgui-tool-plugin-interface.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/libqrgui-facade.1.0.0.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/tools/libupdatesChecker.dylib"
fix_qreal_dependencies "$BUNDLE_CONTENTS/Lib/plugins/tools/libsubprogramsImporterExporter.dylib"

mv "$BUNDLE_CONTENTS/MacOS/trik-studio" "$BUNDLE_CONTENTS/MacOS/trik-studio.bin"
rsync -a     "$INSTALLER_ROOT/platform/$PRODUCT" "$BUNDLE_CONTENTS/MacOS/"
sed -i.bak s/qreal/trik-studio/g "$BUNDLE_CONTENTS/Info.plist"
sed -i.bak s/yourcompany/cybertech/g "$BUNDLE_CONTENTS/Info.plist"
rm -f "$BUNDLE_CONTENTS/Info.plist.bak"
fix_qreal_dependencies "$BUNDLE_CONTENTS/MacOS/${PRODUCT}.bin"
fix_qreal_dependencies "$BUNDLE_CONTENTS/MacOS/patcher"

copy_qt_lib QtCore
copy_qt_lib QtDBus
copy_qt_lib QtGui
copy_qt_lib QtPrintSupport
copy_qt_lib QtSvg
copy_qt_lib QtWidgets
copy_qt_lib QtXml
copy_qt_lib QtScript
copy_qt_lib QtTest
copy_qt_lib QtMacExtras
copy_qt_lib QtConcurrent

mkdir "$BUNDLE_CONTENTS/MacOS/platforms"
mkdir "$BUNDLE_CONTENTS/MacOS/imageformats"
mkdir "$BUNDLE_CONTENTS/MacOS/iconengines"

rsync -a   "$QT_PLUGINS"/platforms/libq{cocoa,minimal,offscreen}.dylib                          "$BUNDLE_CONTENTS/MacOS/platforms"
rsync -a   "$QT_PLUGINS"/imageformats/libqsvg.dylib                         "$BUNDLE_CONTENTS/MacOS/imageformats"
rsync -a   "$QT_PLUGINS"/imageformats/libqjpeg.dylib                        "$BUNDLE_CONTENTS/MacOS/imageformats"
rsync -a   "$QT_PLUGINS"/iconengines/libqsvgicon.dylib                      "$BUNDLE_CONTENTS/MacOS/iconengines"

fix_qreal_dependencies "$BUNDLE_CONTENTS/MacOS/platforms/libqminimal.dylib"       "$QT_LIB/lib" "$LIB_PATH"
fix_qreal_dependencies "$BUNDLE_CONTENTS/MacOS/platforms/libqoffscreen.dylib"       "$QT_LIB/lib" "$LIB_PATH"
fix_qreal_dependencies "$BUNDLE_CONTENTS/MacOS/platforms/libqcocoa.dylib"       "$QT_LIB/lib" "$LIB_PATH"
fix_qreal_dependencies "$BUNDLE_CONTENTS/MacOS/imageformats/libqsvg.dylib"      "$QT_LIB/lib" "$LIB_PATH"
fix_qreal_dependencies "$BUNDLE_CONTENTS/MacOS/imageformats/libqjpeg.dylib"      "$QT_LIB/lib" "$LIB_PATH"
fix_qreal_dependencies "$BUNDLE_CONTENTS/MacOS/iconengines/libqsvgicon.dylib"   "$QT_LIB/lib" "$LIB_PATH"

# Cleaning up prebuild-common.sh results…
rm -rf "$PWD"/../data/platforms/
rm -rf "$PWD"/../data/imageformats/
rm -rf "$PWD"/../data/iconengines/
rm -rf "$PWD"/../data/plugins/
mv "$PWD/../data/acknowledgements.txt" "$BUNDLE_CONTENTS/Resources"
mv "$PWD/../data/changelog.txt" "$BUNDLE_CONTENTS/Resources"

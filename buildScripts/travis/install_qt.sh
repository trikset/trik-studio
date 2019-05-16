#!/bin/bash
download_dir=/tmp/qt_ifw/
mkdir -p $download_dir
download_installer=$download_dir/installer.run
curl -L -o $download_installer http://download.qt-project.org/official_releases/qt-installer-framework/3.0.6/QtInstallerFramework-linux-x64.run
chmod +x $download_installer
/tmp/qt_ifw/installer.run --platform minimal --script "$(dirname "$0")"/qt_ifw_installscript.qs
ls $HOME/Qt_IFW

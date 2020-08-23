#!/bin/bash
set -euxo pipefail

curl --output test_qrs.7z "https://dl.trikset.com/edu/.solutions20200701/test.7z"
7z x test_qrs.7z

case $TRAVIS_OS_NAME in
  linux)
    curl --output installer.run "https://dl.trikset.com/ts/fresh/installer/trik-studio-installer-linux-master.run"
    chmod +x installer.run
    ./installer.run --platform minimal --script ./installer/trik_studio_installscript.qs
    env QT_QPA_PLATFORM=minimal python3.7 ./buildScripts/tests/fieldstest.py "$HOME/TRIKStudio/bin/2D-model" testing
    ;;
  osx)
    ./installer/install_studio_mac.sh ./installer/
    env QT_QPA_PLATFORM=minimal python3.7 ./buildScripts/tests/fieldstest.py "$HOME/TRIKStudio/TRIK Studio.app/Contents/MacOS/2D-model" testing
    ;;
  *) exit 1 ;;
esac

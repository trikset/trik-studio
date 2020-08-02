#!/bin/bash
set -euo pipefail

if [ "$TRAVIS_OS_NAME" = "linux" ]; then
	$EXECUTOR "bin/$CONFIG/build-checker-installer.sh"
fi
$EXECUTOR bash -lixc "curl --output tests_qrs.7z https://dl.trikset.com/edu/.solutions20200701/test.7z \
	&& 7z x tests_qrs.7z \
	&& export ASAN_OPTIONS=detect_leaks=0 \
	&& python3.\${TRIK_PYTHON3_VERSION_MINOR} ./buildScripts/tests/fieldstest.py bin/$CONFIG/2D-model minimal testing"

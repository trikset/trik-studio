#!/bin/bash
set -euo pipefail

curl --output tests_qrs.zip "https://dl.trikset.com/edu/.solutions20200701/test.zip"
unzip tests_qrs.zip
if [ $TRAVIS_OS_NAME = "linux" ]
then
	$EXECUTOR bin/$CONFIG/build-checker-installer.sh
fi
$EXECUTOR bash -lixc "export ASAN_OPTIONS=detect_leaks=0:detect_stack_use_after_return=1:fast_unwind_on_malloc=0:use_sigaltstack=0 LSAN_OPTIONS=suppressions=lsan.supp:fast_unwind_on_malloc=0 \
&& python3.\${TRIK_PYTHON3_VERSION_MINOR} ./buildScripts/tests/fieldstest.py bin/$CONFIG/2D-model testing"

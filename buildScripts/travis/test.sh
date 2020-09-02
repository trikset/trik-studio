#!/bin/bash
set -euo pipefail

$EXECUTOR bash -lic "curl --output tests_qrs.7z https://dl.trikset.com/edu/.solutions20200701/testing_small.7z \
	&& 7z x tests_qrs.7z \
	&& env ASAN_OPTIONS=detect_leaks=1:use_sigaltstack=0 \
	       LSAN_OPTIONS=suppressions=$PWD/bin/$CONFIG/lsan.supp:print_suppressions=0 \
	       PYTHONIOENCODING=utf-8 \
	       QT_QPA_PLATFORM=minimal \
               python3.\${TRIK_PYTHON3_VERSION_MINOR} ./buildScripts/tests/fieldstest.py bin/$CONFIG/2D-model testing_small"

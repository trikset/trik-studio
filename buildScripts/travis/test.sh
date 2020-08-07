#!/bin/bash
set -euo pipefail

$EXECUTOR bash -lixc "curl --output tests_qrs.7z https://dl.trikset.com/edu/.solutions20200701/test.7z \
	&& 7z x tests_qrs.7z \
	&& env ASAN_OPTIONS=detect_leaks=0:use_sigaltstack=0 \
	       PYTHONIOENCODING=utf-8 \
	       QT_QPA_PLATFORM=minimal \
               python3.\${TRIK_PYTHON3_VERSION_MINOR} ./buildScripts/tests/fieldstest.py bin/$CONFIG/2D-model testing"

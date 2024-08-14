export QT_QPA_PLATFORM=minimal
export ASAN_OPTIONS=$(if [[ $RUNNER_OS == Linux ]]; then echo 'detect_leaks=1:'; else echo -n ''; fi)detect_stack_use_after_return=1:fast_unwind_on_malloc=0
export LSAN_OPTIONS=suppressions=$PWD/bin/lsan.supp:print_suppressions=0
export DISPLAY=:0
export TRIK_PYTHONPATH=${TRIK_PYTHONPATH:-$(python3.${TRIK_PYTHON3_VERSION_MINOR} -c 'import sys; import os; print(os.pathsep.join(sys.path))')}
export PYTHONMALLOC=malloc
env
make check -k -s && ( set +eux ; cd "bin" && eval "$TESTS" )

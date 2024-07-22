#!/bin/sh

#This is a magic fix for macOS, but old Linux /usr/bin/env has no -S option, thus we cannot use shabang line
#An obsolete bash (v3) does not support `exec {varname}<>`, thus we want to use zsh
if ! ( eval 'exec {somevar}<>$(mktemp)' ) ; then
    COMPATIBLE_SHELL=/bin/zsh
    [ ! -x $COMPATIBLE_SHELL ] && COMPATIBLE_SHELL=/bin/bash || :
    exec $COMPATIBLE_SHELL "$0" "$@"
fi

# enable kinda `bash compatibility` in zsh
if [ -n "$ZSH_VERSION" ] ; then setopt SH_WORD_SPLIT ; fi

set -xueo pipefail
exec {lock}<>$(mktemp -t trik-build-lock.XXXX) && trap 'while [ -e /proc/$$/fd/$lock ] && [ $(lsof -t /proc/$$/fd/$lock | wc -l) -ne 3 ] ; do echo "Sleep to wait ..." ; lsof /proc/$$/fd/$lock ; sleep 5 ; done' EXIT
export LANG=C
ccache -V && ccache -p
which g++
g++ --version
which qmake
qmake -query
ccache -sz
{ which python3 && python3 -V || true ; }
{ which python && python -V || true ; }
export PKG_CONFIG_PATH=$(python3.${TRIK_PYTHON3_VERSION_MINOR}-config --prefix)/lib/pkgconfig
rm -f .qmake.cache
{ echo -n 'Remove broken object files ' ; find . -name '*.o' -type f -print0 | xargs -0 file --mime-type | grep -v 'application/x-object' | cut -f 1 -d ':' | xargs -t rm -f _RM_REQUIRES_ARGUMENTS_BUT_BSD_XARGS_IS_MISSING_R_PARAMETER_ARGUMENT || : ; echo Done ; }
qmake -Wall PYTHON3_VERSION_MINOR=$TRIK_PYTHON3_VERSION_MINOR CONFIG+=$CONFIG $QMAKE_EXTRA $PROJECT.pro
make -j $(nproc) qmake_all 2>&1 | tee -a build.log
ccache -s
make -j $(nproc) all 2>&1 | tee -a build.log
ccache -s
ls bin/$CONFIG
export QT_QPA_PLATFORM=minimal
export ASAN_OPTIONS=$(if [[ $RUNNER_OS == Linux ]]; then echo 'detect_leaks=1:'; else echo -n ''; fi)detect_stack_use_after_return=1:fast_unwind_on_malloc=0
export LSAN_OPTIONS=suppressions=$PWD/bin/$CONFIG/lsan.supp:print_suppressions=0
export DISPLAY=:0
export TRIK_PYTHONPATH=${TRIK_PYTHONPATH:-$(python3.${TRIK_PYTHON3_VERSION_MINOR} -c 'import sys; import os; print(os.pathsep.join(sys.path))')}
export PYTHONMALLOC=malloc
env
make check -k -s && ( set +eux ; cd "bin/$CONFIG" && eval "$TESTS" )

#!/bin/bash
set -xuevo pipefail

CODECOV=true
case $TRAVIS_OS_NAME in
  osx)
     export PATH="/usr/local/opt/qt/bin:$PATH"
     export PATH="/usr/local/opt/ccache/libexec:$PATH"
     export PATH="/usr/local/opt/coreutils/libexec/gnubin:$PATH"
    ;;
  linux)
     # if [[ "$TESTS" != "true" ]] ; then CODECOV="$EXECUTOR bash -ic \" python -m codecov \" " ; fi
   ;;
  *) exit 1 ;;
esac

mkdir -p $CCACHE_DIR || sudo chown -R $USER $CCACHE_DIR || :
cat << EOF > $CCACHE_CONFIGPATH
compiler_check=none
run_second_cpp=true
cache_dir=$CCACHE_DIR
compression=true
compression_level=3
sloppiness=time_macros,pch_defines,include_file_ctime,include_file_mtime,file_stat_matches
EOF
$EXECUTOR bash -lixc "\
   export CCACHE_CONFIGPATH=$CCACHE_CONFIGPATH \
&& ccache -p \
&& which g++ \
&& g++ --version \
&& which qmake \
&& qmake -query \
&& ccache -sz -M 0 \
&& pkg-config --list-all \
&& { which python3 && python3 -V || true ; } \
&& { which python && python -V || true ; } \
&& rm -f .qmake.cache \
&& qmake -Wall CONFIG+=$CONFIG $QMAKE_EXTRA $PROJECT.pro \
&& sh -c 'make -j2 qmake_all 1>>build.log 2>&1' \
&& sh -c 'make -j2 all 1>>build.log 2>&1' \
&& sh -c \"cd bin/$CONFIG && ls\" \
&& sh -c \"export ASAN_OPTIONS=detect_leaks=0:detect_stack_use_after_return=1:fast_unwind_on_malloc=0 LSAN_OPTIONS=suppressions=lsan.supp:fast_unwind_on_malloc=0:verbosity=1:log_threads=1  DISPLAY=:0 && cd bin/$CONFIG && $TESTS\""
df -h .
$EXECUTOR bash -ic buildScripts/travis/checkStatus.sh

$CODECOV

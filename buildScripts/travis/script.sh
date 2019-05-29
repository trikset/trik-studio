#!/bin/bash
set -euxo pipefail

CODECOV=true
case $TRAVIS_OS_NAME in
  osx)
     export PATH="/usr/local/opt/qt/bin:$PATH"
     export PATH="/usr/local/opt/ccache/libexec:$PATH"
     export PATH="/usr/local/opt/coreutils/libexec/gnubin:$PATH"
     export PATH="$(pyenv root)/bin:$PATH"
     eval "$(pyenv init -)"
     export PKG_CONFIG_PATH="$(python3-config --prefix)/lib/pkgconfig"
    ;;
  linux)
     # if [[ "$TESTS" != "true" ]] ; then CODECOV="$EXECUTOR bash -ic \" python -m codecov \" " ; fi
   ;;
  *) exit 1 ;;
esac

if $VERA ; then $EXECUTOR buildScripts/travis/runVera++.sh ; fi
if $TRANSLATIONS ; then $EXECUTOR lupdate studio.pro plugins/robots/editor/*/translations.pro && $EXECUTOR buildScripts/travis/checkStatus.sh ; fi
mkdir -p $CCACHE_DIR || sudo chown -R $USER $CCACHE_DIR || :
cat << EOF > $CCACHE_CONFIGPATH
compiler_check=none
run_second_cpp=true
cache_dir=$CCACHE_DIR
compression=true
compression_level=3
sloppiness=time_macros,pch_defines,include_file_ctime,include_file_mtime,file_stat_matches
EOF
$EXECUTOR bash -ic "{ [ -r /root/.bashrc ] && source /root/.bashrc || true ; } ; \
   export CCACHE_CONFIGPATH=$CCACHE_CONFIGPATH \
&& ccache -p \
&& eval \"\`pyenv init -\`\" \
&& eval 'export PKG_CONFIG_PATH=\`python3-config --prefix\`/lib/pkgconfig:/usr/local/lib/pkgconfig' \
&& which g++ \
&& g++ --version \
&& which qmake \
&& qmake -query \
&& ccache -sz -M 0 \
&& pyenv root \
&& pyenv versions \
&& pkg-config --list-all \
&& { which python3 && python3 -V || true ; } \
&& { which python && python -V || true ; } \
&& rm -f .qmake.cache \
&& qmake -Wall CONFIG+=$CONFIG $QMAKE_EXTRA $PROJECT.pro \
&& sh -c 'make -j2 qmake_all 1>>build.log 2>&1' \
&& sh -c 'make -j2 all 1>>build.log 2>&1' \
&& ccache -s \
&& sh -c \"cd bin/$CONFIG && ls\" \
&& sh -c \"export ASAN_OPTIONS='detect_leaks=0 detect_stack_use_after_return=1' LSAN_OPTIONS='detect_leaks=0 fast_unwind_on_malloc=0' DISPLAY=:0 && cd bin/$CONFIG && $TESTS\""

$EXECUTOR bash -ic buildScripts/travis/checkStatus.sh

$CODECOV

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
if $VERA ; then git diff --name-only ${TRAVIS_COMMIT_RANGE} | xargs file -i | grep text/x-c | cut -f 1 -d : | $EXECUTOR vera++ --error --root buildScripts/vera++ --profile strict ; fi

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
&& rm -f build.log \
&& sh -c 'make -j2 qmake_all 1>>build.log 2>&1' \
&& sh -c 'make -j2 all 1>>build.log 2>&1' \
&& sh -c \"cd bin/$CONFIG && ls\" \
&& sh -c \"export ASAN_OPTIONS=$( [[ $TRAVIS_OS_NAME == linux ]] && echo detect_leaks=1 || :):detect_stack_use_after_return=1:fast_unwind_on_malloc=0 LSAN_OPTIONS=suppressions=lsan.supp:fast_unwind_on_malloc=0 DISPLAY=:0 && cd bin/$CONFIG && $TESTS\""
df -h .
$EXECUTOR bash -ic buildScripts/travis/checkStatus.sh

$CODECOV

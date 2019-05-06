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
     EXECUTOR="buildScripts/with_pyenv "
    ;;
  linux)
     EXECUTOR="time docker exec builder "
     # if [[ "$TESTS" != "true" ]] ; then CODECOV="$EXECUTOR bash -ic \" python -m codecov \" " ; fi
   ;;
  *) exit 1 ;;
esac

if $VERA ; then $EXECUTOR buildScripts/travis/runVera++.sh ; fi
if $TRANSLATIONS ; then $EXECUTOR lupdate studio.pro && $EXECUTOR buildScripts/travis/checkStatus.sh ; fi


$EXECUTOR bash -ic "{ [ -r /root/.bashrc ] && source /root/.bashrc || true ; } ; \
   export CCACHE_DIR=$HOME/.ccache/$TRAVIS_OS_NAME-$CONFIG \
&& export CCACHE_CPP2=yes \
&& export CCACHE_SLOPPINESS=time_macros \
&& eval \"\`pyenv init -\`\" \
&& eval 'export PKG_CONFIG_PATH=\`python3-config --prefix\`/lib/pkgconfig' \
&& which g++ \
&& g++ --version \
&& which qmake \
&& qmake -query \
&& ccache -M 0 \
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
&& sh -c \"export ASAN_OPTIONS=detect_leaks=0 LSAN_OPTIONS=detect_leaks=0 DISPLAY=:0 && cd bin/$CONFIG && $TESTS\""

if $TRANSLATIONS ; then $EXECUTOR bash -ic "cd plugins/robots/editor && find . -name 'translations.pro' | xargs lupdate && git diff" ; fi
$EXECUTOR bash -ic buildScripts/travis/checkStatus.sh

$CODECOV

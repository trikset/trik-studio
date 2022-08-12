#!/bin/bash
set -uxeo pipefail

CODECOV=true
case $AGENT_OS in
  Darwin)
     QT_DIR=$(ls -dv "$HOME"/Qt/${TRIK_QT_VERSION}*/*/bin | head -n 1)
     [ -d "$QT_DIR" ] && export PATH="$QT_DIR:$PATH"
     export PATH="/usr/local/opt/ccache/libexec:$PATH"
     export PATH="/usr/local/opt/coreutils/libexec/gnubin:$PATH"
     echo "Now path is $PATH"
    ;;
  Linux)
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
max_size=1200M
EOF

$EXECUTOR bash -lic " set -xueo pipefail; \
   export CCACHE_CONFIGPATH=$CCACHE_CONFIGPATH \
&& ccache -V && ccache -p \
&& which g++ \
&& g++ --version \
&& which qmake \
&& qmake -query \
&& ccache -sz \
&& pkg-config --list-all \
&& { which python3 && python3 -V || true ; } \
&& { which python && python -V || true ; } \
&& eval 'export PKG_CONFIG_PATH=\`python3.\${TRIK_PYTHON3_VERSION_MINOR}-config --prefix\`/lib/pkgconfig' \
&& rm -f .qmake.cache \
&&  { echo -n 'Remove broken object files ' ; find . -name '*.o' -type f -print0 | xargs -0 file --mime-type | grep -v 'application/x-object' | cut -f 1 -d ':' | xargs -t rm -f _RM_REQUIRES_ARGUMENTS_BUT_BSD_XARGS_IS_MISSING_R_PARAMETER_ARGUMENT || : ; echo Done ; } \
&& qmake -Wall PYTHON3_VERSION_MINOR=\$TRIK_PYTHON3_VERSION_MINOR CONFIG+=$CONFIG $QMAKE_EXTRA $PROJECT.pro \
&& make -j2 qmake_all 2>&1 | tee -a build.log \
&& ccache -s \
&& make -j2 all 2>&1 | tee -a build.log \
&& ccache -s \
&& ls bin/$CONFIG \
&& { export QT_QPA_PLATFORM=minimal ; \
     export ASAN_OPTIONS=$(if [[ $AGENT_OS == Linux ]]; then echo 'detect_leaks=1:'; else echo -n ''; fi)detect_stack_use_after_return=1:fast_unwind_on_malloc=0:use_sigaltstack=0 ; \
     export LSAN_OPTIONS=suppressions=$PWD/bin/$CONFIG/lsan.supp:print_suppressions=0 ; \
     export DISPLAY=:0 ; \
     env QT_QPA_PLATFORM=minimal make check -k -s && ( set +eux ; cd bin/$CONFIG && $TESTS ) ; \
   }\
"

df -h .
$EXECUTOR bash -ic buildScripts/azure/checkStatus.sh

$CODECOV

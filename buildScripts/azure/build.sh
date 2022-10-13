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
compiler_check=content
run_second_cpp=true
cache_dir=$CCACHE_DIR
compression=true
compression_level=1
sloppiness=time_macros,pch_defines,include_file_ctime,include_file_mtime,file_stat_matches
max_size=1200M
EOF

$EXECUTOR env \
CCACHE_CONFIGPATH="$CCACHE_CONFIGPATH" \
CONFIG="$CONFIG" \
QMAKE_EXTRA="$QMAKE_EXTRA" \
PROJECT="$PROJECT" \
AGENT_OS="$AGENT_OS" \
buildScripts/azure/build_internal.sh


df -h .
$EXECUTOR bash -ic buildScripts/azure/checkStatus.sh

$CODECOV

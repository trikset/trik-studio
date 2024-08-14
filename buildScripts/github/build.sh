#!/bin/bash
set -uxeo pipefail

CODECOV=true
case $RUNNER_OS in
  macOS)
     QT_DIR=$(ls -dv "$HOME"/Qt/${TRIK_QT_VERSION}*/*/bin | head -n 1)
     [ -d "$QT_DIR" ] && export PATH="$QT_DIR:$PATH"
     export PATH="/usr/local/opt/ccache/libexec:$PATH"
     export PATH="/usr/local/opt/coreutils/libexec/gnubin:$PATH"
     echo "Now path is $PATH"
    ;;
  Linux)
    ID=$(grep '^ID=' /etc/os-release | cut -d'=' -f2)
    if [ "$ID" = "altlinux" ]; then
        ln -s /usr/bin/qmake-qt5 /usr/bin/qmake
    fi
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
CCACHE_DIR="$CCACHE_DIR" \
CONFIG="$CONFIG" \
QMAKE_EXTRA="$QMAKE_EXTRA" \
PROJECT="$PROJECT" \
RUNNER_OS="$RUNNER_OS" \
buildScripts/github/build_internal.sh


df -h .

$CODECOV

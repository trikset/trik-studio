#!/bin/bash
set -euxo pipefail
$EXECUTOR env CCACHE_CONFIGPATH="$CCACHE_CONFIGPATH" ccache -s
case $TRAVIS_OS_NAME in
  osx)
    ;;
  linux)
    if [ "$INSTALLER" == "true" ] && [ "$TRAVIS_PULL_REQUEST" == "false" ] && [ "$TRAVIS_REPO_SLUG" == "trikset/trikstudio" ] ; then 
      $EXECUTOR bash -ic "echo Start build installer \
      && installer/build-trik-studio.sh /Qt/5.12.3/gcc_64/bin /Qt/Tools/QtInstallerFramework/3.0/bin . \
      && mv installer/trik-studio*installer* installer/trik-studio-installer-linux-$TRAVIS_BRANCH.run \
      && sshpass -p $password rsync -e 'ssh -o StrictHostKeyChecking=no' installer/trik-studio*installer* $username@$server:dl/ts/fresh/installer/"
    fi
    docker stop builder
    ;;
  *) exit 1 ;;
esac

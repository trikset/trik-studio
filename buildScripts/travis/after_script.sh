#!/bin/bash
set -euxo pipefail
$EXECUTOR env CCACHE_CONFIGPATH="$CCACHE_CONFIGPATH" ccache -s
case $TRAVIS_OS_NAME in
  osx)
    QTBIN=/usr/local/opt/qt/bin
    QTIFWBIN=/usr/local/bin/binarycreator
    TSNAME=trik-studio-installer-mac-$TRAVIS_BRANCH.dmg
    ;;
  linux)
    QTBIN=/Qt/5.12.3/gcc_64/bin
    QTIFWBIN=/Qt/Tools/QtInstallerFramework/3.0/bin
    TSNAME=trik-studio-installer-linux-$TRAVIS_BRANCH.run
    ;;
  *) exit 1 ;;
esac

if $INSTALLER && ! $TIMEOUT && [ "$TRAVIS_REPO_SLUG" == "trikset/trik-studio" ] && [ "$TRAVIS_PULL_REQUEST" == "false" ]
then
      git config remote.origin.fetch +refs/heads/*:refs/remotes/origin/*
      git fetch --unshallow --tags # for `git describe --tags` to work
      $EXECUTOR bash -ic "echo Start build installer \
      && installer/build-trik-studio.sh $QTBIN $QTIFWBIN . \
      && mv installer/trik-studio*installer* installer/$TSNAME \
      && sshpass -p $password rsync -e 'ssh -o StrictHostKeyChecking=no' installer/$TSNAME $username@$server:dl/ts/fresh/installer/"
fi

docker stop builder || :

#!/bin/bash
set -euxo pipefail
$EXECUTOR env CCACHE_CONFIGPATH="$CCACHE_CONFIGPATH" ccache -s
case $TRAVIS_OS_NAME in
  osx)
    QTBIN=/usr/local/opt/qt/bin
    QTIFWBIN=/usr/local/bin
    TSNAME=trik-studio-installer-mac-$TRAVIS_BRANCH.dmg
    ;;
  linux)
    QTBIN=/Qt/5.12.3/gcc_64/bin
    QTIFWBIN=/Qt/Tools/QtInstallerFramework/3.0/bin
    TSNAME=trik-studio-installer-linux-$TRAVIS_BRANCH.run
    ;;
  *) exit 1 ;;
esac

df -h .

if $INSTALLER && ! $TIMEOUT && [ "$TRAVIS_REPO_SLUG" == "trikset/trik-studio" ] && [ "$TRAVIS_PULL_REQUEST" == "false" ]
then
      git config remote.origin.fetch +refs/heads/*:refs/remotes/origin/*
      git fetch --unshallow --tags # for `git describe --tags` to work
      #TODO: We can build installer and checker archive in parallel if needed
      $EXECUTOR bash -ic "\
	      echo Start build installer \
      && installer/build-trik-studio.sh $QTBIN $QTIFWBIN . \
      && mv installer/trik-studio*installer* installer/$TSNAME \
      && sshpass -p $password rsync -avze 'ssh -o StrictHostKeyChecking=no' installer/$TSNAME $username@$server:dl/ts/fresh/installer/\
      && echo Start build checker archive \
      && bin/$CONFIG/build-checker-installer.sh \
      && sshpass -p $password rsync -avze 'ssh -o StrictHostKeyChecking=no' bin/$CONFIG/trik_checker.tar.xz $username@$server:dl/ts/fresh/checker/checker-$TRAVIS_OS_NAME-$CONFIG-$TRAVIS_BRANCH.tar.xz\
"
fi || travis_terminate 3

docker stop builder || :

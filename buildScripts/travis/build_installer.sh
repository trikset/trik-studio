#!/bin/bash
set -euxo pipefail
QTBIN=${QTBIN:-$($EXECUTOR  bash -c "make qmake -n | sed 's#/qmake.*\$##g'")}
case $TRAVIS_OS_NAME in
  osx)
    QTIFWBIN=$HOME/qtifw/bin
    TSNAME=trik-studio-installer-mac-$TRAVIS_BRANCH.dmg
    ;;
  linux)
    QTIFWBIN=/opt/qtifw/bin
    #QTIFWBIN=$($EXECUTOR bash -c  'find /Qt/Tools/QtInstallerFramework/ -maxdepth 2 -name bin -type d -print0 | sort -Vrz | head -zn 1')
    TSNAME=trik-studio-installer-linux-$TRAVIS_BRANCH.run
    ;;
  *) exit 1 ;;
esac
df -h .

if ! $TIMEOUT && [ "$TRAVIS_REPO_SLUG" == "trikset/trik-studio" ] && [ "$TRAVIS_PULL_REQUEST" == "false" ]
then
#      git config remote.origin.fetch +refs/heads/*:refs/remotes/origin/*
#      git fetch --unshallow --tags # for `git describe --tags` to work
      #TODO: We can build installer and checker archive in parallel if needed

      if [[ $TRAVIS_OS_NAME == linux ]] ; then
      $EXECUTOR bash -ic "\
      echo Start build checker archive \
      && bin/$CONFIG/build-checker-installer.sh \
      && sshpass -p $password rsync -avze 'ssh -o StrictHostKeyChecking=no' bin/$CONFIG/trik_checker.tar.xz $server:dl/ts/fresh/checker/checker-$TRAVIS_OS_NAME-$CONFIG-$TRAVIS_BRANCH.tar.xz \
      || false \
"
      fi

      $EXECUTOR bash -ic "\
      echo Start build installer \
      && installer/build-trik-studio.sh $QTBIN $QTIFWBIN . \
      && mv installer/trik-studio*installer* installer/$TSNAME \
      && sshpass -p $password rsync -avze 'ssh -o StrictHostKeyChecking=no' installer/$TSNAME $server:dl/ts/fresh/installer/ \
      || false \
"
fi

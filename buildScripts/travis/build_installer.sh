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
      $EXECUTOR bash -ic "\
      echo Start build installer \
      && installer/build-trik-studio.sh $QTBIN $QTIFWBIN . \
      && mv installer/trik-studio*installer* installer/$TSNAME \
      && sshpass -p $password rsync -avze 'ssh -o StrictHostKeyChecking=no' installer/$TSNAME $server:dl/ts/fresh/installer/ \
      || false \
"
fi

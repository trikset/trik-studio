#!/bin/bash
set -euxo pipefail
BRANCH_NAME="${SYSTEM_PULLREQUEST_SOURCEBRANCH:-master}"
QTBIN=${QTBIN:-$($EXECUTOR  bash -c "make qmake -n | sed 's#/qmake.*\$##g'")}
case $AGENT_OS in
  Darwin)
    QTIFWBIN=$HOME/qtifw/bin
    TSNAME=trik-studio-installer-mac-$BRANCH_NAME.dmg
    export TRIK_PYTHON3_VERSION_MINOR="$(python3 -V | sed 's#^Python [0-9]\.\([0-9]\)\.[0-9]*$#\1#g')"
    ;;
  Linux)
    QTIFWBIN=/opt/qtifw/bin
    #QTIFWBIN=$($EXECUTOR bash -c  'find /Qt/Tools/QtInstallerFramework/ -maxdepth 2 -name bin -type d -print0 | sort -Vrz | head -zn 1')
    TSNAME=trik-studio-installer-linux-$BRANCH_NAME.run
    ;;
  *) exit 1 ;;
esac
df -h .

if [ "$BUILD_REPOSITORY_NAME" == "trikset/trik-studio" ] && [ "${SYSTEM_PULLREQUEST_PULLREQUESTNUMBER:-false}" == "false" ]
then
#      git config remote.origin.fetch +refs/heads/*:refs/remotes/origin/*
#      git fetch --unshallow --tags # for `git describe --tags` to work
      #TODO: We can build installer and checker archive in parallel if needed

      if [[ $AGENT_OS == Linux ]] ; then
      $EXECUTOR bash -ic "\
      echo Start build checker archive \
      && bin/$CONFIG/build-checker-installer.sh \
      && sshpass -p $password rsync -avze 'ssh -o StrictHostKeyChecking=no' bin/$CONFIG/trik_checker.tar.xz $server:dl/ts/fresh/checker/checker-${AGENT_OS}-$CONFIG-$BRANCH_NAME.tar.xz \
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

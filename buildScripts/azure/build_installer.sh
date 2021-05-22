#!/bin/bash
set -euxo pipefail
BRANCH_NAME="${BRANCH_NAME:-$BUILD_SOURCEBRANCHNAME}"
QTBIN=${QTBIN:-$($EXECUTOR  bash -c 'eval $(make qmake -n | cut -f 1 -d " ") -query QT_INSTALL_BINS')}
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

NEED_DEPLOY=$([[ "$BUILD_REPOSITORY_NAME" == "trikset/trik-studio" && "${SYSTEM_PULLREQUEST_PULLREQUESTNUMBER:-false}" == "false" ]] && echo true || echo false )

if [[ $AGENT_OS == Linux ]] ; then
      echo Start build checker archive
      $EXECUTOR bash -ic "bin/$CONFIG/build-checker-installer.sh"
      if $NEED_DEPLOY ; then
          $EXECUTOR bash -ic "sshpass -p $password rsync -avze 'ssh -o StrictHostKeyChecking=no' bin/$CONFIG/trik_checker.tar.xz $server:dl/ts/fresh/checker/checker-linux-$CONFIG-$BRANCH_NAME.tar.xz"
      fi
fi
echo Start build installer
$EXECUTOR bash -ic "installer/build-trik-studio.sh $QTBIN $QTIFWBIN ."

if $NEED_DEPLOY ; then
    $EXECUTOR bash -ic "\
          mv installer/trik-studio*installer* installer/$TSNAME \
          && sshpass -p $password rsync -avze 'ssh -o StrictHostKeyChecking=no' installer/$TSNAME $server:dl/ts/fresh/installer/"
fi

#!/bin/bash
set -euxo pipefail
BRANCH_NAME="${BRANCH_NAME:-${GITHUB_REF#refs/heads/}}"
QTBIN=${QTBIN:-$($EXECUTOR  bash -c 'eval $(make qmake -n | cut -f 1 -d " ") -query QT_INSTALL_BINS')}
case $RUNNER_OS in
  macOS)
    QTIFWBIN=$HOME/qtifw/bin
    TSNAME=trik-studio-installer-mac-$BRANCH_NAME.dmg
#    export TRIK_PYTHON3_VERSION_MINOR="$(python3 -V | sed 's#^Python 3\.\([0-9]+\)\.[0-9]+$#\1#g')"
    ;;
  Linux)
    QTIFWBIN=/opt/qtifw/bin
    #QTIFWBIN=$($EXECUTOR bash -c  'find /Qt/Tools/QtInstallerFramework/ -maxdepth 2 -name bin -type d -print0 | sort -Vrz | head -zn 1')
    TSNAME=trik-studio-installer-linux-$BRANCH_NAME.run
    ;;
  *) exit 1 ;;
esac
df -h .

NEED_DEPLOY=$([[ "$GITHUB_REPOSITORY" == "trikset/trik-studio" && "${PULLREQUESTNUMBER:-false}" == "false" ]] && echo true || echo false )

if $NEED_DEPLOY ; then
    $EXECUTOR bash -c "mkdir -p ~/.ssh && install -m 600 /dev/null ~/.ssh/id_rsa && echo \"$ssh_key\" > ~/.ssh/id_rsa"
fi
          
if [[ $RUNNER_OS == Linux ]] ; then
      echo Start build checker archive
      $EXECUTOR bash -c "bin/build-checker-installer.sh"
      if $NEED_DEPLOY ; then
          $EXECUTOR bash -c "rsync -v --rsh='ssh -o StrictHostKeyChecking=no' bin/trik_checker.tar.xz $username@$host:~/dl/ts/fresh/checker/checker-linux-$CONFIG-$BRANCH_NAME.tar.xz"
      fi
fi

echo Start build installer
$EXECUTOR bash -c "installer/build-trik-studio.sh $QTBIN $QTIFWBIN ."

if $NEED_DEPLOY ; then
    $EXECUTOR bash -c "\
          mv installer/trik-studio*installer* installer/$TSNAME \
          && rsync -v --rsh='ssh -o StrictHostKeyChecking=no' installer/$TSNAME $username@$host:~/dl/ts/fresh/installer/$TSNAME"
fi

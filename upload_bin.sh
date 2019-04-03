#!/bin/bash
set PATH=$MSYS_DIR/usr/bin/;$PATH
pacman -Su --noconfirm sshpass zip
cd $BUILD_DIR/
zip -r tsbin-${APPVEYOR_ACCOUNT_NAME}-qt$QT.zip bin
sshpass -p "%password%" ssh -q -o StrictHostKeyChecking=no "%server%"
sshpass -p "%password%" scp tsbin-${APPVEYOR_ACCOUNT_NAME}-qt$QT.zip $server:/home/devops/dl/ts/fresh/

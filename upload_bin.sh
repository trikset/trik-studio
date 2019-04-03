#!/bin/bash

#$APPVEYOR_BUILD_FOLDER\installer\build-trik-studio.sh $QTDIR\bin $QTIFWDIR\bin $BUILD_DIR

pacman -Su --noconfirm sshpass zip
cd $BUILD_DIR/
ZIP=tsbin-$APPVEYOR_ACCOUNT_NAME-qt$QT.zip
zip -r $ZIP bin
sshpass -p "$password" ssh -q -o StrictHostKeyChecking=no "$server"
sshpass -p "$password" scp $ZIP $server:/home/devops/dl/ts/fresh/

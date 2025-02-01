#!/bin/bash
set -o nounset
set -o errexit
set -x

cd "$(dirname "$0")"

rsync -a "$BIN_DIR"/plugins/editors/robotsMetamodel.dll                   "$PWD"/../data/plugins/editors/
rsync -a "$BIN_DIR"/robots-interpreter-core.dll                           "$PWD"/../data
rsync -a "$BIN_DIR"/plugins/tools/robots-plugin.dll                       "$PWD"/../data/plugins/tools/
rsync -a "$BIN_DIR"/robots-2d-model.dll                                   "$PWD"/../data
rsync -a "$BIN_DIR"/Box2D.dll                                             "$PWD"/../data
rsync -a "$BIN_DIR"/robots-generator-base.dll                             "$PWD"/../data
rsync -a "$BIN_DIR"/robots-kit-base.dll                                   "$PWD"/../data
rsync -a "$BIN_DIR"/robots-utils.dll                                      "$PWD"/../data


rsync -a "$QT_LIB/Qt5Network.dll"			"$PWD/../data"
rsync -a "$QT_LIB/Qt5Multimedia.dll"		"$PWD/../data"


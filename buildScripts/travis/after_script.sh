#!/bin/bash
set -euxo pipefail
$EXECUTOR env CCACHE_CONFIGPATH="$CCACHE_CONFIGPATH" ccache -s

df -h .

docker stop builder || :

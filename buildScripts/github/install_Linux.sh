#!/bin/bash
set -euxo pipefail
docker pull trikset/linux-builder
docker run --cap-add SYS_PTRACE -d -v $HOME:$HOME:rw -w `pwd` --name builder trikset/linux-builder Xvfb :0
docker exec builder git config --global --add safe.directory '*'

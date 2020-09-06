#!/bin/sh

APP_PATH="$1"
echo $PWD
if [ -f "$APP_PATH" ]; then
	./"$APP_PATH"
else
	xdg-open https://lvjonok.github.io/maze-gui-gen/
fi

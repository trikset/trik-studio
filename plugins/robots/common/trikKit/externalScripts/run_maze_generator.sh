#!/bin/bash
# Copyright 2020 CyberTech Labs Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
set -ueo pipefail

APP_NAME="maze-gui-gen"
APP_FULL_PATH="$(dirname ${0})/${APP_NAME}"

if [ -x "$APP_FULL_PATH" ]; then
	"$APP_FULL_PATH"
else
	xdg-open "https://lvjonok.github.io/${APP_NAME}/"
fi

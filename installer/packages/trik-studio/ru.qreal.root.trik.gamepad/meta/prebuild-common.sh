#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

rm -rf "$PWD"/../data/
mkdir -p "$PWD"/../data/

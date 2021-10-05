#!/bin/bash

# shellcheck disable=SC2164
mkdir -p build && cd build
# shellcheck disable=SC2035
rm -rf *
cmake ..
make
cp archiver.sh ..
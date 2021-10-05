#!/bin/bash

# shellcheck disable=SC2164
mkdir -p build && cd build
# shellcheck disable=SC2035
rm -rf *
cmake -DCMAKE_BUILD_TYPE=Release ..
make
cp archiver.sh ..
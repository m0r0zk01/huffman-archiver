#!/bin/bash

mkdir -p "build" || { echo "Can't create directory"; exit 1; }
cd build || { echo "Can't change directory"; exit 1; }
rm -rf ./* || { echo "Can't clear ./build directory"; exit 1; }
cmake .. || { echo "CMake error"; exit 1; } # -DCMAKE_BUILD_TYPE=Release
make || { echo "Make error"; exit 1; }
cp archiver.sh .. || { echo "Can't copy archiver.sh to current folder. Copy it manually from ./build"; exit 1; }

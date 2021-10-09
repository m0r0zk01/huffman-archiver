#!/bin/bash

if [ "$1" = "--help" ]
then
  echo -e "\033[1m\033[0;36m Run ./build.sg to build program in Release mode, add --build to build in Debug \033[0m";
  exit 1;
fi

mkdir -p "build" || { echo "Can't create directory"; exit 1; }
cd build || { echo "Can't change directory"; exit 1; }
rm -rf ./* || { echo "Can't clear ./build directory"; exit 1; }

if [ "$1" = "--debug" ]
then
  cmake -DCMAKE_BUILD_TYPE=Debug .. || { echo "CMake error"; exit 1; }
else
  cmake -DCMAKE_BUILD_TYPE=Release .. || { echo "CMake error"; exit 1; }
fi

make || { echo "Make error"; exit 1; }

if [ "$1" = "--debug" ]
then
  echo -e "\033[1m\033[0;36m \n Built in Debug mode. Run without --debug to build in Release \033[0m"
else
  echo -e "\033[1m\033[0;36m \n Built in Release mode. Run with --debug to build in Debug \033[0m";
fi

cp archiver.sh .. || { echo "Can't copy archiver.sh to current folder. Copy it manually from ./build"; exit 1; }

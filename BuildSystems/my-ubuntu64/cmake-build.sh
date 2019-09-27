#!/bin/bash
clear
export CURRP=$(pwd)
cp CMakeLists.txt "$CURRP/../../C++/CMakeLists.txt"
cd "$CURRP/../../C++/"
rm -rf build
mkdir build && cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cd "$CURRP"
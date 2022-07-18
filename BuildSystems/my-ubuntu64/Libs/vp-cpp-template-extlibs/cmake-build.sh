#!/bin/bash
clear
export CURRP=$(pwd)
export BASEP="$CURRP/../../../.."
export ProjectName="vp-cpp-template-extlibs"
cd "$BASEP/C++/"
rm -rf build_$ProjectName
mkdir build_$ProjectName && cd build_$ProjectName
cp "$CURRP/CMakeLists.txt" "$BASEP/C++/build_$ProjectName/CMakeLists.txt"
mkdir build && cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cd "$CURRP"

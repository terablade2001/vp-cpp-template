#!/bin/bash
clear
export CURRP=$(pwd)
export BASEP="$CURRP/../../../.."
export ProjectName="ExampleCAPI"
cp CMakeLists.txt "$BASEP/C++/CMakeLists.txt"
cd "$BASEP/C++/"
rm -rf build_$ProjectName
mkdir build_$ProjectName && cd build_$ProjectName
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cd "$CURRP"

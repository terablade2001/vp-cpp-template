#!/bin/bash
clear
export CURRP=$(pwd)
export BASEP="$CURRP/../../../.."
export ProjectName="ExampleCAPI"
cd "$BASEP/build/"
rm -rf build_$ProjectName
mkdir build_$ProjectName && cd build_$ProjectName
cp "$CURRP/CMakeLists.txt" "$BASEP/build/build_$ProjectName/CMakeLists.txt"
mkdir build && cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cd "$CURRP"

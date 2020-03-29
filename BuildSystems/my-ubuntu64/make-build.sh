#!/bin/bash
clear
export CURRP=$(pwd)
cd ../../BuildVersion
./UpdateBuildVersion
cd "$CURRP/../../C++/build"
make -j
mv vp-cpp-template "$CURRP/../../workdir/"
cd "$CURRP"

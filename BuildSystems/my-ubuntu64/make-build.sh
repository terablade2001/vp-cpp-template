#!/bin/bash
clear
export CURRP=$(pwd)
cd ../../BuildVersion
./UpdateBuildVersion
cd "$CURRP/../../C++/build"
make -j
# ./ProtobufModifier
cd "$CURRP"
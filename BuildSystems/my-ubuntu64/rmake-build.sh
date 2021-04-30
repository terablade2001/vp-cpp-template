#!/bin/bash
clear
export CURRP=$(pwd)
cd "$CURRP/../../C++/build"
make -j
mv vp-cpp-template "$CURRP/../../workdir/"
cd "$CURRP"

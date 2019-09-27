#!/bin/bash
export CURRP=$(pwd)
cd "$CURRP/../../C++/build"
./vp-cpp-template ../../workdir/test-setup.cfg
cd "$CURRP"
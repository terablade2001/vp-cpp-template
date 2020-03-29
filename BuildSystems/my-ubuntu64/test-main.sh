#!/bin/bash
export CURRP=$(pwd)
cd "$CURRP/../../workdir"
./vp-cpp-template test-setup.cfg
cd "$CURRP"

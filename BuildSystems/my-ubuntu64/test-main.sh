#!/bin/bash
export CURRP=$(pwd)
cd "$CURRP/../../workdir"
./vp-cpp-template confExample.cfg
cd "$CURRP"

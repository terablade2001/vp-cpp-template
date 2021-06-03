#!/bin/bash
cd Libs/vp-cpp-template-extlibs
. ./cmake-build.sh
. ./rmake-build.sh
cd ../ExampleCTypes
. ./cmake-build.sh
. ./rmake-build.sh
cd ../ExampleCAPI
. ./cmake-build.sh
. ./rmake-build.sh
cd ../..
. ./cmake-build.sh
. ./rmake-build.sh
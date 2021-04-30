#!/bin/bash
cd Libs/vp-cpp-template-extlibs
. ./cmake-build.cmd
. ./rmake-build.cmd
cd ../ExampleCTypes
. ./cmake-build.cmd
. ./rmake-build.cmd
cd ../ExampleCAPI
. ./cmake-build.cmd
. ./rmake-build.cmd
cd ../..
. ./cmake-build.cmd
. ./rmake-build.cmd
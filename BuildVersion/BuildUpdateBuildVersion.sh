#!/bin/bash
clear
export CURRP=$(pwd)
cd ../ExtLibs/vkpLibs/vkpBuildVersioner/BuildSystems/my-ubuntu64/
sh cmake-build.sh
sh make-build.sh
cp -f ../../UpdateBuildVersion "$CURRP"
cd "$CURRP"

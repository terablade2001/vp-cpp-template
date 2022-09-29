#!/bin/bash
clear
export CURRP=$(pwd)
export BASEP="$CURRP/../../../.."
export ProjectName="vp-cpp-template-extlibs"
export ProjectFile="lib$ProjectName.so"
cd "$BASEP/build/build_$ProjectName/build"
make -j8
strip --strip-unneeded $ProjectFile
nm -gC $ProjectFile
cp -f $ProjectFile "$BASEP/python/"
mv -f $ProjectFile "$BASEP/workdir/"
cd "$CURRP"

#!/bin/bash
clear
export CURRP=$(pwd)
export BASEP="$CURRP/../../../.."
export ProjectName="ExampleCAPI"
export ProjectFile="lib$ProjectName.so"
cd $BASEP/BuildVersion
./UpdateBuildVersion
cd "$BASEP/C++/build_$ProjectName"
make -j8
strip --strip-unneeded $ProjectFile
nm -gC $ProjectFile
cp -f $ProjectFile "$BASEP/python/"
mv -f $ProjectFile "$BASEP/workdir/"
cd "$CURRP"
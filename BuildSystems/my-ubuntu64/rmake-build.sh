#!/bin/bash
clear
export CURRP=$(pwd)
export BASEP="$CURRP/../.."
export ProjectName="vp-cpp-template"
export ProjectFile="$ProjectName"
cd "$BASEP/build/build_$ProjectName/build"
make -j8
mv -f $ProjectFile "$BASEP/workdir/"
cd "$CURRP"

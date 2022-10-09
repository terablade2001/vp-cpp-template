#!/bin/bash
clear
export CURRP=$(pwd)
export BASEP="$CURRP/../.."
cd Libs
rm -rf ExampleCAPI
rm -rf ExampleCTypes
cd ${BASEP}/C++/Libs
rm -rf ExampleCAPI
rm -rf ExampleCTypes
cd ../src/ModuleTests
rm -rf *
cd ${BASEP}/workdir
rm -rf moduleTests
cd ${BASEP}/BuildSystems/emptyProject
cp -f Dockerfile_localDev ${BASEP}/Dockerfile_localDev
cp -f .gitlab-ci.yml ${BASEP}/.gitlab-ci.yml
cp -f main.yml ${BASEP}/.github/workflows/main.yml
cp -f Main.cpp ${BASEP}/C++/src/Main.cpp
cp -f newModule.cpp ${BASEP}/C++/src/ModuleTests/newModule.cpp
cp -f moduleTestsList.csv ${BASEP}/workdir/moduleTestsList.csv
cp -f my-ubuntu64/CMakeLists.txt ${BASEP}/BuildSystems/my-ubuntu64/CMakeLists.txt
cd ${CURRP}

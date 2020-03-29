#!/bin/sh
cd ../..
git submodule init
git submodule update --remote --recursive
rm -rf .gitmodules
rm .git/config
cp BuildSystems/config .git/config
git rm -rf --cached ExtLibs
rm -rf .git/modules/ExtLibs
cd ExtLibs
rm -rf .git
rm -rf .gitmodules
cd ..
git remote remove origin
git add --all
git commit -m "(DETACH):: Detached vp-cpp-template from origin project and libraries."

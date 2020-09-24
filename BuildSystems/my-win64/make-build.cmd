@echo off
set CURRP=%~dp0
cls
cd ..\..\BuildVersion
call UpdateBuildVersion.exe
cd "%CURRP%..\..\C++\build"
make -j8
move vp-cpp-template.exe "%CURRP%..\..\workdir\"
cd "%CURRP%"

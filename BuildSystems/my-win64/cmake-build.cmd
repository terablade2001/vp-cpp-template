@echo off
set CURRP=%~dp0
cls
copy CMakeLists.txt "%CURRP%..\..\C++\CMakeLists.txt"
cd "%CURRP%\..\..\C++""
rmdir build /S /Q
mkdir build && cd build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cd %CURRP%
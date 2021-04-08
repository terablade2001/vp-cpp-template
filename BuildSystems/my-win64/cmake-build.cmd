@echo off
set CURRP=%~dp0
set BASEP="%CURRP%..\.."
cls
copy CMakeLists.txt "%BASEP%\C++\CMakeLists.txt"
cd "%BASEP%\C++""
rmdir build /S /Q
mkdir build && cd build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cd %CURRP%

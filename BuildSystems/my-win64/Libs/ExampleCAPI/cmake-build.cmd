@echo off
set CURRP=%~dp0
set ProjectName="ExampleCAPI"
cls
copy CMakeLists.txt "%CURRP%..\..\..\..\C++\CMakeLists.txt"
cd "%CURRP%..\..\..\..\C++""
rmdir build_%ProjectName% /S /Q
mkdir build_%ProjectName% && cd build_%ProjectName%
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cd %CURRP%

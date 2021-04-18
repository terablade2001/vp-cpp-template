@echo off
set CURRP=%~dp0
set BASEP="%CURRP%..\..\..\.."
set ProjectName="ExampleCTypes"
cls
copy CMakeLists.txt "%BASEP%\C++\CMakeLists.txt"
cd "%BASEP%\C++""
rmdir build_%ProjectName% /S /Q
mkdir build_%ProjectName% && cd build_%ProjectName%
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cd %CURRP%

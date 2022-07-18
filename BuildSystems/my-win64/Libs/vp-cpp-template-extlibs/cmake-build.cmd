@echo off
set CURRP=%~dp0
set BASEP="%CURRP%..\..\..\.."
set ProjectName="vp-cpp-template-extlibs"
cd "%BASEP%\C++""
rmdir build_%ProjectName% /S /Q
mkdir build_%ProjectName% && cd build_%ProjectName%
copy "%CURRP%\CMakeLists.txt" "%BASEP%\C++\build_%ProjectName%\CMakeLists.txt"
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cd %CURRP%

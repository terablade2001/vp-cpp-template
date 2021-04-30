@echo off
set CURRP=%~dp0
set BASEP="%CURRP%..\.."
cls
cd "%BASEP%\C++\build"
make -j8
move vp-cpp-template.exe "%BASEP%\workdir\"
cd "%CURRP%"

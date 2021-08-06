@echo off
set CURRP=%~dp0
set BASEP="%CURRP%..\..\..\.."
set ProjectName="vp-cpp-template-extlibs"
set ProjectFile="lib%ProjectName%.dll"
cls
cd "%BASEP%\C++\build_%ProjectName%"
make -j8
strip --strip-unneeded "%ProjectFile%"
nm -gC "%ProjectFile%"
copy /Y "%ProjectFile%" "%BASEP%\python\"
move /Y "%ProjectFile%" "%BASEP%\workdir\"
cd "%CURRP%"
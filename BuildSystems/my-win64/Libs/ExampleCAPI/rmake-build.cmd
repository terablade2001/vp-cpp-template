@echo off
set CURRP=%~dp0
set BASEP="%CURRP%..\..\..\.."
set ProjectName="ExampleCAPI"
set ProjectFile="lib%ProjectName%.dll"
cd "%BASEP%\build\build_%ProjectName%\build"
make -j8
strip --strip-unneeded "%ProjectFile%"
nm -gC "%ProjectFile%"
copy /Y "%ProjectFile%" "%BASEP%\python\"
move /Y "%ProjectFile%" "%BASEP%\workdir\"
cd "%CURRP%"

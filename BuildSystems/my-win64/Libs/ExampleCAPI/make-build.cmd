@echo off
set CURRP=%~dp0
set ProjectName="ExampleCAPI"
cls
set ProjectFile="lib%ProjectName%.dll"
cd ..\..\..\..\BuildVersion
call UpdateBuildVersion.exe
cd "%CURRP%..\..\..\..\C++\build_%ProjectName%"
make -j8
strip --strip-unneeded "%ProjectFile%"
nm -gC "%ProjectFile%"
copy /Y "%ProjectFile%" "%CURRP%..\..\..\..\python\"
move /Y "%ProjectFile%" "%CURRP%..\..\..\..\workdir\"
cd "%CURRP%"

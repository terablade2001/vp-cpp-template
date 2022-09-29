@echo off
set CURRP=%~dp0
set BASEP="%CURRP%..\.."
set ProjectName="vp-cpp-template"
set ProjectFile="%ProjectName%.exe"
cd "%BASEP%\build\build_%ProjectName%\build"
make -j8
move /Y "%ProjectFile%" "%BASEP%\workdir\"
cd "%CURRP%"

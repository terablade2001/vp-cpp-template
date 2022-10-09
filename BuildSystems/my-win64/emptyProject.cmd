@echo off
set CURRP=%~dp0
set BASEP="%CURRP%..\.."
cd Libs
rmdir ExampleCAPI /S /Q
rmdir ExampleCTypes /S /Q
cd "%BASEP%\C++\Libs"
rmdir ExampleCAPI /S /Q
rmdir ExampleCTypes /S /Q
cd ..\src\ModuleTests
rmdir include /S /Q
del *.* /S /Q
cd "%BASEP%\workdir"
rmdir moduleTests /S /Q
cd "%BASEP%\BuildSystems\emptyProject"
copy /Y Dockerfile_localDev "%BASEP%\Dockerfile_localDev"
copy /Y .gitlab-ci.yml "%BASEP%\.gitlab-ci.yml%
copy /Y main.yml "%BASEP%\.github\workflows\main.yml"
copy /Y Main.cpp "%BASEP%\C++\src\Main.cpp"
copy /Y newModule.cpp "%BASEP%\C++\src\ModuleTests\newModule.cpp"
copy /Y moduleTestsList.csv "%BASEP%\workdir\moduleTestsList.csv"
copy /Y my-win64\CMakeLists.txt "%BASEP%\BuildSystems\my-win64\CMakeLists.txt"
cd "%CURRP%

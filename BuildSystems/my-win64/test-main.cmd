set CURRP=%~dp0
cd "%CURRP%..\..\C++\build"
vp-cpp-template.exe ..\..\workdir\test-setup.cfg
cd "%CURRP%"
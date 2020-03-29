set CURRP=%~dp0
cd "%CURRP%..\..\workdir"
vp-cpp-template.exe test-setup.cfg
cd "%CURRP%"

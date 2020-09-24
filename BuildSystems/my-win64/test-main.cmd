set CURRP=%~dp0
cd "%CURRP%..\..\workdir"
vp-cpp-template.exe confExample.cfg
cd "%CURRP%"

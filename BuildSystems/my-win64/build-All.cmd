cd Libs/vp-cpp-template-extlibs
call cmake-build.cmd
call rmake-build.cmd
cd ../ExampleCTypes
call cmake-build.cmd
call rmake-build.cmd
cd ../ExampleCAPI
call cmake-build.cmd
call rmake-build.cmd
cd ../..
call cmake-build.cmd
call rmake-build.cmd
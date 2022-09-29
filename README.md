# Table Of Contents

* [What is vp-cpp-template](#What is vp-cpp-template?): A few words about this project and why you may be interested to check and use it!
* [Quick build and testing](#Quick build and testing): Demonstrating how to quick install, compile and test it with just a few commands.
* [TODOs](#TODOs): Things that are planned to be added over time.
* [LICENSE](#LICENSE): License for this software/project.
* For further documentation a new [**Documentation.odt**](Documentation.odt) file (LibreOffice) is included.

**Warning**: The following notes may not be valid after **(0.049)** version...

# **What** is <u>vp-cpp-template</u>?

◄ [Table Of Contents](#Table Of Contents)

It's a C++ & Python framework which includes my most important libraries (CECS / CCEXP / 
MVECTOR / vkp_Config / PThreadPool / vkpLibs), in a ready-to-be-compiled scheme, under two BuildSystems: Windows and Ubuntu. The framework also provides predefined vscode tasks.

You can use this *ready-to-work-on* framework with the combined aforementioned libraries, in order to setup and build quick different C++ / Python projects, for different platforms. These libraries can help you achieve different things, from integrated advanced error control, easy binary data importing/exporting for debuging and integration issues, easy access to configuration files where multiple parameters can be set during development/testing, easy access to thread-pooling mechanisms, CSV files read/write, e.t.c. Regarding the different platforms the **vp-cpp-template** project provides a `BuildSystems/` folder where developers can add specific **cmake** setups for different targeted platforms. By default the project provides Windows (TDM-GCC) and Ubuntu support.

The **vp-cpp-template** project also provides some technologies / know-how (*i.e. contains examples of APIs where the generated C/C++ dynamic files can be accessed via Python*) for the users. The file structure is designed to support easy implementation and testing of libraries, which mean it's possible to use the **vp-cpp-template** project to generate and test different libraries, which you can later use elsewhere as dynamic libraries.

The included libraries can be compiled directly in the project, providing some technologies, like integrated Error Control System, pthreads thread pool, checking and reading of configuration files easily, projects common build versioning between C++ and Python parts, data sharing via dynamic format, etc. The libraries are referred below. 

* [CECS: *C/C++ Error Control System*](https://github.com/terablade2001/CECS)
* [PThreadPool: *pthreads Threading Pool in C++*](https://github.com/terablade2001/PThreadPool)
* [vkp_Config: *Configuration files reader in C++*](https://github.com/terablade2001/vkp_Config)
* [vkpLibs: *Utilities*](https://github.com/terablade2001/vkpLibs)
  * **vkpBuildVersioner** [C++, Python]: System for automated versioning in C++ and Python.
  * **vkpConfigReader** [C++]: Utility to load multiple variables from configuration files directly to the wanted types.
  * **vkpProgressBar** [C++]: A class to create custom progress bars in the stdout, to monitorprogress graphically.
  * **vkpCircularBuffer** [C++, Requires: CECS]: A very simple template-class for circular buffers where their index is treated alike infinite arrays.
  * **vkpTimer** [C++]: Classes for easily measuring and handling processing times between two points of code.
  * **vkpOpmlCpp** [C++]: Export data as strings to MindMap's opml format.
  * **vkpCSVHandler** [C++]: Load, handle and store CSV files in C++.
* [CCEXP: *Utility for easy user-defined structured data recording/importing/sharing in C++ / MatLab / Python3*](https://github.com/terablade2001/CCEXP)
* [MVECTOR: *A modified partial \<vector\> library which also tracks the size of the allocated memory*](https://github.com/terablade2001/MVECTOR) 

◄ [Table Of Contents](#Table Of Contents)

# Quick build and testing

◄ [Table Of Contents](#Table Of Contents)

This section shows how to quickly clone, build and test the template, in both windows (TDM-GCC) and ubuntu systems. In both cases the **vp-cpp-template** project will execute a Modules-Test and provide the results that passed (all 3 modules / tests should pass).

## Windows system

```sh
## clone project.
git clone https://github.com/terablade2001/vp-cpp-template.git

# Detach and autoprepare project: Use commands from bash-shell (i.e. after installing git), not windows CMD shell.
cd vp-cpp-template/BuildSystems/my-win64
./detachProjectFromGit.sh

## Now use windows CMD shell in the clone vp-cpp-template/ folder.
## Start building the sub-modules/libraries (.dll files)
cd BuildSystems\my-win64\Libs\vp-cpp-template-extlibs
cmake-build.cmd
rmake-build.cmd
cd ..\ExampleCTypes
cmake-build.cmd
rmake-build.cmd
cd ..\ExampleCAPI
cmake-build.cmd
rmake-build.cmd
## Build the main project (Main + ModulesTesting)
cd ..\..
cmake-build.cmd
rmake-build.cmd

## Module Testing (C/C++)
cd ..\..\workdir
vp-cpp-template.exe confModuleTesting-Windows.cfg
```

## Ubuntu system
```sh
## clone project
git clone https://github.com/terablade2001/vp-cpp-template.git

# Detach and autoprepare project
cd vp-cpp-template/BuildSystems/my-ubuntu64
./detachProjectFromGit.sh

## Start building the sub-modules/libraries (.so files)
cd Libs/vp-cpp-template-extlibs
./cmake-build.cmd
./rmake-build.cmd
cd ../ExampleCTypes
./cmake-build.cmd
./rmake-build.cmd
cd ../ExampleCAPI
./cmake-build.cmd
./rmake-build.cmd
## Build the main project (Main + ModulesTesting)
cd ../..
./cmake-build.cmd
./rmake-build.cmd

## Module Testing (C/C++)
cd ../../workdir
./vp-cpp-template confModuleTesting-Ubuntu.cfg
```


## Expected similar test-run results like:

```shell
<63, DummyClass.cpp, L-6>: libExampleCAPI.dll:: DummyClass - constructor

=======================================================================
= VP-CPP-TEMPLATE (https://github.com/terablade2001/vp-cpp-template)  =
= Program version: [0.049]                                            =
=======================================================================
ProcessType: ModuleTesting
=======================================================================
Enabled Tests = 3 / 3

------- START TESTING -------
[+][Passed] TestID: [2] (1 / 3) :: time: 34.751 msec
[+][Passed] TestID: [3] (2 / 3) :: time: 30.8361 msec
[+][Passed] TestID: [1] (3 / 3) :: time: 2519.9 msec
----- TESTING COMPLETED ------


>>>>>>> TEST RESULTS <<<<<<<
MODULE-TESTING: Total Tests = [3]
MODULE-TESTING: - Enabled Tests = [3]
   [+][Passed]: TestID = [1] > Testing default example of vp-cpp-template where different utilities are working together as a working example.
   [+][Passed]: TestID = [2] > Testing the CAPI library that is compiled as an example in vp-cpp-template project.
   [+][Passed]: TestID = [3] > Testing the vkpCSVHandler utility.
MODULE-TESTING: - Passed Tests = [3] out of 3
MODULE-TESTING: - Timer [Total Testing Time]: Avg = 2520.63 ms. (2520.63 / 1)
>>>>>>>==============<<<<<<<

=*-*= Program completed =*-*=
```

• The intermediate results of the three individual Module-Tests can be also seen in the generated `moduleTestsLog_Passed.log` file.

◄ [Table Of Contents](#Table Of Contents)


# TODOs

◄ [Table Of Contents](#Table Of Contents)

Things that are expected to be added in the project over time.

- [ ] Update template of Documentation.odt
- [ ] GitLab CI pipeline (for offline runners)
- [ ] GitHub CI pipeline (for offline runners)
- [ ] Support for `info_(level,string)` macro
- [ ] Update `vkpProgressBar` (resolve some issues)
- [ ] Easy support for integration with *OpenCV*
- [ ] Adding some support functions
  - [ ] makeDir()
  - [ ] Support functions for *OpenCV*

## Completed TODOs
### version (0.049)
- [x] Integrated ModuleTesting
- [x] Move all intermediate builds to build/ folder instead of C++/ folder.
  - [x] Ubuntu build
  - [x] Windows build
- [x] Re-write Quick Installation and Testing notes here.
- [x] Update / re-design README.md file
- [x] Some cleaning ...
  - [x] Removing *tasks* for vscode.
  - [x] Removing make-build.{cmd/sh} and build-all.{cmd/sh} commands.


◄ [Table Of Contents](#Table Of Contents)

# LICENSE

◄ [Table Of Contents](#Table Of Contents)

```
MIT License

Copyright (c) 2016 - 2022 Vasileios Kon. Pothos (terablade2001)
https://github.com/terablade2001/vp-cpp-template

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```

◄ [Table Of Contents](#Table Of Contents)


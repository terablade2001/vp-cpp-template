# Table Of Contents

* [What is vp-cpp-template](#what-is-vp-cpp-template): A few words about this project and why you may be interested to check and use it!
* [Quick build and testing](#quick-build-and-testing): Demonstrating how to quick install, compile and test it with just a few commands.
* [TODOs](#todos): Things that are planned to be added over time.
	* [Completed TODOs - versioning](#completed-todos---versioning)
* [LICENSE](#license): License for this software/project.
* For further documentation a new [**Documentation.odt**](Documentation.odt) file (LibreOffice) is included.
  * For the PDF version of the documentation see [Documentation.pdf](Documentation.pdf).

**Warning**: The following notes may not be valid after **(0.057)** version...

# **What** is <u>vp-cpp-template</u>?

◄ [Table Of Contents](#table-of-contents)

It's a C++ & Python framework which includes my most important libraries (CECS / CCEXP / 
MVECTOR / vkp_Config / PThreadPool / vkpLibs), in a ready-to-be-compiled scheme, under two BuildSystems: Windows and Ubuntu.

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

◄ [Table Of Contents](#table-of-contents)

# Quick build and testing

◄ [Table Of Contents](#table-of-contents)

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
= Program version: [0.057]                                            =
=======================================================================
ProcessType: ModuleTesting
=======================================================================
Enabled Tests = 11 / 11

>>>>>>> TEST RESULTS <<<<<<<
MODULE-TESTING: Total Tests = [11]
MODULE-TESTING: - Enabled Tests = [11]
   [+](-)[Passed]: TestID = [1] > Testing default example of vp-cpp-template where different utilities are working together as a working example.
   [+](-)[Passed]: TestID = [2] > Testing the CAPI library that is compiled as an example in vp-cpp-template project.
   [+](+)[Passed]: TestID = [3] > Testing the vkpCSVHandler utility.
   [+](+)[Passed]: TestID = [4] > Testing CLI test id 0 (Test_CLIReader())
   [+](+)[Passed]: TestID = [5] > Testing CLI test id 0 (Test_CLIReader())
   [+](-)[Passed]: TestID = [6] > Testing CLI test id 0 (Test_CLIReader()): No --cli command -> should fail!
   [+](-)[Passed]: TestID = [7] > Testing CLI test id 0 (Test_CLIReader()): Not -testId -> should fail
   [+](-)[Passed]: TestID = [8] > Testing CLI test id 0 (Test_CLIReader()): Not supported -testId -> should fail
   [+](-)[Passed]: TestID = [9] > Testing CLI test id 0 (Test_CLIReader()): --cli command would require testId=0 too -> should fail
   [+](+)[Passed]: TestID = [10] > Testing CLI test id 0 (Test_CLIReader()): Should pass. Two argv[0] should be visible
   [+](+)[Passed]: TestID = [11] > Testing CLI test id 0 (Test_CLIReader()): Should pass (vkpLibs-0.220 tests)
MODULE-TESTING: - Passed Tests = [11] out of 11
MODULE-TESTING: - Timer [Total Testing Time]: Avg = 2020.13 ms. (2020.13 / 1)
>>>>>>>==============<<<<<<<

=*-*= Program completed =*-*=
```

• The intermediate results of the three individual Module-Tests can be also seen in the generated `moduleTestsLog_Passed.log` file.

◄ [Table Of Contents](#table-of-contents)


# TODOs

◄ [Table Of Contents](#table-of-contents)

Things that are expected to be added in the project, over time.

- [ ] Update `vkpProgressBar` (resolve some issues)
- [ ] Easy support for integration with *OpenCV*
- [ ] Adding some support functions
  - [ ] makeDir()
  - [ ] Support functions for *OpenCV*

## Completed TODOs - versioning

### version (0.057)
- [x] GitHub CI pipeline (for offline runners) (see [Documentation.pdf r1v147](Documentation.pdf) :: page 19)

### version (0.056)
- [x] vkpLibs (0.220) - Updates regarding the vkpConfigReader and the CLI relative code (*for more info check [vkpLibs](https://github.com/terablade2001/vkpLibs) repository*)
### version (0.055)
- [x] vkpLibs (0.219) - Support CLI input parsing with vkpConfigReader update (*Support a CLI reader/analyzer integrated with vkpConfigReader*).
  - [x] vkpConfigReader can be used also without the CECS (see self-contained working example code at: `ExtLibs/vkpLibs/vkpConfigReader/test/main.cpp`)
- [x] `Main.cpp` updated to support Module tests either via CLI input or via Configuration Files. For CLI input use `--cli` and `-testId <test number>`. The example uses `-testId 0`. For configuration files (previous behaviour) don't use the `--cli` flag.
- [x] Module `ModuleTesting.cpp` updated to also show the actual test result. For instance the `(-)` in the result:
  `[+](-)[Passed]: TestID = [6] > Testing CLI test id 0 (Test_CLIReader()): No --cli command -> should fail!`
  indicates that the test is indeed failed (see generated fle `moduleTestsLog_Failed.log` ), but we expected it to fail thus it passed, and so it has the symbols `[+]`.
- [x] Including a number of CLI unit tests, reaching up to 10 enabled tests for the whole project.
  - [x] Setting `DbgVerboseLevel` to `1` for Modules Testing


### version (0.054)
- [x] CECS (0.132) - including helper macro `info_(level,string)`.
### version (0.053)
- [x] Document an example of adding and testing a new Module with GitLab CI (see [Documentation.pdf](Documentation.pdf) :: page 19)
### version (0.052)
- [x] Updated GitLab CI pipeline to also delete previous images/containers (cleaning)
- [x] The ModuleTesting module is now comparing against the expected result status of tests. This gives the ability for the user to define in the testing CSV file which tests are expected to completed correctly and which are expected to generate errors. If a test produce what the user expects then it considered as Passed. If not, it's considered as Failed.
### version (0.051)
- [x] Added GitLab CI pipeline for offline runners.
  - [x] Document an example with GitLab CI integration.
- [x] Export and provide `Documentation.odt` also as a PDF.
### version (0.050)
- [x] Update template of Documentation.odt
- [x] Update documentation with more info regarding template's file structure, main() and processed and the ModuleTesting support.
### version (0.049.01)
- [x] Fix README.md anchor links to be displayed correctly.
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


◄ [Table Of Contents](#table-of-contents)

# LICENSE

◄ [Table Of Contents](#table-of-contents)

```
MIT License

Copyright (c) 2016 - 2022 Vasileios Kon. Pothos (terablade2001)
https://github.com/terablade2001/vp-cpp-template

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```

◄ [Table Of Contents](#table-of-contents)


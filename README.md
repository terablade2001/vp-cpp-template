# **What** is <u>vp-cpp-template</u>?

It's a C++ & Python framework which includes my most important libraries (CECS / CCEXP / 
MVECTOR / vkp_Config / PThreadPool / vkpLibs), in a ready-to-be-compiled scheme, under two BuildSystems: Win and Ubuntu. The framework also provides predefined vscode tasks.

## What are those libraries?

There are libraries that can be compiled directly in the project, providing directly some technologies, like integrated Error Control System, pthreads thread pool, checking and reading of configuration files easily, projects common build versioning between C++ and Python parts, data sharing via dynamic format, etc. The included libraries are referred below. 

* [CECS: *C/C++ Error Control System*](https://github.com/terablade2001/CECS)
* [PThreadPool: *pthreads Threading Pool in C++*](https://github.com/terablade2001/PThreadPool)
* [vkp_Config: *Configuration files reader in C++*](https://github.com/terablade2001/vkp_Config)
* [vkpLibs: *Utilities*](https://github.com/terablade2001/vkpLibs)
  * vkpBuildVersioner [C++, Python]: *System for automated versioning in C++ and Python.*
  * vkpProgressBar [C++]: *A class to create custom progress bars in the stdout, to monitor progress graphically.*
* [CCEXP: *Utility for easy user-defined structured data recording/importing/sharing in C++ / MatLab / Python3*](https://github.com/terablade2001/CCEXP)
* [MVECTOR: *A modified partial \<vector\> library which also tracks the size of the allocated memory*](https://github.com/terablade2001/MVECTOR) 

# **Why** to use <u>vp-cpp-template</u>?

If you need a ready-to-work-on framework with those basic technologies, without messing up with the setup of all those libraries.

**vp-cpp-template** project also provides a BuildSystem approach thus the same code to be able to compiled and build on different environments easily.

# **Example** please?

## Clone the library...

Use: `git clone https://github.com/terablade2001/vp-cpp-template.git --recursive`

Or you may clone normally and use later the following commands: `git submodule update --init --recursive`

## Select BuildSystem and test...

Enter the `BuildSystems` folder, and then enter either at `my-ubuntu64` or at `my-win64` folder.

Run the `cmake-build`,`make-build` and `test-main` batch files correspondingly.

Check also python test by running the file `Python/test.py` after having run the `test-main` C++ example code! The python script is using CCEXP to read and display the data that the C++ code exported! 

## View code combining the technologies

Check the `C++/src/Main.cpp` file!
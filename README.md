# Quick **installation**

**From project's root folder...**

## Windows
```bash
### WITH WINDOWS GIT-BASH SOFTWARE ###
# Clone and detach project template for further development.
git clone https://github.com/terablade2001/vp-cpp-template.git
cd vp-cpp-template/BuildSystems/my-win64
./detachProjectFromGit.sh

### WITH WINDOWS COMMAND PROMPT ###
# Build the test project
cd BuildSystems/my-win64
./cmake-build.cmd
./make-build.cmd
./test-main.cmd

# Python 3 reading produced CCEXP Test
cd ../../python
python Test.py
```
## Ubuntu (*with git support*)
```bash
# Clone and detach project template for further development.
git clone https://github.com/terablade2001/vp-cpp-template.git
cd vp-cpp-template/BuildSystems/my-ubuntu
./detachProjectFromGit.sh

# Build the test project
cd BuildSystems/my-ubuntu
./cmake-build.sh
./make-build.sh
./test-main.sh

# Python 3 reading produced CCEXP Test
cd ../../python
python Test.py
```

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
  * vkpCircularBuffer [C++, Requires: CECS]: *A very simple template-class for circular buffers where their index is treated alike infinite arrays.*
  * vkpTimer [C++]: *Classes for easily measuring and handling processing times between two points of code.*
* [CCEXP: *Utility for easy user-defined structured data recording/importing/sharing in C++ / MatLab / Python3*](https://github.com/terablade2001/CCEXP)
* [MVECTOR: *A modified partial \<vector\> library which also tracks the size of the allocated memory*](https://github.com/terablade2001/MVECTOR) 

# **Why** to use <u>vp-cpp-template</u>?

If you need a ready-to-work-on framework with those basic technologies, without messing up with the setup of all those libraries.

**vp-cpp-template** project also provides a BuildSystem approach thus the same code to be able to compiled and build on different environments easily.


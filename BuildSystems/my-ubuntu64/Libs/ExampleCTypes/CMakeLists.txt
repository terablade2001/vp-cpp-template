cmake_minimum_required(VERSION 2.8.11)

set(PROJECTNAME "ExampleCTypes")

project(${PROJECTNAME})
message(WARNING "[CMAKE_CURRENT_LIST_DIR] = ${CMAKE_CURRENT_LIST_DIR}")
set (BASE_PROJECT_FOLDER "${CMAKE_CURRENT_LIST_DIR}/../..")

# Code and Path to other .dlls and libs
# message("PKG_CONFIG_PATH = $ENV{PKG_CONFIG_PATH}")
# find_package(OpenCV 4.1.0 REQUIRED)
# add_library(opencvbuild MODULE IMPORTED)
# set_target_properties(opencvbuild PROPERTIES IMPORTED_LOCATION "[...]/libopencv_world410.dll")

set(CXX_FLAGS "-std=c++11 -O3 -s -Wall -Wno-unused-result -Wno-unused-variable -Wno-parentheses -D__ECSOBJ__=ECS -Ddbg_SHOW_INFO=2 -DVKP_USE_PTHREAD_POOL")
set(C_FLAGS "-Wall -O3 -s -Wno-unused-result -Wno-unused-variable -Wno-parentheses -D__ECSOBJ__=ECS -Ddbg_SHOW_INFO=2 -DVKP_USE_PTHREAD_POOL")
include("${BASE_PROJECT_FOLDER}/BuildSystems/BuildConfigurations.cmake")

set(CMAKE_CONFIGURATION_TYPES "Release")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${C_FLAGS}")
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L. ")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined,-rpath,\$ORIGIN -Wl,-z,origin")

include_directories(
  ${BASE_PROJECT_FOLDER}/
  ${BASE_PROJECT_FOLDER}/C++/Common/
  ${BASE_PROJECT_FOLDER}/ExtLibs/CCEXP/C++/src/include
  ${BASE_PROJECT_FOLDER}/ExtLibs/CECS/C++/src/include
  ${BASE_PROJECT_FOLDER}/ExtLibs/MVECTOR/src/include
  ${BASE_PROJECT_FOLDER}/ExtLibs/PThreadPool/C/src/include
  ${BASE_PROJECT_FOLDER}/ExtLibs/vkpLibs
)

add_library(vpCppTemplateExtLibs MODULE IMPORTED)
set_target_properties(vpCppTemplateExtLibs PROPERTIES IMPORTED_LOCATION "${BASE_PROJECT_FOLDER}/workdir/libvp-cpp-template-extlibs.so")
file(GLOB CXX_SRCS
  "${BASE_PROJECT_FOLDER}/C++/Libs/ExampleCTypes/src/*.cpp"
)

add_library(${PROJECTNAME} SHARED ${CXX_SRCS} ${C_SRCS})
set(LINK_OPTIONS "-pthread" ${LINK_OPTIONS})
target_link_libraries(${PROJECTNAME} vpCppTemplateExtLibs ${LINK_OPTIONS})

cmake_minimum_required(VERSION 2.8.11)

set(PROJECTNAME "vp-cpp-template")
# set(LINK_OPTIONS "-pthread")

project(${PROJECTNAME})
message(WARNING "[CMAKE_CURRENT_LIST_DIR] = ${CMAKE_CURRENT_LIST_DIR}")

set(CXX_FLAGS "-std=c++11 -O3 -s -Wall -Wno-unused-result -Wno-unused-variable -Wno-parentheses -D__ECSOBJ__=ECS -Ddbg_SHOW_INFO=2 -DVKP_USE_PTHREAD_POOL")
set(C_FLAGS "-Wall -O3 -s -Wno-unused-result -Wno-unused-variable -Wno-parentheses -D__ECSOBJ__=ECS -Ddbg_SHOW_INFO=2 -DVKP_USE_PTHREAD_POOL")

set(CMAKE_CONFIGURATION_TYPES "Release")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${C_FLAGS}")
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L. ")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined,-rpath,\$ORIGIN")

add_library(example_c_api MODULE IMPORTED)
set_target_properties(example_c_api PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../workdir/libExampleCAPI.dll")

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../C++/Common
  ${CMAKE_CURRENT_LIST_DIR}/../C++/Libs/ExampleCAPI/API-Headers
  ${CMAKE_CURRENT_LIST_DIR}/../C++/src/include
  ${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/CCEXP/C++/src/include
  ${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/CECS/C++/src/include
  ${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/MVECTOR/src/include
  ${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/PThreadPool/C/src/include
  ${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/vkpLibs
)

add_library(vpCppTemplateExtLibs MODULE IMPORTED)
set_target_properties(vpCppTemplateExtLibs PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../workdir/libvp-cpp-template-extlibs.dll")
file(GLOB CXX_SRCS
  "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
)

add_executable(${PROJECTNAME} ${CXX_SRCS} ${C_SRCS})
target_link_libraries(${PROJECTNAME} example_c_api vpCppTemplateExtLibs ${LINK_OPTIONS})

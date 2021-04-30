cmake_minimum_required(VERSION 2.8.11)

set(PROJECTNAME "vp-cpp-template-extlibs")
set(LINK_OPTIONS "-pthread")

project(${PROJECTNAME})

set(CXX_FLAGS "-std=c++11 -O3 -s -Wall -Wno-unused-result -Wno-unused-variable -Wno-parentheses -D__ECSOBJ__=ECS -Ddbg_SHOW_INFO=2 -DVKP_USE_PTHREAD_POOL")
set(C_FLAGS "-Wall -O3 -s -Wno-unused-result -Wno-unused-variable -Wno-parentheses -D__ECSOBJ__=ECS -Ddbg_SHOW_INFO=2 -DVKP_USE_PTHREAD_POOL")

set(CMAKE_CONFIGURATION_TYPES "Release")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${C_FLAGS}")
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L. ")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined,-rpath,\$ORIGIN")

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/Common/
  ${CMAKE_CURRENT_LIST_DIR}/Libs/vp-cpp-template-extlibs/API-Headers
  ${CMAKE_CURRENT_LIST_DIR}/..
  ${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/CCEXP/C++/src/include
  ${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/CECS/C++/src/include
  ${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/MVECTOR/src/include
  ${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/PThreadPool/C/src/include
  ${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/vkpLibs
)
file(GLOB CXX_SRCS
  "${CMAKE_CURRENT_LIST_DIR}/Libs/vp-cpp-template-extlibs/src/*.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/CCEXP/C++/src/*.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/CECS/C++/src/*.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/MVECTOR/src/*.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/PThreadPool/C/src/*.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/vkpLibs/vkpCircularBuffer/*.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/vkpLibs/vkpConfigReader/src/*.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/vkpLibs/vkpProgressBar/*.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/vkpLibs/vkpTimer/*.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/vkpLibs/vkpOpmlCPP/*.cpp"
)

add_library(${PROJECTNAME} SHARED ${CXX_SRCS} ${C_SRCS})
target_link_libraries(${PROJECTNAME} ${LINK_OPTIONS})

cmake_minimum_required(VERSION 2.8.11)

set(PROJECTNAME "vp-cpp-template-extlibs")

project(${PROJECTNAME})
message(WARNING "[CMAKE_CURRENT_LIST_DIR] = ${CMAKE_CURRENT_LIST_DIR}")
set (BASE_PROJECT_FOLDER "${CMAKE_CURRENT_LIST_DIR}/../..")

set(CXX_FLAGS "-std=c++11 -O3 -s -Wall -Wno-unused-result -Wno-unused-variable -Wno-parentheses -D__ECSOBJ__=ECS -Ddbg_SHOW_INFO=2 -DVKP_USE_PTHREAD_POOL")
set(C_FLAGS "-Wall -O3 -s -Wno-unused-result -Wno-unused-variable -Wno-parentheses -D__ECSOBJ__=ECS -Ddbg_SHOW_INFO=2 -DVKP_USE_PTHREAD_POOL")
include("${BASE_PROJECT_FOLDER}/BuildSystems/BuildConfigurations.cmake")

set(CMAKE_CONFIGURATION_TYPES "Release")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${C_FLAGS}")
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L. ")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined,-rpath,\$ORIGIN")

include_directories(
  ${BASE_PROJECT_FOLDER}/C++/Common/
  ${BASE_PROJECT_FOLDER}/C++/Libs/vp-cpp-template-extlibs/API-Headers
  ${BASE_PROJECT_FOLDER}/
  ${BASE_PROJECT_FOLDER}/ExtLibs/CCEXP/C++/src/include
  ${BASE_PROJECT_FOLDER}/ExtLibs/CECS/C++/src/include
  ${BASE_PROJECT_FOLDER}/ExtLibs/MVECTOR/src/include
  ${BASE_PROJECT_FOLDER}/ExtLibs/PThreadPool/C/src/include
  ${BASE_PROJECT_FOLDER}/ExtLibs/vkpLibs
)
file(GLOB CXX_SRCS
  "${BASE_PROJECT_FOLDER}/C++/Common/*.cpp"
  "${BASE_PROJECT_FOLDER}/C++/Libs/vp-cpp-template-extlibs/src/*.cpp"
  "${BASE_PROJECT_FOLDER}/ExtLibs/CCEXP/C++/src/*.cpp"
  "${BASE_PROJECT_FOLDER}/ExtLibs/CECS/C++/src/*.cpp"
  "${BASE_PROJECT_FOLDER}/ExtLibs/MVECTOR/src/*.cpp"
  "${BASE_PROJECT_FOLDER}/ExtLibs/PThreadPool/C/src/*.cpp"
  "${BASE_PROJECT_FOLDER}/ExtLibs/vkpLibs/vkpCircularBuffer/*.cpp"
  "${BASE_PROJECT_FOLDER}/ExtLibs/vkpLibs/vkpConfigReader/src/*.cpp"
  "${BASE_PROJECT_FOLDER}/ExtLibs/vkpLibs/vkpProgressBar/*.cpp"
  "${BASE_PROJECT_FOLDER}/ExtLibs/vkpLibs/vkpTimer/*.cpp"
  "${BASE_PROJECT_FOLDER}/ExtLibs/vkpLibs/vkpOpmlCPP/*.cpp"
  "${BASE_PROJECT_FOLDER}/ExtLibs/vkpLibs/vkpCSVHandler/*.cpp"
)

add_library(${PROJECTNAME} SHARED ${CXX_SRCS} ${C_SRCS})
# set(LINK_OPTIONS "-pthread" ${LINK_OPTIONS})
target_link_libraries(${PROJECTNAME} ${LINK_OPTIONS})

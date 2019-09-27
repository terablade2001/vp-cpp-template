cmake_minimum_required(VERSION 2.8.11)

set(PROJECTNAME "vp-cpp-template")
set(LINK_OPTIONS "-pthread")

project(${PROJECTNAME})

if (MINGW)
	set(CXX_FLAGS "-std=c++11 -Wall -D__ECSOBJ__=ECS")
	set(C_FLAGS "-Wall -D__ECSOBJ__=ECS")
endif(MINGW)
if (UNIX)
	set(CXX_FLAGS "-std=c++11 -Wall -Wno-unused-result -D__ECSOBJ__=ECS")
	set(C_FLAGS "-Wall -Wno-unused-result -D__ECSOBJ__=ECS")
endif(UNIX)


set(CMAKE_CONFIGURATION_TYPES "Release")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${C_FLAGS}")
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L. ")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")

include_directories(
	${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/CCEXP/C++/src/include
	${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/CECS/C++/src/include
	${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/MVECTOR/src/include
	${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/PThreadPool/C/src/include
	${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/vkp_Config/src
	${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/vkpLibs/vkpBuildVersioner/C++
	${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/vkpLibs/vkpProgressBar
)
file(GLOB CXX_SRCS
    "${CMAKE_CURRENT_LIST_DIR}/src/Main.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/CCEXP/C++/src/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/CECS/C++/src/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/MVECTOR/src/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/PThreadPool/C/src/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/vkp_Config/src/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/../ExtLibs/vkpLibs/vkpProgressBar/*.cpp"
)

add_executable(${PROJECTNAME} ${CXX_SRCS} ${C_SRCS})
target_link_libraries(${PROJECTNAME} ${LINK_OPTIONS})
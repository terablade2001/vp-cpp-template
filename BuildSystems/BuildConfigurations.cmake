# set(CXX_FLAGS "${CXX_FLAGS} -DAPP_RELEASE_MODE")

# set(IS_USING_OPENCV TRUE)


if(DEFINED IS_USING_OPENCV)
  set(CXX_FLAGS "${CXX_FLAGS} -DVP_CPP_TEMPLATE__USING_OPENCV")
  set(C_FLAGS "${C_FLAGS} -DVP_CPP_TEMPLATE__USING_OPENCV")
  if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
    set(ENV{PKG_CONFIG_PATH} "/usr/local/opencv-4.1.0/lib/pkgconfig/:$ENV{PKG_CONFIG_PATH}")
  endif()
  if(CMAKE_GENERATOR STREQUAL "MinGW Makefiles")
    set(ENV{PKG_CONFIG_PATH} "<your .pc file path>")
  endif()
  message("PKG_CONFIG_PATH = $ENV{PKG_CONFIG_PATH}")
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(OPENCV4_PKG REQUIRED IMPORTED_TARGET opencv4>=4.1.0)
  include_directories(
    ${OPENCV4_PKG_INCLUDE_DIRS}
  )
  link_directories(
    ${OPENCV4_PKG_LIBRARY_DIRS}
  )
  set(LINK_OPTIONS ${LINK_OPTIONS} ${OPENCV4_PKG_LDFLAGS})
endif()

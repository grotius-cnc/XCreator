cmake_minimum_required(VERSION 3.5)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

SET(GCC_COVERAGE_COMPILE_FLAGS "-fPIC")
SET(GCC_COVERAGE_LINK_FLAGS    "-fPIC")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

include_directories("${SRC_DIR}/")
include_directories("${SRC_DIR}/lodepng")

ADD_LIBRARY(XClient SHARED
    XBind.cpp
    XClient.h
    XClient.cpp
    lodepng/lodepng.h
    lodepng/lodepng.cpp
    )


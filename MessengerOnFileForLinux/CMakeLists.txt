cmake_minimum_required (VERSION 3.5.1)
project(CMakeBuildTree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(LIBRARY_OUTPUT_PATH build/)
set(BINARY_OUTPUT_PATH build/)
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )



# LIBRARY

include(CTest)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(GTest REQUIRED)


# SRC
add_subdirectory(main/src)


# TEST
#add_subdirectory(main/test)

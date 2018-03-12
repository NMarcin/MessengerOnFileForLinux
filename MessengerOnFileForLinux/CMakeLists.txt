cmake_minimum_required (VERSION 3.5.1)
project(CMakeBuildTree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(LIBRARY_OUTPUT_PATH build/)
set(BINARY_OUTPUT_PATH build/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# OUTSIDE LIBRARIES
include(CTest)
include_directories(${GTEST_INCLUDE_DIRS})
find_package(GTest REQUIRED)


# LIB
include_directories(${CMAKE_SOURCE_DIR}/UserService/src)
include_directories(${CMAKE_SOURCE_DIR}/FileHandling/src)
include_directories(${CMAKE_SOURCE_DIR}/LoggerFramework/src)
include_directories(${CMAKE_SOURCE_DIR}/Chat/src)

# SRC
add_subdirectory(main/src)
add_subdirectory(UserService/src)
add_subdirectory(FileHandling/src)
add_subdirectory(LoggerFramework/src)
add_subdirectory(Chat/src)

message(STATUS ${SOURCES})

add_executable(messenger_binary ${SOURCES})

# TEST
add_subdirectory(main/test)
# add_subdirectory(UserService/test)
# add_subdirectory(FileHandling/test)
# add_subdirectory(Chat/test)
message(STATUS ${TEST_SOURCES})

add_executable(messenger_binary_UT ${TEST_SOURCES})

target_link_libraries(messenger_binary_UT ${GTEST_LIBRARIES} pthread)
#add_custom_target(UT $<TARGET_FILE:messenger_binary_UT>)

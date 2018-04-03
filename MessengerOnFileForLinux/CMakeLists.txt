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
find_package (Threads REQUIRED)


# LIB_SRC
include_directories(${CMAKE_SOURCE_DIR}/UserService/src)
include_directories(${CMAKE_SOURCE_DIR}/FileHandling/src)
include_directories(${CMAKE_SOURCE_DIR}/LoggerFramework/src)
include_directories(${CMAKE_SOURCE_DIR}/ChatFile/src)

# SRC
add_subdirectory(main/src)
add_subdirectory(UserService/src)
add_subdirectory(FileHandling/src)
add_subdirectory(LoggerFramework/src)
add_subdirectory(ChatFile/src)

message(STATUS ${SOURCES})

add_executable(messenger_binary ${SOURCES} ${MAIN})
target_link_libraries (messenger_binary ${CMAKE_THREAD_LIBS_INIT})

#LIB_TEST
include_directories(${CMAKE_SOURCE_DIR}/LoggerFramework/test)
include_directories(${CMAKE_SOURCE_DIR}/ChatFile/test)
# TEST
add_subdirectory(main/test)
add_subdirectory(FileHandling/test)
add_subdirectory(LoggerFramework/test)
add_subdirectory(ChatFile/test)


message(STATUS ${TEST_SOURCES})

set(TEST_SOURCES ${TEST_SOURCES} ${SOURCES})
add_executable(messenger_binary_UT ${TEST_SOURCES})

target_link_libraries(messenger_binary_UT ${GTEST_LIBRARIES} pthread)


#VALGRIND
find_program(VALGRIND "valgrind")
if(VALGRIND)
    message("VALGRIND found in path:" ${VALGRIND})
    target_link_libraries(messenger_binary_UT LINK_PUBLIC)
    add_custom_target(valgrind COMMAND "${VALGRIND}" --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=no --track-origins=yes $<TARGET_FILE:messenger_binary_UT>)
endif()

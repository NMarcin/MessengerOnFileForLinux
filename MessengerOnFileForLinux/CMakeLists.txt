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

################################################################################
#####                         MODULE DIR SOURCES                           #####
################################################################################
set(MODULE_UserService              ${CMAKE_SOURCE_DIR}/UserService/src)
set(MODULE_FileHandling             ${CMAKE_SOURCE_DIR}/FileHandling/src)
set(MODULE_LoggerFramework          ${CMAKE_SOURCE_DIR}/LoggerFramework/src)
set(MODULE_ChatFile                 ${CMAKE_SOURCE_DIR}/ChatFile/src)
set(MODULE_TerminalFunctionality    ${CMAKE_SOURCE_DIR}/TerminalFunctionality/src)

################################################################################
#####                       MAKE BINARY CMAKE PART                         #####
################################################################################
# LIB_SRC
include_directories(${MODULE_UserService})
include_directories(${MODULE_FileHandling})
include_directories(${MODULE_LoggerFramework})
include_directories(${MODULE_ChatFile})
include_directories(${MODULE_TerminalFunctionality})
# SRC
add_subdirectory(main/src)
add_subdirectory(${MODULE_UserService})
add_subdirectory(${MODULE_FileHandling})
add_subdirectory(${MODULE_LoggerFramework})
add_subdirectory(${MODULE_ChatFile})
add_subdirectory(${MODULE_TerminalFunctionality})
# CMAKE BUILD
add_executable(messenger_binary ${SOURCES} ${MAIN})
target_link_libraries (messenger_binary ${CMAKE_THREAD_LIBS_INIT})

################################################################################
#####                       MAKE UNIT TESTS CMAKE PART                     #####
################################################################################
#LIB_TEST
include_directories(${CMAKE_SOURCE_DIR}/LoggerFramework/test)
include_directories(${CMAKE_SOURCE_DIR}/ChatFile/test)
# TEST
add_subdirectory(main/test)
add_subdirectory(FileHandling/test)
add_subdirectory(LoggerFramework/test)
add_subdirectory(ChatFile/test)
add_subdirectory(UserService/test)

# CMAKE BUILD
set(TEST_BINARY_FILES ${TEST_SOURCES} ${TEST_FILES} ${MAIN_TEST})
add_executable(messenger_binary_UT ${TEST_BINARY_FILES})
target_link_libraries(messenger_binary_UT ${GTEST_LIBRARIES} pthread)


################################################################################
#####                               VALGIRN                                #####
################################################################################
find_program(VALGRIND "valgrind")
if(VALGRIND)
    message("VALGRIND found in path:" ${VALGRIND})
    target_link_libraries(messenger_binary_UT LINK_PUBLIC)
    add_custom_target(valgrind COMMAND "${VALGRIND}" --tool=memcheck  --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=no  $<TARGET_FILE:messenger_binary_UT>)
endif()

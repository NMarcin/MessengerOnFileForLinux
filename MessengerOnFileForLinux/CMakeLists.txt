cmake_minimum_required (VERSION 3.5.1)
project(MessengerOnFileForLinux)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(LIBRARY_OUTPUT_PATH build/)
set(BINARY_OUTPUT_PATH build/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(BUILD_SHARED_LIBS OFF)

include(External_GTest.cmake)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(${GTEST_INCLUDE_DIRS})
find_package(Curses REQUIRED)

if(${GTEST_ONLY})
    return()
endif()

################################################################################
#####                         MODULE DIR SOURCES                           #####
################################################################################
set(MODULE_UserService              ${CMAKE_SOURCE_DIR}/UserService/src)
set(MODULE_FileHandling             ${CMAKE_SOURCE_DIR}/FileHandling/src)
set(MODULE_LoggerFramework          ${CMAKE_SOURCE_DIR}/LoggerFramework/src)
set(MODULE_ChatControl              ${CMAKE_SOURCE_DIR}/ChatControl/src)
set(MODULE_ChatStarter              ${CMAKE_SOURCE_DIR}/ChatStarter/src)
set(MODULE_TerminalFunctionality    ${CMAKE_SOURCE_DIR}/TerminalFunctionality/src)
set(MODULE_Common                   ${CMAKE_SOURCE_DIR}/Common/src)
set(MODULE_DisplayChat              ${CMAKE_SOURCE_DIR}/DisplayChat/src)
set(MODULE_MessageFramework         ${CMAKE_SOURCE_DIR}/MessageFramework/src)

################################################################################
#####                       CREATE ENVIRONMENT CMAKE PART                  #####
################################################################################
set(clear_enviroment "/scripts/local_scripts/clear_enviroment.sh")
set(create_enviroment "/scripts/local_scripts/create_messenger_enviroment.sh")
execute_process(COMMAND sh ${CMAKE_SOURCE_DIR}${clear_enviroment})
execute_process(COMMAND sh ${CMAKE_SOURCE_DIR}${create_enviroment})

################################################################################
#####               CREATE DOXYGEN DOCUMENTATION CMAKE PART                #####
################################################################################
set(doxygen_config "/documentation/doxygenConfigurationFile.txt")
if(${SILENT_MOD_OFF})
    execute_process(COMMAND doxygen ${CMAKE_SOURCE_DIR}${doxygen_config})
else()
    execute_process(COMMAND doxygen ${CMAKE_SOURCE_DIR}${doxygen_config}  OUTPUT_QUIET)
endif()

################################################################################
#####                       MAKE BINARY CMAKE PART                         #####
################################################################################
# LIB_SRC
include_directories(${MODULE_UserService})
include_directories(${MODULE_FileHandling})
include_directories(${MODULE_LoggerFramework})
include_directories(${MODULE_ChatControl})
include_directories(${MODULE_ChatStarter})
include_directories(${MODULE_TerminalFunctionality})
include_directories(${MODULE_Common})
include_directories(${MODULE_DisplayChat})
include_directories(${MODULE_MessageFramework})
# SRC
add_subdirectory(main/src)
add_subdirectory(${MODULE_UserService})
add_subdirectory(${MODULE_FileHandling})
add_subdirectory(${MODULE_LoggerFramework})
add_subdirectory(${MODULE_ChatControl})
add_subdirectory(${MODULE_ChatStarter})
add_subdirectory(${MODULE_TerminalFunctionality})
add_subdirectory(${MODULE_Common})
add_subdirectory(${MODULE_DisplayChat})
add_subdirectory(${MODULE_MessageFramework})

################################################################################
#####                       MAKE UNIT TESTS CMAKE PART                     #####
################################################################################
# LIB_TEST
include_directories(${CMAKE_SOURCE_DIR}/ChatStarter/test)
include_directories(${CMAKE_SOURCE_DIR}/UserService/test)
include_directories(${CMAKE_SOURCE_DIR}/MessageFramework/test)
include_directories(${CMAKE_SOURCE_DIR}/TerminalFunctionality/test)
include_directories(${CMAKE_SOURCE_DIR}/DisplayChat/test)
# TEST
add_subdirectory(main/test)
add_subdirectory(FileHandling/test)
add_subdirectory(LoggerFramework/test)
add_subdirectory(ChatStarter/test)
add_subdirectory(UserService/test)
add_subdirectory(Common/test)
add_subdirectory(ChatControl/test)
add_subdirectory(MessageFramework/test)
add_subdirectory(TerminalFunctionality/test)


################################################################################
#####                  LINKING AND BUILD EXECUTALBE PART                   #####
################################################################################
add_library(source_objects_lib OBJECT ${SOURCES})

# messenger_binary
add_executable(messenger_binary $<TARGET_OBJECTS:source_objects_lib>
                                ${MAIN})
target_link_libraries (messenger_binary ${CMAKE_THREAD_LIBS_INIT}
                                        ${CURSES_LIBRARIES})

# messenger_binary_UT
set(TEST_BINARY_FILES $<TARGET_OBJECTS:source_objects_lib>
                      ${TEST_FILES}
                      ${MAIN_TEST})
add_executable(messenger_binary_UT ${TEST_BINARY_FILES})
target_link_libraries(messenger_binary_UT ${CURSES_LIBRARIES}
                                          ${GTEST_MAIN_LIBRARY}
                                          ${GTEST_LIBRARY}
                                          ${GMOCK_MAIN_LIBRARY}
                                          ${GMOCK_LIBRARY})

################################################################################
#####                      SET COMPILATION ORDER                           #####
##### 1.source_objects_lib                                                 #####
##### 2.messenger_binary                                                   #####
##### 3.googletest                                                         #####
##### 4.messenger_binary_UT                                                #####
################################################################################
add_dependencies(messenger_binary_UT messenger_binary)
add_dependencies(googletest messenger_binary)

################################################################################
#####                              VALGRIND                                #####
################################################################################
find_program(VALGRIND "valgrind")
if(VALGRIND)
    message("VALGRIND found in path:" ${VALGRIND})
    target_link_libraries(messenger_binary_UT LINK_PUBLIC)
    add_custom_target(valgrind COMMAND "${VALGRIND}" --tool=memcheck  --leak-check=yes
        --show-reachable=yes --num-callers=20
        --track-fds=no --log-file="valgrindOutput.txt"
        $<TARGET_FILE:messenger_binary_UT>)
endif()

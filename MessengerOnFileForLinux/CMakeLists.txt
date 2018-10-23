cmake_minimum_required (VERSION 3.5.1)
project(CMakeBuildTree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(LIBRARY_OUTPUT_PATH build/)
set(BINARY_OUTPUT_PATH build/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set (CMAKE_EXE_LINKER_FLAGS "-lncurses")
add_definitions( "-lncurses" )

# OUTSIDE LIBRARIES
include(CTest)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(${GTEST_INCLUDE_DIRS})
find_package(GTest REQUIRED)
find_package (Threads REQUIRED)
find_package(Curses REQUIRED)


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
set(clear_enviroment "/scripts/clear_enviroment.sh")
set(create_enviroment "/scripts/create_enviroment.sh")
execute_process(COMMAND sh ${CMAKE_SOURCE_DIR}${clear_enviroment})
execute_process(COMMAND sh ${CMAKE_SOURCE_DIR}${create_enviroment})

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
# CMAKE BUILD
add_executable(messenger_binary ${SOURCES} ${MAIN})
target_link_libraries (messenger_binary ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(messenger_binary ${CURSES_LIBRARIES})

################################################################################
#####                       MAKE UNIT TESTS CMAKE PART                     #####
################################################################################
#LIB_TEST
include_directories(${CMAKE_SOURCE_DIR}/ChatStarter/test)
include_directories(${CMAKE_SOURCE_DIR}/UserService/test)
# TEST
add_subdirectory(main/test)
add_subdirectory(FileHandling/test)
add_subdirectory(LoggerFramework/test)
add_subdirectory(ChatStarter/test)
add_subdirectory(UserService/test)


# CMAKE BUILD
set(TEST_BINARY_FILES ${TEST_SOURCES} ${TEST_FILES} ${MAIN_TEST})
add_executable(messenger_binary_UT ${TEST_BINARY_FILES})
target_link_libraries(messenger_binary_UT ${GTEST_LIBRARIES} pthread)
target_link_libraries(messenger_binary_UT ${CURSES_LIBRARIES})



################################################################################
#####                               VALGIRN                                #####
################################################################################
find_program(VALGRIND "valgrind")
if(VALGRIND)
    message("VALGRIND found in path:" ${VALGRIND})
    target_link_libraries(messenger_binary_UT LINK_PUBLIC)
    add_custom_target(valgrind COMMAND "${VALGRIND}" --tool=memcheck  --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=no  $<TARGET_FILE:messenger_binary_UT>)
endif()

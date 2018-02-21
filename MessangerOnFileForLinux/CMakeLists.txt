project(MessangerOnFileForLinux)

cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include (CTest)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(GTest REQUIRED)
add_executable(lol main.cpp)
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests test.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

add_custom_target(run
	$<TARGET_FILE:lol>
)
add_custom_target(ut
	$<TARGET_FILE:runTests>
)

find_program(VALGRIND "valgrind")
if(VALGRIND)
	target_link_libraries(lol LINK_PUBLIC)
	add_custom_target(valgrind
        COMMAND "${VALGRIND}" --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes $<TARGET_FILE:lol>)
endif()

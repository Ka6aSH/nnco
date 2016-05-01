cmake_minimum_required(VERSION 3.2)
project(unit_tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(lib/googletest)
add_subdirectory(structure_tests)
add_subdirectory(algorithms_tests)
add_subdirectory(util_tests)

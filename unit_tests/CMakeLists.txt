cmake_minimum_required(VERSION 3.3)
project(unit_tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(lib/googletest)
add_subdirectory(algorithms_tests)
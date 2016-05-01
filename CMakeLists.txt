cmake_minimum_required(VERSION 3.2)
project(nnco)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(nnco ${SOURCE_FILES})

include_directories(structures algorithms io_util)

add_subdirectory(structures)
add_subdirectory(algorithms)
add_subdirectory(io_util)
add_subdirectory(unit_tests)

target_link_libraries(nnco algorithms io_util)

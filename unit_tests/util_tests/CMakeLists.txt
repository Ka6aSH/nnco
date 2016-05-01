cmake_minimum_required(VERSION 3.2)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(runUtilTests
        io_util_tests.cpp)

target_link_libraries(runUtilTests gtest gtest_main)
target_link_libraries(runUtilTests io_util)

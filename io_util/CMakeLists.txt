cmake_minimum_required(VERSION 3.2)
project(io_util)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(HEADER_FILES
        io_operations.h)

set(SOURCE_FILES
        io_operations.cpp)

add_library(io_util STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(io_util structures)

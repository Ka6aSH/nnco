cmake_minimum_required(VERSION 3.3)
project (algorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(HEADER_FILES
        point.h)

set(SOURCE_FILES
        point.cpp)

add_library(algorithms STATIC ${SOURCE_FILES} ${HEADER_FILES})
cmake_minimum_required(VERSION 3.2)
project(structures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(HEADER_FILES
        point.h
        metrics.h)

set(SOURCE_FILES
        point.cpp
        metrics.cpp)

add_library(structures STATIC ${SOURCE_FILES} ${HEADER_FILES})
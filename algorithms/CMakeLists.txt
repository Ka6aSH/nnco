cmake_minimum_required(VERSION 3.3)
project (algorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(HEADER_FILES
        point.h
        ialgorithm.h
        kd_tree.h
        kd_node.h)

set(SOURCE_FILES
        point.cpp
        kd_tree.cpp
        kd_node.cpp)

add_library(algorithms STATIC ${SOURCE_FILES} ${HEADER_FILES})
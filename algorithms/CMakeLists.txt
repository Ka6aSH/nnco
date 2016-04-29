cmake_minimum_required(VERSION 3.3)
project(algorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(HEADER_FILES
        point.h
        metrics.h
        ialgorithm.h
        kd_node.h kd_tree.h kd_algorithm.h
        vp_node.h vp_tree.h vp_algorithm.h
        bbf_node.h bbf_algorithm.h
        lsh_hash_function.h lsh_bucket.h lsh_algorithm.h
        linear_algorithm.h
        cluster.h aggl_clustering.h cluster_quality.h)

set(SOURCE_FILES
        point.cpp
        metrics.cpp
        kd_node.cpp kd_tree.cpp kd_algorithm.cpp
        vp_node.cpp vp_tree.cpp vp_algorithm.cpp
        bbf_node.cpp bbf_algorithm.cpp
        lsh_hash_function.cpp lsh_bucket.cpp lsh_algorithm.cpp
        linear_algorithm.cpp
        cluster.cpp aggl_clustering.cpp cluster_quality.cpp)

add_library(algorithms STATIC ${SOURCE_FILES} ${HEADER_FILES})
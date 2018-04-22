cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(public/src)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_INCLUDE_PATH "~/eigen")  # Eigen library

find_package(Eigen3 REQUIRED)  # Eigen 3
find_package(NLopt REQUIRED)  # NLopt
include_directories(${EIGEN3_INCLUDE_DIR})

include_directories(${NLopt_INCLUDE_DIRS})
#include_directories(${CMAKE_SOURSE_DIR}/utility)


# Subdirectories

add_subdirectory(assemble)
add_subdirectory(GUI)

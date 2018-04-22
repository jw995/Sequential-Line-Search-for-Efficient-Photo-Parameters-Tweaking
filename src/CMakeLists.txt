cmake_minimum_required(VERSION 3.0.0)

#project(24783)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(public/src)  # Libraries of Soji
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_INCLUDE_PATH "~/eigen")  # Eigen library

find_package(Eigen3 REQUIRED)  # Eigen 3
find_package(NLopt REQUIRED)  # NLopt
include_directories(${EIGEN3_INCLUDE_DIR})

include_directories(${NLopt_INCLUDE_DIRS})

set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.10.1")  # Qt5
find_package(Qt5 COMPONENTS Widgets)

# Subdirectories
add_subdirectory(utility)
add_subdirectory(GUI)
add_subdirectory(yhh)  # Yen-Hsiang's play ground
add_subdirectory(assemble)	# Han-Yu assemble place
add_subdirectory(hanyu)     # Han-Yu math playground

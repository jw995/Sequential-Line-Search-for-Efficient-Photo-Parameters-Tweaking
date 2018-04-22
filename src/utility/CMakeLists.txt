cmake_minimum_required(VERSION 3.1)

find_package(Eigen3 REQUIRED)
find_package(NLopt REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${NLopt_INCLUDE_DIRS})

file(GLOB files *.cpp *.h)
add_library(utility STATIC ${files})
target_include_directories(utility PUBLIC .)
target_link_libraries(utility ${NLopt_LIBRARIES})

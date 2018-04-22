cmake_minimum_required(VERSION 3.0.0)

find_package(Eigen3 REQUIRED)  # Eigen 3
find_package(NLopt REQUIRED)  # NLopt
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${NLopt_INCLUDE_DIRS})
#include_directories(${CMAKE_SOURSE_DIR}/utility)

file(GLOB files *.cpp *.h)
add_executable(yhh MACOSX_BUNDLE ${files})
#add_executable(yhh MACOSX_BUNDLE main.cpp)
target_link_libraries(yhh ${NLopt_LIBRARIES})
target_link_libraries(yhh fslazywindow)
#target_link_libraries(yhh utility)
#target_link_libraries(yhh custom)

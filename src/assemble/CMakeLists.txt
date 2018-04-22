add_executable(framework MACOSX_BUNDLE framework.cpp)

add_executable(assemble MACOSX_BUNDLE main.cpp)
target_link_libraries(assemble custom)

find_package(Eigen3 REQUIRED)  # Eigen 3
find_package(NLopt REQUIRED)  # NLopt
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${NLopt_INCLUDE_DIRS})

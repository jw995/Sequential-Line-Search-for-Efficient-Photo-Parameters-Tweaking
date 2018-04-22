add_executable(alpha_version MACOSX_BUNDLE main.cpp)
target_link_libraries(alpha_version custom)

find_package(Eigen3 REQUIRED)  # Eigen 3
find_package(NLopt REQUIRED)  # NLopt
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${NLopt_INCLUDE_DIRS})

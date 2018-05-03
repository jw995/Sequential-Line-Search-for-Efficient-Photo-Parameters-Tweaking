find_package(Eigen3 REQUIRED)  # Eigen 3
find_package(NLopt REQUIRED)  # NLopt
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${NLopt_INCLUDE_DIRS})


file(GLOB files *.cpp *.h)
add_executable(beta_version MACOSX_BUNDLE ${files})
target_link_libraries(beta_version custom)
target_link_libraries(beta_version ${NLopt_LIBRARIES})
target_link_libraries(beta_version fslazywindow)
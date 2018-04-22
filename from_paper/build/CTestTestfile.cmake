# CMake generated Testfile for 
# Source directory: /Users/yhh/Documents/CMU/Spring18/24783/src/SimpleLazyTeam/from_paper/sequential-line-search
# Build directory: /Users/yhh/Documents/CMU/Spring18/24783/src/SimpleLazyTeam/from_paper/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(bayesian_optimization_1d_test "/Users/yhh/Documents/CMU/Spring18/24783/src/SimpleLazyTeam/from_paper/build/bayesian_optimization_1d/BayesianOptimization1d")
add_test(sequential_line_search_test "/Users/yhh/Documents/CMU/Spring18/24783/src/SimpleLazyTeam/from_paper/build/sequential_line_search/SequentialLineSearch")
subdirs("sequential_line_search_core")
subdirs("bayesian_optimization_1d")
subdirs("sequential_line_search")
subdirs("bayesian_optimization_1d_gui")
subdirs("bayesian_optimization_2d_gui")
subdirs("sequential_line_search_2d_gui")

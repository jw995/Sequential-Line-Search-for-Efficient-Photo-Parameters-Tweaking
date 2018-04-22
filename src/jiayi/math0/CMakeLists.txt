
add_library(math0 
math0.h math0.cpp)

target_include_directories(math0 PUBLIC .)

target_link_libraries(math0 eigen)

add_executable(GUI MACOSX_BUNDLE main.cpp)
add_library(custom guislidebar.cpp guislidebar.h guitoolbar.cpp guitoolbar.h filter.cpp filter.h)
target_link_libraries(custom fslazywindow)
target_link_libraries(custom fsguilib)
target_link_libraries(custom fssimplefiledialog)
target_include_directories(custom PUBLIC .)
#target_link_libraries(GUI fslazywindow)


target_link_libraries(GUI custom)
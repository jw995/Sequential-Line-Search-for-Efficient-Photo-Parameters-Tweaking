# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build

# Include any dependencies generated for this target.
include public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/depend.make

# Include the progress variables for this target.
include public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/progress.make

# Include the compile flags for this target's objects.
include public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/flags.make

public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.o: public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/flags.make
public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.o: /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysbitmap/cmdtools/ysmakewhitetransparent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.o"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysbitmap/cmdtools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.o -c /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysbitmap/cmdtools/ysmakewhitetransparent.cpp

public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.i"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysbitmap/cmdtools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysbitmap/cmdtools/ysmakewhitetransparent.cpp > CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.i

public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.s"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysbitmap/cmdtools && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysbitmap/cmdtools/ysmakewhitetransparent.cpp -o CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.s

public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.o.requires:

.PHONY : public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.o.requires

public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.o.provides: public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.o.requires
	$(MAKE) -f public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/build.make public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.o.provides.build
.PHONY : public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.o.provides

public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.o.provides.build: public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.o


# Object files for target ysmakewhitetransparent
ysmakewhitetransparent_OBJECTS = \
"CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.o"

# External object files for target ysmakewhitetransparent
ysmakewhitetransparent_EXTERNAL_OBJECTS =

public/src/ysbitmap/cmdtools/ysmakewhitetransparent: public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.o
public/src/ysbitmap/cmdtools/ysmakewhitetransparent: public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/build.make
public/src/ysbitmap/cmdtools/ysmakewhitetransparent: public/src/ysclass/src/libysclass.a
public/src/ysbitmap/cmdtools/ysmakewhitetransparent: public/src/ysbitmap/src/libysbitmap.a
public/src/ysbitmap/cmdtools/ysmakewhitetransparent: public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ysmakewhitetransparent"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysbitmap/cmdtools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ysmakewhitetransparent.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/build: public/src/ysbitmap/cmdtools/ysmakewhitetransparent

.PHONY : public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/build

public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/requires: public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/ysmakewhitetransparent.cpp.o.requires

.PHONY : public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/requires

public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/clean:
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysbitmap/cmdtools && $(CMAKE_COMMAND) -P CMakeFiles/ysmakewhitetransparent.dir/cmake_clean.cmake
.PHONY : public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/clean

public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/depend:
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysbitmap/cmdtools /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysbitmap/cmdtools /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : public/src/ysbitmap/cmdtools/CMakeFiles/ysmakewhitetransparent.dir/depend


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
include public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/depend.make

# Include the progress variables for this target.
include public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/progress.make

# Include the compile flags for this target's objects.
include public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/flags.make

public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.o: public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/flags.make
public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.o: /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/fssimplewindow/samples/sample06-15puzzle/sample06-15puzzle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.o"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/fssimplewindow/samples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.o -c /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/fssimplewindow/samples/sample06-15puzzle/sample06-15puzzle.cpp

public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.i"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/fssimplewindow/samples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/fssimplewindow/samples/sample06-15puzzle/sample06-15puzzle.cpp > CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.i

public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.s"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/fssimplewindow/samples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/fssimplewindow/samples/sample06-15puzzle/sample06-15puzzle.cpp -o CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.s

public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.o.requires:

.PHONY : public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.o.requires

public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.o.provides: public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.o.requires
	$(MAKE) -f public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/build.make public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.o.provides.build
.PHONY : public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.o.provides

public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.o.provides.build: public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.o


# Object files for target sample06-15puzzle
sample06__15puzzle_OBJECTS = \
"CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.o"

# External object files for target sample06-15puzzle
sample06__15puzzle_EXTERNAL_OBJECTS =

public/src/fssimplewindow/samples/sample06-15puzzle.app/Contents/MacOS/sample06-15puzzle: public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.o
public/src/fssimplewindow/samples/sample06-15puzzle.app/Contents/MacOS/sample06-15puzzle: public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/build.make
public/src/fssimplewindow/samples/sample06-15puzzle.app/Contents/MacOS/sample06-15puzzle: public/src/fssimplewindow/src/libfssimplewindow.a
public/src/fssimplewindow/samples/sample06-15puzzle.app/Contents/MacOS/sample06-15puzzle: public/src/ysbitmapfont/src/libysbitmapfont.a
public/src/fssimplewindow/samples/sample06-15puzzle.app/Contents/MacOS/sample06-15puzzle: public/src/ysgl/src/libysgl.a
public/src/fssimplewindow/samples/sample06-15puzzle.app/Contents/MacOS/sample06-15puzzle: public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sample06-15puzzle.app/Contents/MacOS/sample06-15puzzle"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/fssimplewindow/samples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sample06-15puzzle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/build: public/src/fssimplewindow/samples/sample06-15puzzle.app/Contents/MacOS/sample06-15puzzle

.PHONY : public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/build

public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/requires: public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/sample06-15puzzle/sample06-15puzzle.cpp.o.requires

.PHONY : public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/requires

public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/clean:
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/fssimplewindow/samples && $(CMAKE_COMMAND) -P CMakeFiles/sample06-15puzzle.dir/cmake_clean.cmake
.PHONY : public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/clean

public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/depend:
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/fssimplewindow/samples /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/fssimplewindow/samples /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : public/src/fssimplewindow/samples/CMakeFiles/sample06-15puzzle.dir/depend


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
include public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/depend.make

# Include the progress variables for this target.
include public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/progress.make

# Include the compile flags for this target's objects.
include public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/flags.make

public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.o: public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/flags.make
public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.o: /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysgl/src/glsl_src/makeh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.o"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgl/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.o -c /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysgl/src/glsl_src/makeh.cpp

public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.i"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgl/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysgl/src/glsl_src/makeh.cpp > CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.i

public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.s"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgl/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysgl/src/glsl_src/makeh.cpp -o CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.s

public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.o.requires:

.PHONY : public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.o.requires

public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.o.provides: public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.o.requires
	$(MAKE) -f public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/build.make public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.o.provides.build
.PHONY : public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.o.provides

public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.o.provides.build: public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.o


# Object files for target ysgl_makeh
ysgl_makeh_OBJECTS = \
"CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.o"

# External object files for target ysgl_makeh
ysgl_makeh_EXTERNAL_OBJECTS =

exe/ysgl_makeh: public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.o
exe/ysgl_makeh: public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/build.make
exe/ysgl_makeh: public/src/ysclass/src/libysclass.a
exe/ysgl_makeh: public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../../exe/ysgl_makeh"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgl/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ysgl_makeh.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/build: exe/ysgl_makeh

.PHONY : public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/build

public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/requires: public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/glsl_src/makeh.cpp.o.requires

.PHONY : public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/requires

public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/clean:
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgl/src && $(CMAKE_COMMAND) -P CMakeFiles/ysgl_makeh.dir/cmake_clean.cmake
.PHONY : public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/clean

public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/depend:
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysgl/src /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgl/src /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : public/src/ysgl/src/CMakeFiles/ysgl_makeh.dir/depend


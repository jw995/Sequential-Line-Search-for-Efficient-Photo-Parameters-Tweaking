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
include public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/depend.make

# Include the progress variables for this target.
include public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/progress.make

# Include the compile flags for this target's objects.
include public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/flags.make

public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o: public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/flags.make
public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o: /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysgl/src/glsl_src/makec.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgl/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o -c /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysgl/src/glsl_src/makec.cpp

public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.i"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgl/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysgl/src/glsl_src/makec.cpp > CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.i

public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.s"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgl/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysgl/src/glsl_src/makec.cpp -o CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.s

public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o.requires:

.PHONY : public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o.requires

public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o.provides: public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o.requires
	$(MAKE) -f public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/build.make public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o.provides.build
.PHONY : public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o.provides

public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o.provides.build: public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o


# Object files for target ysgl_makec
ysgl_makec_OBJECTS = \
"CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o"

# External object files for target ysgl_makec
ysgl_makec_EXTERNAL_OBJECTS =

exe/ysgl_makec: public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o
exe/ysgl_makec: public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/build.make
exe/ysgl_makec: public/src/ysclass/src/libysclass.a
exe/ysgl_makec: public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../../exe/ysgl_makec"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgl/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ysgl_makec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/build: exe/ysgl_makec

.PHONY : public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/build

public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/requires: public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/glsl_src/makec.cpp.o.requires

.PHONY : public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/requires

public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/clean:
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgl/src && $(CMAKE_COMMAND) -P CMakeFiles/ysgl_makec.dir/cmake_clean.cmake
.PHONY : public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/clean

public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/depend:
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysgl/src /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgl/src /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : public/src/ysgl/src/CMakeFiles/ysgl_makec.dir/depend


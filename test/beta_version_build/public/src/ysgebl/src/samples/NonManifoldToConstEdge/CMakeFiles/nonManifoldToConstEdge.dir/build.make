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
include public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/depend.make

# Include the progress variables for this target.
include public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/progress.make

# Include the compile flags for this target's objects.
include public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/flags.make

public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.o: public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/flags.make
public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.o: /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysgebl/src/samples/NonManifoldToConstEdge/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.o"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgebl/src/samples/NonManifoldToConstEdge && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.o -c /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysgebl/src/samples/NonManifoldToConstEdge/main.cpp

public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.i"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgebl/src/samples/NonManifoldToConstEdge && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysgebl/src/samples/NonManifoldToConstEdge/main.cpp > CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.i

public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.s"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgebl/src/samples/NonManifoldToConstEdge && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysgebl/src/samples/NonManifoldToConstEdge/main.cpp -o CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.s

public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.o.requires:

.PHONY : public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.o.requires

public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.o.provides: public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.o.requires
	$(MAKE) -f public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/build.make public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.o.provides.build
.PHONY : public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.o.provides

public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.o.provides.build: public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.o


# Object files for target nonManifoldToConstEdge
nonManifoldToConstEdge_OBJECTS = \
"CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.o"

# External object files for target nonManifoldToConstEdge
nonManifoldToConstEdge_EXTERNAL_OBJECTS =

public/src/ysgebl/src/samples/NonManifoldToConstEdge/nonManifoldToConstEdge: public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.o
public/src/ysgebl/src/samples/NonManifoldToConstEdge/nonManifoldToConstEdge: public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/build.make
public/src/ysgebl/src/samples/NonManifoldToConstEdge/nonManifoldToConstEdge: public/src/ysgebl/src/kernelutil/libgeblutil.a
public/src/ysgebl/src/samples/NonManifoldToConstEdge/nonManifoldToConstEdge: public/src/ysgebl/src/kernel/libgeblkernel.a
public/src/ysgebl/src/samples/NonManifoldToConstEdge/nonManifoldToConstEdge: public/src/ysport/src/libysport.a
public/src/ysgebl/src/samples/NonManifoldToConstEdge/nonManifoldToConstEdge: public/src/ysglcpp/src/libysglcpp.a
public/src/ysgebl/src/samples/NonManifoldToConstEdge/nonManifoldToConstEdge: public/src/ysclass11/src/libysclass11.a
public/src/ysgebl/src/samples/NonManifoldToConstEdge/nonManifoldToConstEdge: public/src/ysclass/src/libysclass.a
public/src/ysgebl/src/samples/NonManifoldToConstEdge/nonManifoldToConstEdge: public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable nonManifoldToConstEdge"
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgebl/src/samples/NonManifoldToConstEdge && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nonManifoldToConstEdge.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/build: public/src/ysgebl/src/samples/NonManifoldToConstEdge/nonManifoldToConstEdge

.PHONY : public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/build

public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/requires: public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/main.cpp.o.requires

.PHONY : public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/requires

public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/clean:
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgebl/src/samples/NonManifoldToConstEdge && $(CMAKE_COMMAND) -P CMakeFiles/nonManifoldToConstEdge.dir/cmake_clean.cmake
.PHONY : public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/clean

public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/depend:
	cd /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/src/public/src/ysgebl/src/samples/NonManifoldToConstEdge /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgebl/src/samples/NonManifoldToConstEdge /Users/hanyulee/24783/src/SimpleLazyTeam/beta_version/beta_version_build/public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : public/src/ysgebl/src/samples/NonManifoldToConstEdge/CMakeFiles/nonManifoldToConstEdge.dir/depend


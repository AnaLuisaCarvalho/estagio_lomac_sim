# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_COMMAND = /cvmfs/sw.el7/cmake/3.11.2/bin/cmake

# The command to remove a file.
RM = /cvmfs/sw.el7/cmake/3.11.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/t3atlas/aluisa/Geant4/TileFCC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/t3atlas/aluisa/Geant4/TileFCC/build

# Include any dependencies generated for this target.
include CMakeFiles/TileFCCTile.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TileFCCTile.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TileFCCTile.dir/flags.make

CMakeFiles/TileFCCTile.dir/src/TileFCCTile.cc.o: CMakeFiles/TileFCCTile.dir/flags.make
CMakeFiles/TileFCCTile.dir/src/TileFCCTile.cc.o: ../src/TileFCCTile.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/t3atlas/aluisa/Geant4/TileFCC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TileFCCTile.dir/src/TileFCCTile.cc.o"
	/cvmfs/sw.el7/gcc/6.3/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TileFCCTile.dir/src/TileFCCTile.cc.o -c /home/t3atlas/aluisa/Geant4/TileFCC/src/TileFCCTile.cc

CMakeFiles/TileFCCTile.dir/src/TileFCCTile.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TileFCCTile.dir/src/TileFCCTile.cc.i"
	/cvmfs/sw.el7/gcc/6.3/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/t3atlas/aluisa/Geant4/TileFCC/src/TileFCCTile.cc > CMakeFiles/TileFCCTile.dir/src/TileFCCTile.cc.i

CMakeFiles/TileFCCTile.dir/src/TileFCCTile.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TileFCCTile.dir/src/TileFCCTile.cc.s"
	/cvmfs/sw.el7/gcc/6.3/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/t3atlas/aluisa/Geant4/TileFCC/src/TileFCCTile.cc -o CMakeFiles/TileFCCTile.dir/src/TileFCCTile.cc.s

# Object files for target TileFCCTile
TileFCCTile_OBJECTS = \
"CMakeFiles/TileFCCTile.dir/src/TileFCCTile.cc.o"

# External object files for target TileFCCTile
TileFCCTile_EXTERNAL_OBJECTS =

libTileFCCTile.so: CMakeFiles/TileFCCTile.dir/src/TileFCCTile.cc.o
libTileFCCTile.so: CMakeFiles/TileFCCTile.dir/build.make
libTileFCCTile.so: CMakeFiles/TileFCCTile.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/t3atlas/aluisa/Geant4/TileFCC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libTileFCCTile.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TileFCCTile.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TileFCCTile.dir/build: libTileFCCTile.so

.PHONY : CMakeFiles/TileFCCTile.dir/build

CMakeFiles/TileFCCTile.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TileFCCTile.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TileFCCTile.dir/clean

CMakeFiles/TileFCCTile.dir/depend:
	cd /home/t3atlas/aluisa/Geant4/TileFCC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/t3atlas/aluisa/Geant4/TileFCC /home/t3atlas/aluisa/Geant4/TileFCC /home/t3atlas/aluisa/Geant4/TileFCC/build /home/t3atlas/aluisa/Geant4/TileFCC/build /home/t3atlas/aluisa/Geant4/TileFCC/build/CMakeFiles/TileFCCTile.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TileFCCTile.dir/depend

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


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/t3atlas/aluisa/Geant4/TileFCC/CMakeFiles/CMakeTmp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/t3atlas/aluisa/Geant4/TileFCC/CMakeFiles/CMakeTmp

# Include any dependencies generated for this target.
include CMakeFiles/cmTC_08618.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cmTC_08618.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmTC_08618.dir/flags.make

CMakeFiles/cmTC_08618.dir/feature_tests.c.o: CMakeFiles/cmTC_08618.dir/flags.make
CMakeFiles/cmTC_08618.dir/feature_tests.c.o: /home/t3atlas/aluisa/Geant4/TileFCC/CMakeFiles/feature_tests.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/t3atlas/aluisa/Geant4/TileFCC/CMakeFiles/CMakeTmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cmTC_08618.dir/feature_tests.c.o"
	/cvmfs/sw.el7/gcc/6.3/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cmTC_08618.dir/feature_tests.c.o   -c /home/t3atlas/aluisa/Geant4/TileFCC/CMakeFiles/feature_tests.c

CMakeFiles/cmTC_08618.dir/feature_tests.c.i: cmake_force
	@echo "Preprocessing C source to CMakeFiles/cmTC_08618.dir/feature_tests.c.i"
	/cvmfs/sw.el7/gcc/6.3/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/t3atlas/aluisa/Geant4/TileFCC/CMakeFiles/feature_tests.c > CMakeFiles/cmTC_08618.dir/feature_tests.c.i

CMakeFiles/cmTC_08618.dir/feature_tests.c.s: cmake_force
	@echo "Compiling C source to assembly CMakeFiles/cmTC_08618.dir/feature_tests.c.s"
	/cvmfs/sw.el7/gcc/6.3/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/t3atlas/aluisa/Geant4/TileFCC/CMakeFiles/feature_tests.c -o CMakeFiles/cmTC_08618.dir/feature_tests.c.s

# Object files for target cmTC_08618
cmTC_08618_OBJECTS = \
"CMakeFiles/cmTC_08618.dir/feature_tests.c.o"

# External object files for target cmTC_08618
cmTC_08618_EXTERNAL_OBJECTS =

cmTC_08618: CMakeFiles/cmTC_08618.dir/feature_tests.c.o
cmTC_08618: CMakeFiles/cmTC_08618.dir/build.make
cmTC_08618: CMakeFiles/cmTC_08618.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --progress-dir=/home/t3atlas/aluisa/Geant4/TileFCC/CMakeFiles/CMakeTmp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cmTC_08618"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmTC_08618.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmTC_08618.dir/build: cmTC_08618

.PHONY : CMakeFiles/cmTC_08618.dir/build

CMakeFiles/cmTC_08618.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cmTC_08618.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cmTC_08618.dir/clean

CMakeFiles/cmTC_08618.dir/depend:
	cd /home/t3atlas/aluisa/Geant4/TileFCC/CMakeFiles/CMakeTmp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/t3atlas/aluisa/Geant4/TileFCC/CMakeFiles/CMakeTmp /home/t3atlas/aluisa/Geant4/TileFCC/CMakeFiles/CMakeTmp /home/t3atlas/aluisa/Geant4/TileFCC/CMakeFiles/CMakeTmp /home/t3atlas/aluisa/Geant4/TileFCC/CMakeFiles/CMakeTmp /home/t3atlas/aluisa/Geant4/TileFCC/CMakeFiles/CMakeTmp/CMakeFiles/cmTC_08618.dir/DependInfo.cmake
.PHONY : CMakeFiles/cmTC_08618.dir/depend

# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/code/gameproject1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/code/gameproject1

# Include any dependencies generated for this target.
include CMakeFiles/gameproject1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gameproject1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gameproject1.dir/flags.make

CMakeFiles/gameproject1.dir/src/main.cpp.o: CMakeFiles/gameproject1.dir/flags.make
CMakeFiles/gameproject1.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/code/gameproject1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gameproject1.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameproject1.dir/src/main.cpp.o -c /home/pi/code/gameproject1/src/main.cpp

CMakeFiles/gameproject1.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameproject1.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/code/gameproject1/src/main.cpp > CMakeFiles/gameproject1.dir/src/main.cpp.i

CMakeFiles/gameproject1.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameproject1.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/code/gameproject1/src/main.cpp -o CMakeFiles/gameproject1.dir/src/main.cpp.s

# Object files for target gameproject1
gameproject1_OBJECTS = \
"CMakeFiles/gameproject1.dir/src/main.cpp.o"

# External object files for target gameproject1
gameproject1_EXTERNAL_OBJECTS =

gameproject1: CMakeFiles/gameproject1.dir/src/main.cpp.o
gameproject1: CMakeFiles/gameproject1.dir/build.make
gameproject1: CMakeFiles/gameproject1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/code/gameproject1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gameproject1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gameproject1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gameproject1.dir/build: gameproject1

.PHONY : CMakeFiles/gameproject1.dir/build

CMakeFiles/gameproject1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gameproject1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gameproject1.dir/clean

CMakeFiles/gameproject1.dir/depend:
	cd /home/pi/code/gameproject1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/code/gameproject1 /home/pi/code/gameproject1 /home/pi/code/gameproject1 /home/pi/code/gameproject1 /home/pi/code/gameproject1/CMakeFiles/gameproject1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gameproject1.dir/depend

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
CMAKE_COMMAND = /home/egor/Documents/clion-2018.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/egor/Documents/clion-2018.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/egor/Documents/acos/task_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/egor/Documents/acos/task_1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/task_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/task_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/task_1.dir/flags.make

CMakeFiles/task_1.dir/main.c.o: CMakeFiles/task_1.dir/flags.make
CMakeFiles/task_1.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egor/Documents/acos/task_1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/task_1.dir/main.c.o"
	/usr/bin/clang-6.0 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/task_1.dir/main.c.o   -c /home/egor/Documents/acos/task_1/main.c

CMakeFiles/task_1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/task_1.dir/main.c.i"
	/usr/bin/clang-6.0 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/egor/Documents/acos/task_1/main.c > CMakeFiles/task_1.dir/main.c.i

CMakeFiles/task_1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/task_1.dir/main.c.s"
	/usr/bin/clang-6.0 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/egor/Documents/acos/task_1/main.c -o CMakeFiles/task_1.dir/main.c.s

# Object files for target task_1
task_1_OBJECTS = \
"CMakeFiles/task_1.dir/main.c.o"

# External object files for target task_1
task_1_EXTERNAL_OBJECTS =

task_1: CMakeFiles/task_1.dir/main.c.o
task_1: CMakeFiles/task_1.dir/build.make
task_1: CMakeFiles/task_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/egor/Documents/acos/task_1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable task_1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/task_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/task_1.dir/build: task_1

.PHONY : CMakeFiles/task_1.dir/build

CMakeFiles/task_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/task_1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/task_1.dir/clean

CMakeFiles/task_1.dir/depend:
	cd /home/egor/Documents/acos/task_1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/egor/Documents/acos/task_1 /home/egor/Documents/acos/task_1 /home/egor/Documents/acos/task_1/cmake-build-debug /home/egor/Documents/acos/task_1/cmake-build-debug /home/egor/Documents/acos/task_1/cmake-build-debug/CMakeFiles/task_1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/task_1.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kali/x-tetris

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kali/x-tetris/build

# Include any dependencies generated for this target.
include CMakeFiles/x_tetris.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/x_tetris.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/x_tetris.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/x_tetris.dir/flags.make

CMakeFiles/x_tetris.dir/main.c.o: CMakeFiles/x_tetris.dir/flags.make
CMakeFiles/x_tetris.dir/main.c.o: ../main.c
CMakeFiles/x_tetris.dir/main.c.o: CMakeFiles/x_tetris.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kali/x-tetris/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/x_tetris.dir/main.c.o"
	/bin/clang-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/x_tetris.dir/main.c.o -MF CMakeFiles/x_tetris.dir/main.c.o.d -o CMakeFiles/x_tetris.dir/main.c.o -c /home/kali/x-tetris/main.c

CMakeFiles/x_tetris.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/x_tetris.dir/main.c.i"
	/bin/clang-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kali/x-tetris/main.c > CMakeFiles/x_tetris.dir/main.c.i

CMakeFiles/x_tetris.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/x_tetris.dir/main.c.s"
	/bin/clang-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kali/x-tetris/main.c -o CMakeFiles/x_tetris.dir/main.c.s

# Object files for target x_tetris
x_tetris_OBJECTS = \
"CMakeFiles/x_tetris.dir/main.c.o"

# External object files for target x_tetris
x_tetris_EXTERNAL_OBJECTS =

x_tetris: CMakeFiles/x_tetris.dir/main.c.o
x_tetris: CMakeFiles/x_tetris.dir/build.make
x_tetris: /usr/lib/x86_64-linux-gnu/libcurses.so
x_tetris: /usr/lib/x86_64-linux-gnu/libform.so
x_tetris: CMakeFiles/x_tetris.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kali/x-tetris/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable x_tetris"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/x_tetris.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/x_tetris.dir/build: x_tetris
.PHONY : CMakeFiles/x_tetris.dir/build

CMakeFiles/x_tetris.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/x_tetris.dir/cmake_clean.cmake
.PHONY : CMakeFiles/x_tetris.dir/clean

CMakeFiles/x_tetris.dir/depend:
	cd /home/kali/x-tetris/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kali/x-tetris /home/kali/x-tetris /home/kali/x-tetris/build /home/kali/x-tetris/build /home/kali/x-tetris/build/CMakeFiles/x_tetris.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/x_tetris.dir/depend


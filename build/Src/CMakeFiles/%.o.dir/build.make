# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/DnyaneshG/MyProjects/Generix

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/DnyaneshG/MyProjects/Generix/build

# Utility rule file for %.o.

# Include the progress variables for this target.
include Src/CMakeFiles/%.o.dir/progress.make

Src/CMakeFiles/%.o: ../Src/%.asm

%.o: Src/CMakeFiles/%.o
%.o: Src/CMakeFiles/%.o.dir/build.make
.PHONY : %.o

# Rule to build all files generated by this target.
Src/CMakeFiles/%.o.dir/build: %.o
.PHONY : Src/CMakeFiles/%.o.dir/build

Src/CMakeFiles/%.o.dir/clean:
	cd /home/DnyaneshG/MyProjects/Generix/build/Src && $(CMAKE_COMMAND) -P CMakeFiles/%.o.dir/cmake_clean.cmake
.PHONY : Src/CMakeFiles/%.o.dir/clean

Src/CMakeFiles/%.o.dir/depend:
	cd /home/DnyaneshG/MyProjects/Generix/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/DnyaneshG/MyProjects/Generix /home/DnyaneshG/MyProjects/Generix/Src /home/DnyaneshG/MyProjects/Generix/build /home/DnyaneshG/MyProjects/Generix/build/Src /home/DnyaneshG/MyProjects/Generix/build/Src/CMakeFiles/%.o.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Src/CMakeFiles/%.o.dir/depend

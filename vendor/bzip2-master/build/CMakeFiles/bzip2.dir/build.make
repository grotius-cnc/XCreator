# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/user/XCreator/vendor/bzip2-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/XCreator/vendor/bzip2-master/build

# Include any dependencies generated for this target.
include CMakeFiles/bzip2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bzip2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bzip2.dir/flags.make

CMakeFiles/bzip2.dir/bzip2.c.o: CMakeFiles/bzip2.dir/flags.make
CMakeFiles/bzip2.dir/bzip2.c.o: ../bzip2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/bzip2.dir/bzip2.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/bzip2.dir/bzip2.c.o -c /home/user/XCreator/vendor/bzip2-master/bzip2.c

CMakeFiles/bzip2.dir/bzip2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bzip2.dir/bzip2.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/XCreator/vendor/bzip2-master/bzip2.c > CMakeFiles/bzip2.dir/bzip2.c.i

CMakeFiles/bzip2.dir/bzip2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bzip2.dir/bzip2.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/XCreator/vendor/bzip2-master/bzip2.c -o CMakeFiles/bzip2.dir/bzip2.c.s

# Object files for target bzip2
bzip2_OBJECTS = \
"CMakeFiles/bzip2.dir/bzip2.c.o"

# External object files for target bzip2
bzip2_EXTERNAL_OBJECTS = \
"/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles/bz2_ObjLib.dir/blocksort.c.o" \
"/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles/bz2_ObjLib.dir/huffman.c.o" \
"/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles/bz2_ObjLib.dir/crctable.c.o" \
"/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles/bz2_ObjLib.dir/randtable.c.o" \
"/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles/bz2_ObjLib.dir/compress.c.o" \
"/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles/bz2_ObjLib.dir/decompress.c.o" \
"/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles/bz2_ObjLib.dir/bzlib.c.o"

bzip2: CMakeFiles/bzip2.dir/bzip2.c.o
bzip2: CMakeFiles/bz2_ObjLib.dir/blocksort.c.o
bzip2: CMakeFiles/bz2_ObjLib.dir/huffman.c.o
bzip2: CMakeFiles/bz2_ObjLib.dir/crctable.c.o
bzip2: CMakeFiles/bz2_ObjLib.dir/randtable.c.o
bzip2: CMakeFiles/bz2_ObjLib.dir/compress.c.o
bzip2: CMakeFiles/bz2_ObjLib.dir/decompress.c.o
bzip2: CMakeFiles/bz2_ObjLib.dir/bzlib.c.o
bzip2: CMakeFiles/bzip2.dir/build.make
bzip2: CMakeFiles/bzip2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bzip2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bzip2.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating symbolic link (or copy) bzcat of bzip2"
	/usr/bin/cmake -E create_symlink bzip2 bzcat
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating symbolic link (or copy) bunzip of bzip2"
	/usr/bin/cmake -E create_symlink bzip2 bunzip

# Rule to build all files generated by this target.
CMakeFiles/bzip2.dir/build: bzip2

.PHONY : CMakeFiles/bzip2.dir/build

CMakeFiles/bzip2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bzip2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bzip2.dir/clean

CMakeFiles/bzip2.dir/depend:
	cd /home/user/XCreator/vendor/bzip2-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/XCreator/vendor/bzip2-master /home/user/XCreator/vendor/bzip2-master /home/user/XCreator/vendor/bzip2-master/build /home/user/XCreator/vendor/bzip2-master/build /home/user/XCreator/vendor/bzip2-master/build/CMakeFiles/bzip2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bzip2.dir/depend


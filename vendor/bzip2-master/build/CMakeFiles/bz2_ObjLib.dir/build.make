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
include CMakeFiles/bz2_ObjLib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bz2_ObjLib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bz2_ObjLib.dir/flags.make

CMakeFiles/bz2_ObjLib.dir/blocksort.c.o: CMakeFiles/bz2_ObjLib.dir/flags.make
CMakeFiles/bz2_ObjLib.dir/blocksort.c.o: ../blocksort.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/bz2_ObjLib.dir/blocksort.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/bz2_ObjLib.dir/blocksort.c.o -c /home/user/XCreator/vendor/bzip2-master/blocksort.c

CMakeFiles/bz2_ObjLib.dir/blocksort.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bz2_ObjLib.dir/blocksort.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/XCreator/vendor/bzip2-master/blocksort.c > CMakeFiles/bz2_ObjLib.dir/blocksort.c.i

CMakeFiles/bz2_ObjLib.dir/blocksort.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bz2_ObjLib.dir/blocksort.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/XCreator/vendor/bzip2-master/blocksort.c -o CMakeFiles/bz2_ObjLib.dir/blocksort.c.s

CMakeFiles/bz2_ObjLib.dir/huffman.c.o: CMakeFiles/bz2_ObjLib.dir/flags.make
CMakeFiles/bz2_ObjLib.dir/huffman.c.o: ../huffman.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/bz2_ObjLib.dir/huffman.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/bz2_ObjLib.dir/huffman.c.o -c /home/user/XCreator/vendor/bzip2-master/huffman.c

CMakeFiles/bz2_ObjLib.dir/huffman.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bz2_ObjLib.dir/huffman.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/XCreator/vendor/bzip2-master/huffman.c > CMakeFiles/bz2_ObjLib.dir/huffman.c.i

CMakeFiles/bz2_ObjLib.dir/huffman.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bz2_ObjLib.dir/huffman.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/XCreator/vendor/bzip2-master/huffman.c -o CMakeFiles/bz2_ObjLib.dir/huffman.c.s

CMakeFiles/bz2_ObjLib.dir/crctable.c.o: CMakeFiles/bz2_ObjLib.dir/flags.make
CMakeFiles/bz2_ObjLib.dir/crctable.c.o: ../crctable.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/bz2_ObjLib.dir/crctable.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/bz2_ObjLib.dir/crctable.c.o -c /home/user/XCreator/vendor/bzip2-master/crctable.c

CMakeFiles/bz2_ObjLib.dir/crctable.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bz2_ObjLib.dir/crctable.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/XCreator/vendor/bzip2-master/crctable.c > CMakeFiles/bz2_ObjLib.dir/crctable.c.i

CMakeFiles/bz2_ObjLib.dir/crctable.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bz2_ObjLib.dir/crctable.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/XCreator/vendor/bzip2-master/crctable.c -o CMakeFiles/bz2_ObjLib.dir/crctable.c.s

CMakeFiles/bz2_ObjLib.dir/randtable.c.o: CMakeFiles/bz2_ObjLib.dir/flags.make
CMakeFiles/bz2_ObjLib.dir/randtable.c.o: ../randtable.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/bz2_ObjLib.dir/randtable.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/bz2_ObjLib.dir/randtable.c.o -c /home/user/XCreator/vendor/bzip2-master/randtable.c

CMakeFiles/bz2_ObjLib.dir/randtable.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bz2_ObjLib.dir/randtable.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/XCreator/vendor/bzip2-master/randtable.c > CMakeFiles/bz2_ObjLib.dir/randtable.c.i

CMakeFiles/bz2_ObjLib.dir/randtable.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bz2_ObjLib.dir/randtable.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/XCreator/vendor/bzip2-master/randtable.c -o CMakeFiles/bz2_ObjLib.dir/randtable.c.s

CMakeFiles/bz2_ObjLib.dir/compress.c.o: CMakeFiles/bz2_ObjLib.dir/flags.make
CMakeFiles/bz2_ObjLib.dir/compress.c.o: ../compress.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/bz2_ObjLib.dir/compress.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/bz2_ObjLib.dir/compress.c.o -c /home/user/XCreator/vendor/bzip2-master/compress.c

CMakeFiles/bz2_ObjLib.dir/compress.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bz2_ObjLib.dir/compress.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/XCreator/vendor/bzip2-master/compress.c > CMakeFiles/bz2_ObjLib.dir/compress.c.i

CMakeFiles/bz2_ObjLib.dir/compress.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bz2_ObjLib.dir/compress.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/XCreator/vendor/bzip2-master/compress.c -o CMakeFiles/bz2_ObjLib.dir/compress.c.s

CMakeFiles/bz2_ObjLib.dir/decompress.c.o: CMakeFiles/bz2_ObjLib.dir/flags.make
CMakeFiles/bz2_ObjLib.dir/decompress.c.o: ../decompress.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/bz2_ObjLib.dir/decompress.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/bz2_ObjLib.dir/decompress.c.o -c /home/user/XCreator/vendor/bzip2-master/decompress.c

CMakeFiles/bz2_ObjLib.dir/decompress.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bz2_ObjLib.dir/decompress.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/XCreator/vendor/bzip2-master/decompress.c > CMakeFiles/bz2_ObjLib.dir/decompress.c.i

CMakeFiles/bz2_ObjLib.dir/decompress.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bz2_ObjLib.dir/decompress.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/XCreator/vendor/bzip2-master/decompress.c -o CMakeFiles/bz2_ObjLib.dir/decompress.c.s

CMakeFiles/bz2_ObjLib.dir/bzlib.c.o: CMakeFiles/bz2_ObjLib.dir/flags.make
CMakeFiles/bz2_ObjLib.dir/bzlib.c.o: ../bzlib.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/XCreator/vendor/bzip2-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/bz2_ObjLib.dir/bzlib.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/bz2_ObjLib.dir/bzlib.c.o -c /home/user/XCreator/vendor/bzip2-master/bzlib.c

CMakeFiles/bz2_ObjLib.dir/bzlib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bz2_ObjLib.dir/bzlib.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/XCreator/vendor/bzip2-master/bzlib.c > CMakeFiles/bz2_ObjLib.dir/bzlib.c.i

CMakeFiles/bz2_ObjLib.dir/bzlib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bz2_ObjLib.dir/bzlib.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/XCreator/vendor/bzip2-master/bzlib.c -o CMakeFiles/bz2_ObjLib.dir/bzlib.c.s

bz2_ObjLib: CMakeFiles/bz2_ObjLib.dir/blocksort.c.o
bz2_ObjLib: CMakeFiles/bz2_ObjLib.dir/huffman.c.o
bz2_ObjLib: CMakeFiles/bz2_ObjLib.dir/crctable.c.o
bz2_ObjLib: CMakeFiles/bz2_ObjLib.dir/randtable.c.o
bz2_ObjLib: CMakeFiles/bz2_ObjLib.dir/compress.c.o
bz2_ObjLib: CMakeFiles/bz2_ObjLib.dir/decompress.c.o
bz2_ObjLib: CMakeFiles/bz2_ObjLib.dir/bzlib.c.o
bz2_ObjLib: CMakeFiles/bz2_ObjLib.dir/build.make

.PHONY : bz2_ObjLib

# Rule to build all files generated by this target.
CMakeFiles/bz2_ObjLib.dir/build: bz2_ObjLib

.PHONY : CMakeFiles/bz2_ObjLib.dir/build

CMakeFiles/bz2_ObjLib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bz2_ObjLib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bz2_ObjLib.dir/clean

CMakeFiles/bz2_ObjLib.dir/depend:
	cd /home/user/XCreator/vendor/bzip2-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/XCreator/vendor/bzip2-master /home/user/XCreator/vendor/bzip2-master /home/user/XCreator/vendor/bzip2-master/build /home/user/XCreator/vendor/bzip2-master/build /home/user/XCreator/vendor/bzip2-master/build/CMakeFiles/bz2_ObjLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bz2_ObjLib.dir/depend


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
CMAKE_SOURCE_DIR = /home/user/XCreator/vendor/clip-1.5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/XCreator/vendor/clip-1.5/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/clip_image_tests.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/clip_image_tests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/clip_image_tests.dir/flags.make

tests/CMakeFiles/clip_image_tests.dir/image_tests.cpp.o: tests/CMakeFiles/clip_image_tests.dir/flags.make
tests/CMakeFiles/clip_image_tests.dir/image_tests.cpp.o: ../tests/image_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/XCreator/vendor/clip-1.5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/clip_image_tests.dir/image_tests.cpp.o"
	cd /home/user/XCreator/vendor/clip-1.5/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clip_image_tests.dir/image_tests.cpp.o -c /home/user/XCreator/vendor/clip-1.5/tests/image_tests.cpp

tests/CMakeFiles/clip_image_tests.dir/image_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clip_image_tests.dir/image_tests.cpp.i"
	cd /home/user/XCreator/vendor/clip-1.5/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/XCreator/vendor/clip-1.5/tests/image_tests.cpp > CMakeFiles/clip_image_tests.dir/image_tests.cpp.i

tests/CMakeFiles/clip_image_tests.dir/image_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clip_image_tests.dir/image_tests.cpp.s"
	cd /home/user/XCreator/vendor/clip-1.5/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/XCreator/vendor/clip-1.5/tests/image_tests.cpp -o CMakeFiles/clip_image_tests.dir/image_tests.cpp.s

# Object files for target clip_image_tests
clip_image_tests_OBJECTS = \
"CMakeFiles/clip_image_tests.dir/image_tests.cpp.o"

# External object files for target clip_image_tests
clip_image_tests_EXTERNAL_OBJECTS =

tests/clip_image_tests: tests/CMakeFiles/clip_image_tests.dir/image_tests.cpp.o
tests/clip_image_tests: tests/CMakeFiles/clip_image_tests.dir/build.make
tests/clip_image_tests: libclip.a
tests/clip_image_tests: /usr/lib/x86_64-linux-gnu/libpng.so
tests/clip_image_tests: tests/CMakeFiles/clip_image_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/XCreator/vendor/clip-1.5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable clip_image_tests"
	cd /home/user/XCreator/vendor/clip-1.5/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clip_image_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/clip_image_tests.dir/build: tests/clip_image_tests

.PHONY : tests/CMakeFiles/clip_image_tests.dir/build

tests/CMakeFiles/clip_image_tests.dir/clean:
	cd /home/user/XCreator/vendor/clip-1.5/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/clip_image_tests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/clip_image_tests.dir/clean

tests/CMakeFiles/clip_image_tests.dir/depend:
	cd /home/user/XCreator/vendor/clip-1.5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/XCreator/vendor/clip-1.5 /home/user/XCreator/vendor/clip-1.5/tests /home/user/XCreator/vendor/clip-1.5/build /home/user/XCreator/vendor/clip-1.5/build/tests /home/user/XCreator/vendor/clip-1.5/build/tests/CMakeFiles/clip_image_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/clip_image_tests.dir/depend


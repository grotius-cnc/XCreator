# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
include examples/CMakeFiles/put_image.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/CMakeFiles/put_image.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/put_image.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/put_image.dir/flags.make

examples/CMakeFiles/put_image.dir/put_image.cpp.o: examples/CMakeFiles/put_image.dir/flags.make
examples/CMakeFiles/put_image.dir/put_image.cpp.o: /home/user/XCreator/vendor/clip-1.5/examples/put_image.cpp
examples/CMakeFiles/put_image.dir/put_image.cpp.o: examples/CMakeFiles/put_image.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/XCreator/vendor/clip-1.5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/put_image.dir/put_image.cpp.o"
	cd /home/user/XCreator/vendor/clip-1.5/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/CMakeFiles/put_image.dir/put_image.cpp.o -MF CMakeFiles/put_image.dir/put_image.cpp.o.d -o CMakeFiles/put_image.dir/put_image.cpp.o -c /home/user/XCreator/vendor/clip-1.5/examples/put_image.cpp

examples/CMakeFiles/put_image.dir/put_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/put_image.dir/put_image.cpp.i"
	cd /home/user/XCreator/vendor/clip-1.5/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/XCreator/vendor/clip-1.5/examples/put_image.cpp > CMakeFiles/put_image.dir/put_image.cpp.i

examples/CMakeFiles/put_image.dir/put_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/put_image.dir/put_image.cpp.s"
	cd /home/user/XCreator/vendor/clip-1.5/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/XCreator/vendor/clip-1.5/examples/put_image.cpp -o CMakeFiles/put_image.dir/put_image.cpp.s

# Object files for target put_image
put_image_OBJECTS = \
"CMakeFiles/put_image.dir/put_image.cpp.o"

# External object files for target put_image
put_image_EXTERNAL_OBJECTS =

examples/put_image: examples/CMakeFiles/put_image.dir/put_image.cpp.o
examples/put_image: examples/CMakeFiles/put_image.dir/build.make
examples/put_image: libclip.a
examples/put_image: /usr/lib/x86_64-linux-gnu/libpng.so
examples/put_image: examples/CMakeFiles/put_image.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/XCreator/vendor/clip-1.5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable put_image"
	cd /home/user/XCreator/vendor/clip-1.5/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/put_image.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/put_image.dir/build: examples/put_image
.PHONY : examples/CMakeFiles/put_image.dir/build

examples/CMakeFiles/put_image.dir/clean:
	cd /home/user/XCreator/vendor/clip-1.5/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/put_image.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/put_image.dir/clean

examples/CMakeFiles/put_image.dir/depend:
	cd /home/user/XCreator/vendor/clip-1.5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/XCreator/vendor/clip-1.5 /home/user/XCreator/vendor/clip-1.5/examples /home/user/XCreator/vendor/clip-1.5/build /home/user/XCreator/vendor/clip-1.5/build/examples /home/user/XCreator/vendor/clip-1.5/build/examples/CMakeFiles/put_image.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/put_image.dir/depend


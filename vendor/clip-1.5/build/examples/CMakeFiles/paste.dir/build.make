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
include examples/CMakeFiles/paste.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/paste.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/paste.dir/flags.make

examples/CMakeFiles/paste.dir/paste.cpp.o: examples/CMakeFiles/paste.dir/flags.make
examples/CMakeFiles/paste.dir/paste.cpp.o: ../examples/paste.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/XCreator/vendor/clip-1.5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/paste.dir/paste.cpp.o"
	cd /home/user/XCreator/vendor/clip-1.5/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/paste.dir/paste.cpp.o -c /home/user/XCreator/vendor/clip-1.5/examples/paste.cpp

examples/CMakeFiles/paste.dir/paste.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/paste.dir/paste.cpp.i"
	cd /home/user/XCreator/vendor/clip-1.5/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/XCreator/vendor/clip-1.5/examples/paste.cpp > CMakeFiles/paste.dir/paste.cpp.i

examples/CMakeFiles/paste.dir/paste.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/paste.dir/paste.cpp.s"
	cd /home/user/XCreator/vendor/clip-1.5/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/XCreator/vendor/clip-1.5/examples/paste.cpp -o CMakeFiles/paste.dir/paste.cpp.s

# Object files for target paste
paste_OBJECTS = \
"CMakeFiles/paste.dir/paste.cpp.o"

# External object files for target paste
paste_EXTERNAL_OBJECTS =

examples/paste: examples/CMakeFiles/paste.dir/paste.cpp.o
examples/paste: examples/CMakeFiles/paste.dir/build.make
examples/paste: libclip.a
examples/paste: /usr/lib/x86_64-linux-gnu/libpng.so
examples/paste: examples/CMakeFiles/paste.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/XCreator/vendor/clip-1.5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable paste"
	cd /home/user/XCreator/vendor/clip-1.5/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/paste.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/paste.dir/build: examples/paste

.PHONY : examples/CMakeFiles/paste.dir/build

examples/CMakeFiles/paste.dir/clean:
	cd /home/user/XCreator/vendor/clip-1.5/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/paste.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/paste.dir/clean

examples/CMakeFiles/paste.dir/depend:
	cd /home/user/XCreator/vendor/clip-1.5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/XCreator/vendor/clip-1.5 /home/user/XCreator/vendor/clip-1.5/examples /home/user/XCreator/vendor/clip-1.5/build /home/user/XCreator/vendor/clip-1.5/build/examples /home/user/XCreator/vendor/clip-1.5/build/examples/CMakeFiles/paste.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/paste.dir/depend


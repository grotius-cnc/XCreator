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
CMAKE_SOURCE_DIR = /home/user/XCreator/XTerminal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/XCreator/XTerminal/build

# Include any dependencies generated for this target.
include CMakeFiles/XTerminal.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/XTerminal.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/XTerminal.dir/flags.make

CMakeFiles/XTerminal.dir/main.cpp.o: CMakeFiles/XTerminal.dir/flags.make
CMakeFiles/XTerminal.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/XCreator/XTerminal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/XTerminal.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/XTerminal.dir/main.cpp.o -c /home/user/XCreator/XTerminal/main.cpp

CMakeFiles/XTerminal.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/XTerminal.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/XCreator/XTerminal/main.cpp > CMakeFiles/XTerminal.dir/main.cpp.i

CMakeFiles/XTerminal.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/XTerminal.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/XCreator/XTerminal/main.cpp -o CMakeFiles/XTerminal.dir/main.cpp.s

# Object files for target XTerminal
XTerminal_OBJECTS = \
"CMakeFiles/XTerminal.dir/main.cpp.o"

# External object files for target XTerminal
XTerminal_EXTERNAL_OBJECTS =

XTerminal: CMakeFiles/XTerminal.dir/main.cpp.o
XTerminal: CMakeFiles/XTerminal.dir/build.make
XTerminal: ../../vendor/soil/build/libsoil.a
XTerminal: ../../vendor/glfw-3.3.7/build/src/libglfw3.a
XTerminal: ../../vendor/clip-1.5/build/libclip.a
XTerminal: ../../vendor/glad/build/libglad.a
XTerminal: CMakeFiles/XTerminal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/XCreator/XTerminal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable XTerminal"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/XTerminal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/XTerminal.dir/build: XTerminal

.PHONY : CMakeFiles/XTerminal.dir/build

CMakeFiles/XTerminal.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/XTerminal.dir/cmake_clean.cmake
.PHONY : CMakeFiles/XTerminal.dir/clean

CMakeFiles/XTerminal.dir/depend:
	cd /home/user/XCreator/XTerminal/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/XCreator/XTerminal /home/user/XCreator/XTerminal /home/user/XCreator/XTerminal/build /home/user/XCreator/XTerminal/build /home/user/XCreator/XTerminal/build/CMakeFiles/XTerminal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/XTerminal.dir/depend

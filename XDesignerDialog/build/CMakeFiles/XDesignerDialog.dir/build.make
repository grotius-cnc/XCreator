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
CMAKE_SOURCE_DIR = /home/user/XCreator/XDesignerDialog

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/XCreator/XDesignerDialog/build

# Include any dependencies generated for this target.
include CMakeFiles/XDesignerDialog.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/XDesignerDialog.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/XDesignerDialog.dir/flags.make

CMakeFiles/XDesignerDialog.dir/main.cpp.o: CMakeFiles/XDesignerDialog.dir/flags.make
CMakeFiles/XDesignerDialog.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/XCreator/XDesignerDialog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/XDesignerDialog.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/XDesignerDialog.dir/main.cpp.o -c /home/user/XCreator/XDesignerDialog/main.cpp

CMakeFiles/XDesignerDialog.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/XDesignerDialog.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/XCreator/XDesignerDialog/main.cpp > CMakeFiles/XDesignerDialog.dir/main.cpp.i

CMakeFiles/XDesignerDialog.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/XDesignerDialog.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/XCreator/XDesignerDialog/main.cpp -o CMakeFiles/XDesignerDialog.dir/main.cpp.s

# Object files for target XDesignerDialog
XDesignerDialog_OBJECTS = \
"CMakeFiles/XDesignerDialog.dir/main.cpp.o"

# External object files for target XDesignerDialog
XDesignerDialog_EXTERNAL_OBJECTS =

XDesignerDialog: CMakeFiles/XDesignerDialog.dir/main.cpp.o
XDesignerDialog: CMakeFiles/XDesignerDialog.dir/build.make
XDesignerDialog: ../../vendor/soil/build/libsoil.a
XDesignerDialog: ../../vendor/glfw-3.3.7/build/src/libglfw3.a
XDesignerDialog: ../../vendor/clip-1.5/build/libclip.a
XDesignerDialog: ../../vendor/glad/build/libglad.a
XDesignerDialog: CMakeFiles/XDesignerDialog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/XCreator/XDesignerDialog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable XDesignerDialog"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/XDesignerDialog.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/XDesignerDialog.dir/build: XDesignerDialog

.PHONY : CMakeFiles/XDesignerDialog.dir/build

CMakeFiles/XDesignerDialog.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/XDesignerDialog.dir/cmake_clean.cmake
.PHONY : CMakeFiles/XDesignerDialog.dir/clean

CMakeFiles/XDesignerDialog.dir/depend:
	cd /home/user/XCreator/XDesignerDialog/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/XCreator/XDesignerDialog /home/user/XCreator/XDesignerDialog /home/user/XCreator/XDesignerDialog/build /home/user/XCreator/XDesignerDialog/build /home/user/XCreator/XDesignerDialog/build/CMakeFiles/XDesignerDialog.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/XDesignerDialog.dir/depend


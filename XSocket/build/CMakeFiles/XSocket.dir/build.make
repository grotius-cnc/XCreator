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
CMAKE_SOURCE_DIR = /home/user/XCreator/XSocket

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/XCreator/XSocket/build

# Include any dependencies generated for this target.
include CMakeFiles/XSocket.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/XSocket.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/XSocket.dir/flags.make

CMakeFiles/XSocket.dir/main.cpp.o: CMakeFiles/XSocket.dir/flags.make
CMakeFiles/XSocket.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/XCreator/XSocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/XSocket.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/XSocket.dir/main.cpp.o -c /home/user/XCreator/XSocket/main.cpp

CMakeFiles/XSocket.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/XSocket.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/XCreator/XSocket/main.cpp > CMakeFiles/XSocket.dir/main.cpp.i

CMakeFiles/XSocket.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/XSocket.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/XCreator/XSocket/main.cpp -o CMakeFiles/XSocket.dir/main.cpp.s

# Object files for target XSocket
XSocket_OBJECTS = \
"CMakeFiles/XSocket.dir/main.cpp.o"

# External object files for target XSocket
XSocket_EXTERNAL_OBJECTS =

XSocket: CMakeFiles/XSocket.dir/main.cpp.o
XSocket: CMakeFiles/XSocket.dir/build.make
XSocket: ../../vendor/soil/build/libsoil.a
XSocket: ../../vendor/glfw-3.3.7/build/src/libglfw3.a
XSocket: ../../vendor/clip-1.5/build/libclip.a
XSocket: ../../vendor/glad/build/libglad.a
XSocket: /usr/local/lib/libTKOpenGl.so.7.7.0
XSocket: /usr/local/lib/libTKXSDRAW.so.7.7.0
XSocket: /usr/local/lib/libTKBinXCAF.so.7.7.0
XSocket: /usr/local/lib/libTKXmlXCAF.so.7.7.0
XSocket: /usr/local/lib/libTKXDESTEP.so.7.7.0
XSocket: /usr/local/lib/libTKXDEIGES.so.7.7.0
XSocket: /usr/local/lib/libTKSTL.so.7.7.0
XSocket: /usr/local/lib/libTKMeshVS.so.7.7.0
XSocket: /usr/local/lib/libTKVRML.so.7.7.0
XSocket: /usr/local/lib/libTKRWMesh.so.7.7.0
XSocket: /usr/local/lib/libTKDCAF.so.7.7.0
XSocket: /usr/local/lib/libTKViewerTest.so.7.7.0
XSocket: /usr/local/lib/libTKTopTest.so.7.7.0
XSocket: /usr/local/lib/libTKFeat.so.7.7.0
XSocket: /usr/local/lib/libTKOffset.so.7.7.0
XSocket: /usr/local/lib/libTKDraw.so.7.7.0
XSocket: /usr/lib/x86_64-linux-gnu/libtcl.so
XSocket: /usr/local/lib/libTKFillet.so.7.7.0
XSocket: /usr/local/lib/libTKStd.so.7.7.0
XSocket: /usr/local/lib/libTKStdL.so.7.7.0
XSocket: /usr/local/lib/libTKBin.so.7.7.0
XSocket: /usr/local/lib/libTKBinL.so.7.7.0
XSocket: /usr/local/lib/libTKXml.so.7.7.0
XSocket: /usr/local/lib/libTKXmlL.so.7.7.0
XSocket: /usr/local/lib/libTKSTEP.so.7.7.0
XSocket: /usr/local/lib/libTKSTEP209.so.7.7.0
XSocket: /usr/local/lib/libTKSTEPAttr.so.7.7.0
XSocket: /usr/local/lib/libTKSTEPBase.so.7.7.0
XSocket: /usr/local/lib/libTKXCAF.so.7.7.0
XSocket: /usr/local/lib/libTKVCAF.so.7.7.0
XSocket: /usr/local/lib/libTKV3d.so.7.7.0
XSocket: /usr/local/lib/libTKMesh.so.7.7.0
XSocket: /usr/local/lib/libTKHLR.so.7.7.0
XSocket: /usr/local/lib/libTKService.so.7.7.0
XSocket: /usr/lib/x86_64-linux-gnu/libfreeimage.so
XSocket: /usr/lib/x86_64-linux-gnu/libfreetype.so
XSocket: /usr/local/lib/libTKCAF.so.7.7.0
XSocket: /usr/local/lib/libTKLCAF.so.7.7.0
XSocket: /usr/local/lib/libTKCDF.so.7.7.0
XSocket: /usr/local/lib/libTKIGES.so.7.7.0
XSocket: /usr/local/lib/libTKXSBase.so.7.7.0
XSocket: /usr/local/lib/libTKBool.so.7.7.0
XSocket: /usr/local/lib/libTKBO.so.7.7.0
XSocket: /usr/local/lib/libTKShHealing.so.7.7.0
XSocket: /usr/local/lib/libTKPrim.so.7.7.0
XSocket: /usr/local/lib/libTKTopAlgo.so.7.7.0
XSocket: /usr/local/lib/libTKGeomAlgo.so.7.7.0
XSocket: /usr/local/lib/libTKBRep.so.7.7.0
XSocket: /usr/local/lib/libTKGeomBase.so.7.7.0
XSocket: /usr/local/lib/libTKG3d.so.7.7.0
XSocket: /usr/local/lib/libTKG2d.so.7.7.0
XSocket: /usr/local/lib/libTKMath.so.7.7.0
XSocket: /usr/local/lib/libTKXDE.so.7.7.0
XSocket: /usr/local/lib/libTKernel.so.7.7.0
XSocket: CMakeFiles/XSocket.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/XCreator/XSocket/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable XSocket"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/XSocket.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/XSocket.dir/build: XSocket

.PHONY : CMakeFiles/XSocket.dir/build

CMakeFiles/XSocket.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/XSocket.dir/cmake_clean.cmake
.PHONY : CMakeFiles/XSocket.dir/clean

CMakeFiles/XSocket.dir/depend:
	cd /home/user/XCreator/XSocket/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/XCreator/XSocket /home/user/XCreator/XSocket /home/user/XCreator/XSocket/build /home/user/XCreator/XSocket/build /home/user/XCreator/XSocket/build/CMakeFiles/XSocket.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/XSocket.dir/depend

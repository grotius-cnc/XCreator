cmake_minimum_required(VERSION 3.5)
project(XGridLayout LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Rescan project to ensure the copy is done.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/icons DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(LIB_DIR "${SRC_DIR}/../vendor")
set(XCREATOR_DIR "${SRC_DIR}")
set(SOURCES
# main.cpp is only used to tell cmake it has to be compiled for c++ language.
    "${XCREATOR_DIR}/main.cpp"
    "${XCREATOR_DIR}/XMainWindow.h"
    "${XCREATOR_DIR}/XGridLayout.h"
    )
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}/")
target_include_directories(${PROJECT_NAME} PRIVATE "${LIB_DIR}/")
target_include_directories(${PROJECT_NAME} PRIVATE "${LIB_DIR}/glad/build/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${LIB_DIR}/glfw-3.3.7/include/GLFW")
#target_include_directories(${PROJECT_NAME} PRIVATE "${LIB_DIR}/zlib/build")
target_include_directories(${PROJECT_NAME} PRIVATE "${LIB_DIR}/freetype-2.12.1/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${LIB_DIR}/soil/inc")
target_include_directories(${PROJECT_NAME} PRIVATE "${LIB_DIR}/lodepng")
target_include_directories(${PROJECT_NAME} PRIVATE "${LIB_DIR}/clip-1.5")
target_include_directories(${PROJECT_NAME} PRIVATE "${LIB_DIR}/xcreator/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${XCREATOR_DIR}/")

# When compiling zlib and freetypes, we got error. When using internal libs, no problem occurs.
#add_library(zlib SHARED IMPORTED)
#set_target_properties(zlib PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/zlib/build/libz.so)

#add_library(freetypes SHARED IMPORTED)
#set_target_properties(freetypes PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/freetype-2.12.1/build/libfreetype.a)

add_library(glfw3 SHARED IMPORTED)
set_target_properties(glfw3 PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/glfw-3.3.7/build/src/libglfw3.a)

add_library(glad SHARED IMPORTED)
set_target_properties(glad PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/glad/build/libglad.a)

add_library(soil SHARED IMPORTED)
set_target_properties(soil PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/soil/build/libsoil.a)

# Needs png xcb X11 clip
add_library(clip SHARED IMPORTED)
set_target_properties(clip PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/clip-1.5/build/libclip.a)

# Needs png xcb X11 clip
add_library(lodepng SHARED IMPORTED)
set_target_properties(lodepng PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/lodepng/liblodepng.a)

target_link_libraries(${PROJECT_NAME} PRIVATE soil lodepng glfw3 GLU clip xcb X11 GL glad Xrandr pthread Xi dl Xcursor freetype png)



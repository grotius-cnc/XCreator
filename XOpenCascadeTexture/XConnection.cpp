#include "XConnection.h"

//! glfwGetX11Display uses the native include.
#if defined (__APPLE__)
#undef Handle // avoid name collisions in macOS headers
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#elif defined (_WIN32)
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#else
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#endif
#include <GLFW/glfw3native.h>

//! Class to retrieve some info from the Glwf native header file.
//! This info is retrieved in a separate source file, such that it don't give duplicate name errors
//! for XPoint, XTriangle, etc. that are also used in some X11 files.
XConnention::XConnention(){}

//! Returns a new opencascade aspect display connection.
Handle(Aspect_DisplayConnection) XConnention::getNewHandleAspectDisplayConnection(){
    return (new Aspect_DisplayConnection((Aspect_XDisplay* )glfwGetX11Display()));
}
//! Returns the Glfw x11 diplay.
Display* XConnention::getGlfwX11Display(){
    return glfwGetX11Display();
}
//! Returns the Glfw x11 window.
XID XConnention::getGlfwX11Window(GLFWwindow *theGlfwWindowPointer){
    return glfwGetX11Window(theGlfwWindowPointer);
}
//! Returns the Glfw context.
GLXContext XConnention::getGlfwContext(GLFWwindow *theGlfwWindowPointer){
    return glfwGetGLXContext(theGlfwWindowPointer);
}

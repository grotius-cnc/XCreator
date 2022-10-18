#ifndef XCONNECTION_H
#define XCONNECTION_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Aspect_DisplayConnection.hxx>

//! A trick to avoid name conflicts. From here read XPoint as XXPoint.
#ifndef XPoint
#define XPoint XZPoint
#endif

#ifndef XColor
#define XColor XZColor
#endif

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

class XConnention
{
public:
    XConnention();

    Handle(Aspect_DisplayConnection) getNewHandleAspectDisplayConnection();
    XID getGlfwX11Window(GLFWwindow *theGlfwWindowPointer);
    Display *getGlfwX11Display();
    GLXContext getGlfwContext(GLFWwindow *theGlfwWindowPointer);
};

//! Bring back the names to original state.
#ifndef XZColor
#define XZColor XColor
#endif

#ifndef XZPoint
#define XZPoint XPoint
#endif

#endif


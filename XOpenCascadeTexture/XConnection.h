#ifndef XCONNECTION_H
#define XCONNECTION_H
/*
        Copyright (c) 2022 Skynet Cyberdyne

        This software is provided 'as-is', without any express or implied
        warranty. In no event will the authors be held liable for any damages
        arising from the use of this software.

        Permission is granted to anyone to use this software for any purpose,
        excluding commercial applications, and to alter it and redistribute it
        freely, subject to the following restrictions:

        1. The origin of this software must not be misrepresented; you must not
           claim that you wrote the original software. If you use this software
           in a product, an acknowledgment in the product documentation would
           be appreciated but is not required.

        2. Altered source versions must be plainly marked as such, and must not
           be misrepresented as being the original software.

        3. This notice may not be removed or altered from any source
           distribution.
*/
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

//! A closs to retrieve some information from the glfw native header file.
class XConnention
{
public:
    //! Empty constructor.
    XConnention();
    //! Functions:
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


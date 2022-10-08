#ifndef XOPENGLPOINT_H
#define XOPENGLPOINT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <XPoint.h>
#include <XOpenGLLine.h>

class XOpenGLPoint {
public:
    XOpenGLPoint(){}

    //! Draw a point using modern openGL.
    void drawPoint(XPoint thePoint, float thePointSize, XColor theColor, XWindow *theWindow){
        XOpenGLLine().drawLineStrip({thePoint},thePointSize,theColor,theWindow);
    }

private:
};
#endif

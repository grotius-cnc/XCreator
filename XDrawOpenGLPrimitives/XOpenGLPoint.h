#ifndef XOPENGLPOINT_H
#define XOPENGLPOINT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <XPoint.h>

class XOpenGLPoint {
public:
    XOpenGLPoint(){}

    //! Draw openGL point.
    void drawPoint(XPoint thePoint, float thePointSize, XColor theColor){
        glPointSize(1.0);
        glColor4f(theColor.Red(),theColor.Green(),theColor.Blue(),theColor.Alpha());
        glBegin(GL_POINTS);
        glVertex3f(thePoint.X(),thePoint.Y(),thePoint.Z());
        glEnd();
    }

private:
};
#endif

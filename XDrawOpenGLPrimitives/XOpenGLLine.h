#ifndef XOPENGLLINE_H
#define XOPENGLLINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <XPoint.h>
#include <XRectangular.h>

class XOpenGLLine {
public:
    XOpenGLLine(){}

    //! Draw openGL line.
    void drawLine(XPoint theStart, XPoint theEnd, float theWidth, XColor theColor){
        glLineWidth(theWidth);
        glColor4f(theColor.Red(),theColor.Green(),theColor.Blue(),theColor.Alpha());
        glBegin(GL_LINES);
        glVertex3f(theStart.X(),theStart.Y(),theStart.Z());
        glVertex3f(theEnd.X(),theEnd.Y(),theEnd.Z());
        glEnd();
    }

private:

};

#endif














































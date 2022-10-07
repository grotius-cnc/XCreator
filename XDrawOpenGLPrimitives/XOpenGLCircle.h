#ifndef XOPENGLCIRCLE_H
#define XOPENGLCIRCLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <XPoint.h>

class XOpenGLCircle {
public:
    XOpenGLCircle(){}

    //! Draw openGL arc.
    void drawCircle(XPoint theCenter, float theRadius, float theWidth, int theDivision, XColor theColor){
        glLineWidth(theWidth);
        glColor4f(theColor.Red(),theColor.Green(),theColor.Blue(),theColor.Alpha());

        if (myAngleEndRad <= myAngleStartRad){  //! Avoid the start angle is bigger then the end angle value
            myAngleEndRad += 2*M_PI;
        }

        float arc_angle = myAngleEndRad - myAngleStartRad;
        float theta = arc_angle / float(theDivision - 1); //! Theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
        float tangetial_factor = tanf(theta);
        float radial_factor = cosf(theta);
        float x = theRadius * cosf(myAngleStartRad); //! We now start at the start angle
        float y = theRadius * sinf(myAngleStartRad);

        glBegin(GL_LINE_STRIP); //! Since the arc is not a closed curve, this is a strip now
        for(int ii = 0; ii < theDivision; ii++)
        {
            glVertex2f(x + theCenter.X(), y + theCenter.Y());
            float tx = -y;
            float ty = x;
            x += tx * tangetial_factor;
            y += ty * tangetial_factor;
            x *= radial_factor;
            y *= radial_factor;
        }
        glEnd();
    }
private:
    float myAngleStartRad=0;
    float myAngleEndRad=2*M_PI;
};
# endif


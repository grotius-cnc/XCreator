#ifndef XOPENGLCIRCLE_H
#define XOPENGLCIRCLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <XPoint.h>
#include <XOpenGLLine.h>
#include <XOpenGL3PSurface.h>

class XOpenGLCircle {
public:
    XOpenGLCircle(){}

    //! Draw openGL arc.
    void drawCircle(XPoint theCenter, float theRadius, float theWidth, int theDivision, XColor theColor, XWindow *theWindow){

        if (myAngleEndRad <= myAngleStartRad){  //! Avoid the start angle is bigger then the end angle value
            myAngleEndRad += 2*M_PI;
        }

        float arc_angle = myAngleEndRad - myAngleStartRad;
        float theta = arc_angle / float(theDivision - 1); //! Theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
        float tangetial_factor = tanf(theta);
        float radial_factor = cosf(theta);
        float x = theRadius * cosf(myAngleStartRad); //! We now start at the start angle
        float y = theRadius * sinf(myAngleStartRad);

        std::vector<XPoint> thePointVec;
        for(int ii = 0; ii < theDivision; ii++)
        {
            thePointVec.push_back({x + theCenter.X(), y + theCenter.Y(), theCenter.Z()});
            float tx = -y;
            float ty = x;
            x += tx * tangetial_factor;
            y += ty * tangetial_factor;
            x *= radial_factor;
            y *= radial_factor;
        }
        XOpenGLLine().drawLineStrip(thePointVec,theWidth,theColor,theWindow);
    }

    //! This will create a division of cake pieces.
    void drawSolidCircle(XPoint theCenter, float theRadius, float theWidth, int theDivision, XColor theColor, XWindow *theWindow){

        if (myAngleEndRad <= myAngleStartRad){  //! Avoid the start angle is bigger then the end angle value
            myAngleEndRad += 2*M_PI;
        }

        float arc_angle = myAngleEndRad - myAngleStartRad;
        float theta = arc_angle / float(theDivision - 1); //! Theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
        float tangetial_factor = tanf(theta);
        float radial_factor = cosf(theta);
        float x = theRadius * cosf(myAngleStartRad); //! We now start at the start angle
        float y = theRadius * sinf(myAngleStartRad);

        std::vector<XPoint> thePointVec;
        for(int ii = 0; ii < theDivision; ii++)
        {
            thePointVec.push_back({x + theCenter.X(), y + theCenter.Y(), theCenter.Z()});
            float tx = -y;
            float ty = x;
            x += tx * tangetial_factor;
            y += ty * tangetial_factor;
            x *= radial_factor;
            y *= radial_factor;
        }

        mySurface->setWindow(theWindow);
        mySurface->setColor(theColor);
        for(uint i=0; i<thePointVec.size()-1; i++){
            //! Create cake triangles.
            mySurface->setPoints(thePointVec.at(i),thePointVec.at(i+1),theCenter);
            mySurface->draw();
        }
    }
private:
    float myAngleStartRad=0;
    float myAngleEndRad=2*M_PI;
    XOpenGL3PSurface *mySurface=new XOpenGL3PSurface();
};
# endif


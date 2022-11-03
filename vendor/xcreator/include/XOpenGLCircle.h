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
    XOpenGLCircle(XPoint theCenter, float theRadius, float theWidth, int theDivision, XColor theColor, XWindow *theWindow) :
        myCenter(theCenter), myRadius(theRadius), myWidth(theWidth), myDivision(theDivision), myColor(theColor), myWindow(theWindow){

        //! Produce the linestrip.
        myPointVec=getCirclePointVec(myCenter,myRadius,myDivision);
        myLineStrip=new XOpenGLLine(myPointVec,myWidth,myColor,myWindow);

        //! Produce the solid inner circle.
        for(uint i=0; i<myPointVec.size()-1; i++){
            //! Create cake triangles.
            XOpenGL3PSurface *theSurface=new XOpenGL3PSurface();
            theSurface->setWindow(theWindow);
            theSurface->setColor(theColor);
            theSurface->setPoints(myPointVec.at(i),myPointVec.at(i+1),myCenter);
            myInnerSurface.push_back(theSurface);
        }
    }
    void drawCircle(){
        myLineStrip->drawLine();
    }
    void drawSolidCircle(){
        for(uint i=0; i<myInnerSurface.size(); i++){
            myInnerSurface.at(i)->draw();
        }
    }

    //! Draw openGL arc.
    void drawCircle(XPoint theCenter, float theRadius, float theWidth, int theDivision, XColor theColor, XWindow *theWindow){
        XOpenGLLine().drawLineStrip( getCirclePointVec(theCenter,theRadius,theDivision),theWidth,theColor,theWindow);
    }
    //! This will create a division of cake pieces.
    void drawSolidCircle(XPoint theCenter, float theRadius, int theDivision, XColor theColor, XWindow *theWindow){
        std::vector<XPoint> thePointVec=getCirclePointVec(theCenter,theRadius,theDivision);
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
    //! Solid circle preview, a vector of triangle cake pieces.
    std::vector<XOpenGL3PSurface*> myInnerSurface;

    XPoint myCenter;
    float myRadius;
    float myWidth;
    int myDivision;
    XColor myColor;
    XWindow *myWindow;
    XOpenGLLine *myLineStrip;
    std::vector<XPoint> myPointVec;

    std::vector<XPoint> getCirclePointVec(XPoint theCenter, float theRadius, int theDivision){
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
        return thePointVec;
    }
};
# endif


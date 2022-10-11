#ifndef XOPENGLPOINT_H
#define XOPENGLPOINT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <XPoint.h>
#include <XOpenGLLine.h>
#include <XOpenGLCircle.h>

class XOpenGLPoint {
public:
    //! Example :
    //! XOpenGLPoint().drawSquarePoint({20,20,0},10,{1.0,0,0,1.0},Window());
    //! XOpenGLPoint().drawRoundPoint({50,20,0},10,20,{1.0,0,0,1.0},Window());
    XOpenGLPoint(){}
    XOpenGLPoint(XPoint thePoint, float thePointSize, int theDivision, XColor theColor, XWindow *theWindow) :
        myPoint(thePoint), myPointSize(thePointSize), myDivision(theDivision=20), myColor(theColor), myWindow(theWindow){
        myLine=new XOpenGLLine({myPoint},myPointSize,myColor,myWindow);
        myCircle=new XOpenGLCircle(myPoint,thePointSize/2,thePointSize,theDivision,myColor,myWindow);
    }

    void drawSquarePoint(){
        myLine->drawLine();
    }
    void drawRoundPoint(){
        myCircle->drawCircle();
    }

    //! Draw a square point using modern openGL.
    void drawSquarePoint(XPoint thePoint, float thePointSize, XColor theColor, XWindow *theWindow){
        XOpenGLLine().drawLineStrip({thePoint},thePointSize,theColor,theWindow);
    }
    //! Draw a round point using modern openGL.
    void drawRoundPoint(XPoint thePoint, float thePointSize, int theDivision, XColor theColor, XWindow *theWindow){
        XOpenGLCircle().drawSolidCircle(thePoint,thePointSize/2,theDivision,theColor,theWindow);
    }

private:
    XPoint myPoint;
    float myPointSize;
    int myDivision;
    XColor myColor;
    XWindow *myWindow;

    XOpenGLLine* myLine;
    XOpenGLCircle *myCircle;
};
#endif

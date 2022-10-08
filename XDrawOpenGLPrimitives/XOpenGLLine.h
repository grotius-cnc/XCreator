#ifndef XOPENGLLINE_H
#define XOPENGLLINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <XPoint.h>
#include <XRectangular.h>
#include <XOpenGL4PSurface.h>

#define ccw false
#define cw true

class XOpenGLLine {
public:
    //! Draw a line or linestrip using modern OpenGL.

    XOpenGLLine(){}

    //! Draw modern openGL line.
    //! Example:
    //! XOpenGLLine().drawLine({50,50,0},{400,400,0},10,{1.0,1.0,0.0,1.0},Window());
    void drawLine(XPoint theStart, XPoint theEnd, float theWidth, XColor theColor, XWindow *theWindow){
        //! Get the surface points.
        std::vector<XPoint> thePointVec=offset2Side(theStart,theEnd,theWidth/2,cw);
        //! It needs the window dimensions to calculate the mirrored y axis.
        mySurface->setWindow(theWindow);
        mySurface->setSurface(thePointVec);
        mySurface->setColor(theColor);
        mySurface->draw();
    }

    //! Here we have to intersect the inner & outer offset lines, cq surfaces.
    //! Example:
    //! XOpenGLLine().drawLineStrip({{10,10,0},{100,10,0},{100,100,0},{200,100,0},{200,200,0}},9.25,{1.0,0,0,1.0},Window());
    //! Or to draw a Point, just give one point.
    //! XOpenGLLine().drawLineStrip({{100,100,0}}},10,{1.0,0,0,1.0},Window());
    void drawLineStrip(std::vector<XPoint> thePointVec, float theWidth, XColor theColor, XWindow *theWindow){

        if(thePointVec.size()==1){
            XPoint P=thePointVec.front();
            float x=P.X();
            float y=P.Y();
            float z=P.Z();
            float hw=theWidth/2;
            mySurface->setWindow(theWindow);
            mySurface->setSurface({{x-hw,y-hw,z},{x+hw,y-hw,z},{x+hw,y+hw,z},{x-hw,y+hw,z}});
            mySurface->setColor(theColor);
            mySurface->draw();
            std::cout<<"drawing point?"<<std::endl;
            return;
        }

        if(thePointVec.size()==2){
            drawLine(thePointVec.at(0),thePointVec.at(1),theWidth,theColor,theWindow);
            std::cout<<"drawing line instead of linestrip."<<std::endl;
            return;
        }

        if(thePointVec.size()<3){
            std::cout<<"incorect pointVec size from function drawLineStrip"<<std::endl;
            return;
        }
        //! Set the GlfwWindow for the surface widget.
        mySurface->setWindow(theWindow);

        //! Surface S0.
        std::vector<XPoint> S0={{0,0,0},{0,0,0},{0,0,0},{0,0,0}}; //! Initialized for 4 points.
        //! Surface S1.
        std::vector<XPoint> S1={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
        //! Surface result starage.
        std::vector<XPoint> SR={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
        //! Surface intersections.
        XPoint A,B, oldA, oldB;

        for(uint i=0; i<thePointVec.size(); i++){

            //! This will procude all surface data we need.
            if(i<thePointVec.size()-2){
                S0=offset2Side(thePointVec.at(i+0),thePointVec.at(i+1),theWidth/2,cw);
                S1=offset2Side(thePointVec.at(i+1),thePointVec.at(i+2),theWidth/2,cw);

                //! Intersection.
                A=intersect2Lines(S0.at(0),S0.at(1),S1.at(0),S1.at(1));
                B=intersect2Lines(S0.at(3),S0.at(2),S1.at(3),S1.at(2));
            }
            //! At start of linestrip.
            if(i==0){
                SR.at(0)=S0.at(0);
                SR.at(1)=A;
                SR.at(2)=B;
                SR.at(3)=S0.at(3);

                oldA.setPoint(A);
                oldB.setPoint(B);
            }
            //! Inbetween the linestrip start & end points.
            if(i>0 && i<thePointVec.size()-1){
                SR.at(0)=oldA;
                SR.at(1)=A;
                SR.at(2)=B;
                SR.at(3)=oldB;

                oldA.setPoint(A);
                oldB.setPoint(B);
            }
            //! At end of linestrip.
            if(i==thePointVec.size()-1){
                SR.at(0)=A;
                SR.at(1)=S1.at(1);
                SR.at(2)=S1.at(2);
                SR.at(3)=B;
            }
            //! Draw result.
            mySurface->setSurface(SR);
            mySurface->setColor(theColor);
            mySurface->draw();
        }
    }

    //! Offset the line to both sides. For the return value : theWindingOrder=false=ccw (counterclockwise).
    std::vector<XPoint> offset2Side(XPoint theStart, XPoint theEnd, float theOffset, bool theWindingOrder = cw){

        //! One side offset.
        XPoint tempA=rotate2D(theStart,theEnd,-90);
        XPoint tempAA=interpolate3DLine(theStart,tempA,theOffset);
        XPoint tempB=rotate2D(theEnd,theStart,90);
        XPoint tempBB=interpolate3DLine(theEnd,tempB,theOffset);

        //! Opposite side offset.
        XPoint tempC=rotate2D(theStart,theEnd,90);
        XPoint tempCC=interpolate3DLine(theStart,tempC,theOffset);
        XPoint tempD=rotate2D(theEnd,theStart,-90);
        XPoint tempDD=interpolate3DLine(theEnd,tempD,theOffset);

        //! drawLine(tempAA,tempBB,5,{1.0,0.0,0.0,1.0});
        //! drawLine(tempCC,tempDD,5,{1.0,0.0,0.0,1.0});

        //! Return ccw.
        if(!theWindingOrder){
            return {tempCC,tempDD,tempBB,tempAA};
        }
        //! Return cw.
        return {tempAA,tempBB,tempDD,tempCC};
    }

    //! To determine which side of the line from A=(x1,y1) to B=(x2,y2) a point P=(x,y) falls on you need to compute the value:-
    //! d=(x−x1)(y2−y1)−(y−y1)(x2−x1)
    //! If d<0 then the point lies on one side of the line, and if d>0 then it lies on the other side. If d=0 then the point lies exactly line.
    float pointSide2D(XPoint theStart, XPoint theEnd, XPoint thePoint){
        float x=thePoint.X();
        float y=thePoint.Y();
        float x1=theStart.X();
        float y1=theStart.Y();
        float x2=theEnd.X();
        float y2=theEnd.Y();
        return ((x-x1) * (y2-y1)) - ((y-y1) * (x2-x1));
    }

    //! XPoint rotated90Degrees=XOpenGLLine().rotate2D({0,0,0},{100,0,0},90);
    //! std::setprecision(3);
    //! std::cout<<std::fixed<<"rotated point x:"<<rotated90Degrees.X()<<" y:"<<rotated90Degrees.Y()<<std::endl;
    //! Output : rotated point x:-0.000004 y:-100.000000
    XPoint rotate2D(XPoint theCenter, XPoint thePointToRotate, float theRotateDegrees){
        float theRotateRad=toRadians(theRotateDegrees);
        XPoint theDist=thePointToRotate.Substract(theCenter);

        float theXRotated = cos(theRotateRad)* theDist.X() - sin(theRotateRad) * theDist.Y();
        float theYRotated = sin(theRotateRad)* theDist.X() + cos(theRotateRad) * theDist.Y();

        return {theCenter.X()+theXRotated,theCenter.Y()+theYRotated,thePointToRotate.Z()};
    }

    //! cross calculation
    //!   A-----------B------------C
    //! (Xa,Ya)     (Xb,Yb)      (Xc,Yc)

    //! AB = sqrt( (Xb - Xa)² + (Yb - Ya)² )
    //! AC = 1000

    //! Xc = Xa + (AC * (Xb - Xa) / AB)
    //! Yc = Ya + (AC * (Yb - Ya) / AB)
    XPoint interpolate3DLine(XPoint theStart, XPoint theEnd, float theOffset){
        //! LineLenght.
        float AB = sqrt( pow(theEnd.X() - theStart.X(),2) + pow(theEnd.Y() - theStart.Y(),2) + pow(theEnd.Z() - theStart.Z(),2) );
        float AC = theOffset;
        //! Interpolate new point from theStart along the line, given a direction point theEnd.
        float Xc = theStart.X() + (AC * (theEnd.X() - theStart.X()) / AB);
        float Yc = theStart.Y() + (AC * (theEnd.Y() - theStart.Y()) / AB);
        float Zc = theStart.Z() + (AC * (theEnd.Z() - theStart.Z()) / AB);
        //! Result.
        return {Xc,Yc,Zc};
    }
    //! Convert degrees to radian.
    float toRadians(float theValue){
        return theValue*(M_PI/180.0);
    }
    //! Calculate the intersection point between 2 lines.
    XPoint intersect2Lines(XPoint theFirstLineStart, XPoint theFirstLineEnd, XPoint theSecondLineStart, XPoint theSecondLineEnd){

        float x=0,y=0,z=theFirstLineEnd.Z();

        float startpoint_x0=theFirstLineStart.X();
        float startpoint_y0=theFirstLineStart.Y();
        float endpoint_x0=theFirstLineEnd.X();
        float endpoint_y0=theFirstLineEnd.Y();

        float startpoint_x1=theSecondLineStart.X();
        float startpoint_y1=theSecondLineStart.Y();
        float endpoint_x1=theSecondLineEnd.X();
        float endpoint_y1=theSecondLineEnd.Y();

        //! line 1
        float delta_y0 = endpoint_y0 - startpoint_y0;
        float delta_x0 = startpoint_x0 - endpoint_x0;
        float c0 = delta_y0 * startpoint_x0 + delta_x0 * startpoint_y0;

        //! line 2
        float delta_y1 = endpoint_y1 - startpoint_y1;
        float delta_x1 = startpoint_x1 - endpoint_x1;
        float c1 = delta_y1 * startpoint_x1 + delta_x1 * startpoint_y1;

        float determinant = delta_y0*delta_x1 - delta_y1*delta_x0;

        if (determinant==0){ //! The lines are parallel, return original endpoint of first line.
            x=endpoint_x0;
            y=endpoint_y0;
        } else  {
            x = (delta_x1*c0 - delta_x0*c1)/determinant;
            y = (delta_y0*c1 - delta_y1*c0)/determinant;
        }
        return {x,y,z};
    }

private:
    XOpenGL4PSurface *mySurface=new XOpenGL4PSurface();
};
#endif













































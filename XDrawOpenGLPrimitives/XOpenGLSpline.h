#ifndef XOPENGLSPLINE_H
#define XOPENGLSPLINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <XPoint.h>
#include <XOpenGLLine.h>
#include <XOpenGLCircle.h>

//! This needs libeigen3-dev. "sudo apt install libeigen3-dev".
#include <splinelib/cubic_spline.h>

using namespace Eigen;

class XOpenGLSpline {
public:
    //! Example cpu intensive :
    //! XOpenGLSpline().drawSpline({{0,0,0},{100,100,0}},5,20,{1,0,0,1},Window());
    XOpenGLSpline(){}

    //! Example, optimized for cpu :
    //! XOpenGLSpline *mySpline;
    //! mySpline=new XOpenGLSpline({{0,0,0},{100,100,0}},5,20,{1,0,0,1},Window());
    //! mySpline.drawSpline();
    XOpenGLSpline(std::vector<XPoint> thePointVec, float theWidth, int theDivision, XColor theColor, XWindow *theWindow) :
        myPointVec(thePointVec), myWidth(theWidth), myDivision(theDivision), myColor(theColor), myWindow(theWindow){

        //! Calculate the splinepath from the spline waypoints.
        mySplinePointVec=getSplinePath(myPointVec,myDivision);
        if(mySplinePointVec.size()<2){
            std::cout<<"incorrect data from function : XOpenGLSpline"<<std::endl;
        }
        mySurfaceVec=XOpenGLLine().getSurfaceVec(mySplinePointVec,myWidth,myColor,myWindow);
    }
    //! Draw the previous initialized splinepath.
    void drawSpline(){
        for(uint i=0; i<mySurfaceVec.size(); i++){
            mySurfaceVec.at(i)->draw();
        }
    }
    //! Draw a round point using modern openGL.
    void drawSpline(std::vector<XPoint> thePointVec, float theWidth, int theDivision, XColor theColor, XWindow *theWindow){
        if(thePointVec.size()<2){
            std::cout<<"incorrect data from function : XOpenGLSpline"<<std::endl;
            return;
        }
        XOpenGLLine().drawLineStrip(getSplinePath(thePointVec,theDivision), theWidth, theColor, theWindow);
    }
    //! Get the splinepath from the spline waypoint input. Division is the ammount of spline segments, cq spline resolution.
    std::vector<XPoint> getSplinePath(std::vector<XPoint> thePointVec, uint theDivision){
        //! Return as point or line.
        if(thePointVec.size()<3){
            return thePointVec;
        }

        std::vector<Vector3d> path; //! libspline input
        for(unsigned int i=0; i<thePointVec.size(); i++){
            path.push_back(Vector3d(thePointVec.at(i).X(),thePointVec.at(i).Y(),thePointVec.at(i).Z()));
        }
        CubicSpline c_spline(path,theDivision);
        c_spline.BuildSpline(path);
        std::vector<double> c_pathx(c_spline.GetPositionProfile().size());
        std::vector<double> c_pathy(c_spline.GetPositionProfile().size());
        std::vector<double> c_pathz(c_spline.GetPositionProfile().size());

        //! Get profile data for position, speed, acceleration, and curvature
        std::vector<XPoint> theSplinePointVec;
        std::vector<double> ti(c_spline.GetPositionProfile().size());
        for(unsigned int i=0;i<c_pathx.size();++i)
        {
            c_pathx[i] = c_spline.GetPositionProfile()[i].x();
            c_pathy[i] = c_spline.GetPositionProfile()[i].y();
            c_pathz[i] = c_spline.GetPositionProfile()[i].z();
            theSplinePointVec.push_back({float(c_pathx[i]),float(c_pathy[i]),float(c_pathz[i])});
        }
        return theSplinePointVec;
    }

private:
    std::vector<XPoint> myPointVec;
    std::vector<XPoint> mySplinePointVec;
    float myWidth;
    int myDivision;
    XColor myColor;
    XWindow *myWindow;
    std::vector<XOpenGL4PSurface*> mySurfaceVec;
};
#endif //

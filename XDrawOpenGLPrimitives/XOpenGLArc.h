#ifndef XOPENGLARC_H
#define XOPENGLARC_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <XPoint.h>
#include <XOpenGLLine.h>

class XOpenGLArc {
public:
    //! Input :
    //! Startpoint {x,y,z}, WayPoint {x,y,z}, Endpoint {x,y,z}.
    XOpenGLArc(){}

    XOpenGLArc(XPoint theStart, XPoint theWay, XPoint theEnd, float theWidth, int theDivision, XColor theColor, XWindow *theWindow) :
        myStart(theStart), myWay(theWay), myEnd(theEnd), myWidth(theWidth), myDivision(theDivision), myColor(theColor), myWindow(theWindow){
        //! Convert the way point input to a more universal input format.
        process_3P_Arc_to_AcadArc(myStart,myWay,myEnd,theWidth,theColor,theWindow);
        std::vector<XPoint> thePointVec=getArcPointVec(myCenter,myRadius,myRadianStart,myRadianEnd,myDivision);
        myLineStrip=new XOpenGLLine(thePointVec,myWidth,myColor,myWindow);
    }

    void draw_3P_Arc(){
        myLineStrip->drawLine();
    }

    void draw_3P_Arc(XPoint theStart, XPoint theWay, XPoint theEnd, float theWidth, int theDivision, XColor theColor, XWindow *theWindow){
        //! Convert the way point input to a more universal input format.
        process_3P_Arc_to_AcadArc(theStart,theWay,theEnd,theWidth,theColor,theWindow);
        //! Call a more standarized function now.
        drawOpenGLArc({myCenterX,myCenterY,myCenterZ},myRadius,myRadianStart,myRadianEnd,theWidth,theDivision,theColor,theWindow);
    }


private:

    XPoint myStart;
    XPoint myWay;
    XPoint myEnd;
    XPoint myCenter;
    float myWidth;
    int myDivision;
    XColor myColor;
    XWindow *myWindow;
    XOpenGLLine *myLineStrip;

    float myRadianStart, myRadianEnd, myRadius, myCenterX, myCenterY, myCenterZ;

    //! Draw universal openGL arc. Division is the ammount of linestrips, or segments of the arc.
    std::vector<XPoint> getArcPointVec(XPoint theCenter, float theRadius, float theAngleStartRad, float theAngleEndRad, int theDivision){
        myCenterZ=theCenter.Z();
        if (theAngleEndRad <= theAngleStartRad){  //! Avoid the start angle is bigger then the end angle value
            theAngleEndRad += 2*M_PI;
        }

        float arc_angle = theAngleEndRad - theAngleStartRad;
        float theta = arc_angle / float(theDivision - 1); //! Theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
        float tangetial_factor = tanf(theta);
        float radial_factor = cosf(theta);
        float x = theRadius * cosf(theAngleStartRad); //! We now start at the start angle
        float y = theRadius * sinf(theAngleStartRad);

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

    //! Draw universal openGL arc. Division is the ammount of linestrips, or segments of the arc.
    void drawOpenGLArc(XPoint theCenter, float theRadius, float theAngleStartRad, float theAngleEndRad, float theWidth, int theDivision, XColor theColor, XWindow *theWindow){
        XOpenGLLine().drawLineStrip(getArcPointVec(theCenter,theRadius,theAngleStartRad,theAngleEndRad,theDivision),theWidth,theColor,theWindow);
    }

    //! Transform arc given 3 circumfence points to : arc start angle, arc end angle, radius and center point.
    //! Arc preprocess. Calculate the arc centerpoint, arc start & arc end angles in radians.
    void process_3P_Arc_to_AcadArc(XPoint theStart, XPoint theWay, XPoint theEnd, float theWidth, XColor theColor, XWindow *theWindow){

        float X1=theStart.X();
        float Y1=theStart.Y();
        float X2=theWay.X();
        float Y2=theWay.Y();
        float X3=theEnd.X();
        float Y3=theEnd.Y();

        //! calculate 3 point circle... calculate xy center and radius..
        //! Get the perpendicular bisector of (x1, y1) and (x2, y2).
        float x1 = (X2 + X1) / 2;
        float y1 = (Y2 + Y1) / 2;
        float dy1 = X2 - X1;
        float dx1 = -(Y2 - Y1);

        //! Get the perpendicular bisector of (x2, y2) and (x3, y3).
        float x2 = (X3 + X2) / 2;
        float y2 = (Y3 + Y2) / 2;
        float dy2 = X3 - X2;
        float dx2 = -(Y3 - Y2);

        float endpoint_x0 = x1 + dx1;
        float endpoint_y0 = y1 + dy1;
        float endpoint_x1 = x2 + dx2;
        float endpoint_y1 = y2 + dy2;

        //! line 1
        float delta_y0 = endpoint_y0 - y1;
        float delta_x0 = x1 - endpoint_x0;
        float c0 = delta_y0 * x1 + delta_x0 * y1;
        //! line 2
        float delta_y1 = endpoint_y1 - y2;
        float delta_x1 = x2 - endpoint_x1;
        float c1 = delta_y1 * x2 + delta_x1 * y2;

        float determinant = delta_y0*delta_x1 - delta_y1*delta_x0;

        if (determinant == 0) //! The lines are parallel.
        {
            //! The lines are parallel
        }
        else  {
            myCenterX = (delta_x1*c0 - delta_x0*c1)/determinant;
            myCenterY = (delta_y0*c1 - delta_y1*c0)/determinant;
            float dx = myCenterX - X1;
            float dy = myCenterY - Y1;
            myRadius = sqrt(dx * dx + dy * dy);

            //! formula if arc is cw or ccw.. this is nice..
            //! To determine which side of the line from A=(x1,y1) to B=(x2,y2) a point P=(x,y) falls on you need to compute the value:-
            //! d=(x−x1)(y2−y1)−(y−y1)(x2−x1)
            //! If d<0 then the point lies on one side of the line, and if d>0 then it lies on the other side. If d=0 then the point lies exactly line.

            float xp = X3;
            float yp = Y3;
            float x1 = X1;
            float y1 = Y1;
            float x2 = X2;
            float y2 = Y2;

            float d = ((xp-x1)*(y2-y1))-((yp-y1)*(x2-x1));

            if(d > 0){
                myRadianStart = atan2(Y3-myCenterY, X3-myCenterX);
                myRadianEnd = atan2(Y1-myCenterY, X1-myCenterX);
                if (myRadianEnd < myRadianStart){  //! Avoid the start angle is bigger then the end angle value
                    myRadianEnd += 2*M_PI;
                }
            }
            if(d < 0){
                myRadianStart = atan2(Y1-myCenterY, X1-myCenterX);
                myRadianEnd = atan2(Y3-myCenterY, X3-myCenterX);
                if (myRadianEnd < myRadianStart){  //! Avoid the start angle is bigger then the end angle value
                    myRadianEnd += 2*M_PI;
                }
            }
            if(d == 0){ //! Draw a straight line.
                XOpenGLLine().drawLine(theStart,theEnd,theWidth,theColor,theWindow);
                return; //! End here.
            }
        }
        myCenter.setPoint({myCenterX,myCenterY,myCenterZ});
    }
};
# endif


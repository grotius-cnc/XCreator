#ifndef XOPENGLPRIMITIVE_H
#define XOPENGLPRIMITIVE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <XPoint.h>

class XOpenGLPrimitives {
public:
    XOpenGLPrimitives(){}

    //! Draw openGL line.
    void drawLine(XPoint theStart, XPoint theEnd, float theWidth, XColor theColor){
        glLineWidth(theWidth);
        glColor4f(theColor.Red(),theColor.Green(),theColor.Blue(),theColor.Alpha());
        glBegin(GL_LINES);
        glVertex3f(theStart.X(),theStart.Y(),theStart.Z());
        glVertex3f(theEnd.X(),theEnd.Y(),theEnd.Z());
        glEnd();
    }

    //! Draw openGL arc.
    void drawArc(float theStartAngleDeg, float theEndAngleDeg, float theXCenter, float theYCenter, float theRadius, float theWidth, int theDivision, XColor theColor){
        glLineWidth(theWidth);
        glColor4f(theColor.Red(),theColor.Green(),theColor.Blue(),theColor.Alpha());

        double angleStartRad = (theStartAngleDeg/360)*(2*M_PI); //! start angle
        if(theEndAngleDeg==360){theEndAngleDeg=0;} //! autocad degree problem..
        double angleEndRad = (theEndAngleDeg/360)*(2*M_PI);

        if (angleEndRad < angleStartRad){  //! Avoid the start angle is bigger then the end angle value
            angleEndRad += 2*M_PI;
        }

        float arc_angle = angleEndRad - angleStartRad;
        float theta = arc_angle / float(theDivision - 1); //! Theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
        float tangetial_factor = tanf(theta);
        float radial_factor = cosf(theta);
        float x = theRadius * cosf(angleStartRad); //! We now start at the start angle
        float y = theRadius * sinf(angleStartRad);

        glBegin(GL_LINE_STRIP); //! Since the arc is not a closed curve, this is a strip now
        for(int ii = 0; ii < theDivision; ii++)
        {
            glVertex2f(x + theXCenter, y + theYCenter);
            float tx = -y;
            float ty = x;
            x += tx * tangetial_factor;
            y += ty * tangetial_factor;
            x *= radial_factor;
            y *= radial_factor;
        }
        glEnd();
    }

    //! Draw openGL circle.
    void drawCircle(XPoint theCenter, float theRadius, float theWidth, XColor theColor){

    }

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


void process_3P_arc(double X1, double Y1, double X2, double Y2, double X3, double Y3){

    //! Calculate 3 point circle... calculate xy center and radius..
    //! Get the perpendicular bisector of (x1, y1) and (x2, y2).
    double x1 = (X2 + X1) / 2;
    double y1 = (Y2 + Y1) / 2;
    double dy1 = X2 - X1;
    double dx1 = -(Y2 - Y1);

    //! Get the perpendicular bisector of (x2, y2) and (x3, y3).
    double x2 = (X3 + X2) / 2;
    double y2 = (Y3 + Y2) / 2;
    double dy2 = X3 - X2;
    double dx2 = -(Y3 - Y2);

    double endpoint_x0 = x1 + dx1;
    double endpoint_y0 = y1 + dy1;
    double endpoint_x1 = x2 + dx2;
    double endpoint_y1 = y2 + dy2;

    //! Line 1
    double delta_y0 = endpoint_y0 - y1;
    double delta_x0 = x1 - endpoint_x0;
    double c0 = delta_y0 * x1 + delta_x0 * y1;
    //! Line 2
    double delta_y1 = endpoint_y1 - y2;
    double delta_x1 = x2 - endpoint_x1;
    double c1 = delta_y1 * x2 + delta_x1 * y2;

    double determinant = delta_y0*delta_x1 - delta_y1*delta_x0;

    if (determinant == 0) //! The lines are parallel.
    {
        //! The lines are parallel
    }
    else  {
        double x_center = (delta_x1*c0 - delta_x0*c1)/determinant;
        double y_center = (delta_y0*c1 - delta_y1*c0)/determinant;
        double dx = x_center - X1;
        double dy = y_center - Y1;
        double radius = sqrt(dx * dx + dy * dy);

        //! formula if arc is cw or ccw.. this is nice..
        //! To determine which side of the line from A=(x1,y1) to B=(x2,y2) a point P=(x,y) falls on you need to compute the value:-
        //! d=(x−x1)(y2−y1)−(y−y1)(x2−x1)
        //! If d<0 then the point lies on one side of the line, and if d>0 then it lies on the other side. If d=0 then the point lies exactly line.
        double d = ((X3-X1)*(Y2-Y1))-((Y3-Y1)*(X2-X1));
        double centerX, centerY;
        double startAngle, endAngle;

        if(d > 0){
            startAngle = 180/M_PI*atan2(Y3-y_center, X3-x_center);
            endAngle = 180/M_PI*atan2(Y1-y_center, X1-x_center);

            //! calculate arc midpoint..
            double radian_start = atan2(Y3-y_center, X3-x_center);
            double radian_end = atan2(Y1-y_center, X1-x_center);
            if (radian_end < radian_start){  //! Avoid the start angle is bigger then the end angle value
                radian_end += 2*M_PI;
            }
            double radian_mid = (radian_start+radian_end)/2;
            double rotate_x = cos(radian_mid)* radius - sin(radian_mid) * 0;
            double rotate_y = sin(radian_mid)* radius + cos(radian_mid) * 0;
            centerX = rotate_x + x_center;
            centerY = rotate_y + y_center;
        }
        if(d < 0){
            startAngle = 180/M_PI*atan2(Y1-y_center, X1-x_center);
            endAngle = 180/M_PI*atan2(Y3-y_center, X3-x_center);

            //! calculate arc midpoint..
            double radian_start = atan2(Y1-y_center, X1-x_center);
            double radian_end = atan2(Y3-y_center, X3-x_center);
            if (radian_end < radian_start){  //! Avoid the start angle is bigger then the end angle value
                radian_end += 2*M_PI;
            }
            double radian_mid = (radian_start+radian_end)/2;
            double rotate_x = cos(radian_mid)* radius - sin(radian_mid) * 0;
            double rotate_y = sin(radian_mid)* radius + cos(radian_mid) * 0;
            centerX = rotate_x + x_center;
            centerY = rotate_y + y_center;
        }
        if(d == 0){
            //! draw a straight line..
        }
    }
}




















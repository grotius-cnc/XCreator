#ifndef XPOLYGON_H
#define XPOLYGON_H

#include <vector>
#include <XPoint.h>

class XPolygon {
public:
    XPolygon(){}
    XPolygon(std::vector<XPoint> thePoints):myPointVec(thePoints){}

    void setColor(XColor theColor){
        myColor.setColor(&theColor);
        setLineTexture(myColor);
    }
    void setLineWidth(double theValue){
        myLineWidth=theValue;
    }
    double lineWidth(){
        return myLineWidth;
    }
    void setdrawContour(bool theValue){
        mydrawContour=theValue;
    }

    void clear(){
        myPointVec.clear();
    }
    std::vector<XPoint> pointVec(){
        return myPointVec;
    }
    void setPointVec(std::vector<XPoint> thePoints){
        myPointVec=thePoints;
    }
    void draw(){
        if(mydrawContour){
            glEnable(GL_TEXTURE_1D);
            glBindTexture(GL_TEXTURE_1D, myLineTexture);
            glLineWidth(myLineWidth);
            glBegin(GL_LINE_STRIP);
            for(unsigned int i=0; i<myPointVec.size(); i++){
                glVertex3d(myPointVec.at(i).X(),myPointVec.at(i).Y(),myPointVec.at(i).Z());
            }
            glEnd();
            glDisable(GL_TEXTURE_1D);
        }
    }
    bool isCw(){
        if(area()>0){
            return  true;
        }
        return 0;
    }
    bool isCcw(){
        if(area()<0){
            return  true;
        }
        return 0;
    }
    double area(){
        double sumX=0,sumY=0, area=0;
        myPointVec.push_back(myPointVec.front()); // Adds the first element to the back of the list to complete cycle.
        for(unsigned int i=0; i<myPointVec.size()-1; i++){
            sumX+=myPointVec.at(i).X()*myPointVec.at(i+1).Y();
            sumY+=myPointVec.at(i).Y()*myPointVec.at(i+1).X();
        }
        myPointVec.pop_back(); // Remove last element to restore the list.
        area=(sumX-sumY)/2;
        return area;
    }
    //! Centroid or center of mass.
    XPoint gravityPoint(){
        XPoint gravity;
        double x=0.0,y=0.0,z=0.0;
        for(unsigned int i=0; i<myPointVec.size(); i++){
            x+=myPointVec.at(i).X();
            y+=myPointVec.at(i).Y();
            z+=myPointVec.at(i).Z();
        }

        gravity.setX((x/myPointVec.size()));
        gravity.setY((y/myPointVec.size()));
        gravity.setZ((z/myPointVec.size()));
        return gravity;
    }
private:
    GLuint myLineTexture;
    void setLineTexture(XColor theColor){
        myLineTexture = 0;
        glGenTextures( 1, &myLineTexture );
        glBindTexture( GL_TEXTURE_1D, myLineTexture );
        glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        unsigned char buf[ 32 * 4 ];
        for( size_t i = 0; i < sizeof( buf ); i += 4 )
        {
            buf[ i+0 ] = theColor.Red();
            buf[ i+1 ] = theColor.Green();
            buf[ i+2 ] = theColor.Blue();
            buf[ i+3 ] = theColor.Alpha();
        }
        glTexImage1D( GL_TEXTURE_1D, 0, 4, sizeof( buf ) / 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, buf );
    }

    XColor myColor;
    double myLineWidth=1;
    bool mydrawContour=1;
    std::vector<XPoint> myPointVec;
};

#endif // XPOLYGON_H
























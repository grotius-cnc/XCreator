#ifndef XPOINT_H
#define XPOINT_H

/*
        Copyright (c) 2022 Skynet Cyberdyne

        This software is provided 'as-is', without any express or implied
        warranty. In no event will the authors be held liable for any damages
        arising from the use of this software.

        Permission is granted to anyone to use this software for any purpose,
        excluding commercial applications, and to alter it and redistribute it
        freely, subject to the following restrictions:

        1. The origin of this software must not be misrepresented; you must not
           claim that you wrote the original software. If you use this software
           in a product, an acknowledgment in the product documentation would
           be appreciated but is not required.

        2. Altered source versions must be plainly marked as such, and must not
           be misrepresented as being the original software.

        3. This notice may not be removed or altered from any source
           distribution.
*/

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <XColor.h>

class XPoint {
public:
    XPoint(){}
    XPoint(float x, float y):myX(x),myY(y){ }
    XPoint(float x, float y, float z):myX(x),myY(y),myZ(z){ }

    void setX(float x){
        myX=x;
    }
    void setY(float y){
        myY=y;
    }
    void setZ(float z){
        myZ=z;
    }
    void setXYZ(float x, float y, float z){
        myX=x;
        myY=y;
        myZ=z;
    }
    void setPoint(XPoint thePoint){
        myX=thePoint.X();
        myY=thePoint.Y();
        myZ=thePoint.Z();
    }
    XPoint Point(){
        return {myX,myY,myZ};
    }
    float X(){
        return myX;
    }
    float Y(){
        return myY;
    }
    float Z(){
        return myZ;
    }
    float Dist(XPoint *a, XPoint *b){
        return sqrt(pow(b->X()-a->X(),2)+pow(b->Y()-a->Y(),2+pow(b->Z()-a->Z(),2)));
    }
    float Dist(XPoint *thePoint){
        return sqrt(pow(thePoint->X()-myX,2)+pow(thePoint->Y()-myY,2+pow(thePoint->Z()-myZ,2)));
    }
    //! Substract this point from a given point.
    XPoint Substract(XPoint thePoint){
        return {myX-thePoint.X(),myY-thePoint.Y(),myZ-thePoint.Z()};
    }
    //! Substract is like A(xyz) minus B(xyz) or A(xyz)-B(xyz)
    XPoint Substract(XPoint a, XPoint b){
        return {a.X()-b.X(),a.Y()-b.Y(),a.Z()-b.Z()};
    }
    bool EqualToPoint(XPoint b){
        if(myX==b.X() && myY==b.Y() && myZ==b.Z()){
            return 1;
        }
        return 0;
    }
private:
    float myX=0.0, myY=0.0, myZ=0.0;
};

#endif // XPOINT_H

























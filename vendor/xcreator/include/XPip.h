#ifndef XPIP_H
#define XPIP_H

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

#include <XPoint.h>
#include <XSize.h>
#include <XMouse.h>

//! Check if a point is in a rectangular or polygon.
class XPip {
public:
    XPip(){}
    bool getPip(XPoint thePoint, XSize theSize){
        return Pip(thePoint,{{theSize.Origin().X(),theSize.Origin().Y(),theSize.Origin().Z()},
                             {theSize.Origin().X()+theSize.Width(),theSize.Origin().Y(),theSize.Origin().Z()},
                             {theSize.Origin().X()+theSize.Width(),theSize.Origin().Y()+theSize.Height(),theSize.Origin().Z()},
                             {theSize.Origin().X(),theSize.Origin().Y()+theSize.Height(),theSize.Origin().Z()}});
    }
    bool getPipFromMousePos(XSize theSize){
        return Pip(Mouse.Position()->Point(),{{theSize.Origin().X(),theSize.Origin().Y(),theSize.Origin().Z()},
                             {theSize.Origin().X()+theSize.Width(),theSize.Origin().Y(),theSize.Origin().Z()},
                             {theSize.Origin().X()+theSize.Width(),theSize.Origin().Y()+theSize.Height(),theSize.Origin().Z()},
                             {theSize.Origin().X(),theSize.Origin().Y()+theSize.Height(),theSize.Origin().Z()}});
    }
private:
    // Point in polygon algoritme.
    int Pip(XPoint thePoint, std::vector<XPoint> thePointVec){
        int n = thePointVec.size();
        int i, j, c = 0;
        for (i = 0, j = n-1; i < n; j = i++) {
            if ( ((thePointVec.at(i).Y()>thePoint.Y()) != (thePointVec.at(j).Y()>thePoint.Y())) &&
                 (thePoint.X() < (thePointVec.at(j).X()-thePointVec.at(i).X()) *
                  (thePoint.Y()-thePointVec.at(i).Y()) / (thePointVec.at(j).Y()-thePointVec.at(i).Y()) + thePointVec.at(i).X()) ){
                c = !c;
            }
        }
        if(c){
            return 1;
        }
        return 0;
    }
};

#endif // XPIP_H

#ifndef XSIZE_H
#define XSIZE_H

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
#include <XMouse.h>
#include <XWidget.h>
#include <XWindow.h>
//! getUnion(){}
#include <bits/stdc++.h>

// Class to define a XWidget size.
class XSize {
public:
    XSize(){}
    XSize(XPoint theOrigin, float theWidth, float theHeight):myWidth(theWidth),myHeight(theHeight){
        myOrigin->setPoint(theOrigin);
    }
    void setDimension(float theWidth, float theHeight){
        myWidth=theWidth;
        myHeight=theHeight;
    }
    void setWidth(float theWidth){
        myWidth=theWidth;
    }
    void setHeight(float theHeight){
        myHeight=theHeight;
    }
    void setSize(XSize theSize){
        myOrigin->setPoint(theSize.Origin());
        myWidth=theSize.Width();
        myHeight=theSize.Height();
        myRelativeOriginOffset->setPoint(theSize.RelativeOriginOffset());
        myRelativeWidthOffset=theSize.RelativeSizeOffset().first;
        myRelativeHeightOffset=theSize.RelativeSizeOffset().second;
    }
    void setSizeOffset(XPoint theValue){
        myOriginOffset->setPoint(theValue);
    }
    //! Set the size pointing to a size.
    void setSizeWithPointer(XSize *theSize){
        myOrigin->setPoint(theSize->Origin().Point());
        myWidth=theSize->Width();
        myHeight=theSize->Height();
        myRelativeOriginOffset->setPoint(theSize->RelativeOriginOffset());
        myRelativeWidthOffset=theSize->RelativeSizeOffset().first;
        myRelativeHeightOffset=theSize->RelativeSizeOffset().second;
    }
    XPoint Origin(){
        if(myReturnSizeIncludingRelativeOffsets){
            return {myOrigin->X()+myRelativeOriginOffset->X()+myOriginOffset->X(),
                        myOrigin->Y()+myRelativeOriginOffset->Y()+myOriginOffset->Y(),
                        myOrigin->Z()+myRelativeOriginOffset->Z()+myOriginOffset->Z()};
        } else {
            return {myOrigin->X()+myOriginOffset->X(),myOrigin->Y()+myOriginOffset->Y(),myOrigin->Z()+myOriginOffset->Z()};
        }
    }
    //! Set the relative offset for origin. The point values are in fact offset values.
    void setRelativeOriginOffset(XPoint thePoint){
        myRelativeOriginOffset->setPoint(thePoint);
        // std::cout<<"xsize set relative offset"<<std::endl;
    }
    //! Return the relative origin offset.
    XPoint RelativeOriginOffset(){
        return *myRelativeOriginOffset;
    }
    //! Set the relative offsets for relative width & relative height.
    void setRelativeSizeOffset(std::pair<float,float> theRelativeDimensionOffset){
        myRelativeWidthOffset=theRelativeDimensionOffset.first;
        myRelativeHeightOffset=theRelativeDimensionOffset.second;
    }
    std::pair<float,float> RelativeSizeOffset(){
        return {myRelativeWidthOffset,myRelativeHeightOffset};
    }
    //! Merge the relative origin offsets into the origin coordinates.
    void applyRelativeOriginOffset(){
        myOrigin->setX(myOrigin->X()+myRelativeOriginOffset->X());
        myOrigin->setY(myOrigin->Y()+myRelativeOriginOffset->Y());
        myOrigin->setZ(myOrigin->Z()+myRelativeOriginOffset->Z());
        myRelativeOriginOffset->setPoint({0,0,0});
        // std::cout<<"xsize applied relative origin offset"<<std::endl;
    }
    //! Merge the relative widht & height offsets into the width & height value of the widget.
    void applyRelativeSizeOffset(){
        myHeight=myHeight+myRelativeHeightOffset;
        myWidth=myWidth+myRelativeWidthOffset;
        myRelativeHeightOffset=0;
        myRelativeWidthOffset=0;
    }
    XPoint UpperRight(){
        return {myOrigin->X()+myWidth+myRelativeWidthOffset,myOrigin->Y(),myOrigin->Z()};
    }
    XPoint LowerRight(){
        return {myOrigin->X()+myWidth+myRelativeWidthOffset,myOrigin->Y()+myHeight+myRelativeHeightOffset,myOrigin->Z()};
    }
    XPoint LowerLeft(){
        return {myOrigin->X(),myOrigin->Y()+myHeight+myRelativeHeightOffset,myOrigin->Z()};
    }
    float Width(){
        return myWidth;
    }
    float Height(){
        return myHeight;
    }
    XSize Size(){
        if(myReturnSizeIncludingRelativeOffsets){
            return {{myOrigin->X()+myRelativeOriginOffset->X()+myOriginOffset->X(),
                            myOrigin->Y()+myRelativeOriginOffset->Y()+myOriginOffset->Y(),
                            myOrigin->Z()+myRelativeOriginOffset->Z()+myOriginOffset->Z()},myWidth,myHeight};
        } else {
            return {{myOrigin->X()+myOriginOffset->X(),
                            myOrigin->Y()+myOriginOffset->Y(),
                            myOrigin->Z()+myOriginOffset->Z()},myWidth,myHeight};
        }
    }

    XSize* SizePointer(){
        return this;
    }
    XSize SizeIncludeOffsets(){
        return {{myOrigin->X()+myRelativeOriginOffset->X()+myOriginOffset->X(),
                        myOrigin->Y()+myRelativeOriginOffset->Y()+myOriginOffset->Y(),
                        myOrigin->Z()+myRelativeOriginOffset->Z()+myOriginOffset->Z()},
            myWidth+myRelativeWidthOffset,
                    myHeight+myRelativeHeightOffset};
    }
    //! Return a 4-side smaller size formed by a margin value.
    XSize MarginSize(float theValue){
        return {{myOrigin->X()+theValue,myOrigin->Y()+theValue,myOrigin->Z()},myWidth-(2*theValue),myHeight-(2*theValue)};
    }
    //! Return the gravity point of a rectangular.
    XPoint GravityPoint(){
        return {float(myOrigin->X()+(0.5*myWidth)),float(myOrigin->Y()+(0.5*myHeight)),myOrigin->Z()};
    }

    //! if theSize intersects with this size, return the intersection size within this size. Return a union size.
    //! This code is modified from source:
    //! https://www.geeksforgeeks.org/perimeter-of-the-union-of-two-rectangles/
    //!
    /*
        XSize RSize;
        XSize ASize={{0,0,0},100,100};
        XSize BSize={{80,80,0},100,100};
        bool ok=BSize.getUnion(ASize,RSize);
    */

    bool getUnion(XSize theSize, XSize &theUnion){
        //! First rectangular.
        int x1=int(myOrigin->X());
        int y1=int(myOrigin->Y());
        //! lower right.
        int x2=int(myOrigin->X()+myWidth);
        int y2=int(myOrigin->Y()+myHeight);

        //! Second rectangular.
        int x3=int(theSize.Origin().X());
        int y3=int(theSize.Origin().Y());
        //! Lower right.
        int x4=int(theSize.Origin().X()+theSize.Width());
        int y4=int(theSize.Origin().Y()+theSize.Height());

        //! gives origin point
        //! of intersection rectangle
        int x5 = std::max(x1, x3);
        int y5 = std::max(y1, y3);

        //! gives lower-right point
        //! of intersection rectangle
        int x6 = std::min(x2, x4);
        int y6 = std::min(y2, y4);

        //! no intersection
        if (x5 > x6 || y5 > y6) {
             std::cout << "No intersection";
            return 0;
        }

        std::cout<<"resultSize Origin x:"<<x5<<" y:"<<y5<<" w:"<<x6-x5<<" h:"<<y6-y5<<std::endl;
        theUnion.setSize({{float(x5),float(y5),0},float(x6-x5),float(y6-y5)});
        return 1;
    }
    void setReturnSizeIncludingRelativeOffsets(bool theStatus){
        myReturnSizeIncludingRelativeOffsets=theStatus;
    }
    void printSize(std::string theForeWordComment){
        std::cout<<theForeWordComment<<" x:"<<myOrigin->X()<<" y:"<<myOrigin->Y()<<" z:"<<myOrigin->Z()<<" w:"<<myWidth<<" h:"<<myHeight<<std::endl;
    }

private:
    XPoint *myOrigin=new XPoint();
    XPoint *myOriginOffset=new XPoint();
    float myWidth=0;
    float myHeight=0;
    XPoint *myRelativeOriginOffset=new XPoint();
    float myRelativeWidthOffset=0, myRelativeHeightOffset=0;
    bool myReturnSizeIncludingRelativeOffsets=0;
};

#endif // XSIZE_H

#ifndef XMOUSE_H
#define XMOUSE_H

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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <XPoint.h>

class XMouse {
public:

    XMouse(){}
    void setMouseButtons(GLFWwindow* theWindow,int btn, int status, int spare){
        myWindowPointer=theWindow;
        myButton=btn;
        myStatus=status;
        mySpare=spare;

        // std::cout<<"status"<<status<<std::endl;

        if(btn==0 && status==1){
            myLeftMouseSnapShot->setPoint(Position()->Point());
            myLeftMousePressed=1;
            myLeftMouseDrag=1;
            // std::cout<<"LeftMouse pressed."<<std::endl;
        }
        if(btn==0 && status==0){
            myLeftMouseDrag=0;
            myLeftMousePressed=0;
            // std::cout<<"LeftMouse released."<<std::endl;
        }


        if(btn==2 && status==1){
            myMidMouseSnapShot->setPoint(Position()->Point());
            myMidMousePressed=1;
            myMidMouseDrag=1;
        }
        if(btn==2 && status==0){
            myMidMouseDrag=0;
            myMidMousePressed=0;
        }


        if(btn==1 && status==1){
            myRightMouseSnapShot->setPoint(Position()->Point());
            myRightMousePressed=1;
            myRightMouseDrag=1;
        }
        if(btn==1 && status==0){
            myRightMouseDrag=0;
            myRightMousePressed=0;
        }

    }
    void resetLeftMousePressed(){
        myLeftMousePressed=0;
    }
    void resetMidMousePressed(){
        myMidMousePressed=0;
    }
    void resetRightMousePressed(){
        myRightMousePressed=0;
    }
    void resetMousePressed(){
        myLeftMousePressed=0;
        myRightMousePressed=0;
        myMidMousePressed=0;
    }
    void setMouseScrollValue(GLFWwindow* theWindow, float theX, float theY){
        myWindowPointer=theWindow;
        myMouseScrollValueX=int(theX);
        myMouseScrollValueY=int(theY);
        // std::cout<<"mouse scrollvalue x:"<<myMouseScrollValueX<<std::endl;
        // std::cout<<"mouse scrollvalue y:"<<myMouseScrollValueY<<std::endl;
    }
    //! Used by special mouse, problably for xy combinations.
    int ScrollValueX(){
        if(!myScrolLock){
            return myMouseScrollValueX;
        }
        return 0;
    }
    //! Used by normal mouse, scrollValue.
    int ScrollValueY(){
        if(!myScrolLock){
            return myMouseScrollValueY;
        }
        return 0;
    }
    void resetMouseScrollValueXToZero(){
        myMouseScrollValueX=0;
    }
    void resetMouseScrollValueYToZero(){
        myMouseScrollValueY=0;
    }
    void setMousePositon(GLFWwindow* theWindow, XPoint *thePoint){
        myWindowPointer=theWindow;
        myPosition=thePoint;
    }
    void setMouseXPositon(float theX){
        myPosition->setX(theX);
    }
    void setMouseYPositon(float theY){
        myPosition->setY(theY);
    }
    XPoint* Position(){
        return myPosition;
    }
    bool isPressedLeftButton(){
        return myLeftMousePressed;
    }
    bool isPressedMidButton(){
        return myMidMousePressed;
    }
    bool isPressedRightButton(){
        return myRightMousePressed;
    }
    void setLeftMouseSnapshot(){
        myLeftMouseSnapShot->setPoint(myPosition->Point());
    }
    void setMidMouseSnapshot(){
        myMidMouseSnapShot->setPoint(myPosition->Point());
    }
    void setRightMouseSnapshot(){
        myRightMouseSnapShot->setPoint(myPosition->Point());
    }
    XPoint* LeftMouseSnapShot(){
        return myLeftMouseSnapShot;
    }
    XPoint* MidMouseSnapShot(){
        return myMidMouseSnapShot;
    }
    XPoint* RightMouseSnapShot(){
        return myRightMouseSnapShot;
    }
    //! Return the distance from left mouse snapshot to current mouse position.
    float DistLeftSnapshotCurrentMousePos(){
        return myLeftMouseSnapShot->Dist(myPosition);
    }
    //! Return the distance from mid mouse snapshot to current mouse position.
    float DistMidSnapshotCurrentMousePos(){
        return myMidMouseSnapShot->Dist(myPosition);
    }
    //! Return the xyz shift in XPoint format from left mouse snapshot to current mouse position.
    XPoint CoordinateShiftLeftSnapshotCurrentMousePos(){
        return {myPosition->X()-myLeftMouseSnapShot->X(), myPosition->Y()-myLeftMouseSnapShot->Y(), myPosition->Z()-myLeftMouseSnapShot->Z()};
    }
    //! Return the xyz shift in XPoint format from left mouse snapshot to current mouse position.
    XPoint CoordinateShiftMidSnapshotCurrentMousePos(){
        return {myPosition->X()-myMidMouseSnapShot->X(), myPosition->Y()-myMidMouseSnapShot->Y(), myPosition->Z()-myMidMouseSnapShot->Z()};
    }
    //! Return the xyz shift in XPoint format from left mouse snapshot to current mouse position.
    XPoint CoordinateShiftRightSnapshotCurrentMousePos(){
        return {myPosition->X()-myRightMouseSnapShot->X(), myPosition->Y()-myRightMouseSnapShot->Y(), myPosition->Z()-myRightMouseSnapShot->Z()};
    }
    //! Return the distance from right mouse snapshot to current mouse position.
    float DistRightSnapshotCurrentMousePos(){
        return myRightMouseSnapShot->Dist(myPosition);
    }
    // Glfw uses float for mousepos.
    float X(){
        return myPosition->X();
    }
    float Y(){
        return myPosition->Y();
    }
    float Z(){
        return myPosition->Z();
    }
    GLFWwindow* GlfwWindowPointer(){
        return myWindowPointer;
    }
    float Time(){
        return myTime;
    }
    void setTime(float theValue){
        myTime=theValue;
    }
    void setScrollLock(bool theStatus){
        myScrolLock=theStatus;
    }
    int Button(){
        return myButton;
    }
    int Status(){
        return myStatus;
    }
    int Spare(){
        return mySpare;
    }

private:
    GLFWwindow* myWindowPointer;
    float myTime;
    bool myLeftMousePressed=0;
    bool myMidMousePressed=0;
    bool myRightMousePressed=0;
    bool myLeftMouseDrag=0, myMidMouseDrag=0, myRightMouseDrag=0;
    bool myScrolLock=0;
    XPoint *myPosition=new XPoint();
    XPoint *myLeftMouseSnapShot=new XPoint();
    XPoint *myMidMouseSnapShot=new XPoint();
    XPoint *myRightMouseSnapShot=new XPoint();
    int myMouseScrollValueX=0, myMouseScrollValueY=0;
    int myButton;
    int myStatus;
    int mySpare;
    GLFWwindow* myNewWindow;
};
XMouse Mouse;
#endif // XMOUSE_H

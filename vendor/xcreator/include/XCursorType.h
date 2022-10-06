#ifndef XCURSORTYPE_H
#define XCURSORTYPE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <XWindow.h>

//! Global cursor data. The XCursor class will interact with this global data.
class XCursorType {
public:
    XCursorType(){}

    void setCursorType(uint theType){
        //! std::cout<<"theType:"<<theType<<std::endl;
        myCursorNr=theType;
    }
    //! Set the cursor locked.
    void setLock(bool theStatus){
        myLock=theStatus;
    }
    //! Is locked?
    bool isLock(){
        return myLock;
    }
    bool isArrowCursor(){
        if(myCursorNr==GLFW_ARROW_CURSOR){
            return 1;
        }
        return 0;
    }
    bool isIBeamCursor(){
        if(myCursorNr==GLFW_IBEAM_CURSOR){
            return 1;
        }
        return 0;
    }
    bool isCrosshairCursor(){
        if(myCursorNr==GLFW_CROSSHAIR_CURSOR){
            return 1;
        }
        return 0;
    }
    bool isHandCursor(){
        if(myCursorNr==GLFW_HAND_CURSOR){
            return 1;
        }
        return 0;
    }
    bool isHResizeCursor(){
        if(myCursorNr==GLFW_HRESIZE_CURSOR){
            return 1;
        }
        return 0;
    }
    bool isVResizeCursor(){
        if(myCursorNr==GLFW_VRESIZE_CURSOR){
            return 1;
        }
        return 0;
    }
    bool isDisabledCursor(){
        if(myCursorNr==GLFW_CURSOR_DISABLED){
            return 1;
        }
        return 0;
    }
    bool isHiddenCursor(){
        if(myCursorNr==GLFW_CURSOR_HIDDEN){
            return 1;
        }
        return 0;
    }
    bool isNormalCursor(){
        if(myCursorNr==GLFW_CURSOR_NORMAL){
            return 1;
        }
        return 0;
    }
    bool isCustomCursor(){
        if(myCursorNr==0){
            return 1;
        }
        return 0;
    }

private:
    uint myCursorNr=0;
    bool myLock=0;
};
XCursorType CursorType;

#endif // XCURSORTYPE_H

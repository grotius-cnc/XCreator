#ifndef XCURSOR_H
#define XCURSOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <XWindow.h>
#include <XCursorType.h>

//! Local cursor class. XCursorType is the global cursor class.
class XCursor {
public:
    //! Empty constuctor, set the XWindow afterwards.
    XCursor(){}
    //! Constructor setting the GLFWwindow pointer.
    XCursor(XWindow *theWindow):myWindow(theWindow){}

    //! Set window afterwards when using empty constructor.
    void setWindow(XWindow *theWindow){
        myWindow=theWindow;
    }
    //! Different types of cursors.	The regular arrow cursor shape.
    void setArrowCursor(){
        if(!CursorType.isLock()){
            createCursor(GLFW_ARROW_CURSOR);
            CursorType.setCursorType(GLFW_ARROW_CURSOR);
        }
    }
    //! The text input I-beam cursor shape.
    void setIBeamCursor(){
        if(!CursorType.isLock()){
            createCursor(GLFW_IBEAM_CURSOR);
            CursorType.setCursorType(GLFW_IBEAM_CURSOR);
        }
    }
    //! The crosshair shape.
    void setCrosshairCursor(){
        if(!CursorType.isLock()){
            createCursor(GLFW_CROSSHAIR_CURSOR);
            CursorType.setCursorType(GLFW_CROSSHAIR_CURSOR);
        }
    }
    //! The hand shape.
    void setHandCursor(){
        if(!CursorType.isLock()){
            createCursor(GLFW_HAND_CURSOR);
            CursorType.setCursorType(GLFW_HAND_CURSOR);
        }
    }
    //! The horizontal resize arrow shape.
    void setHResizeCursor(){
        if(!CursorType.isLock()){
            createCursor(GLFW_HRESIZE_CURSOR);
            CursorType.setCursorType(GLFW_HRESIZE_CURSOR);
        }
    }
    //! The vertical resize arrow shape.
    void setVResizeCursor(){
        if(!CursorType.isLock()){
            createCursor(GLFW_VRESIZE_CURSOR);
            CursorType.setCursorType(GLFW_VRESIZE_CURSOR);
        }
    }
    //! Create and loat a cursor from a image.
    void setCustomCursor(std::string theImagePath){
        if(!CursorType.isLock()){
            GLFWimage images[1];
            int width, height, channels;
            images[0].pixels=SOIL_load_image(theImagePath.c_str(),&width,&height,&channels,0);
            // std::cout<<"channels:"<<channels<<std::endl; // Output : 4 channels. // Rbga..
            images[0].height=width;
            images[0].width=height;
            myCursor = glfwCreateCursor(images, 0, 0);
            setCursor();
            CursorType.setCursorType(0);
        }
    }
    //! Switch back to the standard cursor.
    void revertToDefaultCursor(){
        if(!CursorType.isLock()){
            glfwSetCursor(myWindow->GlfwWindowPointer(), NULL);
            CursorType.setCursorType(GLFW_ARROW_CURSOR);
        }
    }
    //! Set the cursor hidden.
    void setCursorHidden(){
        if(!CursorType.isLock()){
            createCursor(GLFW_CURSOR_HIDDEN);
            CursorType.setCursorType(GLFW_CURSOR_HIDDEN);
        }
    }
    //! Set the cursor hidden.
    void setCursorDisabled(){
        if(!CursorType.isLock()){
            createCursor(GLFW_CURSOR_DISABLED);
            CursorType.setCursorType(GLFW_CURSOR_DISABLED);
        }
    }
    //! Set the cursor normal.
    void setCursorNormal(){
        if(!CursorType.isLock()){
            createCursor(GLFW_CURSOR_NORMAL);
            CursorType.setCursorType(GLFW_CURSOR_NORMAL);
        }
    }
    //! Set the cursor locked.
    void setLock(bool theStatus){
        CursorType.setLock(theStatus);
    }
    //! isLocked?
    bool isLock(){
        return CursorType.isLock();
    }

private:
    GLFWcursor* myCursor;
    XWindow *myWindow=new XWindow();

    void createCursor(int theShape){
        myCursor = glfwCreateStandardCursor(theShape);
        setCursor();
    }
    void setCursor(){
        glfwSetCursor(myWindow->GlfwWindowPointer(), myCursor);
    }
};
#endif

























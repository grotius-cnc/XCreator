#ifndef XWINDOW_H
#define XWINDOW_H

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
#include <iostream>
#include <XMouse.h>
#include <XKey.h>

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action){
        Key.setKey(window,key,-1);
    }
    // std::cout<<"Window:"<<window<<std::endl;
    // std::cout<<"key:"<<key<<std::endl;
    // std::cout<<"scancode:"<<scancode<<std::endl;
    // std::cout<<"action:"<<action<<std::endl;
    // std::cout<<"mods:"<<mods<<std::endl;
}

static void CharacterCallback(GLFWwindow* window, uint codepoint)
{
    Key.setKey(window,-1,codepoint);
    // std::cout<<"Window:"<<window<<std::endl;
    // std::cout<<(unsigned char)codepoint<<std::endl;
}

static void MousePosCallBack(GLFWwindow* window, double theXPos, double theYPos){
    XPoint *thePoint=new XPoint(float(theXPos),float(theYPos),0);
    Mouse.setMousePositon(window,thePoint);
    // std::cout<<"Window:"<<window<<"Mouxe x:"<<theXPos<<" y:"<<theYPos<<std::endl;
}

static void MouseButtonCallBack(GLFWwindow* window, int btn, int status, int spare){
    Mouse.setMouseButtons(window,btn,status,spare);
    // std::cout<<"Window:"<<window<<std::endl;
    // std::cout<<"MouseButton:"<<btn<<" status:"<<status<<std::endl;
}

static void ScrollCallBack(GLFWwindow* window, double theX, double theY){
    Mouse.setMouseScrollValue(window,theX,theY);
    // std::cout<<"Window:"<<window<<std::endl;
    // std::cout<<"MouseScroll x:"<<theX<<" y:"<<theY<<std::endl;
}

static void WindowCloseCallBack(GLFWwindow* window){

     std::cout<<"CLose callback."<<std::endl;
    // std::cout<<"MouseScroll x:"<<theX<<" y:"<<theY<<std::endl;
}

class XWindow {
public:
    XWindow(){};
    GLFWwindow* GlfwWindowPointer(){
        return myWindow;
    }
    float Width(){
        return myWidth;
    }
    float Height(){
        return myHeight;
    }
    void setWindowDimension(float theWidth, float theHeight){
        myWidth=theWidth;
        myHeight=theHeight;
    }
    void setWindowPointer(GLFWwindow *theWindow){
        myWindow=theWindow;
    }

private:
    std::string myName="Dialog";
    double myWidth, myHeight;
    GLFWwindow *myWindow;
};
#endif



















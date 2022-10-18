#ifndef XKEY_H
#define XKEY_H

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

#include <vector>
#include <iostream>

class XKey {
public:
    XKey(){ };

    void setKey(GLFWwindow* theWindow, int theKey, uint theScancode, int theAction, int theMods){ 
        myWindowPointer=theWindow;
        myKey=theKey;
        myTempKey=theKey;
        myScancode=theScancode;
        myAction=theAction;
        myMods=theMods;
        //! std::cout<<"myKey:"<<myKey<<std::endl;
        //! std::cout<<"myScancode:"<<myScancode<<std::endl;
    }
    void setChar(uint theChar){
        myChar=theChar;
    }
    uint Char(){
        uint r=myChar;
        myChar=-1; //! Reset.
        return r;
    }
    int Key(){
        return myTempKey;
    }
    int Action(){
        return myAction;
    }
    int Mods(){
        return myMods;
    }
    int ScanCode(){
        return myScancode;
    }
    int getGlfwCharKey(){
        int r=myScancode;
        return r;
    }
    void resetScanCode(){
        myScancode=-1;
    }
    void resetKey(){
        myKey=-1;
    }
    bool isGlfwEscapeKey(){
        if(myKey==256){
            return 1;
        }
        return 0;
    }
    bool isGlfwSpaceKey(){
        if(myKey==32){
            return 1;
        }
        return 0;
    }
    bool isGlfwTabKey(){
        if(myKey==258){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwEnterKey(){
        if(myKey==257){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwShiftKey(){
        if(myKey==340){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwControlKey(){
        if(myKey==341){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwBackSpaceKey(){
        if(myKey==259){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwRightKey(){
        if(myKey==262){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwLeftKey(){
        if(myKey==263){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwUpKey(){
        if(myKey==265){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwDownKey(){
        if(myKey==264){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwControlCKey(){
        if(myKey==67){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwControlVKey(){
        if(myKey==86){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwControlXKey(){
        if(myKey==88){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwControlAKey(){
        if(myKey==65){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwControlSKey(){
        if(myKey==83){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwControlZKey(){
        if(myKey==90){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwControlYKey(){ // Redo.
        if(myKey==89){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwDeleteKey(){
        if(myKey==261){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwPageDown(){
        if(myKey==267){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    bool isGlfwPageUp(){
        if(myKey==266){
            myKey=-1;
            return 1;
        }
        return 0;
    }
    GLFWwindow* GlfwWindowPointer(){
        return myWindowPointer;
    }
private:
    GLFWwindow* myWindowPointer;
    int myKey, myTempKey, myAction, myMods;
    uint myScancode;
    uint myChar=-1;
};
XKey Key;
#endif // XKEYS_H

#ifndef XOPENCASCADE_H
#define XOPENCASCADE_H

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

#include <XWidget.h>
#include <XSize.h>
#include <XRectangular.h>
#include <XChar.h>

#include <GlfwOcctView.h>

class XOpencascade : public XWidget {
public:
    //! Empty constructor. setWindow or parent afterwards.
    XOpencascade(){}
    //! The button has to be a member of a GLFWWindow. Mouse events, key events, are valid for the specific window. Otherwise a button press could be valid from other window.
    XOpencascade(XWindow *theWindow){
        this->setWindow(theWindow);
        myOcct->setWindow(theWindow->GlfwWindowPointer());
        myOcct->init();
    }

    //! Empty destructor.
    ~XOpencascade(){}
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XOpencascade";
    }
    //! Set the size of this widget. Size also handles the mouse & key events.
    void setSize(XSize theSize){
        mySize->setSize(theSize);
    }

    //! draw this widget. Eventually use xyz offsets, for example while dragging a widget.
    void draw(){
        //! Save the current scissor size to be restored at end of this function.
        myOcct->draw();
    }

private:
    XString *myString=new XString("Button");
    XSize *mySize=new XSize();
    GlfwOcctView *myOcct = new GlfwOcctView();
};
#endif




























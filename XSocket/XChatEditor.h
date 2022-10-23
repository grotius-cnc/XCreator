#ifndef XCHATEDITOR_H
#define XCHATEDITOR_H

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

#include <XWidget.h>
#include <XButton.h>
#include <XImage.h>
#include <XWindow.h>
#include <XMouse.h>
#include <XKey.h>
#include <XTemplate.h>
#include <XScissor.h>
#include <XTextEdit.h>

class XChatEditor : public XWidget {
public:
    //! Empty constructor.
    XChatEditor(XWindow *theWindow){
        this->setWindow(theWindow);
        setScissorWindow(theWindow);
    }
    //! Destructor.
    ~XChatEditor(){ }
    void setSize(XSize theSize){
        mySize->setSize(theSize.Size());
    }
    void init(){
        //! Class to populate the file dialog with content.
        myTextEdit=new XTextEdit(Window());
        addWidget(myTextEdit);
    }
    void draw(){
        //! Save the current scissor size to be restored at end of this function.
        saveScissorState();
        //! Set the scissor union size.
        setScissorUnion(ParentScissorSize(),mySize->Size());
        //! Set widget sizes.
        myTextEdit->setSize(mySize->Size());
        //! draw content.
        drawWidgetVec();
        //! Restore the scissor size.
        restoreScissorState();
    }
    //! Has command.
    bool hasCommand(){
        if(myTextEdit->Command().size()>0){
            return 1;
        }
        return 0;
    }
    //! The command.
    std::string Command(){
        return myTextEdit->Command();
    }
    void resetCommand(){
        myTextEdit->resetCommand();
    }
    void setText(std::string theText, XColor theColor){
        myTextEdit->setText(theText,theColor);
    }
private:
    std::string myDialogName="XChatEditor";
    XSize *mySize=new XSize();

    XTextEdit *myTextEdit;
};
#endif























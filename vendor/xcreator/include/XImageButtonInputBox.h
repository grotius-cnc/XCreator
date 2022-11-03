#ifndef XIMAGEBUTTONINPUTBOX_H
#define XIMAGEBUTTONINPUTBOX_H
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
#include <XImageButton.h>
#include <tinyfiledialogs.h>

//! A fully functional image button class.
//! This class is subclassed from the XImageButton class, therefore funtions like setSize are available from your main function,
//! wich calls the XImageButtonFileOpen class.
//!
//!     XImageButtonInputBox *myButton;
//!     myButton=new XImageButtonInputBox (Window());
//!     addWidget(myButton);
//!     drawWidgetVec();
//!
class XImageButtonInputBox : public XImageButton {
public:
    //! Empty constructor.
    XImageButtonInputBox(){}
    //! Constructor setting the GLFWwindow pointer and imagepath for the icon.
    XImageButtonInputBox(XWindow *theWindow){
        initImageButton(theWindow,"icons/oxygen/base/32x32/actions/view-list-tree.png",32,32);
    }
    //! Empty destructor.
    ~XImageButtonInputBox(){}
    //! Image button pressed event, forwarded to XImageButton class.
    bool isPressed(){
        if(isPressedPrivate()){
            //! Run the file open dialog.
            if(!runInputDialog()){
                std::cout<<"error input dialog"<<std::endl;
            }
            return 1;
        }
        return 0;
    }
    void setDialogName(std::string theDialogName){
        myDialogName=theDialogName;
    }
    void setDialogQuestion(std::string theQuestion){
        myQuestion=theQuestion;
    }
    //! Return input.
    std::string Result(){
        return myInput;
    }
private:
    std::string myInput="", myDialogName="Input Dialog", myQuestion="Input value or text";

    //! Vendor interface function.
    bool runInputDialog(){
        char const * lInput;
        lInput = tinyfd_inputBox(
            myDialogName.c_str(), myQuestion.c_str(), NULL);
        if (!lInput) return 0;
        myInput=lInput;
        return 1;
    }
};
#endif

#ifndef XIMAGEBUTTONMESSAGE_H
#define XIMAGEBUTTONMESSAGE_H
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
//!     XImageButtonMessage *myButton;
//!     myButton=new XImageButtonMessage (Window());
//!     addWidget(myButton);
//!     drawWidgetVec();
//!
class XImageButtonMessage : public XImageButton {
public:
    //! Empty constructor.
    XImageButtonMessage(){}
    //! Constructor setting the GLFWwindow pointer and imagepath for the icon.
    XImageButtonMessage(XWindow *theWindow){
        initImageButton(theWindow,"icons/oxygen/base/32x32/actions/dialog-ok-apply.png",32,32);
    }
    //! Empty destructor.
    ~XImageButtonMessage(){}
    //! Image button pressed event, forwarded to XImageButton class.
    bool isPressed(){
        if(isPressedPrivate()){
            //! Run the file open dialog.
            if(!runMessageDialog()){
                std::cout<<"error message dialog"<<std::endl;
            }
            return 1;
        }
        return 0;
    }
    void setDialogName(std::string theDialogName){
        myDialogName=theDialogName;
    }
    //! Set the message.
    void setMessage(std::string theMessage){
        myMessage=theMessage;
    }
private:
    std::string myDialogName="Message Dialog", myMessage="XCreator by Skynet Cyberdyne.\nTry another dialog.";

    //! Vendor interface function.
    bool runMessageDialog(){
        tinyfd_messageBox(
            myDialogName.c_str(),
            myMessage.c_str(),
            "ok",
            NULL, //! "error" to show as error dialog.
            0);
        return 1 ;
    }
};
#endif

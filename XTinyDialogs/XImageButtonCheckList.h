#ifndef XIMAGEBUTTONCHECKLIST_H
#define XIMAGEBUTTONCHECKLIST_H
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
#include <tinyfd_moredialogs.h>

//! A fully functional image button class.
//! This class is subclassed from the XImageButton class, therefore funtions like setSize are available from your main function,
//! wich calls the XImageButtonFileOpen class.
//!
//!     XImageButtonCheckList *myButton;
//!     myButton=new XImageButtonCheckList(Window());
//!     addWidget(myButton);
//!     drawWidgetVec();
//!
class XImageButtonCheckList : public XImageButton {
public:
    //! Empty constructor.
    XImageButtonCheckList(){}
    //! Constructor setting the GLFWwindow pointer and imagepath for the icon.
    XImageButtonCheckList(XWindow *theWindow){
        initImageButton(theWindow,"icons/Adwaita/16x16/legacy/format-justify-fill.png");
    }
    //! Empty destructor.
    ~XImageButtonCheckList(){}
    //! Image button pressed event, forwarded to XImageButton class.
    bool isPressed(){
        if(isPressedPrivate()){
            //! Run the file open dialog.
            if(!runCheckListDialog()){
                std::cout<<"error checklist dialog"<<std::endl;
            }
            return 1;
        }
        return 0;
    }
    void setDialogName(std::string theDialogName){
        myDialogName=theDialogName;
    }
    //! Return retul.
    std::string Result(){
        return myResult;
    }
private:
    std::string myDialogName="Checklist Dialog", myResult;

    //! Vendor interface function.
    int aNumOfOptions=4;
    char const * myOptions[5] = {"option a", "option b", "option c", "option d"};

    bool runCheckListDialog(){
        char * result = tinyfd_checklistDialog(
                    myDialogName.c_str(),
                    aNumOfOptions,
                    myOptions);
        myResult=result;
        return 1;
    }
};
#endif

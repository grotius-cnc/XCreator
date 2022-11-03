#ifndef XIMAGEBUTTONFILEOPEN_H
#define XIMAGEBUTTONFILEOPEN_H
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
//!     XImageButtonFileOpen *myButton;
//!     myButton=new XImageButtonFileOpen (Window());
//!     addWidget(myButton);
//!     drawWidgetVec();
//!
class XImageButtonFileOpen : public XImageButton {
public:
    //! Empty constructor.
    XImageButtonFileOpen(){}
    //! Constructor setting the GLFWwindow pointer and imagepath for the icon.
    XImageButtonFileOpen(XWindow *theWindow){
        initImageButton(theWindow,"icons/document-open.png",32,32);
    }
    //! Image button pressed event, forwarded to XImageButton class.
    bool isPressed(){
        if(isPressedPrivate()){
            //! Run the file open dialog.
            if(!fileOpen()){
                std::cout<<"error file dialog"<<std::endl;
            }
            return 1;
        }
        return 0;
    }
    void setDialogName(std::string theDialogName){
        myDialogName=theDialogName;
    }
    //! Return the path from the filedialog.
    std::string Result(){
        return myPath;
    }

    //! Empty destructor.
    ~XImageButtonFileOpen(){}

private:
    std::string myPath, myDialogName="File Open Dialog";
    char const * myFilterPatterns[2] = { "*.txt", "*.text"};

    //! Vendor interface function.
    int fileOpen(){
        char const * lTheOpenFileName;
        lTheOpenFileName = tinyfd_openFileDialog(
                myDialogName.c_str(),
                "",
                2,
                myFilterPatterns,
                NULL,
                0);

            if (! lTheOpenFileName)
            {
                tinyfd_messageBox(
                    "Error",
                    "Open file name is NULL",
                    "ok",
                    "error",
                    0);
                return 0 ;
            }
            myPath=lTheOpenFileName;
            return 1;
    }
};
#endif






































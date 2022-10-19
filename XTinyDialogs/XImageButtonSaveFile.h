#ifndef XIMAGEBUTTONSAVEFILE_H
#define XIMAGEBUTTONSAVEFILE_H
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
//!     XImageButtonSaveFile *myButton;
//!     myButton=new XImageButtonSaveFile (Window());
//!     addWidget(myButton);
//!     drawWidgetVec();
//!
class XImageButtonSaveFile : public XImageButton {
public:
    //! Empty constructor.
    XImageButtonSaveFile(){}
    //! Constructor setting the GLFWwindow pointer and imagepath for the icon.
    XImageButtonSaveFile(XWindow *theWindow){
        initImageButton(theWindow,"icons/Adwaita/16x16/legacy/document-save-as.png");
    }
    //! Empty destructor.
    ~XImageButtonSaveFile(){}
    //! Image button pressed event, forwarded to XImageButton class.
    bool isPressed(){
        if(isPressedPrivate()){
            //! Run the file open dialog.
            if(!runSaveFileDialog()){
                std::cout<<"error save file dialog"<<std::endl;
            }
            return 1;
        }
        return 0;
    }
    //! Set the dialog name.
    void setDialogName(std::string theDialogName){
        myDialogName=theDialogName;
    }
    //! Return the saved filename.
    std::string Result(){
        return mySaveFileName;
    }

private:
    std::string mySaveFileName, myDialogName="Save File Dialog";

    //! Vendor interface function.
    bool runSaveFileDialog(){
        char const * lTheSaveFileName;
        char const * lFilterPatterns[2] = { "*.txt", "*.text" };
        lTheSaveFileName = tinyfd_saveFileDialog(
            myDialogName.c_str(),
            "Document.txt",
            2,
            lFilterPatterns,
            NULL);

        if (! lTheSaveFileName)
        {
            tinyfd_messageBox(
                "Error",
                "Save file name is NULL",
                "ok",
                "error",
                1);
            return 0 ;
        }
        mySaveFileName=lTheSaveFileName;
        return 1;
    }
};
#endif

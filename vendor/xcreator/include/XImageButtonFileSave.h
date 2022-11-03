#ifndef XIMAGEBUTTONFILESAVE_H
#define XIMAGEBUTTONFILESAVE_H

#include <XImageButton.h>
#include <../tinyfiledialogs/tinyfiledialogs.h>

//! A fully functional image button class.
//! This class is subclassed from the XImageButton class, therefore funtions like setSize are available from your main function,
//! wich calls the XImageButtonFileOpen class.
//!
//!     XImageButtonSaveFile *myButton;
//!     myButton=new XImageButtonSaveFile (Window());
//!     addWidget(myButton);
//!     drawWidgetVec();
//!
class XImageButtonFileSave : public XImageButton {
public:
    //! Empty constructor.
    XImageButtonFileSave(){}
    //! Constructor setting the GLFWwindow pointer and imagepath for the icon.
    XImageButtonFileSave(XWindow *theWindow){
        initImageButton(theWindow,"icons/document-save-as.png",32,32);
    }
    //! Empty destructor.
    ~XImageButtonFileSave(){}
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

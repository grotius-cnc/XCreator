#ifndef XIMAGEBUTTONARRAY_H
#define XIMAGEBUTTONARRAY_H
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
//!     XImageButtonArray *myButton;
//!     myButton=new XImageButtonArray (Window());
//!     addWidget(myButton);
//!     drawWidgetVec();
//!
class XImageButtonArray : public XImageButton {
public:
    //! Empty constructor.
    XImageButtonArray(){}
    //! Constructor setting the GLFWwindow pointer and imagepath for the icon.
    XImageButtonArray(XWindow *theWindow){
        initImageButton(theWindow,"icons/Adwaita/16x16/legacy/address-book-new.png");
    }
    //! Empty destructor.
    ~XImageButtonArray(){}
    //! Image button pressed event, forwarded to XImageButton class.
    bool isPressed(){
        if(isPressedPrivate()){
            //! Run the file open dialog.
            if(!runDialog()){
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
    int aNumOfColumns=2;
    int aNumOfRows=2;
    char const * aColums[2] = {"left", "right"};
    char const * aCells[4] ={"a","b","c","d"};

    bool runDialog(){
        char * result =  tinyfd_arrayDialog(
                    myDialogName.c_str(),
                    aNumOfColumns,  //! 2
                    aColums,        //! {"Column 1","Column 2"}
                    aNumOfRows,     //! 2
                    aCells);        //! {"Row1 Col1","Row1 Col2","Row2 Col1","Row2 Col2"}
        if(!result){
            myResult="";
            return 0;
        }
        myResult=result;
        return 1;
    }
};
#endif





















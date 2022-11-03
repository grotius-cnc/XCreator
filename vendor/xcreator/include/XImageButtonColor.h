#ifndef XIMAGEBUTTONCOLOR_H
#define XIMAGEBUTTONCOLOR_H
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
class XImageButtonColor : public XImageButton {
public:
    //! Empty constructor.
    XImageButtonColor(){}
    //! Constructor setting the GLFWwindow pointer and imagepath for the icon.
    XImageButtonColor(XWindow *theWindow){
        initImageButton(theWindow,"icons/oxygen/base/32x32/actions/format-stroke-color.png",32,32);
    }
    //! Empty destructor.
    ~XImageButtonColor(){}

    //! Image button pressed event, forwarded to XImageButton class.
    bool isPressed(){
        if(isPressedPrivate()){
            //! Run the file open dialog.
            if(!runColorDialog()){
                std::cout<<"error color dialog"<<std::endl;
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
    //! Return hex color as string.
    std::string Result_Hex(){
        return myHexColor;
    }
    //! Return rgb colors as float.
    std::vector<float> Result_Rgb(){
        float r=float(myRgbColor[0])/255;  //! To openGl color.
        float g=float(myRgbColor[1])/255;
        float b=float(myRgbColor[2])/255;
        return {r,g,b};
    }
private:
    std::string myInput="", myDialogName="Color Dialog", myQuestion="Input value or text";
    char const * myHexColor;
    unsigned char myRgbColor[3];

    //! Vendor interface function.
    bool runColorDialog(){
        myHexColor = tinyfd_colorChooser(
            myDialogName.c_str(),
            "#FF0077",
            myRgbColor,
            myRgbColor);
        if (!myHexColor){
            return 0;
        }
        return 1;
    }
};
#endif














#ifndef XIMAGEBUTTON_H
#define XIMAGEBUTTON_H

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
#include <XText.h>
#include <XChar.h>
#include <XSize.h>
#include <XIcon.h>

class XImageButton : public XWidget {
public:
    //! Empty constructor.
    XImageButton(){}
    //! Constructor setting the GLFWwindow pointer and imagepath for the icon.
    XImageButton(XWindow *theWindow, std::string theImagePath):myImagePath(theImagePath){
        this->setWindow(theWindow);
        myBorder->setWindow(this->Window());
        myBackground->setWindow(this->Window());
        myIcon=new XIcon(Window(),myImagePath,{{0,0,0},15,15});
    }
    //! Empty destructor.
    ~XImageButton(){}
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XImageButton";
    }
    //! To initialize afterwards when using a empty constructor.
    void initImageButton(XWindow *theWindow, std::string theImagePath){
        this->setWindow(theWindow);
        myBorder->setWindow(this->Window());
        myBackground->setWindow(this->Window());
        myIcon=new XIcon(Window(),theImagePath,{{0,0,0},15,15});
    }
    //! To initialize afterwards when using a empty constructor.
    void initImageButton(XWindow *theWindow, std::string theImagePath, float theWidth, float theHeight){
        this->setWindow(theWindow);
        myBorder->setWindow(this->Window());
        myBackground->setWindow(this->Window());
        myIcon=new XIcon(Window(),theImagePath,{{0,0,0},theWidth,theHeight});
    }
    //! Set the size of this widget. Size also handles the mouse & key events.
    void setSize(XSize theSize){
        mySize->setSize(theSize);
    }
    //! Add a origin offset.
    void setSizeOffset(XPoint theValue){
        mySize->setSizeOffset(theValue);
    }
    //! Return the size.
    XSize Size(){
        return mySize->Size();
    }
    //! Set the size of the border.
    void setBorderSize(float theSize){
        myBorderSize=theSize;
    }
    //! Return the border size.
    float BorderSize(){
        return myBorderSize;
    }
    //! Return the size including relative offset values.
    XSize SizeIncludeOffsets(){
        return mySize->SizeIncludeOffsets();
    }
    //! Set relative offset.
    void setRelativeOriginOffset(XPoint theRelativeOffset){
        mySize->setRelativeOriginOffset(theRelativeOffset);
    }
    //! Return relative offset.
    XPoint RelativeOriginOffset(){
        return mySize->RelativeOriginOffset();
    }
    //! Set the relative size offset for relative width offset & relative height offset.
    void setRelativeSizeOffset(std::pair<float,float> theRelativeDimensionOffset){
        mySize->setRelativeSizeOffset(theRelativeDimensionOffset);
    }
    //! Return the relative size offset for relative width & relative height.
    std::pair<float,float> RelativeSizeOffset(){
        return mySize->RelativeSizeOffset();
    }
    //! Merge the relative origin offset into mySize and reset.
    void applyRelativeOriginOffset(){
        mySize->applyRelativeOriginOffset();
    }
    //! Merge the relative size offset into mySize and reset.
    void applyRelativeSizeOffset(){
        mySize->applyRelativeSizeOffset();
    }
    //! Set a color.
    void setColor(XColorType theColorType, XColor theColor){
        if(theColorType==XColorType::BackgroundColor){
            myBackgroundColor->setColor(theColor);
        }
        if(theColorType==XColorType::BorderColor){
            myBorderColor->setColor(theColor);
        }
        if(theColorType==XColorType::HoverColor){
            myHoverColor->setColor(theColor);
        }
        if(theColorType==XColorType::PressedColor){
            myPressedColor->setColor(theColor);
        }
        if(theColorType==XColorType::TextColor){
            myTextColor->setColor(theColor);
        }
    }
    XColor Color(XColorType theColorType){
        if(theColorType==XColorType::BackgroundColor){
            return myBackgroundColor->Color();
        }
        if(theColorType==XColorType::BorderColor){
            return myBorderColor->Color();
        }
        if(theColorType==XColorType::HoverColor){
            return myHoverColor->Color();
        }
        if(theColorType==XColorType::PressedColor){
            return myPressedColor->Color();
        }
        if(theColorType==XColorType::TextColor){
            return myTextColor->Color();
        }
        return {0,0,0,0};
    }
    bool isHovered(){
        return myIsHovered;
    }
    //! If this widget is subclassed, use the IsPressedPrivate to avoid duplicate name clashes.
    bool isPressed(){
        return isPressedPrivate();
    }
    bool isPressedPrivate(){
        bool r=myIsPressed;
        myIsPressed=false; //! Reset after request.
        return r;
    }
    //! draw this widget. Eventually use xyz offsets, for example while dragging a widget.
    void draw(){
//        myBorder->setSize(mySize->Size());
//        myBorder->setRelativeOriginOffset(mySize->RelativeOriginOffset());
//        myBorder->setRelativeSizeOffset(mySize->RelativeSizeOffset());
//        myBorder->setColor(XColorType::BorderColor,myBackgroundColor->Color());
//        myBorder->draw();

        myBackground->setSize(mySize->Size().MarginSize(myBorderSize));
//        myBackground->setRelativeOriginOffset(mySize->RelativeOriginOffset());
//        myBackground->setRelativeSizeOffset(mySize->RelativeSizeOffset());
//        myBackground->setColor(XColorType::BackgroundColor,myBackgroundColor->Color());
//        myBackground->draw();

        myIcon->setSize(mySize->Size().MarginSize(myBorderSize));
        myIcon->setRelativeOriginOffset(mySize->RelativeOriginOffset());
        myIcon->draw();

        if(myBackground->Event(XEventEnum::PressedLeft)){
            myIsPressed=true;
        }
        myBackground->Event(XEventEnum::ReleasedLeft);

        if(myBackground->Event(XEventEnum::Hovered)){
            myIsHovered=true;
        } else {
            myIsHovered=false;
        }

        //! draw content.
        for(uint i=0; i<WidgetVec().size(); i++){
            WidgetVec().at(i)->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            WidgetVec().at(i)->draw();
        }
    }
private:
    std::string myName;
    XString *myString=new XString("ImageButton");
    XSize *mySize=new XSize({{0,0,0},20,20});
    float myBorderSize=2;
    XColor //! Create colors and set standard values.
    *myBackgroundColor=new XColor(0.1,0.1,0.1,0.9),
    *myBorderColor=new XColor(0.0,0.0,0.0,0.9),
    *myHoverColor=new XColor(0.2,0.2,0.2,0.9),
    *myPressedColor=new XColor(0.3,0.3,0.3,0.9),
    *myTextColor=new XColor(1.0,1.0,1.0,0.9);
    XRectangular *myBorder=new XRectangular();
    XRectangular *myBackground=new XRectangular();
    std::string myImagePath;
    XIcon *myIcon;
    bool myIsPressed=0;
    bool myIsHovered=0;
};
#endif






















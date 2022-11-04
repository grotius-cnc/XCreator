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
        myText->setWindow(Window());
        setScissorWindow(Window());
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
        //! Save the current scissor size to be restored at end of this function.
        saveScissorState();

        myBackground->setSize(mySize->Size().MarginSize(myBorderSize));

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

        //! Set the scissor size, for designermode we include the relative offsets.
        if(hasParent()){
            setScissorUnion(ParentScissorSize(),myBackground->SizeIncludeOffsets());
        }

        //! Draw the button text.
        myText->setSize(mySize->Size());
        myText->setRelativeOriginOffset(mySize->RelativeOriginOffset());
        setCenterText();
        myString->setColorToString(myTextColor->Color());
        myText->drawText(*myString,0,myString->size(),int(myTextShiftX),int(myTextShiftY));

        //! draw content.
        for(uint i=0; i<WidgetVec().size(); i++){
            WidgetVec().at(i)->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            WidgetVec().at(i)->draw();
        }

        restoreScissorState();
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

    //! Text
    float myFontSize=13,myVerticalFontSpace=2,myTextShiftX=0,myTextShiftY=0;
    bool myCenterButtonTextX=1;
    bool myCenterButtonTextY=1;
    float myTextWidth;
    XText *myText=new XText();

    void setCenterText(){
        if(myCenterButtonTextX){
            myTextWidth=myText->StringWidth(myString->toStdString());  // Converse to pixelsize, see XText.h for more info.
            uint correction=4;
            myTextShiftX=((mySize->Size().Width()-myTextWidth)/2+correction);
        }
        if(myCenterButtonTextY){
            myTextShiftY=((mySize->Size().Height()-(myFontSize+myVerticalFontSpace))/2);
        }
    }
};
#endif






















#ifndef XVERTICALSLIDER_H
#define XVERTICALSLIDER_H

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
#include <XSize.h>
#include <XRectangular.h>
#include <XWidget.h>
#include <XButton.h>
#include <XImageButton.h>
#include <XCursor.h>

class XVerticalSlider : public XWidget {
public:
    //! Empty constructor.
    XVerticalSlider(){}
    //! Constructor setting the GLFWwindow pointer.
    XVerticalSlider(XWindow *theWindow){
        this->setWindow(theWindow);
        myBorder->setWindow(theWindow);
        myBackground->setWindow(theWindow);
        myButton->setWindow(theWindow);
        myCursor->setWindow(theWindow);
        myImageButtonDown=new XImageButton(theWindow,"icons/Adwaita/16x16/ui/pan-down-symbolic.symbolic.png");
        myImageButtonUp=new XImageButton(theWindow,"icons/Adwaita/16x16/ui/pan-up-symbolic.symbolic.png");
        setScissorWindow(theWindow);
    }
    //! Empty destructor.
    ~XVerticalSlider(){}
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XVerticalSlider";
    }
    //! Set the size of this widget. Size also handles the mouse & key events.
    void setSize(XSize theSize){
        mySize->setSize(theSize);
    }
    //! Add a origin offset.
    void setSizeOffset(XPoint theValue){
        mySize->setSizeOffset(theValue);
    }
    //! Set the size pointing to a size.
    void setSizeWithPointer(XSize *theSize){
        mySize=theSize;
    }
    //! Set the size of the border.
    void setBorderSize(float theSize){
        myBorderSize=theSize;
    }
    //! Return the border size.
    float BorderSize(){
        return myBorderSize;
    }
    //! Return the size.
    XSize Size(){
        return mySize->Size();
    }
    //! Return the size pointer, pointing to the size.
    XSize* SizePointer(){
        return mySize->SizePointer();
    }
    //! Return the size including relative offsets values.
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
    //! Set the string.
    void setString(std::string theString){
        myString->setStringFromStdString(theString);
    }
    //! Return text.
    std::string String(){
        return myString->toStdString();
    };
    void draw(){
        //! Save the current scissor size to be restored at end of this function.
        saveScissorState();

        myBorder->setSize(mySize->Size());
        myBorder->setRelativeOriginOffset(mySize->RelativeOriginOffset());
        myBorder->setRelativeSizeOffset(mySize->RelativeSizeOffset());
        myBorder->setColor(myBorderColor->Color());
        myBorder->draw();

        myBackground->setSize(mySize->Size().MarginSize(myBorderSize));
        myBackground->setRelativeOriginOffset(mySize->RelativeOriginOffset().Point());
        myBackground->setRelativeSizeOffset(mySize->RelativeSizeOffset());
        myBackground->setColor(myBackgroundColor->Color());
        myBackground->draw();

        //! Button height.
        myBh=mySize->Width()-myBorderSize-myBorderSize;
        //! Button width.
        myBw=myBh;
        //! Slider stroke.
        myStroke=mySize->Height()-myBorderSize-myBorderSize-myBh-myBh-myBh;

        myImageButtonDown->setSize({{mySize->Origin().X()+myBorderSize,mySize->Origin().Y()+mySize->Height()-myBorderSize-myBh,mySize->Origin().Z()}, myBw,myBh});
        myImageButtonDown->setRelativeOriginOffset(mySize->RelativeOriginOffset().Point());
        myImageButtonDown->setRelativeSizeOffset(mySize->RelativeSizeOffset());
        myImageButtonDown->setColor(XColorType::BackgroundColor,{0.4,0.4,0.4,0.9});
        myImageButtonDown->draw();

        myImageButtonUp->setSize({{mySize->Origin().X()+myBorderSize,mySize->Origin().Y()+myBorderSize,mySize->Origin().Z()}, myBw,myBh});
        myImageButtonUp->setRelativeOriginOffset(mySize->RelativeOriginOffset().Point());
        myImageButtonUp->setRelativeSizeOffset(mySize->RelativeSizeOffset());
        myImageButtonUp->setColor(XColorType::BackgroundColor,{0.4,0.4,0.4,0.9});
        myImageButtonUp->draw();

        //! Events.
        if(myButton->Event(XEventEnum::PressedLeft)){
            myPressedSliderUp=0;
            myPressedSliderMid=1;
            myPressedSliderDown=0;
            myHasEvent=1;
        }
        if(myImageButtonUp->Event(XEventEnum::PressedLeft)){
            myPosition-=myStep*myStroke;
            myPressedSliderUp=1;
            myPressedSliderMid=0;
            myPressedSliderDown=0;
            myHasEvent=1;
        }
        if(myImageButtonDown->Event(XEventEnum::PressedLeft)){
            myPosition+=myStep*myStroke;
            myPressedSliderUp=0;
            myPressedSliderMid=0;
            myPressedSliderDown=1;
            myHasEvent=1;
        }
        if(myButton->Event(XEventEnum::ReleasedLeft)){
            myPressedSliderMid=0;
            myHasEvent=0;
        }
        if(myImageButtonUp->Event(XEventEnum::ReleasedLeft)){
            myPressedSliderUp=0;
            myHasEvent=0;
        }
        if(myImageButtonDown->Event(XEventEnum::ReleasedLeft)){
            myPressedSliderDown=0;
            myHasEvent=0;
        }
        if(myButton->Event(XEventEnum::DraggedLeft)){
            myPosition=Mouse.Position()->Y()-(mySize->Origin().Y()+myBorderSize+myBh+(0.5*myBh));
            myPressedSliderUp=0;
            myPressedSliderDown=0;
        }
        if(myButton->Event(XEventEnum::Hovered)){
            myCursor->setHandCursor();
        } else
            if(myBackground->Event(XEventEnum::Hovered)){
                myCursor->revertToDefaultCursor();
            } else
                if(myImageButtonUp->Event(XEventEnum::Hovered)){
                    myCursor->revertToDefaultCursor();
                } else
                    if(myImageButtonDown->Event(XEventEnum::Hovered)){
                        myCursor->revertToDefaultCursor();
                    }
        if(myBackground->Event(XEventEnum::ScrollUp)){
            myPosition-=myStep*myStroke;
            myPressedSliderUp=0;
            myPressedSliderMid=0;
            myPressedSliderDown=0;
            myHasScrollEvent=1;
        }
        if(myBackground->Event(XEventEnum::ScrollDown)){
            myPosition+=myStep*myStroke;
            myPressedSliderUp=0;
            myPressedSliderMid=0;
            myPressedSliderDown=0;
            myHasScrollEvent=1;
        }
        //! Lower limits.
        if(myPosition<0){
            myPosition=0;
        }
        //! Upper limits.
        if(myPosition>myStroke){
            myPosition=myStroke;
        }
        myValue=myPosition/myStroke;

        myButton->setSize({{mySize->Origin().X()+myBorderSize, mySize->Origin().Y()+myBorderSize+myBh+myPosition, mySize->Origin().Z()},  myBw,myBh});
        myButton->setRelativeOriginOffset(mySize->RelativeOriginOffset().Point());
        myButton->setRelativeSizeOffset(mySize->RelativeSizeOffset());
        myButton->setColor(XColorType::BackgroundColor,{0.4,0.4,0.4,0.9});
        myButton->draw();

        //! Set the scissor size, for designermode we include the relative offsets.
        if(hasParent()){
            setScissorUnion(ParentScissorSize(),myBackground->SizeIncludeOffsets());
        }

        //! draw content.
        for(uint i=0; i<WidgetVec().size(); i++){
            WidgetVec().at(i)->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            WidgetVec().at(i)->draw();
        }
        //! Restore the scissor size.
        restoreScissorState();
    }

    //! Non virtual functions.
    void setValue(float theValue){
        myPosition=myStroke*theValue;
    }
    //! Return the value 0-1.
    float Value(){
        return myValue;
    }
    //! Set the step down between 0-1.
    void setStep(float theValue){
        myStep=theValue;
    }
    //! Set step up.
    void setStepUp(){
        myPosition-=myStep*myStroke;
    }
    //! Set step up.
    void setStepDown(){
        myPosition+=myStep*myStroke;
    }
    //! Event.
    bool hasEvent(){
        if(myHasScrollEvent){
            myHasScrollEvent=0;
            return 1;
        }
        if(myHasEvent){
            return 1;
        }
        return 0;
    }
    //! Left pressed.
    bool PressedSliderUp(){
        return myPressedSliderUp;
    }
    //! Mid pressed.
    bool PressedSliderMid(){
        return myPressedSliderMid;
    }
    //! Right pressed.
    bool PressedSliderDown(){
        return myPressedSliderDown;
    }
private:
    XSize *mySize=new XSize();
    float myBorderSize=1;
    XString *myString=new XString("Slider");

    XRectangular *myBackground=new XRectangular();
    XRectangular *myBorder=new XRectangular();
    XRectangular *myButton=new XRectangular();
    XImageButton *myImageButtonDown, *myImageButtonUp;

    //! Create colors and set standard values.
    XColor *myBackgroundColor=new XColor(0.1,0.1,0.1,0.9);
    XColor *myBorderColor=new XColor(0.0,0.0,0.0,0.9);
    XColor *myHoverColor=new XColor(0.2,0.2,0.2,0.9);
    XColor *myPressedColor=new XColor(0.3,0.3,0.3,0.9);
    XColor *myTextColor=new XColor(1.0,1.0,1.0,0.9);

    XCursor *myCursor=new XCursor();

    //! SLider position in pixels.
    float myPosition=0;
    //! Effective slider stroke.
    float myStroke=0;
    //! Step down, step up value.
    float myStep=0.1;
    //! Value 0-1.
    float myValue=0;
    //! Button height, width.
    float myBh=0, myBw=0;
    //! Event.
    bool myHasEvent=0, myHasScrollEvent=0;
    //! Status.
    bool myPressedSliderUp=0, myPressedSliderDown=0, myPressedSliderMid=0;
private:
};
#endif

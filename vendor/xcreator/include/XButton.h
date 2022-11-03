#ifndef XBUTTON_H
#define XBUTTON_H

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
#include <XColorAnimate.h>
#include <XCursor.h>

class XButton : public XWidget {
public:
    //! Empty constructor. setWindow or parent afterwards.
    XButton(){}
    //! The button has to be a member of a GLFWWindow. Mouse events, key events, are valid for the specific window. Otherwise a button press could be valid from other window.
    XButton(XWindow *theWindow){
        this->setWindow(theWindow);
        myBackground->setWindow(Window());
        myBorder->setWindow(Window());
        myText->setWindow(Window());
        setScissorWindow(theWindow);

        //! Widget hover and press animation.
        myAnimate=new XColorAnimate(20);
        myAnimate->setAnimationColorsStageOne(myBackgroundColor->Color(),myHoverColor->Color());
        myAnimate->setAnimationColorsStageTwo(myPressedColor->Color());
        myAnimate->setIncrementStageOne(0.05);
        myAnimate->setIncrementStageTwo(0.05);
        myAnimate->startTimer(1);

        myCursor=new XCursor(Window());
    }
    //! Empty destructor.
    ~XButton(){}
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XButton";
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
    //! Return the size.
    XSize Size(){
        return mySize->Size();
    }
    //! Return the size pointer, pointing to the size.
    XSize* SizePointer(){
        return mySize->SizePointer();
    }
    //! Set the size of the border.
    void setBorderSize(float theSize){
        myBorderSize=theSize;
    }
    //! Return the border size.
    float BorderSize(){
        return myBorderSize;
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
             myAnimate->setAnimationColorsStageOne(myBackgroundColor->Color(),myHoverColor->Color());
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
    //! draw this widget. Eventually use xyz offsets, for example while dragging a widget.
    void draw(){
        //! Save the current scissor size to be restored at end of this function.
        saveScissorState();

        //! Prevents widget mirroring.
        if(mySize->Width()>0 && mySize->Height()>0){

            //! If the text is not centered, start from the left edge.
            if(!myCenterButtonTextX){
                myTextShiftX=5;
            }

            myBorder->setSize(mySize->Size());
            myBorder->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            myBorder->setRelativeSizeOffset(mySize->RelativeSizeOffset());
            myBorder->setColor(myBorderColor->Color());

            myBackground->setSize(mySize->Size().MarginSize(myBorderSize));
            myBackground->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            myBackground->setRelativeSizeOffset(mySize->RelativeSizeOffset());
            //! myBackground->setColor(myBackgroundColor->Color());

            //! Update the animation thread.
            myAnimate->update();

            //! Check if mouse is inside the scisssor area.
            bool inScissorSize=XPip().getPipFromMousePos(ScissorSize().Size());

            if(Event(XEventEnum::PressedLeft) && inScissorSize){
                  myIsPressed=1;
            }
            if(Event(XEventEnum::ReleasedLeft)){
            }

            if(Event(XEventEnum::PressedLeftContinious) && inScissorSize){
                myAnimate->startAnimationStageTwo(1);
            } else {
                myAnimate->startAnimationStageTwo(0);
            }



            if(isHovered() && inScissorSize){
                myAnimate->AnimationStageOne(1);
                myCursor->revertToDefaultCursor();
            } else {
                myAnimate->AnimationStageOne(0);
            }

            //! Set the result of the animation color.
            myBackground->setColor(myAnimate->Color());

            //! Draw widget.
            myBorder->draw();
            myBackground->draw();

            //! Set the scissor size, for designermode we include the relative offsets.
            if(hasParent()){
                setScissorUnion(ParentScissorSize(),myBackground->SizeIncludeOffsets());
            }

            //! Draw the button text.
            myText->setSize(mySize->Size());
            myText->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            setCenterText();
            myString->setColorToString(myTextColor->Color());
            myText->drawText(*myString,0,myString->size(),int(myTextShiftX),int(myTextShiftY),false);

            //! Draw child widgets, if there are present.
            for(uint i=0; i<WidgetVec().size(); i++){
                WidgetVec().at(i)->setRelativeOriginOffset(mySize->RelativeOriginOffset());
                WidgetVec().at(i)->draw();
            }
        }
        //! Restore the scissor size.
        restoreScissorState();
    }
    //! Non virtual functions.
    void setCenterText(bool theStatusForX, bool theStatusForY){
        myCenterButtonTextX=theStatusForX;
        myCenterButtonTextY=theStatusForY;
    }
    void setColorToString(XColor theColor){
        myString->setColorToString(theColor);
    }
    void setColorToChar(XColor theColor, uint thePosition){
        myString->setCharColor(thePosition,theColor);
    }
    bool isPressed(){
        bool result=myIsPressed;
        myIsPressed=0;
        return result;
    }
    bool isHovered(){
        return Event(XEventEnum::Hovered);
    }

private:
    XString *myString=new XString("Button");
    XSize *mySize=new XSize();
    XColor //! Create colors and set standard values.
    *myBackgroundColor=new XColor(0.1,0.1,0.1,0.9),
    *myBorderColor=new XColor(0.0,0.0,0.0,0.9),
    *myHoverColor=new XColor(0.3,0.3,0.3,0.9),
    *myPressedColor=new XColor(0.6,0.6,0.6,0.9),
    *myTextColor=new XColor(1.0,1.0,1.0,0.9);
    XColorAnimate *myAnimate;
    float myFontSize=13,myVerticalFontSpace=2,myTextShiftX=0,myTextShiftY=0;
    bool myCenterButtonTextX=1;
    bool myCenterButtonTextY=1;
    float myTextWidth;
    XText *myText=new XText();
    XRectangular *myBackground=new XRectangular();
    XRectangular *myBorder=new XRectangular();
    float myBorderSize=2;
    bool myIsPressed=0;

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

    XCursor *myCursor;
};
#endif



























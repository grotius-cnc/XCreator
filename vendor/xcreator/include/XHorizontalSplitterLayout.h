#ifndef XHORIZONTALSPLITTERLAYOUT_H
#define XHORIZONTALSPLITTERLAYOUT_H

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
#include <XCursor.h>

class XHorizontalSplitterLayout : public XWidget {
public:
    //! Empty constructor. setWindow or parent afterwards.
    XHorizontalSplitterLayout(){}
    //! The button has to be a member of a GLFWWindow. Mouse events, key events, are valid for the specific window. Otherwise a button press could be valid from other window.
    XHorizontalSplitterLayout(XWindow *theWindow){
        this->setWindow(theWindow);
        myCursor->setWindow(theWindow);
        myBorder->setWindow(Window());
        myBackground->setWindow(Window());
        myLeftLayout->setWindow(Window());
        mySplitter->setWindow(Window());
        myRightLayout->setWindow(Window());
        setScissorWindow(theWindow);
    }
    //! Empty destructor.
    ~XHorizontalSplitterLayout(){}
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XHorizontalSplitterLayout";
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

        myBorder->setSize(mySize->Size());
        myBorder->setRelativeOriginOffset(mySize->RelativeOriginOffset());
        myBorder->setRelativeSizeOffset(mySize->RelativeSizeOffset());
        myBorder->setColor(myBorderColor->Color());
        myBorder->draw();

        myBackground->setSize(mySize->Size().MarginSize(myBorderSize));
        myBackground->setRelativeOriginOffset(mySize->RelativeOriginOffset());
        myBackground->setRelativeSizeOffset(mySize->RelativeSizeOffset());
        myBackground->setColor(myBackgroundColor->Color());
        myBackground->draw();

        myLeftLayout->setSize({{myBackground->Size().Origin().X(),
                                myBackground->Size().Origin().Y(),
                                myBackground->Size().Origin().Z()},float((myRatio*myBackground->Size().Width())-(0.5*mySplitterWidth)),myBackground->Size().Height()});
        myLeftLayout->setRelativeOriginOffset(mySize->RelativeOriginOffset());
        //! Only update size in height.
        myLeftLayout->setRelativeSizeOffset({0,mySize->RelativeSizeOffset().second});
        myLeftLayout->setColor({0.1,0.0,0.0,0.9});

        mySplitter->setSize({{myLeftLayout->Size().Origin().X()+myLeftLayout->Size().Width(),
                              myBackground->Size().Origin().Y(),
                              myBackground->Size().Origin().Z()},mySplitterWidth,myBackground->Size().Height()});
        mySplitter->setRelativeOriginOffset(mySize->RelativeOriginOffset());
        //! Only update size in height.
        mySplitter->setRelativeSizeOffset({0,mySize->RelativeSizeOffset().second});
        mySplitter->setColor({0.6,0.6,0.6,0.9});
        mySplitter->draw();

        myRightLayout->setSize({{  mySplitter->Size().Origin().X()+mySplitter->Size().Width(),
                                   myBackground->Size().Origin().Y(),
                                   myBackground->Size().Origin().Z()},myBackground->Size().Width()-mySplitter->Size().Width()-myLeftLayout->Size().Width(),myBackground->Size().Height()});
        myRightLayout->setRelativeOriginOffset(mySize->RelativeOriginOffset());
        //! Only update size in height.
        myRightLayout->setRelativeSizeOffset({0,mySize->RelativeSizeOffset().second});
        myRightLayout->setColor({0.1,0.0,0.0,0.9});

        //! Event cycle.
        if(mySplitter->Event(XEventEnum::PressedLeft)){}
        if(mySplitter->Event(XEventEnum::ReleasedLeft)){}
        if(mySplitter->Event(XEventEnum::DraggedLeft)){
            float myPosition=Mouse.Position()->X()-(myBackground->Size().Origin().X());
            myRatio=myPosition/myBackground->Size().Width();
            if(myRatio<0){
                myRatio=0.0;
            }
            if(myRatio>1){
                myRatio=1.0;
            }
            myIsDragged=true;
        } else {
            myIsDragged=false;
        }

        //! Set the cursor type at a splitter event.
        if(mySplitter->Event(XEventEnum::Hovered) || mySplitter->Event(XEventEnum::DraggedLeft)){
            //! Set the cursor. Adding non nervous limits.
            if((Mouse.Position()->Y()>mySplitter->Size().Origin().Y()+5) && (Mouse.Position()->Y()<mySplitter->Size().Origin().Y()+mySplitter->Size().Height()-5)){
                myCursor->setHResizeCursor();
            }
        }

        //! Set the scissor size, for designermode we include the relative offsets.
        if(hasParent()){
            setScissorUnion(ParentScissorSize(),myBackground->SizeIncludeOffsets());
        }

        //! When a widget is added, determine using the left or right layout.
        for(uint i=0; i<WidgetVec().size(); i++){
            if(i==0){
                WidgetVec().at(i)->setSize(myLeftLayout->Size());
            }
            if(i==1){
                //! Prevent bad behaviour when the width=0;
                WidgetVec().at(i)->setSize(myRightLayout->Size());
            }
        }

        //! Draw child widgets, if there are present.
        for(uint i=0; i<WidgetVec().size(); i++){
            WidgetVec().at(i)->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            WidgetVec().at(i)->draw();
        }
        //! Restore the scissor size.
        restoreScissorState();
    }
    //! Non virtual functions.
    //! Set the splitter size.
    void setSplitterWidth(float theValue){
        mySplitterWidth=theValue;
    }
    //! Set the left to right layout ratio from 0-1.
    void setLayoutRatio(float theValue){
        myRatio=theValue;
    }
    //! Is dragged?
    bool isDragged(){
        return myIsDragged;
    }

private:
    XString *myString=new XString("XHorizontalSplitterLayout");
    XSize *mySize=new XSize();
    XColor //! Create colors and set standard values.
    *myBackgroundColor=new XColor(0.1,0.1,0.1,0.9),
    *myBorderColor=new XColor(0.0,0.0,0.0,0.9),
    *myHoverColor=new XColor(0.3,0.3,0.3,0.9),
    *myPressedColor=new XColor(0.6,0.6,0.6,0.9),
    *myTextColor=new XColor(1.0,1.0,1.0,0.9);

    XRectangular *myBorder=new XRectangular();
    float myBorderSize=2;
    XRectangular *myBackground=new XRectangular();
    XRectangular *mySplitter=new XRectangular();
    float mySplitterWidth=5;
    XRectangular *myLeftLayout=new XRectangular();
    XRectangular *myRightLayout=new XRectangular();
    //! Ratio left to right from 0-1.
    float myRatio=0.5;
    XCursor *myCursor=new XCursor();

    bool myIsDragged=0;

    //! Event lock for child members.
    bool myChildEventLock=0;
};
#endif

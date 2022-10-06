#ifndef XSTACKEDFRAME_H
#define XSTACKEDFRAME_H

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
#include <XImageButton.h>

class XStackedFrame : public XWidget {
public:
    //! Empty constructor. setWindow or parent afterwards.
    XStackedFrame(){}
    //! The button has to be a member of a GLFWWindow. Mouse events, key events, are valid for the specific window. Otherwise a button press could be valid from other window.
    XStackedFrame(XWindow *theWindow){
        this->setWindow(theWindow);
        myBackground->setWindow(Window());
        myBorder->setWindow(Window());
        setScissorWindow(theWindow);
        myCursor=new XCursor(Window());
        myImageButtonStackPrevious=new XImageButton(Window(),"icons/Adwaita/16x16/ui/pan-start-symbolic.symbolic.png");
        myImageButtonStackNext=new XImageButton(Window(),"icons/Adwaita/16x16/ui/pan-end-symbolic.symbolic.png");
    }
    //! Empty destructor.
    ~XStackedFrame(){}
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XStackedFrame";
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

        //! Prevents widget mirroring.
        if(mySize->Width()>0 && mySize->Height()>0){

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


            myImageButtonStackPrevious->setSize({{myBackground->Size().Origin().X()+myBackground->Size().Width()-40,
                                                  myBackground->Size().Origin().Y()+5,
                                                  myBackground->Size().Origin().Z()},16,16});
            myImageButtonStackPrevious->setRelativeOriginOffset(mySize->RelativeOriginOffset());

            myImageButtonStackNext->setSize({{myBackground->Size().Origin().X()+myBackground->Size().Width()-20,
                                              myBackground->Size().Origin().Y()+5,
                                              myBackground->Size().Origin().Z()},16,16});
            myImageButtonStackNext->setRelativeOriginOffset(mySize->RelativeOriginOffset());

            //! Event cycle.
            if(myImageButtonStackPrevious->Event(XEventEnum::PressedLeft)){
                myStackIndexNr--;
                std::cout<<"stack previous."<<std::endl;
                //! Check stackIndexNr limits.
                if(myStackIndexNr<0){
                    myStackIndexNr=0;
                }
            }
            if(myImageButtonStackPrevious->Event(XEventEnum::ReleasedLeft)){}

            if(myImageButtonStackNext->Event(XEventEnum::PressedLeft)){
                myStackIndexNr++;
                std::cout<<"stack next."<<std::endl;
                //! Check stackIndexNr limits.
                if(myStackIndexNr>int(WidgetVec().size()-1)){
                    myStackIndexNr=WidgetVec().size()-1;
                }
            }
            if(myImageButtonStackNext->Event(XEventEnum::ReleasedLeft)){}

            //! When the XStackedFrame buttons are hovered, lock the underlying child widget events.
            if(myImageButtonStackPrevious->Event(XEventEnum::Hovered) || myImageButtonStackNext->Event(XEventEnum::Hovered)){
                if(WidgetVec().size()>0){
                    WidgetVec().at(myStackIndexNr)->setEventLock(1);
                }
            } else {
                 if(WidgetVec().size()>0){
                         WidgetVec().at(myStackIndexNr)->setEventLock(0);
                 }
            }

            //! Set the scissor size, for designermode we include the relative offsets.
            if(hasParent()){
                setScissorUnion(ParentScissorSize(),myBackground->SizeIncludeOffsets());
            }

            //! Draw child widgets, if there are present. Size child to fit the background.
            //! Normally we should draw the ChildVec, now we just draw one child.
            if(WidgetVec().size()>0){
                WidgetVec().at(myStackIndexNr)->setRelativeOriginOffset(mySize->RelativeOriginOffset());
                WidgetVec().at(myStackIndexNr)->setSize(myBackground->Size());
                WidgetVec().at(myStackIndexNr)->draw();
            }

            //! After the child widgets are drawed. Revert to standard cursor when the imagebuttons are hovered.
            if(myImageButtonStackPrevious->Event(XEventEnum::Hovered)){
                myCursor->revertToDefaultCursor();
            }
            if(myImageButtonStackNext->Event(XEventEnum::Hovered)){
                myCursor->revertToDefaultCursor();
            }

            //! After the childs widgets are drawed, show the stack previous and forward button on top of the widget.
            myImageButtonStackPrevious->draw();
            myImageButtonStackNext->draw();
        }
        //! Restore the scissor size.
        restoreScissorState();
    }
    //! Non virtual functions.

private:
    XString *myString=new XString("StackedFrame");
    XSize *mySize=new XSize();
    XColor //! Create colors and set standard values.
    *myBackgroundColor=new XColor(0.1,0.1,0.1,0.9),
    *myBorderColor=new XColor(0.0,0.0,0.0,0.9),
    *myHoverColor=new XColor(0.3,0.3,0.3,0.9),
    *myPressedColor=new XColor(0.6,0.6,0.6,0.9),
    *myTextColor=new XColor(1.0,1.0,1.0,0.9);
    XColorAnimate *myAnimate;
    XRectangular *myBackground=new XRectangular();
    XRectangular *myBorder=new XRectangular();
    XImageButton *myImageButtonStackPrevious, *myImageButtonStackNext;
    float myBorderSize=4;
    XCursor *myCursor;
    int myStackIndexNr=0;
};
#endif



























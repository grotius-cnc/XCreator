#ifndef XVERTICALLAYOUT_H
#define XVERTICALLAYOUT_H

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
#include <XPip.h>

//! A XWidget containing a XSize.
class XVerticalLayout : public XWidget {
public:
    //! Empty constructor. setWindow or parent afterwards.
    XVerticalLayout(){}
    //! Constructor setting the GLFWwindow pointer.
    XVerticalLayout(XWindow *theWindow){
        this->setWindow(theWindow);
        myBorder->setWindow(theWindow);
        myBackground->setWindow(theWindow);
        setScissorWindow(theWindow);
    }
    //! Empty destructor.
    ~XVerticalLayout(){}
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XVerticalLayout";
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
    //! Stretch to parent widget.
    void stretchToParent(bool theValue){
        myStrechToParent=theValue;
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
    //! Request current color.
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
    void draw(){
        //! Save the current scissor size to be restored at end of this function.
        saveScissorState();

        //! Event cycle.
        if(Event(XEventEnum::PressedMid)){
             myStrechToParent=!myStrechToParent;
        }
        if(Event(XEventEnum::ReleasedMid)){
        }

        //! Always set a layout size to fit Parent Size, except when its dragged in general.
        if(myStrechToParent){
            mySize->setSize(Parent()->Size().MarginSize(myMargin));
            mySize->setRelativeOriginOffset(Parent()->RelativeOriginOffset());
            mySize->setRelativeSizeOffset(Parent()->RelativeSizeOffset());
        }

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

        //* Draw childs as vertical layout.
        //! Short notations:
        //! relative height rh.
        //! relative width rw.
        //! relative size offset height rsow.
        //! relative size offset height rsoh.
        float x,y,z,w,h;
        //! Short notation size s.
        uint s=WidgetVec().size();

        x=mySize->Origin().X()+myMargin+mySize->RelativeOriginOffset().X();
        y=mySize->Origin().Y()+myMargin+mySize->RelativeOriginOffset().Y();
        z=mySize->Origin().Z();
        w=mySize->Width()-myMargin-myMargin+mySize->RelativeSizeOffset().first;
        h=mySize->Height()-myMargin-myMargin+mySize->RelativeSizeOffset().second;

        //! Set the scissor size, for designermode we include the relative offsets.
        if(hasParent()){
            setScissorUnion(ParentScissorSize(),myBackground->Size());
        }

        //! draw content.
        for(uint i=0; i<WidgetVec().size(); i++){
            WidgetVec().at(i)->setSize({{x,y,z},w,h/s});
            y+=h/s;
            WidgetVec().at(i)->draw();
        }

        //! Restore the scissor size.
        restoreScissorState();
    }
private:
    XSize *mySize=new XSize();
    XColor //! Create colors and set standard values.
    *myBackgroundColor=new XColor(0.1,0.1,0.1,0.9),
    *myBorderColor=new XColor(0.0,0.0,0.0,0.9),
    *myHoverColor=new XColor(0.2,0.2,0.2,0.9),
    *myPressedColor=new XColor(0.3,0.3,0.3,0.9),
    *myTextColor=new XColor(1.0,1.0,1.0,0.9);
    XRectangular *myBackground=new XRectangular();
    XRectangular *myBorder=new XRectangular();
    float myBorderSize=2;
    float myMargin=5;
    bool myStrechToParent=0;
};

#endif


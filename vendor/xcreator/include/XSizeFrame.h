#ifndef XSIZEFRAME_H
#define XSIZEFRAME_H

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
#include <XFrame.h>
#include <XRectangular.h>
#include <XButton.h>
#include <XHorizontalSlider.h>
#include <XVerticalSlider.h>
#include <XScissor.h>

//! A XWidget containing a XSize.
class XSizeFrame : public XWidget {
public:
    //! Empty constructor. setWindow or parent afterwards.
    XSizeFrame(){}
    //! Constructor setting the GLFWwindow pointer.
    XSizeFrame(XWindow *theWindow){
        this->setWindow(theWindow);
        myBackground->setWindow(theWindow);
        myBorder->setWindow(theWindow);
        myHorizontalSlider=new XHorizontalSlider(theWindow);
        myVerticalSlider=new XVerticalSlider(theWindow);
        setScissorWindow(theWindow);
    }
    //! Empty destructor.
    ~XSizeFrame(){}
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XSizeFrame";
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
    //! Set the size of the border.
    void setBorderSize(float theSize){
        myBorderSize=theSize;
    }
    //! Return the border size.
    float BorderSize(){
        return myBorderSize;
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
    void draw(){
        //! Save the current scissor size to be restored at end of this function.
        saveScissorState();

        //! Prevents widget mirroring.
        if(mySize->Width()>18 && mySize->Height()>18){

            myBorder->setSize(mySize->Size());
            myBorder->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            myBorder->setRelativeSizeOffset(mySize->RelativeSizeOffset());
            myBorder->setColor(myBorderColor->Color());

            myBackground->setSize(mySize->Size().MarginSize(myBorderSize));
            myBackground->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            myBackground->setRelativeSizeOffset(mySize->RelativeSizeOffset());
            myBackground->setColor(myBackgroundColor->Color());

            if(myBorder->Event(XEventEnum::PressedLeft)){}
            if(myBorder->Event(XEventEnum::ReleasedLeft)){}
            if(myBorder->Event(XEventEnum::DraggedLeft)){}

            myHorizontalSlider->setSize({{myBackground->Size().Origin().X(),
                                          myBackground->Size().Origin().Y()+myBackground->Size().Height()-18,
                                          myBackground->Size().Origin().Z()},
                                         myBackground->Size().Width()-18,
                                         18});
            myHorizontalSiderValue=myHorizontalSlider->Value();

            myVerticalSlider->setSize({{myBackground->Size().Origin().X()+myBackground->Size().Width()-18,
                                        myBackground->Size().Origin().Y(),
                                        myBackground->Size().Origin().Z()},
                                       18,
                                       myBackground->Size().Height()-18});
            myVerticalSliderValue=myVerticalSlider->Value();

            //! Remove slider sizes.
            myBackground->setSize({{myBackground->Size().Origin().X(),
                                    myBackground->Size().Origin().Y(),
                                    myBackground->Size().Origin().Z()},
                                   myBackground->Size().Width()-18,
                                   myBackground->Size().Height()-18});
            myBackground->setColor(myBackgroundColor->Color());

            myBorder->draw();
            myHorizontalSlider->draw();
            myVerticalSlider->draw();
            myBackground->draw();

            //! Set the scissor size, for designermode we include the relative offsets.
            if(hasParent()){
                setScissorUnion(ParentScissorSize(),myBackground->SizeIncludeOffsets());
            }

            //! Set the work size to the first widget of the WidgetVec.
            if(WidgetVec().size()>0){
                myWorkWidth=WidgetVec().front()->Size().Width();
                myWorkHeight=WidgetVec().front()->Size().Height();
                WidgetVec().front()->setSize({{myBackground->Size().Origin().X(),
                                               myBackground->Size().Origin().Y(),
                                               myBackground->Size().Origin().Z()},WidgetVec().front()->Size().Width(),WidgetVec().front()->Size().Height()});
            }

            if(myVerticalSlider->hasEvent()){
                for(uint i=0; i<WidgetVec().size(); i++){
                    WidgetVec().at(i)->setSizeOffset({-myHorizontalSiderValue*(myWorkWidth-myBackground->Size().Width()-18),-myVerticalSliderValue*(myWorkHeight-myBackground->Size().Height()),0});
                }
            }
            if(myHorizontalSlider->hasEvent()){
                for(uint i=0; i<WidgetVec().size(); i++){
                    WidgetVec().at(i)->setSizeOffset({-myHorizontalSiderValue*(myWorkWidth-myBackground->Size().Width()-18),-myVerticalSliderValue*(myWorkHeight-myBackground->Size().Height()),0});
                }
            }

            //! Test a event and draw content.
            for(uint i=0; i<WidgetVec().size(); i++){
                //! Event cycle.
                if(!myModeEdit){
                    if(WidgetVec().at(i)->Event(XEventEnum::PressedLeft)){
                        std::cout<<"Widget:"<<WidgetVec().at(i)->Name()<<" is pressed."<<std::endl;
                    }
                    if(WidgetVec().at(i)->Event(XEventEnum::ReleasedLeft)){}
                }
                if(myModeEdit){
                    //WidgetVec().at(i)->setRelativeOriginOffset(mySize->RelativeOriginOffset());
                }
                //! Set the framesize to the widget size.
                //! Draw widgets.
                WidgetVec().at(i)->draw();
            }
        }
        //! Restore the scissor size.
        restoreScissorState();
    }

    //! Non virtual functions.
    void setFrameSize(float theWidth, float theHeight){
        myWorkWidth=theWidth;
        myWorkHeight=theHeight;
    }
    void setModeEdit(bool theStatus){
        myModeEdit=theStatus;
    }

private:
    std::string myName;
    XSize *mySize=new XSize();

    float myBorderSize=5, myHorizontalSiderValue=0, myVerticalSliderValue=0, myWorkWidth=100, myWorkHeight=100;
    XColor //! Create colors and set standard values.
    *myBackgroundColor=new XColor(0.1,0.1,0.1,0.9),
    *myBorderColor=new XColor(0.0,0.0,0.0,0.9),
    *myHoverColor=new XColor(0.2,0.2,0.2,0.9),
    *myPressedColor=new XColor(0.3,0.3,0.3,0.9),
    *myTextColor=new XColor(1.0,1.0,1.0,0.9);
    XRectangular *myBackground=new XRectangular();
    XRectangular *myBorder=new XRectangular();
    XHorizontalSlider *myHorizontalSlider;
    XVerticalSlider *myVerticalSlider;
    bool myModeEdit=0;
    XScissor *myScissor;
};

#endif // XFRAME_H











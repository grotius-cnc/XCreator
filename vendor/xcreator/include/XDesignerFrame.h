#ifndef XDESIGNERFRAME_H
#define XDESIGNERFRAME_H

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
#include <XChar.h>
#include <XButton.h>
#include <XImageButton.h>
#include <XHorizontalSlider.h>
#include <XVerticalSlider.h>

// A XWidget containing a XSize.
class XDesignerFrame : public XWidget {
public:
    //! Empty constructor.
    XDesignerFrame(){}
    //! Constructor setting the GLFWwindow pointer.
    XDesignerFrame(XWindow *theWindow){
        this->setWindow(theWindow);
        myBorder->setWindow(theWindow);
        myBackground->setWindow(theWindow);
        myWidget->setWindow(theWindow);
        setScissorWindow(theWindow);
    }
    //! Empty destructor.
    ~XDesignerFrame(){}
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XDesignerFrame";
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
        //! Save the scissor size to be restored at the end of this function.
        saveScissorState();

        if(myBackground->Event(XEventEnum::PressedRight)){
            myRightSnapshot->setPoint(Mouse.Position()->Point());
            myWidget=myWidgetView->findTopmostWidgetByPoint(this,Mouse.Position()->Point());
            if(myWidget!=NULL){
                // std::cout<<"widget found, name:"<<aWidget->Name()<<std::endl;
            } else {
                // std::cout<<"no widget found"<<std::endl;
            }

            std::cout<<"right press"<<std::endl;
        }
        if(myBackground->Event(XEventEnum::DraggedRight)){
            //! Resize wigets by draggin right mouse button.
            w=Mouse.Position()->X()-myRightSnapshot->Point().X();
            h=Mouse.Position()->Y()-myRightSnapshot->Point().Y();
            myWidget->setRelativeSizeOffset({w,h});
            myWidget->stretchToParent(0);

            //! Remove widget from parent to enable modification.
            if(myWidget->hasParent() && myWidget!=this){
                XWidget *parent=myWidget->Parent();
                parent->removeWidget(myWidget);
                parent->stretchToParent(0);
            }
            if(!this->hasWidget(myWidget) && myWidget!=this){
                this->addWidget(myWidget);
            }
            std::cout<<"dragged right"<<std::endl;
        }
        if(myBackground->Event(XEventEnum::ReleasedRight)){
            //! Apply relative offsets.
            myWidget->applyRelativeSizeOffset();
            myWidget->stretchToParent(0);
            //! Evaluate chils of aWidget. aWidget size could be dragged outside the child's origin.
            for(uint i=0; i<myWidget->WidgetVec().size(); i++){
                XWidget *aChild=myWidget->WidgetVec().at(i);
                if(XPip().getPip(aChild->Size().Origin(),myWidget->Size())){
                    std::cout<<"is inside parent."<<std::endl;
                } else {
                    //! Set the child's origin to fit in the Parent size. We set the origin mid position of parent.
                    //! Remove widget from current parent, set the designer as new parent.
                    if(aChild->Parent()->Type()=="XSizeFrame"){
                        break;
                    }
                    if(aChild->hasParent()){
                        XWidget *parent=aChild->Parent();
                        parent->removeWidget(aChild);
                    }
                    if(!this->hasWidget(aChild)){
                        this->addWidget(aChild);
                    }
                }
            }
            std::cout<<"right release"<<std::endl;
        }
        if(myBackground->Event(XEventEnum::PressedMid)){
            // Find toplevel widget, toggle to strecht to parent..
            myLeftSnapshot->setPoint(Mouse.Position()->Point());
            myWidget=myWidgetView->findTopmostWidgetByPoint(this,Mouse.Position()->Point());
            myWidget->stretchToParent(1);
            std::cout<<"mid press"<<std::endl;
        }
        if(myBackground->Event(XEventEnum::ReleasedMid)){
            std::cout<<"mid release"<<std::endl;
        }
        if(myBackground->Event(XEventEnum::DraggedMid)){
            std::cout<<"dragged mid"<<std::endl;
        }
        if(myBackground->Event(XEventEnum::ScrollUp)){
            std::cout<<"scroll up"<<std::endl;
        }
        if(myBackground->Event(XEventEnum::ScrollDown)){
            std::cout<<"scroll down"<<std::endl;
        }
        if(myBackground->Event(XEventEnum::EscKey)){
            std::cout<<"esc pressed"<<std::endl;
        }
        if(myBackground->Event(XEventEnum::DelKey)){
            if(myWidget!=NULL && myWidget!=this && myWidget->Name()!=""){
                std::cout<<"del pressed, removing widget:"<<myWidget->Name()<<std::endl;
                XWidget *toDel=myWidget;
                myWidget->clearWidgetVec();
                myWidget=myWidget->Parent();
                myWidget->removeWidget(toDel);
                toDel=NULL;
            } else {
                std::cout<<"no widget selected"<<std::endl;
            }
            std::cout<<"del Key"<<std::endl;
        }

        if(myBackground->Event(XEventEnum::PressedLeft)){
            myLeftSnapshot->setPoint(Mouse.Position()->Point());
            myWidget=myWidgetView->findTopmostWidgetByPoint(this,Mouse.Position()->Point());
            if(myWidget!=NULL){
                // std::cout<<"widget found, name:"<<aWidget->Name()<<std::endl;
            } else {
                // std::cout<<"no widget found"<<std::endl;
            }
        }
        if(myBackground->Event(XEventEnum::DraggedLeft) && myWidget!=this){
            // std::cout<<"widget dragged"<<std::endl;
            x=Mouse.Position()->X()-myLeftSnapshot->Point().X();
            y=Mouse.Position()->Y()-myLeftSnapshot->Point().Y();
            z=Mouse.Position()->Z()-myLeftSnapshot->Point().Z();
            myWidget->setRelativeOriginOffset({x,y,z});
            myWidget->stretchToParent(0);
            myWidget->Parent()->stretchToParent(0);

            //! Remove widget from parent to enable modification.
            if(myWidget->hasParent()){
                XWidget *parent=myWidget->Parent();
                parent->removeWidget(myWidget);
            }
            if(!this->hasWidget(myWidget)){
                this->addWidget(myWidget);
            }
        }
        if(myBackground->Event(XEventEnum::ReleasedLeft)){
            if(myWidget!=NULL){
                myWidget->applyRelativeOriginOffset();
                // std::cout<<"applyReleativeOffset"<<std::endl;
            }
            //! Update widget structure?
            myWidget=myWidgetView->findTopmostWidgetByPoint(this,Mouse.Position()->Point());
            myWidget->stretchToParent(0);

            // In general when mouse is released, apply relative offset to all widgets.
            std::vector<XWidget*> theTree=XWidgetView().WidgetList(this);
            for(uint i=0; i<theTree.size(); i++){
                // std::cout<<"theTree at i"<<i<<" name"<<theTree.at(i)->Name()<<std::endl;
                theTree.at(i)->applyRelativeOriginOffset();
            }
            // std::cout<<"this released"<<std::endl;
        }
        //! Replace released widget into the widget structure tree again.
        if(!myBackground->Event(XEventEnum::DraggedLeft) && !myBackground->Event(XEventEnum::DraggedRight)){
            bool ok=0;
            std::vector<XWidget*> theList=myWidgetView->WidgetList();
            // std::cout<<"theList size:"<<theList.size()<<std::endl;

            //! Traverse back trough the widgetlist.
            for(int i=theList.size()-1; i>-1; i--){
                // std::cout<<"checking i:"<<i<<" name:"<<theList.at(i)->Name()<<std::endl;
                if(ok){
                    if(XPip().getPip(myWidget->Size().Origin().Point(),theList.at(i)->Size())){
                        // std::cout<<aWidget->Name()<<" fits in :"<<theList.at(i)->Name()<<std::endl;
                        //! Add as child.. check if its already the child.
                        if(!theList.at(i)->hasWidget(myWidget)){
                            //! Set the widgets parent offset value.
                            // aWidget->setParentOffset(XPoint().Substract(aWidget->Size().Origin(),theList.at(i)->Size().Origin()));
                            // std::cout<<"parentOffset x:"<<aWidget->ParentOffset().X()<<" y:"<<aWidget->ParentOffset().Y()<<std::endl;
                            //! Add widget to the parent if its origin is on top of the Parent size.
                            //                            if(aWidget->Type()=="XLayout"){
                            //                                aWidget->setSize(theList.at(i)->Size().MarginSize(10));
                            //                            }
                            myWidget->stretchToParent(0);
                            theList.at(i)->addWidget(myWidget);

                            //! The designer has to get rid of this widget copy.
                            if(this->hasWidget(myWidget)){
                                this->removeWidget(myWidget);
                            }
                            //! Update widget structure?
                            myWidget=myWidgetView->findTopmostWidgetByPoint(this,Mouse.Position()->Point());
                        } else {
                            // std::cout<<"widget already a child"<<std::endl;
                        }
                        break;
                    }
                }
                if(theList.at(i)==myWidget){
                    ok=1;
                }
            }
        }

        myBorder->setSize(mySize->Size());
        myBorder->setRelativeOriginOffset(mySize->RelativeOriginOffset());
        myBorder->setColor(myBorderColor->Color());
        myBorder->draw();

        //! Set the scissor size to not exceed the parent widget, and set the size including the frame border.
        if(hasParent()){
            setScissorUnion(ParentScissorSize(),myBackground->Size());
        }

        //! Background.
        myBackground->setSize(mySize->MarginSize(myBorderSize));
        myBackground->setColor({0.0,0.1,0.0,0.2});
        myBackground->draw();

        //! draw content.
        for(uint i=0; i<WidgetVec().size(); i++){
            WidgetVec().at(i)->draw();
        }

        //! Restore the scissor size.
        restoreScissorState();
    }

    //! Non virtual functions.
    XWidget* WidgetSelected(){
        return myWidget;
    }
    //! Return the widget structure text preview.
    std::string WidgetStructure(){
        return myWidgetView->printWidgetToString(this);
    }

private:
    XSize *mySize=new XSize();
    float myBorderSize=5;
    XString *myString=new XString("DesignerFrame");

    XRectangular *myBackground=new XRectangular();
    XRectangular *myBorder=new XRectangular();
//    XHorizontalSlider *myHorizontalSlider;
//    XVerticalSlider *myVerticalSlider;
//    XImageButton *myImageButtonSLidersMax;

    //! Create colors and set standard values.
    XColor *myBackgroundColor=new XColor(0.2,0.2,0.2,0.9);
    XColor *myBorderColor=new XColor(0.3,0.3,0.3,0.9);
    XColor *myHoverColor=new XColor(0.2,0.2,0.2,0.9);
    XColor *myPressedColor=new XColor(0.3,0.3,0.3,0.9);
    XColor *myTextColor=new XColor(1.0,1.0,1.0,0.9);

    XPoint *myLeftSnapshot=new XPoint();
    XPoint *myRightSnapshot=new XPoint();
    XWidgetView* myWidgetView=new XWidgetView();
    float x=0,y=0,z=0,w=0,h=0;
    XWidget* myWidget=new XWidget();
};

#endif // XDESIGNERFRAME_H











#ifndef XWIDGET_H
#define XWIDGET_H

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

#include <iostream>
#include <XSize.h>
#include <XPip.h>
#include <XPoint.h>
#include <XWindow.h>
#include <XMouse.h>
#include <XKey.h>
#include <XScissor.h>

enum XColorType{
    BackgroundColor,
    BorderColor,
    HoverColor,
    PressedColor,
    TextColor
};

enum XEventEnum {
    Hovered,
    PressedLeft,
    PressedLeftContinious,
    ReleasedLeft,
    PressedMid,
    PressedMidContinious,
    ReleasedMid,
    PressedRight,
    PressedRightContinious,
    ReleasedRight,
    DraggedLeft,
    DraggedMid,
    DraggedRight,
    ScrollUp,
    ScrollDown,
    DelKey,
    EscKey,
    EnterKey
};

//! Recursive solution.
class XWidgetView;
//! Toplevel widget class.
class XWidget {
public:
    //! Empty constructor.
    XWidget(){}
    //! Widget setting the parent widget.
    XWidget(XWidget *theParent){
        theParent->addWidget(this);
        myParent=theParent;
    }
    //! Widget setting the GLFWwindow pointer.
    XWidget(XWindow *theWindow):myWindow(theWindow){}
    //! Widget setting the parent widget.
    XWidget(XWidget *theParent, XWindow *theWindow):myWindow(theWindow){
        theParent->addWidget(this);
        myParent=theParent;
    }

    //! Virtual functions.
    virtual ~XWidget(){}
    virtual std::string Type(){return{};}
    virtual void setSize(XSize theSize){}
    virtual void setSizeOffset(XPoint theValue){}
    virtual void setSizeWithPointer(XSize *theSize){}
    virtual XSize Size(){return {};}
    virtual XSize* SizePointer(){return {};}
    virtual XSize SizeIncludeOffsets(){return{};}
    virtual void setBorderSize(float theSize){}
    virtual float BorderSize(){return{};}
    virtual void setRelativeOriginOffset(XPoint theRelativeOffset){}
    virtual XPoint RelativeOriginOffset(){return {};}
    virtual void setRelativeSizeOffset(std::pair<float,float> theRelativeDimensionOffset){}
    virtual std::pair<float,float> RelativeSizeOffset(){return {};}
    virtual void applyRelativeOriginOffset(){}
    virtual void applyRelativeSizeOffset(){}

    //! Set the color of the colortype.
    virtual void setColor(XColorType theColorType, XColor theColor){};
    //! Return the color of the colortype.
    virtual XColor Color(XColorType theColorType){return {};}
    //! Set the string.
    virtual void setString(std::string theString){}
    //! Return the string. Name only.
    virtual std::string String(){return{};};
    virtual void draw(){}
    //! XLayout, mid mouse toggle.
    virtual void stretchToParent(bool theValue){}
    //! XTreeView.
    virtual bool MouseOnStroke(){return {};};
    //! Set the GLWFwindow pointer.
    virtual void setWindow(XWindow *theWindow){
        myWindow=theWindow;
        // setScissorWindow(theWindow);
    }
    //! Set a normal scissor. Not usable for nested scissor operations.
    void setScissorSize(XSize theSize){
        myScissor->setScissorSize(theSize);
    }
    //! Set the union scissor. Usable for nested scissor operations.
    void setScissorUnion(XSize theParentSize, XSize theChildSize){
        myScissor->setScissorUnion(theParentSize,theChildSize);
    }
    //! Return the scissor size.
    XSize ScissorSize(){
        return myScissor->ScissorSize();
    }
    //! Return the scissor size.
    XSize ParentScissorSize(){
        return myParent->ScissorSize();
    }
    //! Enable scissor.
    void enableScissor(bool theStatus){
        myScissor->enableScissor(theStatus);
    }
    //! Restart the scissor. Put off and on.
    void restartScissor(){
        myScissor->enableScissor(0);
        myScissor->enableScissor(1);
    }
    //! Save the scissor size state.
    void saveScissorState(){
        myScissor->saveState();
    }
    //! Restore the scissor size state.
    void restoreScissorState(){
        myScissor->restoreState();
    }
    //! Set the GLFWwindow pointer.
    void setScissorWindow(XWindow *theWindow){
        myScissor->setWindow(theWindow);
    }


    void setWindowPointer(GLFWwindow *thePointer){
        myWindow->setWindowPointer(thePointer);
    }

    XWindow* Window(){
        return myWindow;
    }
    float WindowWidth(){
        return myWindow->Width();
    }
    float WindowHeight(){
        return myWindow->Height();
    }
    void setWindowDimension(float theWidth, float theHeight){
        myWindow->setWindowDimension(theWidth,theHeight);
    }
    //! Returns the status of the given XEventEnum.
    //! For dragging add a pressed & released event before.
    //! For pressed event add a release event to complete cycle.
    bool Event(XEventEnum theEvent){
        //! The eventlock is used by XStackedFrame when underlying widget's may not trigger a event by the
        //! XStackedFrame previous and forward buttons wich lie on top of the child widgets.
        if(!myEventLock){
            if(theEvent==XEventEnum::Hovered){
                return isHovered();
            }
            if(theEvent==XEventEnum::PressedLeft){
                return isPressedLeft();
            }
            if(theEvent==XEventEnum::PressedLeftContinious){
                return isPressedLeftContinious();
            }
            if(theEvent==XEventEnum::ReleasedLeft){
                return isReleasedLeft();
            }
            if(theEvent==XEventEnum::PressedMid){
                return isPressedMid();
            }
            if(theEvent==XEventEnum::PressedMidContinious){
                return isPressedMidContinious();
            }
            if(theEvent==XEventEnum::ReleasedMid){
                return isReleasedMid();
            }
            if(theEvent==XEventEnum::PressedRight){
                return isPressedRight();
            }
            if(theEvent==XEventEnum::PressedRightContinious){
                return isPressedRightContinious();
            }
            if(theEvent==XEventEnum::ReleasedRight){
                return isReleasedRight();
            }
            if(theEvent==XEventEnum::DraggedLeft){
                return isDraggedLeft();
            }
            if(theEvent==XEventEnum::DraggedMid){
                return isDraggedMid();
            }
            if(theEvent==XEventEnum::DraggedRight){
                return isDraggedRight();
            }
            if(theEvent==XEventEnum::ScrollUp){
                return isScrollUp();
            }
            if(theEvent==XEventEnum::ScrollDown){
                return isScrollDown();
            }
            if(theEvent==XEventEnum::EscKey){
                return isEscKey();
            }
            if(theEvent==XEventEnum::DelKey){
                return isDelKey();
            }
            if(theEvent==XEventEnum::EnterKey){
                return isEnterKey();
            }
        }
        return 0;
    }
    void setEventLock(bool theStatus){
        myEventLock=theStatus;
    }
    bool EventLock(){
        return myEventLock;
    }
    XPoint MousePos(){
        return Mouse.Position()->Point();
    }
    XPoint LeftMouseSnapShot(){
        return Mouse.LeftMouseSnapShot()->Point();
    }
    XPoint MidMouseSnapShot(){
        return Mouse.MidMouseSnapShot()->Point();
    }
    XPoint RightMouseSnapShot(){
        return Mouse.RightMouseSnapShot()->Point();
    }

    //! Non virtual functions.
    //! Set the Widget name.
    void setName(std::string theText){
        myName=theText;
    }
    //! Return the Widget name. FullFilePath.
    std::string Name(){
        if(myName==""){
            // std::cout<<"warning from function  std::string WidgetName(){}, no name is specified"<<std::endl;
        }
        return myName;
    }
    //! Set the Parent of this Widget.
    void setParent(XWidget *theParent){
        if(theParent==NULL){
            // std::cout<<"error from function void addChildWidget(XWidget *theChild){}, no child is given"<<std::endl;
            myParent=NULL;
        } else {
            theParent->addWidget(this);
            myParent=theParent;
        }
    }
    //! Add a ChildWidget to this Widget.
    void addWidget(XWidget *theChild){
        if(theChild==NULL){
            // std::cout<<"error from function void addChildWidget(XWidget *theChild){}, no child is given"<<std::endl;
        }
        theChild->myParent=this;
        myWidgetVec.push_back(theChild);
    }
    //! Test.
    void drawWidgetVec(){
        for(uint i=0; i<myWidgetVec.size(); i++){
            myWidgetVec.at(i)->draw();
        }
    }
    //! Return the Child Widget vector.
    std::vector<XWidget*> WidgetVec(){
        return myWidgetVec;
    }
    bool hasWidget(XWidget *theWidget){
        for(uint i=0; i<myWidgetVec.size(); i++){
            if(myWidgetVec.at(i)==theWidget){
                return 1;
            }
        }
        return 0;
    }
    //! Set the WidgetVec.
    void setWidgetVec(std::vector<XWidget*> theWidgetVec){
        myWidgetVec=theWidgetVec;
    }
    //! Remove all Child Widgets of this Widget.
    void clearWidgetVec(){
        myWidgetVec.clear();
    }
    //! If this Widget has a Child Widget vector, remove the first Child Widget of the vector, like pop_front().
    void WidgetVecPopFront(){
        if(myWidgetVec.size()==0){
            // std::cout<<"warning from function void ChildWidgetVecPopFront(){}, vector size=0"<<std::endl;
        }
        std::vector<XWidget*> myChildWidgetVecCopy;
        for(uint i=0; i<myWidgetVec.size(); i++){
            if(i>0){
                myChildWidgetVecCopy.push_back(myWidgetVec.at(i));
            }
        }
        myWidgetVec=myChildWidgetVecCopy;
    }
    void WidgetVecPopBack(){
        if(myWidgetVec.size()==0){
            // std::cout<<"warning from function void ChildWidgetVecPopBack(){}, vector size=0"<<std::endl;
        }
        if(myWidgetVec.size()>0){
            myWidgetVec.pop_back();
        }
    }
    void removeWidget(XWidget *theWidget){
        if(myWidgetVec.size()==0){
            // std::cout<<"warning from function void removeWidget(XWidget *theWidget){}, vector size=0"<<std::endl;
        }
        std::vector<XWidget*> myChildWidgetVecCopy;
        for(uint i=0; i<myWidgetVec.size(); i++){
            if(myWidgetVec.at(i)!=theWidget){
                myChildWidgetVecCopy.push_back(myWidgetVec.at(i));
            }
        }
        myWidgetVec=myChildWidgetVecCopy;
    }
    //! Return the Parent Widget of this Widget.
    XWidget* Parent(){
        if(myParent==NULL){
            std::cout<<"error in function XWidget* ParentWidget(){}, myParentWidget==NULL"<<std::endl;
        }
        return myParent;
    }
    //! Returns true if this Widget has a Child Widget or more.
    bool hasWidget(){
        if(myWidgetVec.size()>0){
            return 1;
        }
        return 0;
    }
    //! If this Widget has a Child Widget vector. In the vector select the first unselected item.
    void setFirstUnselectedWidgetVecItemSelected(){
        for(uint i=0; i<myWidgetVec.size(); i++){
            if(!myWidgetVec.at(i)->isWidgetSelected()){
                myWidgetVec.at(i)->setWidgetSelected();
                // std::cout<<"Setting first found unselected Widget, selected at :"<<i<<std::endl;
                break;
            }
        }
    }
    //! If this Widget has a Child Widget vector. In the vector select the first unselected item. Return this item.
    XWidget* setFirstUnselectedWidgetVecItemSelectedReturnWidget(){
        for(uint i=0; i<myWidgetVec.size(); i++){
            if(!myWidgetVec.at(i)->isWidgetSelected()){
                myWidgetVec.at(i)->setWidgetSelected();
                // std::cout<<"Setting first found unselected Widget, selected at :"<<i<<std::endl;
                return myWidgetVec.at(i);
            }
        }
        // std::cout<<"error function XWidget* setFirstUnselectedChildVecWidgetSelectedReturnWidget(){}"<<std::endl;
        return NULL;
    }
    //! If this Widget has a Child Widget vector. In the vector pick up the first unselected Widget and return this Widget.
    XWidget* FirstUnselectedItemWidgetVec(){
        for(uint i=0; i<myWidgetVec.size(); i++){
            if(!myWidgetVec.at(i)->isWidgetSelected()){
                // std::cout<<"First unselected Widget, name:"<<aWidget->WidgetText()<<std::endl;
                return myWidgetVec.at(i);
            }
        }
        // std::cout<<"error function XWidget* FirstUnselectedChildVecWidget(){}"<<std::endl;
        return NULL;
    }
    //! Check if the Child Widget vector has unselected Widgets inside.
    bool hasUnselectedItemWidgetVec(){
        for(uint i=0; i<myWidgetVec.size(); i++){
            if(!myWidgetVec.at(i)->isWidgetSelected()){
                return 1;
            }
        }
        return 0;
    }
    //! Check if this Widget has a Parent Widget.
    bool hasParent(){
        if(myParent==NULL){
            return 0;
        }
        return 1;
    }
    //! Set this Widget selected.
    void setWidgetSelected(){
        mySelect=1;
    }
    //! Set this Widget unselected.
    void setWidgetUnselect(){
        mySelect=0;
    }
    //! Check if this Widget is selected.
    bool isWidgetSelected(){
        return mySelect;
    }
    bool PressTriggerLeft(){
        return myPressTriggerLeft;
    }
    bool PressTriggerMid(){
        return myPressTriggerMid;
    }
    bool PressTriggerRight(){
        return myPressTriggerRight;
    }
    void setVisible(bool theStatus){
        myIsVisible=theStatus;
    }
    bool isVisible(){
        return myIsVisible;
    }

private:
    //! Store the parent Widget if there is one.
    XWidget *myParent;
    XWindow *myWindow=new XWindow();
    //! Set the scissor.
    XScissor *myScissor=new XScissor();
    //! Select flag, used to create a Widget structure graph.
    bool mySelect=0;
    //! Child Widget pointer list. This is just a list of pointers, pointing to a XWidget.
    std::vector<XWidget*> myWidgetVec;
    std::string myName;

    bool myPressTriggerLeft=0;
    bool myPressTriggerMid=0;
    bool myPressTriggerRight=0;
    bool myIsVisible=1;
    bool myEventLock=0;

    // Private event interface. Solves a continious stream of mouse clicks to a status.
    bool isHovered(){
        //! Include relative offsets when dragging a widget around.
        if(myWindow->GlfwWindowPointer()==Mouse.GlfwWindowPointer() && XPip().getPipFromMousePos(SizeIncludeOffsets())){
            return 1;
        }
        return 0;
    }
    //! Left mouse button.
    bool isPressedLeft(){
        if(myWindow->GlfwWindowPointer()==Mouse.GlfwWindowPointer() && Mouse.isPressedLeftButton() && XPip().getPipFromMousePos(SizeIncludeOffsets()) && !myPressTriggerLeft){
            Mouse.setLeftMouseSnapshot();
            //! std::cout<<"pressed:"<<this->Name()<<std::endl;
            myPressTriggerLeft=1;
            return 1;
        }
        return 0;
    }
    bool isPressedLeftContinious(){
        if(myWindow->GlfwWindowPointer()==Mouse.GlfwWindowPointer() && Mouse.isPressedLeftButton() && XPip().getPipFromMousePos(SizeIncludeOffsets())){
            return 1;
        }
        return 0;
    }
    bool isReleasedLeft(){
        if(myWindow->GlfwWindowPointer()==Mouse.GlfwWindowPointer() && !Mouse.isPressedLeftButton() && myPressTriggerLeft){
            // std::cout<<"widget released"<<std::endl;
            myPressTriggerLeft=0;
            return 1;
        }
        // std::cout<<"error from fucntion bool isPressedLeft(){}, possible incorrect output."<<std::endl;
        return 0;
    }
    //! Middle mouse button.
    bool isPressedMid(){
        if(myWindow->GlfwWindowPointer()==Mouse.GlfwWindowPointer() && Mouse.isPressedMidButton() && XPip().getPipFromMousePos(SizeIncludeOffsets()) && !myPressTriggerMid){
            Mouse.setMidMouseSnapshot();
            myPressTriggerMid=1;
            return 1;
        }
        return 0;
    }
    bool isPressedMidContinious(){
        if(myWindow->GlfwWindowPointer()==Mouse.GlfwWindowPointer() && Mouse.isPressedMidButton() && XPip().getPipFromMousePos(SizeIncludeOffsets())){
            return 1;
        }
        return 0;
    }
    bool isReleasedMid(){
        if(myWindow->GlfwWindowPointer()==Mouse.GlfwWindowPointer() && !Mouse.isPressedMidButton() && myPressTriggerMid){
            // std::cout<<"widget released"<<std::endl;
            myPressTriggerMid=0;
            return 1;
        }
        // std::cout<<"error from fucntion bool isPressedMid(){}, possible incorrect output."<<std::endl;
        return 0;
    }
    //! Right mouse button, scroll button.
    bool isPressedRight(){
        if(myWindow->GlfwWindowPointer()==Mouse.GlfwWindowPointer() && Mouse.isPressedRightButton() && XPip().getPipFromMousePos(SizeIncludeOffsets()) && !myPressTriggerRight){
            Mouse.setRightMouseSnapshot();
            myPressTriggerRight=1;
            return 1;
        }
        return 0;
    }
    bool isPressedRightContinious(){
        if(myWindow->GlfwWindowPointer()==Mouse.GlfwWindowPointer() && Mouse.isPressedRightButton() && XPip().getPipFromMousePos(SizeIncludeOffsets())){
            return 1;
        }
        return 0;
    }
    bool isReleasedRight(){
        if(myWindow->GlfwWindowPointer()==Mouse.GlfwWindowPointer() && !Mouse.isPressedRightButton() && myPressTriggerRight){
            // std::cout<<"widget released"<<std::endl;
            myPressTriggerRight=0;
            return 1;
        }
        // std::cout<<"error from fucntion bool isPressedLeft(){}, possible incorrect output."<<std::endl;
        return 0;
    }
    //! Dragging left mouse button.
    bool isDraggedLeft(){
        if(myWindow->GlfwWindowPointer()==Mouse.GlfwWindowPointer() && myPressTriggerLeft && Mouse.Position()->Dist(Mouse.LeftMouseSnapShot())){
            // std::cout<<"widget dragged"<<std::endl;
            return 1;
        }
        return 0;
    }
    //! Dragging middle mouse button.
    bool isDraggedMid(){
        if(myWindow->GlfwWindowPointer()==Mouse.GlfwWindowPointer() && myPressTriggerMid && Mouse.Position()->Dist(Mouse.MidMouseSnapShot())){
            // std::cout<<"widget dragged"<<std::endl;
            return 1;
        }
        return 0;
    }
    //! Dragging right mouse button.
    bool isDraggedRight(){
        if(myWindow->GlfwWindowPointer()==Mouse.GlfwWindowPointer() && myPressTriggerRight && Mouse.Position()->Dist(Mouse.RightMouseSnapShot())){
            // std::cout<<"widget dragged"<<std::endl;
            return 1;
        }
        return 0;
    }
    //! Mouse middle scroll button. There is a special scroll X coordinate available at Mouse.ScrollValueX().
    bool isScrollUp(){
        if(Mouse.ScrollValueY()>0  && XPip().getPipFromMousePos(SizeIncludeOffsets()) ){
            Mouse.resetMouseScrollValueYToZero();
            return 1;
        }
        return 0;
    }
    //! Mouse middle scroll button.
    bool isScrollDown(){
        if(Mouse.ScrollValueY()<0  && XPip().getPipFromMousePos(SizeIncludeOffsets()) ){
            Mouse.resetMouseScrollValueYToZero();
            return 1;
        }
        return 0;
    }
    //! Escape key.
    bool isEscKey(){
        if(Key.isGlfwEscapeKey()){
            // Key.resetKey(); // Reset at toplevel.
            return 1;
        }
        return 0;
    }
    //! Delete key.
    bool isDelKey(){
        if(Key.isGlfwDeleteKey()){
            return 1;
        }
        return 0;
    }
    //! Return key.
    bool isEnterKey(){
        if(Key.isGlfwEnterKey()){
            return 1;
        }
        return 0;
    }
};

//! The tool to manipulate the XWidget class.
//!
//! To garanty no parent in designermode : theWidget->setParent(NULL);
class XWidgetView {
public:
    XWidgetView(){}
    //! Test different scenario's.
    void testSample(){
        //! A Widget without parent.
        XWidget *aNode0=new XWidget();
        aNode0->setName("Node 0");
        //! Widget with parent.
        XWidget *aNode01=new XWidget(aNode0);
        aNode01->setName("Node 01");
        XWidget *aNode02=new XWidget(aNode0);
        aNode02->setName("Node 02");
        XWidget *aNode03=new XWidget(aNode0);
        aNode03->setName("Node 03");
        XWidget *aNode001=new XWidget(aNode01);
        aNode001->setName("Node 001");
        XWidget *aNode0001=new XWidget(aNode001);
        aNode0001->setName("Node 0001");
        XWidget *aNode002=new XWidget(aNode02);
        aNode002->setName("Node 002");

        //! WidgetView removes 2 nodes.
        XWidgetView *view=new XWidgetView();
        view->printWidget(aNode0);
        // view->removeWidget(aNode0,aNode001);
        // view->removeWidget(aNode0,aNode002);

        //! Add a widget without parent.
        XWidget *aNode004=new XWidget();
        aNode004->setName("Node 004");
        //! Set the parent afterwards.
        aNode01->addWidget(aNode004);
        //! Print result.
        view->printWidget(aNode0);

        //! Add a widget without parent.
        XWidget *aNode005=new XWidget();
        aNode005->setName("Node 005");
        //! Set the parent afterwards.
        aNode005->setParent(aNode03);
        //! Print result.
        view->printWidget(aNode0);
    }
    //! Print and process Widget structure.
    void printWidget(XWidget *theWidget){
        std::cout<<processWidgetTextGraph(theWidget)<<std::endl;
    }
    //! Return the widget structure as string.
    std::string printWidgetToString(XWidget *theWidget){
        return processWidgetTextGraph(theWidget);
    }
    //! theWidget is problably your topWidget containing Child Widgets.
    //! theWidgetName is the Child Widget to find by name input.
    XWidget* findWidgetByName(XWidget *theWidget, std::string theWidgetName){
        // std::cout<<"Finding Widget by name"<<std::endl;
        // std::cout<<processWidgetTextGraph(theWidget)<<std::endl;
        processWidgetTextGraph(theWidget);
        return findWidgetByName(theWidgetName);
    }
    //! Print Widget structure after one Widget is removed.
    //! This fuction will currently not work outside the XWidget class. It will work in XNode.
    //    void removeWidget(XWidget *theWidget, XWidget *theWidgetToRemove){
    //        // std::cout<<"Removing Widget by name"<<std::endl;
    //        processWidgetTextGraphAndRemoveWidget(theWidget,theWidgetToRemove);
    //    }
    //    //! Find and remove the Widget by given Widget name.
    //    void removeWidgetByName(XWidget *theWidget, std::string theWidgetName){
    //        // std::cout<<"Removing Widget by name"<<std::endl;
    //        processWidgetTextGraphAndRemoveWidget(theWidget,findWidgetByName(theWidgetName));
    //        std::cout<<processWidgetTextGraph(theWidget)<<std::endl;
    //    }

    //! Find topmost widget under a given point, the last drawed widget should be the topmost widget.
    //! the childVec of theWidget will be searched.
    XWidget* findTopmostWidgetByPoint(XWidget* theWidget, XPoint thePoint){
        // std::cout<<"Finding topmost Widget at given position x:"<<thePoint.X()<<" y:"<<thePoint.Y()<<" z:"<<thePoint.Z()<<std::endl;
        std::cout<<processWidgetTextGraph(theWidget)<<std::endl;
        //! Walk trough the generated widgetList from back to front.
        //! This is a simple list, containing all widgets in order from front to back.
        // std::cout<<"mySelectedWidgetList.size:"<<mySelectedWidgetList.size()<<std::endl;
        for(int i=mySelectedWidgetList.size()-1; i>-1; i--){
            if(XPip().getPip(thePoint, mySelectedWidgetList.at(i)->SizeIncludeOffsets())){
                // std::cout<<"widget found, widget name:"<<mySelectedWidgetList.at(i)->Name()<<std::endl;
                // std::cout<<"thePosition x:"<<thePoint.X()<<" y:"<<thePoint.Y()<<" z:"<<thePoint.Z()<<std::endl;
                return mySelectedWidgetList.at(i);
            }
        }
        //! Nothing found.
        return NULL;
    }
    //! Returns all widgets in one list.
    std::vector<XWidget*> WidgetList(){
        return mySelectedWidgetList;
    }
    //! Returns all widgets in one list.
    std::vector<XWidget*> WidgetList(XWidget *theWidget){
        std::cout<<processWidgetTextGraph(theWidget)<<std::endl;
        return mySelectedWidgetList;
    }
    //! Finds the Toplevel widget of the widget tree. Input is current widget. Retuns the toplevel widget.
    XWidget* findToplevelWidget(XWidget *theWidget){
        XWidget *aWidget=theWidget;
        while(aWidget->hasParent()){
            aWidget=aWidget->Parent();
        }
        return aWidget;
    }

private:
    std::vector<XWidget*> mySelectedWidgetList;
    XWidget* findWidgetByName(std::string theWidgetName){
        if(theWidgetName==""){
            // std::cout<<"warning from function XWidget* findWidgetByName(std::string theWidgetName){}, empty Widget name"<<std::endl;
        }
        for(uint i=0; i<mySelectedWidgetList.size(); i++){
            if(mySelectedWidgetList.at(i)->Name()==theWidgetName){
                return mySelectedWidgetList.at(i);
            }
        }
        // std::cout<<"error from function XWidget* findWidgetByName(std::string theWidgetName){}, no Widget found by this name."<<std::endl;
        return NULL;
    }
    //! Print the list off all selected Widgets. This list is available after the processWidgetTextGraph function is executed.
    void printSelectedWidgetList(){
        // std::cout<<"Printing the selectedWidgetList"<<std::endl;
        for(uint i=0; i<mySelectedWidgetList.size(); i++){
            std::cout<<mySelectedWidgetList.at(i)->Name()<<std::endl;
        }
    }
    //! Reset the select flag for each Widget to zero. The mySelectWidgetList is a one dimensional Widget list made by the processWidgetTextGraph function.
    //! Basicly a fast and simple pointer overview list.
    void resetWidgetSelection(){
        // std::cout<<"Resetting the selectedWidgetList to initial state"<<std::endl;
        for(uint i=0; i<mySelectedWidgetList.size(); i++){
            mySelectedWidgetList.at(i)->setWidgetUnselect();
        }
    }
    //! Processing the Widget structure graph. Return's a std::string to display in terminal.
    std::string processWidgetTextGraph(XWidget *theWidget){
        // std::cout<<"Processing Widget layout"<<std::endl;
        mySelectedWidgetList.clear();
        std::string theWidgetStructureText;
        std::string theFrontText=" - ";

        // theWidget->printWidgetText(theFrontText); // For debugging, Print toplevelWidget.
        theWidgetStructureText.append(theFrontText+theWidget->Name()+'\n');
        mySelectedWidgetList.push_back(theWidget); //! Add toplevel widget to the list.

        //if(!theWidget->hasParent() && !theWidget->hasWidget()){
        //    return theWidget->Name();
        //}

        while(1){ // Do it infinite.
            if(theWidget->hasUnselectedItemWidgetVec()){
                theWidget=theWidget->FirstUnselectedItemWidgetVec();

                uint theSize=theFrontText.size();
                theFrontText.clear();
                theFrontText.resize(theSize+2,' ');
                theFrontText.push_back('|');
                theFrontText.push_back('-');
                theFrontText.push_back(' ');
                //* theWidget->printWidgetText(theFrontText); // For debugging.
                theWidgetStructureText.append(theFrontText+theWidget->Name()+'\n');
                mySelectedWidgetList.push_back(theWidget); //! Add childVec widgets to the list.

            } else {  // At deepest child Widget. No more child's left.

                if(theWidget->hasParent()){
                    theWidget=theWidget->Parent(); // Go back one level.
                    theFrontText.erase(0,5);
                    if(theWidget->hasUnselectedItemWidgetVec()){
                        theWidget->setFirstUnselectedWidgetVecItemSelectedReturnWidget();
                    }
                } else {
                    // Nothing left, leave this while loop.
                    break;
                }
            }
        }
        // printSelectedWidgetList();
        resetWidgetSelection();
        return theWidgetStructureText;
    }
    //! A copy off processWidgetTextGraph, removing the text graph code, and adding code to remove a Widget.
    void processWidgetTextGraphAndRemoveWidget(XWidget *theWidget, XWidget *theWidgetToDelete){
        // std::cout<<"Processing Widget layout at removal"<<std::endl;
        mySelectedWidgetList.clear();
        mySelectedWidgetList.push_back(theWidget); //! Add toplevel widget to the list.
        while(1){ // Do it infinite.
            if(theWidget->hasUnselectedItemWidgetVec()){
                //theWidget=theWidget->ChildWidgetVec().front(); // Goto first child Widget at front of vector.
                theWidget=theWidget->FirstUnselectedItemWidgetVec();
                mySelectedWidgetList.push_back(theWidget); //! Add childVec widgets to the list.
            } else {  // At deepest child Widget. No more child's left.

                if(theWidget->hasParent()){
                    theWidget=theWidget->Parent(); // Go back one level.
                    if(theWidget->hasUnselectedItemWidgetVec()){
                        XWidget *aWidget=theWidget->setFirstUnselectedWidgetVecItemSelectedReturnWidget();
                        if(aWidget==theWidgetToDelete){
                            // Do nothing.
                        } else {
                            mySelectedWidgetList.push_back(aWidget);
                        }

                    }
                } else {
                    // Nothing left, leave this while loop.
                    break;
                }
            }
        }
        resetWidgetSelection();
    }
};

#endif // XWIDGET_H


#ifndef XTREEVIEW_H
#define XTREEVIEW_H

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
#include <XScissor.h>
#include <XChar.h>
#include <XRectangular.h>
#include <XNode.h>
#include <XText.h>
#include <XIcon.h>
#include <XCursor.h>
#include <XTimer.h>
#include <XFileOption.h>

float x=0.0, y=0.0;
uint count=0;

class XTreeViewItem : public XWidget {
public:
    //! Empty constructor. setWindow or parent afterwards.
    XTreeViewItem(){}
    //! The button has to be a member of a GLFWWindow. Mouse events, key events, are valid for the specific window. Otherwise a button press could be valid from other window.
    XTreeViewItem(XWindow *theWindow){
        myText->setWindow(theWindow);
        myIconTriangleRight->setWindow(theWindow);
        myIconTriangleDown->setWindow(theWindow);
        myIcon->setWindow(theWindow);
        this->setWindow(theWindow);
    }
    //! Empty destructor.
    ~XTreeViewItem(){}
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XTreeViewItem";
    }
    //! Set the GLFWwindow pointer afterwards when a empty constuctor is used like : XTreeViewItem *Item = new XTreeViewItem();
    void setWindow(XWindow *theWindow){
        //! Done by XWidget: myWindow=theWindow;
        myText->setWindow(theWindow);
        myIconTriangleRight->setWindow(theWindow);
        myIconTriangleDown->setWindow(theWindow);
        myIcon->setWindow(theWindow);
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
    //! Set the string if the widget is a button or label.
    void setString(std::string theString){
        myString->setStringFromStdString(theString);
    }
    //! Return the string.
    std::string String(){
        return myString->toStdString();
    };
    //! draw this widget. Eventually use xyz offsets, for example while dragging a widget.
    void draw(){
        if(count==1){
            x+=10;
        }
        count++;
        setVisible(1);

        // set as parent size. parent height + origin y = new startpoint next item.
        // or add a origin offset value in XSize.
        myIconTriangleRight->setSizeOffset({x,y,0});
        myIconTriangleDown->setSizeOffset({x,y,0});
        myIcon->setSizeOffset({x,y,0});
        myText->setSizeOffset({x,y,0});
        myStrokeSize->setSize(mySize->Size());
        myStrokeSize->setRelativeOriginOffset(mySize->RelativeOriginOffset());
        myStrokeSize->setSizeOffset({0,y,0});
        y+=18;

        //! Save the current scissor size to be restored at end of this function.
        saveScissorState();
        //! Add code here.
        myIconTriangleRight->setSize({{mySize->Origin().X()+5,
                                       mySize->Origin().Y()+1, //! Center icon on Y.
                                       mySize->Origin().Z()}, 16, 16});
        myIconTriangleRight->setRelativeOriginOffset(mySize->RelativeOriginOffset());
        myIconTriangleDown->setSize({{mySize->Origin().X()+5,
                                      mySize->Origin().Y()+1, //! Center icon on Y.
                                      mySize->Origin().Z()}, 16, 16});
        myIconTriangleDown->setRelativeOriginOffset(mySize->RelativeOriginOffset());

        if(myIconTriangleRight->Event(XEventEnum::PressedLeft)){
            myIconTriangleToggle=!myIconTriangleToggle;
        }
        if(myIconTriangleRight->Event(XEventEnum::ReleasedLeft)){}

        if(hasWidget()){
            if(myIconTriangleToggle){
                myIconTriangleRight->draw();
            } else {
                myIconTriangleDown->draw();
                x+=10;
            }
        }

        float startX=25;
        //! The icon is set, process it.
        if(myIcon->hasIcon()){
            myIcon->setSize({{mySize->Origin().X()+startX,
                              mySize->Origin().Y()+1, //! Center icon on Y.
                              mySize->Origin().Z()}, 16, 16});
            myIcon->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            myIcon->draw();
            startX+=20;
        }

        myText->setSize({{mySize->Origin().X()+startX,
                          mySize->Origin().Y(),
                          mySize->Origin().Z()},
                         mySize->Width(), myRowHeight});
        myText->setRelativeOriginOffset(mySize->RelativeOriginOffset());
        myString->setColorToString(myTextColor->Color());
        myText->drawText(*myString,0,myString->size(),int(5),int(0),false);

        //! Draw child widgets, if there are present.
        for(uint i=0; i<WidgetVec().size(); i++){
            //! If the icon direction down, show the child.
            if(!myIconTriangleToggle){
                //! Set the child widgets to a certain x offset.
                WidgetVec().at(i)->setSize({{mySize->Origin().X(),
                                             mySize->Origin().Y(),
                                             mySize->Origin().Z()}, mySize->Width(),myRowHeight});
                WidgetVec().at(i)->setRelativeOriginOffset(mySize->RelativeOriginOffset());
                WidgetVec().at(i)->draw();
                WidgetVec().at(i)->setVisible(1);
            } else {
                WidgetVec().at(i)->setVisible(0);
            }
        }
        //! Restore the x offset when child widgets are drawn.
        if(hasWidget()){
            if(myIconTriangleToggle){
            } else {
                x-=10;
            }
        }
        //! Restore the scissor size.
        restoreScissorState();
    }
    //! Non virtual functions.
    void setRowHeight(float theValue){
        myRowHeight=theValue;
    }
    //! Set the icon.
    void setIcon(std::string thePath){
        myIcon->setIcon(thePath);
    }
    //! Stroke size is a size with offsets included.
    bool MouseOnStroke(){
        return XPip().getPip(Mouse.Position()->Point(),myStrokeSize->Size());
    }
    //! Set unfold toggle triangle.
    void setUnfoldToggleTriangle(){
        myIconTriangleToggle=false;
    }

private:
    XString *myString=new XString("TreeViewItem");
    XSize *mySize=new XSize();
    XSize *myStrokeSize=new XSize();
    float myBorderSize=2;
    XColor //! Create colors and set standard values.
    *myBackgroundColor=new XColor(0.1,0.1,0.1,0.9),
    *myBorderColor=new XColor(0.0,0.0,0.0,0.9),
    *myHoverColor=new XColor(0.3,0.3,0.3,0.9),
    *myPressedColor=new XColor(0.6,0.6,0.6,0.9),
    *myTextColor=new XColor(1.0,1.0,1.0,0.9);

    XText *myText=new XText();
    //! 1=Unfold. 0=Fold.
    bool myIconTriangleToggle=1;
    XIcon *myIconTriangleRight=new XIcon("icons/Adwaita/16x16/ui/pan-end-symbolic.symbolic.png",{{0,0,0},16,16});
    XIcon *myIconTriangleDown=new XIcon("icons/Adwaita/16x16/ui/pan-down-symbolic.symbolic.png",{{0,0,0},16,16});
    XIcon *myIcon=new XIcon();
    float myRowHeight=18;
};

class XTreeView : public XWidget {
public:
    //! Empty constructor. setWindow or parent afterwards.
    XTreeView(){}
    //! The button has to be a member of a GLFWWindow. Mouse events, key events, are valid for the specific window. Otherwise a button press could be valid from other window.
    XTreeView(XWindow *theWindow){
        this->setWindow(theWindow);
        myBackground->setWindow(theWindow);
        myBorder->setWindow(theWindow);
        myStroke->setWindow(theWindow);
        myToplevelTreeViewItem->setWindow(theWindow);
        myCursor->setWindow(theWindow);
        setScissorWindow(theWindow);
    }
    //! Empty destructor.
    ~XTreeView(){}
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XTreeView";
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
    //! Set the string if the widget is a button or label.
    void setString(std::string theString){
        myString->setStringFromStdString(theString);
    }
    //! Return the string.
    std::string String(){
        return myString->toStdString();
    };
    void init(){
        myFileOption=new XFileOption(Window());
        myFileOption->init();
        addWidget(myFileOption);
    }
    //! draw this widget. Eventually use xyz offsets, for example while dragging a widget.
    void draw(){
        if(!myInit){
            init();
            myInit=1;
        }
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

        //! Set the scissor size, for designermode we include the relative offsets.
        if(hasParent()){
            setScissorUnion(ParentScissorSize(),myBackground->SizeIncludeOffsets());
        }

        //! When file option is visible, set event lock for underlying XTreeView.
        if(myFileOption->isVisible() && XPip().getPipFromMousePos(myFileOption->Size())){
            myBackground->setEventLock(1);
        } else {
            myBackground->setEventLock(0);
        }

        //! When pressed set the stroke at position.
        if(!EventLock()){
            if(myBackground->Event(XEventEnum::PressedLeft) && XPip().getPipFromMousePos(ParentScissorSize())){

                //! Double click counter.
                myClicks++;

                //! First click, start timer.
                if(!myDoubleClickTimer->TimerActive()){
                    //! std::cout<<"timer start."<<std::endl;
                    myDoubleClickTimer->setIntervalMs(200);
                    myDoubleClickTimer->startTimer(true);

                    //! Set selected row at first click.
                    //! Y offset to highlighted stroke. Starting at row : 0.
                    mySelectedRow=(Mouse.Position()->Y()-myBackground->Size().Origin().Y()-myYShift)/myRowHeight;

                    //! Get the current mySelectedWidgetName.
                    std::vector<XWidget*> myList=myWidgetView->WidgetList(myToplevelTreeViewItem);

                    if(mySelectedRow>=myList.size()){
                        std::cout<<"out of scope"<<std::endl;
                        myOutOfScope=1;
                    } else {
                        myOutOfScope=0;
                        for(uint i=0; i<myList.size(); i++){
                            if(myList.at(i)->MouseOnStroke() && myList.at(i)->isVisible()){
                                mySelectedWidget=myList.at(i);
                                //! Print selected item's name.
                                mySelectedWidgetName=mySelectedWidget->Name(); //! Full filepath.
                                mySelectedWidgetString=mySelectedWidget->String(); //! Name only.
                                break;
                            }
                        }
                        std::cout<<"mouse selected item name:"<<mySelectedWidget->Name()<<std::endl;
                        std::cout<<"mouse selected item string:"<<mySelectedWidget->String()<<std::endl;
                    }
                }

                //! If second click is within the timer interval, double click is performed, go on.
                if(myClicks==2){
                    myIsPressed=true;
                }

                myFileOption->hide();
            }
            if(myBackground->Event(XEventEnum::ReleasedLeft)){}
            if(myBackground->Event(XEventEnum::Hovered) && XPip().getPipFromMousePos(ParentScissorSize()) && !Mouse.isPressedLeftButton()){
                myCursor->revertToDefaultCursor();
            }

            if(myBackground->Event(XEventEnum::PressedRight) && XPip().getPipFromMousePos(myStroke->Size())){
                std::cout<<"pressed right."<<std::endl;
                //! Show a frame with file options.

                if(!myOutOfScope){
                    myFileOption->setText(mySelectedWidgetString,mySelectedWidgetName);
                    myFileOption->show(Mouse.Position()->Point());
                }
            }

            if(myBackground->Event(XEventEnum::ReleasedRight)){}
        }

        if(myFileOption->NeedFileUpdate()){
            std::cout<<"newName:"<<myFileOption->NewPath()<<std::endl;
            std::cout<<"newString:"<<myFileOption->NewString()<<std::endl;
            mySelectedWidget->setName(myFileOption->NewPath());
            mySelectedWidget->setString(myFileOption->NewString());

            myNeedsUpdate=1;
        }

        //! When interval is reaced, reset click to zero.
        if(myDoubleClickTimer->IntervalReached()){
            //! std::cout<<"interval reached:"<<std::endl;
            myDoubleClickTimer->stopTimer();
            myClicks=0;
        }

        //! Add timer update to current thread.
        myDoubleClickTimer->update();

        //! Selection stroke.
        myStroke->setSize({{myBackground->Size().Origin().X(),
                            myBackground->Size().Origin().Y()+(mySelectedRow*myRowHeight)+myYShift,
                            myBackground->Size().Origin().Z()},myBackground->Size().Width(),myRowHeight});
        myStroke->setRelativeOriginOffset(mySize->RelativeOriginOffset());
        myStroke->setRelativeSizeOffset(mySize->RelativeSizeOffset());
        myStroke->setColor(myHoverColor->Color());
        myStroke->draw();

        //! Upper node, TreeViewItem.
        myToplevelTreeViewItem->setSize({{myBackground->Size().Origin().X(),
                                          myBackground->Size().Origin().Y()+myYShift,
                                          myBackground->Size().Origin().Z()}, myBackground->Size().Width(),myRowHeight});
        myToplevelTreeViewItem->setRelativeOriginOffset(mySize->RelativeOriginOffset());
        myToplevelTreeViewItem->setParent(NULL);

        //! Example:
        if(!myContentInit){
            setTopLevelItem("ToplevelItem","ToplevelItem_Data","icons/Adwaita/16x16/places/folder.png",true);
            addChildItem("SubLevelItem_0","SubLevelItem_0_Data","ToplevelItem","icons/Adwaita/16x16/legacy/appointment-soon.png");
            myContentInit=1;
        }

        x=0.0, y=0; count=0;
        myToplevelTreeViewItem->draw();

        //! Draw child widgets, if there are present.
        for(uint i=0; i<WidgetVec().size(); i++){
            WidgetVec().at(i)->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            WidgetVec().at(i)->draw();
        }

        //! Restore the scissor size.
        restoreScissorState();
    }
    //! Non virtual functions.

    //! theName is internal name, theString is text to display.
    void setTopLevelItem(std::string theName, std::string theString, std::string theIconPath, bool theTopLevelShow){
        myTopLevelShow=theTopLevelShow;
        myToplevelTreeViewItem->setName(theName);
        myToplevelTreeViewItem->setString(theString);
        if(theIconPath.size()>0){
            myToplevelTreeViewItem->setIcon(theIconPath);
        }
        //! Remove all child content.
        myToplevelTreeViewItem->clearWidgetVec();
        //! Test output:
        //! view->printWidget(myToplevelTreeViewItem);
    }
    //! Set the status of the toplevelitem to unfold.
    void setTopLevelItemUnfold(){
        myToplevelTreeViewItem->setUnfoldToggleTriangle();
    }
    //! Add a child widget, theName is internal name, theString is text to display.
    void addChildItem(std::string theName, std::string theString, std::string theParent, std::string theIconPath){
        //! New XTreeViewItem.
        XTreeViewItem *aTreeViewItem=new XTreeViewItem(Window());
        aTreeViewItem->setName(theName);
        aTreeViewItem->setString(theString);
        if(theIconPath.size()>0){
            aTreeViewItem->setIcon(theIconPath);
        }
        //! Find parent by name, where myToplevelTreeViewItem is the most upper node of the widget tree.
        XWidget *aParent=myWidgetView->findWidgetByName(myToplevelTreeViewItem,theParent);
        aParent->addWidget(aTreeViewItem);
    }
    //! The item name, not the display text.
    std::string mySelectedItemName(){
        return mySelectedWidgetName;
    }
    //! To startup without any demo content.
    void setContentInit(bool theStatus){
        myContentInit=theStatus;
    }
    //! Events.
    bool isPressed(){
        bool status=myIsPressed;
        //! Reset pressed.
        myIsPressed=false;
        //! Reset selected row to zero.
        return status;
    }
    //! Reset selected row to zero.
    void resetSelectedRowToTop(){
        mySelectedRow=0;
    }
    //! Get the ammount of items that are displayed. Can be used to control a vertical slider.
    uint ContentHeight(){
        //! std::cout<<"Items:"<<myToplevelTreeViewItem->WidgetVec().size()+1<<std::endl;
        return ((myToplevelTreeViewItem->WidgetVec().size()+1)*myRowHeight) /* -myBackground->Size().Height() */;
    }
    //! Set the vertical scroll value.
    void setVerticalScroll(float theValue){
        myYShift=theValue*ContentHeight()*-1;
    }
    //! Needs update.
    bool NeedsUpdate(){
        bool result=myNeedsUpdate;
        myNeedsUpdate=0;
        return result;
    }

private:
    XString *myString=new XString("TreeView");
    XSize *mySize=new XSize();
    float myBorderSize=2;
    XColor //! Create colors and set standard values.
    *myBackgroundColor=new XColor(0.5,0.5,0.5,0.9),
    *myBorderColor=new XColor(0.0,0.0,0.0,0.9),
    *myHoverColor=new XColor(0.3,0.3,0.3,0.9),
    *myPressedColor=new XColor(0.6,0.6,0.6,0.9),
    *myTextColor=new XColor(1.0,1.0,1.0,0.9);
    XRectangular *myBackground=new XRectangular();
    XRectangular *myBorder=new XRectangular();
    XRectangular *myStroke=new XRectangular();
    XWidget *myWidget=new XWidget();
    //! Highlight stroke.
    float myRowHeight=18;
    uint mySelectedRow=0;
    //! TreeViewItem.
    XTreeViewItem *myToplevelTreeViewItem=new XTreeViewItem();
    XWidgetView *myWidgetView=new XWidgetView();
    XWidget* mySelectedWidget;
    std::string mySelectedWidgetName, mySelectedWidgetString;
    bool myContentInit=0;

    bool myIsPressed=0;
    bool myTopLevelShow=0;
    float myYShift=0;
    XTimer *myDoubleClickTimer=new XTimer();
    uint myClicks=0;

    XCursor *myCursor=new XCursor();
    XFileOption *myFileOption;
    bool myInit=0;
    bool myNeedsUpdate=0;
    bool myOutOfScope=0;
};
#endif










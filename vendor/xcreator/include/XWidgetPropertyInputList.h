#ifndef XWIDGETPROPERTYINPUTLIST_H
#define XWIDGETPROPERTYINPUTLIST_H

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
#include <XLabel.h>
#include <XButton.h>
#include <XLineEdit.h>
#include <XSize.h>

class XWidgetPropertyInputList : public XWidget {
public:
    //! Empty constructor. setWindow or parent afterwards.
    XWidgetPropertyInputList(){}
    //! The button has to be a member of a GLFWWindow. Mouse events, key events, are valid for the specific window. Otherwise a button press could be valid from other window.
    XWidgetPropertyInputList(XWindow *theWindow){
        this->setWindow(theWindow);
        setScissorWindow(theWindow);
    }
    //! Empty destructor.
    ~XWidgetPropertyInputList(){}
    //! Initialisation function.
    void init(){
        myLabel=new XLabel(Window());
        myLabel->setBorderSize(0.5);
        myLabelName=new XLabel(Window());
        myLabelName->setBorderSize(0.5);

        myBackground=new XRectangular(Window());
        myBorder=new XRectangular(Window());
        myLineEditType=new XLineEdit(Window());
        myLineEditType->setBorderSize(0.5);
        myLineEditName=new XLineEdit(Window());
        myLineEditName->setBorderSize(0.5);
        myLineEditString=new XLineEdit(Window());
        myLineEditString->setBorderSize(0.5);
        myLineEditOriginX=new XLineEdit(Window());
        myLineEditOriginX->setBorderSize(0.5);
        myLineEditOriginY=new XLineEdit(Window());
        myLineEditOriginY->setBorderSize(0.5);
        myLineEditOriginZ=new XLineEdit(Window());
        myLineEditOriginZ->setBorderSize(0.5);
        myLineEditWidth=new XLineEdit(Window());
        myLineEditWidth->setBorderSize(0.5);
        myLineEditHeight=new XLineEdit(Window());
        myLineEditHeight->setBorderSize(0.5);
        myLineEditBorderSize=new XLineEdit(Window());
        myLineEditBorderSize->setBorderSize(0.5);

        myLineEditBackgroundColorRed=new XLineEdit(Window());
        myLineEditBackgroundColorRed->setBorderSize(0.5);
        myLineEditBackgroundColorGreen=new XLineEdit(Window());
        myLineEditBackgroundColorGreen->setBorderSize(0.5);
        myLineEditBackgroundColorBlue=new XLineEdit(Window());
        myLineEditBackgroundColorBlue->setBorderSize(0.5);
        myLineEditBackgroundColorAlpha=new XLineEdit(Window());
        myLineEditBackgroundColorAlpha->setBorderSize(0.5);

        myLineEditBorderColorRed=new XLineEdit(Window());
        myLineEditBorderColorRed->setBorderSize(0.5);
        myLineEditBorderColorGreen=new XLineEdit(Window());
        myLineEditBorderColorGreen->setBorderSize(0.5);
        myLineEditBorderColorBlue=new XLineEdit(Window());
        myLineEditBorderColorBlue->setBorderSize(0.5);
        myLineEditBorderColorAlpha=new XLineEdit(Window());
        myLineEditBorderColorAlpha->setBorderSize(0.5);

        myLineEditHoverColorRed=new XLineEdit(Window());
        myLineEditHoverColorRed->setBorderSize(0.5);
        myLineEditHoverColorGreen=new XLineEdit(Window());
        myLineEditHoverColorGreen->setBorderSize(0.5);
        myLineEditHoverColorBlue=new XLineEdit(Window());
        myLineEditHoverColorBlue->setBorderSize(0.5);
        myLineEditHoverColorAlpha=new XLineEdit(Window());
        myLineEditHoverColorAlpha->setBorderSize(0.5);

        myLineEditPressedColorRed=new XLineEdit(Window());
        myLineEditPressedColorRed->setBorderSize(0.5);
        myLineEditPressedColorGreen=new XLineEdit(Window());
        myLineEditPressedColorGreen->setBorderSize(0.5);
        myLineEditPressedColorBlue=new XLineEdit(Window());
        myLineEditPressedColorBlue->setBorderSize(0.5);
        myLineEditPressedColorAlpha=new XLineEdit(Window());
        myLineEditPressedColorAlpha->setBorderSize(0.5);

        myLineEditTextColorRed=new XLineEdit(Window());
        myLineEditTextColorRed->setBorderSize(0.5);
        myLineEditTextColorGreen=new XLineEdit(Window());
        myLineEditTextColorGreen->setBorderSize(0.5);
        myLineEditTextColorBlue=new XLineEdit(Window());
        myLineEditTextColorBlue->setBorderSize(0.5);
        myLineEditTextColorAlpha=new XLineEdit(Window());
        myLineEditTextColorAlpha->setBorderSize(0.5);

        myLineEditHoverColorRed=new XLineEdit(Window());
        myLineEditHoverColorRed->setBorderSize(0.5);
        myLineEditPressedColorRed=new XLineEdit(Window());
        myLineEditPressedColorRed->setBorderSize(0.5);
        myLineEditTextColorRed=new XLineEdit(Window());
        myLineEditTextColorRed->setBorderSize(0.5);

        myLineEditOriginX->setString("0");
        myLineEditOriginY->setString("0");
        myLineEditOriginZ->setString("0");
        myLineEditWidth->setString("0");
        myLineEditHeight->setString("0");
    }
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XWidgetPropertyInputList";
    }
    //! Set the size of this widget. Size also handles the mouse & key events.
    void setSize(XSize theSize){
        mySize->setSize(theSize);
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
        if(!myInit){
            init();
            myInit=1;
        }

        float x=mySize->Origin().X()+mySize->RelativeOriginOffset().X();
        float y=mySize->Origin().Y()+mySize->RelativeOriginOffset().Y();
        float z=mySize->Origin().Z()+mySize->RelativeOriginOffset().Z();
        float w=mySize->Width();
        //! float h=mySize->Height();
        //! Left width.
        float lw=150;
        //! Row height.
        float rh=18;

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

        // Todo edit mode.
        if(myWidget==NULL){
            std::cout<<"Widget is NULL"<<std::endl;
        }
        //! If used in design mode, set myWidget as the current property input list.
        if(myModeDesigner){
            myWidget=this;
        }
        if(myWidget!=NULL){

#define LemonChion {1.0,0.98,0.804,0.9}
#define White {1.0,1.0,1.0,0.9}
#define Black {0.0,0.0,0.0,0.9}

            myLabel->setColor(XColorType::TextColor,Black);

            //! New set.
            myLabel->setSize({{x,y,z},lw,rh});
            myLabel->setString("Type");
            myLabel->setColor(XColorType::BackgroundColor,LemonChion);
            myLabel->draw();
            myLineEditType->setSize({{x+lw,y,z},w-lw+mySize->RelativeSizeOffset().first,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                myLineEditType->setString(myWidget->Type(),{0.0,0.0,0.0,0.9});
            }
            myLineEditType->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditType->setColor(XColorType::TextColor,Black);
            myLineEditType->draw();
            y+=rh;

            //! New set.
            myLabel->setSize({{x,y,z},lw,rh});
            myLabel->setString("String");
            myLabel->setColor(XColorType::BackgroundColor,LemonChion);
            myLabel->draw();
            myLineEditString->setSize({{x+lw,y,z},w-lw+mySize->RelativeSizeOffset().first,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                myLineEditString->setString(myWidget->String(),{0.0,0.0,0.0,0.9});
            }
            myLineEditString->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditString->setColor(XColorType::TextColor,Black);
            myLineEditString->draw();
            y+=rh;

            //! New set.
            myLabelName->setSize({{x,y,z},lw,rh});
            myLabelName->setString("Name");
            myLabelName->setColor(XColorType::BackgroundColor,White);
            myLabelName->setColor(XColorType::TextColor,Black);
            myLabelName->draw();
            myLineEditName->setSize({{x+lw,y,z},w-lw+mySize->RelativeSizeOffset().first,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                myLineEditName->setString(myWidget->Name(),{0.0,0.0,0.0,0.9});
            }
            myLineEditName->setColor(XColorType::BackgroundColor,White);
            myLineEditName->setColor(XColorType::TextColor,Black);
            myLineEditName->draw();
            y+=rh;

            //! New set.
            myLabel->setSize({{x,y,z},lw,rh});
            myLabel->setString("Origin X");
            myLabel->setColor(XColorType::BackgroundColor,LemonChion);
            myLabel->draw();
            myLineEditOriginX->setSize({{x+lw,y,z},w-lw+mySize->RelativeSizeOffset().first,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                myLineEditOriginX->setString(std::to_string(int(myWidget->Size().Origin().X())),{0.0,0.0,0.0,0.9});
            }
            myLineEditOriginX->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditOriginX->setColor(XColorType::TextColor,Black);
            myLineEditOriginX->draw();
            y+=rh;

            //! New set.
            myLabel->setSize({{x,y,z},lw,rh});
            myLabel->setString("Origin Y");
            myLabel->setColor(XColorType::BackgroundColor,White);
            myLabel->draw();
            myLineEditOriginY->setSize({{x+lw,y,z},w-lw+mySize->RelativeSizeOffset().first,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                myLineEditOriginY->setString(std::to_string(int(myWidget->Size().Origin().Y())),{0.0,0.0,0.0,0.9});
            }
            myLineEditOriginY->setColor(XColorType::BackgroundColor,White);
            myLineEditOriginY->setColor(XColorType::TextColor,Black);
            myLineEditOriginY->draw();
            y+=rh;

            //! New set.
            myLabel->setSize({{x,y,z},lw,rh});
            myLabel->setString("Origin Z");
            myLabel->setColor(XColorType::BackgroundColor,LemonChion);
            myLabel->draw();
            myLineEditOriginZ->setSize({{x+lw,y,z},w-lw+mySize->RelativeSizeOffset().first,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                myLineEditOriginZ->setString(std::to_string(int(myWidget->Size().Origin().Z())),{0.0,0.0,0.0,0.9});
            }
            myLineEditOriginZ->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditOriginZ->setColor(XColorType::TextColor,Black);
            myLineEditOriginZ->draw();
            y+=rh;

            //! New set.
            myLabel->setSize({{x,y,z},lw,rh});
            myLabel->setString("Width");
            myLabel->setColor(XColorType::BackgroundColor,White);
            myLabel->draw();
            myLineEditWidth->setSize({{x+lw,y,z},w-lw+mySize->RelativeSizeOffset().first,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                myLineEditWidth->setString(std::to_string(int(myWidget->Size().Width())),{0.0,0.0,0.0,0.9});
            }
            myLineEditWidth->setColor(XColorType::BackgroundColor,White);
            myLineEditWidth->setColor(XColorType::TextColor,Black);
            myLineEditWidth->draw();
            y+=rh;

            //! New set.
            myLabel->setSize({{x,y,z},lw,rh});
            myLabel->setString("Height");
            myLabel->setColor(XColorType::BackgroundColor,LemonChion);
            myLabel->draw();
            myLineEditHeight->setSize({{x+lw,y,z},w-lw+mySize->RelativeSizeOffset().first,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                myLineEditHeight->setString(std::to_string(int(myWidget->Size().Height())),{0.0,0.0,0.0,0.9});
            }
            myLineEditHeight->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditHeight->setColor(XColorType::TextColor,Black);
            myLineEditHeight->draw();
            y+=rh;

            //! New set.
            myLabel->setSize({{x,y,z},lw,rh});
            myLabel->setString("BorderSize");
            myLabel->setColor(XColorType::BackgroundColor,LemonChion);
            myLabel->draw();
            myLineEditBorderSize->setSize({{x+lw,y,z},w-lw+mySize->RelativeSizeOffset().first,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                myLineEditBorderSize->setString(std::to_string(myWidget->BorderSize()),{0.0,0.0,0.0,0.9});
            }
            myLineEditBorderSize->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditBorderSize->setColor(XColorType::TextColor,Black);
            myLineEditBorderSize->draw();
            y+=rh;

            //! Background color.
            //! Color red.
            myLabel->setSize({{x,y,z},lw,rh});
            myLabel->setString("Background Color");
            myLabel->setColor(XColorType::BackgroundColor,White);
            myLabel->draw();
            myLineEditBackgroundColorRed->setSize({{x+lw,y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::BackgroundColor).Red(),3);
                myLineEditBackgroundColorRed->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditBackgroundColorRed->setColor(XColorType::BackgroundColor,White);
            myLineEditBackgroundColorRed->setColor(XColorType::TextColor,Black);
            myLineEditBackgroundColorRed->draw();

            //! Color green.
            myLineEditBackgroundColorGreen->setSize({{x+lw+((w-lw)/4),y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::BackgroundColor).Green(),3);
                myLineEditBackgroundColorGreen->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditBackgroundColorGreen->setColor(XColorType::BackgroundColor,White);
            myLineEditBackgroundColorGreen->setColor(XColorType::TextColor,Black);
            myLineEditBackgroundColorGreen->draw();

            //! Color blue.
            myLineEditBackgroundColorBlue->setSize({{x+lw+((w-lw)/4)+((w-lw)/4),y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::BackgroundColor).Blue(),3);
                myLineEditBackgroundColorBlue->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditBackgroundColorBlue->setColor(XColorType::BackgroundColor,White);
            myLineEditBackgroundColorBlue->setColor(XColorType::TextColor,Black);
            myLineEditBackgroundColorBlue->draw();

            //! Color alpha.
            myLineEditBackgroundColorAlpha->setSize({{x+lw+((w-lw)/4)+((w-lw)/4)+((w-lw)/4),y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::BackgroundColor).Alpha(),3);
                myLineEditBackgroundColorAlpha->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditBackgroundColorAlpha->setColor(XColorType::BackgroundColor,White);
            myLineEditBackgroundColorAlpha->setColor(XColorType::TextColor,Black);
            myLineEditBackgroundColorAlpha->draw();
            y+=rh;


            //! Border color.
            //! Color red.
            myLabel->setSize({{x,y,z},lw,rh});
            myLabel->setString("Border Color");
            myLabel->setColor(XColorType::BackgroundColor,LemonChion);
            myLabel->draw();
            myLineEditBorderColorRed->setSize({{x+lw,y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::BorderColor).Red(),3);
                myLineEditBorderColorRed->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditBorderColorRed->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditBorderColorRed->setColor(XColorType::TextColor,Black);
            myLineEditBorderColorRed->draw();

            //! Color green.
            myLineEditBorderColorGreen->setSize({{x+lw+((w-lw)/4),y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::BorderColor).Green(),3);
                myLineEditBorderColorGreen->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditBorderColorGreen->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditBorderColorGreen->setColor(XColorType::TextColor,Black);
            myLineEditBorderColorGreen->draw();

            //! Color blue.
            myLineEditBorderColorBlue->setSize({{x+lw+((w-lw)/4)+((w-lw)/4),y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::BorderColor).Blue(),3);
                myLineEditBorderColorBlue->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditBorderColorBlue->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditBorderColorBlue->setColor(XColorType::TextColor,Black);
            myLineEditBorderColorBlue->draw();

            //! Color alpha.
            myLineEditBorderColorAlpha->setSize({{x+lw+((w-lw)/4)+((w-lw)/4)+((w-lw)/4),y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::BorderColor).Alpha(),3);
                myLineEditBorderColorAlpha->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditBorderColorAlpha->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditBorderColorAlpha->setColor(XColorType::TextColor,Black);
            myLineEditBorderColorAlpha->draw();
            y+=rh;


            //! Hover color.
            //! Color red.
            myLabel->setSize({{x,y,z},lw,rh});
            myLabel->setString("Hover Color");
            myLabel->setColor(XColorType::BackgroundColor,White);
            myLabel->draw();
            myLineEditHoverColorRed->setSize({{x+lw,y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::HoverColor).Red(),3);
                myLineEditHoverColorRed->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditHoverColorRed->setColor(XColorType::BackgroundColor,White);
            myLineEditHoverColorRed->setColor(XColorType::TextColor,Black);
            myLineEditHoverColorRed->draw();

            //! Color green.
            myLineEditHoverColorGreen->setSize({{x+lw+((w-lw)/4),y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::HoverColor).Green(),3);
                myLineEditHoverColorGreen->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditHoverColorGreen->setColor(XColorType::BackgroundColor,White);
            myLineEditHoverColorGreen->setColor(XColorType::TextColor,Black);
            myLineEditHoverColorGreen->draw();

            //! Color blue.
            myLineEditHoverColorBlue->setSize({{x+lw+((w-lw)/4)+((w-lw)/4),y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::HoverColor).Blue(),3);
                myLineEditHoverColorBlue->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditHoverColorBlue->setColor(XColorType::BackgroundColor,White);
            myLineEditHoverColorBlue->setColor(XColorType::TextColor,Black);
            myLineEditHoverColorBlue->draw();

            //! Color alpha.
            myLineEditHoverColorAlpha->setSize({{x+lw+((w-lw)/4)+((w-lw)/4)+((w-lw)/4),y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::HoverColor).Alpha(),3);
                myLineEditHoverColorAlpha->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditHoverColorAlpha->setColor(XColorType::BackgroundColor,White);
            myLineEditHoverColorAlpha->setColor(XColorType::TextColor,Black);
            myLineEditHoverColorAlpha->draw();
            y+=rh;

            //! Pressed color.
            //! Color red.
            myLabel->setSize({{x,y,z},lw,rh});
            myLabel->setString("Pressed Color");
            myLabel->setColor(XColorType::BackgroundColor,LemonChion);
            myLabel->draw();
            myLineEditPressedColorRed->setSize({{x+lw,y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::PressedColor).Red(),3);
                myLineEditPressedColorRed->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditPressedColorRed->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditPressedColorRed->setColor(XColorType::TextColor,Black);
            myLineEditPressedColorRed->draw();

            //! Color green.
            myLineEditPressedColorGreen->setSize({{x+lw+((w-lw)/4),y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::PressedColor).Green(),3);
                myLineEditPressedColorGreen->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditPressedColorGreen->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditPressedColorGreen->setColor(XColorType::TextColor,Black);
            myLineEditPressedColorGreen->draw();

            //! Color blue.
            myLineEditPressedColorBlue->setSize({{x+lw+((w-lw)/4)+((w-lw)/4),y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::PressedColor).Blue(),3);
                myLineEditPressedColorBlue->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditPressedColorBlue->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditPressedColorBlue->setColor(XColorType::TextColor,Black);
            myLineEditPressedColorBlue->draw();

            //! Color alpha.
            myLineEditPressedColorAlpha->setSize({{x+lw+((w-lw)/4)+((w-lw)/4)+((w-lw)/4),y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::PressedColor).Alpha(),3);
                myLineEditPressedColorAlpha->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditPressedColorAlpha->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditPressedColorAlpha->setColor(XColorType::TextColor,Black);
            myLineEditPressedColorAlpha->draw();
            y+=rh;

            //! Text color.
            //! Color red.
            myLabel->setSize({{x,y,z},lw,rh});
            myLabel->setString("Text Color");
            myLabel->setColor(XColorType::BackgroundColor,LemonChion);
            myLabel->draw();
            myLineEditTextColorRed->setSize({{x+lw,y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::TextColor).Red(),3);
                myLineEditTextColorRed->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditTextColorRed->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditTextColorRed->setColor(XColorType::TextColor,Black);
            myLineEditTextColorRed->draw();

            //! Color green.
            myLineEditTextColorGreen->setSize({{x+lw+((w-lw)/4),y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::TextColor).Green(),3);
                myLineEditTextColorGreen->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditTextColorGreen->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditTextColorGreen->setColor(XColorType::TextColor,Black);
            myLineEditTextColorGreen->draw();

            //! Color blue.
            myLineEditTextColorBlue->setSize({{x+lw+((w-lw)/4)+((w-lw)/4),y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::TextColor).Blue(),3);
                myLineEditTextColorBlue->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditTextColorBlue->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditTextColorBlue->setColor(XColorType::TextColor,Black);
            myLineEditTextColorBlue->draw();

            //! Color alpha.
            myLineEditTextColorAlpha->setSize({{x+lw+((w-lw)/4)+((w-lw)/4)+((w-lw)/4),y,z},(w-lw)/4,rh});
            //! Enables edit.
            if(!XPip().getPip(Mouse.Position()->Point(),Size())){
                std::setprecision(3);
                std::string str=XColor().ColorNumerToStringWithPresision(myWidget->Color(XColorType::TextColor).Alpha(),3);
                myLineEditTextColorAlpha->setString(str,{0.0,0.0,0.0,0.9});
            }
            myLineEditTextColorAlpha->setColor(XColorType::BackgroundColor,LemonChion);
            myLineEditTextColorAlpha->setColor(XColorType::TextColor,Black);
            myLineEditTextColorAlpha->draw();
            y+=rh;

            //! Events.
            if(!myModeDesigner){
            myWidget->setName(myLineEditName->Text());
            myWidget->setString(myLineEditString->Text());
            myWidget->setBorderSize(stringToValueFailsave(myLineEditBorderSize->Text()));
            myWidget->setSize({{std::stof(myLineEditOriginX->Text()),
                                std::stof(myLineEditOriginY->Text()),
                                std::stof(myLineEditOriginZ->Text())},std::stof(myLineEditWidth->Text()),std::stof(myLineEditHeight->Text())});

            //! Ensure failsafe lineEdit input.
            XColor aColor;
            aColor={stringToValueFailsave(myLineEditBackgroundColorRed->Text()),
                    stringToValueFailsave(myLineEditBackgroundColorGreen->Text()),
                    stringToValueFailsave(myLineEditBackgroundColorBlue->Text()),
                    stringToValueFailsave(myLineEditBackgroundColorAlpha->Text())};
            myWidget->setColor(XColorType::BackgroundColor,aColor);

            //! Ensure failsafe lineEdit input.
            aColor={stringToValueFailsave(myLineEditBorderColorRed->Text()),
                    stringToValueFailsave(myLineEditBorderColorGreen->Text()),
                    stringToValueFailsave(myLineEditBorderColorBlue->Text()),
                    stringToValueFailsave(myLineEditBorderColorAlpha->Text())};
            myWidget->setColor(XColorType::BorderColor,aColor);

            //! Ensure failsafe lineEdit input.
            aColor={stringToValueFailsave(myLineEditHoverColorRed->Text()),
                    stringToValueFailsave(myLineEditHoverColorGreen->Text()),
                    stringToValueFailsave(myLineEditHoverColorBlue->Text()),
                    stringToValueFailsave(myLineEditHoverColorAlpha->Text())};
            myWidget->setColor(XColorType::HoverColor,{aColor});

            //! Ensure failsafe lineEdit input.
            aColor={stringToValueFailsave(myLineEditPressedColorRed->Text()),
                    stringToValueFailsave(myLineEditPressedColorGreen->Text()),
                    stringToValueFailsave(myLineEditPressedColorBlue->Text()),
                    stringToValueFailsave(myLineEditPressedColorAlpha->Text())};
            myWidget->setColor(XColorType::PressedColor,aColor);

            //! Ensure failsafe lineEdit input.
            aColor={stringToValueFailsave(myLineEditTextColorRed->Text()),
                    stringToValueFailsave(myLineEditTextColorGreen->Text()),
                    stringToValueFailsave(myLineEditTextColorBlue->Text()),
                    stringToValueFailsave(myLineEditTextColorAlpha->Text())};
            myWidget->setColor(XColorType::TextColor,aColor);
            }
        }

        //! draw content.
        for(uint i=0; i<WidgetVec().size(); i++){
            WidgetVec().at(i)->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            WidgetVec().at(i)->draw();
        }
    }
    //! Non virtual functions.
    void setWidget(XWidget *theWidget){
        myWidget=theWidget;
    }
    float stringToValueFailsave(std::string theString){
        //! Remove empty spaces adde by lineEdit.
        while(theString.back()==' '){
            theString.pop_back();
        }
        //! If string size is zero, set a value.
        if(theString.size()==0){
            theString="0";
        }
        return std::stof(theString);
    }
    void setModeDesigner(bool theStatus){
        myModeDesigner=theStatus;
    }

private:
    XSize *mySize=new XSize();
    float myBorderSize=5;
    XRectangular *myBackground;
    XRectangular *myBorder;
    XString *myString=new XString("WidgetPropertyInputList");
    XColor //! Create colors and set standard values.
    *myBackgroundColor=new XColor(0.1,0.1,0.1,0.9),
    *myBorderColor=new XColor(0.0,0.0,0.0,0.9),
    *myHoverColor=new XColor(0.2,0.2,0.2,0.9),
    *myPressedColor=new XColor(0.3,0.3,0.3,0.9),
    *myTextColor=new XColor(1.0,1.0,1.0,0.9);
    XWidget *myWidget;
    XLabel *myLabel, *myLabelName;
    XLineEdit
    *myLineEditType,
    *myLineEditName,
    *myLineEditString,
    *myLineEditOriginX,
    *myLineEditOriginY,
    *myLineEditOriginZ,
    *myLineEditWidth,
    *myLineEditHeight,
    *myLineEditBorderSize,
    *myLineEditBackgroundColorRed,
    *myLineEditBackgroundColorGreen,
    *myLineEditBackgroundColorBlue,
    *myLineEditBackgroundColorAlpha,
    *myLineEditBorderColorRed,
    *myLineEditBorderColorGreen,
    *myLineEditBorderColorBlue,
    *myLineEditBorderColorAlpha,
    *myLineEditHoverColorRed,
    *myLineEditHoverColorGreen,
    *myLineEditHoverColorBlue,
    *myLineEditHoverColorAlpha,
    *myLineEditPressedColorRed,
    *myLineEditPressedColorGreen,
    *myLineEditPressedColorBlue,
    *myLineEditPressedColorAlpha,
    *myLineEditTextColorRed,
    *myLineEditTextColorGreen,
    *myLineEditTextColorBlue,
    *myLineEditTextColorAlpha;

    bool myInit=0, myModeDesigner=0;
};

#endif























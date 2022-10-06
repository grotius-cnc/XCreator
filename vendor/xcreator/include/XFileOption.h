#ifndef XFILEOPTION_H
#define XFILEOPTION_H

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

#include <XButton.h>
#include <XLineEdit.h>

class XFileOption : public XWidget {
public:
    //! Constructor setting the glfwWindow pointer.
    XFileOption(XWindow *theWindow){
        this->setWindow(theWindow);
        setScissorWindow(theWindow);
    }
    //! Destructor.
    ~XFileOption(){}

    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XFileOption";
    }
    //! Set the size of this widget. Size also handles the mouse & key events.
    void setSize(XSize theSize){
        mySize->setSize(theSize);
    }
    //! Add a origin offset.
    void setSizeOffset(XPoint theValue){
        mySize->setSizeOffset(theValue);
    }
    //! Return the size.
    XSize Size(){
        return mySize->Size();
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
    void init(){
        mySize->setSize({{0,0,0},200,200});

        myButton=new XButton(Window());
        myButton->setName("Button_ok");
        myButton->setString(" Ok");
        myButton->setCenterText(0,1);
        addWidget(myButton);

        myLineEdit=new XLineEdit(Window());
        addWidget(myLineEdit);
    }
    void draw(){
        //! Save the current scissor size to be restored at end of this function.
        saveScissorState();
        //! Set the scissor union size.
        setScissorUnion(ParentScissorSize(),mySize->Size());

        if(myShow){
            Mouse.setScrollLock(1);

            std::cout<<"myPath:"<<myPath<<std::endl;

            if(myButton->isPressed()){
                //! Set new name for myFilePath.
                std::string parentDir=std::filesystem::path(myPath).parent_path();
                myNewPath=parentDir+"/"+myLineEdit->Text();

                std::filesystem::rename(myPath,myNewPath);
                myNewString=std::filesystem::path(myNewPath).filename();
                myShow=0;



                //! Uplevel widget has to update the modified file view.
                myFileUpdate=true;
            }

            drawWidgetVec();
        }
        if(!myShow){
            Mouse.setScrollLock(0);
        }
        //! Restore the scissor size.
        restoreScissorState();
    }
    void show(XPoint thePosition){
        myLineEdit->setSize({{thePosition.X(),thePosition.Y(),thePosition.Z()},mySize->Width(),20});
        myLineEdit->setString(myText);
        myButton->setSize({{thePosition.X(),thePosition.Y()+20,thePosition.Z()},50,20});
        mySize->setSize({thePosition,mySize->Width(),mySize->Height()});
        //! Toggle.
        myShow=!myShow;
    }
    void hide(){
        myShow=false;
    }
    bool isVisible(){
        return myShow;
    }
    void setText(std::string theText, std::string thePath){
        myText=theText;
        myPath=thePath;
        // myNewPath=thePath;
        // myNewPath.append("x");
        std::cout<<"theText:"<<myText<<std::endl;

        mySize->setWidth(XText().StringWidth(myText)+200);
    }
    bool NeedFileUpdate(){
        bool result=myFileUpdate;
        myFileUpdate=0;
        return result;
    }
    std::string NewPath(){
        return myNewPath;
    }
    std::string NewString(){
        return myNewString;
    }

private:
    std::string myName;
    XSize *mySize=new XSize();
    XButton *myButton;
    XLineEdit *myLineEdit;
    bool myShow=false;
    std::string myText, myPath, myNewPath, myNewString;
    bool myFileUpdate=0;
};
#endif




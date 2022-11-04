#ifndef XLINEEDIT_H
#define XLINEEDIT_H

#include <XWidget.h>
#include <XRectangular.h>
#include <XMouse.h>
#include <XKey.h>
#include <XText.h>
#include <XFile.h>
#include <XSize.h>
#include <XChar.h>
#include <XScissor.h>
// #include <XKeyWord.h>
// #include <clip.h> // https://github.com/dacap/clip/
//! To be reviewed.
class XLineEdit : public XWidget  {
public:
    //! Empty constructor, set the GLFWwindow pointer afterwards.
    XLineEdit(){}
    //! Constructor setting the GLFWwindow pointer.
    XLineEdit(XWindow *theWindow){
        this->setWindow(theWindow);
    }
    //! Various init methodes.
    void init(){
        init(13,2);
    }
    //! Initialisation function.
    void init(float theFontSize, float theVerticalFontSpace){
        myFontSize=theFontSize;
        myVerticalFontSpace=theVerticalFontSpace;

        myEditor->setWindow(Window());
        myBackground=new XRectangular(Window());
        myBorder=new XRectangular(Window());

        myCursor=new XRectangular(Window());
        myCursor->setColor({1.0,0.0,0.0,1.0});
        myCursor->setSize({{0,0,0},2,myFontSize});

        mySelectionRectangular=new XRectangular(Window());
        mySelectionRectangular->setColor({1.0,1.0,0.0,0.25});
        mySelectionRectangular->setSize({{0,0,0},0,0});

        setScissorWindow(Window());

        //! During startup somehow a key is pressed wich will result in a char on the screen. Avoid this.
        Key.resetScanCode();
        myInit=1;
    }
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XLineEdit";
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
    //! Return the size.
    XSize Size(){
        return mySize->Size();
    }
    //! Return the size pointer, pointing to the size.
    XSize* SizePointer(){
        return mySize->SizePointer();
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
        std::cout<<"Error from class XLineEdit, function XColor Color(XColorType theColorType){}"<<std::endl;
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
    //! String size width.
    float StringWidth(){
        return XText().StringWidth(myString->toStdString());
    }
    //! Draw content.
    void draw(){
        if(!myInit){
            init(13,2);
        }
        //! Save the current scissor size to be restored at end of this function.
        saveScissorState();

        if(myModeEdit){
            mySize->setReturnSizeIncludingRelativeOffsets(0);
        } else {
            mySize->setReturnSizeIncludingRelativeOffsets(1);
        }

        if(Mouse.GlfwWindowPointer()==Window()->GlfwWindowPointer()){ //! Only process the current active window for mouse events.
            MouseEvents();
        }
        if(Key.GlfwWindowPointer()==Window()->GlfwWindowPointer()){ //! Only process the current active window for key events.
            KeyboardEvents();
        }

        //! There are two algo's processing the visible part of the text. Text positioned out of the screen coordinates is not processed by the XText class.
        //! GlScissor && getStartCharNr+getEndCharNr are used to process the visible part of the text.
        //! These algo's will keep the gui responsive with huge text files.
        myBorder->setSize(mySize->Size());
        if(myModeEdit){
            myBorder->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            myBorder->setRelativeSizeOffset(mySize->RelativeSizeOffset());
        }
        myBorder->setColor(myBorderColor->Color());
        myBorder->draw();

        myBackground->setSize(mySize->Size().MarginSize(myBorderSize));
        if(myModeEdit){
            myBackground->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            myBackground->setRelativeSizeOffset(mySize->RelativeSizeOffset());
        }
        myBackground->setColor(myBackgroundColor->Color());
        myBackground->draw();

        myEditor->setSize({{mySize->Origin().X()+myLeftMargin+myBorderSize,
                            mySize->Origin().Y()+myBorderSize,
                            mySize->Origin().Z()},mySize->Width()-(2*myBorderSize),mySize->Height()-(2*myBorderSize)});
        if(myModeEdit){
            myEditor->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            myEditor->setRelativeSizeOffset(mySize->RelativeSizeOffset());
        }

        //! Set the scissor size, for designermode we include the relative offsets.
        if(hasParent()){
            setScissorUnion(ParentScissorSize(),myBackground->SizeIncludeOffsets());
        }

        myString->setColorToString(myTextColor->Color());
        myEditor->drawText(*myString,getStartCharNrMyText(),getEndCharNrMyText(),0,0);
        drawSelectedText();
        if(Mouse.GlfwWindowPointer()==Window()->GlfwWindowPointer()){
            drawCursor();
        }

        //! Draw ChildVec content.
        for(uint i=0; i<WidgetVec().size(); i++){
            WidgetVec().at(i)->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            //! The child widgets will call the parent scissor size by itself.
            WidgetVec().at(i)->draw();
        }
        //! Restore the scissor size.
        restoreScissorState();
    }
    //! Non virtual functions.
    //! Set the text and specify textcolor.
    void setString(std::string theText, XColor theColor){
        myString->setStringFromStdString(theText);
        myString->setColorToString(theColor);
    }
    //! Set one character.
    void setCharInText(uint thePosition, XChar theChar){
        myString->at(thePosition).setChar(theChar);
    }
    //! Clear text.
    void clearText(){
        myString->clear();
    }
    //! Return the text.
    std::string Text(){
        return myString->toStdString();
    }
    //! set left text margin.
    void setLeftMargin(float theLeftMargin){
        myLeftMargin=theLeftMargin;
    }
    //! When using XDesignerFrame.
    void setModeEdit(bool theStatus){
        myModeEdit=theStatus;
    }

private:
    // XKeyWord *myKeyWord;
    XText *myEditor=new XText();
    XRectangular *myBackground, *myBorder;
    XRectangular *myCursor,*mySelectionRectangular;
    XSize *mySize=new XSize();
    XColor //! Create colors and set standard values.
    *myBackgroundColor=new XColor(0.1,0.1,0.1,0.9),
    *myBorderColor=new XColor(0.0,0.0,0.0,0.9),
    *myHoverColor=new XColor(0.2,0.2,0.2,0.9),
    *myPressedColor=new XColor(0.3,0.3,0.3,0.9),
    *myTextColor=new XColor(1.0,1.0,1.0,0.9);
    float myFontSize=14.0, myVerticalFontSpace=0.0, myLeftMargin=5, myBorderSize=1;
    bool myLeftMouseButtonTrigger=0;
    uint myCursorCount=0;
    std::vector<std::string> myRestoreTextVec={};
    XString *myString=new XString();
    XString *myIndexText=new XString();
    uint mySelectionStartCharNr=0, mySelectionEndCharNr=0;
    bool myInit=0;
    bool myModeEdit=0;

    //! Get the line count of the view.
    int getLineCountOfView(){
        return mySize->Height()/(myFontSize+myVerticalFontSpace);
    }
    //! Get the line count of the total text.
    int getTotalLineCount(){
        uint theLineCount=0;
        for(uint i=0; i<myString->size(); i++){
            if(myString->at(i).Char()==XChar('\n').Char()){
                theLineCount++;
            }
        }
        return theLineCount;
    }
    //! Get line number where mouse cursor is blinking.
    uint getCurrentCursorLineNr(){
        uint theLineCount=0;
        uint theCharCount=0;
        for(uint i=0; i<myString->size(); i++){
            theCharCount++;
            if(myString->at(i).Char()==XChar('\n').Char()){
                theLineCount++;
            }
            if(theCharCount==myCursorCount){
                return  theLineCount;
            }
        }
        return theLineCount;
    }
    //! Start offset for y.
    float getStartOffset(){
        return 0;
    }
    //! The first char to display.
    uint getStartCharNrMyText(){
        return 0;
    }
    //! The last char to display.
    uint getEndCharNrMyText(){
        return myString->size();
    }
    //! The first line index nr. char to display.
    uint getStartCharNrMyIndexText(){
        return 0;
    }
    //! The current text selection.
    std::string getSelectedText(){
        std::string theSelection;
        uint start=mySelectionStartCharNr;
        uint end=mySelectionEndCharNr;
        if(end<start){
            uint temp=start;
            start=end;
            end=temp;
        }
        for(uint i=0; i<myString->size(); i++){
            if(i>=start && i<= end){
                theSelection.push_back(myString->at(i).Char());
            }
        }
        return theSelection;
    }
    //! Set closest cursor position given a mouse click.
    void setClosestCursorPressedPos(){
        //! This solves setting the mouse cursor after last character when having only one text line.
        bool newLine=0;
        for(uint i=0; i<myString->size(); i++){
            if(myString->at(i).Char()=='\n'){
                newLine=1;
            }
        }
        if(!newLine){
            if(myString->size()>0){
                if(myString->at(myString->size()-1).Char()!=' '){
                    myString->push_back(' ');
                }
            }
        }

        float mpx=(Mouse.X()-myEditor->Size().Origin().X()); // std::cout<<"mousepos x:"<<(Mouse.X()-myEditor->X())-newX<<" y:"<<(Mouse.Y()-myEditor->Y())-newY<<std::endl;
        float mpy=(Mouse.Y()-myEditor->Size().Origin().Y());
        float sampleDist=INFINITY;
        float cpx=0.0; float cpy=0.0;
        bool noNewLine=0;
        for(uint i=0; i<myString->size(); i++){
            float dist=sqrt(pow(cpx-mpx,2)+pow(cpy-mpy,2));
            if(dist<=sampleDist){
                sampleDist=dist;
                myCursorCount=i;
            }
            if(myString->at(i).Char()=='\n'){
                cpy+=(myFontSize+myVerticalFontSpace);
                cpx=0;
                noNewLine=1;
            } else {
                cpx+=myEditor->CharacterPixelWidth(myString->at(i).Char());
            }
        }
    }
    //! Return char count under blinking cursor.
    uint getCharNrUnderCursorPos(){
        uint theCharNr=0;
        float mpx=(Mouse.X()-myEditor->Size().Origin().X()); // std::cout<<"mousepos x:"<<(Mouse.X()-myEditor->X())-newX<<" y:"<<(Mouse.Y()-myEditor->Y())-newY<<std::endl;
        float mpy=(Mouse.Y()-myEditor->Size().Origin().Y());
        float sampleDist=INFINITY;
        float cpx=0.0; float cpy=0.0;
        for(uint i=0; i<myString->size(); i++){
            float dist=sqrt(pow(cpx-mpx,2)+pow(cpy-mpy,2));
            if(dist<=sampleDist){
                sampleDist=dist;
                theCharNr=i;
            }
            if(myString->at(i).Char()=='\n'){
                cpy+=(myFontSize+myVerticalFontSpace);
                cpx=0;
            } else {
                cpx+=myEditor->CharacterPixelWidth(myString->at(i).Char());
            }
        }
        return theCharNr;
    }
    //! Process keyboard events.
    void KeyboardEvents(){
        //! Process key events for the correct widget.
        if(XPip().getPip(Mouse.Position()->Point(),mySize->Size())){
            if(Key.isGlfwRightKey()){
                if(myCursorCount<myString->size()){
                    myCursorCount++;
                }
            }
            if(Key.isGlfwLeftKey()){
                myCursorCount--;
            }
            if(Key.isGlfwUpKey()){
            }
            if(Key.isGlfwDownKey()){
            }
            if(Key.isGlfwPageDown()){
            }
            if(Key.isGlfwPageUp()){
            }
            if(Key.isGlfwEnterKey()){
                // myText.insert(myCursorCount,XChar('\n'));
                // myCursorCount++;
                Key.resetScanCode();
            }
            if(Key.isGlfwBackSpaceKey()){
                if(myCursorCount>0){
                    myString->erase(myCursorCount);
                    myCursorCount--;
                }
            }
            if(Key.isGlfwTabKey()){
                myString->insert(myCursorCount,XChar(' '));
                myCursorCount++;
                myString->insert(myCursorCount,XChar(' '));
                myCursorCount++;
                myString->insert(myCursorCount,XChar(' '));
                myCursorCount++;
                myString->insert(myCursorCount,XChar(' '));
                myCursorCount++;
                Key.resetScanCode();
            }
            if(Key.getGlfwCharKey()!=-1){
                myString->insert(myCursorCount,XChar(Key.getGlfwCharKey(),{0.0,0.0,0.0,0.9}));
                myCursorCount++;
                Key.resetScanCode();
            }
            if(Key.isGlfwControlAKey()){
                //! clip::set_text(myText.toStdString());
                mySelectionStartCharNr=0;
                mySelectionEndCharNr=myString->size();
            }
            if(Key.isGlfwControlCKey()){
                //! clip::set_text(getSelectedText());
            }
            if(Key.isGlfwControlVKey()){
                std::string value;
                //! clip::get_text(value);
                myString->insert(myCursorCount,value);
                myCursorCount+=value.size();
            }
            if(Key.isGlfwControlXKey()){
                //! Copy selected text to clip.
                //!clip::set_text(getSelectedText());
                //! Remove the selexted text from the myText.
                XString *theResult;
                uint start=mySelectionStartCharNr;
                uint end=mySelectionEndCharNr;
                if(start>end){
                    uint temp=start;
                    start=end;
                    end=temp;
                }
                for(uint i=0; i<myString->size(); i++){
                    if(i>=start && i<end){
                        //! Do nothing with the selection.
                    } else {
                        theResult->push_back(myString->at(i));
                    }
                }
                myString=theResult;

                // Update cursorposition. The cursorcount is a uint and does not like a negative value.
                int ensurePosCursorCountValue=myCursorCount-(end-start);
                if(ensurePosCursorCountValue<0){ensurePosCursorCountValue=0;}
                myCursorCount=ensurePosCursorCountValue;
            }
        }
    }
    //! Process mouse events.
    void MouseEvents(){
        if(myEditor->Event(XEventEnum::PressedMid)){
        }
        if(myEditor->Event(XEventEnum::DraggedMid)){
        }
        if(myEditor->Event(XEventEnum::ReleasedMid)){
        }
        if(myEditor->Event(XEventEnum::Hovered)){
        }
        if(myEditor->Event(XEventEnum::PressedLeft) && !myLeftMouseButtonTrigger){
            setClosestCursorPressedPos();
            mySelectionStartCharNr=getCharNrUnderCursorPos();
            myLeftMouseButtonTrigger=1;
        }
        if(myEditor->Event(XEventEnum::ReleasedLeft)){
            myLeftMouseButtonTrigger=0;
        }
        if(myLeftMouseButtonTrigger){
            mySelectionEndCharNr=getCharNrUnderCursorPos();
        }
    }
    //! Draw the blinking cursor.
    void drawCursor(){
        float cpx=0; float cpy=0; //! cursor position.
        for(uint i=0; i<myString->size(); i++){
            //! std::cout<<"myText at i:"<<i<<" text:"<<myText.at(i)<<std::endl;
            if(myCursorCount==i){
                break;
            }
            if(myString->at(i).Char()== XChar('\n').Char()){
                cpy+=(myFontSize+myVerticalFontSpace);
                cpx=0;
            }  else {
                cpx+=myEditor->CharacterPixelWidth(myString->at(i).Char());
            }
        }
        myCursor->setSize({{myEditor->Size().Origin().X()+cpx,myEditor->Size().Origin().Y()+cpy,
                            myEditor->Size().Origin().Z()},
                           myCursor->Size().Width(),
                           myCursor->Size().Height()});
        if(myModeEdit){
            myCursor->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            //! No size offset for cursor.
        }
        if(Mouse.Time()>500 && XPip().getPip(Mouse.Position()->Point(),mySize->Size())){ //! Blinking cursor.
            //! Draw the cursor only in the editor window, do not draw the cursor outside this region.
            myCursor->draw();
        }
    }
    //! Draw the selected text rectangulars.
    void drawSelectedText(){ //! Masterpiece.
        uint start=mySelectionStartCharNr;
        uint end=mySelectionEndCharNr;
        if(end<start){ //! Swap.
            uint temp=start;
            start=end;
            end=temp;
        }
        float cpx=0.0; float cpy=2.0;
        float dx=0;
        for(uint i=0; i<myString->size(); i++){
            if(start==i){
                mySelectionRectangular->setSize({{myEditor->Size().Origin().X()+cpx,myEditor->Size().Origin().Y()+cpy,0},mySelectionRectangular->Size().Width(),mySelectionRectangular->Size().Height()});
                dx=cpx;
            }
            if(end==i){
                mySelectionRectangular->setSize({{mySelectionRectangular->Size().Origin().X(),
                                                  mySelectionRectangular->Size().Origin().Y(),
                                                  mySelectionRectangular->Size().Origin().Z()},cpx-dx,(myFontSize+myVerticalFontSpace)-1});
                if(!myModeEdit){
                    mySelectionRectangular->draw();
                }
                return;
            }
            if(i>=start && i<=end && myString->at(i).Char()=='\n'){
                mySelectionRectangular->setSize({{mySelectionRectangular->Size().Origin().X(),
                                                  mySelectionRectangular->Size().Origin().Y(),
                                                  mySelectionRectangular->Size().Origin().Z()},cpx-dx,(myFontSize+myVerticalFontSpace)-1});
                if(!myModeEdit){
                    mySelectionRectangular->draw();
                }
            }
            if(myString->at(i).Char()=='\n'){
                cpy+=(myFontSize+myVerticalFontSpace);
                cpx=0;
                dx=0;
            } else {
                cpx+=myEditor->CharacterPixelWidth(myString->at(i).Char());
            }
            if(i>=start && i<=end && myString->at(i).Char()=='\n'){
                mySelectionRectangular->setSize({{myEditor->Size().Origin().X(),myEditor->Size().Origin().Y()+cpy,0},
                                                 mySelectionRectangular->Size().Width(),
                                                 mySelectionRectangular->Size().Height()});
            }
        }
    }
};
#endif

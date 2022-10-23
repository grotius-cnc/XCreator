#ifndef XTEXTEDIT_H
#define XTEXTEDIT_H

#include <XWidget.h>
#include <XRectangular.h>
#include <XMouse.h>
#include <XKey.h>
#include <XText.h>
#include <XFile.h>
#include <XSize.h>
#include <XChar.h>
#include <XCursor.h>
// #include <XKeyWord.h>
#include <clip.h> // https://github.com/dacap/clip/

//! Todo. limit dragging to editor scissor area.

//! Mention that the XSize returns a size including the relative offsets. This is done by setting the flag setReturnSizeIncludingRelativeOffsets to 1.
class XTextEdit : public XWidget  {
public:
    //! Empty constructor, set the GLFWwindow pointer afterwards.
    XTextEdit(){}
    //! Constructor setting the GLFWwindow pointer.
    XTextEdit(XWindow *theWindow){
        this->setWindow(theWindow);
    }
    //! Various init methodes.
    void init(){
        init(13,2,true);
    }
    //! Initialize without line number index at left.
    void init_WithoutLineNrIndex(){
        init(13,2,false);
    }
    //! Initialize without line number index and no edit mode, view only.
    void init_WithoutLineNrIndex_ModeViewOnly(){
        init(13,2,false);
        myViewOnly=true;
    }
    //! Initialisation function.
    void init(float theFontSize, float theVerticalFontSpace, bool showLineNrIndex){
        myFontSize=theFontSize;
        myVerticalFontSpace=theVerticalFontSpace;
        myShowLineNrIndex=showLineNrIndex;

        myEditor=new XText(Window());

        myBorder=new XRectangular(Window());
        myBorder->setColor(myBorderColor->Color());

        myBackground=new XRectangular(Window());
        myBackground->setColor(myBackgroundColor->Color());

        // myKeyWord=new XKeyWord();

        if(myShowLineNrIndex){
            myLineNrIndex=new XText(Window());
            mySpacer=new XRectangular(Window());
            mySpacer->setColor({0.1,0.5,0.1,0.9});
        }

        myCursor=new XRectangular(Window());
        myCursor->setColor({1.0,0.0,0.0,1.0});
        myCursor->setSize({{0,0,0},2,myFontSize});

        myCursorIcon=new XCursor(Window());

        mySelectionRectangular=new XRectangular(Window());
        mySelectionRectangular->setColor({1.0,1.0,0.0,0.25});
        mySelectionRectangular->setSize({{0,0,0},0,0});

        //! During startup somehow a key is pressed wich will result in a char on the screen. Avoid this.
        Key.resetScanCode();
        Key.resetKey();
        myInit=1;

        mySize->setReturnSizeIncludingRelativeOffsets(1);

        setScissorWindow(Window());
    }
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XTextEdit";
    }
    //! Set the size of this widget. Size also handles the mouse & key events.
    void setSize(XSize theSize){
        mySize->setSize(theSize.Size());
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
    //! Draw content.
    void draw(){
        if(!myInit){
            init(13,2,true);
        }
        //! Save the current scissor size to be restored at end of this function.
        saveScissorState();

        //! Prevents widget mirroring.
        if(mySize->Width()>0 && mySize->Height()>0){

            if(myModeEdit){
                mySize->setReturnSizeIncludingRelativeOffsets(0);
            } else {
                mySize->setReturnSizeIncludingRelativeOffsets(1);
            }

            if(myShowLineNrIndex){
                myIndexWidth=processIndexWidth();
                myLineNrIndex->setSize({{mySize->Origin().X(),mySize->Origin().Y(),mySize->Origin().Z()},myIndexWidth,mySize->Height()});
                mySpacer->setSize({{mySize->Origin().X()+myIndexWidth,mySize->Origin().Y(),mySize->Origin().Z()},mySpacerWidth,mySize->Height()});
            } else {
                mySpacerWidth=0;
            }

            if(!myViewOnly){
                if(Mouse.GlfwWindowPointer()==Window()->GlfwWindowPointer()){ //! Only process the current active window for mouse events.
                    MouseEvents();
                }
                if(Key.GlfwWindowPointer()==Window()->GlfwWindowPointer()){ //! Only process the current active window for key events.
                    //! Process key events when inside the parent scissor size.
                    if(XPip().getPipFromMousePos(ParentScissorSize())){
                        KeyboardEvents();
                    }
                }
            }
            //! Process keywords for a specific programming language etc.
            //! The keywords are only processed for the visible part of the gui.
            //! Just like google maps processes only the part that is viewed and not the whole planet is loaded into memory.
            if(!myViewOnly){
                // myText=myKeyWord->process(myText,getStartCharNrMyText(),getEndCharNrMyText());
            }
            //! There are two algo's processing the visible part of the text. Text positioned out of the screen coordinates is not processed by the XText class.
            //! GlScissor && getStartCharNr+getEndCharNr are used to process the visible part of the text.
            //! These algo's will keep the gui responsive with huge text files.
            myBorder->setSize(mySize->Size());
            if(myModeEdit){
                myBorder->setRelativeOriginOffset(mySize->RelativeOriginOffset());
                myBorder->setRelativeSizeOffset(mySize->RelativeSizeOffset());
            }
            myBorder->draw();

            myBackground->setSize(mySize->Size().MarginSize(myBorderSize));
            if(myModeEdit){
                myBackground->setRelativeOriginOffset(mySize->RelativeOriginOffset());
                myBackground->setRelativeSizeOffset(mySize->RelativeSizeOffset());
            }
            myBackground->draw();

            myEditor->setSize({{mySize->Origin().X()+myIndexWidth+mySpacerWidth,
                                mySize->Origin().Y(),
                                mySize->Origin().Z()},
                               mySize->Width()-(myIndexWidth+mySpacerWidth),mySize->Height()});
            if(myModeEdit){
                myEditor->setRelativeOriginOffset(mySize->RelativeOriginOffset());
                myEditor->setRelativeSizeOffset(mySize->RelativeSizeOffset());
            }
            //! fuck.
            // myString.setColorToString(myTextColor->Color());


            if(myEditor->Event(XEventEnum::Hovered) && XPip().getPipFromMousePos(ParentScissorSize()) && !Mouse.isPressedLeftButton()){
                myCursorIcon->setIBeamCursor();
            } else
                if(myBorder->Event(XEventEnum::Hovered) && XPip().getPipFromMousePos(ParentScissorSize()) && !Mouse.isPressedLeftButton()){
                    myCursorIcon->revertToDefaultCursor();
                } else
                    if(mySpacer->Event(XEventEnum::Hovered) && XPip().getPipFromMousePos(ParentScissorSize())&& !Mouse.isPressedLeftButton()){
                        myCursorIcon->revertToDefaultCursor();
                    } else
                        if(myLineNrIndex->Event(XEventEnum::Hovered) && XPip().getPipFromMousePos(ParentScissorSize())&& !Mouse.isPressedLeftButton()){
                            myCursorIcon->revertToDefaultCursor();
                        }

            //! Set the scissor size, for designermode we include the relative offsets.
            if(hasParent()){
                setScissorUnion(ParentScissorSize(),myBackground->SizeIncludeOffsets());
            }

            myEditor->drawText(myString,getStartCharNrMyText(),getEndCharNrMyText(),newX,newY+getStartOffset(),0);
            //! Draw mouse cursor when in edit mode.
            if(!myViewOnly){
                drawSelectedText();
                if(Mouse.GlfwWindowPointer()==Window()->GlfwWindowPointer()){
                    drawCursor();
                }
            }

            //! When line number index is active.
            if(myShowLineNrIndex){
                if(myModeEdit){
                    mySpacer->setRelativeOriginOffset(mySize->RelativeOriginOffset());
                    mySpacer->setRelativeSizeOffset({0,mySize->RelativeSizeOffset().second});
                }
                mySpacer->draw();
                if(mySpacer->Event(XEventEnum::PressedLeft)){
                    //! Set text position to zero.
                    newX=0, newY=0;
                }
                if(mySpacer->Event(XEventEnum::ReleasedLeft)){ }
                processIndexText();
            }

            //! Draw ChildVec content.
            for(uint i=0; i<WidgetVec().size(); i++){
                WidgetVec().at(i)->setRelativeOriginOffset(mySize->RelativeOriginOffset());
                WidgetVec().at(i)->draw();
            }
        }
        //! Restore the scissor size.
        restoreScissorState();
    }
    //! Used for terminal implementation.
    std::string Command(){
        return myCommand;
    }
    void resetCommand(){
        myCommand="";
    }
    //! Non virtual functions.
    //! Load textfile.
    void loadFile(std::string theFileName){
        myString=XFile().readTextFile(theFileName);
        myFileName=theFileName;
    }
    //! Set the text and specify textcolor.
    void setText(std::string theText, XColor theColor){
        myString.setStringFromStdString(theText);
        myString.setColorToString(theColor);
    }
    //! Set text.
    void setText(std::string theText){
        myString.setStringFromStdString(theText);
    }
    //! Set one character.
    void setCharInText(uint thePosition, XChar theChar){
        myString.at(thePosition).setChar(theChar);
    }
    //! Append
    void appendText(XString theText){
        myString.insert(myString.size(),theText);
        myCursorCount+=theText.size();
    }
    //! Clear text.
    void newFile(){
        myString.clear();
    }
    //! Save file using myFileName.
    void saveFile(){
        XFile().saveFile(myFileName,myString.toStdString());
    }
    //! Save file given the filename path.
    void saveFile(std::string theFileName){
        XFile().saveFile(theFileName,myString.toStdString());
    }
    //! Set no edit mode.
    void setViewOnly(bool theValue){
        myViewOnly=theValue;
    }
    //! Set text drage move enable.
    void setScrollEnable(bool theValue){
        myScrollEnable=theValue;
    }
    //! Return the text.
    std::string Text(){
        return myString.toStdString();
    }
    //! Use OpenGl scissor. Display only a certain size.
    void useGlScissor(bool theValue){
        myUseGlScissor=theValue;
    }
    //! Enable or disable editing text.
    void setModeEdit(bool theStatus){
        myModeEdit=theStatus;
    }
    //! Reset some values to init stage.
    void reset(){
        myCursorCount=0;
        myString.clear();
        myCommand.clear();
        Key.resetScanCode();
        Key.resetKey();
        //! Set text position to zero.
        newX=0, newY=0;
    }
private:
    // XKeyWord *myKeyWord;
    XText *myLineNrIndex;
    XText *myEditor;
    XRectangular *myBackground;
    XRectangular *myBorder;
    float myBorderSize=1;
    XRectangular *mySpacer,*myCursor,*mySelectionRectangular;
    XSize *mySize=new XSize();
    XColor //! Create colors and set standard values.
    *myBackgroundColor=new XColor(0.1,0.1,0.1,0.9),
    *myBorderColor=new XColor(0.0,0.0,0.0,0.9),
    *myHoverColor=new XColor(0.2,0.2,0.2,0.9),
    *myPressedColor=new XColor(0.3,0.3,0.3,0.9),
    *myTextColor=new XColor(1.0,1.0,1.0,0.9);
    XPoint *myMidSnapshot=new XPoint();
    float myIndexWidth=0.0,mySpacerWidth=10.0,myFontSize=14.0,myVerticalFontSpace=0.0;
    //! Mid mouse text drag values.
    float newX=0.0,oldX=0.0,newY=0.0,oldY=0.0;
    bool myLeftMouseButtonTrigger=0, myShowLineNrIndex=0, myViewOnly=0, myScrollEnable=1;
    std::string myFileName="TextEditFile.txt";
    std::vector<XColor> myTextColorVec, myIndexColorVec;
    uint myCursorCount=0;
    std::vector<std::string> myRestoreTextVec={};
    XString myString,myIndexText;
    uint mySelectionStartCharNr=0, mySelectionEndCharNr=0;
    bool myInit=0;
    bool myUseGlScissor=0;
    bool myModeEdit=0;
    XCursor *myCursorIcon;
    std::string myCommand;

    //! Process the numbers for the line number index text.
    void processIndexText(){
        //! Find the ammount of lines of the text.
        uint theLineCount=XString().getLineCount(myString);
        //! Produce a complete string for the line count index.
        XString theLineCountString=XString().getLineCountString(theLineCount);
        //! Set the string.
        myIndexText.setString(theLineCountString);
        myIndexText.setColorToString({0.600,0.600,0.600,1.000});
        //! Colorize a string position where the mouse cursor is.
        uint theCursorCount=getCurrentCursorLineNr();
        theLineCount=0;
        for(uint i=0; i<myIndexText.size(); i++){
            if(myIndexText.at(i).Char()=='\n'){
                theLineCount++;
            }
            if(theCursorCount==theLineCount){
                myIndexText.setCharColor(i,{1.000,0.843,0.000,1.000});
            }
        }
        if(myModeEdit){
            myLineNrIndex->setRelativeOriginOffset(mySize->RelativeOriginOffset());
        }

        myLineNrIndex->drawText(myIndexText,getStartCharNrMyIndexText(),getEndCharNrMyIndexText(),0,newY+getStartOffset(),myUseGlScissor);
    }
    //! Get the ammount of chars to display.
    float processIndexWidth(){
        int myDigits=0;
        int num=getTotalLineCount();
        if(num==0){num=1;} //! At least simulate one line.
        while(num>0){ //! Get the ammount of digits of the indexnr.
            myDigits++;
            num=num/10;
        }
        return myDigits*(myLineNrIndex->StringWidth("0")); //! Get a char width and convert to pixel size.
    }
    //! Get the line count of the view.
    int getLineCountOfView(){
        return mySize->Height()/(myFontSize+myVerticalFontSpace);
    }
    //! Get the line count of the total text.
    int getTotalLineCount(){
        uint theLineCount=0;
        for(uint i=0; i<myString.size(); i++){
            if(myString.at(i).Char()==XChar('\n').Char()){
                theLineCount++;
            }
        }
        return theLineCount;
    }
    //! Get line number where mouse cursor is blinking.
    uint getCurrentCursorLineNr(){
        uint theLineCount=0;
        uint theCharCount=0;
        for(uint i=0; i<myString.size(); i++){
            theCharCount++;
            if(myString.at(i).Char()==XChar('\n').Char()){
                theLineCount++;
            }
            if(theCharCount==myCursorCount){
                return  theLineCount;
            }
        }
        //! std::cout<<"cursor linecount:"<<theLineCount<<std::endl;
        return theLineCount;
    }
    //! Get the top line of the viewer.
    int getStartLine(){
        int theStartLine=(newY/(myFontSize+myVerticalFontSpace))*-1;
        if(theStartLine<0){theStartLine=0;}
        return theStartLine;
    }
    //! Start offset for y.
    float getStartOffset(){
        return getStartLine()*(myFontSize+myVerticalFontSpace);
    }
    //! The first char to display.
    uint getStartCharNrMyText(){
        int theYCounter=0; int theCharCounter=0;
        for(uint i=0; i<myString.size(); i++){
            if(theYCounter==getStartLine()){
                return theCharCounter;
            }
            if(myString.at(i).Char()=='\n'){
                theYCounter++;
            }
            theCharCounter++;
        }
        return theCharCounter;
    }
    //! The last char to display.
    uint getEndCharNrMyText(){
        int theYCounter=0; int theCharCounter=0;
        for(uint i=0; i<myString.size(); i++){
            if(theYCounter==getStartLine()+getLineCountOfView()){
                return theCharCounter;
            }
            if(myString.at(i).Char()=='\n'){
                theYCounter++;
            }
            theCharCounter++;
        }
        return theCharCounter;
    }
    //! The first line index nr. char to display.
    uint getStartCharNrMyIndexText(){
        int theYCounter=0; int theCharCounter=0;
        for(uint i=0; i<myIndexText.size(); i++){
            if(theYCounter==getStartLine()){
                return theCharCounter;
            }
            if(myIndexText.at(i).Char()=='\n'){
                theYCounter++;
            }
            theCharCounter++;
        }
        return theCharCounter;
    }
    //! The last line index nr. to display.
    uint getEndCharNrMyIndexText(){
        int theYCounter=0; int theCharCounter=0;
        for(uint i=0; i<myIndexText.size(); i++){
            if(theYCounter==getStartLine()+getLineCountOfView()){
                return theCharCounter-1;
            }
            if(myIndexText.at(i).Char()=='\n'){
                theYCounter++;
            }
            theCharCounter++;
        }
        return theCharCounter;
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
        for(uint i=0; i<myString.size(); i++){
            if(i>=start && i<= end){
                theSelection.push_back(myString.at(i).Char());
            }
        }
        return theSelection;
    }
    //! Set closest cursor position given a mouse click.
    void setClosestCursorPressedPos(){
        //! This solves setting the mouse cursor after last character when having only one text line.
        bool newLine=0;
        for(uint i=0; i<myString.size(); i++){
            if(myString.at(i).Char()=='\n'){
                newLine=1;
            }
        }
        if(!newLine){
            if(myString.size()>0){
                if(myString.at(myString.size()-1).Char()!=' '){
                    myString.push_back(' ');
                }
            }
        }
        float mpx=(Mouse.X()-myEditor->Size().Origin().X())-newX; // std::cout<<"mousepos x:"<<(Mouse.X()-myEditor->X())-newX<<" y:"<<(Mouse.Y()-myEditor->Y())-newY<<std::endl;
        float mpy=(Mouse.Y()-myEditor->Size().Origin().Y())-newY;
        float sampleDist=INFINITY;
        float cpx=0.0; float cpy=0.0;
        for(uint i=0; i<myString.size(); i++){
            float dist=sqrt(pow(cpx-mpx,2)+pow(cpy-mpy,2));
            if(dist<=sampleDist){
                sampleDist=dist;
                myCursorCount=i;
            }
            if(myString.at(i).Char()=='\n'){
                cpy+=(myFontSize+myVerticalFontSpace);
                cpx=0;
            } else {
                cpx+=myEditor->CharacterPixelWidth(myString.at(i).Char());
            }
        }
    }
    //! Return char count under blinking cursor.
    uint getCharNrUnderCursorPos(){
        uint theCharNr=0;
        float mpx=(Mouse.X()-myEditor->Size().Origin().X())-newX; // std::cout<<"mousepos x:"<<(Mouse.X()-myEditor->X())-newX<<" y:"<<(Mouse.Y()-myEditor->Y())-newY<<std::endl;
        float mpy=(Mouse.Y()-myEditor->Size().Origin().Y())-newY;
        float sampleDist=INFINITY;
        float cpx=0.0; float cpy=0.0;
        for(uint i=0; i<myString.size(); i++){
            float dist=sqrt(pow(cpx-mpx,2)+pow(cpy-mpy,2));
            if(dist<=sampleDist){
                sampleDist=dist;
                theCharNr=i;
            }
            if(myString.at(i).Char()=='\n'){
                cpy+=(myFontSize+myVerticalFontSpace);
                cpx=0;
            } else {
                cpx+=myEditor->CharacterPixelWidth(myString.at(i).Char());
            }
        }
        return theCharNr;
    }
    std::string getStringFromLineNr(uint theLineNr){
        std::string theString;
        uint theLineCount=0;
        uint theCharCount=0;
        for(uint i=0; i<myString.size(); i++){
            theCharCount++;
            if(myString.at(i).Char()==XChar('\n').Char()){
                theLineCount++;
            }
            if(theLineCount==theLineNr && myString.at(i).Char()!='\n'){
                //! std::cout<<"theCursorIsAtLine:"<<theLineCount<<std::endl;
                theString.push_back(myString.at(i).Char());
            }
            if(theLineCount>theLineNr){ //! Shorten the algoritme if possible.
                break;
            }
        }
        //! std::cout<<"theCursorIsAtLine:"<<theLineCount<<std::endl;
        return theString;
    }
    std::string getLineContentAtCursor(){
        return getStringFromLineNr(getCurrentCursorLineNr());
    }
    std::string getPreviousLineContentAtCursor(){
        int nr=getCurrentCursorLineNr()-1;
        return getStringFromLineNr(nr);
    }
    //! Process keyboard events.
    void KeyboardEvents(){
        //! Process key events for the correct widget.
        if(XPip().getPip(Mouse.Position()->Point(),mySize->Size())){
            if(Key.isGlfwRightKey()){
                if(myCursorCount<myString.size()){
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
                uint val=(myEditor->Size().Height()/(myFontSize+myVerticalFontSpace))-2;
                uint theTotalYSize=(getTotalLineCount()-val)*(myFontSize+myVerticalFontSpace);
                if(abs(newY)<theTotalYSize){
                    newY-=val*(myFontSize+myVerticalFontSpace);
                }
                if(abs(newY)>theTotalYSize){
                    newY=int(theTotalYSize*-1);
                }
            }
            if(Key.isGlfwPageUp()){
                uint val=(myEditor->Size().Height()/(myFontSize+myVerticalFontSpace))-2;
                newY+=val*(myFontSize+myVerticalFontSpace);
                if(newY>0){
                    newY=0;
                }
            }
            if(Key.isGlfwEnterKey()){
                myString.insert(myCursorCount,XChar('\n'));
                myCursorCount++;
                Key.resetScanCode();
                //! If this is a Terminal implementation, it reads the previous line in as a command.
                myCommand=getPreviousLineContentAtCursor();
                //! std::cout<<"myCommand:"<<myCommand<<std::endl;
            }
            if(Key.isGlfwBackSpaceKey()){
                if(myCursorCount>0){
                    myString.erase(myCursorCount);
                    myCursorCount--;
                }
                Key.resetScanCode();
            }
            if(Key.isGlfwTabKey()){
                myString.insert(myCursorCount,XChar(' '));
                myCursorCount++;
                myString.insert(myCursorCount,XChar(' '));
                myCursorCount++;
                myString.insert(myCursorCount,XChar(' '));
                myCursorCount++;
                myString.insert(myCursorCount,XChar(' '));
                myCursorCount++;
                Key.resetScanCode();
            }
            if(Key.Char()!=-1){
                myString.insert(myCursorCount,XChar(Key.Char(),myTextColor->Color()));
                myCursorCount++;
                Key.resetScanCode();
                Key.setChar(-1);
                //! Set no selection at a left press.
                mySelectionEndCharNr=mySelectionStartCharNr;
            }
            if(Key.isGlfwControlAKey()){
                clip::set_text(myString.toStdString());
                mySelectionStartCharNr=0;
                mySelectionEndCharNr=myString.size();

            }
            if(Key.isGlfwControlCKey()){
                clip::set_text(getSelectedText());
            }
            if(Key.isGlfwControlVKey()){
                std::string value;
                clip::get_text(value);

                myString.insert(myCursorCount,value);
                myCursorCount+=value.size();
            }
            if(Key.isGlfwControlXKey()){
                //! Copy selected text to clip.
                clip::set_text(getSelectedText());
                //! Remove the selexted text from the myText.
                XString theResult;
                uint start=mySelectionStartCharNr;
                uint end=mySelectionEndCharNr;
                if(start>end){
                    uint temp=start;
                    start=end;
                    end=temp;
                }
                for(uint i=0; i<myString.size(); i++){
                    if(i>=start && i<end){
                        //! Do nothing with the selection.
                    } else {
                        theResult.push_back(myString.at(i));
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
            Mouse.setMidMouseSnapshot();
        }
        if(myEditor->Event(XEventEnum::DraggedMid) && XPip().getPipFromMousePos(ParentScissorSize().Size())){
            newX=(Mouse.Position()->X()-Mouse.MidMouseSnapShot()->X())+oldX;
            newY=(Mouse.Position()->Y()-Mouse.MidMouseSnapShot()->Y())+oldY;

            //! Here we set the drag y-pos in line with the fontheight.
            int val=newY/(myFontSize+myVerticalFontSpace);
            newY=val*(myFontSize+myVerticalFontSpace);
        }
        if(myEditor->Event(XEventEnum::ReleasedMid)){
            oldX=newX;
            oldY=newY;
        }
        if(myEditor->Event(XEventEnum::Hovered)){
            if(myScrollEnable &&  XPip().getPipFromMousePos(ParentScissorSize())){
                //! Only scroll if the mouse is inside the parent scissor size.
                if(Mouse.ScrollValueY()>0){
                    //! std::cout<<"scrollup"<<std::endl;
                    newY+=(5*(myFontSize+myVerticalFontSpace));
                    //! std::cout<<"newY:"<<newY<<std::endl;
                }
                if(Mouse.ScrollValueY()<0){
                    //! std::cout<<"scrolldown"<<std::endl;
                    newY-=(5*(myFontSize+myVerticalFontSpace));
                    //! std::cout<<"newY:"<<newY<<std::endl;
                }
                Mouse.setMouseScrollValue(Window()->GlfwWindowPointer(),0,0);
            }
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
            // std::cout<<"dragging"<<std::endl;
            mySelectionEndCharNr=getCharNrUnderCursorPos();
        }
    }
    //! Draw the blinking cursor.
    void drawCursor(){
        //! Only draw cursor when mouse is inside the parent scissor size.
        if(XPip().getPipFromMousePos(ParentScissorSize())){
            float cpx=0.0; float cpy=0.0; //! cursor position.
            for(uint i=0; i<myString.size(); i++){
                //! std::cout<<"myText at i:"<<i<<" text:"<<myText.at(i)<<std::endl;
                if(myCursorCount==i){
                    break;
                }
                if(myString.at(i).Char()== XChar('\n').Char()){
                    cpy+=(myFontSize+myVerticalFontSpace);
                    cpx=0;
                }  else {
                    cpx+=myEditor->CharacterPixelWidth(myString.at(i).Char());
                }
            }
            myCursor->setSize({{myEditor->Size().Origin().X()+newX+cpx,myEditor->Size().Origin().Y()+newY+cpy,myEditor->Size().Origin().Z()},myCursor->Size().Width(),myCursor->Size().Height()});
            if(myModeEdit){
                myCursor->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            }
            if(Mouse.Time()>500 && XPip().getPip(Mouse.Position()->Point(),mySize->Size())){ //! Blinking cursor.
                myCursor->draw();
            }
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
        for(uint i=0; i<myString.size(); i++){
            mySelectionRectangular->setRelativeOriginOffset(mySize->RelativeOriginOffset());
            if(start==i){
                mySelectionRectangular->setSize({{myEditor->Size().Origin().X()+newX+cpx,myEditor->Size().Origin().Y()+newY+cpy,0},mySelectionRectangular->Size().Width(),mySelectionRectangular->Size().Height()});
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
            if(i>=start && i<=end && myString.at(i).Char()=='\n'){
                mySelectionRectangular->setSize({{mySelectionRectangular->Size().Origin().X(),
                                                  mySelectionRectangular->Size().Origin().Y(),
                                                  mySelectionRectangular->Size().Origin().Z()},cpx-dx,(myFontSize+myVerticalFontSpace)-1});
                if(!myModeEdit){
                    mySelectionRectangular->draw();
                }
            }
            if(myString.at(i).Char()=='\n'){
                cpy+=(myFontSize+myVerticalFontSpace);
                cpx=0;
                dx=0;
            } else {
                cpx+=myEditor->CharacterPixelWidth(myString.at(i).Char());
            }
            if(i>=start && i<=end && myString.at(i).Char()=='\n'){
                mySelectionRectangular->setSize({{myEditor->Size().Origin().X()+newX,myEditor->Size().Origin().Y()+newY+cpy,0},
                                                 mySelectionRectangular->Size().Width(),
                                                 mySelectionRectangular->Size().Height()});
            }
        }
    }
};
#endif

#ifndef XTERMINALTEXTEDIT_H
#define XTERMINALTEXTEDIT_H

#include <XWidget.h>
#include <XRectangular.h>
#include <XMouse.h>
#include <XKey.h>
#include <XText.h>
#include <XFile.h>
#include <XHorizontalSlider.h>

#include <XChar.h>
#include <XKeyWord.h>
//#include <clip.h> // https://github.com/dacap/clip/

// Todo list.
// Draw cursor with scissor.    => Done.
// Colorize keywords.           => In progress.
// Cntrl+Z ..
// Colorize values.
// Key tap.
// Text space.

/* Test comment. */

class XTerminalTextEdit : public XWidget  {
public:
    XTerminalTextEdit(XWindow *theWindow):myWindow(theWindow){}

    void init(){
        init(13,2,true);
    }
    void init_WithoutLineNrIndex(){
        init(13,2,false);
    }
    void init_WithoutLineNrIndex_ModeViewOnly(){
        init(13,2,false);
        myViewOnly=true;
    }
    void init(float theFontSize, float theVerticalFontSpace, bool showLineNrIndex){
        myFontSize=theFontSize;
        myVerticalFontSpace=theVerticalFontSpace;
        myShowLineNrIndex=showLineNrIndex;

        myEditor=new XText(myWindow);
        // myEditor->setBackGroundColor({0.2,0.2,0.2,0.9}); // Alpha: 1.0=no opacy. 0.0=full opacy*

        // myKeyWord=new XKeyWord();

        if(myShowLineNrIndex){
            myLineNrIndex=new XText(myWindow);
            // myLineNrIndex->setBackGroundColor({0.2,0.2,0.2,0.9}); // Alpha: 1.0=no opacy. 0.0=full opacy*

            mySpacer=new XRectangular(myWindow);
            mySpacer->setColor({0.1,0.1,0.1,0.9});
        }

        myCursor=new XRectangular(myWindow);
        myCursor->setColor({1.0,0.0,0.0,1.0});
        myCursor->setSize({{0,0,0},2,myFontSize});

        mySelectionRectangular=new XRectangular(myWindow);
        mySelectionRectangular->setColor({1.0,1.0,0.0,0.25});
        mySelectionRectangular->setSize({{0,0,0},0,0});

        // During startup somehow a key is pressed wich will result in a char on the screen. Avoid this.
        Key.resetScanCode();
        myInit=1;
    }

    std::string Command(){
        return myCommand;
    }
    void resetCommand(){
        myCommand="";
    }
    void loadFile(std::string theFileName){
        myText=XFile().readTextFile(theFileName);
        myFileName=theFileName;
    }
    void setText(std::string theText, XColor theColor){
        myText.setStringFromStdString(theText);
        myText.setColorToString(theColor);
        myCursorCount=myText.size();
    }
    void appendText(std::string theText, XColor theColor){
            myText.insert(myText.size(),theText,theColor);
            myCursorCount+=theText.size();
    }
    void setCharInText(uint thePosition, XChar theChar){
        myText.at(thePosition).setChar(theChar);
    }
    std::string getLineContentAtCursor(){
        return getStringFromLineNr(getCurrentCursorLineNr());
    }
    void newFile(){
        myText.clear();
    }
    void saveFile(){
        XFile().saveFile(myFileName,myText.toStdString());
    }
    void saveFile(std::string theFileName){
        XFile().saveFile(theFileName,myText.toStdString());
    }

    // Function calls from virtual base class XWidget.
    void setSize(XSize theSize){
        myOrigin->setPoint(theSize.Origin());
        myWidth=theSize.Width();
        myHeight=theSize.Height();
    }
    XSize Size(){
        return {{myOrigin->Point()},myWidth,myHeight};
    }

    void draw(){
        if(!myInit){
            init(13,2,true);
        }
        processSize();
        if(!myViewOnly){
            if(Mouse.myWindow==myWindow->GlfwWindowPointer()){ // Only process the current active window.
                processMouse();
            }
            if(Key.myWindow==myWindow->GlfwWindowPointer()){
                processKeyboard();
            }
        }
        // Process keywords for a specific programming language etc.
        // The keywords are only processed for the visible part of the gui.
        // Just like google maps processes only the part that is viewed and not the whole planet is loaded into memory.
        if(!myViewOnly){
            // myText=myKeyWord->process(myText,getStartCharNrMyText(),getEndCharNrMyText());
        }
        // There are two algo's processing the visible part of the text. Text positioned out of the screen coordinates is not processed by the XText class.
        // GlScissor && getStartCharNr+getEndCharNr are used to process the visible part of the text.
        // These algo's will keep the gui responsive with huge text files.
        myEditor->drawText(myText,getStartCharNrMyText(),getEndCharNrMyText(),newX,newY+getStartOffset(),true);
        if(myShowLineNrIndex){
            mySpacer->draw();
            if(mySpacer->isPressed()){ // Set text position to zero.
                newX=0, newY=0;
            }
            processIndexText();
            myLineNrIndex->drawText(myIndexText,getStartCharNrMyIndexText(),getEndCharNrMyIndexText(),0,newY+getStartOffset(),true);
        }
        if(!myViewOnly){
            drawSelectedText();
            if(Mouse.myWindow==myWindow->GlfwWindowPointer()){
                drawCursor();
            }
        }
    }

private:
    XWindow *myWindow;
    XKeyWord *myKeyWord;
    XText *myLineNrIndex;
    XText *myEditor;
    XRectangular *mySpacer,*myCursor,*mySelectionRectangular;
    XPoint *myOrigin=new XPoint();;
    float myWidth=0.0,myHeight=0.0,myIndexWidth=0.0,mySpacerWidth=10.0,myFontSize=14.0,myVerticalFontSpace=0.0;
     //XSizePolicy mySizePolicy;
    float newX=0.0,oldX=0.0,newY=0.0,oldY=0.0;
    bool myLeftMouseButtonTrigger=0, myShowLineNrIndex=0, myViewOnly=0;;
    std::string myFileName="TextEditFile.txt";
    std::vector<XColor> myTextColorVec, myIndexColorVec;
    uint myCursorCount=0;
    std::vector<std::string>  myRestoreTextVec={};

    XString myText,myIndexText;
    uint mySelectionStartCharNr=0, mySelectionEndCharNr=0;

    bool myInit=0;
    std::string myCommand;

    void processSize(){
        if(myShowLineNrIndex){
            myIndexWidth=processIndexWidth();
            myLineNrIndex->setSize({myOrigin->X(),myOrigin->Y(),myOrigin->Z()},myIndexWidth,myHeight);
            mySpacer->setSize({{myOrigin->X()+myIndexWidth,myOrigin->Y(),myOrigin->Z()},mySpacerWidth,myHeight});
        } else {
            mySpacerWidth=0;
        }
        myEditor->setSize({myOrigin->X()+myIndexWidth+mySpacerWidth,myOrigin->Y(),myOrigin->Z()},myWidth-(myIndexWidth+mySpacerWidth),myHeight);
    }
    void processIndexText(){
        // Find the ammount of lines of the text.
        uint theLineCount=XString().getLineCount(myText);
        // Procude a complete string for the line count index.
        XString theLineCountString=XString().getLineCountString(theLineCount);
        // Set the string.
        myIndexText.setString(theLineCountString);
        myIndexText.setColorToString({0.600,0.600,0.600,1.000});
        // Colorize a string position where the mouse cursor is.
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
    }
    float processIndexWidth(){
        int myDigits=0;
        int num=getTotalLineCount();
        if(num==0){num=1;} // At least simulate one line.
        while(num>0){ // Get the ammount of digits of the indexnr.
            myDigits++;
            num=num/10;
        }
        return myDigits*(myLineNrIndex->StringWidth("0")/64 /*Get a char width and convert to pixel size.*/);
    }
    int getLineCountOfView(){
        return myHeight/(myFontSize+myVerticalFontSpace);
    }
    int getTotalLineCount(){
        uint theLineCount=0;
        for(uint i=0; i<myText.size(); i++){
            if(myText.at(i).Char()==XChar('\n').Char()){
                theLineCount++;
            }
        }
        return theLineCount;
    }
    uint getCurrentCursorLineNr(){
        uint theLineCount=0;
        uint theCharCount=0;
        for(uint i=0; i<myText.size(); i++){
            theCharCount++;
            if(myText.at(i).Char()==XChar('\n').Char()){
                theLineCount++;
            }
            if(theCharCount==myCursorCount){
                // std::cout<<"theCursorIsAtLine:"<<theLineCount<<std::endl;
                return  theLineCount;
            }
        }
        // std::cout<<"theCursorIsAtLine:"<<theLineCount<<std::endl;
        return theLineCount;
    }
    int getStartLine(){
        int theStartLine=(newY/(myFontSize+myVerticalFontSpace))*-1;
        if(theStartLine<0){theStartLine=0;}
        return theStartLine;
    }
    float getStartOffset(){
        return getStartLine()*(myFontSize+myVerticalFontSpace);
    }
    uint getStartCharNrMyText(){
        int theYCounter=0; int theCharCounter=0;
        for(uint i=0; i<myText.size(); i++){
            if(theYCounter==getStartLine()){
                return theCharCounter;
            }
            if(myText.at(i).Char()=='\n'){
                theYCounter++;
            }
            theCharCounter++;
        }
        return theCharCounter;
    }
    uint getEndCharNrMyText(){
        int theYCounter=0; int theCharCounter=0;
        for(uint i=0; i<myText.size(); i++){
            if(theYCounter==getStartLine()+getLineCountOfView()){
                return theCharCounter;
            }
            if(myText.at(i).Char()=='\n'){
                theYCounter++;
            }
            theCharCounter++;
        }
        return theCharCounter;
    }
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
    std::string getSelectedText(){
        std::string theSelection;
        uint start=mySelectionStartCharNr;
        uint end=mySelectionEndCharNr;
        if(end<start){
            uint temp=start;
            start=end;
            end=temp;
        }
        for(uint i=0; i<myText.size(); i++){
            if(i>=start && i<= end){
                theSelection.push_back(myText.at(i).Char());
            }
        }
        return theSelection;
    }
    void setClosestCursorPressedPos(){
        float mpx=(Mouse.X()-myEditor->X())-newX; // std::cout<<"mousepos x:"<<(Mouse.X()-myEditor->X())-newX<<" y:"<<(Mouse.Y()-myEditor->Y())-newY<<std::endl;
        float mpy=(Mouse.Y()-myEditor->Y())-newY;
        float sampleDist=INFINITY;
        float cpx=0.0; float cpy=0.0;
        for(uint i=0; i<myText.size(); i++){
            float dist=sqrt(pow(cpx-mpx,2)+pow(cpy-mpy,2));
            if(dist<=sampleDist){
                sampleDist=dist;
                myCursorCount=i;
            }
            if(myText.at(i).Char()=='\n'){
                cpy+=(myFontSize+myVerticalFontSpace);
                cpx=0;
            } else {
                cpx+=myEditor->CharacterPixelWidth(myText.at(i).Char());
            }
        }
    }
    uint getCharNrUnderCursorPos(){
        uint theCharNr=0;
        float mpx=(Mouse.X()-myEditor->X())-newX; // std::cout<<"mousepos x:"<<(Mouse.X()-myEditor->X())-newX<<" y:"<<(Mouse.Y()-myEditor->Y())-newY<<std::endl;
        float mpy=(Mouse.Y()-myEditor->Y())-newY;
        float sampleDist=INFINITY;
        float cpx=0.0; float cpy=0.0;
        for(uint i=0; i<myText.size(); i++){
            float dist=sqrt(pow(cpx-mpx,2)+pow(cpy-mpy,2));
            if(dist<=sampleDist){
                sampleDist=dist;
                theCharNr=i;
            }
            if(myText.at(i).Char()=='\n'){
                cpy+=(myFontSize+myVerticalFontSpace);
                cpx=0;
            } else {
                cpx+=myEditor->CharacterPixelWidth(myText.at(i).Char());
            }
        }
        return theCharNr;
    }
    std::string getStringFromLineNr(uint theLineNr){
        std::string theString;
        uint theLineCount=0;
        uint theCharCount=0;
        for(uint i=0; i<myText.size(); i++){
            theCharCount++;
            if(myText.at(i).Char()==XChar('\n').Char()){
                theLineCount++;
            }
            if(theLineCount==theLineNr && myText.at(i).Char()!='\n'){
                // std::cout<<"theCursorIsAtLine:"<<theLineCount<<std::endl;
                theString.push_back(myText.at(i).Char());
            }
            if(theLineCount>theLineNr){ // Shorten the algoritme if possible.
                break;
            }
        }
        // std::cout<<"theCursorIsAtLine:"<<theLineCount<<std::endl;
        return theString;
    }
    void processKeyboard(){
        if(Key.isGlfwRightKey()){
            if(myCursorCount<myText.size()){
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
            uint val=(myEditor->Height()/(myFontSize+myVerticalFontSpace))-2;
            uint theTotalYSize=(getTotalLineCount()-val)*(myFontSize+myVerticalFontSpace);
            if(abs(newY)<theTotalYSize){
                newY-=val*(myFontSize+myVerticalFontSpace);
            }
            if(abs(newY)>theTotalYSize){
                newY=int(theTotalYSize*-1);
            }
            // std::cout<<"newY:"<<newY<<std::endl;
            // std::cout<<"theTotalYSize:"<<theTotalYSize<<std::endl;
        }
        if(Key.isGlfwPageUp()){
            uint val=(myEditor->Height()/(myFontSize+myVerticalFontSpace))-2;
            newY+=val*(myFontSize+myVerticalFontSpace);
            if(newY>0){
                newY=0;
            }
        }
        if(Key.isGlfwEnterKey()){
            myCommand=getLineContentAtCursor();
            myText.insert(myCursorCount,XChar('\n'));
            myCursorCount++;
            Key.resetScanCode();
        }
        if(Key.isGlfwBackSpaceKey()){
            if(myCursorCount>0){
                myText.erase(myCursorCount);
                myCursorCount--;
            }
        }
        if(Key.isGlfwTabKey()){
            myText.insert(myCursorCount,XChar(' '));
            myCursorCount++;
            myText.insert(myCursorCount,XChar(' '));
            myCursorCount++;
            myText.insert(myCursorCount,XChar(' '));
            myCursorCount++;
            myText.insert(myCursorCount,XChar(' '));
            myCursorCount++;
            Key.resetScanCode();
        }
        if(Key.getGlfwCharKey()!=-1){
            myText.insert(myCursorCount,XChar(Key.getGlfwCharKey(),{1.0,1.0,1.0,1.0}));
            myCursorCount++;
            Key.resetScanCode();
        }
        if(Key.isGlfwControlAKey()){
            //clip::set_text(myText.toStdString());
            mySelectionStartCharNr=0;
            mySelectionEndCharNr=myText.size();

        }
        if(Key.isGlfwControlCKey()){
            //clip::set_text(getSelectedText());
        }
        if(Key.isGlfwControlVKey()){
            std::string value;
           // clip::get_text(value);

            myText.insert(myCursorCount,value);
            myCursorCount+=value.size();
        }
        if(Key.isGlfwControlXKey()){
            // Copy selected text to clip.
           // clip::set_text(getSelectedText());
            // Remove the selexted text from the myText.
            XString theResult;
            uint start=mySelectionStartCharNr;
            uint end=mySelectionEndCharNr;
            if(start>end){
                uint temp=start;
                start=end;
                end=temp;
            }
            for(uint i=0; i<myText.size(); i++){
                if(i>=start && i<end){
                    // Do nothing with the selection.
                } else {
                    theResult.push_back(myText.at(i));
                }
            }
            myText=theResult;

            // Update cursorposition. The cursorcount is a uint and does not like a negative value.
            int ensurePosCursorCountValue=myCursorCount-(end-start);
            if(ensurePosCursorCountValue<0){ensurePosCursorCountValue=0;}
            myCursorCount=ensurePosCursorCountValue;
        }
    }
    void processMouse(){
        // Editor.
        if(myEditor->isDraggedMidButton()){
            newX=(Mouse.X()-Mouse.MouseSnapShotX())+oldX;
            newY=(Mouse.Y()-Mouse.MouseSnapShotY())+oldY;

            // Here we set the drag y-pos in line with the fontheight.
            int val=newY/(myFontSize+myVerticalFontSpace);
            newY=val*(myFontSize+myVerticalFontSpace);
        }
        if(myEditor->isReleasedMidButton()){
            oldX=newX;
            oldY=newY;
        }
        if(myEditor->isHovered()){
            if(Mouse.MouseScrollValueY()>0){
                // std::cout<<"scrollup"<<std::endl;
                newY+=(5*(myFontSize+myVerticalFontSpace));
                // std::cout<<"newY:"<<newY<<std::endl;
            }
            if(Mouse.MouseScrollValueY()<0){
                // std::cout<<"scrolldown"<<std::endl;
                newY-=(5*(myFontSize+myVerticalFontSpace));
                // std::cout<<"newY:"<<newY<<std::endl;
            }
            Mouse.setMouseScrollValue(myWindow->GlfwWindowPointer(),0,0);
        }
        if(myEditor->isPressedLeftButtonNoOneShot() && !myLeftMouseButtonTrigger){
            setClosestCursorPressedPos();
            mySelectionStartCharNr=getCharNrUnderCursorPos();
            myLeftMouseButtonTrigger=1;
        }
        if(myEditor->isReleasedLeftButtonNoOneShot()){
            myLeftMouseButtonTrigger=0;
        }
        if(myLeftMouseButtonTrigger){
            // std::cout<<"dragging"<<std::endl;
            mySelectionEndCharNr=getCharNrUnderCursorPos();
        }
    }
    void drawCursor(){
        float cpx=0.0; float cpy=0.0; // cursor position.
        for(uint i=0; i<myText.size(); i++){
            // std::cout<<"myText at i:"<<i<<" text:"<<myText.at(i)<<std::endl;
            if(myCursorCount==i){
                break;
            }
            if(myText.at(i).Char()== XChar('\n').Char()){
                cpy+=(myFontSize+myVerticalFontSpace);
                cpx=0;
            }  else {
                cpx+=myEditor->CharacterPixelWidth(myText.at(i).Char());
            }
        }
        myCursor->setSize({myEditor->X()+newX+cpx,myEditor->Y()+newY+cpy,myEditor->Z()});
        if(Mouse.time>500){ // Blinking cursor.
            // Draw the cursor only in the editor window, do not draw the cursor outside this region.
            glScissor(myEditor->X()/*Lowerleft*/,myWindow->Height()-(myEditor->Y()+myEditor->Height())/*Lowerleft*/,myEditor->Width(),myEditor->Height());
            glEnable(GL_SCISSOR_TEST);
            myCursor->draw();
            glDisable(GL_SCISSOR_TEST);
        }
    }
    void drawSelectedText(){ // Masterpiece.
        uint start=mySelectionStartCharNr;
        uint end=mySelectionEndCharNr;
        if(end<start){ // Swap.
            uint temp=start;
            start=end;
            end=temp;
        }
        float cpx=0.0; float cpy=2.0;
        float dx=0;
        for(uint i=0; i<myText.size(); i++){
            if(start==i){
                mySelectionRectangular->setSize({myEditor->X()+newX+cpx,myEditor->Y()+newY+cpy,0});
                dx=cpx;
            }
            if(end==i){
                mySelectionRectangular->setSize(cpx-dx,(myFontSize+myVerticalFontSpace)-1);
                mySelectionRectangular->draw();
                return;
            }
            if(i>=start && i<=end && myText.at(i).Char()=='\n'){
                mySelectionRectangular->setSize(cpx-dx,(myFontSize+myVerticalFontSpace)-1);
                mySelectionRectangular->draw();
            }
            if(myText.at(i).Char()=='\n'){
                cpy+=(myFontSize+myVerticalFontSpace);
                cpx=0;
                dx=0;
            } else {
                cpx+=myEditor->CharacterPixelWidth(myText.at(i).Char());
            }
            if(i>=start && i<=end && myText.at(i).Char()=='\n'){
                mySelectionRectangular->setSize({myEditor->X()+newX,myEditor->Y()+newY+cpy,0});
            }
        }
    }
};
#endif // XTERMINALTEXTEDIT_H

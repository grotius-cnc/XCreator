#ifndef XTERMINAL_H
#define XTERMINAL_H

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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <XWidget.h>
#include <XButton.h>
#include <XImage.h>
#include <XWindow.h>
#include <XMouse.h>
#include <XKey.h>
#include <XTemplate.h>
#include <XScissor.h>
#include <XTextEdit.h>

class XTerminal : public XWidget {
public:
    //! Empty constructor.
    XTerminal(XWindow *theWindow){
        this->setWindow(theWindow);
        setScissorWindow(theWindow);
    }
    //! Destructor.
    ~XTerminal(){
        fclose(myFp);
    }
    void setSize(XSize theSize){
        mySize->setSize(theSize.Size());
    }
    void init(){
        //! Class to populate the file dialog with content.
        myTextEdit=new XTextEdit(Window());
        myTextEdit->setSize({{0,0,0},500,500});
        addWidget(myTextEdit);

        myDirText=new XText(Window()); //! Shows current path at bottom of window.
        myDirText->init();
        addWidget(myDirText);
    }
    void draw(){
        //! Save the current scissor size to be restored at end of this function.
        saveScissorState();
        //! Set the scissor union size.
        setScissorUnion(ParentScissorSize(),mySize->Size());
        //! Process the terminal enter input.
        processImput();

        //! Set widget sizes.
        myTextEdit->setSize({{0,0,0},mySize->Width(),mySize->Height()-20});
        myDirText->setSize({{0,mySize->Size().Height()-20,0},mySize->Width(),20});
        //! Get current working directory and display.
        XString theDirectoryPath=processDir();
        myDirText->drawText(theDirectoryPath,0,theDirectoryPath.size(),0,0);

        //! draw content.
        drawWidgetVec();
        //! Restore the scissor size.
        restoreScissorState();
    }
private:
    std::string myDialogName="XTerminal";
    XSize *mySize=new XSize();

    XTextEdit *myTextEdit;
    XText *myDirText;

    std::string myUserName;

    std::string myResult;
    FILE *myFp;
    char myBuffer[256];

    //! Get current working directory.
    XString processDir(){
        char cwd[256];
        getcwd(cwd,sizeof (cwd));
        std::string str=cwd;

        std::string totalString=" User: "+getUser()+" Path: "+str;
        XString theXString;
        theXString.setStringFromStdString(totalString);
        theXString.setColorToString({0.6,0.6,0.0,0.9});
        return theXString;
    }
    //! Process terminal enter input.
    void processImput(){
        if(myTextEdit->Command().size()!=0){ //! Has command.

            //! std::cout<<"hasCommand:"<<myTextEdit->Command()<<std::endl;
            std::string theCommand=myTextEdit->Command();

            if(theCommand=="clear"){
                command(theCommand);
                //! This is a fast way to reset some values.
                myTextEdit->reset();
                return;
            }
            if(theCommand=="dir"){ //! Old dos command.
                //! std::cout<<"dir found, command:"<<theCommand<<std::endl;
                theCommand="ls";
            }
            if(theCommand.size()>2 && theCommand.at(0)=='c' && theCommand.at(1)=='d' && theCommand.at(2)==' '){
                theCommand.erase(0,3);
                //! std::cout<<"cd found, command:"<<theCommand<<std::endl;
                chdir(theCommand.c_str());
                theCommand.clear();
            }

            XString theXStringCommand;
            theXStringCommand.setString(command(theCommand));
            theXStringCommand.setColorToString({0.8,0.5,0.0,1.0});
            myTextEdit->appendText(theXStringCommand);
            myTextEdit->resetCommand();
        }
    }

    std::string command(std::string cmd){
        myResult.clear();
        cmd.append(" 2>&1"); // Todo. Add the error channel output stream.
        myFp = popen(cmd.c_str(), "r");
        //! std::cout<<"theTerminal:"<<*ctermid<<std::endl;

        if(myFp){
            //! std::cout<<"stream ok."<<std::endl;
            while(feof(myFp)==0){
                if(fgets(myBuffer, 250, myFp)){
                    //! std::cout<<"buffer:"<<buffer<<std::endl;
                    myResult.append(myBuffer);
                }
            }
        }
        //! fclose(fp);
        return myResult;
    }
    //! Get the user name.
    std::string getUser(){
        std::string theUserName=getlogin();
        // std::cout<<"userName: "<<theUserName<<std::endl;
        return theUserName;
    }
};
#endif
























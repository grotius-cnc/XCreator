#ifndef XMAINWINDOW_H
#define XMAINWINDOW_H

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

class XMainWindow : public XWidget {
public:
    XMainWindow(){ }
    XMainWindow(std::string theDialogName, uint theStartupWidth, uint theStartupHeight):myDialogName(theDialogName),myWidth(theStartupWidth),myHeight(theStartupHeight){ }
    ~XMainWindow(){
        fclose(myFp);
    }

    void run(){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw window creation
        // --------------------
        window=glfwCreateWindow(myWidth, myHeight, myDialogName.c_str(), NULL, NULL);
        setWindowPointer(window);

        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwSetWindowOpacity(window,1.0); // 0-1. 1=no opacy.
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(EXIT_FAILURE);
        }

        glfwSetKeyCallback(window, KeyCallback);
        glfwSetCharCallback(window, CharacterCallback);
        glfwSetScrollCallback(window, ScrollCallBack);
        glfwSetCursorPosCallback(window, MousePosCallBack);
        glfwSetMouseButtonCallback(window, MouseButtonCallBack);
        glfwSetWindowCloseCallback(window, WindowCloseCallBack);
        glfwSetWindowSizeLimits(window,0,0,GLFW_DONT_CARE,GLFW_DONT_CARE);

        //! Class to populate the file dialog with content.
        myTextEdit=new XTextEdit(Window());
        myTextEdit->init();
        addWidget(myTextEdit);

        myDirText=new XText(Window()); //! Shows current path at bottom of window.
        myDirText->init();
        addWidget(myDirText);

        setScissorWindow(Window());
        enableScissor(1);

        while (!glfwWindowShouldClose(window)){
            glfwMakeContextCurrent(window); // Solves window flickering.

            glfwGetFramebufferSize(window, &myWidth, &myHeight);
            //! Set the XWindow size.
            this->setWindowDimension(myWidth,myHeight);

            //! Set the scissor size.
            mySize->setSize({{0,0,0},float(myWidth),float(myHeight)});
            setScissorSize(mySize->Size());
            //! ScissorSize().printSize("ScissorSize Mainwindow:");

            glViewport(0, 0, myWidth, myHeight);
            glClear(GL_COLOR_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, myWidth, myHeight, 0, -10000, 10000);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            if(glfwGetTime()>1){ // Reset every 1000 Ms.
                glfwSetTime(0);
            }
            // Timer for blinking mouse cursor when using text editor widgets. This function has to be done called once each project.
            Mouse.setTime(glfwGetTime()*1000);

            //! Process the terminal enter input.
            processImput();

            //! Set widget sizes.
            myTextEdit->setSize({{0,0,0},mySize->Width(),mySize->Height()-20});
            myDirText->setSize({{0,mySize->Size().Height()-20,0},mySize->Width(),20});
            //! Get current working directory and display.
            XString theDirectoryPath=processDir();
            myDirText->drawText(theDirectoryPath,0,theDirectoryPath.size(),0,0,0);

            //! draw content.
            drawWidgetVec();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        enableScissor(0);

        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
private:
    GLFWwindow* window;
    std::string myDialogName="XTerminal";
    int myWidth=500, myHeight=250;
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
























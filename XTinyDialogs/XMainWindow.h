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

#include <XImageButtonFileOpen.h>
#include <XImageButtonMessage.h>
#include <XImageButtonInputBox.h>
#include <XImageButtonSaveFile.h>
#include <XImageButtonColor.h>
#include <XImageButtonCheckList.h>
#include <XImageButtonArray.h>

class XMainWindow : public XWidget {
public:
    XMainWindow(){ }
    XMainWindow(std::string theDialogName, uint theStartupWidth, uint theStartupHeight):myDialogName(theDialogName),myWidth(theStartupWidth),myHeight(theStartupHeight){ }
    ~XMainWindow(){}

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

        float x=0;
        //! Class to populate the file dialog with content.
        myFileOpenButton=new XImageButtonFileOpen (Window());
        myFileOpenButton->setSize({{x,0,0},20,20});
        addWidget(myFileOpenButton);
        x+=20;

        myMessageButton=new XImageButtonMessage(Window());
        myMessageButton->setSize({{x,0,0},20,20});
        addWidget(myMessageButton);
        x+=20;

        myInputBoxButton=new XImageButtonInputBox(Window());
        myInputBoxButton->setSize({{x,0,0},20,20});
        addWidget(myInputBoxButton);
        x+=20;

        mySaveFileButton=new XImageButtonSaveFile(Window());
        mySaveFileButton->setSize({{x,0,0},20,20});
        addWidget(mySaveFileButton);
        x+=20;

        myColorButton=new XImageButtonColor(Window());
        myColorButton->setSize({{x,0,0},20,20});
        addWidget(myColorButton);
        x+=20;

        myCheckListButton=new XImageButtonCheckList(Window());
        myCheckListButton->setSize({{x,0,0},20,20});
        addWidget(myCheckListButton);
        x+=20;

        myArrayButton=new XImageButtonArray(Window());
        myArrayButton->setSize({{x,0,0},20,20});
        addWidget(myArrayButton);
        x+=20;

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

            //! This request will automaticly run the fileopen dialog.
            if(myFileOpenButton->isPressed()){
                std::cout<<"theFilePath result:"<<myFileOpenButton->Result()<<std::endl;
            }
            //! This request will automaticly run the message dialog.
            if(myMessageButton->isPressed()){}

            //! This request will automaticly run the input box dialog.
            if(myInputBoxButton->isPressed()){
                std::cout<<"theInput result:"<<myInputBoxButton->Result()<<std::endl;
            }
            //! This request will automaticly run the save file dialog.
            if(mySaveFileButton->isPressed()){
                std::cout<<"theInput result:"<<mySaveFileButton->Result()<<std::endl;
            }
            //! This request will automaticly run color dialog.
            if(myColorButton->isPressed()){
                std::cout<<"theInput result:"<<myColorButton->Result_Hex()<<std::endl;
                std::cout<<"theInput result r:"<<myColorButton->Result_Rgb().at(0)<<
                            " g:"<<myColorButton->Result_Rgb().at(1)<<
                            " b:"<<myColorButton->Result_Rgb().at(2)<<std::endl;
            }
            //! This request will automaticly run the checklist dialog.
            if(myCheckListButton->isPressed()){
                std::cout<<"theInput result:"<<myCheckListButton->Result()<<std::endl;
            }
            //! This request will automaticly run the array dialog.
            if(myArrayButton->isPressed()){
                std::cout<<"theInput result:"<<myArrayButton->Result()<<std::endl;
            }


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
    std::string myDialogName="XTinyDialogs";
    int myWidth=500, myHeight=250;
    XSize *mySize=new XSize();

    //! XButton *myButton = new XButton(myWindow); does not work because myWindow has not been initialised at this stage.
    XImageButtonFileOpen *myFileOpenButton;
    XImageButtonMessage *myMessageButton;
    XImageButtonInputBox *myInputBoxButton;
    XImageButtonSaveFile *mySaveFileButton;
    XImageButtonColor *myColorButton;
    XImageButtonCheckList *myCheckListButton;
    XImageButtonArray *myArrayButton;
};
#endif
























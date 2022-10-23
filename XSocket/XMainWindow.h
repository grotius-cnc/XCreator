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
#include <XTextEdit.h>
#include <XWindow.h>
#include <XMouse.h>
#include <XKey.h>
#include <XTemplate.h>
#include <XScissor.h>
#include <XServer.h>
#include <XClient.h>
//#include <XTerminalTextEdit.h>

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

        //! Class to populate the file dialog with content.
        myButtonServer=new XButton(Window());
        myButtonServer->setSize({{0,0,0},200,100});
        myButtonServer->setString("Server");
        addWidget(myButtonServer);

        myButtonClient=new XButton(Window());
        myButtonClient->setSize({{205,0,0},200,100});
        myButtonClient->setString("Client");
        addWidget(myButtonClient);

        myTextEditServerInput=new XTextEdit(Window());
        myTextEditServerInput->setSize({{0,105,0},200,100});
        addWidget(myTextEditServerInput);

        myTextEditClientInput=new XTextEdit(Window());
        myTextEditClientInput->setSize({{205,105,0},200,100});
        addWidget(myTextEditClientInput);

        //myTerminalServer=new XTerminalTextEdit(Window());
        //myTerminalServer->setSize({{205,210,0},200,200});
        //addWidget(myTerminalServer);

        //! Setup server.
        myServer=new XServer();
        myServer->run();

        //! Setup client.
        myClient=new XClient();
        myClient->run();

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
            glClearColor(0.5,0.0,0.2,1.0);
            glLoadIdentity();

            if(glfwGetTime()>1){ // Reset every 1000 Ms.
                glfwSetTime(0);
            }
            //! Timer for blinking mouse cursor when using text editor widgets. This function has to be done called once each project.
            Mouse.setTime(glfwGetTime()*1000);

            //! draw content.
            drawWidgetVec();

            if(myButtonServer->isPressed()){
                myServer->sendMessage();
            }
            if(myButtonClient->isPressed()){
                myClient->sendMessage();
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        enableScissor(0);

        myClient->terminate();
        myServer->terminate();

        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
private:
    GLFWwindow* window;
    std::string myDialogName="XMainWindow";
    int myWidth=0, myHeight=0;
    XSize *mySize=new XSize();

    //! XButton *myButton = new XButton(myWindow); does not work because myWindow has not been initialised at this stage.
    XButton *myButtonServer;
    XButton *myButtonClient;

    XTextEdit *myTextEditServerInput;
    XTextEdit *myTextEditClientInput;

    XServer *myServer;
    XClient *myClient;
};
#endif





















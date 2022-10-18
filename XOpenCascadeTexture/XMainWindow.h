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
#include <XScissor.h>
#include <XDialog.h>
#include <XButton.h>
#include <XWindow.h>
#include <XMouse.h>
#include <XKey.h>

//! MainWindow.
class XMainWindow : public XWidget {
public:
    //! Empty constructor.
    XMainWindow(){ }
    //! Empty destructor.
    ~XMainWindow(){}
    //! Called from main.cpp.
    void run(){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        //! glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        //! Glfw window creation
        window=glfwCreateWindow(myWidth, myHeight, myDialogName.c_str(), NULL, NULL);
        setWindowPointer(window);

        if (window==NULL){
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwSetWindowOpacity(window,1.0); // 0-1. 1=no opacy.
        glfwMakeContextCurrent(window);
        glfwSwapInterval(0);

        //! glad: load all OpenGL function pointers
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(EXIT_FAILURE);
        }

        //! Callback functions, visit XWindow.h
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetCharCallback(window, CharacterCallback);
        glfwSetScrollCallback(window, ScrollCallBack);
        glfwSetCursorPosCallback(window, MousePosCallBack);
        glfwSetMouseButtonCallback(window, MouseButtonCallBack);
        glfwSetWindowCloseCallback(window, WindowCloseCallBack);
        glfwSetWindowSizeLimits(window,0,0,GLFW_DONT_CARE,GLFW_DONT_CARE);

        //! OpenGl scissor implementation.
        setScissorWindow(Window());
        enableScissor(1);

        //! A button.
        myButton=new XButton(Window());
        myButton->setSize({{200,100,0},200,100});
        myButton->setColor(XColorType::BackgroundColor,{0.9,0.9,0.9,1.0});
        myButton->setString("button");
        addWidget(myButton);

        //! The dialog where opencascade is drawed to. Like offscreen rendering, cq offscreen Framebuffer Fbo.
        myDummyDialog=new XDialog();

        //! Main thread.
        while (!glfwWindowShouldClose(window)){
            glfwMakeContextCurrent(window); //! Solves window flickering.
            glfwGetFramebufferSize(window, &myWidth, &myHeight);
            //! Set the XWindow size.
            this->setWindowDimension(myWidth,myHeight);
            mySize->setSize({{0,0,0},float(myWidth),float(myHeight)});
            //! Set the scissor size.
            setScissorSize(mySize->Size());
            //! ScissorSize().printSize("ScissorSize Mainwindow:");

            //! Reset OpenGl state.
            glViewport(0, 0, myWidth, myHeight);
            glClear(GL_COLOR_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, myWidth, myHeight, 0, -10000, 10000);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            //! Used for mouse cursor blink and animation.
            if(glfwGetTime()>1){ //! Reset every 1000 Ms.
                glfwSetTime(0);
            }
            //! Timer for blinking mouse cursor when using text editor widgets. This function has to be done called once each project.
            Mouse.setTime(glfwGetTime()*1000);

            //! If dummy dialog is up and running, draw the opencascade texture on this window.
            if(myDummyDialog!=NULL){
                //! This draw's the openGl texture, here right now. OpenGl's state machine trick.
                //! Draw it in this window before the glfw buffer swap.
                myDummyDialog->drawTexture();
            }
            //! Draw content, this will draw the button, wich is part of the widgetVec. The above addWidget function.
            drawWidgetVec();
            //! Draw the result.
            glfwSwapBuffers(window);
            glfwPollEvents();

            //! Subwindow's are processed after the MainWindow bufferswap.
            if(myDummyDialog!=NULL){
                //! Hide the dummy window.
                glfwHideWindow(myDummyDialog->Window()->GlfwWindowPointer());
                //! Set the dummy window size the same as this window size. This is also the OpenGl texture output size.
                glfwSetWindowSize(myDummyDialog->Window()->GlfwWindowPointer(),mySize->Width(),mySize->Height());
                //! This update opencascade myView, the central opencascade routine.
                myDummyDialog->draw();
                //! Process opencascade mouse and key events.
                myDummyDialog->processEvents();
                //! If this window has to close, close also the dummydialog.
                if(myDummyDialog->shouldClose() || glfwWindowShouldClose(window)){
                    myDummyDialog->close();
                    std::cout<<"closing window."<<std::endl;
                    myDummyDialog=NULL;
                }
            }
        }
        //! Disable the scissor.
        enableScissor(0);
        //! Destroy dummy dialog.
        myDummyDialog->close();
        myDummyDialog=NULL;
        //! Destroy mainwindow.
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
private:
    GLFWwindow* window;
    std::string myDialogName="XOpenCascade";
    int myWidth=500, myHeight=250;
    XSize *mySize=new XSize();

    XButton *myButton;
    XDialog *myDummyDialog;
};

#endif // XMAINWINDOW_H
























#ifndef XDIALOG_H
#define XDIALOG_H
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
#include <SOIL/SOIL.h>

#include <XWidget.h>
#include <XLinuxCnc.h>

//! Dummy dialog to draw the opencascade content. To show the dummy Dialog, in MainWindow outcomment : glfwHideWindow(myDummyDialog->Window()->GlfwWindowPointer());
//! Thiss class is just a GlfwWindow creation and updated by the XMainWindow thread by calling : draw();
class XDialog: public XWidget {
public:
    //! Empty constructor.
    XDialog(){
        init();
    }
    //! Empty destructor.
    ~XDialog(){}
    //! Return widget type.
    std::string Type(){
        return "XDialog";
    }
    //! Set the widget size.
    void setSize(XSize theSize){
        myWidth=theSize.Width();
        myHeight=theSize.Height();
    }
    //! Return the widget size.
    XSize Size(){
        return {{0.0,0.0,0.0},float(myWidth),float(myHeight)};
    }
    //! Init, cq setup the dialog.
    void init(){
        //! Ensure the init stage is done once.
        if(!myInit){
            std::cout<<"Dialog init"<<std::endl;

            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            //! glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
            this->setName("Dialog Opencascade");
            window =glfwCreateWindow(myWidth, myHeight, this->Name().c_str(), NULL, NULL);
            setWindowPointer(window);
            setWindowDimension(myWidth,myHeight);
            mySize->setSize({{0,0,0},float(myWidth),float(myHeight)});
            //! Usable for debugging.
            //! glfwSetWindowPos(window,10,10);

            if (window==NULL){
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                exit(EXIT_FAILURE);
            }

            glfwSetWindowOpacity(window,1.0); //! 0-1. 1=no opacy.
            glfwMakeContextCurrent(window);
            glfwSwapInterval(0);

            //! Callback functions, visit XWindow.h
            glfwSetKeyCallback(window, KeyCallback);
            glfwSetCharCallback(window, CharacterCallback);
            glfwSetScrollCallback(window, ScrollCallBack);
            glfwSetCursorPosCallback(window, MousePosCallBack);
            glfwSetMouseButtonCallback(window, MouseButtonCallBack);

            //! Use a window icon.
            GLFWimage images[1];
            int width, height, channels; //! Channels 4=RGBA.
            images[0].pixels=SOIL_load_image("icons/Adwaita/16x16/legacy/dialog-information.png",&width,&height,&channels,0);
            images[0].height=width;
            images[0].width=height;
            glfwSetWindowIcon(window, 1, images);

            //! Set the openGl scissor size.
            setScissorWindow(Window());

            //! Add opencascade widget.
            myOcct=new XLinuxCnc(Window());
            addWidget(myOcct);

            myInit=1;
        }
    }
    //! Update the dialog, draw content.
    void draw(){
        glfwMakeContextCurrent(window); //! Solves window flickering.
        glfwGetFramebufferSize(window, &myWidth, &myHeight);
        //! Set the XWindow size.
        setWindowDimension(myWidth,myHeight);
        //! Draw WidgetVec content.
        drawWidgetVec();
    }
    //! Function to draw the openGl texture.
    void drawTexture(){
        myOcct->drawTexture();
    }
    //! Return if this window should be closed.
    bool shouldClose(){
        if(glfwWindowShouldClose(window)){
            return 1;
        }
        return 0;
    }
    //! Close this window.
    void close(){
        myOcct=NULL;
        glfwDestroyWindow(window);
    }
    //! Process a event.
    void processEvent(){
        XPython().runPython();
    }
private:
    GLFWwindow* window;
    int myWidth=500, myHeight=250;
    XSize *mySize=new XSize();
    bool myInit=0;
    XLinuxCnc *myOcct;
};
#endif



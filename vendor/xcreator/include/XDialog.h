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

class XDialog: public XWidget {
public:
    XDialog(){init();}
    ~XDialog(){}

    std::string Type(){
        return "XDialog";
    }
    void setSize(XSize theSize){
        myWidth=theSize.Width();
        myHeight=theSize.Height();
    }
    XSize Size(){
        return {{0.0,0.0,0.0},float(myWidth),float(myHeight)};
    }

    void init(){
        std::cout<<"Dialog init"<<std::endl;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        this->setName("Dialog Test");
        window =glfwCreateWindow(myWidth, myHeight, this->Name().c_str(), NULL, NULL);
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

        glfwSetKeyCallback(window, KeyCallback);
        glfwSetCharCallback(window, CharacterCallback);
        glfwSetScrollCallback(window, ScrollCallBack);
        glfwSetCursorPosCallback(window, MousePosCallBack);
        glfwSetMouseButtonCallback(window, MouseButtonCallBack);

        GLFWimage images[1];
        int width, height, channels;
        images[0].pixels=SOIL_load_image("icons/Adwaita/16x16/legacy/dialog-information.png",&width,&height,&channels,0);
        // std::cout<<"channels:"<<channels<<std::endl; // Output : 4 channels. // Rbga..
        images[0].height=width;
        images[0].width=height;
        glfwSetWindowIcon(window, 1, images);

        setScissorWindow(Window());
    }
    void draw(){
        glfwMakeContextCurrent(window); // Solves window flickering.
        glfwGetFramebufferSize(window, &myWidth, &myHeight);
        //! Set the XWindow size.
        setWindowDimension(myWidth,myHeight);
        //! Set the XSize.
        mySize->setSize({{0,0,0},float(myWidth),float(myHeight)});

        glViewport(0, 0, myWidth, myHeight);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, myWidth, myHeight, 0, -10000, 10000);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //! Restart the scissor at the begin of every Window cq dialog.
        restartScissor();
        //! Set the scissor size.
        setScissorSize(mySize->Size());
        //! ScissorSize().printSize("designerdialog scissorsize:");

        //! Draw WidgetVec content.
        drawWidgetVec();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    bool shouldClose(){
        if(glfwWindowShouldClose(window)){
            return 1;
        }
        return 0;
    }
    void close(){
        glfwDestroyWindow(window);
    }
private:
    GLFWwindow* window;
    int myWidth=1200, myHeight=800;
    XSize *mySize=new XSize();
};
#endif



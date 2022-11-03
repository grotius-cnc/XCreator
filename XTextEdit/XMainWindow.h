#ifndef XMAINWINDOW_H
#define XMAINWINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <XWidget.h>
#include <XButton.h>
#include <XImage.h>
#include <XWindow.h>
#include <XMouse.h>
#include <XKey.h>
#include <XCursor.h>
#include <XTemplate.h>
#include <XScissor.h>
#include <XTextEdit.h>
#include <XImageButtonFileOpen.h>
#include <XImageButtonFileSave.h>
#include <tinyfiledialogs.h>

class XMainWindow : public XWidget {
public:
    XMainWindow(std::string theFile):myFile(theFile){ }
    XMainWindow(std::string theDialogName, uint theStartupWidth, uint theStartupHeight):myDialogName(theDialogName),myWidth(theStartupWidth),myHeight(theStartupHeight){ }
    ~XMainWindow(){}

    void run(){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        //! glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        //! glfw window creation
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

        //! glad: load all OpenGL function pointers
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

        GLFWimage images[1];
        int width, height, channels;
        images[0].pixels=SOIL_load_image("icons/document-edit.png",&width,&height,&channels,0);
        // std::cout<<"channels:"<<channels<<std::endl; // Output : 4 channels. // Rbga..
        images[0].height=width;
        images[0].width=height;
        glfwSetWindowIcon(window, 1, images);

        myCursorIcon=new XCursor(Window());

        myFileOpenButton=new XImageButtonFileOpen(Window());
        myFileOpenButton->setSize({{0,0,0},32,32});
        addWidget(myFileOpenButton);

        myFileSaveAsButton=new XImageButtonFileSave(Window());
        myFileSaveAsButton->setSize({{32,0,0},32,32});
        addWidget(myFileSaveAsButton);

        myFileSaveButton=new XImageButton(Window(),"icons/document-save.png");
        myFileSaveButton->setSize({{64,0,0},32,32});
        addWidget(myFileSaveButton);

        myTextEdit=new XTextEdit(Window());
        myTextEdit->setSize({{0,32,0},500,250-32});
        myTextEdit->init();
        addWidget(myTextEdit);

        if(myFile.size()>0){
            myTextEdit->loadFile(myFile);
        }

        setScissorWindow(Window());
        enableScissor(1);

        while (!glfwWindowShouldClose(window)){
            glfwMakeContextCurrent(window); //! Solves window flickering.

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

            if(glfwGetTime()>1){ //! Reset every 1000 Ms.
                glfwSetTime(0);
            }
            //! Timer for blinking mouse cursor when using text editor widgets. This function has to be done called once each project.
            Mouse.setTime(glfwGetTime()*1000);

            //! Events.
            myTextEdit->setSize({{0,32,0},mySize->Width(),mySize->Height()-32});

            if(myFileOpenButton->isPressed()){
                myFile=myFileOpenButton->Result();
                myTextEdit->loadFile(myFile);
            }
            if(myFileOpenButton->isHovered()){
                myCursorIcon->setArrowCursor();
            }
            if(myFileSaveAsButton->isPressed()){
                myTextEdit->saveFile(myFileSaveAsButton->Result());
            }
            if(myFileSaveAsButton->isHovered()){
                myCursorIcon->setArrowCursor();
            }
            if(myFileSaveButton->isHovered()){
                myCursorIcon->setArrowCursor();
            }
            if(myFileSaveButton->isPressed()){
                if(myFile.size()>0){
                    myTextEdit->saveFile(myFile);
                } else {
                    std::string myDialogName="Message", myMessage="Use save-as, empty file name.";

                    //! Vendor interface function.
                    tinyfd_messageBox(
                                myDialogName.c_str(),
                                myMessage.c_str(),
                                "ok",
                                NULL, //! "error" to show as error dialog.
                                0);
                }
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
    std::string myFile;
    GLFWwindow* window;
    std::string myDialogName="XTextEditor";
    int myWidth=500, myHeight=250;
    XSize *mySize=new XSize();

    //! XButton *myButton = new XButton(myWindow); does not work because myWindow has not been initialised at this stage.
    XTextEdit *myTextEdit;
    XImageButtonFileOpen *myFileOpenButton;
    XImageButtonFileSave *myFileSaveAsButton;
    XImageButton *myFileSaveButton;
    XCursor *myCursorIcon;
};
#endif
























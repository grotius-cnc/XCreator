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
#include <XToggleButton.h>
#include <XLabel.h>
#include <XTextEdit.h>
#include <XFrame.h>
#include <XSizeFrame.h>
#include <XVerticalLayout.h>
#include <XHorizontalLayout.h>
#include <XHorizontalSlider.h>
#include <XVerticalSlider.h>
#include <XLineEdit.h>
#include <XDesignerFrame.h>
#include <XImageButton.h>
#include <XWidgetPropertyInputList.h>
#include <XDesignerCodeGenerator.h>
#include <XWidgetPropertyInputList.h>
#include <XStretchLayout.h>
#include <XTreeView.h>
#include <XHorizontalSplitterLayout.h>
#include <XVerticalSplitterLayout.h>
#include <XStackedFrame.h>

//! When "process layout code" is pressed, a file "XTemplate.h" is saved in the build directory.
//! This file contains the generated layout made by the designer.
class XMainWindow : public XWidget {
public:
    XMainWindow(){ }
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
        //! --------------------
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
        //! ---------------------------------------
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

        //! Populate the designer dialog.
        float x=0, y=0;
        myButtonAddButton=new XButton(Window());
        myButtonAddButton->setString("Add button");
        myButtonAddButton->setSize({{x,y,0},200,20});
        myButtonAddButton->setName("button_add_button");
        myButtonAddButton->setCenterText(0,1);
        addWidget(myButtonAddButton);
        x+=205;
        myButtonAddToggleButton=new XButton(Window());
        myButtonAddToggleButton->setString("Add toggle button");
        myButtonAddToggleButton->setSize({{x,y,0},200,20});
        myButtonAddToggleButton->setName("button_add_togglebutton");
        myButtonAddToggleButton->setCenterText(0,1);
        addWidget(myButtonAddToggleButton);
        x+=205;
        myButtonAddLabel=new XButton(Window());
        myButtonAddLabel->setString("Add label");
        myButtonAddLabel->setSize({{x,y,0},200,20});
        myButtonAddLabel->setName("button_add_label");
        myButtonAddLabel->setCenterText(0,1);
        addWidget(myButtonAddLabel);
        x+=205;
        myButtonAddFrame=new XButton(Window());
        myButtonAddFrame->setString("Add frame");
        myButtonAddFrame->setSize({{x,y,0},200,20});
        myButtonAddFrame->setName("button_add_frame");
        myButtonAddFrame->setCenterText(0,1);
        addWidget(myButtonAddFrame);
        x+=205;
        myButtonAddTextEdit=new XButton(Window());
        myButtonAddTextEdit->setString("Add textEdit");
        myButtonAddTextEdit->setSize({{x,y,0},200,20});
        myButtonAddTextEdit->setName("button_add_textedit");
        myButtonAddTextEdit->setCenterText(0,1);
        addWidget(myButtonAddTextEdit);
        x+=205;
        myButtonAddLineEdit=new XButton(Window());
        myButtonAddLineEdit->setString("Add lineEdit");
        myButtonAddLineEdit->setSize({{x,y,0},200,20});
        myButtonAddLineEdit->setName("button_add_lineedit");
        myButtonAddLineEdit->setCenterText(0,2);
        addWidget(myButtonAddLineEdit);
        x=0;
        y+=25;
        myButtonAddHorizontalSlider=new XButton(Window());
        myButtonAddHorizontalSlider->setString("Add horizontal slider");
        myButtonAddHorizontalSlider->setSize({{x,y,0},200,20});
        myButtonAddHorizontalSlider->setName("button_add_horizontal_slider");
        myButtonAddHorizontalSlider->setCenterText(0,1);
        addWidget(myButtonAddHorizontalSlider);
        x+=205;
        myButtonAddVerticalSlider=new XButton(Window());
        myButtonAddVerticalSlider->setString("Add vertical slider");
        myButtonAddVerticalSlider->setSize({{x,y,0},200,20});
        myButtonAddVerticalSlider->setName("button_add_vertical_slider");
        myButtonAddVerticalSlider->setCenterText(0,1);
        addWidget(myButtonAddVerticalSlider);
        x+=205;
        myButtonAddHorizontalLayout=new XButton(Window());
        myButtonAddHorizontalLayout->setString("Add horizontal layout");
        myButtonAddHorizontalLayout->setSize({{x,y,0},200,20});
        myButtonAddHorizontalLayout->setName("button_add_horizontal_layout");
        myButtonAddHorizontalLayout->setCenterText(0,1);
        addWidget(myButtonAddHorizontalLayout);
        x+=205;
        myButtonAddVerticalLayout=new XButton(Window());
        myButtonAddVerticalLayout->setString("Add vertical layout");
        myButtonAddVerticalLayout->setSize({{x,y,0},200,20});
        myButtonAddVerticalLayout->setName("button_add_vertical_layout");
        myButtonAddVerticalLayout->setCenterText(0,1);
        addWidget(myButtonAddVerticalLayout);
        x+=205;
        myButtonAddSizeFrame=new XButton(Window());
        myButtonAddSizeFrame->setString("Add size frame");
        myButtonAddSizeFrame->setSize({{x,y,0},200,20});
        myButtonAddSizeFrame->setName("button_add_size_frame");
        myButtonAddSizeFrame->setCenterText(0,1);
        addWidget(myButtonAddSizeFrame);
        x+=205;
        myButtonAddTreeView=new XButton(Window());
        myButtonAddTreeView->setString("Add tree view");
        myButtonAddTreeView->setSize({{x,y,0},200,20});
        myButtonAddTreeView->setName("button_add_tree_view");
        myButtonAddTreeView->setCenterText(0,1);
        addWidget(myButtonAddTreeView);
        x=0;
        y+=25;
        myButtonAddHorizontalSplitterLayout=new XButton(Window());
        myButtonAddHorizontalSplitterLayout->setString("Add horizontal splitter layout");
        myButtonAddHorizontalSplitterLayout->setSize({{x,y,0},200,20});
        myButtonAddHorizontalSplitterLayout->setName("button_horizontal_splitter_layout");
        myButtonAddHorizontalSplitterLayout->setCenterText(0,1);
        addWidget(myButtonAddHorizontalSplitterLayout);
        x+=205;
        myButtonAddVerticalSplitterLayout=new XButton(Window());
        myButtonAddVerticalSplitterLayout->setString("Add vertical splitter layout");
        myButtonAddVerticalSplitterLayout->setSize({{x,y,0},200,20});
        myButtonAddVerticalSplitterLayout->setName("button_vertical_splitter_layout");
        myButtonAddVerticalSplitterLayout->setCenterText(0,1);
        addWidget(myButtonAddVerticalSplitterLayout);
        x+=205;
        myButtonAddStackedFrame=new XButton(Window());
        myButtonAddStackedFrame->setString("Add stacked frame");
        myButtonAddStackedFrame->setSize({{x,y,0},200,20});
        myButtonAddStackedFrame->setName("button_add_stacked_frame");
        myButtonAddStackedFrame->setCenterText(0,1);
        addWidget(myButtonAddStackedFrame);
        x+=205;
        myButtonWidgetPropertyInputList=new XButton(Window());
        myButtonWidgetPropertyInputList->setString("Add widget property list");
        myButtonWidgetPropertyInputList->setSize({{x,y,0},200,20});
        myButtonWidgetPropertyInputList->setName("button_add_widget_property_list");
        myButtonWidgetPropertyInputList->setCenterText(0,1);
        addWidget(myButtonWidgetPropertyInputList);
        x+=205;
        myButtonAddStretchLayout=new XButton(Window());
        myButtonAddStretchLayout->setString("Add stretch layout");
        myButtonAddStretchLayout->setSize({{x,y,0},200,20});
        myButtonAddStretchLayout->setCenterText(0,1);
        //! AutoGeneratedName.
        addWidget(myButtonAddStretchLayout);
        x+=205;
        myButtonGenerateCode=new XButton(Window());
        myButtonGenerateCode->setString("Process layout code");
        myButtonGenerateCode->setSize({{x,y,0},200,20});
        myButtonGenerateCode->setName("button_process_layout");
        myButtonGenerateCode->setCenterText(0,1);
        addWidget(myButtonGenerateCode);
        x=0;
        y+=25;
        myImageButtonWidgetUp=new XImageButton(Window(),"icons/Adwaita/16x16/legacy/go-up.png");
        myImageButtonWidgetUp->setSize({{x,y,0},20,20});
        myImageButtonWidgetUp->setName("widget_up");
        addWidget(myImageButtonWidgetUp);
        x+=20;
        myImageButtonWidgetDown=new XImageButton(Window(),"icons/Adwaita/16x16/legacy/go-down.png");
        myImageButtonWidgetDown->setSize({{x,y,0},20,20});
        myImageButtonWidgetDown->setName("widget_down");
        addWidget(myImageButtonWidgetDown);
        x+=20;
        myImageButtonClear=new XImageButton(Window(),"icons/Adwaita/16x16/legacy/edit-clear-all.png");
        myImageButtonClear->setSize({{x,y,0},20,20});
        myImageButtonClear->setName("imageBtnClear");
        addWidget(myImageButtonClear);
        x+=20;

        myLabelWidgetStructure=new XLabel(Window());
        myLabelWidgetStructure->setSize({{615,100,0},250,250});
        myLabelWidgetStructure->setName("LabelWidgetStructure");
        addWidget(myLabelWidgetStructure);

        myDesingerFrame=new XDesignerFrame(Window());
        myDesingerFrame->setSize({{0,100,0},610,500});
        myDesingerFrame->setName("DesignerFrame");
        addWidget(myDesingerFrame);

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

            //! Process events.
            if(myButtonAddButton->Event(XEventEnum::PressedLeft)){
                XButton* theButton=new XButton(Window());
                theButton->setSize({myDesingerFrame->Size().Origin(),200,50});
                theButton->setName("Button_"+std::to_string(myId));
                theButton->setString("Button_"+std::to_string(myId)); myId++;
                myDesingerFrame->addWidget(theButton);
                // std::cout<<"add button pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddButton->Event(XEventEnum::ReleasedLeft)){}

            if(myButtonAddToggleButton->Event(XEventEnum::PressedLeft)){
                XToggleButton* theToggleButton=new XToggleButton(Window());
                theToggleButton->setSize({myDesingerFrame->Size().Origin(),200,50});
                theToggleButton->setName("ToggleButton_"+std::to_string(myId));
                theToggleButton->setString("ToggleButton_"+std::to_string(myId)); myId++;
                myDesingerFrame->addWidget(theToggleButton);
                //! std::cout<<"add button pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddButton->Event(XEventEnum::ReleasedLeft)){}


            if(myButtonAddLabel->Event(XEventEnum::PressedLeft)){
                XLabel* theLabel=new XLabel(Window());
                theLabel->setSize({myDesingerFrame->Size().Origin(),100,18});
                theLabel->setName("Label_"+std::to_string(myId));
                theLabel->setString("Label_"+std::to_string(myId)); myId++;
                myDesingerFrame->addWidget(theLabel);
                //! std::cout<<"add button pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddLabel->Event(XEventEnum::ReleasedLeft)){}

            if(myButtonAddVerticalLayout->Event(XEventEnum::PressedLeft)){
                XVerticalLayout *theVerticalLayout=new XVerticalLayout(Window());
                theVerticalLayout->setSize({myDesingerFrame->Size().Origin(),125,125});
                theVerticalLayout->setName("VerticalLayout_"+std::to_string(myId)); myId++;
                myDesingerFrame->addWidget(theVerticalLayout);
                //! std::cout<<"add frame pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddVerticalLayout->Event(XEventEnum::ReleasedLeft)){}

            if(myButtonAddHorizontalLayout->Event(XEventEnum::PressedLeft)){
                XHorizontalLayout *theHorizontalLayout=new XHorizontalLayout(Window());
                theHorizontalLayout->setSize({myDesingerFrame->Size().Origin(),125,125});
                theHorizontalLayout->setName("HorizontalLayout_"+std::to_string(myId)); myId++;
                myDesingerFrame->addWidget(theHorizontalLayout);
                //! std::cout<<"add frame pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddHorizontalLayout->Event(XEventEnum::ReleasedLeft)){}

            if(myButtonAddFrame->Event(XEventEnum::PressedLeft)){
                XFrame* theFrame=new XFrame(Window());
                theFrame->setSize({myDesingerFrame->Size().Origin(),300,300});
                theFrame->setName("Frame_"+std::to_string(myId)); myId++;
                myDesingerFrame->addWidget(theFrame);
                //! std::cout<<"add frame pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddFrame->Event(XEventEnum::ReleasedLeft)){}

            if(myButtonAddTextEdit->Event(XEventEnum::PressedLeft)){
                XTextEdit* theTextEdit=new XTextEdit(Window());
                theTextEdit->setSize({myDesingerFrame->Size().Origin(),300,300});
                theTextEdit->setName("TextEdit_"+std::to_string(myId)); myId++;
                theTextEdit->setModeEdit(1);
                myDesingerFrame->addWidget(theTextEdit);
                // std::cout<<"add frame pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddTextEdit->Event(XEventEnum::ReleasedLeft)){}

            if(myButtonAddLineEdit->Event(XEventEnum::PressedLeft)){
                XLineEdit* theLineEdit=new XLineEdit(Window());
                theLineEdit->setSize({myDesingerFrame->Size().Origin(),100,18});
                theLineEdit->setName("LineEdit_"+std::to_string(myId)); myId++;
                theLineEdit->setModeEdit(1);
                myDesingerFrame->addWidget(theLineEdit);
                //! std::cout<<"add frame pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddLineEdit->Event(XEventEnum::ReleasedLeft)){}

            if(myButtonAddHorizontalSlider->Event(XEventEnum::PressedLeft)){
                XHorizontalSlider *theHorizontalSlider=new XHorizontalSlider(Window());
                theHorizontalSlider->setSize({myDesingerFrame->Size().Origin(),250,18});
                theHorizontalSlider->setName("HorizontalSlider_"+std::to_string(myId)); myId++;
                myDesingerFrame->addWidget(theHorizontalSlider);
                // std::cout<<"add frame pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddHorizontalSlider->Event(XEventEnum::ReleasedLeft)){}

            if(myButtonAddVerticalSlider->Event(XEventEnum::PressedLeft)){
                XVerticalSlider *theVerticalSlider=new XVerticalSlider(Window());
                theVerticalSlider->setSize({myDesingerFrame->Size().Origin(),18,258});
                theVerticalSlider->setName("VerticalSlider_"+std::to_string(myId)); myId++;
                myDesingerFrame->addWidget(theVerticalSlider);
                // std::cout<<"add frame pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddVerticalSlider->Event(XEventEnum::ReleasedLeft)){}

            if(myButtonAddSizeFrame->Event(XEventEnum::PressedLeft)){
                XSizeFrame *theSizeFrame=new XSizeFrame(Window());
                theSizeFrame->setSize({myDesingerFrame->Size().Origin(),500,508});
                theSizeFrame->setName("SizeFrame_"+std::to_string(myId)); myId++;
                theSizeFrame->setModeEdit(1);
                myDesingerFrame->addWidget(theSizeFrame);
                // std::cout<<"add frame pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddSizeFrame->Event(XEventEnum::ReleasedLeft)){}

            if(myButtonAddTreeView->Event(XEventEnum::PressedLeft)){
                XTreeView *theTreeView=new XTreeView(Window());
                theTreeView->setSize({myDesingerFrame->Size().Origin(),500,508});
                theTreeView->setName("TreeView_"+std::to_string(myId)); myId++;
                myDesingerFrame->addWidget(theTreeView);
                // std::cout<<"add frame pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddTreeView->Event(XEventEnum::ReleasedLeft)){}

            if(myButtonAddHorizontalSplitterLayout->Event(XEventEnum::PressedLeft)){
                XHorizontalSplitterLayout *theHorizontalSplitterLayout=new XHorizontalSplitterLayout(Window());
                theHorizontalSplitterLayout->setSize({myDesingerFrame->Size().Origin(),500,508});
                theHorizontalSplitterLayout->setName("HorizontalSplitterLayout_"+std::to_string(myId)); myId++;
                myDesingerFrame->addWidget(theHorizontalSplitterLayout);
                // std::cout<<"add frame pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddHorizontalSplitterLayout->Event(XEventEnum::ReleasedLeft)){}

            if(myButtonAddVerticalSplitterLayout->Event(XEventEnum::PressedLeft)){
                XVerticalSplitterLayout *theVerticalSplitterLayout=new XVerticalSplitterLayout(Window());
                theVerticalSplitterLayout->setSize({myDesingerFrame->Size().Origin(),500,508});
                theVerticalSplitterLayout->setName("VerticalSplitterLayout_"+std::to_string(myId)); myId++;
                myDesingerFrame->addWidget(theVerticalSplitterLayout);
                // std::cout<<"add frame pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddVerticalSplitterLayout->Event(XEventEnum::ReleasedLeft)){}

            if(myButtonAddStackedFrame->Event(XEventEnum::PressedLeft)){
                XStackedFrame *theStackedFrame=new XStackedFrame(Window());
                theStackedFrame->setSize({myDesingerFrame->Size().Origin(),500,508});
                theStackedFrame->setName("StackedFrame_"+std::to_string(myId)); myId++;
                myDesingerFrame->addWidget(theStackedFrame);
                //! std::cout<<"add frame pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddStackedFrame->Event(XEventEnum::ReleasedLeft)){}

            if(myButtonAddStretchLayout->Event(XEventEnum::PressedLeft)){
                XStretchLayout *theStretchLayout=new XStretchLayout(Window());
                theStretchLayout->setSize({myDesingerFrame->Size().Origin(),500,508});
                theStretchLayout->setName("StretchLayout_"+std::to_string(myId)); myId++;
                myDesingerFrame->addWidget(theStretchLayout);
                // std::cout<<"add stretchLayout pressed"<<std::endl;
            }
            //! Reset buttonpress cycle by a release request.
            if(myButtonAddStretchLayout->Event(XEventEnum::ReleasedLeft)){}

            if(myButtonGenerateCode->Event(XEventEnum::PressedLeft)){
                std::string thePath=std::filesystem::current_path();
                //! std::cout<<"current path:"<<thePath<<std::endl;
                XDesignerCodeGenerator().processCode(myDesingerFrame,thePath+"/LICENSE.md",thePath+"/VirtualFunctionTemplateText.txt");
            }
            if(myButtonGenerateCode->Event(XEventEnum::ReleasedLeft)){}

            if(myImageButtonClear->Event(XEventEnum::PressedLeft)){
                myDesingerFrame->clearWidgetVec();
                //! std::cout<<"clear pressed"<<std::endl;
            }
            if(myImageButtonClear->Event(XEventEnum::ReleasedLeft)){}

            if(myImageButtonWidgetUp->Event(XEventEnum::PressedLeft)){
                //! std::cout<<"widget up pressed"<<std::endl;
            }
            if(myImageButtonWidgetUp->Event(XEventEnum::ReleasedLeft)){}

            if(myImageButtonWidgetDown->Event(XEventEnum::PressedLeft)){
                //! std::cout<<"widget down pressed"<<std::endl;
            }
            if(myImageButtonWidgetDown->Event(XEventEnum::ReleasedLeft)){}

            myLabelWidgetStructure->setSize({{float(myWidth)-200,100,0},200,400});
            myLabelWidgetStructure->setString(myDesingerFrame->WidgetStructure());

            myDesingerFrame->setSize({{10,110,0},float(myWidth)-210,float(myHeight-100)});

            //! Draw WidgetVec content.
            drawWidgetVec();

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
    std::string myDialogName="XDesigner";
    int myWidth=1500, myHeight=800;
    XSize *mySize=new XSize();

    //! XButton *myButton = new XButton(myWindow); does not work because myWindow has not been initialised at this stage.
    XButton *myButtonAddStretchLayout;
    XButton *myButtonAddButton;
    XButton *myButtonAddToggleButton;
    XButton *myButtonAddLabel;
    XButton *myButtonAddTextEdit;
    XButton *myButtonAddLineEdit;
    XButton *myButtonAddFrame;
    XButton *myButtonAddSizeFrame;
    XButton *myButtonAddVerticalLayout;
    XButton *myButtonAddHorizontalLayout;
    XButton *myButtonAddHorizontalSlider;
    XButton *myButtonAddVerticalSlider;
    XButton *myButtonAddTreeView;
    XButton *myButtonAddHorizontalSplitterLayout;
    XButton *myButtonAddVerticalSplitterLayout;
    XButton *myButtonAddStackedFrame;
    XButton *myButtonWidgetPropertyInputList;
    XButton *myButtonGenerateCode;

    XImageButton *myImageButtonWidgetUp, *myImageButtonWidgetDown, *myImageButtonClear;
    XDesignerFrame *myDesingerFrame;
    XLabel *myLabelWidgetStructure;

    uint myId=0;
};
#endif
























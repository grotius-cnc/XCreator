#ifndef XOPENCASCADE_H
#define XOPENCASCADE_H
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
#include <XWidget.h>
#include <XSize.h>
#include <XRectangular.h>
#include <XChar.h>
#include <XColor.h>
#include <XPoint.h>
#include <XKey.h>
#include <XMouse.h>
#include <XTriangle.h>
//! No need to include native glfw headers. We made a XConnection class to avoid name duplicates like XPoint, XTriangle wich
//! are also used by some X11 files.
#include <XConnection.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);

//! Opencascade.
#include <OpenGl_GraphicDriver.hxx>
#include <OpenGl_Context.hxx>
#include <OpenGl_FrameBuffer.hxx>
#include <OpenGl_GraphicDriver.hxx>

#include <V3d_View.hxx>

#include <Aspect_DisplayConnection.hxx>
#include <Aspect_Handle.hxx>
#include <Aspect_Window.hxx>
#include <Aspect_NeutralWindow.hxx>
#include <Aspect_RenderingContext.hxx>
#include <Aspect_Window.hxx>
#include <Image_PixMap.hxx>

#include <TCollection_AsciiString.hxx>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>

#include <Message.hxx>
#include <Message_Messenger.hxx>

#include <Graphic3d_Vec.hxx>

#include <TopAbs_ShapeEnum.hxx>

#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewCube.hxx>
#include <AIS_Shape.hxx>
#include <AIS_ViewController.hxx>
#include <V3d_View.hxx>

#include <SOIL/SOIL.h>

class XOpencascade : public XWidget , public AIS_ViewController {
public:
    //! Empty constructor. setWindow or parent afterwards. Do a init() afterwards.
    XOpencascade(){}
    //! The button has to be a member of a GLFWWindow. Mouse events, key events, are valid for the specific window. Otherwise a button press could be valid from other window.
    XOpencascade(XWindow *theWindow){
        this->setWindow(theWindow);
        init();
    }
    //! Empty destructor.
    ~XOpencascade(){}
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XOpencascade";
    }
    //! Set the size of this widget. Size also handles the mouse & key events.
    void setSize(XSize theSize){
        mySize->setSize(theSize);
    }
    //! XOpencascade source file function.
    void getMyDisplay();

    //! Initialize opencascade.
    void init(){
        //! Setup fbo, setup glcontext.
        initGL(false,true);
    }
    //! draw this widget. Eventually use xyz offsets, for example while dragging a widget.
    void draw(){
        drawGL();
    }
    //! Draw the openGL texture.
    //!
    //! Note: opengl is a state machine, calling this function will just draw it on the window where the function call is done.
    //! So it's not drawing the texture on the XOpencascade window, this function is called from the MainWindow therefore it's drawed
    //! on the MainWindow screen.
    void drawTexture(){
        //! I don't like to compile a shader program each iteration. But it works.
        initGLShader();
        initGLTexture();
        drawGLTexture();
    }
    void processEvents(){
        //! Mouse scroll.
        onMouseScroll(Mouse.ScrollValueX(),Mouse.ScrollValueY());
        Mouse.resetMouseScrollValueYToZero();

        onMouseMove(Mouse.Position()->X(),Mouse.Position()->Y());
        onMouseButton(Mouse.Button(),Mouse.Status(),Key.Mods());

        //! Process the ViewController events.
        FlushViewEvents (myContext, myView, true);
    }

private:
    XString *myString=new XString("XOpencascade");
    XSize *mySize=new XSize();

    //! Opencascade
    Handle(OpenGl_GraphicDriver) myDriver;
    Handle(V3d_View) myView;
    Handle(V3d_Viewer) myViewer;
    Handle(AIS_InteractiveContext) myContext;
    Handle(AIS_ViewCube) myViewCube;
    // Handle(OpenGl_Texture) myTexture;
    Handle(OpenGl_FrameBuffer) myFbo;
    Handle(OpenGl_Context) myGlContext;
    // AIS_ViewController myViewController;
    Handle(AIS_Shape) myBox;
    Image_PixMap myPixmap;
    unsigned int myTexture;

    unsigned int VBO, VAO, EBO;
    unsigned int myShaderProgram;

    //! If opencascade screen needs resize update, these values are used to compare.
    int OLD_SCR_WIDTH = 0;
    int OLD_SCR_HEIGHT = 0;

    //! Convert GLFW mouse button into Aspect_VKeyMouse.
    static Aspect_VKeyMouse mouseButtonFromGlfw (int theButton)
    {
        switch (theButton)
        {
        case GLFW_MOUSE_BUTTON_LEFT:   return Aspect_VKeyMouse_LeftButton;
        case GLFW_MOUSE_BUTTON_RIGHT:  return Aspect_VKeyMouse_RightButton;
        case GLFW_MOUSE_BUTTON_MIDDLE: return Aspect_VKeyMouse_MiddleButton;
        }
        return Aspect_VKeyMouse_NONE;
    }

    //! Convert GLFW key modifiers into Aspect_VKeyFlags.
    static Aspect_VKeyFlags keyFlagsFromGlfw (int theFlags)
    {
        Aspect_VKeyFlags aFlags = Aspect_VKeyFlags_NONE;
        if ((theFlags & GLFW_MOD_SHIFT) != 0)
        {
            aFlags |= Aspect_VKeyFlags_SHIFT;
        }
        if ((theFlags & GLFW_MOD_CONTROL) != 0)
        {
            aFlags |= Aspect_VKeyFlags_CTRL;
        }
        if ((theFlags & GLFW_MOD_ALT) != 0)
        {
            aFlags |= Aspect_VKeyFlags_ALT;
        }
        if ((theFlags & GLFW_MOD_SUPER) != 0)
        {
            aFlags |= Aspect_VKeyFlags_META;
        }
        return aFlags;
    }
    //! Mouse scroll event.
    void onMouseScroll (double theOffsetX, double theOffsetY)
    {
        Graphic3d_Vec2i aPos = Graphic3d_Vec2i(Mouse.Position()->X(),Mouse.Position()->Y());
        if (!myView.IsNull())
        {
            UpdateZoom (Aspect_ScrollDelta (aPos, int(theOffsetY * 8.0)));
        }
    }
    //! Mouse button event.
    void onMouseButton (int theButton, int theAction, int theMods)
    {
        if (myView.IsNull()) { return; }

        Graphic3d_Vec2i aPos = Graphic3d_Vec2i(Mouse.Position()->X(),Mouse.Position()->Y());
        if (theAction == GLFW_PRESS)
        {
            PressMouseButton (aPos, mouseButtonFromGlfw (theButton), keyFlagsFromGlfw (theMods), false);
        }
        else
        {
            ReleaseMouseButton (aPos, mouseButtonFromGlfw (theButton), keyFlagsFromGlfw (theMods), false);
        }
    }
    //! Mouse move event.
    void onMouseMove (int thePosX, int thePosY)
    {
         const Graphic3d_Vec2i aNewPos = Graphic3d_Vec2i(Mouse.Position()->X(),Mouse.Position()->Y());
        if (!myView.IsNull())
        {
            UpdateMousePosition (aNewPos, PressedMouseButtons(), LastMouseFlags(), false);
        }
    }

    //! Draw opencascade content to the glfw window.
    void drawGL()
    {
        //! Update window when it's resized.
        if(OLD_SCR_HEIGHT!=Window()->Height() || OLD_SCR_WIDTH!=Window()->Width()){
            //! Set window size when resized.
            Handle(Aspect_NeutralWindow) aWindow = Handle(Aspect_NeutralWindow)::DownCast (myView->Window());
            //! To show it's not always filling the entire window.
            aWindow->SetSize(Window()->Width(),Window()->Height());
            myView->MustBeResized();
            myView->Invalidate();

            OLD_SCR_HEIGHT=Window()->Height();
            OLD_SCR_WIDTH=Window()->Width();
        }
        //! Display content.
        myContext->Display (myBox, AIS_Shaded, 0, false);

        //! Redraw.
        myView->Redraw();
        myGlContext->SwapBuffers();

        V3d_ImageDumpOptions options;
        options.BufferType=Graphic3d_BT_RGBA;
        options.Width=Window()->Width();
        options.Height=Window()->Height();

        //! Save the view as pixmap to be used as openGL texture later on.
        myView->ToPixMap(myPixmap,options);

        //! Dump as picture.jpg, load as texture with the XIcon class.
        //! myView->Dump("texture.png",Graphic3d_BufferType::Graphic3d_BT_RGBA);
    }
    //! Initialize opencascade.
    void initGL(bool initFramebuffer, bool initGLContext)
    {
        //! Setup display & driver.
        //! Handle(Aspect_DisplayConnection) aDisplay = new Aspect_DisplayConnection((Aspect_XDisplay* )glfwGetX11Display());
        Handle(Aspect_DisplayConnection) aDisplay = XConnention().getNewHandleAspectDisplayConnection();
        myDriver = new OpenGl_GraphicDriver (aDisplay, false);
        //! Set properties.
        myDriver->ChangeOptions().ffpEnable = Standard_False;
        //! aDriver->ChangeOptions().glslWarnings = Standard_True;
        myDriver->ChangeOptions().buffersNoSwap = Standard_False;
        //! lets QOpenGLWidget to manage buffer swap
        myDriver->ChangeOptions().buffersNoSwap = true;
        //! don't write into alpha channel
        //! aDriver->ChangeOptions().buffersOpaqueAlpha = true;
        //! offscreen FBOs should be always used
        myDriver->ChangeOptions().useSystemBuffer = false;

        //! Create viewer.
        myViewer = new V3d_Viewer (myDriver);
        myViewer->SetDefaultBackgroundColor (Quantity_NOC_BLACK);
        myViewer->SetDefaultLights();
        myViewer->SetLightOn();
        myViewer->SetDefaultTypeOfView (V3d_PERSPECTIVE);
        myViewer->ActivateGrid (Aspect_GT_Rectangular, Aspect_GDM_Lines);

        //! Create view from viewer.
        myView = myViewer->CreateView();
        myView->SetImmediateUpdate (false);
        //! Check.
        if(myViewer.IsNull()){
            std::cout<<"aViewer error."<<std::endl;
        }
        //! Check.
        if(myView.IsNull()){
            std::cout<<"aView error."<<std::endl;
        }
        //! Create context.
        myContext = new AIS_InteractiveContext (myViewer);

        //! Create 3D navigation cube.
        //! It seems it's not working properly when cube is clicked.
        myViewCube = new AIS_ViewCube();
        myViewCube->SetViewAnimation (myViewAnimation);
        myViewCube->SetBoxColor(Quantity_NOC_GRAY75);
        myViewCube->SetDrawAxes(false);
        myViewCube->SetFixedAnimationLoop (true);
        myViewCube->SetAutoStartAnimation (true);
        myViewCube->SetSize(40);
        myViewCube->SetFontHeight(10);
        myViewCube->SetTransformPersistence(
                    new Graphic3d_TransformPers(
                        Graphic3d_TMF_TriedronPers,
                        Aspect_TOTP_LEFT_LOWER,
                        Graphic3d_Vec2i(85, 85)));
        //! myContext->Display(myViewCube,Standard_True);

        //! Print the actual opencascade performance.
        myView->ChangeRenderingParams().NbMsaaSamples = 0; // warning - affects performance
        myView->ChangeRenderingParams().ToShowStats = true;
        myView->ChangeRenderingParams().CollectedStats = (Graphic3d_RenderingParams::PerfCounters )
                (Graphic3d_RenderingParams::PerfCounters_FrameRate
                 | Graphic3d_RenderingParams::PerfCounters_FrameTime
                 | Graphic3d_RenderingParams::PerfCounters_FrameTimeMax
                 | Graphic3d_RenderingParams::PerfCounters_Triangles
                 | Graphic3d_RenderingParams::PerfCounters_Lines
                 | Graphic3d_RenderingParams::PerfCounters_Points
                 );

        //! Set model view as perspective.
        myView->Camera()->SetProjectionType (Graphic3d_Camera::Projection_Perspective);

        /// Show triedron. This is the 3d axis cross at the lower left of the screen.
        myView->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_GOLD, 0.08, V3d_ZBUFFER);

        if(initGLContext){
            //! Create - opengl - context.
            myGlContext = new OpenGl_Context();
            //! if(!myGlContext->Init(glfwGetX11Window(Window()->GlfwWindowPointer()), glfwGetX11Display(), glfwGetGLXContext(Window()->GlfwWindowPointer()))){
            if(!myGlContext->Init(XConnention().getGlfwX11Window(Window()->GlfwWindowPointer()), XConnention().getGlfwX11Display(), XConnention().getGlfwContext(Window()->GlfwWindowPointer()))){
                std::cout<<"opengl_context init error."<<std::endl;
                return;
            }
            //! myGlContext->MakeCurrent();
        }

        if(initFramebuffer){
            //! Create frame buffer.
            myFbo = new OpenGl_FrameBuffer;
            //! Initialize the framebuffer.
            if(!myFbo->Init(myGlContext, Graphic3d_Vec2i(Window()->Width(), Window()->Height()), GL_RGBA8, GL_DEPTH24_STENCIL8, 0)) {
                myView->View()->SetFBO(myGlContext);
                myView->SetBackgroundColor(Quantity_NOC_ALICEBLUE);
                //! myTexture = myFbo->ColorTexture();

                std::cout<<"myFbo error."<<std::endl;
                return;
            }
        }
        //! This is a temponary way for getting the window for myView.
        Handle(Aspect_NeutralWindow) aWindow = new Aspect_NeutralWindow();
        if(aWindow.IsNull()){
            std::cout<<"aWindow error."<<std::endl;
            return;
        }
        Aspect_Drawable aNativeWin = (Aspect_Drawable) XConnention().getGlfwX11Window(Window()->GlfwWindowPointer());
        aWindow->SetNativeHandle (aNativeWin);
        aWindow->SetSize (Window()->Width() ,Window()->Height());
        // myView->SetWindow (aWindow, (Aspect_RenderingContext) glXGetCurrentContext());
        myView->SetWindow(aWindow, myGlContext->RenderingContext());

        //! Show perspective view.
        myView->Camera()->SetProjectionType (Graphic3d_Camera::Projection_Perspective);
        myView->FitAll();

        //! Create a shape, a box in this case.
        gp_Ax2 anAxis;
        anAxis.SetLocation (gp_Pnt (0.0, 0.0, 0.0));
        myBox = new AIS_Shape (BRepPrimAPI_MakeBox (anAxis, 200, 200, 200).Shape());
        //! Move cq. translate the box origin.
        gp_Trsf move;
        move.SetTranslation({0,0,0},{-100,-100,-100});
        myBox->SetLocalTransformation(move);
        //! Show object outlines.
        myBox->Attributes()->SetFaceBoundaryDraw(true);
        myBox->Attributes()->SetFaceBoundaryAspect(new Prs3d_LineAspect(Quantity_NOC_BLACK, Aspect_TOL_SOLID, 1.));
        myBox->Attributes()->SetIsoOnTriangulation(true);
        //! Set tranceparancy value 0-1.
        myBox->SetTransparency(0.5f);
    }
    //! dumpGlInfo
    void dumpGlInfo (bool theIsBasic)
    {
        TColStd_IndexedDataMapOfStringString aGlCapsDict;
        myView->DiagnosticInformation (aGlCapsDict, theIsBasic ? Graphic3d_DiagnosticInfo_Basic : Graphic3d_DiagnosticInfo_Complete);
        TCollection_AsciiString anInfo;
        for (TColStd_IndexedDataMapOfStringString::Iterator aValueIter (aGlCapsDict); aValueIter.More(); aValueIter.Next())
        {
            if (!aValueIter.Value().IsEmpty())
            {
                if (!anInfo.IsEmpty())
                {
                    anInfo += "\n";
                }
                anInfo += aValueIter.Key() + ": " + aValueIter.Value();
            }
        }
        Message::SendInfo (anInfo);
    }
    //! Compile shader program.
    void initGLShader(){
        //! GLSL language. This text is compiled and uploaded to the GPU processors.
        const char *vertexShaderSource =    "#version 330 core \n"
                                            "layout (location = 0) in vec3 aPos;  \n"
                                            "layout (location = 1) in vec3 aColor; \n"
                                            "layout (location = 2) in vec2 aTexCoord;  \n"
                                            "uniform mat4 myProjection; \n"
                                            "out vec3 ourColor; \n"
                                            "out vec2 TexCoord;  \n"
                                            "void main() \n"
                                            "{ \n"
                                            "    gl_Position = myProjection * vec4(aPos, 1.0); \n"
                                            "    ourColor = aColor; \n"
                                            "    TexCoord = vec2(aTexCoord.x, aTexCoord.y); \n"
                                            "} \n\0";

        const char *fragmentShaderSource =  "#version 330 core \n"
                                            "out vec4 FragColor; \n"
                                            "in vec3 ourColor; \n"
                                            "in vec2 TexCoord; \n"
                                            "// texture sampler \n"
                                            "uniform sampler2D texture1;  \n"
                                            "void main() \n"
                                            "{ \n"
                                            "    FragColor = texture(texture1, TexCoord);  \n"
                                            "} \n\0";

        //! build and compile our shader program
        uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        //! fragment shader
        uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        //! link shaders
        myShaderProgram = glCreateProgram();
        glAttachShader(myShaderProgram, vertexShader);
        glAttachShader(myShaderProgram, fragmentShader);
        glLinkProgram(myShaderProgram);
        //! check for linking errors
        glGetProgramiv(myShaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(myShaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    void initGLTexture(){
        //! Create a openGL texture from the opencascade Pixmap data, retrieved from myView->toPixmap.
        myTexture=SOIL_create_OGL_texture(myPixmap.Data(),myPixmap.Width(), myPixmap.Height(),4,1,0 );
    }
    //! Draw the texture.
    void drawGLTexture(){
        glEnable(GL_BLEND);
        //! glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC1_ALPHA);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //! glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC1_ALPHA);

        float w=Window()->Width();
        float h=Window()->Height();
        float x=0;
        float y=0;

        //! build and compile our shader zprogram
        float vertices[] = {  //! positions     //! colors            //! texture coords
                              x+w,  y,           0.0f, 1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
                              x+w,  y+h,         0.0f, 0.0f, 1.0f,     0.0f, 1.0f, 1.0f,
                              x,    y+h,         0.0f, 0.0f, 0.0f,     1.0f, 0.0f, 1.0f,
                              x,    y,           0.0f, 1.0f, 1.0f,     0.0f, 0.0f, 0.0f
                           };
        unsigned int indices[] = {
            0, 1, 3, //! first triangle
            1, 2, 3  //! second triangle
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        //! position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //! color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //! texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glUseProgram(myShaderProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, myTexture);

        glm::mat4 projection = glm::ortho(0.0f, Window()->Width(), 0.0f, Window()->Height());
        glUniformMatrix4fv(glGetUniformLocation(myShaderProgram, "myProjection"), 1, GL_FALSE, glm::value_ptr(projection));

        //! draw :
        //! render container
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glDisable(GL_BLEND);

        destroyGL();
    }

    void destroyGL(){
        //! optional: de-allocate all resources once they've outlived their purpose:
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        //! glDeleteTextures(1, &myTexture);
    }
};
#endif




























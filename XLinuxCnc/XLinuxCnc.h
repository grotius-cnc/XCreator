#ifndef XLINUXCNC_H
#define XLINUXCNC_H
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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <SOIL/SOIL.h>

#include "Python.h"
#include <ctype.h>

class XPython {
    public:
    XPython(){}

    void initPython(){
         Py_Initialize();

    }

    void runPython(){

     //   Py_Initialize();


//        PyObject * sys = PyImport_ImportModule("sys");
//        PyObject * path = PyObject_GetAttrString(sys, "/home/user/XCreator/XLinuxCnc/build");
//        PyList_Append(path, PyUnicode_FromString((char*) "."));

//        PyObject * ModuleString = PyUnicode_FromString((char*) "py_function");
//        PyObject * Module = PyImport_Import(ModuleString);
//       PyObject * Dict = PyModule_GetDict(Module);
//        PyObject * Func = PyDict_GetItemString(Dict, "python_test");
//        PyObject * Result = PyObject_CallObject(Func, NULL);

//        Py_Finalize();
    }

//    double call_func(PyObject *func, double x, double y)
//    {
//        PyObject *args;
//        PyObject *kwargs;
//        PyObject *result = 0;
//        double retval;

//        // Make sure we own the GIL
//        PyGILState_STATE state = PyGILState_Ensure();


//        // Verify that func is a proper callable
//        if (!PyCallable_Check(func))
//        {
//            fprintf(stderr, "call_func: expected a callable\n");
//        }
//    }

    void exitPython(){
        Py_Finalize();
    }

    private:
};

class XLinuxCnc : public XWidget {
public:
    //! Empty constructor. setWindow or parent afterwards. Do a init() afterwards.
    XLinuxCnc(){}
    //! The button has to be a member of a GLFWWindow. Mouse events, key events, are valid for the specific window. Otherwise a button press could be valid from other window.
    XLinuxCnc(XWindow *theWindow){
        this->setWindow(theWindow);
    }
    //! Empty destructor.
    ~XLinuxCnc(){}
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XOpencascade";
    }
    //! Set the size of this widget. Size also handles the mouse & key events.
    void setSize(XSize theSize){
        mySize->setSize(theSize);
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

private:
    XString *myString=new XString("XOpencascade");
    XSize *mySize=new XSize();

    unsigned int myTexture;
    unsigned int VBO, VAO, EBO;
    unsigned int myShaderProgram;

    //! If opencascade screen needs resize update, these values are used to compare.
    int OLD_SCR_WIDTH = 0;
    int OLD_SCR_HEIGHT = 0;

    //! Draw opencascade content to the glfw window.
    void drawGL()
    {
        //! Save the view as pixmap to be used as openGL texture later on.
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
        //! Create a openGL texture from a picture. This is a slow process.
        myTexture=SOIL_load_OGL_texture("skynet_cyberdyne.png",3,1,0);
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




























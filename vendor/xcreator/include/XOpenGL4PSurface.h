#ifndef XOPENGL4PSURFACE_H
#define XOPENGL4PSURFACE_H

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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <XWidget.h>
#include <XSize.h>
#include <XPoint.h>
#include <XMouse.h>
#include <XTriangle.h>
#include <XPip.h>

//! The XOpenGL4PSurface : OpenGL 4 Point Surface, is derived from the XRectangular class, but then may have a 4 point non-square surface.
//! Therefore the setSize is not used. To set the size of the 4 surface points, use the setSurface function.
//! A clockwise input is ok. When using a counterclockwise input, the back of the surface may be viewed.
//! The XOpenGLLine class is the class that primairy uses the XOpenGL4PSurface.
class XOpenGL4PSurface : public XWidget {
public:
    //! Empty destructor.
    XOpenGL4PSurface(){
        init();
    }
    //! Constructor setting the GLFWwindow pointer.
    XOpenGL4PSurface(XWindow *theWindow){
        this->setWindow(theWindow);
        init();
    }
    //! Init function.
    void init(){
        initGL();
    }
    //! Destructor.
    ~XOpenGL4PSurface(){
        destroyGL();
        glDeleteProgram(shaderProgram);
        delete this;
    }
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XOpenGL4PSurface";
    }
    //! Example : {{0,0,0},100,20}
    void setSize(XSize theSize){
        mySize->setSize(theSize);
    }
    //! Add a origin offset.
    void setSizeOffset(XPoint theValue){
        mySize->setSizeOffset(theValue);
    }
    //! Set the size pointing to a size.
    void setSizeWithPointer(XSize *theSize){
        mySize=theSize;
    }
    XSize Size(){
        return mySize->Size();
    }
    //! Return the size pointer, pointing to the size.
    XSize* SizePointer(){
        return mySize->SizePointer();
    }
    //! Return the size including relative offsets values.
    XSize SizeIncludeOffsets(){
        return mySize->SizeIncludeOffsets();
    }
    void setRelativeOriginOffset(XPoint thePoint){
        mySize->setRelativeOriginOffset(thePoint);
    }
    XPoint RelativeOriginOffset(){
        return mySize->RelativeOriginOffset().Point();
    }
    //! Set the relative size offset for relative width offset & relative height offset.
    void setRelativeSizeOffset(std::pair<float,float> theRelativeDimensionOffset){
        mySize->setRelativeSizeOffset(theRelativeDimensionOffset);
    }
    //! Return the relative size offset for relative width & relative height.
    std::pair<float,float> RelativeSizeOffset(){
        return mySize->RelativeSizeOffset();
    }
    //! Merge the relative origin offset into mySize and reset.
    void applyRelativeOriginOffset(){
        mySize->applyRelativeOriginOffset();
    }
    //! Merge the relative size offset into mySize and reset.
    void applyRelativeSizeOffset(){
        mySize->applyRelativeSizeOffset();
    }
    //! Set a color, limit the color to one color.
    void setColor(XColorType theColorType, XColor theColor){
        if(theColorType==XColorType::BackgroundColor){
             myColor->setColor(theColor);
        }
    }
    XColor Color(XColorType theColorType){
        if(theColorType==XColorType::BackgroundColor){
             return myColor->Color();
        }
        return {1.0,1.0,1.0,1.0};
    }
    //! Where x,y,z is 0 for draw with no offset.
    void draw(){
        drawGL();
    }
    //! Non virtual functions.
    void setColor(XColor theColor){
        myColor->setColor(theColor);
    }
    //! Set the surface points, input them clockwise cw.
    //! Input 4 points.
    void setSurface(std::vector<XPoint> thePointVec){
        myPointVec=thePointVec;
    }

private:
    std::string myName;
    XSize *mySize=new XSize();
    XColor //! Create colors and set standard values.
    *myColor=new XColor(0.1,0.1,0.1,0.9);

    std::vector<XPoint> myPointVec={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

    // OpenGL section.
    uint VBO, VAO, EBO;
    uint shaderProgram;

    void initGL(){
        // GLSL language. This text is compiled and uploaded to the GPU processors.
        const char *vertexShaderSource =    "#version 330 core\n"
                                            "layout (location = 0) in vec3 aPos; \n"
                                            "uniform mat4 myProjection; \n"
                                            "void main()\n"
                                            "{\n"
                                            "   gl_Position = myProjection* vec4(aPos.x, aPos.y, aPos.z, 1.0f); \n"
                                            "}\0";

        const char *fragmentShaderSource =  "#version 330 core\n"
                                            "out vec4 FragColor;\n"
                                            "uniform vec4 myColor;\n"
                                            "void main()\n"
                                            "{\n"
                                            "   FragColor = myColor;\n"
                                            "}\n\0";

        // build and compile our shader program
        // ------------------------------------
        // vertex shader
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
        // fragment shader
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
        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void drawGL(){
        glEnable(GL_BLEND);
        //! glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC1_ALPHA);
        //// glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC1_ALPHA);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //! The Window-Y is inverted because most widgets start on the top side of window and are build up from there.

        float vertices[] = {
            //! To integer resolution. For cad displays this could be avoided.
            //! UpperRight.
            myPointVec.at(1).X(), this->Window()->Height()-(myPointVec.at(1).Y()), myPointVec.at(1).Z(),
            //! LowerRight.
            myPointVec.at(2).X(), this->Window()->Height()-(myPointVec.at(2).Y()), myPointVec.at(2).Z(),
            //! LowerLeft.
            myPointVec.at(3).X(), this->Window()->Height()-(myPointVec.at(3).Y()), myPointVec.at(3).Z(),
            //! UpperLeft.
            myPointVec.at(0).X(), this->Window()->Height()-(myPointVec.at(0).Y()), myPointVec.at(0).Z()
        };
        uint indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // draw
        glUseProgram(shaderProgram);
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");

        glUniform4f(vertexColorLocation,
                    myColor->Red(),
                    myColor->Green(),
                    myColor->Blue(),
                    myColor->Alpha());

        // use window size float format with openGL.
        glm::mat4 projection = glm::ortho(0.0f, this->Window()->Width(), 0.0f, this->Window()->Height());
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "myProjection"), 1, GL_FALSE, glm::value_ptr(projection));
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // no need to unbind it every time
        glBindVertexArray(0);

        glDisable(GL_BLEND);

        destroyGL();
    }

    void destroyGL(){
        // optional: de-allocate all resources once they've outlived their purpose:
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
};
#endif 

























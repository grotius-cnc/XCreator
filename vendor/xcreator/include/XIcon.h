#ifndef XICON_H
#define XICON_H

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

#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <XColor.h>
#include <XMouse.h>
#include <XWindow.h>
#include <XRectangular.h>
#include <XWidget.h>
#include <XChar.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_TYPES_H
#include FT_OUTLINE_H
#include FT_RENDER_H

#include <learnopengl/includes/stb_image.h>

class XIcon : public XWidget {
public:
    //! Empty constuctor, set imagepath, set window, set size afterwards.
    XIcon(){}
    //! Use .png format, for .jpg format edit GL_RGBA to GL_RGB in this file.
    XIcon(std::string theImagePath, XSize theSize):myImagePath(theImagePath){
        mySize->setSize(theSize);
        init();
    }
    XIcon(XWindow *theWindow, std::string theImagePath, XSize theSize):myImagePath(theImagePath){
        this->setWindow(theWindow);
        mySize->setSize(theSize);
        init();
    }
    ~XIcon(){
        glDeleteProgram(myShaderProgram);
        std::cout<<"delete glshader program."<<std::endl;
    }
    void init(){
        initGL();
        myInit=1;
    }
    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XIcon";
    }
    //! Set the size of this widget. Size also handles the mouse & key events.
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
    //! Return the size.
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
    //! Set relative offset.
    void setRelativeOriginOffset(XPoint theRelativeOffset){
        mySize->setRelativeOriginOffset(theRelativeOffset);
    }
    //! Return relative offset.
    XPoint RelativeOriginOffset(){
        return mySize->RelativeOriginOffset();
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
    //! Draw content.
    void draw(){
        drawImage();
    }
    //! Non virtual functions.
    void setIcon(std::string thePath){
        myImagePath=thePath;
        init();
    }
    bool hasIcon(){
        return myInit;
    }
private:
    bool myInit=0;
    unsigned int VBO, VAO, EBO;
    uint myShaderProgram;
    XSize *mySize=new XSize();
    std::string myImagePath;
    unsigned int myTexture;

    unsigned char *data;
    int width, height, nrChannels;

    void initGL(){
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
        //! Vertex shader
        uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        //! Check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        //! Fragment shader
        uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        //! Check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        //! Link shaders
        myShaderProgram = glCreateProgram();
        glAttachShader(myShaderProgram, vertexShader);
        glAttachShader(myShaderProgram, fragmentShader);
        glLinkProgram(myShaderProgram);
        //! Check for linking errors
        glGetProgramiv(myShaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(myShaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        //! load and create a texture
        glGenTextures(1, &myTexture);
        glBindTexture(GL_TEXTURE_2D, myTexture); //! All upcoming GL_TEXTURE_2D operations now have effect on this texture object
        //! set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//! Set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //! set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //! The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        //! unsigned char *data = stbi_load(myImagePath.c_str(), &width, &height, &nrChannels, 0);
        data = stbi_load(myImagePath.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
    //! Create vertex & fragment shader programs that are used by the GPU when compiled. Then load the shader program.
    void drawImage(){
        glEnable(GL_BLEND);
        //! glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC1_ALPHA);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //! glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC1_ALPHA);

        float w=mySize->Width();
        float h=mySize->Height();
        float x=mySize->Origin().X()+mySize->RelativeOriginOffset().X();
        float y=mySize->Origin().Y()+mySize->RelativeOriginOffset().Y();
        float z=mySize->Origin().Z()+mySize->RelativeOriginOffset().Z();
        float wh=Window()->Height();

        float vertices[] = { //! Icon flipped.
                             //! positions            // colors           // texture coords
                             x+w,  wh-y,     z,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, //! top right
                             x+w,  wh-(y+h), z,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, //! bottom right
                             x,    wh-(y+h), z,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, //! bottom left
                             x,    wh-y,     z,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  //! top left
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
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

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

#endif // XICON_H

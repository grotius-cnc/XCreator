#ifndef XTEXTURESTREAM_H
#define XTEXTURESTREAM_H

#include <iostream>
#include <vector>
#include <XColor.h>
#include <XMouse.h>
#include <XWindow.h>
#include <XRectangular.h>
#include <XWidget.h>
#include <XChar.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <XPixmap.h>

#include <../vendor/lodepng/lodepng.h>

class XTextureStream : public XWidget {
public:
    //! Use .png format, for .jpg format edit GL_RGBA to GL_RGB
    XTextureStream(XWindow *theWindow){
        setWindow(theWindow);
    }
    ~ XTextureStream(){
        destroyGL();
        glDeleteProgram(myShaderProgram);
    }

    void draw(){
        if(!myInit){
            initGL();
            myInit=1;
        }
        drawImage(mySize);
    }
    void setSize(XSize theSize){
        mySize->setSize(theSize);
    }
    //! Set the size of the border.
    void setBorderSize(float theSize){
        myBorderSize=theSize;
    }
    //! Load texture from XPixmap.
    void setTexture(XPixmap thePixmap){
        myPixmap=thePixmap;
    }
    //! Load texture from file.
    void setTextureFile(std::string theTexturePath, bool theFlipVertical){
        myFlipVertical=theFlipVertical;
        //! decode
        unsigned error = lodepng::decode(myPixmap.pixels, myPixmap.width, myPixmap.height, theTexturePath);
        //! if there's an error, display it
        if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }

private:
    bool myInit=0;
    unsigned int VBO, VAO, EBO;
    uint myShaderProgram;
    XSize *mySize=new XSize();
    float myBorderSize=0;
    unsigned int myTexture;
    //! Image data.
    XPixmap myPixmap;
    bool myFlipVertical=false;

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
        //! ------------------------------------
        //! vertex shader
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

        //! Re usable texture id.
        glGenTextures(1, &myTexture);
    }
    //! Generate texture, above the myTexture is initialized just once to make it re usable.
    void generateTexture(){
        //! load and create a texture
        glBindTexture(GL_TEXTURE_2D, myTexture); //! all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        //! set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//! set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //! set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, myPixmap.width, myPixmap.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &myPixmap.pixels[0]);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    //! Create vertex & fragment shader programs that are used by the GPU when compiled. Then load the shader program.
    void drawImage(XSize *theSize){
        XSize myBorder;
        myBorder.setSize(theSize->MarginSize(myBorderSize));
        float w= myBorder.Width();
        float h= myBorder.Height();
        float x= myBorder.Origin().X();
        float y= myBorder.Origin().Y();
        float wh=this->Window()->Height();

        float verticesFlipY[] = { //! Icon flipped.
                                  //! positions        //! colors          //! texture coords
                                  x+w,  wh-y,     0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, //! top right
                                  x+w,  wh-(y+h), 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, //! bottom right
                                  x,    wh-(y+h), 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, //! bottom left
                                  x,    wh-y,     0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  //! top left
                                };

        float vertices[] = { //! Icon
                             //! positions        //! colors          //! texture coords
                             x+w,  y,     0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, //! top right
                             x+w,  (y+h), 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, //! bottom right
                             x,    (y+h), 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, //! bottom left
                             x,    y,     0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  //! top left
                           };

        unsigned int indices[] = {
            0, 1, 3, //! first triangle
            1, 2, 3  //! second triangle
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);

        if(!myFlipVertical){
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        } else {
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(verticesFlipY), verticesFlipY, GL_STATIC_DRAW);
        }

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

        generateTexture();

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

        destroyGL();
    }

    void destroyGL(){
        //! optional: de-allocate all resources once they've outlived their purpose:
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
};

#endif

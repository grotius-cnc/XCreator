#ifndef XTEXT_H
#define XTEXT_H

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

#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <XColor.h>
#include <XMouse.h>
#include <XWindow.h>
#include <XRectangular.h>
#include <XChar.h>
#include <XScissor.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_TYPES_H
#include FT_OUTLINE_H
#include FT_RENDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Holds all state information relevant to a character as loaded using FreeType
class XFontCharacter {
public:
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
    uint lineHeight;
};

class XText : public XWidget {
public:

    XText(){
        myFontName="fonts/SourceCodePro-Regular.ttf";
        myFontSize=13;
        myVerticalFontSpace=2;
        init();
    }


    XText(XWindow *theWindow){
        this->setWindow(theWindow);
        myFontName="fonts/SourceCodePro-Regular.ttf";
        myFontSize=13;
        myVerticalFontSpace=2;
        init();
    }

    XText(XWindow *theWindow, uint theFontSize, uint theVerticalFontSpace, std::string theFontName){
        this->setWindow(theWindow);
        myFontName=theFontName;
        myFontSize=theFontSize;
        myVerticalFontSpace=theVerticalFontSpace;
        init();
    }

    ~XText(){
        glDeleteProgram(myShaderProgram);
    }
    void init(){
        if(!loadFont(myFontName,myFontSize)){ std::cout<<"XText loadfont failed."<<std::endl;}
        if(!initGL()){std::cout<<"XText initGL failed."<<std::endl;}
        if(!loadVaoVbo()){std::cout<<"XText loadVaoVbo failed."<<std::endl;};
    }

    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XText";
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

    //! Non virtual functions.
    void setFontName(std::string theFontName){
        myFontName=theFontName;
         if(!loadFont(myFontName,myFontSize)){ std::cout<<"XText loadfont failed."<<std::endl;}
    }
    void setFontSize(float theFontSize){
        myFontSize=theFontSize;
        if(!loadFont(myFontName,myFontSize)){ std::cout<<"XText loadfont failed."<<std::endl;}
    }
    void setVerticalFontSpace(float theVerticalFontSpace){
        myVerticalFontSpace=theVerticalFontSpace;
    }
    // draw a text right away.
    void drawText(XString theText, uint theCharStartNr, uint theCharEndNr, float scrollX, float scrollY){
        if(!RenderText(theText, theCharStartNr, theCharEndNr, mySize->Origin().X()+scrollX, mySize->Origin().Y()+scrollY, 1.0f)){std::cout<<"XText rendertext error."<<std::endl;}
    }
    void setMemoryText(XString theText){
        myMemoryText.setString(theText);
    }
    uint MemoryTextSize(){
        return myMemoryText.size();
    }
    // draw a text right away.
   //void drawMemoryText(uint theCharStartNr, uint theCharEndNr, float scrollX, float scrollY, bool useGLScissor){
   //     if(!RenderText(myMemoryText, theCharStartNr, theCharEndNr, mySize->Origin().X()+scrollX, mySize->Origin().Y()+scrollY, 1.0f, useGLScissor)){std::cout<<"XText rendertext error."<<std::endl;}
   // }

    // Get the string width to automate button width size.
    float StringWidth(std::string text){
        // iterate through all characters
        float theWidth=0;
        std::string::const_iterator c;
         XFontCharacter ch;
        for (c = text.begin(); c != text.end(); c++)
        {
            ch = XFontCharacters[*c];
            theWidth+=ch.Advance/64;
        }
        //! One extra.
        theWidth+=ch.Advance/64;
        return theWidth;
    }
    // Get a character place width, called : advance.
    float CharacterPixelWidth(char theCharacter){
        XFontCharacter ch = XFontCharacters[theCharacter];
        return ch.Advance/64; /*ToPixels*/
    }
    float FontSize(){
        return myFontSize;
    }
    std::string FontName(){
        return myFontName;
    }

private:
    std::string myName;
    XSize *mySize=new XSize();
    std::string myFontName="fonts/SourceCodePro-Regular.ttf";
    uint myFontSize=0, myVerticalFontSpace=0;
    std::map<GLchar, XFontCharacter> XFontCharacters;
    unsigned int VAO, VBO;
    uint myShaderProgram;
    std::vector<glm::fvec4> theGlmColorVec;
    XString myMemoryText;
    unsigned int myTexture;

    bool loadVaoVbo(){
        // configure VAO/VBO for texture quads
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        return 1;
    }

    // Create vertex & fragment shader programs that are used by the GPU when compiled. Then load the shader program.
    bool initGL(){
        // GLSL language. This text is compiled and uploaded to the GPU processors.
        const char *vertexShaderSource =    "#version 330 core \n"
                                            "layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex> \n"
                                            "out vec2 TexCoords; \n"
                                            "uniform mat4 projection; \n"
                                            "void main()\n"
                                            "{\n"
                                            "   gl_Position = projection * vec4(vertex.x, vertex.y, vertex.z, 1.0); \n"
                                            "   TexCoords = vertex.zw; \n"
                                            "}\0";

        const char *fragmentShaderSource =  "#version 330 core \n"
                                            "in vec2 TexCoords; \n"
                                            "out vec4 color; \n"
                                            "uniform sampler2D text; \n"
                                            "uniform vec4 textColor; \n"
                                            "void main()\n"
                                            "{\n"
                                            "   vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r); \n"
                                            "   color = textColor * sampled; \n"
                                            "}\n\0";

        // build and compile our shader program
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
            std::cout << "XText ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            return 0;
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
            std::cout << "XText ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            return 0;
        }
        // link shaders
        myShaderProgram = glCreateProgram();
        glAttachShader(myShaderProgram, vertexShader);
        glAttachShader(myShaderProgram, fragmentShader);
        glLinkProgram(myShaderProgram);
        // check for linking errors
        glGetProgramiv(myShaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(myShaderProgram, 512, NULL, infoLog);
            std::cout<<"XText ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infoLog<<std::endl;
            return 0;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 1;
    }

    bool loadFont(std::string theFontName, float theFontSize){
        XFontCharacters.clear();
        // FreeType
        FT_Library ft;
        // All functions return a value different than 0 whenever an error occurred
        if (FT_Init_FreeType(&ft))
        {
            std::cout<<"XText ERROR::FREETYPE: Could not init FreeType Library"<<std::endl;
            return -1;
        }

        // find path to font
        if (theFontName.empty())
        {
            std::cout<<"XText ERROR::FREETYPE: Failed to load font_name"<<std::endl;
            return -1;
        }

        // load font as face
        FT_Face face;
        if (FT_New_Face(ft, theFontName.c_str(), 0, &face)) {
            std::cout<<"XText ERROR::FREETYPE: Failed to load font"<<std::endl;
            return -1;
        }
        else {
            // set size to load glyphs as
            FT_Set_Pixel_Sizes(face, 0, theFontSize);

            // disable byte-alignment restriction
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            // load first 128 characters of ASCII set
            for (unsigned char c = 0; c < 128; c++)
            {
                // Load character glyph
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                {
                    std::cout<<"XText ERROR::FREETYTPE: Failed to load Glyph"<<std::endl;
                    continue;
                }

                glGenTextures(1, &myTexture);
                glBindTexture(GL_TEXTURE_2D, myTexture);
                glTexImage2D(
                            GL_TEXTURE_2D,
                            0,
                            GL_RED,
                            face->glyph->bitmap.width,
                            face->glyph->bitmap.rows,
                            0,
                            GL_RED,
                            GL_UNSIGNED_BYTE,
                            face->glyph->bitmap.buffer
                            );
                // set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                // now store character for later use
                XFontCharacter character = {
                    myTexture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x),
                    face->glyph->bitmap.rows
                };
                XFontCharacters.insert(std::pair<char, XFontCharacter>(c, character));
            }
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        // destroy FreeType once we're finished
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        return 1;
    }

    // Render text.
    bool RenderText(XString theCharText, uint theCharStartNr, uint theCharEndNr, float x, float y, float scale)
    {
        //! Used by editing mode.
        x+=mySize->RelativeOriginOffset().X();
        y+=mySize->RelativeOriginOffset().Y();

        // Get the start of line x value.
        float reset=x;
        // Fix the first line origin.
        y+=myFontSize;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // activate corresponding render state
        glm::mat4 projection = glm::ortho(0.0f, Window()->Width(), 0.0f, Window()->Height());
        glUseProgram(myShaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(myShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        //glUniform4f(glGetUniformLocation(myShaderProgram, "textColor"), color.r, color.g, color.b, color.a);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        for (uint i=0; i<theCharText.size(); i++)
        {
            if(i>=theCharStartNr && i<=theCharEndNr){

                XFontCharacter ch = XFontCharacters[theCharText.at(i).Char()];
                glUniform4f(glGetUniformLocation(myShaderProgram, "textColor"), theCharText.at(i).Color().Red(), theCharText.at(i).Color().Green(), theCharText.at(i).Color().Blue(), theCharText.at(i).Color().Alpha());
                //std::cout<<"r:"<<theCharText.at(i).Color().Red()<<std::endl;

                //else
                // if (theCharText.at(i).theChar=='\0'){
                // Do nothing.. We hate printing Null characters.
                /* // To show if there are any :
                            for(uint i=0; i<text.size(); i++){
                                std::cout<<"text:"<<text.at(i)<<std::endl;
                                if(text.at(i)=='\0'){
                                   std::cout<<"null found at i"<<i<<std::endl;
                                }
                            }*/

                if(theCharText.at(i).Char()=='\n'){
                    //skip.
                    y+=myFontSize+myVerticalFontSpace;
                    x=reset;
                }  else {

                    float xpos = x + ch.Bearing.x * scale;
                    float ypos = (Window()->Height()-y) - (ch.Size.y - ch.Bearing.y) * scale;

                    float w = ch.Size.x * scale;
                    float h = ch.Size.y * scale;
                    // update VBO for each character

                    // Converte to integer and back to float. To avoid non-sharp text.
                    int xposi=xpos;
                    int yposi=ypos;
                    int hi=h;
                    int wi=w;
                    float xposf=xposi;
                    float yposf=yposi;
                    float hf=hi;
                    float wf=wi;

                    float vertices[6][4] = {
                        { xposf,     yposf + hf,   0.0f, 0.0f },
                        { xposf,     yposf,       0.0f, 1.0f },
                        { xposf + wf, yposf,       1.0f, 1.0f },

                        { xposf,     yposf + hf,   0.0f, 0.0f },
                        { xposf + wf, yposf,       1.0f, 1.0f },
                        { xposf + wf, yposf + hf,   1.0f, 0.0f }
                    };
                    // render glyph texture over quad
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
                    // update content of VBO memory
                    glBindBuffer(GL_ARRAY_BUFFER, VBO);
                    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

                    glBindBuffer(GL_ARRAY_BUFFER, 0);
                    // render quad
                    glDrawArrays(GL_TRIANGLES, 0, 6);
                    // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
                    x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
                }
            }

        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glDisable(GL_BLEND);

        return 1;
    }
};

#endif // XTEXT_H

#ifndef XTRIANGLE_H
#define XTRIANGLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <XPoint.h>
#include <XMouse.h>
#include <XWindow.h>

class XTriangle {
public:
    // The GLfront face of the triangle is always draw ccw. The GLBack is cw.
    XTriangle(XWindow *theWindow, XPoint *theA, XPoint *theB, XPoint *theC, XColor *theColor):myA(theA),myB(theB),myC(theC),myColor(theColor){
        myWindow=theWindow;
        initGL();
    }
    ~XTriangle(){
        destroyGL();
        glDeleteProgram(shaderProgram);
        delete this;
    }
    XPoint A(){
        return *myA;
    }
    float Ax(){
        return myA->X();
    }
    float Ay(){
        return myA->Y();
    }
    float Az(){
        return  myA->Z();
    }
    XPoint B(){
        return *myB;
    }
    float Bx(){
        return myB->X();
    }
    float By(){
        return myB->Y();
    }
    float Bz(){
        return  myB->Z();
    }
    XPoint C(){
        return *myC;
    }
    float Cx(){
        return myC->X();
    }
    float Cy(){
        return myC->Y();
    }
    float Cz(){
        return  myC->Z();
    }
    void setAXYZ(float x, float y, float z){
        myA->setXYZ(x,y,z);
    }
    void setBXYZ(float x, float y, float z){
        myB->setXYZ(x,y,z);
    }
    void setCXYZ(float x, float y, float z){
        myC->setXYZ(x,y,z);
    }
    void setPoints(XPoint a, XPoint b, XPoint c){
        myA->setPoint(a);
        myB->setPoint(b);
        myC->setPoint(c);
    }
    void setColor(XColor *theValue){
        myColor=theValue;
    }
    bool isCw(){
        if(area()>0){
            return  true;
        }
        return 0;
    }
    bool isCcw(){
        if(area()<0){
            return  true;
        }
        return 0;
    }
    // Area in mm2.
    float area(){
        float sumX=0,sumY=0,area=0;

        sumX+=myA->X()*myB->Y();
        sumX+=myB->X()*myC->Y();
        sumX+=myC->X()*myA->Y();

        sumY+=myA->Y()*myB->X();
        sumY+=myB->Y()*myC->X();
        sumY+=myC->Y()*myA->X();

        area=(sumX-sumY)/2;
        return area;
    }
    // Centroid or center of mass.
    XPoint gravityPoint(){
        XPoint gravity;
        gravity.setX((myA->X()+myB->X()+myC->X())/3);
        gravity.setY((myA->Y()+myB->Y()+myC->Y())/3);
        gravity.setZ((myA->Z()+myB->Z()+myC->Z())/3);
        return gravity;
    }
    bool isPressed(){
        if(Mouse.isPressedLeftButton() && isMouseOnShape()){
            myMousePressOneShot++;
            if(myMousePressOneShot==1){
                myMouseSnapShot->setPoint(*Mouse.Position());
                return 1;
            }
        }
        if(isReleased()){
            myMousePressOneShot=0;
        }
        return 0;
    }
    bool isReleased(){
        if(!Mouse.isPressedLeftButton()){
            myMousePressOneShot=0;
            return 1;
        }
        return 0;
    }
    bool isHovered(){
        if(isMouseOnShape()){
            return 1;
        }
        return 0;
    }
    bool isDragged(){
        if(!isReleased() && myMouseSnapShot->Dist(Mouse.Position())>1){
            return 1;
        }
        return 0;
    }
    XPoint mouseSnapShot(){
       return *myMouseSnapShot;
    }
    void highLight(bool status){
        myHighLightStatus=status;
    }

    // OpenGL
    void init(){
        initGL();
    }
    void draw(){
        drawGL();
    }
private:
    XWindow *myWindow;
    XPoint *myA=new XPoint(), *myB=new XPoint(), *myC=new XPoint();
    XColor *myColor=new XColor();
    XColor *myHighLightColor=new XColor(0.1,0.1,0.1,0.1); // This is a colorvalue that will be added to the myColor value when the widget is hovered and myHighLightStatus=true.
    XPoint *myMouseSnapShot=new XPoint();
    int myMousePressOneShot=0;
    bool myHighLightStatus=false;

    bool isMouseOnShape(){

        int result=Pip(*Mouse.Position(),{myA,myB,myC});
        if(result){
            return 1;
        }

        return 0;
    }

    // Point in polygon algoritme.
    int Pip(XPoint thePoint, std::vector<XPoint*> thePointVec){
        int n = thePointVec.size();
        int i, j, c = 0;
        for (i = 0, j = n-1; i < n; j = i++) {
            if ( ((thePointVec.at(i)->Y()>thePoint.Y()) != (thePointVec.at(j)->Y()>thePoint.Y())) && (thePoint.X() < (thePointVec.at(j)->X()-thePointVec.at(i)->X()) * (thePoint.Y()-thePointVec.at(i)->Y()) / (thePointVec.at(j)->Y()-thePointVec.at(i)->Y()) + thePointVec.at(i)->X()) ){
                c = !c;
            }
        }
        return c;
    }

    // OpenGL section.
    uint VBO, VAO;
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
        //glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC1_ALPHA);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC1_ALPHA);
        // XWindow.height();
        // The Window-Y is inverted because most widgets start on the top side of window and are build up from there.
        float vertices[] = {
            // ensure float format with openGL.
            A().X(),myWindow->Height()-A().Y(),A().Z(),
            B().X(),myWindow->Height()-B().Y(),B().Z(),
            C().X(),myWindow->Height()-C().Y(),C().Z()
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // draw our first triangle
        glUseProgram(shaderProgram);

        int vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");
        if(!myHighLightStatus){
             glUniform4f(vertexColorLocation, myColor->Red(), myColor->Green(), myColor->Blue(), myColor->Alpha());
        } else {
            glUniform4f(vertexColorLocation, myColor->Red()+myHighLightColor->Red(), myColor->Green()+myHighLightColor->Green(), myColor->Blue()+myHighLightColor->Blue(), myColor->Alpha()+myHighLightColor->Alpha());
        }


        // use window size float format with openGL.
        glm::mat4 projection = glm::ortho(0.0f, myWindow->Width(), 0.0f, myWindow->Height());
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "myProjection"), 1, GL_FALSE, glm::value_ptr(projection));
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // no need to unbind it every time
        glBindVertexArray(0);

        glDisable(GL_BLEND);
        destroyGL();
    }

    void destroyGL(){
        // optional: de-allocate all resources once they've outlived their purpose:
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

};

#endif // XTRIANGLE_H









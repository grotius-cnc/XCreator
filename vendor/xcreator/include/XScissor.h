#ifndef XSCISSOR_H
#define XSCISSOR_H

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

//! OpenGl Scissor, for limiting display output to a certain rectangular.
//! When performing nested scissor operations, the nested scissor operations have to be restored to
//! previous state, otherwise scissor output will be overwritten by the previous one.
//!
//! * Once the scissor is enabled by startScissor, it is enabled for all the windows, cq dialogs.
class XScissor {
public:
    //! Empty constructor.
    XScissor(){}
    //! Constructor setting the GLFWwindow pointer to get the size of the glfw dialog.
    XScissor(XWindow *theWindow):myWindow(theWindow){}
    //! Start the scissor. Save previous state.
    void saveState(){
        //! Save current state.
        glGetIntegerv(GL_SCISSOR_BOX, myRect);
        // std::cout<<"saving scissor size to x:"<<myRect[0]<<" y:"<<myRect[1]<<" w:"<<myRect[2]<<" h:"<<myRect[3]<<std::endl;
    }
    //! Stop the scissor, restore to previous state if there was one.
    void restoreState(){
        //! Restore to previous scissor state.
        // std::cout<<"restoring scissor size to x:"<<myRect[0]<<" y:"<<myRect[1]<<" w:"<<myRect[2]<<" h:"<<myRect[3]<<std::endl;
        glScissor(myRect[0], myRect[1], myRect[2], myRect[3]);
    }
    //! A normal scissor. Is not usable for nested scissor operations.
    void setScissorSize(XSize theSize){
        mySize->setSize(theSize);
        //! Set the size to display.
        //! Convert coordinates from our origin wich is top left of screen to coordinate lower left of screen.
        int x=int(mySize->Size().Origin().X());
        int y=int(myWindow->Height()-(mySize->Size().Origin().Y()+mySize->Size().Height()));
        int w=int(mySize->Width());
        int h=int(mySize->Height());

        //! Enable the scissor.
        //glEnable(GL_SCISSOR_TEST);

        //! Set the scissor size.
        glScissor(x,  // Lowerleft.
                  y,  // Lowerleft.
                  w,  // -..= remove from right side.
                  h); // -..= remove from top.

        // std::cout<<"Set scissor size x:"<<x<<" y:"<<y<<" w:"<<w<<" h:"<<h<<std::endl;
    }
    //! Create a union from 2 intersecting rectangulars.
    bool setScissorUnion(XSize theParentSize, XSize theChildSize){
        //! First rectangular.
        int x1=int(theParentSize.Origin().X());
        int y1=int(theParentSize.Origin().Y());
        //! lower right.
        int x2=int(theParentSize.Origin().X()+theParentSize.Width());
        int y2=int(theParentSize.Origin().Y()+theParentSize.Height());

        //! Second rectangular.
        int x3=int(theChildSize.Origin().X());
        int y3=int(theChildSize.Origin().Y());
        //! Lower right.
        int x4=int(theChildSize.Origin().X()+theChildSize.Width());
        int y4=int(theChildSize.Origin().Y()+theChildSize.Height());

        //! gives origin point
        //! of intersection rectangle
        int x5 = std::max(x1, x3);
        int y5 = std::max(y1, y3);

        //! gives lower-right point
        //! of intersection rectangle
        int x6 = std::min(x2, x4);
        int y6 = std::min(y2, y4);

        //! no intersection
        if (x5 > x6 || y5 > y6) {
             //! std::cout << "No intersection, setting parent size.";
             setScissorSize(theParentSize.Size());
            return 0;
        }
        //! std::cout<<"resultSize Origin x:"<<x5<<" y:"<<y5<<" w:"<<x6-x5<<" h:"<<y6-y5<<std::endl;
        setScissorSize({{float(x5),float(y5),0},float(x6-x5),float(y6-y5)});
        return 1;
    }
    //! Is the size, can be the normal setted size or the union setted size.
    XSize ScissorSize(){
        return mySize->Size();
    }
    //! At Initialisation of window cq dialog, enable. Disable when closing window or dialog.
    void enableScissor(bool theStatus){
        if(theStatus){
            glEnable(GL_SCISSOR_TEST);
        } else {
            glDisable(GL_SCISSOR_TEST);
        }
    }
    //! Set the pointer to the window afterwards when using a empty constructor.
    void setWindow(XWindow *theWindow){
        myWindow=theWindow;
    }
    //! Return state.
    bool Enabled(){
        return glIsEnabled(GL_SCISSOR_TEST);
    }
    //! Print the current scissor size.
    void printCurrentScissorSize(){
        int aRect[4];
        glGetIntegerv(GL_SCISSOR_BOX, aRect);
        std::cout<<"scissor size x:"<<aRect[0]<<" y:"<<aRect[1]<<" w:"<<aRect[2]<<" h:"<<aRect[3]<<std::endl;
    }
private:
    int myRect[4];
    XWindow *myWindow;
    XSize *mySize=new XSize();
};

#endif // XSCISSOR_H


























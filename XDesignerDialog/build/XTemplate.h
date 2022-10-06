#ifndef XTEMPLATE_H
#define XTEMPLATE_H

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


#include <XFrame.h>
#include <XButton.h>
/*
Implementation example.
   Init stage:
       myTemplate=new XTemplate(Window());
       myTemplate->setName("Template");
       myTemplate->setSize({{5,25,0},800,800});
       myTemplate->init();
   Program loop:
       myTemplate->draw();
   Private section:
       XTemplate *myTemplate;
*/

class XTemplate : public XWidget { 
public:
	XTemplate(XWindow *theWindow){
		this->setWindow(theWindow);
		setScissorWindow(theWindow);
	}
	~XTemplate(){}

    	//! Virtual functions.
    	//! Type of this widget.
    	std::string Type(){
        	return "XTemplate";
    	}
    	//! Set the size of this widget. Size also handles the mouse & key events.
    	void setSize(XSize theSize){
        	mySize->setSize(theSize);
    	}
    	//! Add a origin offset.
    		void setSizeOffset(XPoint theValue){
        mySize->setSizeOffset(theValue);
    	}
    	//! Return the size.
    	XSize Size(){
        	return mySize->Size();
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

	void init(){
		DesignerFrame=new XFrame(Window());
		DesignerFrame->setSize({{10,110,0},1290,244});
		DesignerFrame->setName("DesignerFrame");
		DesignerFrame->setString("DesignerFrame");

		Button_0=new XButton(Window());
		Button_0->setSize({{164,165,0},200,50});
		Button_0->setName("Button_0");
		Button_0->setString("Button_0");

		DesignerFrame->addWidget(Button_0);
		addWidget(DesignerFrame);
	}
	void draw(){
		//! Save the current scissor size to be restored at end of this function.
		saveScissorState();
		//! Set the scissor union size.
		setScissorUnion(ParentScissorSize(),mySize->Size());
		DesignerFrame->setSize(mySize->Size());
		Button_0->setSize(DesignerFrame->Size());
		drawWidgetVec();
		//! Restore the scissor size.
		restoreScissorState();
	}
private:
	std::string myName;
	XSize *mySize=new XSize();
	XFrame *DesignerFrame;
	XButton *Button_0;
};
#endif 

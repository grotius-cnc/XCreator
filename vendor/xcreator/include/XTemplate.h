#ifndef XTEMPLATE_H
#define XTEMPLATE_H

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

#include <XFrame.h>
#include <XHorizontalSplitterLayout.h>
#include <XTreeView.h>
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
		DesignerFrame->setSize({{10,110,0},990,700});
		DesignerFrame->setName("DesignerFrame");
		DesignerFrame->setString("DesignerFrame");

		HorizontalSplitterLayout_0=new XHorizontalSplitterLayout(Window());
		HorizontalSplitterLayout_0->setSize({{129,155,0},500,508});
		HorizontalSplitterLayout_0->setName("HorizontalSplitterLayout_0");
		HorizontalSplitterLayout_0->setString("HorizontalSplitterLayout_0");

		TreeView_1=new XTreeView(Window());
		TreeView_1->setSize({{131,157,0},247.5,504});
		TreeView_1->setName("TreeView_1");
		TreeView_1->setString("TreeView_1");

		TreeView_2=new XTreeView(Window());
		TreeView_2->setSize({{383.5,157,0},243.5,504});
		TreeView_2->setName("TreeView_2");
		TreeView_2->setString("TreeView_2");

		Button_3=new XButton(Window());
		Button_3->setSize({{422,668,0},127,37});
		Button_3->setName("Button_3");
		Button_3->setString("Button_3");

		Button_4=new XButton(Window());
		Button_4->setSize({{552,668,0},80,38});
		Button_4->setName("Button_4");
		Button_4->setString("Button_4");

		DesignerFrame->addWidget(HorizontalSplitterLayout_0);
		DesignerFrame->addWidget(Button_3);
		DesignerFrame->addWidget(Button_4);
		HorizontalSplitterLayout_0->addWidget(TreeView_1);
		HorizontalSplitterLayout_0->addWidget(TreeView_2);
		addWidget(DesignerFrame);
	}
	void draw(){
		//! Save the current scissor size to be restored at end of this function.
		saveScissorState();
		//! Set the scissor union size.
		setScissorUnion(ParentScissorSize(),mySize->Size());
		DesignerFrame->setSize(mySize->Size());
		HorizontalSplitterLayout_0->setSize(DesignerFrame->Size());
		drawWidgetVec();
		//! Restore the scissor size.
		restoreScissorState();
	}
private:
	std::string myName;
	XSize *mySize=new XSize();
	XFrame *DesignerFrame;
	XHorizontalSplitterLayout *HorizontalSplitterLayout_0;
	XTreeView *TreeView_1;
	XTreeView *TreeView_2;
	XButton *Button_3;
	XButton *Button_4;
};
#endif 

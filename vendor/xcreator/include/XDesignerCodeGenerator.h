#ifndef XDESIGNERCODEGENERATOR_H
#define XDESIGNERCODEGENERATOR_H

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
#include <XButton.h>
#include <XFrame.h>
#include <XTextEdit.h>
#include <XLineEdit.h>
#include <XFile.h>

#include <sstream>
#include <unistd.h> // getwcd.
#include <filesystem>

class XDesignerCodeGenerator {
public:
    //* Convert a XDesigner layout to code and write this to a textfile with .h extension to include in a XCreator project.
    XDesignerCodeGenerator(){}
    ~XDesignerCodeGenerator(){}

    // Possible process steps.
    // 1. Create all widgets stand alone.
    //      function (aWidget..), create a vector of text blocks?
    // 2. Add widget structure in the end of the file...
    //      ..->addWidget( ..) to create the node structure from XWidgetView data.
    // 3. Create events.

    void processCode(XWidget *theWidget, std::string theLicenceTextPath, std::string theVirtualFunctionTemplateTextPath){

        if(theWidget->WidgetVec().size()==0){
            std::cout<<"no items in the designer.. Abort."<<std::endl;
            return;
        }

        std::vector<XWidget*> theWidgetList=XWidgetView().WidgetList(theWidget);
        std::stringstream ss;
        char ACO='"';
        //! Short notation for parent.
        XWidget *Pa=theWidget;

        //! Process header ifdef.
        ss<<"#ifndef XTEMPLATE_H"; ss<<"\n";
        ss<<"#define XTEMPLATE_H"; ss<<"\n";
        ss<<"\n";

        //! Add licence text from LicenceText.txt
        //! Get current working directory.
        /* Now using std::filesystem::current_path() instead of :
        char cwd[256];
        getcwd(cwd,sizeof (cwd));
        std::string thePath, theDir;
        for(auto entry : std::filesystem::directory_iterator(cwd)){
            theDir=entry.path().parent_path().parent_path().c_str();
            //! Hidden file.
            thePath=theDir+"/vendor/xcreator/.LicenceText.txt";
            break;
        }
        */
        ss<<XFile().readTextFile(theLicenceTextPath);

        //! Process includes, filter out dubplicates.
        std::vector<std::string> includeVec;
        for(uint i=0; i<theWidgetList.size(); i++){
            // Find duplicate.
            bool duplicate=0;
            for(uint j=0; j<includeVec.size(); j++){
                if(includeVec.at(j)==theWidgetList.at(i)->Type()){
                    duplicate=1;
                    break;
                }
            }
            if(!duplicate){
                includeVec.push_back(theWidgetList.at(i)->Type());
            }
        }
        for(uint i=0; i<includeVec.size(); i++){
            //! Include the XFrame instead of the XDesignerFrame during code processing.
            if(includeVec.at(i)=="XDesignerFrame"){
                includeVec.at(i)="XFrame";
            }
            ss<<"#include <"<<includeVec.at(i)<<".h>"<<"\n";
        }

        //! Process comments.
        ss<<"/*"; ss<<"\n";
        ss<<"Implementation example."; ss<<"\n";
        ss<<"   Init stage:"; ss<<"\n";
        ss<<"       myTemplate=new XTemplate(Window());"; ss<<"\n";
        ss<<"       myTemplate->setName("; ss<<ACO; ss<<"Template"; ss<<ACO; ss<<");"; ss<<"\n";
        ss<<"       myTemplate->setSize({{5,25,0},800,800});"; ss<<"\n";
        ss<<"       myTemplate->init();"; ss<<"\n";
        ss<<"   Program loop:"; ss<<"\n";
        ss<<"       myTemplate->draw();"; ss<<"\n";
        ss<<"   Private section:"; ss<<"\n";
        ss<<"       XTemplate *myTemplate;"; ss<<"\n";
        ss<<"*/"; ss<<"\n";
        ss<<"\n";

        //! Process class.
        ss<<"class XTemplate : public XWidget { "<<"\n";
        ss<<"public:"<<"\n";

        //! Process constructor, destructor.
        ss<<"\t"; ss<<"XTemplate(XWindow *theWindow){"; ss<<"\n";
        ss<<"\t\t"; ss<<"this->setWindow(theWindow);"; ss<<"\n";
        ss<<"\t\t"; ss<<"setScissorWindow(theWindow);"; ss<<"\n";
        ss<<"\t"; ss<<"}" <<"\n";
        ss<<"\t"; ss<<"~XTemplate(){}" <<"\n";
        ss<<"\n";

        //! Add virtual funcions trough VirtualFunctionTemplateText.txt file.
        /*
        for(auto entry : std::filesystem::directory_iterator(cwd)){
            theDir=entry.path().parent_path().parent_path().c_str();
            //! Hidden file.
            thePath=theDir+"/vendor/xcreator/.VirtualFunctionTemplateText.txt";
            break;
        }
        */
        ss<<XFile().readTextFile(theVirtualFunctionTemplateTextPath);

        //! Process init:
        ss<<"\t"<<"void init(){"<<"\n";

        for(uint i=0; i<theWidgetList.size(); i++){
            //! Short notation for this widget.
            XWidget *Wi=theWidgetList.at(i);
            float x,y,z,w,h;
            x=Wi->Size().Origin().X();
            y=Wi->Size().Origin().Y();
            z=Wi->Size().Origin().Z();
            w=Wi->Size().Width();
            h=Wi->Size().Height();

            std::string widgetType=Wi->Type();
            //! Convert a XDesignerFrame to a XFrame during code processing.
            if(widgetType=="XDesignerFrame"){
                widgetType="XFrame";
            }
            ss<<"\t\t"<<Wi->Name()<<"=new "<<widgetType<<"(Window());"<<"\n";
            ss<<"\t\t"<<Wi->Name()<<"->"<<"setSize("<<"{{"<<x<<","<<y<<","<<z<<"},"<<w<<","<<h<<"}"<<");"<<"\n";
            ss<<"\t\t"<<Wi->Name()<<"->"<<"setName("<<ACO<<Wi->Name()<<ACO<<");"<<"\n";
            ss<<"\t\t"<<Wi->Name()<<"->"<<"setString("<<ACO<<Wi->Name()<<ACO<<");"<<"\n";
            ss<<"\n";
        }
        //! Add parent, child structure. This is quite easy to do. Just go through theWidgetlist and addWidget.
        for(uint i=0; i<theWidgetList.size(); i++){
            //! Short notation for this widget.
            XWidget *Wi=theWidgetList.at(i);
            for(uint j=0; j<Wi->WidgetVec().size(); j++){
                //! Short notation for this child wiget.
                XWidget *Ci=Wi->WidgetVec().at(j);
                // Sample: aMainWindow->addWidget(aFrame_0);
                ss<<"\t\t"<<Wi->Name()<<"->addWidget("<<Ci->Name()<<");"<<"\n";
            }
        }
        //! From the XTemplate add toplevel child.
        ss<<"\t\t"<<"addWidget("<<theWidgetList.front()->Name()<<");"<<"\n";

        ss<<"\t"<<"}"<<"\n";

        //! Process draw:
        ss<<"\t"<<"void draw(){"<<"\n";

        //! Set scissor.
        ss<<"\t\t"<<"//! Save the current scissor size to be restored at end of this function."<<"\n";
        ss<<"\t\t"<<"saveScissorState();"<<"\n";
        ss<<"\t\t"<<"//! Set the scissor union size."<<"\n";
        ss<<"\t\t"<<"setScissorUnion(ParentScissorSize(),mySize->Size());"<<"\n";

        //! Set the designer frame size to dialog size.
        ss<<"\t\t"<<"DesignerFrame->setSize(mySize->Size());"<<"\n";
        //! Set the first child widget to the designer frame size.
        if(theWidgetList.size()>0){
            ss<<"\t\t"<<theWidgetList.at(1)->Name()<<"->setSize(DesignerFrame->Size());"<<"\n";
        }

        //! Draw content.
        ss<<"\t\t"<<"drawWidgetVec();"; ss<<"\n";

        //! Restore scissor.
        ss<<"\t\t"<<"//! Restore the scissor size."<<"\n";
        ss<<"\t\t"<<"restoreScissorState();"<<"\n";

        ss<<"\t"<<"}"<<"\n";

        //! Process private:
        ss<<"private:"<<"\n";
        //! Add name.
        ss<<"\t"<<"std::string myName;"; ss<<"\n";
        //! Add size.
        ss<<"\t"<<"XSize *mySize=new XSize();"; ss<<"\n";
        for(uint i=0; i<theWidgetList.size(); i++){

            std::string widgetType=theWidgetList.at(i)->Type();
            //! Convert the XDesignerFrame to a XFrame during code processing.
            if(widgetType=="XDesignerFrame"){
                widgetType="XFrame";
            }
            ss<<"\t"<<widgetType<<" *"<<theWidgetList.at(i)->Name()<<";"<<"\n";
        }

        //! End of class.
        ss<<"};"<<"\n";

        //! End of .h file.
        ss<<"#endif "<<"\n";

        //! Get current working directory.
        /*
        for(auto entry : std::filesystem::directory_iterator(cwd)){
            // theDir=entry.path().parent_path().parent_path().c_str();
            thePath=theDir+"/vendor/xcreator/XTemplate.h";
            break;
        }
        */
        //! Print result to terminal.
        std::cout<<ss.str()<<std::endl;
        //! Save result to file.
        std::string thePath=std::filesystem::current_path();
        thePath.append("/XTemplate.h");
        XFile().saveFile(thePath,ss.str());
        //! Save widget structure to file.
        thePath=std::filesystem::current_path();
        thePath.append("/WidgetStructureOutputs.txt");
        XFile().saveFile(thePath,XWidgetView().printWidgetToString(Pa));
    }


    void sampleCode(/*process node text to .h code line by line.. frame adds button.. next node.*/){
        std::stringstream ss;

        //* Creata a class, put code in public domain.

        //* Create function to automate the separate widget setup, data source XWidgetView.
        //! Pass trough the GLFWwindow pointer.
        XWindow *aWindow=myWindow;

        XWidget* aMainWindow=new XWidget(aWindow);

        //! Create a new frame.
        XFrame *aFrame_0=new XFrame();
        aFrame_0->setWindow(aWindow);
        aFrame_0->setSize({{0,0,0},200,20});
        aFrame_0->setName("aFrame_0");

        //! Create a new button.
        XButton *aButton_0=new XButton(aWindow);
        aButton_0->setString("aButton_0");
        aButton_0->setSize({{0,0,0},200,20});
        aButton_0->setName("aButton_0");

        //* Create function to automate this add widget structure step, data source XWidgetView.
        //! Add widget structure
        aMainWindow->addWidget(aFrame_0);
        aFrame_0->addWidget(aButton_0);

        //* Create a event functions to automate event creation.
        //! Process events.
        if(aButton_0->Event(XEventEnum::PressedLeft)){

        }
        if(aButton_0->Event(XEventEnum::ReleasedLeft)){

        }

        //! Draw the content.
        aButton_0->draw();
    };

private:
    XWidget *myWidget;
    std::string myLicenceTextPath;
    //! A pointer to the dialog window.
    XWindow *myWindow;

};

#endif // XDESIGNERCODEGENERATOR_H












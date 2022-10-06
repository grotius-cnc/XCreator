#ifndef XFILEOPEN_H
#define XFILEOPEN_H

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
#include <XButton.h>
#include <XImageButton.h>
#include <XTextEdit.h>
#include <XTreeView.h>
#include <XVerticalSlider.h>

// Fileinfo modification time & date of file.
#include <sys/stat.h>
#ifdef WIN32
#include <unistd.h>
#define stat _stat
#endif

// Owner of file.
#include <pwd.h>
#include <grp.h>

// Others.
#include <filesystem>
#include <optional>
#include <fstream>
#include <cstdlib>

struct itemStruct{
    //! Path includes filename.
    std::string path,filename,icon;
};

class XFileOpen : public XWidget {
public:
    XFileOpen(XWindow *theWindow){
        this->setWindow(theWindow);
        setScissorWindow(theWindow);
    }
    ~XFileOpen(){}

    //! Virtual functions.
    //! Type of this widget.
    std::string Type(){
        return "XDialogFileContent";
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
        myButton_up=new XImageButton(Window(),"icons/Adwaita/16x16/legacy/go-up.png");
        myButton_up->setName("Button_up");
        myButton_up->setBorderSize(2);

        myTreeView=new XTreeView(Window());
        myTreeView->setName("TreeView_left");
        myTreeView->setString("TreeView_left");

        mySlider=new XVerticalSlider(Window());
        mySlider->setName("Slider");

        myButton_cancel=new XButton(Window());
        myButton_cancel->setName("Button_cancel");
        myButton_cancel->setString("Cancel");

        myButton_ok=new XButton(Window());
        myButton_ok->setName("Button_ok");
        myButton_ok->setString("Ok");

        addWidget(myButton_up);
        addWidget(myButton_cancel);
        addWidget(myButton_ok);
        addWidget(myTreeView);
        addWidget(mySlider);

        //! Skip demo content.
        myTreeView->setContentInit(1);

        //! Initialize content of current path and set toplevel item to unfold.
        process(CurrentPath());
        myTreeView->setTopLevelItemUnfold();
    }
    void draw(){
        //! Save the current scissor size to be restored at end of this function.
        saveScissorState();
        //! Set the scissor union size.
        setScissorUnion(ParentScissorSize(),mySize->Size());

        myButton_up->setSize({{0,0,0},20,20});
        myTreeView->setSize({{0,20,0},mySize->Width()-20,mySize->Height()-40});
        mySlider->setSize({{mySize->Width()-20,20,0},20,mySize->Height()-40});
        myButton_cancel->setSize({{mySize->Width()-200,mySize->Height()-20,0},100,20});
        myButton_ok->setSize({{mySize->Width()-100,mySize->Height()-20,0},100,20});

        //! set event lock when slider is active.
        if(mySlider->hasEvent()){
            myTreeView->setEventLock(1);
            myButton_cancel->setEventLock(1);
            myButton_ok->setEventLock(1);
            myButton_up->setEventLock(1);
        } else {
            myTreeView->setEventLock(0);
            myButton_cancel->setEventLock(0);
            myButton_ok->setEventLock(0);
            myButton_up->setEventLock(0);
        }

        if(myTreeView->NeedsUpdate()){
             process(CurrentPath());
        }

        //! Dir up event.
        if(myButton_up->Event(XEventEnum::PressedLeft)){
            process(ParentPath());
            myTreeView->resetSelectedRowToTop();
            mySlider->setValue(0);
        }
        if(myButton_up->Event(XEventEnum::ReleasedLeft)){
            //! std::cout<<"up released"<<std::endl;
        }
        //! Left TreeView item selected.
        if(myTreeView->isPressed()){
            if(isDirectory(myTreeView->mySelectedItemName())){
                myTreeView->resetSelectedRowToTop();
                mySlider->setValue(0);
            }
            process(myTreeView->mySelectedItemName());
        }
        //! Close this window when cancel is pressed.
        if(myButton_cancel->isPressed()){
            myShouldCloseOnCancel=true;
            myShouldClose=true;
            // std::cout<<"cancel pressed"<<std::endl;
        }
        //! Close this window and return chosen file.
        if(myButton_ok->isPressed()){
            myShouldClose=true;
        }

        if(myTreeView->Event(XEventEnum::ScrollDown)){
            mySlider->setStepDown();
        }
        if(myTreeView->Event(XEventEnum::ScrollUp)){
            mySlider->setStepUp();
        }

        //! Set the treeview scroll value.
        myTreeView->setVerticalScroll(mySlider->Value());

        drawWidgetVec();
        //! Restore the scissor size.
        restoreScissorState();
    }
    std::string Path(){
        return myPath;
    }
    std::string Result(){
        //! Return empty result on cancel.
        if(myShouldCloseOnCancel){
            return "";
        }
        return myTreeView->mySelectedItemName();
    }
    bool ShouldClose(){
        return myShouldClose;
    }

private:
    std::string myName;
    XSize *mySize=new XSize();
    XTreeView *myTreeView;
    XButton *myButton_cancel;
    XButton *myButton_ok;
    XImageButton *myButton_up;
    XVerticalSlider *mySlider;

    bool myShouldClose=0;
    bool myShouldCloseOnCancel=0;
    std::string myPath;

    void process(std::string thePath){
        //! If a directory is pressed, go on.
        if(isDirectory(thePath)){
            myPath=thePath;
            //! Populate left TreeView with parent directory path.
            myTreeView->setTopLevelItem(myPath,std::filesystem::path(myPath).filename(),"icons/Adwaita/16x16/places/folder.png",true);
            std::vector<itemStruct> ItemVec=getFileList(myPath);
            for(uint i=0; i<ItemVec.size(); i++){
                myTreeView->addChildItem(ItemVec.at(i).path,ItemVec.at(i).filename,myPath,ItemVec.at(i).icon);
            }
        }
    }

    std::string CurrentPath(){
        return std::filesystem::current_path();
    }
    std::string ParentPath(){
        //! std::cout<<"myPath:"<<myPath<<std::endl;
        //! std::cout<<"ParentPath:"<<std::filesystem::path(myPath).parent_path()<<std::endl;
        return std::filesystem::path(myPath).parent_path();
    }

    bool isDirectory(std::string thePath){
        bool status=std::filesystem::is_directory(thePath);
        //! std::cout<<"isDirectory:"<<status<<std::endl;
        return status;
    }

    //! Get file list of current directory.
    std::vector<itemStruct> getFileList(std::string thePath){

        std::vector<itemStruct> itemVec;
        for(auto entry : std::filesystem::directory_iterator(thePath)){

            //! Get the file extension text.
            std::string extension=entry.path().extension().generic_string();
            //! std::cout<<"extension:"<<extension<<std::endl;

            //! Add icon for file extension.
            std::string icon="icons/Adwaita/16x16/mimetypes/application-x-generic.png";

            if(extension=="" && entry.is_directory()){
                icon="icons/Adwaita/16x16/places/folder.png";
            }
            if(extension=="" && !entry.is_directory() && entry.path().filename()!="Makefile"){
                icon="icons/Adwaita/16x16/mimetypes/application-x-executable.png";
            }
            if(extension==".ttf"){
                icon="icons/Adwaita/16x16/mimetypes/font-x-generic.png";
            }
            if(extension==".png" || extension==".jpg" || extension==".svg" || extension==".bmp"){
                icon="icons/Adwaita/16x16/mimetypes/image-x-generic.png";
            }
            if(extension==".txt"){
                icon="icons/Adwaita/16x16/mimetypes/text-x-generic.png";
            }
            if(extension==".so"){
                icon="icons/Adwaita/16x16/mimetypes/application-x-sharedlib.png";
            }
            if(extension==".tar" || extension==".gz" || extension==".zip" || extension==".deb"){
                icon="icons/Adwaita/16x16/mimetypes/package-x-generic.png";
            }
            if(extension==".sh"){
                icon="icons/Adwaita/16x16/mimetypes/text-x-script.png";
            }
            if(extension==".mp3"){
                icon="icons/Adwaita/16x16/mimetypes/audio-x-generic.png";
            }
            if(extension==".mp4"){
                icon="icons/Adwaita/16x16/mimetypes/video-x-generic.png";
            }
            if(extension==".html"){
                icon="icons/Adwaita/16x16/mimetypes/text-html.png";
            }
            if(extension==".appimage" || extension==".AppImage"){
                icon="icons/Adwaita/16x16/mimetypes/application-x-executable.png";
            }
            //! Add to vector.
            itemVec.push_back({entry.path(),entry.path().filename(),icon});
        }
        return itemVec;
    }

    void exampleFunction(std::string thePath){
        struct stat theFileInfoStruct;
        struct tm *timeinfo;
        struct passwd *pw;
        struct group *gr;
        //! if(std::filesystem::is_directory(thePath)){ // Go on if it's a directory.

        for(auto entry : std::filesystem::directory_iterator(thePath)){
            std::cout<<entry.path()<<std::endl;
            //! If unknown, do something. It could be a dir or executable.
            if(entry.path().has_filename()){
                std::cout<<"hasFileName."<<std::endl;
            }
            if(entry.is_directory()){
                std::cout<<"isDirectory."<<std::endl;
            }
            if(entry.is_symlink()){
                std::cout<<"isSymlink"<<std::endl;
            }
            if(entry.is_regular_file()){
                std::cout<<"isRegularFile."<<std::endl;
                //! Get the time and date of file modified info.
                if(stat(entry.path().c_str(),&theFileInfoStruct)==0){;
                    timeinfo = localtime(&theFileInfoStruct.st_ctime);
                    std::cout<<"File time & date:"<<asctime(timeinfo);
                    pw=getpwuid(theFileInfoStruct.st_uid);
                    std::cout<<"Owner:"<<pw->pw_name<<std::endl;
                    gr=getgrgid(theFileInfoStruct.st_gid);
                    std::cout<<"Group:"<<gr->gr_name<<std::endl;
                }
            }
            if(entry.is_other()){
                std::cout<<"isOtherFile."<<std::endl;
            }
            if(entry.is_character_file()){
                //! std::cout<<"isCharacterFile."<<std::endl;
            }
            if(entry.is_fifo()){
                //! std::cout<<"isFifo"<<std::endl;
            }
            if(entry.is_block_file()){
                //! std::cout<<"isBlockFile"<<std::endl;
            }
            if(entry.is_socket()){
                //! std::cout<<"isSocket"<<std::endl;
            }
        }
    }
};
#endif




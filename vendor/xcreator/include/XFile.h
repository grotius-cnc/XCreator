#ifndef XFILE_H
#define XFILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <XColor.h>
#include <XChar.h>

class XFile {
public:
    XFile(){}
    //! Read the texfile into memory.
    XFile(std::string theFileName):myFileName(theFileName){
        myString=readTextFile(theFileName);
    }
    std::string getText(){
        return myString;
    }
    void setText(std::string theText){
        myString=theText;
    }
    // To be checked.
    void insertText(std::string theText, uint thePos){
        myString.insert(thePos,theText.size(),*theText.c_str());
    }
    void removeText(uint theStartPos, uint theEndPos){
        myString.erase(theStartPos,theEndPos);
    }
    void reloadFile(){
        readTextFile(myFileName);
    }
    //! Read a textfile into a std::string.
    std::string readTextFile(std::string theFileName){
        std::fstream newfile;
        std::string theString;
        std::string tp;
        newfile.open(theFileName.c_str(),std::ios::in); //open a file to perform read operation using file object
        if (newfile.is_open()){   //checking whether the file is open
            while(getline(newfile, tp)){  //read data from file object and put it into string.
                theString.append(tp);
                theString.append("\n");
                // std::cout << tp << "\n";   //print the data of the string
            }
            theString.append("\n");
            newfile.close();   //close the file object.
        } else {
            std::cout<<"XFile, error opening textfile."<<std::endl;
        }
        std::cout<<"theString:"<<theString<<std::endl;
        // theString.erase(0,1); // removes first character

        return theString;
    }
    //! Read a textfile into a XString.
    XString readTextFileIntoXString(std::string theFileName, XColor theTextColor={1.0,1.0,1.0,1.0}){
        std::string theString=readTextFile(theFileName);
        XString theXString;
        theXString.setStringFromStdString(theString);
        theXString.setColorToString(theTextColor);
        return theXString;
    }

    void saveFile(std::string theFileName, std::string theString){
        std::fstream newfile;
        newfile.open(theFileName.c_str(),std::ios::out);  // open a file to perform write operation using file object
        if(newfile.is_open())     //checking whether the file is open
        {
            newfile<<theString;  //inserting text
            newfile.close();     //close the file object
        } else {
            std::cout<<"Error writing file."<<std::endl;
        }
    }

private:
    std::string myFileName;
    std::string myString;
};
#endif // XFILE_H

#ifndef XCHAR_H
#define XCHAR_H

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

#include <vector>
#include <iostream>
#include <XColor.h>

class XChar {
public:
    XChar(){}
    XChar(char theChar):myChar(theChar){}
    XChar(char theChar, XColor theColor):myChar(theChar),myColor(theColor){}

    void setColor(XColor theColor){
        myColor.setColor(theColor);
    }
    void setChar(char theChar){
        myChar=theChar;
    }
    void setChar(XChar theChar){
        myChar=theChar.Char();
        myColor=theChar.Color();
    }
    char Char(){
        return myChar;
    }
    XColor Color(){
        return myColor;
    }
private:
    char  myChar='0';
    XColor myColor;
};

class XString {
public:
    XString(){}
    XString(std::string theString){
        myString.clear();
        for(uint i=0; i<theString.size(); i++){
            myString.push_back(XChar(theString.at(i)));
        }
    }
    XString(std::string theString, XColor theColor){
        myString.clear();
        for(uint i=0; i<theString.size(); i++){
            myString.push_back(XChar(theString.at(i)));
            myString.back().setColor(theColor);
        }
    }
    void setStringFromStdString(std::string theString){
        myString.clear();
        for(uint i=0; i<theString.size(); i++){
            myString.push_back(XChar(theString.at(i)));
        }
    }
    void setString(XString theString){
        myString.clear();
        for(uint i=0; i<theString.size(); i++){
            myString.push_back(theString.at(i).Char());
        }
    }
    uint getLineCount(XString theString){
        uint theLineCount=0;
        for(uint i=0; i<theString.size(); i++){
            if(theString.at(i).Char()==XChar('\n').Char()){
                theLineCount++;
            }
        }
        return theLineCount;
    }
    XString getLineCountString(uint theLineCount){
        XString theString;
        for(uint i=0; i<theLineCount+1; i++){ // Add extra line nr at end.
            std::string theStringNr=std::to_string(i+1); // Begin at nr 1.
            for(uint j=0; j<theStringNr.size(); j++){
                theString.push_back(theStringNr.at(j));
            }
            theString.push_back('\n');
        }
        return theString;
    }
    std::string toStdString(){
        std::string theString;
        for(uint i=0; i<myString.size(); i++){
            theString.push_back(myString.at(i).Char());
        }
        return theString;
    }

    void push_back(char theChar){
        myString.push_back(XChar(theChar));
    }
    void push_back(XChar theChar){
        myString.push_back(theChar);
    }
    //! Get the back XChar.
    XChar back(){
        return myString.back();
    }
    //! Get the front XChar.
    XChar front(){
        return myString.front();
    }
    void pop_back(){
        myString.pop_back();
    }
    void insert(uint thePosition, XChar theChar){
        std::vector<XChar> result;

        if(thePosition==0){
            result.push_back(theChar);
        }
        if(myString.size()>0){
            for(uint i=0; i<myString.size(); i++){
                result.push_back(myString.at(i));
                if(i==thePosition-1){
                    result.push_back(theChar);
                }
            }
        }
        myString=result;
    }
    void insert(uint thePosition, std::string theStringToInsert){
        // std::cout<<"thePosition:"<<thePosition<<std::endl;
        std::string str=this->toStdString();
        str.insert(thePosition,theStringToInsert);
        myString.clear();
        for(uint i=0; i<str.size(); i++){
            myString.push_back(XChar(str.at(i)));
        }
    }
    void insert(uint thePosition, std::string theStringToInsert, XColor theColor){
        // std::cout<<"thePosition:"<<thePosition<<std::endl;
        std::string str=this->toStdString();
        str.insert(thePosition,theStringToInsert);
        myString.clear();
        for(uint i=0; i<str.size(); i++){
            myString.push_back(XChar(str.at(i),theColor));
        }
    }
    void erase(uint thePosition){
        std::vector<XChar> result;
        if(myString.size()>0){
            for(uint i=0; i<myString.size(); i++){
                if(i!=thePosition-1){
                    result.push_back(myString.at(i));
                }
            }
        }
        myString=result;
    }
    void clear(){
        myString.clear();
    }
    void print(){
        std::string str;
        for(uint i=0; i<myString.size(); i++){
            str.push_back(myString.at(i).Char());
        }
        std::cout<<str<<std::endl;
    }
    uint size(){
        return myString.size();
    }
    XChar at(uint thePosition){
        return myString.at(thePosition);
    }
    void setCharColor(uint thePosition, XColor theColor){
        myString.at(thePosition).setColor(theColor);
    }
    void setColorStringToWhite(){
        for(uint i=0; i<myString.size(); i++){
            myString.at(i).setColor({1.0,1.0,1.0,1.0});
        }
    }
    void setColorToString(XColor theColor){
        for(uint i=0; i<myString.size(); i++){
            myString.at(i).setColor(theColor);
        }
    }

private:
    std::vector<XChar> myString;
};

#endif // XCHAR_H



















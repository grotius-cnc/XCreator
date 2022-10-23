#ifndef XKEYWORD_H
#define XKEYWORD_H

#include <vector>
#include <string>
#include <iostream>
#include <XColor.h>
#include <XChar.h>

class XKeyWord{
public:
    XKeyWord(){}

    XString process(XString theString, uint theStartChar, uint theEndChar){

        theString.setColorToString({0.933,0.910,0.667,1.000});

        // std::cout<<"theStartChar:"<<theStartChar<<std::endl;
        // std::cout<<"theEndChar:"<<theEndChar<<std::endl;

        // Create a string of the visible text part.
        myTempText.clear();
        for(uint i=0; i<theString.size(); i++){
            if(i>=theStartChar && i<=theEndChar){
                myTempText.push_back(theString.at(i).Char());
            }
        }

        // Find and process Keywords.
        for(uint k=0; k<myKeyWords.size(); k++){
            // Modify colors to keywords.
            std::string myKeyWord=myKeyWords.at(k).first;
            XColor myKeyWordColor=myKeyWords.at(k).second;
            for(uint i=0; i<myTempText.size(); i++){
                size_t found=myTempText.find(myKeyWord,i);
                if(found != std::string::npos){
                    // std::cout<<"keyword found at:"<<found<<std::endl;
                    // Colorize..
                    for(uint j=0; j<myKeyWord.size(); j++){
                        //myTextColorVec.at(found+j)=myKeyWordColor; // A modified color.
                        theString.setCharColor(theStartChar+found+j,myKeyWordColor);
                    }
                }
                i+=myKeyWord.size();
            }
        }

        // Find sets line by line. Sets like : "" '' etc.
        uint count=0;
        std::vector<uint> countVec;
        bool theSwitch=0;
        for(uint i=0; i<myTempText.size(); i++){
            if(myTempText.at(i)==39 /* a decimal nr for : ' */){
                count++;
                countVec.push_back(i);
            }

            if(myTempText.at(i)=='\n' || i==myTempText.size()-1 /*EOF*/){
                // Evaluate sets as code.
                if(count>0 && count%2==0){
                    for(uint j=countVec.front(); j<myTempText.size(); j++){
                        for(uint k=0; k<countVec.size(); k++){
                            if(j==countVec.at(k)){
                                // Match.
                                if(theSwitch){
                                    // Colorize last character.
                                    theString.setCharColor(theStartChar+j,{0.961, 0.871, 0.702, 1.000});
                                }
                                theSwitch=!theSwitch;
                                break;
                            }
                        }
                        if(theSwitch){
                            theString.setCharColor(theStartChar+j,{0.961, 0.871, 0.702, 1.000});
                        }
                    }
                }
                countVec.clear();
                count=0;
            }
        }

        count=0;
        countVec.clear();
        theSwitch=0;
        for(uint i=0; i<myTempText.size(); i++){
            if(myTempText.at(i)=='"'){
                count++;
                countVec.push_back(i);
            }

            if(myTempText.at(i)=='\n' || i==myTempText.size()-1 /*EOF*/){
                // Evaluate sets as code.
                if(count>0 && count%2==0){
                    for(uint j=countVec.front(); j<myTempText.size(); j++){
                        for(uint k=0; k<countVec.size(); k++){
                            if(j==countVec.at(k)){
                                // Match.
                                if(theSwitch){
                                    // Colorize last character.
                                    theString.setCharColor(theStartChar+j,{0.804, 0.522, 0.247, 1.000});
                                }
                                theSwitch=!theSwitch;
                                break;
                            }
                        }
                        if(theSwitch){
                            theString.setCharColor(theStartChar+j,{0.804, 0.522, 0.247, 1.000});
                        }
                    }
                }
                countVec.clear();
                count=0;
            }
        }

        count=0;
        countVec.clear();
        theSwitch=0;
        bool disable;
        for(uint i=0; i<myTempText.size(); i++){
            if(myTempText.at(i)=='"'){ // Dont produce a comment line if we are inside quotes.
                disable=!disable;
            }
            if(!disable){
                // Find a comment like : //
                if(myTempText.size()>0 && myTempText.at(i)=='/' && myTempText.at(i+1)=='/'){
                    count++;
                    countVec.push_back(i);
                }
                if(myTempText.at(i)=='\n'){
                    count++;
                    countVec.push_back(i);
                }
            }

            if(myTempText.at(i)=='\n' || i==myTempText.size()-1 /*EOF*/){
                // Evaluate sets as code.
                if(count>0 && count%2==0){
                    for(uint j=countVec.front(); j<myTempText.size(); j++){
                        for(uint k=0; k<countVec.size(); k++){
                            if(j==countVec.at(k)){
                                // Match.
                                if(theSwitch){
                                    // Colorize last character.
                                    theString.setCharColor(theStartChar+j,{0.5, 0.5, 0.5, 1.0});
                                }
                                theSwitch=!theSwitch;
                                break;
                            }
                        }
                        if(theSwitch){
                            theString.setCharColor(theStartChar+j,{0.5, 0.5, 0.5, 1.0});
                        }
                    }
                }
                disable=0;
                countVec.clear();
                count=0;
                theSwitch=0;
            }
        }

        // Colorize values.
        // To be repaired there is a bug.
//        for(uint i=0; i<myTempText.size(); i++){
//            bool theFound=0;
//            if(myTempText.at(i)=='1'
//                    || myTempText.at(i)=='2'
//                    || myTempText.at(i)=='3'
//                    || myTempText.at(i)=='4'
//                    || myTempText.at(i)=='5'
//                    || myTempText.at(i)=='6'
//                    || myTempText.at(i)=='7'
//                    || myTempText.at(i)=='8'
//                    || myTempText.at(i)=='9'
//                    || myTempText.at(i)=='0'){
//                 theString.setCharColor(theStartChar+i,{0.722, 0.525, 0.043, 1.000});
//                 theFound=1;
//            }
//            // If a next char is a dot, it is part of the value.
//            if(theFound && myTempText.at(i+1)=='.' && myTempText.size()>i+1){
//                theString.setCharColor(theStartChar+i+1,{0.722, 0.525, 0.043, 1.000});
//            }
//        }

        return theString;
    }

private:
    std::string myTempText;

    std::vector<std::pair<std::string,XColor>> myKeyWords=
    {
        // Cyan.
        {"for",                 {0.000, 0.808, 0.820, 1.000}},
        {"if",                  {0.000, 0.808, 0.820, 1.000}},
        {"else",                {0.000, 0.808, 0.820, 1.000}},
        {"while",               {0.000, 0.808, 0.820, 1.000}},
        {"new ",                {0.000, 0.808, 0.820, 1.000}},
        {"return",              {0.000, 0.808, 0.820, 1.000}},
        {"delete ",             {0.000, 0.808, 0.820, 1.000}},
        {"this",                {0.000, 0.808, 0.820, 1.000}},
        {"class ",              {0.000, 0.808, 0.820, 1.000}},
        {"public:",             {0.000, 0.808, 0.820, 1.000}},
        {"private:",            {0.000, 0.808, 0.820, 1.000}},
        {"typename ",           {0.000, 0.808, 0.820, 1.000}},
        {"template",            {0.000, 0.808, 0.820, 1.000}},

        // HotPink.
        {"#ifndef ",            {1.000, 0.412, 0.706, 1.000}},
        {"#define" ,            {1.000, 0.412, 0.706, 1.000}},
        {"#include ",           {1.000, 0.412, 0.706, 1.000}},
        {"#endif ",             {1.000, 0.412, 0.706, 1.000}},

        // LightSalmon.
        {"void ",               {1.080, 0.627, 0.478, 1.000}},

        // FireBrick.
        {"bool ",               {0.100, 0.647, 0.000, 1.000}},
        {"float ",             {0.100, 0.647, 0.000, 1.000}},
        {"float ",              {0.100, 0.647, 0.000, 1.000}},
        {"uint ",               {0.100, 0.647, 0.000, 1.000}},
        {"int ",                {0.100, 0.647, 0.000, 1.000}}
    };

    std::vector<std::pair<std::string,XColor>> myComments=
    {
        {"// ",                 {0.600, 0.600, 0.600, 1.000}},
        {"//",                 {0.600, 0.600, 0.600, 1.000}}
    };
};

#endif // XKEYWORD_H

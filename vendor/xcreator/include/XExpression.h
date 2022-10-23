#ifndef XEXPRESSION_H
#define XEXPRESSION_H

#include <vector>
#include <string>
#include <iostream>
#include <math.h>

// A bucket like : {{"a"},{"b"},{"c"}}, also used by the Tokenizer.
typedef std::vector<std::string> strVec;

// Implementation:
// log, cos, acos, sin, asin, tan, atan, sqrt, pow, (), '+', '-', '*', '/', ','

// The XExpression class takes a textEdit text input and calculates the mathematical result logical step by step.
// Note: The result is given by the function result and is not displayed in the textEdit input field.
class XExpression{
public:
    // Empty constructor.
    // Usage: XExpression().runExample();
    // or
    // Usage: float theValue=XExpression().getExpressionResult("1+1+(10*10)");
    XExpression(){}
    // If you want to do it excel style like : $(0)+$(1), theCellValueVec holds all the cell results. $(0) will point to the first std::vector item.
    XExpression(std::vector<float> theCellValueVec):myCellValueVec(theCellValueVec){
        myCellValueVecSize=myCellValueVec.size();
        myEnableCell=true;
    }

    // Run a example.
    void runExample(){

        printString("running example.");
        // Set debug output.
        setDebug(true);
        // Set expresion.
        solve("(2+sqrt(16)+2+pow((1+1),2))/2");
    }
    // Calculate a expression and get a return value.
    float getExpressionResult(std::string theExpression){
        theExpression=checkForTyposAndRepair(theExpression);
        myResult=solve(theExpression);
        return myResult;
    }

    void setDebug(bool theStatus){
        myDebug=theStatus;
    }

    /* TestCase:
    strVec strTokenVec=createTokensFromString("-10.0+50.0+20.0/0.5*2*2");
    printStringVec("tokenvec:",strTokenVec);
    strTokenVec=solveTokenVec_Multiplication_Division(strTokenVec);
    printStringVec("tokenvec after * & / :",strTokenVec);
    strTokenVec=solveTokenVec_Addition_Substraction(strTokenVec);
    printStringVec("tokenvec after + & - ",strTokenVec);*/

private:
    float myResult=0;
    bool myDebug=0;
    bool myEnableCell=0;
    std::vector<float> myCellValueVec;
    uint myCellValueVecSize;

    // Prevent errors like : terminate called after throwing an instance of 'std::invalid_argument', what(): stof
    float stringToFloat(std::string theText){
        for(uint i=0; i<theText.size(); i++){
            if(getCharType(theText.at(i)==valueType)){
                // Ok, do nothing.
            } else {
                return 0;
            }
        }
        if(theText.size()==0){
            theText.push_back('0');
        }
        // std::cout<<"theTextToFloat, find the exception.."<<theText<<std::endl;
        return std::stof(theText);;
    }

    // This function looks for a valid expression input and try's to repair it.
    std::string checkForTyposAndRepair(std::string theText){
        std::string theNewText;
        uint openbracket=0, closebracket=0;
        for(uint i=0; i<theText.size()-1; i++){
            if(getCharType(theText.at(i))==valueType && theText.at(i+1)=='('){
                printError("no operator before open bracket.");
                return "0";
            }
        }
        // Filter out comments like : // Comment..
        bool theCommentTrigger=0;
        for(uint i=0; i<theText.size(); i++){
             if(theText.at(i)=='#'){
                 theCommentTrigger=1;
             }
             if(!theCommentTrigger){
                theNewText.push_back(theText.at(i));
             }
             if(theText.at(i)=='\n'){
                 theCommentTrigger=0;
             }
        }
        theText=theNewText;
        theNewText.clear(); // Swap for next function.

        for(uint i=0; i<theText.size(); i++){
            if(theText.at(i)=='\n' || theText.at(i)=='\0'){
                // Do nothing.
            } else {
                theNewText.push_back(theText.at(i));
            }
            if(theText.at(i)=='('){
                openbracket++;
            }
            if(theText.at(i)==')'){
                closebracket++;
            }
        }

        if(openbracket!=closebracket){
            // printError("unequal brackets.");
            return "0";
        }
        if(theNewText.size()==0){
            // printError("no input.");
            return "0";
        }
        if(getCharType(theNewText.back())!=valueType && getCharType(theNewText.back())!=BracketCloseType){ // Dont allow a last char as operator type : 5+5+
            // printError("last character is of type operator.");
            return "0";
        }
        return theNewText;
    }
    // Solve complete expression input and retun a float value.
    float solve(std::string theText){
        printString("Original expression:",theText);
        printString("theMaxBracketDepth:",evaluateBrackets(theText));

        // 1. Bracket solver loop.
        uint step=0;
        while(1){
            if(evaluateBrackets(theText)==0){ // If no brackets () are found it will skip this part.
                break;
            }
            theText=solveBracketStep(theText);
            if(myDebug){
                std::cout<<"bracket solved:"<<step<<" expression:"<<theText<<std::endl;
            }

            step++;
        }
        // 2. Final step.
        theText=solveNonBracketStep(theText);

        // 3. Print output.
        float theResult=stringToFloat(theText);
        printString("Result:",theResult);

        return theResult;
    }
    // Find brackets and look for nested bracket set's. Find the deepest nested bracket depth.
    uint evaluateBrackets(std::string theText){
        uint theCurrentDepth=0, theOpenBracketCount=0, theCloseBracketCount=0, theMaxBracketDepth=0;
        for(uint i=0; i<theText.size(); i++){
            if(theText.at(i)=='('){
                theCurrentDepth++;
                theOpenBracketCount++;
                if(theMaxBracketDepth<theCurrentDepth){
                    theMaxBracketDepth=theCurrentDepth;
                }
            }
            if(theText.at(i)==')'){
                theCurrentDepth--;
                theCloseBracketCount++;
            }
        }
        if(theCloseBracketCount==theOpenBracketCount){
            // Ok.
        } else {
            // std::cout<<"maxDepth error, non equal brackets sets in text."<<std::endl;
        }
        return theMaxBracketDepth;
    }
    // This just solves one expression text without brackets, like : 2+2*4
    std::string solveNonBracketStep(std::string theText){
        strVec strTokenVec=createTokensFromString(theText);
        if(strTokenVec.size()>2){
            strTokenVec=solveTokenVec_Multiplication_Division(strTokenVec);
            // printStringVec("tokenvec after * & / :",strTokenVec);
        }
        if(strTokenVec.size()>2){
            strTokenVec=solveTokenVec_Addition_Substraction(strTokenVec);
            // printStringVec("tokenvec after + & - :",strTokenVec);
        }
        if(strTokenVec.size()>1){
            printError("error in solveNonBracketStep function.");
        }
        return strTokenVec.back();
    }
    // Solve the expression between a bracket set, like : (2+2+4)+(5+5+(1+1))
    // This function will solve a single bracket set, only solving the deepest one, in above case : (1+1).
    // This function is repeatedly called to sove a serie of bracket set's.
    // If all bracket set's are solved, finally "solveNonBracketStep" is called to calculate final value.
    std::string solveBracketStep(std::string theText){
        uint theCurrentDepth=0, theOpenBracketCount=0, theCloseBracketCount=0, theMaxBracketDepth=0;
        bool theTrigger=0, theFinish=0;
        std::string theSubExpression;
        uint istart=0, iend=0;
        strVec strTokenVec;

        // Switches to be uses by expressions like : pow(2,2) or POW(2,2)
        bool thePowTrigger=0, theSqrtTrigger=0;
        bool theCosTrigger=0, theSinTrigger=0, theTanTrigger=0;
        bool theACosTrigger=0, theASinTrigger=0, theATanTrigger=0;
        bool theLogTrigger=0, theCellTrigger=0;

        theMaxBracketDepth=evaluateBrackets(theText); // Find maxdepth bracket set "(..)".

        for(uint i=0; i<theText.size(); i++){
            if(theText.at(i)=='('){
                theCurrentDepth++;
                theOpenBracketCount++;
                if(theMaxBracketDepth==theCurrentDepth){ // At maxDepth bracket set. Look for a special expression like : pow(..) or POW(..)
                    // Check if its a pow expression.
                    if((i>2 && theText.at(i-3)=='p' && theText.at(i-2)=='o' && theText.at(i-1)=='w')||
                            (i>2 && theText.at(i-3)=='P' && theText.at(i-2)=='O' && theText.at(i-1)=='W')){
                        printString("pow found");
                        thePowTrigger=1;
                    }
                    // Check if its a sqrt expression.
                    if((i>3 && theText.at(i-4)=='s' && theText.at(i-3)=='q' && theText.at(i-2)=='r' && theText.at(i-1)=='t') ||
                            (i>3 && theText.at(i-4)=='S' && theText.at(i-3)=='Q' && theText.at(i-2)=='R' && theText.at(i-1)=='T')){
                        printString("sqrt found");
                        theSqrtTrigger=1;
                    }
                    // Check if its a cosinus expression.
                    if((i>2 && theText.at(i-3)=='c' && theText.at(i-2)=='o' && theText.at(i-1)=='s')||
                            (i>2 && theText.at(i-3)=='C' && theText.at(i-2)=='O' && theText.at(i-1)=='S')){
                        printString("cos found");
                        theCosTrigger=1;
                    }
                    // Check if its a Acosinus expression.
                    if((i>3 && theText.at(i-3)=='a' && theText.at(i-2)=='c' && theText.at(i-1)=='o' && theText.at(i-1)=='s')||
                            (i>3 && theText.at(i-3)=='A' && theText.at(i-2)=='C' && theText.at(i-1)=='O' && theText.at(i-1)=='S')){
                        printString("acos found");
                        theACosTrigger=1;
                    }
                    // Check if its a sinus expression.
                    if((i>2 && theText.at(i-3)=='s' && theText.at(i-2)=='i' && theText.at(i-1)=='n')||
                            (i>2 && theText.at(i-3)=='S' && theText.at(i-2)=='I' && theText.at(i-1)=='N')){
                        printString("sin found");
                        theSinTrigger=1;
                    }
                    // Check if its a Asinus expression.
                    if((i>3 && theText.at(i-3)=='a' && theText.at(i-2)=='s' && theText.at(i-1)=='i' && theText.at(i-1)=='n')||
                            (i>3 && theText.at(i-3)=='A' && theText.at(i-2)=='S' && theText.at(i-1)=='I' && theText.at(i-1)=='N')){
                        printString("asin found");
                        theASinTrigger=1;
                    }
                    // Check if its a tangens expression.
                    if((i>2 && theText.at(i-3)=='t' && theText.at(i-2)=='a' && theText.at(i-1)=='n')||
                            (i>2 && theText.at(i-3)=='T' && theText.at(i-2)=='A' && theText.at(i-1)=='N')){
                        printString("tan found");
                        theTanTrigger=1;
                    }
                    // Check if its a ATangens expression.
                    if((i>3 && theText.at(i-3)=='a' && theText.at(i-2)=='t' && theText.at(i-1)=='a' && theText.at(i-1)=='n')||
                            (i>3 && theText.at(i-3)=='A' && theText.at(i-2)=='T' && theText.at(i-1)=='A' && theText.at(i-1)=='N')){
                        printString("atan found");
                        theATanTrigger=1;
                    }
                    // Check if its a Log expression.
                    if((i>2 && theText.at(i-3)=='l' && theText.at(i-2)=='o' && theText.at(i-1)=='g')||
                            (i>2 && theText.at(i-3)=='L' && theText.at(i-2)=='O' && theText.at(i-1)=='G')){
                        printString("log found");
                        theLogTrigger=1;
                    }
                    // Check if is a cell position.
                    if(i>0 && theText.at(i-1)=='$' && myEnableCell){
                        printString("cell found");
                        theCellTrigger=1;
                    }

                    theTrigger=1;
                    istart=i;
                    i++;
                }
            }
            if(theText.at(i)==')'){
                theCurrentDepth--;
                theCloseBracketCount++;
                iend=i;
                if(theTrigger){
                    theTrigger=0;
                    theFinish=1;
                }
            }
            if(theTrigger){
                theSubExpression.push_back(theText.at(i));
            }
            if(theFinish){
                if(getCharType(theSubExpression.back())==operatorType){ // Avoid a expression with a operator as last char like : (5+5+)
                    theSubExpression.pop_back();
                }
                if(theSubExpression==""){ // Prevent a empty expression like : (), make it (0)
                    theSubExpression="0";
                }

                strTokenVec=createTokensFromString(theSubExpression);
                printStringVec("tokenvec:",strTokenVec);
                if(strTokenVec.size()>2){
                    strTokenVec=solveTokenVec_Multiplication_Division(strTokenVec);
                }
                printStringVec("tokenvec after * & / :",strTokenVec);
                if(strTokenVec.size()>2){
                    strTokenVec=solveTokenVec_Addition_Substraction(strTokenVec);
                }
                printStringVec("tokenvec after + & - :",strTokenVec);
                if(thePowTrigger){
                    if(strTokenVec.size()>2){
                        strTokenVec=solveTokenVec_Pow(strTokenVec);
                    }
                    printStringVec("tokenvec after pow",strTokenVec);
                }
                if(theSqrtTrigger){
                    if(strTokenVec.size()>0){
                        strTokenVec=solveTokenVec_Sqrt(strTokenVec);
                    }
                    printStringVec("tokenvec after sqrt",strTokenVec);
                }
                if(theCosTrigger){
                    if(strTokenVec.size()>0){
                        strTokenVec=solveTokenVec_Cos(strTokenVec);
                    }
                    printStringVec("tokenvec after cos",strTokenVec);
                }
                if(theACosTrigger){
                    if(strTokenVec.size()>0){
                        strTokenVec=solveTokenVec_ACos(strTokenVec);
                    }
                    printStringVec("tokenvec after acos",strTokenVec);
                }
                if(theSinTrigger){
                    if(strTokenVec.size()>0){
                        strTokenVec=solveTokenVec_Sin(strTokenVec);
                    }
                    printStringVec("tokenvec after sin",strTokenVec);
                }
                if(theASinTrigger){
                    if(strTokenVec.size()>0){
                        strTokenVec=solveTokenVec_ASin(strTokenVec);
                    }
                    printStringVec("tokenvec after asin",strTokenVec);
                }
                if(theTanTrigger){
                    if(strTokenVec.size()>0){
                        strTokenVec=solveTokenVec_Tan(strTokenVec);
                    }
                    printStringVec("tokenvec after tan",strTokenVec);
                }
                if(theATanTrigger){
                    if(strTokenVec.size()>0){
                        strTokenVec=solveTokenVec_ATan(strTokenVec);
                    }
                    printStringVec("tokenvec after atan",strTokenVec);
                }
                if(theLogTrigger){
                    if(strTokenVec.size()>0){
                        strTokenVec=solveTokenVec_Log(strTokenVec);
                    }
                    printStringVec("tokenvec after log",strTokenVec);
                }
                if(theCellTrigger){
                    if(strTokenVec.size()>0){
                        strTokenVec=solveTokenVec_Cell(strTokenVec);
                    }
                    printStringVec("tokenvec after cell",strTokenVec);
                }

                theText.erase(istart,(iend-istart)+1);
                theText.insert(istart,strTokenVec.back());
                return theText;
            }
        }
        return "error";
    }
    // Create a token vector from a string input like : -12.5*8.0-6.0*5.0/2.0+90.1
    // The tokenVec would then look like : -12.5, *, 8.0, -, 6.0, *, 5.0, /, 2.0, +, 90.1
    // The tokenVec parses a input text like a lexer.
    std::vector<std::string> createTokensFromString(std::string theText){
        std::string theValue;
        std::vector<std::string> theTokenVec;
        bool theMinusStartTrigger=0;

        for(uint i=0; i<theText.size(); i++){
            if(theText.at(0)=='-' && !theMinusStartTrigger){ // When the first value of the string is a negative value and not a operator.
                theValue.push_back(theText.at(0));
                theMinusStartTrigger=1;
            }
            if(getCharType(theText.at(i))==valueType){
                theValue.push_back(theText.at(i));
            }
            if(i>0 && getCharType(theText.at(i))==operatorType){
                if(getCharType(theText.at(i-1))==operatorType){
                    // For now prevent a multiple operator sequence like +-, ++, +-, *=, etc.
                    printString("CreateTokensFromString, multiple operator sequence found, skipp.");
                } else {
                    theTokenVec.push_back(theValue);
                    theValue.clear();
                    std::string theOperator;
                    theOperator.push_back(theText.at(i));
                    theTokenVec.push_back(theOperator);
                }
            }
            if(i==theText.size()-1){ // Finisch EOF.
                theTokenVec.push_back(theValue);
                theValue.clear();
            }
        }
        return theTokenVec;
    }
    // At this stage theTokenVec has only one member left.
    strVec solveTokenVec_Sqrt(strVec theTokenVec){
        theTokenVec.back()=std::to_string(sqrt(stringToFloat(theTokenVec.back()))); // Expressions like : SQRT(16) or sqrt(16)
        return theTokenVec;
    }
    strVec solveTokenVec_Cos(strVec theTokenVec){
        theTokenVec.back()=std::to_string(cos(stringToFloat(theTokenVec.back())));
        return theTokenVec;
    }
    strVec solveTokenVec_ACos(strVec theTokenVec){
        theTokenVec.back()=std::to_string(acos(stringToFloat(theTokenVec.back())));
        return theTokenVec;
    }
    strVec solveTokenVec_Sin(strVec theTokenVec){
        theTokenVec.back()=std::to_string(sin(stringToFloat(theTokenVec.back())));
        return theTokenVec;
    }
    strVec solveTokenVec_ASin(strVec theTokenVec){
        theTokenVec.back()=std::to_string(asin(stringToFloat(theTokenVec.back())));
        return theTokenVec;
    }
    strVec solveTokenVec_Tan(strVec theTokenVec){
        theTokenVec.back()=std::to_string(tan(stringToFloat(theTokenVec.back())));
        return theTokenVec;
    }
    strVec solveTokenVec_ATan(strVec theTokenVec){
        theTokenVec.back()=std::to_string(atan(stringToFloat(theTokenVec.back())));
        return theTokenVec;
    }
    strVec solveTokenVec_Log(strVec theTokenVec){
        theTokenVec.back()=std::to_string(log(stringToFloat(theTokenVec.back())));
        return theTokenVec;
    }
    strVec solveTokenVec_Cell(strVec theTokenVec){
        if(std::stoi(theTokenVec.back())>int(myCellValueVecSize-1)){ // Limit the user input to the vector size.
            theTokenVec.back()=std::to_string(int(myCellValueVecSize)-1);
        }
        theTokenVec.back()=std::to_string(myCellValueVec.at(std::stoi(theTokenVec.back())));
        return theTokenVec;
    }
    strVec solveTokenVec_Pow(strVec theTokenVec){ // Expressions like : POW(2,2) or pow(2,2)
        strVec theNewTokenVec;
        bool theTrigger=0;
        theNewTokenVec.clear();
        for(uint i=0; i<theTokenVec.size(); i++){
            theNewTokenVec.push_back(theTokenVec.at(i));
            if(i<theTokenVec.size()-2){
                if(theTokenVec.at(i+1)=="," && !theTrigger){
                    theTrigger=1;
                    float a=stringToFloat(theNewTokenVec.back());
                    float b=stringToFloat(theTokenVec.at(i+2));
                    if(theTokenVec.at(i+1)==","){
                        theNewTokenVec.back()=std::to_string(pow(a,b));
                    }
                    i+=2;
                }
            }
        }
        return theNewTokenVec;
    }
    // Solve a expression like 5+5 or 5/5.
    strVec solveTokenVec_Multiplication_Division(strVec theTokenVec){
        strVec theNewTokenVec;
        while(1){
            bool theTrigger=0;
            theNewTokenVec.clear();
            for(uint i=0; i<theTokenVec.size(); i++){
                theNewTokenVec.push_back(theTokenVec.at(i));
                if(i<theTokenVec.size()-2){
                    if(theTokenVec.at(i+1)=="*" && !theTrigger){
                        theTrigger=1;
                        float a=stringToFloat(theNewTokenVec.back());
                        float b=stringToFloat(theTokenVec.at(i+2));
                        if(theTokenVec.at(i+1)=="*"){
                            theNewTokenVec.back()=std::to_string(a*b);
                        }
                        i+=2;
                    } else
                        if(theTokenVec.at(i+1)=="/" && !theTrigger){
                            theTrigger=1;
                            float a=stringToFloat(theNewTokenVec.back());
                            float b=stringToFloat(theTokenVec.at(i+2));
                            if(theTokenVec.at(i+1)=="/"){
                                theNewTokenVec.back()=std::to_string(a/b);
                            }
                            i+=2;
                        }
                }
            }
            bool stop=1; // Are there more to solve?
            for(uint i=0; i<theNewTokenVec.size(); i++){
                if(theNewTokenVec.at(i)=="*" || theNewTokenVec.at(i)=="/" ){
                    stop=0;
                    theTokenVec.clear();
                    theTokenVec=theNewTokenVec; // Reload.
                }
            }
            if(stop){
                break;
            }
        }
        return theNewTokenVec;
    }
    // Solve a expression like 5+5 or 5-5
    strVec solveTokenVec_Addition_Substraction(strVec theTokenVec){
        strVec theNewTokenVec;
        while(1){
            bool theTrigger=0;
            theNewTokenVec.clear();
            for(uint i=0; i<theTokenVec.size(); i++){
                theNewTokenVec.push_back(theTokenVec.at(i));
                if(i<theTokenVec.size()-2){
                    if(theTokenVec.at(i+1)=="+" && !theTrigger){
                        theTrigger=1;
                        float a=stringToFloat(theNewTokenVec.back());
                        float b=stringToFloat(theTokenVec.at(i+2));
                        if(theTokenVec.at(i+1)=="+"){
                            theNewTokenVec.back()=std::to_string(a+b);
                        }
                        i+=2;
                    } else
                        if(theTokenVec.at(i+1)=="-" && !theTrigger){
                            theTrigger=1;
                            float a=stringToFloat(theNewTokenVec.back());
                            float b=stringToFloat(theTokenVec.at(i+2));
                            if(theTokenVec.at(i+1)=="-"){
                                theNewTokenVec.back()=std::to_string(a-b);
                            }
                            i+=2;
                        }
                }
            }
            bool stop=1; // Are there more to solve?
            for(uint i=0; i<theNewTokenVec.size(); i++){
                if(theNewTokenVec.at(i)=="+" || theNewTokenVec.at(i)=="-" ){
                    stop=0;
                    theTokenVec.clear();
                    theTokenVec=theNewTokenVec; // Reload.
                }
            }
            if(stop){
                break;
            }
        }
        return theNewTokenVec;
    }
    // Is used by the Tokenizer function "createTokensFromString" to evaluate the chars and their meanings.
    enum myCharType{
        valueType,          // .0123456789
        operatorType,       // +,-,*,/,%,&,$,^
        BracketCloseType,    // )
        BracketOpenType,
        None
    };

    // Evaluate the char and it's meaning.
    myCharType getCharType(char theChar){
        if(theChar=='+'||theChar=='-'||theChar=='*'||theChar=='/'||theChar==','||theChar=='%'||theChar=='$'||
                theChar=='^'||theChar=='='||theChar==';'||theChar==':'||theChar=='"'){
            return operatorType;
        }
        if(theChar=='0'||theChar=='1'||theChar=='2'||theChar=='3'||
                theChar=='4'||theChar=='5'||theChar=='6'||theChar=='7'||
                theChar=='8'||theChar=='9'||theChar=='0'||theChar=='.'){
            return valueType;
        }
        if(theChar=='('){
            return BracketOpenType;
        }
        if(theChar==')'){
            return BracketCloseType;
        }
        return None;
    }
    // Internal print functions.
    void printStringVec(std::string theComment, std::vector<std::string> theStringVec){
        if(myDebug){
            for(uint i=0; i<theStringVec.size(); i++){
                std::cout<<theComment<<" i:"<<i<<" value:"<<theStringVec.at(i)<<std::endl;
            }
        }
    }
    void printString(std::string theComment, std::string theString){
        if(myDebug){
            std::cout<<theComment<<" value:"<<theString<<std::endl;
        }
    }
    void printString(std::string theComment, float theValue){
        if(myDebug){
            std::cout<<theComment<<" value:"<<theValue<<std::endl;
        }
    }
    void printString(std::string theComment){
        if(myDebug){
            std::cout<<theComment<<std::endl;
        }
    }
    void printError(std::string theComment){
        std::cout<<theComment<<std::endl;
    }
};

#endif // XEXPRESSION_H


































#ifndef XCOLOR_H
#define XCOLOR_H

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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>

class XColor {
public:
    XColor(){};
    XColor(float red, float green, float blue, float alpha) : myRed(red), myGreen(green), myBlue(blue), myAlpha(alpha){ }

    void setColor(float red, float green, float blue, float alpha){
        myRed=red;
        myGreen=green;
        myBlue=blue;
        myAlpha=alpha;
    }
    void setColor(XColor theColor){
        myRed=theColor.Red();
        myGreen=theColor.Green();
        myBlue=theColor.Blue();
        myAlpha=theColor.Alpha();
    }
    XColor Color(){
        return {myRed,myGreen,myBlue,myAlpha};
    }
    float Red(){
        return myRed;
    }
    float Green(){
        return myGreen;
    }
    float Blue(){
        return myBlue;
    }
    float Alpha(){
        return myAlpha;
    }
    std::string ColorNumerToStringWithPresision(float theNumber, uint thePresision){
        std::stringstream ss;
        //! Avoid scientific notations.
        ss<<std::fixed<<std::setprecision(thePresision);
        ss<<theNumber;
        return ss.str();
    }
    std::string ColorToString(){
        std::stringstream ss;
        //! Avoid scientific notations.
        ss<<std::fixed<<std::setprecision(3);
        ss<<myRed;
        ss<<",";
        ss<<myGreen;
        ss<<",";
        ss<<myBlue;
        ss<<",";
        ss<<myAlpha;
        return ss.str();
    }
    XColor StringToColor(std::string theString){
        float r=0.0,g=0.0,b=0.0,a=0.0;
        std::string str;
        std::vector<std::string> strVec;

        for(uint i=0; i<theString.size(); i++){
            if(theString.at(i)!=','){
                str.push_back(theString.at(i));
            }
            if(theString.at(i)==','){
                strVec.push_back(str);
                str.clear();
            }
        }
        strVec.push_back(str);

        r=std::stof(strVec.at(0));
        g=std::stof(strVec.at(1));
        b=std::stof(strVec.at(2));
        a=std::stof(strVec.at(3));

        XColor aColor={r,g,b,a};
        return aColor;
    }
    void animate(XColor theTarget, float theIncrement){
        float myRedTarget=theTarget.Red();
        float myGreenTarget=theTarget.Green();
        float myBlueTarget=theTarget.Blue();
        float myAlphaTarget=theTarget.Alpha();

        //! Color up.
        if(myRedTarget>myRed || myBlueTarget>myBlue || myGreenTarget>myGreen || myAlphaTarget>myAlpha){
            if(myRed+theIncrement<=myRedTarget){
                myRed+=theIncrement;
            } else {
                myRed=theTarget.Red();
            }
            if(myGreen+theIncrement<=myGreenTarget){
                myGreen+=theIncrement;
            }else {
                myGreen=theTarget.Green();
            }
            if(myBlue+theIncrement<=myBlueTarget){
                myBlue+=theIncrement;
            } else {
                myBlue=theTarget.Blue();
            }
            if(myAlpha+theIncrement<=myAlphaTarget){
                myAlpha+=theIncrement;
            } else {
                myAlpha=theTarget.Alpha();
            }
        }
        //! Color down.
        if(myRedTarget<myRed || myBlueTarget<myBlue || myGreenTarget<myGreen || myAlphaTarget<myAlpha){
            if(myRed-theIncrement>=myRedTarget){
                myRed-=theIncrement;
            } else {
                myRed=theTarget.Red();
            }
            if(myGreen-theIncrement>=myGreenTarget){
                myGreen-=theIncrement;
            }else {
                myGreen=theTarget.Green();
            }
            if(myBlue-theIncrement>=myBlueTarget){
                myBlue-=theIncrement;
            } else {
                myBlue=theTarget.Blue();
            }
            if(myAlpha-theIncrement>=myAlphaTarget){
                myAlpha-=theIncrement;
            } else {
                myAlpha=theTarget.Alpha();
            }
        }
    }
    bool EqualToColor(XColor theTarget){
        if(myRed==theTarget.Red() && myGreen==theTarget.Green() && myBlue==theTarget.Blue() && myAlpha==theTarget.Alpha()){
            return 1;
        }
        return 0;
    }
private:
    // Standard white.
    float myRed=1.0, myGreen=1.0, myBlue=1.0, myAlpha=1.0; // Alpha: 1.0=no opacy. 0.0=full opacy*
};

#endif // XCOLOR_H

/* OpenGl colorlist : https://web.archive.org/web/20180301041827/https://prideout.net/archive/colors.php#Floats
aliceblue = {0.941f, 0.973f, 1.000f};
antiquewhite = {0.980f, 0.922f, 0.843f};
aqua = {0.000f, 1.000f, 1.000f};
aquamarine = {0.498f, 1.000f, 0.831f};
azure = {0.941f, 1.000f, 1.000f};
beige = {0.961f, 0.961f, 0.863f};
bisque = {1.000f, 0.894f, 0.769f};
black = {0.000f, 0.000f, 0.000f};
blanchedalmond = {1.000f, 0.922f, 0.804f};
blue = {0.000f, 0.000f, 1.000f};
blueviolet = {0.541f, 0.169f, 0.886f};
brown = {0.647f, 0.165f, 0.165f};
burlywood = {0.871f, 0.722f, 0.529f};
cadetblue = {0.373f, 0.620f, 0.627f};
chartreuse = {0.498f, 1.000f, 0.000f};
chocolate = {0.824f, 0.412f, 0.118f};
coral = {1.000f, 0.498f, 0.314f};
cornflowerblue = {0.392f, 0.584f, 0.929f};
cornsilk = {1.000f, 0.973f, 0.863f};
crimson = {0.863f, 0.078f, 0.235f};
cyan = {0.000f, 1.000f, 1.000f};
darkblue = {0.000f, 0.000f, 0.545f};
darkcyan = {0.000f, 0.545f, 0.545f};
darkgoldenrod = {0.722f, 0.525f, 0.043f};
darkgray = {0.663f, 0.663f, 0.663f};
darkgreen = {0.000f, 0.392f, 0.000f};
darkgrey = {0.663f, 0.663f, 0.663f};
darkkhaki = {0.741f, 0.718f, 0.420f};
darkmagenta = {0.545f, 0.000f, 0.545f};
darkolivegreen = {0.333f, 0.420f, 0.184f};
darkorange = {1.000f, 0.549f, 0.000f};
darkorchid = {0.600f, 0.196f, 0.800f};
darkred = {0.545f, 0.000f, 0.000f};
darksalmon = {0.914f, 0.588f, 0.478f};
darkseagreen = {0.561f, 0.737f, 0.561f};
darkslateblue = {0.282f, 0.239f, 0.545f};
darkslategray = {0.184f, 0.310f, 0.310f};
darkslategrey = {0.184f, 0.310f, 0.310f};
darkturquoise = {0.000f, 0.808f, 0.820f};
darkviolet = {0.580f, 0.000f, 0.827f};
deeppink = {1.000f, 0.078f, 0.576f};
deepskyblue = {0.000f, 0.749f, 1.000f};
dimgray = {0.412f, 0.412f, 0.412f};
dimgrey = {0.412f, 0.412f, 0.412f};
dodgerblue = {0.118f, 0.565f, 1.000f};
firebrick = {0.698f, 0.133f, 0.133f};
floralwhite = {1.000f, 0.980f, 0.941f};
forestgreen = {0.133f, 0.545f, 0.133f};
fuchsia = {1.000f, 0.000f, 1.000f};
gainsboro = {0.863f, 0.863f, 0.863f};
ghostwhite = {0.973f, 0.973f, 1.000f};
gold = {1.000f, 0.843f, 0.000f};
goldenrod = {0.855f, 0.647f, 0.125f};
gray = {0.502f, 0.502f, 0.502f};
green = {0.000f, 0.502f, 0.000f};
greenyellow = {0.678f, 1.000f, 0.184f};
grey = {0.502f, 0.502f, 0.502f};
honeydew = {0.941f, 1.000f, 0.941f};
hotpink = {1.000f, 0.412f, 0.706f};
indianred = {0.804f, 0.361f, 0.361f};
indigo = {0.294f, 0.000f, 0.510f};
ivory = {1.000f, 1.000f, 0.941f};
khaki = {0.941f, 0.902f, 0.549f};
lavender = {0.902f, 0.902f, 0.980f};
lavenderblush = {1.000f, 0.941f, 0.961f};
lawngreen = {0.486f, 0.988f, 0.000f};
lemonchiffon = {1.000f, 0.980f, 0.804f};
lightblue = {0.678f, 0.847f, 0.902f};
lightcoral = {0.941f, 0.502f, 0.502f};
lightcyan = {0.878f, 1.000f, 1.000f};
lightgoldenrodyellow = {0.980f, 0.980f, 0.824f};
lightgray = {0.827f, 0.827f, 0.827f};
lightgreen = {0.565f, 0.933f, 0.565f};
lightgrey = {0.827f, 0.827f, 0.827f};
lightpink = {1.000f, 0.714f, 0.757f};
lightsalmon = {1.000f, 0.627f, 0.478f};
lightseagreen = {0.125f, 0.698f, 0.667f};
lightskyblue = {0.529f, 0.808f, 0.980f};
lightslategray = {0.467f, 0.533f, 0.600f};
lightslategrey = {0.467f, 0.533f, 0.600f};
lightsteelblue = {0.690f, 0.769f, 0.871f};
lightyellow = {1.000f, 1.000f, 0.878f};
lime = {0.000f, 1.000f, 0.000f};
limegreen = {0.196f, 0.804f, 0.196f};
linen = {0.980f, 0.941f, 0.902f};
magenta = {1.000f, 0.000f, 1.000f};
maroon = {0.502f, 0.000f, 0.000f};
mediumaquamarine = {0.400f, 0.804f, 0.667f};
mediumblue = {0.000f, 0.000f, 0.804f};
mediumorchid = {0.729f, 0.333f, 0.827f};
mediumpurple = {0.576f, 0.439f, 0.859f};
mediumseagreen = {0.235f, 0.702f, 0.443f};
mediumslateblue = {0.482f, 0.408f, 0.933f};
mediumspringgreen = {0.000f, 0.980f, 0.604f};
mediumturquoise = {0.282f, 0.820f, 0.800f};
mediumvioletred = {0.780f, 0.082f, 0.522f};
midnightblue = {0.098f, 0.098f, 0.439f};
mintcream = {0.961f, 1.000f, 0.980f};
mistyrose = {1.000f, 0.894f, 0.882f};
moccasin = {1.000f, 0.894f, 0.710f};
navajowhite = {1.000f, 0.871f, 0.678f};
navy = {0.000f, 0.000f, 0.502f};
oldlace = {0.992f, 0.961f, 0.902f};
olive = {0.502f, 0.502f, 0.000f};
olivedrab = {0.420f, 0.557f, 0.137f};
orange = {1.000f, 0.647f, 0.000f};
orangered = {1.000f, 0.271f, 0.000f};
orchid = {0.855f, 0.439f, 0.839f};
palegoldenrod = {0.933f, 0.910f, 0.667f};
palegreen = {0.596f, 0.984f, 0.596f};
paleturquoise = {0.686f, 0.933f, 0.933f};
palevioletred = {0.859f, 0.439f, 0.576f};
papayawhip = {1.000f, 0.937f, 0.835f};
peachpuff = {1.000f, 0.855f, 0.725f};
peru = {0.804f, 0.522f, 0.247f};
pink = {1.000f, 0.753f, 0.796f};
plum = {0.867f, 0.627f, 0.867f};
powderblue = {0.690f, 0.878f, 0.902f};
purple = {0.502f, 0.000f, 0.502f};
red = {1.000f, 0.000f, 0.000f};
rosybrown = {0.737f, 0.561f, 0.561f};
royalblue = {0.255f, 0.412f, 0.882f};
saddlebrown = {0.545f, 0.271f, 0.075f};
salmon = {0.980f, 0.502f, 0.447f};
sandybrown = {0.957f, 0.643f, 0.376f};
seagreen = {0.180f, 0.545f, 0.341f};
seashell = {1.000f, 0.961f, 0.933f};
sienna = {0.627f, 0.322f, 0.176f};
silver = {0.753f, 0.753f, 0.753f};
skyblue = {0.529f, 0.808f, 0.922f};
slateblue = {0.416f, 0.353f, 0.804f};
slategray = {0.439f, 0.502f, 0.565f};
slategrey = {0.439f, 0.502f, 0.565f};
snow = {1.000f, 0.980f, 0.980f};
springgreen = {0.000f, 1.000f, 0.498f};
steelblue = {0.275f, 0.510f, 0.706f};
tan = {0.824f, 0.706f, 0.549f};
teal = {0.000f, 0.502f, 0.502f};
thistle = {0.847f, 0.749f, 0.847f};
tomato = {1.000f, 0.388f, 0.278f};
turquoise = {0.251f, 0.878f, 0.816f};
violet = {0.933f, 0.510f, 0.933f};
wheat = {0.961f, 0.871f, 0.702f};
white = {1.000f, 1.000f, 1.000f};
whitesmoke = {0.961f, 0.961f, 0.961f};
yellow = {1.000f, 1.000f, 0.000f};
yellowgreen = {0.604f, 0.804f, 0.196f};
*/

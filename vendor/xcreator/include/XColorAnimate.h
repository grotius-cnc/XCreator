#ifndef XCOLORANIMATE_H
#define XCOLORANIMATE_H

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

/*
        //! Implementation example.
        //! #include <XColorAnimate.h>
        //! Init.
        myAnimate=new XColorAnimate(20);
        myAnimate->setAnimationColors({0.1,0.1,0.1,0.9},{0.5,0.5,0.5,0.9});
        myAnimate->setIncrement(0.05);
        myAnimate->startTimer(1);
        //! Thread.
        //! At a button press:
        myAnimate->startAnimation();
        //! Set the button color:
        XColor theAnimatedColor=myAnimate->update();

        private:
        XColorAnimate *myAnimate;
*/

#include <XTimer.h>
#include <XColor.h>
#include <iostream>

//! Class to perform a color animation.
//! There is a start color, a end color. The animation will go from starcolor to endcolor and to startcolor again.
class XColorAnimate {
public:
    //! Constructor, setting the timer interval time=20 ms.
    XColorAnimate(float theInterval){
        myTimer=new XTimer;
        myTimer->setIntervalMs(theInterval);
        myTimer->startTimer(1);
    }
    //! Empty destructor. SetIntervalMs and startTimer has to be done manually afterwards.
    ~XColorAnimate(){}
    //! Set the start color, end color of the color animation.
    void setAnimationColorsStageOne(XColor theColorLow, XColor theColorHigh){
        myColorStageOneLow.setColor(theColorLow);
        myColorStageOneHigh.setColor(theColorHigh);
        //! Startup color of this widget.
        myColor.setColor(theColorLow.Color());
    }
    //! Set the start color, end color of the color animation.
    void setAnimationColorsStageTwo(XColor theColorHigh){
        myColorStageTwoHigh.setColor(theColorHigh);
    }
    //! Start or stop the timer.
    void startTimer(bool theStatus){
        myTimer->startTimer(theStatus);
    }
    //! Set the color increment value.
    void setIncrementStageOne(float theIncrement){
        myIncrementStageOne=theIncrement;
    }
    //! Set the color increment value.
    void setIncrementStageTwo(float theIncrement){
        myIncrementStageTwo=theIncrement;
    }
    //! Start the animation. For example at a mouse press.
    void AnimationStageOne(bool theStatus){
        myStageOne=theStatus;
        myOneTop=0;
        myOneLow=0;
    }
    //! Start the animation. For example at a mouse press.
    void startAnimationStageTwo(bool theStatus){
        myStageTwo=theStatus;
        myTwoTop=0;
        myTwoLow=0;
    }
    //! Add to a thread.
    void update(){
        myTimer->update();

        //! Perform a action at a certain timestamp.
        if(myTimer->IntervalReached()){
            if(!myStageTwo){
                //! Stage one, continious hover.
                if(myStageOne && !myOneTop){
                    //! Increment.
                    myColor.animate(myColorStageOneHigh.Color(),myIncrementStageOne);
                    //! Finished?
                    myOneTop=myColor.EqualToColor(myColorStageOneHigh.Color());
                }
                //! Decrement cycle.
                if(!myStageOne && !myOneLow){
                    //! Decrement.
                    myColor.animate(myColorStageOneLow.Color(),myIncrementStageOne);
                    //! Finished?
                    myOneLow=myColor.EqualToColor(myColorStageOneLow.Color());
                }
            }
            //! Stage two, oneshot button press.
            if(myStageTwo && !myTwoTop){
                //! Increment.
                myColor.animate(myColorStageTwoHigh.Color(),myIncrementStageTwo);
                //! Finished?
                myTwoTop=myColor.EqualToColor(myColorStageTwoHigh.Color());
            }
            //! Decrement cycle.
            if(myTwoTop){
                //! Decrement.
                myColor.animate(myColorStageOneHigh.Color(),myIncrementStageTwo);
                //! Finished?
                bool myFinished=myColor.EqualToColor(myColorStageOneHigh.Color());
                if(myFinished){
                    myStageTwo=0;
                    myTwoTop=0;
                }
            }
        }
    }
    //! Get the animated color after the update is done.
    XColor Color(){
        return myColor;
    }
private:
    XTimer *myTimer;
    XColor myColorStageOneLow, myColorStageOneHigh, myColorStageTwoHigh, myColor;
    float myIncrementStageOne=0, myIncrementStageTwo=0;
    bool myOneTop=0, myTwoTop=0, myOneLow=0, myTwoLow=0, myStageOne=0, myStageTwo=0;
};
#endif



















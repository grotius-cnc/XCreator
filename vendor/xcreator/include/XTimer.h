#ifndef XTIMER_H
#define XTIMER_H

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
        //! Include.
        #include <XTimer.h>
        //! Init.
        myTimer=new XTimer();
        myTimer->setIntervalMs(20);
        myTimer->startTimer();
        //! Thread.
        myTimer->update();
        if(myTimer->IntervalReached()){
               std::cout<<"interval reached"<<std::endl;
        }
        private:
        XTimer *myTimer;
*/

#include <chrono>

//! Class to do timer cq stopwatch operations.
class XTimer {
public:
    //! Empty constructor. setWindow or parent afterwards.
    XTimer(){}
    //! Empty destructor.
    ~XTimer(){}
    //! Add to thread.
    void update(){
        //! If timer is started and setInvertalMs is set>0, check when to set the interval state to high.
        if(myStart && !myStop && myInterval>0 && !myIntervalState){
            if(DurationFromStart()>myInterval){
                myIntervalState=1;
                start = std::chrono::high_resolution_clock::now();
            }
        }
    }
    //! Start the timer.
    void startTimer(bool theStatus){
        if(theStatus){
            start = std::chrono::high_resolution_clock::now();
            myStart=1;
        } else {
            end = std::chrono::high_resolution_clock::now();
            myStop=1;
        }
    }
    //! Timer is active.
    bool TimerActive(){
        if(myStart){
            return 1;
        }
        if(myStop){
            return 0;
        }
        return 0;
    }
    //! Reset start, stop triggers.
    void stopTimer(){
        myStart=0;
        myStop=0;
    }
    //! Interval in milliSeconds [ms].
    void setIntervalMs(float theValue){
        myInterval=theValue;
    }
    //! Return the interval state and reset for next request.
    bool IntervalReached(){
        bool result=myIntervalState;
        if(myIntervalState){ //! Reset the interval state after the request.
            myIntervalState=0;
        }
        return result;
    }
    //! Return the time from start in millisecond [ms].
    float DurationFromStart(){
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start).count();
    }
    //! Return stop-start in millisecond [ms].
    float DurationStartStop(){
        return (end-start).count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    bool myStart=0, myStop=0;
    float myInterval=0;
    bool myIntervalState=0;
};
#endif


















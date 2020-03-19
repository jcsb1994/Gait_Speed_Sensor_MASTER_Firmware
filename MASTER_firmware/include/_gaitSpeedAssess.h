#ifndef GAIT_SPEED_ASSESS_H
#define GAIT_SPEED_ASSESS_H

#include "main.h"

/*
Some data needs to be shared via bluetooth with both devices. It is the case for: exact distance and test type

RFID triggers tof, bluetooth used to check if the other device  has an ungoing (identified this tag first) reading and time is stored as start time if not, else as end time
*/

class gaitSpeedAssess
{
private:
    uint8_t mTestType = 5; // 3 possible types; 3mWT, 4mWT or 5mWT
    unsigned long mStartTime;
    bool mCalculatedFlag;
    unsigned long mLastSpeed;
    

public:
    int exactDistance = 500; // Takes values from 3 to 5 meters: 300 to 500 in cm
    bool BT_flag;   //flags reception of BT sensor reading (only without RFID IDs since only 1 reading at a time)
    bool BTcalibFlag;
    bool continuous;    // Flags when we are in continuous mode, not caring about RFID reading and staying in ToF mode

    gaitSpeedAssess() {} //ctor
    uint8_t getTestType()
    {
        return mTestType;
    }
    void setTestTypeUp()
    {
        //mTestType = 5;
        if (mTestType < 5)
            mTestType++;
        //Serial.println(mTestType);
    }
    void setTestTypeDown()
    {
        if (mTestType > 3)
            mTestType--;
        //Serial.println(mTestType);
    }
    void setStartTime()
    {
        mStartTime = millis();
    }
    bool hasBegun()
    {
        if (mStartTime)
            return 1;
        else
            return 0;
    }

    bool isDone() {
        if(mCalculatedFlag)
        {  
            return 1;
        }
        else return 0;
    }

    void computeSpeed();

    unsigned long getSpeed()
    {
        return mLastSpeed;
    }

    void reset()
    {
        //No start time, hasbegun will return false
        mStartTime = 0;
        // BT flag 0, received packets will start a new reading
        BT_flag = 0;
        //final flag reset, computespeed will work again
        mCalculatedFlag = 0;
    }
};

extern gaitSpeedAssess gait_assessment;

#endif

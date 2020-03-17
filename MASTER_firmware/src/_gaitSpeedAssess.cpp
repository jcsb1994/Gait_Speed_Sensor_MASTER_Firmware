
#include "_gaitSpeedAssess.h"

void gaitSpeedAssess::computeSpeed()
{
    if (!mCalculatedFlag)
    {
        unsigned long chrono = millis() - mStartTime;
        mCalculatedFlag++;
        mLastSpeed = chrono;
        //Serial.println();
        
         //Serial.println(gait_assessment.hasBegun());
        mStartTime = 0;
        //Serial.println(gait_assessment.hasBegun());
        //Serial.println("calculated");
    }

}

gaitSpeedAssess gait_assessment;

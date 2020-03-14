
#include "_gaitSpeedAssess.h"

unsigned long gaitSpeedAssess::computeSpeed()
{
    if (!mCalculatedFlag)
    {
        unsigned long chrono = millis() - mStartTime;
        mCalculatedFlag++;
        mLastSpeed = chrono;
        Serial.println();
        Serial.println(chrono);
        return chrono;
    }
    else
        return 0;
}

gaitSpeedAssess gait_assessment;

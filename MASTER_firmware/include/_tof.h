#ifndef _TOF_H
#define _TOF_H

#include "main.h"
#include <VL53L1X.h>

class TOF
{
private:
  VL53L1X *linked_sensor;
  // Debounce variables
  int currentReading;
  int lastReading;
  bool maybeFlag;
  int integrator;
  bool tof_status;

  // Calibration variables
  
  bool calibrationFlag;
  int minimumClearValue;
  

public:
  TOF(VL53L1X &sensor_to_link) : linked_sensor(&sensor_to_link)   //ctor
  {
  }
  void init();    // Initialize the TOF sensor

  void calibrate(); // calibrates with current wall distance before entering measurement mode
  bool isCalibrationDone;

  bool isCalibrated() {
    return calibrationFlag;
  }

  void debounce();  // debounces readings to determine if blocked or clear

  bool getStatus()  // returns 1 for blocked or 0 for clear
  {
    return tof_status;
  }

  bool flag;  // Marks when it has been read in current speed assessment
};

extern VL53L1X masterSensor;
extern TOF myMasterSensor;

void tof_setup();

#endif
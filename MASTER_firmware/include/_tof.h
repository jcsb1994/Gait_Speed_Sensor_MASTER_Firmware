#ifndef _TOF_H
#define _TOF_H

#include "main.h"
#include <VL53L1X.h>

class TOF
{
private:
  int currentReading;
  int lastReading;
  bool maybeFlag;
  int integrator;
  bool tof_status;
  VL53L1X *linked_sensor;

public:
  TOF(VL53L1X &sensor_to_link):
    linked_sensor(&sensor_to_link)
  {}
  void debounce();
  void init();
  bool getStatus() {
    return tof_status;
  }
  bool flag;
};


extern VL53L1X masterSensor;
extern TOF myMasterSensor;

void tof_setup();

#endif
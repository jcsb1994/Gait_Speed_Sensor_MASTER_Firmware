#include "_tof.h"

#define THRESHOLD 400
#define UBSTRUCTED_MAXIMUM 3
#define CLEAR_MAXIMUM -3
#define PATH_UBSTRUCTED 1
#define PATH_CLEAR 0

// TOF class to give proper measurement methods to each VL53L1X

void TOF::debounce()
{
  currentReading = linked_sensor->read(); //get the newest reading
  //Serial.println(currentReading);

  if (lastReading - currentReading > THRESHOLD) //if last was bigger, someone might be in front
  {
    if (integrator < UBSTRUCTED_MAXIMUM)
    {
      integrator++;
    }
  }
  else if (currentReading - lastReading > THRESHOLD) //if now is bigger, someone might have left
  {
    if (integrator > CLEAR_MAXIMUM)
    {
      integrator--;
    }
  }
  else if (integrator > 0 /*&& integrator < UBSTRUCTED_MAXIMUM*/)
    integrator--;
  else if (integrator < 0 /*&& integrator > CLEAR_MAXIMUM*/)
    integrator++;

  if (integrator >= UBSTRUCTED_MAXIMUM)
  {
    integrator = 0; // Defensive code if integrator got corrupted
    tof_status = PATH_UBSTRUCTED;
  }

  if (integrator <= CLEAR_MAXIMUM)
  {
    integrator = 0; // Defensive code if integrator got corrupted
    tof_status = PATH_CLEAR;
  }

  (integrator) ? (maybeFlag++) : (maybeFlag = 0, lastReading = currentReading);
}

void TOF::init()
{
  linked_sensor->init();
  linked_sensor->setTimeout(500);
  linked_sensor->setDistanceMode(VL53L1X::Long);
  linked_sensor->setMeasurementTimingBudget(50000);
  linked_sensor->startContinuous(50);
}

VL53L1X masterSensor;
TOF myMasterSensor(masterSensor);

#define sensorShutPin 2

void tof_setup()
{

  //Serial.begin(9600);
  Wire.begin();
  //Wire.beginTransmission(0x29);
  //pinMode(sensorShutPin, OUTPUT);
  Wire.setClock(400000); // use 400 kHz I2C

  myMasterSensor.init();
  //digitalWrite(sensorShutPin, HIGH);

  /*
  sensor.init(); //resets address back to default
  sensor2.init();

  digitalWrite(sensorShutPin, LOW); //shuts down sensor1, talk to sensor2
  delay(1);
  sensor2.setAddress(0x25);
  Serial.println(sensor2.getAddress());
  digitalWrite(sensorShutPin, HIGH);
  Serial.println(sensor.getAddress());

   mySensor.init();  
  finalSensor.init();
*/
}
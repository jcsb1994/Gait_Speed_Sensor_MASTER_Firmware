#include "_tof.h"

#define THRESHOLD 300
#define UBSTRUCTED_MAXIMUM 3
#define CLEAR_MAXIMUM -3
#define PATH_UBSTRUCTED 1
#define PATH_CLEAR 0

// TOF class to give proper measurement methods to each VL53L1X

#define CALIB_READINGS 20
#define MAX_CALIB_ATTEMPTS 5
void TOF::calibrate()
{
  calibrationFlag = 0; //reset last calibration results

  int curr;
  int max = linked_sensor->read();  // Max to make sure the minimum clear value is not due to someone blocking during calib
  uint8_t nAttempts;
  do
  {
    // Serial.println("trying calib");
    nAttempts++;

    for (int i = 0; i < CALIB_READINGS; i++)
    {
      curr = linked_sensor->read();
      minimumClearValue = curr;
      max = curr;

      if (curr < minimumClearValue)
        minimumClearValue = curr;
      if (curr > max)
        max = curr;
      delay(100);
    }
      Serial.println(minimumClearValue);
        Serial.println();
        delay(700);

  } while ((max - minimumClearValue) > 800 && nAttempts < MAX_CALIB_ATTEMPTS); // Do again if more than 800 difference between calib readings
  // Serial.println("calib done");

  if (nAttempts < MAX_CALIB_ATTEMPTS)
    calibrationFlag = 1; // Succesful calib
  else
  {
    calibrationFlag = 0;
  }

}

void TOF::debounce()
{
  currentReading = linked_sensor->read(); //get the newest reading

  //Serial.println(currentReading);

  if (lastReading - currentReading > THRESHOLD && currentReading < minimumClearValue) //if last was bigger, someone might be in front
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
  //Serial.println(integrator);
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
#ifndef MAIN_H
#define MAIN_H

// Arduino libraries
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

// App setup
#include "app_config.h"
#include "addons.h"

// Classes for embedded projects
#include "74HC165.h"
#include "tact.h"
#include "menu.h"
#include "FSM.h"

#include "functions_config.h"  //Includes application's custom functions for FSM, menu and tact

// Atmega328p additional operations
#include "Timers.h"
#include "sleep.h"


/*####################################################################################################
    Add your application specific includes here
####################################################################################################*/

#include "_tof.h"
#include "_gaitSpeedAssess.h"
#include "_HC05.h"



#endif // MAIN_H
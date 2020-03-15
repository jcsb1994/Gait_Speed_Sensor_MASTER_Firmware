#include "main.h"

tact upPin(4);
tact selectPin(3); //should be 3
tact downPin(5);
tact rightPin(6);
tact leftPin(7);

ISR(WDT_vect)
{
  upPin.timerCount();
  selectPin.timerCount();
  leftPin.timerCount();
  rightPin.timerCount();
  downPin.timerCount();
}

void setup()
{
  Serial.begin(9600); 
  BTserial.begin(9600);

  leftPin.setFunctions(left_r, left_h);
  upPin.setFunctions(up_r, up_h);
  selectPin.setFunctions(sel_r, sel_h);
  downPin.setFunctions(down_r, down_h);
  rightPin.setFunctions(ri_r, ri_h);


  WDT_setup();
  sleep_setup();

  lcd_setup();
  tof_setup();
  myFSM.init();
}

void loop()
{
  //Do State  
  myFSM.doState();

  // Check for incoming events
  read_BT_events();

  selectPin.poll(NOT_DEBOUNCED);
  downPin.poll(NOT_DEBOUNCED);
  leftPin.poll(NOT_DEBOUNCED);
  upPin.poll(NOT_DEBOUNCED);
  rightPin.poll(NOT_DEBOUNCED);

  selectPin.activate();
  downPin.activate();
  leftPin.activate();
  upPin.activate();
  rightPin.activate();

  //activate_sleep();
}

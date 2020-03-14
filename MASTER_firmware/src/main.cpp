#include "main.h"

input_shift_register buttons_shift;

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
  //tact::timerCount(); // Very important to use this version when not using simultaneous presses (changes long press period)
  //Serial.println((int)&selectPin.hold_ptr, HEX);
}

/*
//example use of timer 1
ISR(TIMER1_COMPA_vect)
{
  TCNT1 = 0;
  PORTD ^= (1 << timerLedPin);
  selectPin.debounce(); // Debounce is useful when not sleeping (i.e. when an timer ISR can handle it)
}
*/

void setup()
{
  Serial.begin(9600); //Serial.begin(38400); // Speed to comm with HC05
  BTserial.begin(9600);
  Serial.println("fuck you");

  //pinMode(ledPin, OUTPUT);
  //pinMode(LedPin2, OUTPUT);
  //pinMode(LedPin3, OUTPUT);

  leftPin.setFunctions(left_r, left_h);
  upPin.setFunctions(up_r, up_h);
  selectPin.setFunctions(sel_r, sel_h);
  downPin.setFunctions(down_r, down_h);
  rightPin.setFunctions(ri_r, ri_h);

  input_shift_reg_SPI_setup();
  WDT_setup();
  //timer1_setup();
  sleep_setup();
  lcd_setup();
  tof_setup();
  myFSM.init();
}

void loop()
{
send_byte_BT(ENTER_MEASURING_MODE_MESSAGE);

  
  myFSM.doState();

  //shift_reg_snapshot();
  //buttons_shift.data = transfer_shift_reg_data();

  selectPin.poll(NOT_DEBOUNCED);
  downPin.poll(NOT_DEBOUNCED);
  leftPin.poll(NOT_DEBOUNCED);
  upPin.poll(NOT_DEBOUNCED); // Do not debounce if using sleep!
  rightPin.poll(NOT_DEBOUNCED);

  selectPin.activate();
  downPin.activate();
  leftPin.activate();
  upPin.activate();
  rightPin.activate();

  //activate_sleep();
}

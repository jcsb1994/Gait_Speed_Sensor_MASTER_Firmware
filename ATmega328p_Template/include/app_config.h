#ifndef APP_CONFIG_H
#define APP_CONFIG_H


/*##################################################################
* USED PINS ON THE ATMEGA328P
##################################################################*/

//#define ledPin 8
//#define LedPin2 9
//#define LedPin3 10

//74HC165 input shift register
#define LOAD_CONNECTION 11
#define LOAD_PIN_PORT_DATA_DIRECTION_REG DDRD
#define LOAD_PIN_PORT_STATE_REG PORTD

/********** ST7789 OLED SPI pins ***********/
#define TFT_CS 10 // define chip select pin
#define TFT_DC 9  // define data/command pin
#define TFT_RST 8 // define reset pin, or set to -1 and connect to Arduino RESET pin


/*##################################################################
* BASIC APP CONFIG
##################################################################*/

/***************************************************************************
 * BUTTONS (TACT SWITCHES) MACROS
 ***************************************************************************/

#define BUTTON_ACTIVE_STATE_CONFIG 1 // 1 for active HIGH buttons or 0 for active low

#define SHORT_BUTTON_PRESS_CONFIG 0        // 1 to turn ON functionality for short button presses
#define BUTTON_RELEASE_CONFIG 1             // 1 to turn ON functionality for button releases
#define LONG_BUTTON_PRESS_CONFIG 1       // 1 to turn ON functionality for long button presses
#define RELEASE_AFTER_LONG_EFFECT_CONFIG 0 // 1 will trigger a release effect even after long press effects occured
#define SIMULTANEOUS_BUTTON_PRESSES_CONFIG 1

/* sleep stops millis() so if no timer is used and sleep is used, long press timings won't fit */

//TIMER FOR TIMERCOUNTER() FUNCTION ONLY (debounce can be called anywhere faster paced)
#define TIMERCOUNT_ISR_CONFIG WDT_USED // Set up if there is a timer ISR managing tact.timerCounter()
#define TACT_TIMER_PERIOD WDT_PERIOD   // Set up the period of the timer used for tact.timerCounter
#define LONG_PRESS_DELAY 1000          // Set up desired time before long presses are triggered in milliseconds

// Debouncing in main is too fast by default (adds a delay for running tact.debounce();)
#define DEBOUNCE_IN_MAIN 0 // Not created yet... Might not be useful

// Debounce algorithm macros (do not debounce if using sleep)
#define DEBOUNCE_TIME 0.3
#define SAMPLE_FREQUENCY 6



/***************************************************************************
 * Sleep
 * 
 * DO NOT DEBOUNCE BUTTONS WHEN SLEEP IS ACTIVE
 * 
 * TIMERS (EXCEPT WDT) ARE NOT GOING TO WORK IF SLEEP IS ACTIVE
 * (except if waking up is faster than the ISR)
 ***************************************************************************/

#define SLEEP_CONFIG 1

/***************************************************************************
 * WDT period
 * acceptable values in ms:
 * 16, 32, 64, 125, 250, 500, 1000, 2000, 4000 and 8000
 * leave any value if unused, do not undefine
 * 
 ***************************************************************************/

#define WDT_CONFIG 1
#define WDT_PERIOD 64 // WDT period in microseconds, or from other timer chosen

#define TIMER_ONE_CONFIG 0 // Should not be used if sleep is active (disactivate timers)
#define TIMER1_PERIOD
#define TIMER_ONE_PRESCALER

/*##################################################################
ADDONS : ADD HEADERS IF USING THOSE PARTS
##################################################################*/

/***************************************************************************
 * DS1307 RTC
 ***************************************************************************/
#define DS1307_CONFIG 0

/***************************************************************************
 * EXTERNAL EEPROM
 ***************************************************************************/
#define EXTERNAL_EEPROM_CONFIG 0

/***************************************************************************
 * ST7789 OLED display
 ***************************************************************************/
#define ST7789_CONFIG 0

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240

#define SCREEN_CENTER_X SCREEN_WIDTH / 2
#define SCREEN_CENTER_Y SCREEN_HEIGHT / 2

#define SCREEN_TEXT_PIXEL 30
#define SCREEN_TEXT_SIZE SCREEN_TEXT_PIXEL / 10
#define SCREEN_TEXT_ROWS SCREEN_HEIGHT / SCREEN_TEXT_PIXEL

/***************************************************************************
 * 4x20 LCD
 ***************************************************************************/

#define FOUR_LCD_CONFIG 1
#define LCD_I2C_ADDR 0x27 //0x3F

/*##################################################################
CONSTANT MACROS (DO NOT EDIT)
##################################################################*/

//possible ISRs
#define TIMER0_USED 1
#define TIMER1_USED 2
#define TIMER2_USED 3
#define WDT_USED 4

#define ITERATIONS_TO_LONG_PRESS_TRIGGER LONG_PRESS_DELAY / TACT_TIMER_PERIOD //calculates how many ISR fires needed for long press
#define MAXIMUM (DEBOUNCE_TIME * SAMPLE_FREQUENCY)                            //debounce algorith max samples

// End of File
#endif
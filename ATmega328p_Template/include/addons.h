#ifndef ADDONS_H
#define ADDONS_H

#include "main.h"

/*####################################################################################################
    EXTERNAL EEPROM
####################################################################################################*/

#if EXTERNAL_EEPROM_CONFIG

#define EEPROM_I2C_ADDR 80 //0x50
#define M_CELL_I2C_ADDR 20   //0x14

/***************************************************************************
 * writeTo function
 * 
 * This function writes 1 byte (8 bits)
 * to a 16 bits address on the EEPROM chip (24C_ series) 
 * 
 ***************************************************************************/

void writeTo(unsigned int cell_address, uint8_t wData);

/***************************************************************************
 * readFrom function
 * 
 * This function reads from a 16 bits address on the EEPROM chip (24C_ series) 
 * 
 ***************************************************************************/

uint8_t readFrom(unsigned int cell_address);

#endif

/*####################################################################################################
    DS1307 RTC
####################################################################################################*/

#if DS1307_CONFIG
// Add external libraries
#include <RTClib.h>

extern RTC_DS1307 rtc;

void DS1307_setup();

#endif

/*####################################################################################################
    4 X 20 LCD
####################################################################################################*/

#if FOUR_LCD_CONFIG

// Add libraries
#include <LCD.h>
#include <LiquidCrystal_I2C.h> // F Malpartida's NewLiquidCrystal library

//LCD to I2C pinout
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

#define LED_OFF 1
#define LED_ON 0

extern LiquidCrystal_I2C lcd;

void lcd_setup();

#endif

/*####################################################################################################
    ST7789 OLED
####################################################################################################*/

#if ST7789_CONFIG
// Add libraries
#include <Adafruit_ST7789.h> //includes Adafruit_GFX.h

extern Adafruit_ST7789 tft;

void tft_setup();

#endif

#endif //ADDON_H
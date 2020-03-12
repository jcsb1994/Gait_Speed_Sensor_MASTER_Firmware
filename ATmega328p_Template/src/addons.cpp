#include "addons.h"

/*####################################################################################################
   EXTERNAL EEPROM
####################################################################################################*/

#if EXTERNAL_EEPROM_CONFIG

void writeTo(unsigned int cell_address, uint8_t wData)
{
  Wire.beginTransmission(EEPROM_I2C_ADDR);
  Wire.write((int)(cell_address >> 8));
  Wire.write((int)(cell_address & 0xFF));
  Wire.write(wData);
  Wire.endTransmission();
  delay(100);
}

uint8_t readFrom(unsigned int cell_address)
{
  Wire.beginTransmission(EEPROM_I2C_ADDR);
  Wire.write((int)(cell_address >> 8));
  Wire.write((int)(cell_address & 0xFF));
  Wire.endTransmission();

  Wire.requestFrom(EEPROM_I2C_ADDR, 1);

  delay(10);

  uint8_t rData = 0;
  if (Wire.available())
  {
    rData = Wire.read();
  }

  return rData;
}

#endif

/*####################################################################################################
    DS1307 RTC
####################################################################################################*/

#if DS1307_CONFIG

RTC_DS1307 rtc;

void DS1307_setup()
{
  rtc.begin();
  rtc.adjust(DateTime(__DATE__, __TIME__));
  //REAL_TIME_CLOCK_NAME_CONFIG.adjust(DateTime(2016, 11, 19, 13, 45, 0)); // <----------------------SET TIME AND DATE: YYYY,MM,DD,HH,MM,SS
}

#endif

/*####################################################################################################
    4 X 20 LCD
####################################################################################################*/

#if FOUR_LCD_CONFIG

LiquidCrystal_I2C lcd(LCD_I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

void lcd_setup()
{
  lcd.begin(20, 4); // initialize the lcd
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  //lcd.setBacklight(LED_ON);  //turn on backlight
  lcd.backlight();     //Backlight ON if under program control
  lcd.setCursor(0, 0); //character 1 on line 0
  //lcd.print("Dummie code");
}

#endif

/*####################################################################################################
    ST7789 OLED
####################################################################################################*/

#if ST7789_CONFIG

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void tft_setup() // Put any ST7789 function needed for the setup code
{
  tft.init(240, 240, SPI_MODE2); // Init ST7789 display 240x240 pixel
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(3);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(true);
  tft.setCursor(0, 2 * SCREEN_TEXT_PIXEL);
  tft.print("Dummie text");
}

#endif
#include "menu.h"

/*####################################################################################################
    Menu:: config
####################################################################################################*/

//menu instance
menu myMenu(4);

//Set which characters to erase and to print when drawing cursor on screen
#define CURSOR_SIZE 2
void menu::printCursor()
{
    for (int i = 0; i < mRows; i++)
    {
        lcd.setCursor(0, i);
        lcd.print("  ");
    }

    lcd.setCursor(0, menu::cursorPos);
    lcd.print("->");
};

/*####################################################################################################
    Pages to print
####################################################################################################*/

void print_init_page()
{
    lcd.clear();
    myMenu.printCursor();
    lcd.setCursor(CURSOR_SIZE, INIT_SETUP_POS);
    lcd.print("Setup");
    lcd.setCursor(CURSOR_SIZE, INIT_START_POS);
    lcd.print("Start measuring");
};

void print_setup_page()
{
    lcd.clear();
    myMenu.printCursor();
    lcd.setCursor(CURSOR_SIZE, SETUP_TEST_TYPE_POS);
    lcd.print("Test dist: ");
    lcd.print(gait_assessment.getTestType());
    lcd.print("mWT");
    lcd.setCursor(CURSOR_SIZE, SETUP_EXACT_DISTANCE);
    lcd.print("Exact dist: ");
    lcd.print(gait_assessment.exactDistance);
    lcd.print("cm");
    lcd.setCursor(CURSOR_SIZE, SETUP_BT_PAIR_POS);
    lcd.print("BT pairing");
};

void print_tof_calib_page()
{
    lcd.clear();
    //myMenu.printCursor();
    lcd.setCursor(4, 0);
    lcd.print("calibrating..");
    lcd.setCursor(0, 1);
    lcd.print("Step aside of lasers");

    if (myMasterSensor.isCalibrationDone)
    {
        if (myMasterSensor.isCalibrated()  && gait_assessment.BTcalibFlag)
        {
            lcd.clear();
            lcd.print("Success!");
        }
        else
        {
            lcd.clear();
            lcd.print("Failed");
        }
    }
}

void print_wait_for_rfid_page()
{
    lcd.clear();
    //myMenu.printCursor();
    lcd.setCursor(5, 0);
    lcd.print("Waiting for");
    lcd.setCursor(7, 1);
    lcd.print("patients..");
}

void print_rfid_detected_page()
{
    //Serial.println("tof page");
    lcd.clear();
    //myMenu.printCursor();
    lcd.setCursor(CURSOR_SIZE + 2, 0);
    lcd.print("Patient near");
    lcd.setCursor(CURSOR_SIZE, 1);
    (gait_assessment.hasBegun() /* && (!myMasterSensor.flag != !finalSensor.flag)*/) ? (lcd.print("Reading..")) : (lcd.print("         "));
    if (gait_assessment.getSpeed())
    {
        lcd.setCursor(CURSOR_SIZE, 2);
        lcd.print("ID: ");
        lcd.print(myRFID.getUID());
        lcd.setCursor(CURSOR_SIZE, 3);
        lcd.print("measured: ");
        lcd.print(gait_assessment.getSpeed());
    }
}
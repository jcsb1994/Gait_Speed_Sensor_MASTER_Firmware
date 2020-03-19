#ifndef RFID_H
#define RFID_H

#include <MFRC522.h>
#include "main.h"

/*
 * 
 * All the resources for this project: https://randomnerdtutorials.com/
 * Modified by Rui Santos
 * 
 * Created by FILIPEFLOP
 * 
 */

#include <SPI.h>


#define SS_PIN 10
#define RST_PIN 9

//#define RFID_MAX 3

class Patient_RFID
{
private:
    MFRC522 *linked_RFID;
    unsigned char activeID[4];
    unsigned long last_RFID_read;
    unsigned char currUID;
    //unsigned char integrator;
    //bool patient_UID_flag;
    unsigned char UID_integrator;

public:
    Patient_RFID(MFRC522 &rfid_to_link) : linked_RFID(&rfid_to_link) {}
    void scanUIDs();
    void setup()
    {
        SPI.begin(); // Initiate  SPI bus
        linked_RFID->PCD_Init();
    }
    void setUID() {
        currUID = activeID[0];
    }
    unsigned char getUID() {
        return currUID;
    }
};

extern MFRC522 mfrc522; // Create MFRC522 instance.
extern Patient_RFID myRFID;
/*
void RFID_setup();

void isPatientNear();
// receive an hex value and store it as activeID

void sendActiveID();
*/
#endif
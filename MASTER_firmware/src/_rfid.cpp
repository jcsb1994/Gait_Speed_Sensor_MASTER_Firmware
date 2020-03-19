#include "_rfid.h"

//unsigned char activeID[4];
//unsigned long last_RFID_read;

#define LEFT_MAX 3

void Patient_RFID::scanUIDs()
{
    if (millis() - last_RFID_read > 200)
    {
        last_RFID_read = millis();
        if (linked_RFID->PICC_IsNewCardPresent() && linked_RFID->PICC_ReadCardSerial()) // If card is read, read the active
        {
            //Serial.print("act: ");
            UID_integrator = 0; // Reset count before being sure they left
            for (int i = 0; i < 4; i++)
            {
                activeID[i] = linked_RFID->uid.uidByte[i];
                //Serial.print(activeID[i]);
            }
            //Serial.println();

            //patient_UID_flag++;
            setUID();
            myFSM.setEvent(events::RFID_detected);
        }

        else
        {
            //Serial.println("fu");
            UID_integrator++;
            if (UID_integrator >= LEFT_MAX)
            {
                //patient_UID_flag = 0;
                memset(activeID, 0, sizeof(activeID));
                myFSM.setEvent(events::RFID_left);
                /*
                Serial.print("act: ");
                for (int i = 0; i < 4; i++)
                {
                    Serial.print(activeID[i]);
                }
                Serial.println();
                */
                setUID();
            }
        }
    }
}

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
Patient_RFID myRFID(mfrc522);

/*
void Patient_RFID::scanUIDs()
{
    if (millis() - last_RFID_read > 200)
    {
        Serial.println(integrator);
        if (linked_RFID->PICC_IsNewCardPresent() || linked_RFID->PICC_ReadCardSerial() && integrator < RFID_MAX) // If card is read, read the active
        {
            integrator++;
        }

        else if (!linked_RFID->PICC_IsNewCardPresent() && !linked_RFID->PICC_ReadCardSerial()&& integrator > 0)
        {
            integrator--;
        }

        if (integrator >= RFID_MAX)
        {
            for (int i = 0; i < 4; i++)
            {
                activeID[i] = linked_RFID->uid.uidByte[i];
                Serial.print(activeID[i]);
            }
            Serial.println();
        }

        else if (!integrator)
        {
            memset(activeID, 0, sizeof(activeID));
        }
    }
}
*/

/*
void RFID_setup()
{
    SPI.begin();        // Initiate  SPI bus
    mfrc522.PCD_Init(); // Initiate MFRC522
}

void isPatientNear()
{
    if (millis() - last_RFID_read > 200)
    {
        //    digitalWrite(INPUT_SHIFT_NPN, LOW); // Acts as a SPI chip select, shuts HC165 down to talk to RFID module
        //   delay(500);
        if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) // If card is read, read the active
        {
            for (int i = 0; i < 4; i++)
            {
                activeID[i] = mfrc522.uid.uidByte[i];
                Serial.print(activeID[i]);
            }
            Serial.println();
        }
        else
        {
            memset(activeID, 0, sizeof(activeID));
        }
        //  digitalWrite(INPUT_SHIFT_NPN, HIGH);
        //  last_RFID_read = millis();
    }
}

// receive an hex value and store it as activeID

void sendActiveID() //needs to send a flag that mentions we are talking about the RFID #, then the data.
{
    for (int i = 0; i < 4; i++)
    {
        Serial.print(activeID[1]);
    }
}

// Check for available data and

*/
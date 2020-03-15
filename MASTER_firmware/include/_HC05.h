#ifndef _HC05_H
#define _HC05_H

#include <SoftwareSerial.h>
extern SoftwareSerial BTserial; // SRX | STX

#include "main.h"


#define ENTER_MEASURING_MODE_MESSAGE 'a' // 97
#define RFID_RECOGNIZED_MESSAGE 'b'
#define TIME_MEASURED_MESSAGE 'c' 
#define TEST_RESULT_MILLISEC_MESSAGE 'd'

void testBT();

void read_BT_events();

void send_byte_BT(unsigned char message);

#endif
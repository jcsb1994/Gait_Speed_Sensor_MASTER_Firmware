#ifndef _HC05_H
#define _HC05_H

#include <SoftwareSerial.h>
extern SoftwareSerial BTserial; // SRX | STX

#include "main.h"

// Msgs to send to slave
#define ENTER_MEASURING_MODE_MESSAGE 'a' // 97
#define ENTER_CALIB_MESSAGE 'e'
#define TEST_RESULT_MILLISEC_MESSAGE 'd'
#define STOP_MEASURING_MESSAGE 'g'

// Msgs received from slave
#define CALIB_SUCCESSFUL_MESSAGE 'f'
#define RFID_RECOGNIZED_MESSAGE 'b'
#define TIME_MEASURED_MESSAGE 'c' 


void testBT();

void read_BT_events();

void send_byte_BT(unsigned char message);

#endif
#ifndef TACT_ACT_H
#define TACT_ACT_H

#include "main.h"

/*####################################################################################################
    Tact switch buttons actions (create a function for each) **in tact config cpp file
####################################################################################################*/

void empty();

// Up button
//void up_s();

void up_r();

void up_h();

// Select button
//void sel_s();

void sel_r();

void sel_h();

// Down button
//void down_s();

void down_r();

void down_h();

// Left button
//void left_s();

void left_r();

void left_h();

//
// Right button

void ri_r();

void ri_h();

/*####################################################################################################
    Pages to print (create a function for each) **in menu config cpp file
####################################################################################################*/

#define INIT_SETUP_POS 0
#define INIT_START_POS 2
void print_init_page();

#define SETUP_TEST_TYPE_POS 0
#define SETUP_EXACT_DISTANCE 1
#define SETUP_BT_PAIR_POS 2
void print_setup_page();

void print_tof_calib_page();

void print_wait_for_rfid_page();

void print_rfid_detected_page();

/*####################################################################################################
    State Machine (FSM) events (list all possible events here, STARTING WITH = 1)
####################################################################################################*/
enum events
{
    // Menu tact events
    select = 1,
    increment,
    decrement = 3,
    back,
    TOF_blocked,
    TOF_time_received,  //BT event
    calib_success_received,
    RFID_detected,
    speed_measured, //maybe?
    RFID_left
};

/*####################################################################################################
    State Machine (FSM) state handlers (create a function for each) **in FSM config cpp file
####################################################################################################*/

void INIT_stateHandler();

void SETUP_stateHandler();

void BT_PAIR_stateHandler();

void TOF_CALIB_stateHandler();

void WAIT_FOR_RFID_stateHandler();

void TOF_stateHandler();

#endif
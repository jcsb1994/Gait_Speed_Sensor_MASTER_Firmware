#include "FSM.h"

FSM myFSM;

// FSM events must be listed in functions_config.h

/*####################################################################################################
    setup which initial state for the State machine (and print its page)
####################################################################################################*/

void FSM::init()
{
    myFSM.setState(INIT_stateHandler);
    print_init_page();
}

/*####################################################################################################
    create your state handling functions for your FSM here
####################################################################################################*/

/***************************************************************************
 * States:
 * INIT, SETUP, WAIT_FOR_RFID, TOF, 
 * 
 ***************************************************************************/

void INIT_stateHandler()
{
    if (myFSM.getEvent() == events::select)
    {
        switch (myMenu.getCursorPos())
        {
        case INIT_SETUP_POS:
            print_setup_page();
            myMenu.setCurrentPage(print_setup_page); // Used because refreshPage() is used in this state
            myFSM.setState(SETUP_stateHandler);
            break;

        case INIT_START_POS:
            print_wait_for_rfid_page();
            myMenu.setCurrentPage(print_tof_calib_page);
            myFSM.setState(TOF_CALIB_stateHandler);
            break;

        default:
            break;
        }
    }
}

void SETUP_stateHandler()
{

    switch (myFSM.getEvent())
    {
    case events::back:
        print_init_page();
        myFSM.setState(INIT_stateHandler);
        break;

    case events::increment:
        switch (myMenu.getCursorPos())
        {
        case SETUP_TEST_TYPE_POS:

            gait_assessment.setTestTypeUp();
            gait_assessment.exactDistance = gait_assessment.getTestType() * 100;
            myMenu.refreshPage();
            break;

        case SETUP_EXACT_DISTANCE:
            gait_assessment.exactDistance++;
            myMenu.refreshPage();
            break;

        default:
            break;
        }
        break;

    case events::decrement:
        switch (myMenu.getCursorPos())
        {
        case SETUP_TEST_TYPE_POS:

            gait_assessment.setTestTypeDown();
            gait_assessment.exactDistance = gait_assessment.getTestType() * 100;
            myMenu.refreshPage();
            break;

        case SETUP_EXACT_DISTANCE:
            gait_assessment.exactDistance--;
            myMenu.refreshPage();
            break;

        default:
            break;
        }
        break;

    case events::select:
        if (myMenu.getCursorPos() == SETUP_BT_PAIR_POS)
            //go to BT menu
            //void print_wait_for_rfid_page();
            //myFSM.setState(WAIT_FOR_RFID_stateHandler);
            break;
        break;

    default:
        break;
    }
}

void TOF_CALIB_stateHandler()
{
    if (!myMasterSensor.isCalibrationDone)
    {
        print_tof_calib_page();
        send_byte_BT(ENTER_CALIB_MESSAGE);
        delay(2000);
        myMasterSensor.calibrate();
        myMasterSensor.isCalibrationDone++;
    }
    else
    {
        myMenu.refreshPage();
        delay(1000);
        if (myMasterSensor.isCalibrated() && gait_assessment.BTcalibFlag) // Success if both devices calibrated properly
        {
            print_wait_for_rfid_page();
            myFSM.setState(WAIT_FOR_RFID_stateHandler); // start measuring after calibration
        }
        else // calib has failed
        {
            print_init_page();
            myFSM.setState(INIT_stateHandler);
            send_byte_BT(STOP_MEASURING_MESSAGE); // slave starts measuring even if fails, so stop it if unsuccessful
        }
        myMasterSensor.isCalibrationDone = 0;
        gait_assessment.BTcalibFlag = 0;
        //Serial.println("bt calib reset");
    }
}

void WAIT_FOR_RFID_stateHandler()
{
    switch (myFSM.getEvent())
    {
    case events::back:
        print_init_page();
        send_byte_BT(STOP_MEASURING_MESSAGE);
        myFSM.setState(INIT_stateHandler);
        break;

    case events::RFID_detected:
        print_rfid_detected_page();
        myMenu.setCurrentPage(print_rfid_detected_page); // Used because refreshPage() is used in this state
        myFSM.setState(TOF_stateHandler);
        break;

    case events::select: // Pressing select gets you into continuous reading
        myFSM.setEvent(events::RFID_detected);
        break;

    default:
        break;
    }
}

void TOF_stateHandler()
{
    myMasterSensor.debounce(); // Read TOF sensor

    if (myMasterSensor.getStatus()) // If status is blocked, we measure time
    {
        if (!myMasterSensor.flag)
        {
            myMasterSensor.flag++;
            myFSM.setEvent(events::TOF_blocked);
        }
    }

    if (gait_assessment.isDone() && !myMasterSensor.getStatus()) // If speed calculated and this sensor isnt blocked anymore, reset
    {
        gait_assessment.reset();
        myMasterSensor.flag = 0;
        myMenu.refreshPage();
    }

    switch (myFSM.getEvent())
    {
    case events::back:
        print_init_page();
        myMasterSensor.flag = 0;
        gait_assessment.reset();
        send_byte_BT(STOP_MEASURING_MESSAGE);
        myFSM.setState(INIT_stateHandler);
        break;

    case events::select:
        myMasterSensor.flag = 0;
        gait_assessment.reset();
        myMenu.refreshPage();
        //Serial.println("reseted!");
        break;

    case events::speed_measured:
        myMenu.refreshPage();
        break;

    case events::TOF_time_received: // When time is received, save time (either start or finish)

        if (!gait_assessment.BT_flag)
            gait_assessment.BT_flag++;
        myFSM.setEvent(events::TOF_blocked);
        break;

    case events::TOF_blocked:

        (gait_assessment.hasBegun()) ? (gait_assessment.computeSpeed()) : (gait_assessment.setStartTime());
        myMenu.refreshPage();

        break;

    default:
        break;
    }
}

#ifndef FSM_H
#define FSM_H

#include "main.h"

class FSM
{

private:
    int incoming_event;

    void (*do_state)();

public:
    FSM() {}

    enum events : unsigned int;

    int getEvent() //used as output for tact switches
    {
        //if(incoming_event)Serial.print("ev "), Serial.println(incoming_event);
        int event = incoming_event;
        incoming_event = 0;
        return event;
    }

    void setEvent(int incomingEvent) //used as output for tact switches
    {
        incoming_event = incomingEvent;
    }

    void setState(void newStateHandler())
    {
        do_state = newStateHandler;
    }

    void doState()
    {
        do_state();
    }

    void init();
};

extern FSM myFSM;

#endif
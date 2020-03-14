#ifndef TACT_H
#define TACT_H

#include "main.h"

/*##################################################
            MACROS
##################################################*/

// Debounce macros
#define DEBOUNCED 1
#define NOT_DEBOUNCED 0
// Polling macros
#define SHORT_EFFECT_REQUIRED 1
#define RELEASE_EFFECT_REQUIRED 2
#define LONG_EFFECT_REQUIRED 3

/*##################################################
            DECLARATION
##################################################*/

struct input_shift_register
{
    bool not_used;
    int data;
    int *ptr_to_data;
};

class tact
{
public:
    tact(int assigned_pin);                              // Constructor
    tact(int assigned_pin, input_shift_register &shift); // Overloaded constructor for tacts linked to a shift register chip

    void debounce();
    void poll(bool debounce_flag);
    static int *pressOutput;


    void activate();
    void setFunctions(
#if SHORT_BUTTON_PRESS_CONFIG
        void short_press_function(void)
#if BUTTON_RELEASE_CONFIG || LONG_BUTTON_PRESS_CONFIG
        ,
#endif
#endif

#if BUTTON_RELEASE_CONFIG
        void release_press_function(void)
#if LONG_BUTTON_PRESS_CONFIG
        ,
#endif
#endif

#if LONG_BUTTON_PRESS_CONFIG
        void long_press_function(void)
#endif
        );

#if LONG_BUTTON_PRESS_CONFIG
#if SIMULTANEOUS_BUTTON_PRESSES_CONFIG
    void timerCount();
#else
    static void timerCount();
#endif
#endif // Long button presses

private:
    int pin;
    static int mCount;
    unsigned int mID;

    short state;

    bool input_shift_used;
    input_shift_register *input_shift_ptr;

    // Pointers to tact effect functions
    void (*hold_ptr)();
    void (*short_ptr)();
    void (*release_ptr)();

    // Debounce variables
    volatile unsigned int input; // Current state of the tact switch
    volatile unsigned int integrator;
    volatile bool now_debounced_input; // Output of the algorithm
    volatile bool last_debounced_input;

    // Press and long press variables (multiple simultaneous presses version)
#if SIMULTANEOUS_BUTTON_PRESSES_CONFIG
    volatile unsigned int tact_is_pressed; // Keeps track if button is pressed during poll
#if LONG_BUTTON_PRESS_CONFIG
    volatile bool long_effect_done;           // Flags when a long press was executed
#if TIMERCOUNT_ISR_CONFIG                     // If a timer is checking tact, can be used to count time
    volatile unsigned int long_press_counter; // Keeps count of how long the tact has been pressed for

#else // If No ISR, tact.TimerCount(); is not used and counts are handled by millis();
    volatile unsigned long last_press_millis;

#endif // TIMERCOUNT_ISR_CONFIG
#endif // LONG_BUTTON_PRESS_CONFIG

    // Press and long press variables (single press at a time version)
#else //no simultaneous button presses
    static unsigned int tact_is_pressed;    // Keeps track of which button is pressed during poll
#if LONG_BUTTON_PRESS_CONFIG
    static bool long_effect_done;           // Flags when a long press was executed

#if TIMERCOUNT_ISR_CONFIG // If a timer is checking tact, can be used to count time
    static unsigned int long_press_counter; // Keeps count of how long the tact has been pressed for

#else // If No ISR, tact.TimerCount(); is not used and counts are handled by millis();
    static unsigned long last_press_millis;

#endif // TIMERCOUNT_ISR_CONFIG
#endif // LONG_BUTTON_PRESS_CONFIG
#endif // SIMULTANEOUS_BUTTON_PRESSES_CONFIG
};

#endif // Header guard
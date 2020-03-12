#include "tact.h"

// Initialization of static variables
int tact::mCount = 0;
int *tact::pressOutput = 0;
#if SIMULTANEOUS_BUTTON_PRESSES_CONFIG == 0
unsigned int tact::tact_is_pressed = 0;
#if LONG_BUTTON_PRESS_CONFIG
unsigned int tact::long_press_counter = 0;
bool tact::long_effect_done = 0;
#endif
#endif

// Constructors
tact::tact(int assigned_pin) : pin(assigned_pin)
{
    mCount++;
    mID = mCount;
#if BUTTON_ACTIVE_STATE_CONFIG == 1
    pinMode(pin, INPUT);
#elif BUTTON_ACTIVE_STATE_CONFIG == 0
    pinMode(pin, INPUT_PULLUP);
#endif
}

tact::tact(int assigned_pin, input_shift_register &shift) : pin(assigned_pin), input_shift_ptr(&shift)
{
    mCount++;
    mID = mCount;
    input_shift_used++;
    //tact::input_shift_ptr = &shift;
}

// Functions
void tact::debounce()
{
    if (input_shift_used)
    {
        input = (input_shift_ptr->data & (1 << pin)) >> pin;
    }
    else
        input = digitalRead(pin);

    if (input == 0)
    {
        if (integrator > 0)
            integrator--;
    }
    else if (integrator < MAXIMUM)
        integrator++;

    if (integrator == 0)
        now_debounced_input = 0;
    else if (integrator >= MAXIMUM)
    {
        integrator = MAXIMUM; // Defensive code if integrator got corrupted
        now_debounced_input = 1;
    }
}

void tact::poll(bool debounce_flag) //accepts DEBOUNCED or NOT_DEBOUNCED
{

    if (debounce_flag == NOT_DEBOUNCED)
    {
        if (!input_shift_used)
            now_debounced_input = digitalRead(tact::pin);
        else
            now_debounced_input = ((input_shift_ptr->data & (1 << pin)) >> pin);
    }

/***************************************************************************
* Option 1: The button "pin" was just pressed.
* If it was LOW and now HIGH (active HIGH), action is activated and
* refresh flag is set to refresh the screen. The semaphore value is set
* to the current polled button.
***************************************************************************/
#if BUTTON_ACTIVE_STATE_CONFIG == 1
    if (now_debounced_input && !last_debounced_input && !tact_is_pressed)
    {
#elif BUTTON_ACTIVE_STATE_CONFIG == 0
    if (!now_debounced_input && last_debounced_input && !tact_is_pressed)
    {
#endif
        tact_is_pressed += mID;

#if !TIMERCOUNT_ISR_CONFIG
        last_press_millis = millis();
        //Serial.println(last_press_millis);
#endif

#if SHORT_BUTTON_PRESS_CONFIG == 1
        tact::state = SHORT_EFFECT_REQUIRED;
        //*pressOutput = (mID << 2) + state;

#endif
    }

    /***************************************************************************
  * Option 2: the button "pin" was just released.
  * ~ tact was marked as pressed on the last pull. Now 
  * check if buttons are active HIGH or LOW
  * if release is on, activate effect.
  * If debounced button is now LOW and was HIGH, its released so no long press effect is applied.
  ***************************************************************************/

#if BUTTON_ACTIVE_STATE_CONFIG == 1
    else if (last_debounced_input && !now_debounced_input && tact_is_pressed == mID)
    {
#elif BUTTON_ACTIVE_STATE_CONFIG == 0
    else if (!last_debounced_input && now_debounced_input && tact_is_pressed == mID)
    {
#endif

#if BUTTON_RELEASE_CONFIG

        if (tact_is_pressed)
        {

#if LONG_BUTTON_PRESS_CONFIG == 1 && !RELEASE_AFTER_LONG_EFFECT_CONFIG
            if (!long_effect_done) //if there was no long press. If there was, releasing will not trigger another effect
#endif
                tact::state = RELEASE_EFFECT_REQUIRED;
                //*pressOutput = (mID << 2) + state;
        }
#endif

#if LONG_BUTTON_PRESS_CONFIG == 1
        long_effect_done = 0;
        long_press_counter = 0;
#endif

        tact_is_pressed = 0;
    }

    /***************************************************************************
  * Option 3: Long press effect reached
  * (either counted in the timer with tact.timerCount) or with millis())
  * 
  * The long_press_counter has reached a treshold time value and we are
  * polling the right button, which is pressed and marked with the semaphore.
  ***************************************************************************/

#if LONG_BUTTON_PRESS_CONFIG

#if TIMERCOUNT_ISR_CONFIG
    else if (tact_is_pressed && !long_effect_done && long_press_counter >= ITERATIONS_TO_LONG_PRESS_TRIGGER)
    {
        //Serial.println(long_press_counter);
        long_press_counter = 0; // Stop counting, flag up
#else
    else if (tact_is_pressed && !long_effect_done && (millis() - last_press_millis) >= LONG_PRESS_DELAY)
    {
#endif

        state = LONG_EFFECT_REQUIRED;
        //*pressOutput = (mID << 2) + state;
        long_effect_done++;
    }
#endif

    /***************************************************************************
  * Mark the pressed button as read to prevent multiple readings
  ***************************************************************************/

    tact::last_debounced_input = tact::now_debounced_input;
}

void tact::setFunctions(
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
)
{
#if SHORT_BUTTON_PRESS_CONFIG
    short_ptr = short_press_function;
#endif

#if BUTTON_RELEASE_CONFIG
    release_ptr = release_press_function;
#endif

#if LONG_BUTTON_PRESS_CONFIG
    hold_ptr = long_press_function;
#endif
}

void tact::activate()
{
    if (state)
    {
        //Serial.println((int)&hold_ptr, HEX);
        switch (state)
        {
        case LONG_EFFECT_REQUIRED:
            //Serial.print("ID "),Serial.println(mID);
            hold_ptr();
            break;

        case SHORT_EFFECT_REQUIRED:
            short_ptr();
            break;

        case RELEASE_EFFECT_REQUIRED:
            release_ptr();
            //Serial.println(mID);
            break;

        default:
            break;
        }
        tact::state = 0;
    }
}

#if LONG_BUTTON_PRESS_CONFIG
void tact::timerCount()
{
    if (tact_is_pressed && !long_effect_done)
        long_press_counter++;
}
#endif
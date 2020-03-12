#include "Timers.h"

/*##################################################
            WDT
##################################################*/

#if WDT_CONFIG

volatile uint8_t wdt_counter; // Volatile is preferable when modified in WDT

void WDT_setup()
{
    WDTCSR = (24); // Change enable and WDE - also resets

    //prescalers only - get rid of the WDE and WDCE bit.

#if WDT_PERIOD == 8000
    WDTCSR = (0b100001); // 8 sec
#endif

#if WDT_PERIOD == 4000
    WDTCSR = (0b100000); // 4 sec
#endif

#if WDT_PERIOD == 1000
    WDTCSR = (6); // 1 sec
#endif

#if WDT_PERIOD == 125
    WDTCSR = (3); // 0,125 sec
#endif

#if WDT_PERIOD == 64
    WDTCSR = (2); //64 ms
#endif

#if WDT_PERIOD == 32
    WDTCSR = (1); //32 ms
#endif

#if WDT_PERIOD == 16
WDTCSR = (0);
#endif

    WDTCSR |= (1 << 6); //enable interrupt mode - WDT as an interrupt is useful to wake up from sleep
}

#endif

/*##################################################
            TIMER 1
##################################################*/

#if TIMER_ONE_CONFIG

void timer1_setup() {
  //TIMER 1 SETUP (used for debouncing)
  TCCR1A = 0; //timer 1 control register is reset as this is needed before we setup the prescaler for the

  //BITS 2:0 (CS12 TO CS10) OF TCCR1B USED TO SETUP PRESCALER AS NEEDED TO CHANGE TCNT1 SPEED
  TCCR1B |= (1 << CS12); // bit config as 0 0 1 gives a prescaler of 1
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);

  //RESET TCNT1 TO START COUNTING AFTER SETUP
  TCNT1 = 0;

  //SETUP DESIRED NUMBER OF CYCLES ON TCNT1 UNTIL INTERRUPT IS FIRED
  OCR1A = 1000;

  //ACTIVATE INTERRUPTS WITH OCR1A REGISTER (FIRE INTERRUPT WHEN TCNT1 VALUE MATCHES WITH IT)
  TIMSK1 = (1 << OCIE1A); //OCIE1A is the bit that sets up interrupts with OCR1A

  sei(); //activate global interrupts
}

#endif
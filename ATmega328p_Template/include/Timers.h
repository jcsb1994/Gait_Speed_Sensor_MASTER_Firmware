#ifndef WDT_H
#define WDT_H

#include "main.h"


/*##################################################
            WDT
##################################################*/

#if WDT_CONFIG

extern volatile uint8_t wdt_counter;

/***************************************************************************
 * WDT_setup function
 * This function sets the appropriate registers for WDT to be turned on.
 ***************************************************************************/

void WDT_setup();

#endif

/*##################################################
            TIMER1
##################################################*/
#if TIMER_ONE_CONFIG

void timer1_setup();

#endif

#endif
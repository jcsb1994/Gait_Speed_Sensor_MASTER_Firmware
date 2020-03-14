#include "sleep.h"

#if SLEEP_CONFIG

void sleep_setup()
{
    SMCR |= (1 << 2);   //power down mode
    SMCR |= 1;          //enable sleep
    ADCSRA |= (1 << 7); //Disable ADC (saves additional power)
}

void activate_sleep()
{
    MCUCR |= (3 << 5);                      //set both BODS and BODSE at the same time
    MCUCR = (MCUCR & ~(1 << 5)) | (1 << 6); //then set the BODS bit and clear the BODSE bit at the same time
    //ADCSRA |= (1 << 7);                      //Disable ADC (saves additional power)
    __asm__ __volatile__("sleep"); //in line assembler to go to sleep
    //ADCSRA &= ~(1 << 7);                     //Enable ADC after sleep (if used)
}

#endif
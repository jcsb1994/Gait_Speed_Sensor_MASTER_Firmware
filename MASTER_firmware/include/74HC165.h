#ifndef IN_SHI_REG_H
#define  IN_SHI_REG_H

#include "main.h"


void input_shift_reg_SPI_setup();

/***************************************************************************
 * inputShiftSnapShot function
 * 
 * 1) Turn the load Pin HIGH for a millisecond, saves the state of the input pins
 * at a given moment
 * 2) 1 empty byte is transfered for each shift register via the SPI protocol
 *    and received exchange byte is stored in the shift register's data member.
 * 
 ***************************************************************************/

void shift_reg_snapshot();

int transfer_shift_reg_data();




#endif
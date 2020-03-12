#include "74HC165.h"

void input_shift_reg_SPI_setup()
{
    pinMode(LOAD_CONNECTION, OUTPUT);
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    SPI.setDataMode(SPI_MODE0);
    SPI.setBitOrder(MSBFIRST);
    SPI.begin();
}

void shift_reg_snapshot()
{
    PORTD &= ~(1 << LOAD_CONNECTION);
    delay(1);
    PORTD ^= (1 << LOAD_CONNECTION);
}

int transfer_shift_reg_data()
{
    int data = SPI.transfer(0x00);
    return data;
}
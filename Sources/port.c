//************************************************************************************************************
// FILE: port.c
//
// DESCRIPTION
// Writes 001 into the MUX field for pin control register (PORTx_PCRn)
// to enable the ports for GPIO
// Currently only writes to Port B, pins 0-3.  Still trying to figure out
// how to generalize it.
//
// AUTHOR
// John J. Hritz (John.Hritz@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
//************************************************************************************************************
#include "global.h"
#include "port.h"

void porta_gpio_config()
{
	PORTA_PCR1 |= 0b001 << 8;
	PORTA_PCR2 |= 0b001 << 8;
	PORTA_PCR12 |= 0b001 << 8;
}

void portb_gpio_config()
{
	PORTB_PCR0 |= 0b001 << 8;
	PORTB_PCR1 |= 0b001 << 8;
	PORTB_PCR2 |= 0b001 << 8;
	PORTB_PCR3 |= 0b001 << 8;
}


void portd_gpio_config()
{
	PORTD_PCR3 |= 0b001 << 8;
}


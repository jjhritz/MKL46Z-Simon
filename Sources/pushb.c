//************************************************************************************************************
// FILE: pushb.c
//
// DESCRIPTION
//
// AUTHOR
// John J. Hritz (John.Hritz@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
//************************************************************************************************************
#include "pushb.h"
#include "global.h"
#include "gpio.h"
#include "sim.h"
#include "port.h"

void pushb_init()
{
	enableSIM(9); 	//Enable SIM for Port A
	enableSIM(12); 	//Enable SIM for Port D
	
	porta_gpio_config();	//configure port A for GPIO
	portd_gpio_config();	//configure port D for GPIO
	
	//Configure PTA1-2, PTD3, PTA12 for input
	gpioa_pddr_config(1, GPIO_PDDR_IN);
	gpioa_pddr_config(2, GPIO_PDDR_IN);
	gpiod_pddr_config(3, GPIO_PDDR_IN);
	gpioa_pddr_config(12, GPIO_PDDR_IN);
}

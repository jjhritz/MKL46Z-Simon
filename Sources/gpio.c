//************************************************************************************************************
// FILE: gpio.c
//
// DESCRIPTION
// Configures the Port Data Direction Register for GPIO port x
// (GPIOx_PDDR) for output.  
// Currently only configures Port B.  
//
// AUTHOR
// John J. Hritz (John.Hritz@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
//************************************************************************************************************
#include "global.h"
#include "gpio.h"

//configures PORT A GPIO pins for input or output
void gpioa_pddr_config(uint32_t pin, uint32_t direction)
{
	//if direction is input (GPIO_PDDR_IN)
	if(direction == 0)
	{
		GPIOA_PDDR &= ~(1 << pin);
	}
	//if direction is output (GPIO_PDDR_OUT)	
	else if(direction == 1)
	{
		GPIOA_PDDR |= (1 << pin);
	}
}

//configures PORT B GPIO pins for input or output
void gpiob_pddr_config(uint32_t pin, uint32_t direction)
{
	//if direction is input (GPIO_PDDR_IN)
	if(direction == 0)
	{
		GPIOB_PDDR &= ~(1 << pin);
	}
	//if direction is output (GPIO_PDDR_OUT)
	else if(direction == 1)
	{
		GPIOB_PDDR |= (1 << pin);
	}
}

//configures PORT D GPIO pins for input or output
void gpiod_pddr_config(uint32_t pin, uint32_t direction)
{
	//if direction is input (GPIO_PDDR_IN)
	if(direction == 0)
	{
		GPIOD_PDDR &= ~(1 << pin);
	}
	//if direction is output (GPIO_PDDR_OUT)
	else if(direction == 1)
	{
		GPIOD_PDDR |= (1 << pin);
	}
}

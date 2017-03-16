/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "global.h"
#include "main.h"
#include "tpm.h"
#include "led.h"
#include "sim.h"
#include "port.h"
#include "gpio.h"
#include "simon.h"
#include "pushb.h"
#include "systick.h"



void hardware_init()
{
	SysTick_init(); //initialize the SysTick timer.
	
	enableSIM(10); 	//Enable SIM for Port B
	
	portb_gpio_config();	//configure port B for GPIO
	
	//Configure PTB0-3 for output
	for(uint32_t n = 0; n < 4; n++)
	{
		gpiob_pddr_config(n, GPIO_PDDR_OUT);
	}
	
	//initialize push button hardware
	pushb_init();
}

int main()
{
	hardware_init();
	
	simon_play();
	
	return 0;
}

//************************************************************************************************************
// FILE: led.c
//
// DESCRIPTION
//
// AUTHOR
// John J. Hritz (John.Hritz@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
//************************************************************************************************************
#include "global.h"
#include "led.h"

//Turns on the LED at Port B Pin n
void led_on(uint32_t logic, uint32_t n)
{
	//if using positive logic (LED_LOGIC_POS)
	if(logic == 0)
	{	
		GPIOB_PDOR |= 1 << n;
	}
	//if using negative logic (LED_LOGIC_NEG)
	else
	{
		GPIOB_PDOR &= ~(1 << n);
	}
}

//Turn on first n LEDs
void led_all_on(uint32_t logic, uint32_t n)
{
	uint32_t i = 0;
	while(i < n)
	{
		led_on(logic, i);
		i++;
	}
}

//Turns off the LED at Port B Pin n
void led_off(uint32_t logic, uint32_t n)
{
	//if using positive logic (LED_LOGIC_POS)
	if(logic == 0)
	{
		GPIOB_PDOR &= ~(1 << n);
	}
	//if using negative logic (LED_LOGIC_NEG)
	else
	{
		GPIOB_PDOR |= 1 << n;
	}
}

//Turn off first n LEDs
void led_all_off(uint32_t logic, uint32_t n) 
{
	uint32_t i = 0;
	while(i < n)
	{
		led_off(logic, i);
		i++;
	}
}

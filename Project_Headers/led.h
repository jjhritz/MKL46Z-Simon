//************************************************************************************************************
// FILE: led.h
//
// DESCRIPTION
//
// AUTHOR
// John J. Hritz (John.Hritz@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
//************************************************************************************************************
#ifndef LED_H_
#define LED_H_

#include "global.h"

#define LED_LOGIC_POS	0
#define LED_LOGIC_NEG	1

void led_on(uint32_t, uint32_t);
void led_all_on(uint32_t, uint32_t);
void led_off(uint32_t, uint32_t);
void led_all_off(uint32_t, uint32_t);

#endif

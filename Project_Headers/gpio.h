//************************************************************************************************************
// FILE: gpio.h
//
// DESCRIPTION
//
// AUTHOR
// John J. Hritz (John.Hritz@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
//************************************************************************************************************
#ifndef GPIO_H_
#define GPIO_H_

#include "global.h"

#define GPIO_PDDR_IN	0
#define GPIO_PDDR_OUT	1

void gpioa_pddr_config(uint32_t, uint32_t);
void gpiob_pddr_config(uint32_t, uint32_t);
void gpiod_pddr_config(uint32_t, uint32_t);

#endif

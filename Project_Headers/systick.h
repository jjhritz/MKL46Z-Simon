//************************************************************************************************************
// FILE: systick.h
//
// DESCRIPTION
//
// AUTHOR
// John J. Hritz (John.Hritz@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
//************************************************************************************************************
#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "global.h"

void SysTick_init();
uint32_t systick_read();

#endif

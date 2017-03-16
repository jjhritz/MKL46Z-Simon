//************************************************************************************************************
// FILE: simon.h
//
// DESCRIPTION
//
// AUTHOR
// John J. Hritz (John.Hritz@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
//************************************************************************************************************
#ifndef SIMON_H_
#define SIMON_H_

#include "global.h"
#include "led.h"

#define PUSHB1_STATE		(GPIOA_PDIR & (1 << 1))
#define PUSHB2_STATE		(GPIOA_PDIR & (1 << 2))
#define PUSHB3_STATE		(GPIOD_PDIR & (1 << 3))
#define PUSHB4_STATE		(GPIOA_PDIR & (1 << 12))


void simon_play();

#endif

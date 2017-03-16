//************************************************************************************************************
// FILE: rand.h
//
// DESCRIPTION
//
// AUTHOR
// John J. Hritz (John.Hritz@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
//************************************************************************************************************
#ifndef RAND_H_
#define RAND_H_

#include "global.h"


//Initializes the linear congruential generator using a seed from 
//Systick
uint32_t rand_init();

//Generates a new random number using the previous generated value 
uint32_t rand_next();

//Generates a new random number in the range [p_lower, p_upper]
uint32_t rand_between(uint32_t, uint32_t);

#endif

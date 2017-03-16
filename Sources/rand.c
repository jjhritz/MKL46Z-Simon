//************************************************************************************************************
// FILE: rand.c
//
// DESCRIPTION
//
// AUTHOR
// John J. Hritz (John.Hritz@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
//************************************************************************************************************
#include "rand.h"
#include "global.h"
#include "systick.h"

uint32_t A = 1103515245, C = 12345, M = 2^31, next = 0, prev = 0;

//prev = systick_read();

//Initializes the linear congruential generator using a seed from 
//Systick
uint32_t rand_init()
{
	next = (A * systick_read() + C) % M;
	
	prev = next;
	
	return next;
}

//Generates a new random number using the previous generated value
uint32_t rand_next()
{
	next = (A * prev + C) % M;
	
	prev = next;
	
	return next;
}

//Generates a new random number in the range [p_lower, p_upper]
uint32_t rand_between(uint32_t p_lower, uint32_t p_upper)
{
	return (rand_next()) % (p_upper + 1) - p_lower;
}

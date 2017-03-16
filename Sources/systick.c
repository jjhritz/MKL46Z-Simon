//************************************************************************************************************
// FILE: systick.c
//
// DESCRIPTION
//
// AUTHOR
// John J. Hritz (John.Hritz@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
//************************************************************************************************************
#include "systick.h"
#include "global.h"

void SysTick_init()
{
	//Write the reload value to SYST_RVR.
	SYST_RVR = 0x00FFFFFF;
	
	//Write 0 to SYST_CVR to set the current value of the counter to 0. 
	//This will cause the counter to reload with 0xFF_FFFF 
	//on the next clock pulse.
	SYST_CVR = 0;
	
	//Write 0x00000005 to SYST_CSR. 
	//This will choose the 48 MHz core clock as the clock source for SysTick
	//(the counter will tick every 20.833 ns) 
	//and will enable the counter to begin counting.
	SYST_CSR = 0x00000005;
}

uint32_t systick_read()
{
	return (uint32_t)SYST_CVR;
}

//************************************************************************************************************
// FILE: tpm.c
//
// DESCRIPTION
//
// AUTHOR
// John J. Hritz (John.Hritz@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
//************************************************************************************************************
#include "global.h"
#include "tpm.h"


void tpm_busy_delay_us(uint32_t p_delay_us)
{
	//Enable the clock gate to the TPM module
	SIM_SCGC6 |= 1 << 24;
		
	// Initialize SIM_SOPT2 to select MCGIRCLK as the TPM0 clock source.
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b11);
		
	// Initialize TPM0_SC to: clear TOF (in case it was set) 
	TPM0_SC |= 1 << 7;
		
	//Intialize TPM0_SC to: operate in up-counting mode
	TPM0_SC &= ~(1 << 5);
			
	// Initialize TPM0_SC to: disable the TPM counter
	TPM0_SC &= ~(0b11 << 3);
			
	//Clear TPM0_SC[PS]
	TPM0_SC &= ~(0b111 << 0);
	
	//Initialize TPM0_SC[PS] to divide MCGIRCLK by 4.
	TPM0_SC |= (1 << 1);
		
	// Write 0 to TPM0_CNT[COUNT] to reset the TPM counter to 0.
	TPM0_CNT = 0;
		
	// Write (p_delay_us - 1) to TPM0_MOD[MOD] to cause TOF to be set after (p_delay_us - 1) us have elapsed.
	TPM0_MOD = (p_delay_us - 1);
		
	// Write 0 to TPM_CONF to: clear CSOO so the counter will continue counting on overflow; 
	TPM0_CONF = 0;
			
	// Write 0 to TPM_CONF to clear CSOT which will cause the counter to begin counting immediately after it is enabled.
	TPM0_CONF &= 0 << 16;
	
	//Write 01 to TPM0_SC[CMOD] so the TPM counter increments on ever TPM counter clock
	TPM0_SC |= (1 << 3);

	// At this time, the TPM counter will begin counting. Wait in a loop polling TOM0_SC[TOF] until it is set.
	while (~TPM0_SC & TPM_SC_TOF_MASK) {}
	
	// Write to TPM0_SC[TOF] to clear the timer overflow flag.
	TPM0_SC |= 1 << 7;
}

void tpm_busy_delay_ms(uint32_t p_delay_ms)
{
	//Enable the clock gate to the TPM module
	SIM_SCGC6 |= 1 << 24;
	
	// Initialize SIM_SOPT2 to select MCGIRCLK as the TPM0 clock source.
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b11);
	
	// Initialize TPM0_SC to: clear TOF (in case it was set) 
	TPM0_SC |= 1 << 7;
	
	//Intialize TPM0_SC to: operate in up-counting mode
	TPM0_SC &= ~(1 << 5);
		
	// Initialize TPM0_SC to: disable the TPM counter
	TPM0_SC &= ~(0b11 << 3);
		
	//Clear TPM0_SC[PS]
	TPM0_SC &= ~(0b111 << 0);
	
	//Initialize TPM0_SC[PS] to divide MCGIRCLK by 4.
	TPM0_SC |= (1 << 1);
	
	// Write 0 to TPM0_CNT[COUNT] to reset the TPM counter to 0.
	TPM0_CNT = 0;
	
	// Write 999 to TPM0_MOD[MOD] to cause TOF to be set after 1000 us have elapsed.
	TPM0_MOD = 999;
	
	// Write 0 to TPM_CONF to: clear CSOO so the counter will continue counting on overflow; 
	TPM0_CONF = 0;
		
	// Write 0 to TPM_CONF to clear CSOT which will cause the counter to begin counting immediately after it is enabled.
	TPM0_CONF &= 0 << 16;
	
	//Write 01 to TPM0_SC[CMOD] so the TPM counter increments on ever TPM counter clock
	TPM0_SC |= (1 << 3);
	
	for(uint32_t i = 0; i < p_delay_ms; i++)
	{
		// At this time, the TPM counter will begin counting. Wait in a loop polling TOM0_SC[TOF] until it is set.
		while (~TPM0_SC & TPM_SC_TOF_MASK) {}
	
		// Write to TPM0_SC[TOF] to clear the timer overflow flag.
		TPM0_SC |= 1 << 7;
	}

}

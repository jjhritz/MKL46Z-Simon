//************************************************************************************************************
// FILE: tpm.h
//
// DESCRIPTION
// Header file for tpm.c; declares functions
//
// AUTHOR
// John J. Hritz (John.Hritz@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
//************************************************************************************************************
#ifndef TPM_H_
#define TPM_H_

#include "global.h"

#define TPM_SC(x) 		(*(volatile uint32_t *)(0x40038000u + (x) * 0x1000))
#define TPM_CNT(x) 		(*(volatile uint32_t *)(0x40038000u + (x) * 0x1000 + 0x04))
#define TPM_MOD(x) 		(*(volatile uint32_t *)(0x40038000u + (x) * 0x1000 + 0x08))
#define TPM_CSC(x, n) 	(*(volatile uint32_t *)(0x40038000u + (x) * 0x1000 + 0x0C + (n) * 0x08))
#define TPM_CV(x, n) 	(*(volatile uint32_t *)(0x40038000u + (x) * 0x1000 + 0x10 + (n) * 0x08 + 0x04))
#define TPM_STATUS(x) 	(*(volatile uint32_t *)(0x40038000u + (x) * 0x1000 + 0x50))
#define TPM_CONF(x) 	(*(volatile uint32_t *)(0x40038000u + (x) * 0x1000 + 0x84))

void tpm_busy_delay_us(uint32_t); //tpm delay in microseconds

void tpm_busy_delay_ms(uint32_t); //tpm delay in milliseconds

#endif

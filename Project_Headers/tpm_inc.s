@*************************************************************************************************************
@ FILE: tpm_inc.s
@
@ DESCRIPTION
@ Contains public declarations for the tpm module
@
@ AUTHOR
@ John J. Hritz (John.Hritz@asu.edu)
@ Computer Science & Engineering
@ Arizona State University, Tempe AZ 85287-8809
@*************************************************************************************************************

.ifndef tpm_inc
.equ tpm_inc, 1

.file   "tpm_inc.s"   @ Name of the source code file for the debugger
.syntax unified       @ Using ARM unified assembly languae syntax

@=================================================================================
@Public symbols to be imported
@=================================================================================

@Public Functions
.extern tpm_busy_delay_us
.extern tpm_busy_delay_ms

.endif

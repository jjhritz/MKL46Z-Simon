@*************************************************************************************************************
@ FILE: pushb_inc.s
@
@ DESCRIPTION
@ Contains public declarations for the push button module
@
@ AUTHOR
@ John J. Hritz (John.Hritz@asu.edu)
@ Computer Science & Engineering
@ Arizona State University, Tempe AZ 85287-8809
@*************************************************************************************************************

.ifndef pushb_inc
.equ pushb_inc, 1

.file   "pushb_inc.s"   @ Name of the source code file for the debugger
.syntax unified         @ Using ARM unified assembly languae syntax

@=================================================================================
@Public symbols to be imported
@=================================================================================

@Public Functions
.extern pushb_init

.endif

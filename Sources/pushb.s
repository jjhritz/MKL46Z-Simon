@*************************************************************************************************************
@ FILE: pushb.s
@
@ DESCRIPTION
@ Contains function implementations for the push button module
@
@ AUTHOR
@ John J. Hritz (John.Hritz@asu.edu)
@ Computer Science & Engineering
@ Arizona State University, Tempe AZ 85287-8809
@*************************************************************************************************************

.file   "pushb.s"     @ Name of the source code file for the debugger
.syntax unified       @ Using ARM unified assembly language syntax
.include "pushb_inc.s"

@=================================================================================
@Public symbols to be exported
@=================================================================================

@Public functions
.global pushb_init


@=================================================================================
@Function Definitions
@=================================================================================
.text

@---------------------------------------------------------------------------------
@ FUNCTION: void pushb_init()
@
@ PARAMETERS
@ None
@
@ DESCRIPTION
@ Initializes push button hardware.
@ Enables SIM to Ports A & D
@ Configures Ports A & D for GPIO
@ Configures PTA1-2, PTD3, PTA12 for input
@
@ NOTES
@
@ PSEUDOCODE
@ Function void pushb_init()
@       EnableSIM(PortBitA)
@       EnableSIM(PortBitD)
@       porta_gpio_config()
@       portd_gpio_config()
@       gpioa_pddr_config(1, GPIO_PDDR_IN)
@       gpioa_pddr_config(2, GPIO_PDDR_IN)
@       gpiod_pddr_config(3, GPIO_PDDR_IN)
@       gpioa_pddr_config(12, GPIO_PDDR_IN)
@ End function
@
@ STACK FRAME
@ lr <- SP
@
@---------------------------------------------------------------------------------
.func pushb_init, pushb_init
.type pushb_init, %function
.thumb_func

pushb_init:
    push    {lr}        @save lr to stack
    
    @EnableSIM(PortBitA)
        movs    r0, #9      @r0 = 9 (the bit for Port A in SIM_SCGC5)
        bl      enableSIM   @Call enableSIM() from port.c
    
    @EnableSIM(PortBitD)
        movs    r0, #12     @r0 = 12 (the bit for Port D in SIM_SCGC5)
        bl      enableSIM   @Call enableSIM() from port.c
        
    @porta_gpio_config()
        bl      porta_gpio_config   @Call porta_gpio_config() from port.c
    
    @portd_gpio_config()
        bl      portd_gpio_config   @Call portd_gpio_config() from port.c
     
    @gpioa_pddr_config(1, GPIO_PDDR_IN)
        movs    r0, #1              @r0 = 1 (Bit for PTA1)
        movs    r1, #0              @r1 = 0 (Sets PTA1 for input)
        bl      gpioa_pddr_config   @Call gpioa_pddr_config() from gpio.c
     
    @gpioa_pddr_config(2, GPIO_PDDR_IN)
        movs    r0, #2              @r0 = 2 (Bit for PTA2)
        movs    r1, #0              @r1 = 0 (Sets PTA2 for input)
        bl      gpioa_pddr_config   @Call gpioa_pddr_config() from gpio.c
     
    @gpiod_pddr_config(3, GPIO_PDDR_IN)
        movs    r0, #3              @r0 = 1 (Bit for PTD3)
        movs    r1, #0              @r1 = 0 (Sets PTD3 for input)
        bl      gpiod_pddr_config   @Call gpiod_pddr_config() from gpio.c
        
    @gpioa_pddr_config(12, GPIO_PDDR_IN)
        movs    r0, #12             @r0 = 12 (Bit for PTA12)
        movs    r1, #0              @r1 = 0 (Sets PTA12 for input)
        bl      gpioa_pddr_config   @Call gpioa_pddr_config() from gpio.c

    pop         {pc}                @pc = lr (return to caller)

.endfunc

@*************************************************************************************************************
@ FILE: tpm.s
@
@ DESCRIPTION
@ Contains function implementations for the tpm module
@
@ AUTHOR
@ John J. Hritz (John.Hritz@asu.edu)
@ Computer Science & Engineering
@ Arizona State University, Tempe AZ 85287-8809
@*************************************************************************************************************

.file   "tpm.s"     @ Name of the source code file for the debugger
.syntax unified       @ Using ARM unified assembly language syntax
.include "tpm_inc.s"

@=================================================================================
@Public symbols to be exported
@=================================================================================

@Public functions
.global tpm_busy_delay_us
.global tpm_busy_delay_ms


@=================================================================================
@Function Definitions
@=================================================================================
.text

@---------------------------------------------------------------------------------
@ FUNCTION: void tpm_busy_delay_us(uint32_t p_delay_us)
@
@ PARAMETERS
@ r0 - p_delay_us
@
@ DESCRIPTION
@ Engages a busy delay using the TPM for a specified number of microseconds
@
@ NOTES
@
@
@ PSEUDOCODE
@ Function void tpm_busy_delay_us(uint32_t p_delay_us)
@    //Enable the clock gate to the TPM module
@    SIM_SCGC6 |= 1 << 24;
@        
@    // Initialize SIM_SOPT2 to select MCGIRCLK as the TPM0 clock source.
@    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b11);
@        
@    // Initialize TPM0_SC to: clear TOF (in case it was set) 
@    TPM0_SC |= 1 << 7;
@        
@    //Intialize TPM0_SC to: operate in up-counting mode
@    TPM0_SC &= ~(1 << 5);
@            
@    // Initialize TPM0_SC to: disable the TPM counter
@    TPM0_SC &= ~(0b11 << 3);
@            
@    //Clear TPM0_SC[PS]
@    TPM0_SC &= ~(0b111 << 0);
@    
@    //Initialize TPM0_SC[PS] to divide MCGIRCLK by 4.
@    TPM0_SC |= (1 << 1);
@        
@    // Write 0 to TPM0_CNT[COUNT] to reset the TPM counter to 0.
@    TPM0_CNT = 0;
@        
@    // Write (p_delay_us - 1) to TPM0_MOD[MOD] to cause TOF to be set after (p_delay_us - 1) us have elapsed.
@    TPM0_MOD = (p_delay_us - 1);
@        
@    // Write 0 to TPM_CONF to: clear CSOO so the counter will continue counting on overflow; 
@    TPM0_CONF = 0;
@            
@    // Write 0 to TPM_CONF to clear CSOT which will cause the counter to begin counting immediately after it is enabled.
@    TPM0_CONF &= 0 << 16;
@    
@    //Write 01 to TPM0_SC[CMOD] so the TPM counter increments on ever TPM counter clock
@    TPM0_SC |= (1 << 3);
@
@    // At this time, the TPM counter will begin counting. Wait in a loop polling TOM0_SC[TOF] until it is set.
@    while (~TPM0_SC & TPM_SC_TOF_MASK) {}
@    
@    // Write to TPM0_SC[TOF] to clear the timer overflow flag.
@    TPM0_SC |= 1 << 7;
@ End function
@
@ STACK FRAME
@ lr <- SP + 4
@ r0 <- SP
@
@---------------------------------------------------------------------------------
.func tpm_busy_delay_us, tpm_busy_delay_us
.type tpm_busy_delay_us, %function
.thumb_func

tpm_busy_delay_us:
    
    push    {r0, lr}        @save p_delay_us, lr to stack
    
    @Enable the clock gate to the TPM module
    @SIM_SCGC6 |= 1 << 24;
        movs    r1, #24         @r1 = 24 (bit in SIM_SCGC6 that enables TPM0)
        ldr     r2, sim_scgc6   @r2 = address of SIM_SCGC6 register
        ldr     r3, [r2]        @r3 = value of SIM_SCGC6 register
        movs    r4, 1           @r4 = 1
        lsls    r4, r1          @r4 = 1 << 24
        orrs    r3, r4          @r3 = SIM_SCGC6 | (1 << 24)
        str     r3, [r2]        @SIM_SCGC6 = SIM_SCGC6 | (1 << 24) 
        
    @Initialize SIM_SOPT2 to select MCGIRCLK as the TPM0 clock source.
    @SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b11);
        movs    r1, #24         @r1 = 24 (first bit in SIM_SOPT2 that selects TPM source)
        ldr     r2, sim_sopt2   @r2 = address of SIM_SOPT2 register
        ldr     r3, [r2]        @r3 = value of SIM_SOPT2 register
        movs    r4, 0b11        @r4 = 0b11
        lsls    r4, r1          @r4 = 0b11 << 24
        orrs    r3, r4          @r3 = SIM_SOPT2 | (0b11 << 24)
        str     r3, [r2]        @SIM_SOPT2 = SIM_SOPT2 | (0b11 << 24) 
     
    @Initialize TPM0_SC to: clear TOF (in case it was set) 
    @TPM0_SC |= 1 << 7;
        movs    r1, #7          @r1 = 7 (bit in TPM0_SC that holds the TOF flag)
        ldr     r2, tpm0_sc     @r2 = address of TPM0_SC register
        ldr     r3, [r2]        @r3 = value of TPM0_SC register
        movs    r4, 1           @r4 = 1
        lsls    r4, r1          @r4 = 1 << 7
        orrs    r3, r4          @r3 = TPM0_SC | (1 << 7)
        str     r3, [r2]        @TPM0_SC = TPM0_SC | (1 << 7) 
     
    @Intialize TPM0_SC to: operate in up-counting mode
    @TPM0_SC &= ~(1 << 5);
        movs    r1, #5          @r1 = 5 (bit in TPM0_SC that determines count mode)
        ldr     r2, tpm0_sc     @r2 = address of TPM0_SC register
        ldr     r3, [r2]        @r3 = value of TPM0_SC register
        movs    r4, 1           @r4 = 1
        lsls    r4, r1          @r4 = 1 << 5
        bics    r3, r4          @r3 = TPM0_SC & ~(1 << 5)
        str     r3, [r2]        @TPM0_SC = TPM0_SC & ~(1 << 5)          
   
    @Initialize TPM0_SC to: disable the TPM counter
    @TPM0_SC &= ~(0b11 << 3);
        movs    r1, #3          @r1 = 3 (first bit in TPM0_SC that determines clock mode)
        ldr     r2, tpm0_sc     @r2 = address of TPM0_SC register
        ldr     r3, [r2]        @r3 = value of TPM0_SC register
        movs    r4, 0b11        @r4 = 0b11
        lsls    r4, r1          @r4 = 0b11 << 3
        bics    r3, r4          @r3 = TPM0_SC & ~(0b11 << 3)
        str     r3, [r2]        @TPM0_SC = TPM0_SC & ~(0b11 << 3)         
    
    @Clear TPM0_SC[PS]
    @TPM0_SC &= ~(0b111 << 0);
        movs    r1, #0          @r1 = 0 (first bit in TPM0_SC that determines prescale factor)
        ldr     r2, tpm0_sc     @r2 = address of TPM0_SC register
        ldr     r3, [r2]        @r3 = value of TPM0_SC register
        movs    r4, 0b111       @r4 = 0b111
        lsls    r4, r1          @r4 = 0b111 << 0
        bics    r3, r4          @r3 = TPM0_SC & ~(0b111 << 0)
        str     r3, [r2]        @TPM0_SC = TPM0_SC & ~(0b11 << 0)
          
    @Initialize TPM0_SC[PS] to divide MCGIRCLK by 4.
    @TPM0_SC |= (1 << 1);
        movs    r1, #1          @r1 = 1 (second bit in TPM0_SC that determines prescale factor (divides clock frequency by 4))
        ldr     r2, tpm0_sc     @r2 = address of TPM0_SC register
        ldr     r3, [r2]        @r3 = value of TPM0_SC register
        movs    r4, 1           @r4 = 1
        lsls    r4, r1          @r4 = 1 << 1
        orrs    r3, r4          @r3 = TPM0_SC | (1 << 1)
        str     r3, [r2]        @TPM0_SC = TPM0_SC | (1 << 1) 
        
    @Write 0 to TPM0_CNT[COUNT] to reset the TPM counter to 0.
    @TPM0_CNT = 0;
        movs    r1, #0          @r1 = 0 (What we want to sent the COUNT field to)
        ldr     r2, tpm0_cnt    @r2 = address of TPM0_CNT register
        str     r2, [r1]        @TPM0_SC = 0 
 
    @Write (p_delay_us - 1) to TPM0_MOD[MOD] to cause TOF to be set after (p_delay_us - 1) us have elapsed.
    @TPM0_MOD = (p_delay_us - 1);
        subs    r1, r0, #1      @r1 = (p_delay_us - 1) (What we want to sent the MOD field to)
        ldr     r2, tpm0_mod    @r2 = address of TPM0_MOD register
        str     r1, [r2]        @TPM0_MOD = (p_delay_us - 1)
   
    @Write 0 to TPM_CONF to: clear CSOO so the counter will continue counting on overflow; 
    @TPM0_CONF = 0;
        movs    r1, #0          @r1 = 0 (What we want to sent the CSOO field to)
        ldr     r2, tpm0_conf   @r2 = address of TPM0_CONF register
        str     r1, [r2]        @TPM0_SC = 0 
          
    @Write 0 to TPM_CONF to clear CSOT which will cause the counter to begin counting immediately after it is enabled.
    @TPM0_CONF &= ~(1 << 16);
        movs    r1, #16         @r1 = 16 (bit in TPM0_CONF that determines count start on trigger)
        ldr     r2, tpm0_conf   @r2 = address of TPM0_CONF register
        ldr     r3, [r2]        @r3 = value of TPM0_CONF register
        movs    r4, 1           @r4 = 1
        lsls    r4, r1          @r4 = 1 << 16
        bics    r3, r4          @r3 = TPM0_CONF & ~(1 << 16)
        str     r3, [r2]        @TPM0_CONF = TPM0_CONF & ~(1 << 16)  
        
    @Write 01 to TPM0_SC[CMOD] so the TPM counter increments on ever TPM counter clock
    @TPM0_SC |= (1 << 3);
        movs    r1, #3          @r1 = 3 (first bit in TPM0_SC that determines clock mode selection)
        ldr     r2, tpm0_sc     @r2 = address of TPM0_SC register
        ldr     r3, [r2]        @r3 = value of TPM0_SC register
        movs    r4, 1           @r4 = 1
        lsls    r4, r1          @r4 = 1 << 3
        orrs    r3, r4          @r3 = TPM0_SC | (1 << 3)
        str     r3, [r2]        @TPM0_SC = TPM0_SC | (1 << 1)
    
    @At this time, the TPM counter will begin counting. Wait in a loop polling TOM0_SC[TOF] until it is set.
    @while (~TPM0_SC & TPM_SC_TOF_MASK) {}
        ldr     r2, tpm0_sc         @r2 = address of TPM0_SC register
        ldr     r4, tpm_sc_tof_mask @r4 = load TOF check mask
        
        check_cond_us:
            ldr     r3, [r2]            @r3 = value of TPM0_SC register
            mvns    r5, r3              @r5 = bitwise NOT of the value of TPM0_SC
            ands    r5, r4              @r5 = ~TPM0_SC & TPM_SC_TOF_MASK
            cmp     r5, r4              @r5 - r4 = (~TPM0_SC & TPM_SC_TOF_MASK) - TPM_SC_TOF_MASK
            bne     loop_end_us         @if ((~TPM0_SC & TPM_SC_TOF_MASK) != TPM_SC_TOF_MASK
                                        @i.e. TOF is set, drop out of loop
            b       check_cond_us       @go back and check condition
        
        loop_end_us:
    

    @Write to TPM0_SC[TOF] to clear the timer overflow flag.
    @TPM0_SC |= 1 << 7;
        movs    r1, #7          @r1 = 7 (bit in TPM0_SC that holds the TOF flag)
        ldr     r2, tpm0_sc     @r2 = address of TPM0_SC register
        ldr     r3, [r2]        @r3 = value of TPM0_SC register
        movs    r4, 1           @r4 = 1
        lsls    r4, r1          @r4 = 1 << 7
        orrs    r3, r4          @r3 = TPM0_SC | (1 << 7)
        str     r3, [r2]        @TPM0_SC = TPM0_SC | (1 << 7) 

    pop         {r1, pc}                @r1 = p_delay_us, pc = lr (return to caller)

.endfunc


@---------------------------------------------------------------------------------
@ FUNCTION: void tpm_busy_delay_ms(uint32_t p_delay_ms)
@
@ PARAMETERS
@ r0 - p_delay_us
@
@ DESCRIPTION
@ Engages a busy delay using the TPM for a specified number of milliseconds
@
@ NOTES
@
@ PSEUDOCODE
@ Function void tpm_busy_delay_ms(uint32_t p_delay_ms)
@    //Enable the clock gate to the TPM module
@    SIM_SCGC6 |= 1 << 24;
@        
@    // Initialize SIM_SOPT2 to select MCGIRCLK as the TPM0 clock source.
@    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b11);
@        
@    // Initialize TPM0_SC to: clear TOF (in case it was set) 
@    TPM0_SC |= 1 << 7;
@        
@    //Intialize TPM0_SC to: operate in up-counting mode
@    TPM0_SC &= ~(1 << 5);
@            
@    // Initialize TPM0_SC to: disable the TPM counter
@    TPM0_SC &= ~(0b11 << 3);
@            
@    //Clear TPM0_SC[PS]
@    TPM0_SC &= ~(0b111 << 0);
@    
@    //Initialize TPM0_SC[PS] to divide MCGIRCLK by 4.
@    TPM0_SC |= (1 << 1);
@        
@    // Write 0 to TPM0_CNT[COUNT] to reset the TPM counter to 0.
@    TPM0_CNT = 0;
@        
@    // Write 999 to TPM0_MOD[MOD] to cause TOF to be set after 1000 us have elapsed.
@    TPM0_MOD = 999;
@        
@    // Write 0 to TPM_CONF to: clear CSOO so the counter will continue counting on overflow; 
@    TPM0_CONF = 0;
@            
@    // Write 0 to TPM_CONF to clear CSOT which will cause the counter to begin counting immediately after it is enabled.
@    TPM0_CONF &= 0 << 16;
@    
@    //Write 01 to TPM0_SC[CMOD] so the TPM counter increments on ever TPM counter clock
@    TPM0_SC |= (1 << 3);
@
@    //Need to run through p_delay_ms cycles of 1000 us 
@    for(uint32_t i = 0; i < p_delay_ms; i++)
@    {  
@       // At this time, the TPM counter will begin counting. Wait in a loop polling TOM0_SC[TOF] until it is set.
@       while (~TPM0_SC & TPM_SC_TOF_MASK) {}
@    
@       // Write to TPM0_SC[TOF] to clear the timer overflow flag.
@       TPM0_SC |= 1 << 7;
@    }
@ End function
@
@ STACK FRAME
@ lr <- SP + 4
@ r0 <- SP
@
@---------------------------------------------------------------------------------
.func tpm_busy_delay_ms, tpm_busy_delay_ms
.type tpm_busy_delay_ms, %function
.thumb_func

tpm_busy_delay_ms:
    
    push    {r0, lr}        @save p_delay_us, lr to stack
    
   
    @Enable the clock gate to the TPM module
    @SIM_SCGC6 |= 1 << 24;
        movs    r1, #24         @r1 = 24 (bit in SIM_SCGC6 that enables TPM0)
        .align 2 
        ldr     r2, sim_scgc6   @r2 = address of SIM_SCGC6 register
        ldr     r3, [r2]        @r3 = value of SIM_SCGC6 register
        movs    r4, 1           @r4 = 1
        lsls    r4, r1          @r4 = 1 << 24
        orrs    r3, r4          @r3 = SIM_SCGC6 | (1 << 24)
        str     r3, [r2]        @SIM_SCGC6 = SIM_SCGC6 | (1 << 24) 
        
    @Initialize SIM_SOPT2 to select MCGIRCLK as the TPM0 clock source.
    @SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b11);
        movs    r1, #24         @r1 = 24 (first bit in SIM_SOPT2 that selects TPM source)
        ldr     r2, sim_sopt2   @r2 = address of SIM_SOPT2 register
        ldr     r3, [r2]        @r3 = value of SIM_SOPT2 register
        movs    r4, 0b11        @r4 = 0b11
        lsls    r4, r1          @r4 = 0b11 << 24
        orrs    r3, r4          @r3 = SIM_SOPT2 | (0b11 << 24)
        str     r3, [r2]        @SIM_SOPT2 = SIM_SOPT2 | (0b11 << 24) 
     
    @Initialize TPM0_SC to: clear TOF (in case it was set) 
    @TPM0_SC |= 1 << 7;
        movs    r1, #7          @r1 = 7 (bit in TPM0_SC that holds the TOF flag)
        ldr     r2, tpm0_sc     @r2 = address of TPM0_SC register
        ldr     r3, [r2]        @r3 = value of TPM0_SC register
        movs    r4, 1           @r4 = 1
        lsls    r4, r1          @r4 = 1 << 7
        orrs    r3, r4          @r3 = TPM0_SC | (1 << 7)
        str     r3, [r2]        @TPM0_SC = TPM0_SC | (1 << 7) 
     
    @Intialize TPM0_SC to: operate in up-counting mode
    @TPM0_SC &= ~(1 << 5);
        movs    r1, #5          @r1 = 5 (bit in TPM0_SC that determines count mode)
        ldr     r2, tpm0_sc     @r2 = address of TPM0_SC register
        ldr     r3, [r2]        @r3 = value of TPM0_SC register
        movs    r4, 1           @r4 = 1
        lsls    r4, r1          @r4 = 1 << 5
        bics    r3, r4          @r3 = TPM0_SC & ~(1 << 5)
        str     r3, [r2]        @TPM0_SC = TPM0_SC & ~(1 << 5)          
   
    @Initialize TPM0_SC to: disable the TPM counter
    @TPM0_SC &= ~(0b11 << 3);
        movs    r1, #3          @r1 = 3 (first bit in TPM0_SC that determines clock mode)
        ldr     r2, tpm0_sc     @r2 = address of TPM0_SC register
        ldr     r3, [r2]        @r3 = value of TPM0_SC register
        movs    r4, 0b11        @r4 = 0b11
        lsls    r4, r1          @r4 = 0b11 << 3
        bics    r3, r4          @r3 = TPM0_SC & ~(0b11 << 3)
        str     r3, [r2]        @TPM0_SC = TPM0_SC & ~(0b11 << 3)         
    
    @Clear TPM0_SC[PS]
    @TPM0_SC &= ~(0b111 << 0);
        movs    r1, #0          @r1 = 0 (first bit in TPM0_SC that determines prescale factor)
        ldr     r2, tpm0_sc     @r2 = address of TPM0_SC register
        ldr     r3, [r2]        @r3 = value of TPM0_SC register
        movs    r4, 0b111        @r4 = 0b111
        lsls    r4, r1          @r4 = 0b111 << 0
        bics    r3, r4          @r3 = TPM0_SC & ~(0b111 << 0)
        str     r3, [r2]        @TPM0_SC = TPM0_SC & ~(0b11 << 0)
          
    @Initialize TPM0_SC[PS] to divide MCGIRCLK by 4.
    @TPM0_SC |= (1 << 1);
        movs    r1, #1          @r1 = 1 (second bit in TPM0_SC that determines prescale factor (divides clock frequency by 4))
        ldr     r2, tpm0_sc     @r2 = address of TPM0_SC register
        ldr     r3, [r2]        @r3 = value of TPM0_SC register
        movs    r4, 1           @r4 = 1
        lsls    r4, r1          @r4 = 1 << 1
        orrs    r3, r4          @r3 = TPM0_SC | (1 << 1)
        str     r3, [r2]        @TPM0_SC = TPM0_SC | (1 << 1) 
        
    @Write 0 to TPM0_CNT[COUNT] to reset the TPM counter to 0.
    @TPM0_CNT = 0;
        movs    r1, #0          @r1 = 0 (What we want to sent the COUNT field to)
        ldr     r2, tpm0_cnt    @r2 = address of TPM0_CNT register
        str     r1, [r2]        @TPM0_SC = 0 
 
    @Write 999 to TPM0_MOD[MOD] to cause TOF to be set after 1000 us have elapsed.
    @TPM0_MOD = 999;
        ldr     r1, ms_mod      @r1 = 999 (What we want to sent the MOD field to)
        ldr     r2, tpm0_mod    @r2 = address of TPM0_MOD register
        str     r1, [r2]        @TPM0_MOD = 999
   
    @Write 0 to TPM_CONF to: clear CSOO so the counter will continue counting on overflow; 
    @TPM0_CONF = 0;
        movs    r1, #0          @r1 = 0 (What we want to sent the CSOO field to)
        ldr     r2, tpm0_conf   @r2 = address of TPM0_CONF register
        str     r1, [r2]        @TPM0_SC = 0 
          
    @Write 0 to TPM_CONF to clear CSOT which will cause the counter to begin counting immediately after it is enabled.
    @TPM0_CONF &= ~(1 << 16);
        movs    r1, #16         @r1 = 16 (bit in TPM0_CONF that determines count start on trigger)
        ldr     r2, tpm0_conf   @r2 = address of TPM0_CONF register
        ldr     r3, [r2]        @r3 = value of TPM0_CONF register
        movs    r4, 1           @r4 = 1
        lsls    r4, r1          @r4 = 1 << 16
        bics    r3, r4          @r3 = TPM0_CONF & ~(1 << 16)
        str     r3, [r2]        @TPM0_CONF = TPM0_CONF & ~(1 << 16)  
        
    @Write 01 to TPM0_SC[CMOD] so the TPM counter increments on ever TPM counter clock
    @TPM0_SC |= (1 << 3);
        movs    r1, #3          @r1 = 3 (first bit in TPM0_SC that determines clock mode selection)
        ldr     r2, tpm0_sc     @r2 = address of TPM0_SC register
        ldr     r3, [r2]        @r3 = value of TPM0_SC register
        movs    r4, 1           @r4 = 1
        lsls    r4, r1          @r4 = 1 << 3
        orrs    r3, r4          @r3 = TPM0_SC | (1 << 3)
        str     r3, [r2]        @TPM0_SC = TPM0_SC | (1 << 1)
    
    @Need to run through p_delay_ms cycles of 1000 us 
    @for(uint32_t i = 0; i < p_delay_ms; i++)
        movs    r6, #0                  @r6 (i) = 0
        ldr     r2, tpm0_sc             @r2 = address of TPM0_SC register
        ldr     r4, tpm_sc_tof_mask     @r4 = load TOF check mask
        
        check_cond_ms:
            cmp     r6, r0                  @r6 - r0 = i - p_delay_ms
            bge     loop_end_ms             @if (i >= p_delay_ms) drop out of loop
   
            @else, go into microsecond loop
            
            @At this time, the TPM counter will begin counting. Wait in a loop polling TOM0_SC[TOF] until it is set.
            @while (~TPM0_SC & TPM_SC_TOF_MASK) {}
            check_cond_us2:
                ldr     r3, [r2]            @r3 = value of TPM0_SC register
                mvns    r5, r3              @r5 = bitwise NOT of the value of TPM0_SC
                ands    r5, r4              @r5 = ~TPM0_SC & TPM_SC_TOF_MASK
                cmp     r5, r4              @r5 - r4 = (~TPM0_SC & TPM_SC_TOF_MASK) - TPM_SC_TOF_MASK
                bne     loop_end_us2        @if ((~TPM0_SC & TPM_SC_TOF_MASK) != TPM_SC_TOF_MASK
                                            @i.e. TOF is set, drop out of loop
                b       check_cond_us2      @else go back and check condition
        
            loop_end_us2:
            @Write to TPM0_SC[TOF] to clear the timer overflow flag.
            @TPM0_SC |= 1 << 7;
                movs    r1, #7          @r1 = 7 (bit in TPM0_SC that holds the TOF flag)
                ldr     r2, tpm0_sc     @r2 = address of TPM0_SC register
                ldr     r3, [r2]        @r3 = value of TPM0_SC register
                movs    r4, 1           @r4 = 1
                lsls    r4, r1          @r4 = 1 << 7
                orrs    r3, r4          @r3 = TPM0_SC | (1 << 7)
                str     r3, [r2]        @TPM0_SC = TPM0_SC | (1 << 7) 
                
            adds    r6, r6, #1              @i++
            b       check_cond_ms           @go check the loop condition
            
       loop_end_ms:

    pop         {r1, pc}                @r1 = p_delay_ms, pc = lr (return to caller)

.endfunc

.align 2                                    @ensure word alignment
sim_scgc6:          .word 0x4004803C        @address of SIM_SCGC6 register
sim_sopt2:          .word 0x40048004        @address of SIM_SOPT2 register
tpm0_sc:            .word 0x40038000        @address of TPM0_SC register
tpm0_cnt:           .word 0x40038004        @address of TPM0_CNT register
tpm0_mod:           .word 0x40038008        @address of TPM0_MOD register
tpm0_conf:          .word 0x40038084        @address of TPM0_CONF register
tpm_sc_tof_mask:    .word 0x80              @mask for checking TOF flag
ms_mod:             .word 999               @integer 999 used to set TPM0_MOD[MOD] in tpm_busy_delay_ms

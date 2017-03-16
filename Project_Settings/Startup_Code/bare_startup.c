//**********************************************************************************************************************
// FILE: bare_startup.c
//
// DESCRIPTION
// Contains startup code functions written in C. Also contains the definition of the exception vector table.
//
// AUTHOR
// Kevin R. Burger (burgerk@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe AZ 85287-8809
// Web: http://www.devlang.com
//**********************************************************************************************************************
#include "bare_startup.h"
#include "global.h"
#include "libcse325.h"

//======================================================================================================================
// Private Type Definitions
//======================================================================================================================

// The ROM pointer table defined in the linker script is used to copy bytes from flash (ROM) to SRAM during startup.
// The table is a 1D array of struct bare_rom_table_t entries. Each entry has three members: m_source is the address
// in flash of a block of data to be copied to RAM; m_target is the address in SRAM where the data is to be copied to;
// and m_size is the number of bytes in the block being copied. The ROM pointer table array ends with an entry where
// all three data members are 0. The ROM table is copied in the bare_coopy_rom_sections_to_ram() function which is in
// this source code file.
typedef struct {
    uint8_t *m_source; // Address of beginning of block in flash to be copied
    uint8_t *m_target; // Address of where the block is to be copied to in SRAM.
    int m_size;        // Size of the block to be copied in bytes
} bare_rom_table_t;

//======================================================================================================================
// Public Global Variable Declarations
//======================================================================================================================

// The initial value (address) of the stack pointer register is defined in the linker script. This value is used in this
// file to initialize the first entry in the exception vector table.
extern uint32_t __init_sp;

// The address of the exception vector table is defined in the linker scipt by creating this __vector_table variable.
// This value is used in bare_hw_init() to initialize SCB_VTOR.
extern uint32_t __vector_table[];

// This array variable provides access to the ROM pointer table that is defined in the linker script file. See comments
// for bare_rom_table_t typedef above.
extern bare_rom_table_t __romp[];

//======================================================================================================================
// Public Function Declarations
//======================================================================================================================

// Weak definitions of interrupt service routines point to bare_default_isr if not implemented.
void nmi_isr()       __attribute__((weak, alias("bare_default_isr")));
void hardfault_isr() __attribute__((weak, alias("bare_default_isr")));
void svc_isr()       __attribute__((weak, alias("bare_default_isr")));
void pendsv_isr()    __attribute__((weak, alias("bare_default_isr")));
void systick_isr()   __attribute__((weak, alias("bare_default_isr")));
void dma0_isr()      __attribute__((weak, alias("bare_default_isr")));
void dma1_isr()      __attribute__((weak, alias("bare_default_isr")));
void dma2_isr()      __attribute__((weak, alias("bare_default_isr")));
void dma3_isr()      __attribute__((weak, alias("bare_default_isr")));
void ftfa_isr()      __attribute__((weak, alias("bare_default_isr")));
void pmc_isr()       __attribute__((weak, alias("bare_default_isr")));
void llw_isr()       __attribute__((weak, alias("bare_default_isr")));
void i2c0_isr()      __attribute__((weak, alias("bare_default_isr")));
void i2c1_isr()      __attribute__((weak, alias("bare_default_isr")));
void spi0_isr()      __attribute__((weak, alias("bare_default_isr")));
void spi1_isr()      __attribute__((weak, alias("bare_default_isr")));
void uart0_isr()     __attribute__((weak, alias("bare_default_isr")));
void uart1_isr()     __attribute__((weak, alias("bare_default_isr")));
void uart2_isr()     __attribute__((weak, alias("bare_default_isr")));
void adc0_isr()      __attribute__((weak, alias("bare_default_isr")));
void cmp0_isr()      __attribute__((weak, alias("bare_default_isr")));
void tpm0_isr()      __attribute__((weak, alias("bare_default_isr")));
void tmp1_isr()      __attribute__((weak, alias("bare_default_isr")));
void tmp2_isr()      __attribute__((weak, alias("bare_default_isr")));
void rtcalarm_isr()  __attribute__((weak, alias("bare_default_isr")));
void rtcsecs_isr()   __attribute__((weak, alias("bare_default_isr")));
void pit_isr()       __attribute__((weak, alias("bare_default_isr")));
void i2s0_isr()      __attribute__((weak, alias("bare_default_isr")));
void usbotg_isr()    __attribute__((weak, alias("bare_default_isr")));
void dac0_isr()      __attribute__((weak, alias("bare_default_isr")));
void tsi0_isr()      __attribute__((weak, alias("bare_default_isr")));
void mcg_isr()       __attribute__((weak, alias("bare_default_isr")));
void lptimer_isr()   __attribute__((weak, alias("bare_default_isr")));
void slcd_isr()      __attribute__((weak, alias("bare_default_isr")));
void porta_isr()     __attribute__((weak, alias("bare_default_isr")));
void portscd_isr()   __attribute__((weak, alias("bare_default_isr")));

//======================================================================================================================
// Private Variable Definitions
//======================================================================================================================

// Define and initialize the interrupt vector table. Place the vector table in its own section named .vectortable
// in the .o file. The linker script will use this section name to make sure the vector table is placed in the flash
// at 0x0000_0000.
void (* const bare_vector_table[])() __attribute__((section(".vectortable"))) = {
    (void *)&__init_sp,	  // Initial value of the SP register
    bare_startup,         // Reset vector will jump here and begin executing code
    nmi_isr,              // Nonmaskable interrupt service routine
    hardfault_isr,        // Hardfault interrupt service routine
    0,                    // Reserved
    0,                    // Reserved
    0,                    // Reserved
    0,                    // Reserved
    0,                    // Reserved
    0,                    // Reserved
    0,                    // Reserved
    svc_isr,
    0,                    // Reserved
    0,                    // Reserved
    pendsv_isr,
    systick_isr,
    dma0_isr,             // DMA Channel 0 Transfer Complete and Error
    dma1_isr,             // DMA Channel 1 Transfer Complete and Error
    dma2_isr,             // DMA Channel 2 Transfer Complete and Error
    dma3_isr,             // DMA Channel 3 Transfer Complete and Error
    0,                    // Reserved
    ftfa_isr,             // Command complete and read collision
    pmc_isr,              // PMC Interrupt */
    llw_isr,              // Low Leakage Wake-up */
    i2c0_isr,             // I2C0 interrupt */
    i2c1_isr,             // I2C1 interrupt */
    spi0_isr,             // SPI0 Interrupt */
    spi1_isr,             // SPI1 Interrupt */
    uart0_isr,            // UART0 Status and Error interrupt */
    uart1_isr,            // UART1 Status and Error interrupt */
    uart2_isr,            // UART2 Status and Error interrupt */
    adc0_isr,             // ADC0 interrupt
    cmp0_isr,             // CMP0 interrupt
    tpm0_isr,             // TPM0
    tmp1_isr,             // TPM1
    tmp2_isr,             // TPM2
    rtcalarm_isr,         // RTC Alarm interrupt
    rtcsecs_isr,          // RTC Seconds interrupt
    pit_isr,              // PIT timer all channels interrupt
    i2s0_isr,             // Single interrupt vector for all sources
    usbotg_isr,           // USB interrupt
    dac0_isr,             // DAC0 interrupt
    tsi0_isr,             // TSI0 Interrupt
    mcg_isr,              // MCG Interrupt
    lptimer_isr,          // LPTimer interrupt
    slcd_isr,             // SLCD
    porta_isr,            // Port A interrupt
    portscd_isr           // Single interrupt vector for Port C and Port D interrupt
};

//======================================================================================================================
// Private Function Declarations
//======================================================================================================================
#ifdef CLKOUT_ENABLE
static void bare_clkout_init();
#endif

static void bare_clocks_init();

//======================================================================================================================
// Public and Private Function Definitions
//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
// FUNCTION: bare_bss_zero_fill
//
// DESCRIPTION
// This function fills the .bss section in RAM with all zeros. __bss_begin and __bss_end are defined in the linker
// script.
//----------------------------------------------------------------------------------------------------------------------
void bare_bss_zero_fill()
{
    extern uint8_t __bss_begin[];
    extern uint8_t __bss_end[];
    cse325_memset(__bss_begin, 0, __bss_end - __bss_begin);
}

//----------------------------------------------------------------------------------------------------------------------
// FUNCTION: bare_clkout_init()
//
// DESCRIPTION
// Initializes the CLKOUT signal on microcontroller pin 73 (PTC3) to be the Bus clock.
//----------------------------------------------------------------------------------------------------------------------
#ifdef CLKOUT_ENABLE
static void bare_clkout_init()
{
    // Configure PTC3 function as ALT5 (CLKOUT).
    PORTC_PCR3 = 0b101 << 8;
        
    // Configure CLKOUT Select in SIM_SOPT2.
    uint32_t reg = SIM_SOPT2; // Store current SIM_SOPT2 value in reg
    reg &= ~(0b111 << 5);     // Clear SIM_SOPT2[CLKOUTSEL] field.
    reg |= 0b010 << 5;        // CLKOUT is bus clock.
    SIM_SOPT2 = reg;          // Write SIM_SOPT2.
}
#endif

//----------------------------------------------------------------------------------------------------------------------
// FUNCTION: bare_clocks_init()
//
// DESCRIPTION
// Initializes the Core, Platform, and System clocks to 48 MHz and the Bus and Flash clocks to 24 MHz. This code is
// originally from Freescale, but I modified it a bit to make it -- in my opinion -- a bit more readable.
//----------------------------------------------------------------------------------------------------------------------
static void bare_clocks_init()
{
    // Write 1 to SIM_CLKDIV1[OUTDIV1] and SIM_CLKDIV1[OUTDIV4] so the Core, Platform, and System clock divider
    // value will be 2 and the Bus and Flash clock divider value will be 2. The PLL VCOCLK output will be configured to
    // 96 MHz, so these dividers will result in the Core, Platform, and System clock freqs to be 48 MHz and the Bus
    // and Flash clock freqs to be 24 MHz.
    // SIM_CLKDIV1[OUTDIV1] = 1 (divide value for Core, Platform, and System clocks = 2)
    // SIM_CLKDIV1[OUTDIV4] = 1 (divide value for Bus and Flash clocks = 2; clock freq will be one-half System clock)
    SIM_CLKDIV1 = 0x10010000;

    // Configure the fast internal reference clock divider to be 1. The reset value is divide by 2.
    // MCG_SC[ATM]      = unchanged
    // MCG_SC[ATMS]     = unchanged
    // MCG_SC[ATF]      = unchanged
    // MCG_SC[FLTPRSRV] = unchanged
    // MCG_SC[FRCDIV]   = 0b000 (divide-by-1)
    // MCG_SC[LOCS0]    = unchanged
    MCG_SC &= ~(0b111 << 1);

    // MCG is in FEI mode at reset. Transition to FBE mode. FBE mode is entered by configuring MCG_C2, OSC0_CR, MCG_C1,
    // MCG_C4, MCG_C5, and MCG_C6 and then waiting for status bits in MCG_S to change.

    // Start by configuring MCG_C2.
    // Note: FCFTRIM should not be changed from its reset value as altering this bit will alter the frequency of the
    // fast internal reference clock (I learned this the hard way).
    // MCG_C2[LOCRE0]  = 0 (interrupt request is generated on loss of OSCCLK)
    // MCG_C2[FCFTRIM] = unchanged
    // MCG_C2[RANGE0]  = 0b10 (OSC external clock source is very high range 8-32 MHz)
    // MCG_C2[HGO0]    = 0 (OSC configured for low power operation)
    // MCG_C2[EREFS0]  = 1 (external ref clock from OSC = EXTAL is requested)
    // MCG_C2[LP]      = 0 (FLL or PLL is not disabled in bypass mode)
    // MCG_C2[IRCS]    = 1 (MCGIRCLK is fast internal ref clock)
    uint8_t mcg_c2 = MCG_C2;               // mcg_c2 = current value of MCG_C2
    mcg_c2 &= 0b01000000;                  // Clear all bits except for FCFTRIM, leave it unchanged
    mcg_c2 |= (0b10 << 4) | (1 << 2) | 1;  // Write 0b10 to OSC, 1 to EREFS0, and 1 to MCGIRCLK
    MCG_C2 = mcg_c2;                       // Update MCG_C2

    // Continuing, configure OSC0_CR.
    // OSC0_CR[ERCLKEN]  = 1 (enable OSCERCLK)
    // OSC0_CR[EREFSTEN] = 0 (OSCERCLK is disabled in Stop mode)
    OSC0_CR = 0b10000000;

    // Continuing, configure MCG_C1.
    // MCG_C1[CLKS]     = 0b10 (MCGOUTCLK is external ref clock OSCCLK = 8 MHz)
    // MCG_C1[FRDIV]    = 0b011 = 3 (external ref clock OSCCLK is divided by 256 = 8 MHz / 256 = 31.25 KHz)
    // MCG_C1[IREFS]    = 0 (FLL clock source is OSCCLK divided by FRDIV)
    // MCG_C1[IRCLKEN]  = 1 (MCGIRCLK is enabled)
    // MCG_C1[IREFSTEN] = 0 (internal ref clock is disabled in Stop mode)
    MCG_C1 = 0b10011010;

    // Continuing, configure MCG_C4.
    // Note: FCTRIM must not be changed from its reset value as changing it would alter the frequency of the fast
    // internal reference clock (I learned this the hard way).
    // MCG_C4[DMX32]    = 0
    // MCG_C4[DRST_DRS] = 0b00
    // MCG_C4[FCTRIM]   = 0b1000
    // MCG_C4[SCFTRIM]  = 0
    // When DMX32:DRST_DRS = 0b000 = 0, the FLL clock source reference range is [31.25, 39.0625] KHz, the FLL multiplier
    // factor is 640, and the DCOCLK range is [20, 25] MHz. In our case, since the FLL clock source is 31.25 KHz, the
    // DCOCLK will be 32.25 KHz x 640 = 20 MHz.
    uint8_t mcg_c4 = MCG_C4;  // mcg_c4 = current value of MCG_C4
    mcg_c4 &= 0b00011110;     // Clear all bits except for FCTRIM, leave it unchanged
    MCG_C4 = mcg_c4;          // Update MCG_C4

    // Continuing, configure MCG_C5.
    // MCG_C5[reserved] = 0
    // MCG_C5[PLLCLKEN] = 0 (MCGPLLCLK is inactive)
    // MCG_C5[PLLSTEN0] = 0 (MCGPLLCLK is disabled in Stop mode)
    // MCG_C5[PRDIV0]   = 0b00001 (divides the PLL external ref clock OSCCLK by 2; will be 8 MHz / 2 = 4 MHz)
    MCG_C5 = 0b00000001;

    // Continuing, configure MCG_C6.
    // MCG_C6[LOLIE0] = 0 (no irq generated on loss of FLL or PLL lock)
    // MCG_C6[PLLS]   = 0 (MCGOUTCLK is still external ref clock OSCCLK = 8 MHz)
    // MCG_C6[CME0]   = 0 (disables clock monitoring for OSC)
    // MCG_C6[VDIV0]  = 0b00000 (VCOCLK output from PLL is multiplied by 24; it will be 96 MHz)
    MCG_C6 = 0b00000000;

    // Wait until MCG_S[IREFST] changes to 0 indicating that the source of the FLL ref clock is the external ref
    // clock OSCCLK). At this time MCGOUTCLK is 8 MHz.
    while ((MCG_S & 0b00010000) != 0b00000000) {
    }

    // Wait until MCG_S[CLKST] changes to 0b10 indicating that MCGOUTCLK is OSCCLK = 8 MHz.
    while ((MCG_S & 0b00001100) != 0b00001000) {
    }

    // We are now in FBE mode. Switch to PBE mode by configuring MCG_C6.
    // MCG_C6[LOLIE0] = 0 (no irq generated on loss of FLL or PLL lock)
    // MCG_C6[PLLS]   = 1 (MCGOUTCLK is MCGPLLCLK)
    // MCG_C6[CME0]   = 0 (disables clock monitoring for OSC)
    // MCG_C6[VDIV0]  = 0b00000 (VCOCLK output from PLL is multiplied by 24; it will be 96 MHz)
    MCG_C6 = 0b01000000;

    // Wait until MCG_S[CLKST] changes to 0b10 indicating that MCGOUTCLK is OSCCLK = 8 MHz).
    while ((MCG_S & 0b00001100) != 0b00001000) {
    }

    // Wait until MCG_S[LOCK0] changes to 1 indicating that the PLL has locked onto its ref clock.
    while ((MCG_S & 0b01000000) == 0b00000000) {
    }

    // We are now in PBE mode. Switch to PEE mode.
    // MCG_C1[CLKS]     = 0b00 (MCGOUTCLK is MCGPLLCLK which is VCOCLK / 2 = 96 MHz / 2 = 48 MHz)
    // MCG_C1[FRDIV]    = 0b011 = 3 (do not change)
    // MCG_C1[IREFS]    = 0 (do not change)
    // MCG_C1[IRCLKEN]  = 1 (MCGIRCLK is enabled)
    // MCG_C1[IREFSTEN] = 0 (internal ref clock is disabled in Stop mode)
    MCG_C1 = 0b00011010;

    // Wait until MCG_S[CLKST] changes to 0b11 indicating that MCGOUTCLK = MCGPLLCLK = 48 MHz).
    while ((MCG_S & 0b00001100) != 0b00001100) {
    }

    // Set global variables. These are defined in global.c and declared in global.h.
    global_core_clock_freq_mhz     = 48;
    global_platform_clock_freq_mhz = 48;
    global_system_clock_freq_mhz   = 48;
    global_bus_clock_freq_mhz      = 24;
    global_flash_clock_freq_mhz    = 24;
    global_oscerclk_freq_mhz       = 8;
    global_mcgirclk_freq_mhz       = 4;  // Note that MCGIRCLK is the fast internal reference clock = 4 MHz

    // Select MCGPLLCLK/2 to be the clock source for some peripherals.
    SIM_SOPT2 |= 1 << 16;

    #ifdef CLKOUT_ENABLE
        // Enable the CLKOUT pin to be the Bus clock. Note that this disables use of PTC3.
       bare_clkout_init();
    #endif
}

//----------------------------------------------------------------------------------------------------------------------
// FUNCTION: bare_copy_rom_sections_to_ram
//
// DESCRIPTION
// This function copies all sections marked as ROM in the .elf file to their target addresses in SRAM. __romp is
// defined in the linker script as a 1D array where each element is a structure of type bare_rom_table_t. The end of
// the ROM entries is specified by a structure with all 0's for each of the fields.
//----------------------------------------------------------------------------------------------------------------------
void bare_copy_rom_sections_to_ram()
{
    // If there are no ROM sections to copy then return.
    if (__romp == 0L) return;

    // Iterate over table entry, copying the section from ROM to SRAM.
    for (int i = 0; __romp[i].m_source != 0L; ++i) {
        cse325_memcpy(__romp[i].m_target, __romp[i].m_source, __romp[i].m_size);
    }
}

//----------------------------------------------------------------------------------------------------------------------
// FUNCTION: bare_default_usr()
//
// DESCRIPTION
// Default interrupt service routine. All interrupt vectors direct here unless changed by writing a new address for the
// ISR to the vector table. This function simply executes an ARM breakpoint instruction, which causes execution to halt.
//----------------------------------------------------------------------------------------------------------------------
void bare_default_isr()
{
    __asm("bkpt");
}

//----------------------------------------------------------------------------------------------------------------------
// FUNCTION: bare_hw_init()
//
// DESCRIPTION
// Called by bare_startup. Initializes SCB_VTOR and SIM_COPC.
//----------------------------------------------------------------------------------------------------------------------
void bare_hw_init()
{
    // Write the address of the exception vector table to SCB_VTOR.
    SCB_VTOR = (uint32_t)__vector_table;

    // Disable the watchdog because it may reset the core before entering main().
    SIM_COPC = 0x00000000;

    // Initialize the Core, Platform, System, Bus, and Flash clocks.
    bare_clocks_init();
}

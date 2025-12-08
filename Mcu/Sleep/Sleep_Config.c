#include "Sleep_Config.h"

/* =============================================================================
 * Sleep_Config
 * Purpose: Configure PMU and ARM SCR registers for sleep mode
 * ===========================================================================*/
void Sleep_Config(void)
{
    // Clear DPDFLAG (Deep Power-Down flag) by writing 1
    LPC_PMU->PCON |= (1 << 11);

    // Clear SLEEPFLAG by writing 1
    LPC_PMU->PCON |= (1 << 8);

    // Configure for Deep-Sleep: set SLEEPDEEP bit in SCR
    SCB->SCR |= (1 << 2);
} 
  

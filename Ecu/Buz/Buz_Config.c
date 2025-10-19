#include "Buz_Config.h"

void Buz_Config(void)
{
// IO pin used: GPIO0_8/GPT2_MAT

/*Syscon
- PCLK to enable for IOCON
- PCLK to enable for GPT2 */
	Syscon_Pclk_Iocon_Enable();
	Syscon_Pclk_Gpt2_Enable();

/* Iocon
- Pin function: 2 (GPT2_MAT)
- Pin Mode: 1 (Pull Down enable) */
	Iocon_Pio0_8_Set(2, 1, 0, 0, 0, 0);	

// Core configuration (Gpt2)
	Gpt2_Clock_Set(GPT_CLOCK_1MHZ);
}


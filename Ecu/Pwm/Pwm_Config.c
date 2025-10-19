#include "Pwm_Config.h"



void Pwm_Config(void)
{
	// Base configuration: Syscon
	Syscon_Pclk_Iocon_Enable();
	Syscon_Pclk_Gpt1_Enable();
	
	// Base configuration: Iocon
	Iocon_R_Pio1_1_Set(3,1,0,1,0,0);
	
	// Core configuration: Gpt
	Gpt1_Clock_Set(GPT_CLOCK_1MHZ);
}



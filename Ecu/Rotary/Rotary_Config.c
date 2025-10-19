#include "Rotary_Config.h"

void Rotary_Config(void)
{
	// Base configuration: Syscon
	Syscon_Pclk_Iocon_Enable();
	Syscon_Pclk_Gpio_Enable();
	
	// Base configuration: Iocon
	Iocon_Pio1_5_Set(0,2,1,0,0,0);
	Iocon_Pio1_8_Set(0,2,1,0,0,0);
	Iocon_Pio0_7_Set(0,2,1,0,0,0);

	// Core configuration: Gpio
	Gpio1_Direction_Set(5, INPUT);
	Gpio1_Direction_Set(8, INPUT);
	Gpio0_Direction_Set(7, INPUT);
	
	// Core configuration: Eint
	Eint1_Edge_Trigger_Set(5,FALLING_EDGE_TRIGGER);
	
	// Enable EINT1 IRQ
	NVIC_EnableIRQ(EINT1_IRQn);
	
	// Enable EINT1 in GPIO block
	Eint1_Enable(5);
}



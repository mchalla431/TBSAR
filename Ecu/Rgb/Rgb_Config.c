#include "Rgb_Config.h"

void Rgb_Config(void)
{
	// Base configuration: Syscon
	Syscon_Pclk_Iocon_Enable();
	Syscon_Pclk_Gpio_Enable();
	
	// Base configuration: Iocon
	Iocon_Pio2_10_Set(0,2,0,0,0,0);
	Iocon_R_Pio1_2_Set(1,2,0,1,0,0);
	Iocon_Pio1_10_Set(0,2,0,1,0,0);
	
	// Core configuration: Gpio
	Gpio2_Direction_Set(10, OUTPUT);
	Gpio1_Direction_Set(2, OUTPUT);
	Gpio1_Direction_Set(10, OUTPUT);
}




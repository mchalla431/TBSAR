#include "Ukeys_Config.h"

void Ukeys_Config(void)
{
    // Base configuration: syscon
	Syscon_Pclk_Iocon_Enable();
	Syscon_Pclk_Gpio_Enable();
	
    // Base configuration: Iocon
	Iocon_Pio0_3_Set(0,2,1,0,0,0);
	Iocon_Pio1_4_Set(0,2,1,1,0,0); // AD Mode applicable
	Iocon_Pio2_6_Set(0,2,1,0,0,0);
	Iocon_Pio2_7_Set(0,2,1,0,0,0);
	Iocon_Pio2_8_Set(0,2,1,0,0,0);
	
	// Core configuration: Gpio
	Gpio0_Direction_Set(3, INPUT);
	Gpio1_Direction_Set(4, INPUT);
	Gpio2_Direction_Set(6, INPUT);
	Gpio2_Direction_Set(7, INPUT);
	Gpio2_Direction_Set(8, INPUT);
}


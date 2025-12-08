#include "Sensors_Config.h"


void Sensors_Config(void)
{
	// Base configuration: Syscon
	Syscon_Pclk_Iocon_Enable();
	Syscon_Pclk_Adc_Enable();
	Syscon_Adc_Power_Down_Disable();
	
	// Core configuration: Iocon
	Iocon_R_Pio0_11_Set(2,0,1,0,0,0);  // Pull-up and Pull-down resistor disabled
	Iocon_R_Pio1_0_Set(2,0,1,0,0,0);   // Pull-up and Pull-down resistor disabled
	
	// Core configuration: Adc
	Adc_Clock_Set(ADC_CLOCK_1MHZ);
}


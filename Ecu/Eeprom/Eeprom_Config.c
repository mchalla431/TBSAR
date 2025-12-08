#include "Eeprom_Config.h"
#include "Dio.h"
#include "Dio_Config.h"


void Eeprom_Config(void)
{
	// Base configuration: syscon
	Syscon_Pclk_Iocon_Enable();
	Syscon_Pclk_Gpio_Enable();
	Syscon_Pclk_I2c_Enable();
	Syscon_I2c_Preset_Deassert();
					  
	// Base configuration: iocon
	Iocon_Pio0_4_Set(1, 2, 0, 0, 0, 0);
	Iocon_Pio0_5_Set(1, 2, 0, 0, 0, 0);
	
	// Configure PIO2_3 as GPIO output for EEPROM WP
    Iocon_Pio2_3_Set(0, 0, 0, 0, 0, 0); // GPIO mode
    Gpio2_Direction_Set(3, OUTPUT);
    Gpio2_Pin_Set(3, HIGH); // Default: Write Protect Enabled
	
	// Core configuration: i2c
	I2c_Clock_Set(I2C_CLOCK_400KHZ);
	
}









#include "Dac_Config.h"

void Dac_Config(void)
{
	// Base Configuration: Syscon
	Syscon_Pclk_Iocon_Enable();
	Syscon_Pclk_Spi_Enable();
	Syscon_Pclk_Gpio_Enable();
	Syscon_Spi_Clkdiv_Set(1);
	Syscon_Spi_Preset_Deassert();
	
	// Base Configuration: Iocon
	Iocon_Pio2_11_Set(1, 2, 0, 0, 0, 0);
	Iocon_Pio0_9_Set(1, 2, 0, 0, 0, 0);
	Iocon_Pio0_2_Set(0, 2, 0, 0, 0, 0);
	
	// Core Configuration: Gpio and Spi
	Gpio0_Direction_Set(2, OUTPUT);
	Spi_Data_Size_Set(SPI_DATA_16BIT);
	Spi_Mode_Set(SPI_MODE0);
	Spi_Clock_Set(SPI_CLOCK_1MHZ);
}





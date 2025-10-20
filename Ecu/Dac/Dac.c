#include "Dac.h"


void Dac_Chip_Select(void)
{
	// GPIO0_2 to set LOW	
	Gpio0_Pin_Set(2, LOW);
}

void Dac_Chip_Deselect(void)
{
	// GPIO0_2 to set HIGH	
	Gpio0_Pin_Set(2, HIGH);
}

uint16_t Dac_Value_Update(uint16_t val)
{
	uint16_t dummy =0;

// Update the Shift Register with a 16-bit value
	Spi_Shift_Register_Set(val);

// Wait for SPI transfer complete
	while((Spi_Transfer_Status_Get()));

// Read the Shift Register (dummy)
	dummy = Spi_Shift_Register_Get();

	return dummy;
}

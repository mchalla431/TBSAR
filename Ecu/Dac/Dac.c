#include "Dac.h"
#include "Monitor.h"

// Internal inline functions for chip select operations
static inline void Dac_Chip_Select(void)
{
	// GPIO0_2 to set LOW	
	Gpio0_Pin_Set(2, LOW);
}

static inline void Dac_Chip_Deselect(void)
{
	// GPIO0_2 to set HIGH	
	Gpio0_Pin_Set(2, HIGH);
}

static inline uint16_t Dac_Value_Update(uint16_t val)
{
	uint16_t dummy = 0;
	uint16_t dac_command = 0;
	
	// MCP4911 Configuration bits:
	// Bit 15: 0 = Write to DAC register
	// Bit 14: 0 = Unbuffered Vref  
	// Bit 13: 1 = 1x Gain (Vout = Vref * D/1024)
	// Bit 12: 1 = Output Power Control (Active mode)
	// Bits 11-2: 10-bit DAC data (D9-D0)
	// Bits 1-0: Don't care (set to 0)
	
	// Create command word: 0011xxxxxxxxxxxx (0x3000) + (10-bit data << 2)
	dac_command = 0x3000 | ((val & 0x3FF) << 2);

	// Update the Shift Register with the 16-bit command
	Spi_Shift_Register_Set(dac_command);

	// Wait for SPI transfer complete
	while((Spi_Transfer_Status_Get()));

	// Read the Shift Register (dummy)
	dummy = Spi_Shift_Register_Get();

	return dummy;
}

void Dac_Set_Input(uint16_t val)
{
	// Select the DAC chip (CS low)
	Dac_Chip_Select();
	
	// Update the DAC value via SPI
	Dac_Value_Update(val);
	
	// Deselect the DAC chip (CS high)
	Dac_Chip_Deselect();
}

static uint16_t Dac_Get_A2D(void)
{
	uint16_t adc_count = 0;
	volatile uint32_t delay;
	
	// Select ADC input channel 7 (DAC output feedback)
	Adc_Input_Select(7);
	
	// Add settling time for ADC input after DAC output
	for(delay = 0; delay < 1000; delay++);  // Small delay for DAC settling
	
	// Start the ADC conversion
	Adc_Start();
	
	// Wait for the conversion to complete
	Adc_Conversion_Wait(7);
	
	// Read the ADC count (10-bit: 0-1023)
	adc_count = Adc_Count_Get(7);
	
	// Stop the ADC
	Adc_Stop();
	
	return adc_count;
}

uint16_t Dac_Get_Output(void)
{
	uint16_t adc_count, voltage_mv = 0;
	
	// Get the ADC reading first
	adc_count = Dac_Get_A2D();
	
	// Convert ADC count to voltage in millivolts
	// ADC step size = 3.22mV per count (3300mV / 1024 counts)
	// Using integer math: (adc_count * 3226) / 1000
	voltage_mv = (adc_count * 3226) / 1000;
	
	return voltage_mv;
}

void Dac_Monitor(void)
{
	extern uint16_t dac_val;  // Access global DAC value
	uint16_t adc_count, voltage_mv;
	
	// Get ADC reading once
	adc_count = Dac_Get_A2D();
	
	// Convert ADC count to voltage in millivolts
	// ADC step size = 3.22mV per count (3300mV / 1024 counts)
	// Using integer math: (adc_count * 3226) / 1000
	voltage_mv = (adc_count * 3226) / 1000;
	
	// Convert voltage to decimal format (e.g., 1650mV = 1.65V)
	uint16_t voltage_int = voltage_mv / 1000;
	uint16_t voltage_dec = (voltage_mv % 1000) / 100;  // One decimal place
	
	// Display DAC readings (overwrite same line)
	uart_printf("\r[DAC] Set:%d A2D:%d Voltage:%d.%dV          ", 
	           dac_val, adc_count, voltage_int, voltage_dec);
}

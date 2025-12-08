#include "Dac.h"
#include "Monitor.h"

/* DAC chip select pin (PIO0_2) */
#define DAC_CS_PIN		2

/* Global Variables */
uint16_t dac_in = 0;
uint16_t dac_a2d = 0;

void Dac_Set_Input(void)
{
	uint16_t dac_command;
	
	dac_command = (1<<13) | (1<<12) | (dac_in << 2);
	
	/* Pull CS low to select DAC */
	Gpio0_Pin_Set(DAC_CS_PIN, 0);
	
	/* Transfer 16-bit command to MCP4911 */
	Spi_Transfer(dac_command);
	
	/* Pull CS high to deselect DAC and latch command */
	Gpio0_Pin_Set(DAC_CS_PIN, 1);
}

void Dac_Get_A2d(void)
{
	/* Read ADC channel 7 (DAC feedback) - selects and converts internally */
	dac_a2d = Adc_Read_Count_Channel(7);
}


void Dac_Monitor(void)
{
	uart_printf("\rDAC:Val=");
	uart_printf("%u", dac_in);
	uart_printf(" | A2D=");
	uart_printf("%u", dac_a2d);
}

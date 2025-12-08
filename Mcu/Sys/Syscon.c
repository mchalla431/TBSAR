#include "Syscon.h"

/* Power Down Disable Macro */
#define PowerDown_Disable(bp)		SYSCON_PDRUNCFG &= ~(1<<bp)

/* PRESET Deassert Macro */
#define Preset_Deassert(bp)			SYSCON_PRESETCTRL |= (1<<bp)

/* Clock Divider for PCLK_SPI Macro */
#define SPI_PCLK_Div(val)			SYSCON_SPICLKDIV = val 

/* Clock Divider for PCLK_UART Macro */
#define UART_PCLK_Div(val)			SYSCON_UARTCLKDIV = val 

#define PCLK_Enable(bp)				SYSCON_SYSAHBCLKCTRL |=  (1<<bp)


void Syscon_Pclk_Iocon_Enable(void)
{
	PCLK_Enable(16);
}

void Syscon_Pclk_Gpio_Enable(void)
{
	PCLK_Enable(6);
}

void Syscon_Pclk_Adc_Enable(void)
{
	PCLK_Enable(13);
}

void Syscon_Pclk_Gpt0_Enable(void)
{
	PCLK_Enable(9);
}

void Syscon_Pclk_Gpt1_Enable(void)
{
	PCLK_Enable(10);
}

void Syscon_Pclk_Gpt2_Enable(void)
{
	PCLK_Enable(7);
}

void Syscon_Pclk_Spi_Enable(void)
{
	PCLK_Enable(11);
}

void Syscon_Pclk_I2c_Enable(void)
{
	PCLK_Enable(5);
}

void Syscon_Pclk_Uart_Enable(void)
{
	PCLK_Enable(12);
}

void Syscon_Pclk_Can_Enable(void)
{
	PCLK_Enable(17);
}

void Syscon_Pclk_Wdt_Enable(void)
{
	PCLK_Enable(15);
}


void Syscon_Uart_Clkdiv_Set(int val)
{
	UART_PCLK_Div(val);
}

void Syscon_Spi_Clkdiv_Set(int val)
{
	SPI_PCLK_Div(val);
}

void Syscon_Spi_Preset_Deassert(void)
{
	Preset_Deassert(0);	
}

void Syscon_I2c_Preset_Deassert(void)
{
	Preset_Deassert(1);		
}

void Syscon_Uart_Preset_Deassert(void)
{
	Preset_Deassert(3);		
}

void Syscon_Adc_Power_Down_Disable(void)
{
	PowerDown_Disable(4);
}

void Syscon_Wdt_Power_Down_Disable(void)
{
	PowerDown_Disable(6);
}





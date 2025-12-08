#ifndef __SYSCON_H__
#define __SYSCON_H__


/* Includes Section */
#include "lpc11xx.h"

/* Preprocessor labels and Function prototypes */

void Syscon_Pclk_Iocon_Enable(void);
void Syscon_Pclk_Gpio_Enable(void);
void Syscon_Pclk_Adc_Enable(void);
void Syscon_Pclk_Gpt0_Enable(void);
void Syscon_Pclk_Gpt1_Enable(void);
void Syscon_Pclk_Gpt2_Enable(void);
void Syscon_Pclk_Spi_Enable(void);
void Syscon_Pclk_I2c_Enable(void);
void Syscon_Pclk_Uart_Enable(void);
void Syscon_Pclk_Can_Enable(void);
void Syscon_Pclk_Wdt_Enable(void);

void Syscon_Uart_Clkdiv_Set(int val);
void Syscon_Spi_Clkdiv_Set(int val);

void Syscon_Spi_Preset_Deassert(void);
void Syscon_I2c_Preset_Deassert(void);
void Syscon_Uart_Preset_Deassert(void);

void Syscon_Adc_Power_Down_Disable(void);
void Syscon_Wdt_Power_Down_Disable(void);

#endif



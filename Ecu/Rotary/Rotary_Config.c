

/**
 * @file Rotary_Config.c
 * @brief Rotary encoder hardware configuration
 */

#include "lpc11xx.h"
#include "Dio.h"
#include "Rotary_Config.h"
#include "Rotary.h"

void Rotary_Config(void)
{
	/* Enable GPIO and Iocon clocks */
	Syscon_Pclk_Iocon_Enable();
	Syscon_Pclk_Gpio_Enable();
	
	/* Configure Phase A (PIO1_5) as digital input with pull-up and hysteresis */
	Iocon_Pio1_5_Set(0, 2, 1, 0, 0, 0);  /* GPIO mode, pull-up enabled, hysteresis enabled */
	
	/* Configure Phase B (PIO1_8) as digital input with pull-up and hysteresis */
	Iocon_Pio1_8_Set(0, 2, 1, 0, 0, 0);  /* GPIO mode, pull-up enabled, hysteresis enabled */
	
	/* Configure Switch (PIO0_7) as digital input with pull-up and hysteresis */
	Iocon_Pio0_7_Set(0, 2, 1, 0, 0, 0);  /* GPIO mode, pull-up enabled, hysteresis enabled */
	
	/* Set pins as inputs */
	Gpio1_Direction_Set(5, INPUT);   /* Phase A input - generates interrupt */
	Gpio1_Direction_Set(8, INPUT);   /* Phase B input - polled during interrupt */
	Gpio0_Direction_Set(7, INPUT);   /* Switch input - polled for click detection */
	
	/* Enable external interrupts */
	/* Phase A (PIO1_5): Eint1 on rising edge only for single count per detent */
	Eint1_Edge_Trigger_Set(5, RISING_EDGE_TRIGGER);
	Eint1_Enable(5);
	
	/* Enable NVIC interrupt for GPIO Port 1 (PIOINT1) */
	/* GPIO Port 1 uses EINT1_IRQn (IRQ 30) */
	NVIC_EnableIRQ(EINT1_IRQn);
}

#include "Buz_Config.h"

void Buz_Config(void)
{
	/* Enable Iocon clock */
	Syscon_Pclk_Iocon_Enable();
	Syscon_Pclk_Gpio_Enable();
	
	/* Configure GPIO pin for buzzer (PIO0_8) */
	Iocon_Pio0_8_Set(0, 1, 0, 0, 0, 0);

    /* Set Gpio direction as Ouput */
    Gpio0_Direction_Set(8, OUTPUT);
}

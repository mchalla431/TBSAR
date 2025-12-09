#include "Buz.h"
#include "Monitor.h"

void Buz_On(void)
{
	Gpio0_Pin_Set(8, 1);
}

void Buz_Off(void)
{
	Gpio0_Pin_Set(8, 0);
}

void Buz_Monitor(void)
{
	// Print buzzer status to UART
	int state = Gpio0_Pin_Get(8);
	if (state)
		uart_printf("Buzzer: ON\n");
	else
		uart_printf("Buzzer: OFF\n");
}



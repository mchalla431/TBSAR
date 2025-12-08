#include "Wakeup_Config.h"
#include "Dio_Config.h"

void Wakeup_Config(void)
{
	/* Configure center key on PIO2_8 for falling edge interrupt */
	Eint2_Edge_Trigger_Set(8, FALLING_EDGE_TRIGGER);
	Eint2_Reset(8);
	Eint2_Enable(8);

	/* Enable NVIC for Port 2 interrupt */
	NVIC_EnableIRQ(EINT2_IRQn);

	/* LPC11C24: enable start logic for EINT2 (GPIO Port 2 interrupt)
	   - STARTERP0 bit for EINT2 is 29
	   - Use falling edge in STARTAPRP0
	   - Clear any latched start status */
	LPC_SYSCON->STARTERP0 |= (1u << 29);
	LPC_SYSCON->STARTAPRP0 &= ~(1u << 29);
	LPC_SYSCON->STARTRSRP0CLR = (1u << 29);
}


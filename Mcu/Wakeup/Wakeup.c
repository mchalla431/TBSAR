#include "Wakeup.h"
#include "Wakeup_Config.h"
#include "Dio.h"

volatile uint8_t g_wakeup_event = 0U;

void PIOINT2_IRQHandler(void)
{
	/* Clear interrupt on center key pin (PIO2_8) */
	Eint2_Reset(8);
	g_wakeup_event = 1U;
}


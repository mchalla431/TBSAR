#ifndef MCU_WAKEUP_H
#define MCU_WAKEUP_H

#include "lpc11xx.h"

/* Optional flag to observe wake events in application */
extern volatile uint8_t g_wakeup_event;

void PIOINT2_IRQHandler(void);


#endif // MCU_WAKEUP_H

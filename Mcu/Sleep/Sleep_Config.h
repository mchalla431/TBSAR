#ifndef MCU_SLEEP_CONFIG_H
#define MCU_SLEEP_CONFIG_H

#include "lpc11xx.h"

/* =============================================================================
 * Sleep Configuration API
 * Purpose: Low-level PMU and SCR register configuration for sleep
 * ===========================================================================*/

// Configure PMU registers for sleep mode
void Sleep_Config(void);

#endif // MCU_SLEEP_CONFIG_H

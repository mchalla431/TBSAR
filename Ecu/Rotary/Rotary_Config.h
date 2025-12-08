/**
 * @file Rotary_Config.h
 * @brief Rotary encoder hardware configuration header
 */

#ifndef __ROTARY_CONFIG_H__
#define __ROTARY_CONFIG_H__

#include "Syscon.h"
#include "Iocon.h"
#include "Dio_Config.h"

/**
 * @brief Initialize rotary encoder pins
 * 
 * - Phase A (PIO1_5): GPIO with interrupt on rising edge only
 * - Phase B (PIO1_8): GPIO input (polled in ISR)
 * - Switch (PIO0_7): GPIO input (polled in scheduler)
 * 
 * All pins: pull-up and hysteresis enabled.
 */
void Rotary_Config(void);

#endif

/**
 * @file Rotary.h
 * @brief Rotary encoder interface with quadrature decoding and click detection
 */

#ifndef __ROTARY_H__
#define __ROTARY_H__

#include <stdint.h>
#include "Dio.h"

/* Global Variables*/
extern int32_t rcount;       /* Rotary encoder count (increments/decrements) */
extern uint8_t rclicks;      /* Switch click counter */


void Rotary_Clicks(void);
void Rotary_Monitor(void);

#endif

#ifndef __ROTARY_H__
#define __ROTARY_H__


#include "../../Mcu/Dio/Dio.h"
#include "../../Mcu/Gpt/Gpt.h"

/* Rotary Encoder IO Map
Rotary Terminal A is interfaced to GPIO1_5 of MCU
Rotary Terminal B is interfaced to GPIO1_8 of MCU
Rotary Swicth is interfaced to GPIO0_7 of MCU */

// Rotary feature labels
#define ROTARY_DIR_CLK	1
#define ROTARY_DIR_CCLK	2

#define ROTARY_SW_PRESS  1
#define ROTARY_SW_DPRESS 2

// Rotary function prototypes
uint8_t  Rotary_Rotation_Get(uint8_t *cnt);  // returns ROTARY_DIR_CLK/ ROTARY_DIR_CCLK
void Rotary_Rotation_Reset(void);
void Rotary_Rotation_Set(uint8_t cnt);

uint8_t  Rotary_Switch_Get(void);    	 // returns ROTARY_SW_PRESS/ ROTARY_SW_DPRESS

void Rotary_Switch_Clicks_Get(uint8_t *clicks); // Get the clicks by reference variable

#endif


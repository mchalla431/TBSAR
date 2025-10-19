#ifndef __DIO_CONFIG_H__
#define __DIO_CONFIG_H__

#include "Dio.h"


// GPIO Configuration Functions
#define INPUT  0
#define OUTPUT 1
void Gpio0_Direction_Set(int pin, int dir); // pin: 0 to 11,  dir: INPUT/ OUTPUT
void Gpio1_Direction_Set(int pin, int dir);
void Gpio2_Direction_Set(int pin, int dir);
void Gpio3_Direction_Set(int pin, int dir);

// Eint Configuration Functions
#define FALLING_EDGE_TRIGGER 1
#define RISING_EDGE_TRIGGER  2
#define BOTH_EDGE_TRIGGER    3
void Eint0_Edge_Trigger_Set(int pin, int option);
void Eint1_Edge_Trigger_Set(int pin, int option);
void Eint2_Edge_Trigger_Set(int pin, int option);
void Eint3_Edge_Trigger_Set(int pin, int option);

#define LOW_LEVEL_TRIGGER	1
#define HIGH_LEVEL_TRIGGER	2
void Eint0_Level_Trigger_Set(int pin, int option);
void Eint1_Level_Trigger_Set(int pin, int option);
void Eint2_Level_Trigger_Set(int pin, int option);
void Eint3_Level_Trigger_Set(int pin, int option);

#endif

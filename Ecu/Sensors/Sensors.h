#ifndef __SENSORS_H__
#define __SENSORS_H__

#include "../../Mcu/Adc/Adc.h"
#include "../../Mcu/Gpt/Gpt.h"

int Sensor_Vpot_Get(void); // returns milli volts (0 to 3300)
int Sensor_Lm35_Get(void); // returns celsius (0 to 100)
void Sensor_Monitor(void); // Display sensors in single row with emojis

#endif

#ifndef __SENSORS_H__
#define __SENSORS_H__

#include "../../Mcu/Adc/Adc.h"
#include "../../Mcu/Gpt/Gpt.h"


int Sensor_Vpot_Get(void); // returns milli volts (0 to 3300)
int Sensor_Lm35_Get(void); // returns celicus (0 to 100)


#endif

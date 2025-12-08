#ifndef __SENSORS_H__
#define __SENSORS_H__

#include "Adc.h"

/* Global Variables */
extern int vpot_mv;
extern int temp_c;

/* Serial Sensor prototype functions */  
void Sensor_Vpot(void);
void Sensor_Lm35(void);
void Sensor_Monitor(void);

#endif

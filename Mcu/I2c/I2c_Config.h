#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__

#include "I2c.h"

#define I2C_CLOCK_100KHZ 	1
#define I2C_CLOCK_400KHZ	2
void I2c_Clock_Set(int clk);



#endif
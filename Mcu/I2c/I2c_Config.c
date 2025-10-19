#include "I2c_Config.h"

#define I2C_Update_SCLL(val)		I2C_SCLL = val
#define I2C_Update_SCLH(val)		I2C_SCLH = val
#define I2C_Enable()				I2C_CONSET = (1<<6)
#define I2C_Disable()				I2C_CONCLR = (1<<6)

void I2c_Clock_Set(int clk)
{
	switch(clk)
	{
		case I2C_CLOCK_100KHZ:
			I2C_Update_SCLL(240);
			I2C_Update_SCLH(240);	
			break;

		case I2C_CLOCK_400KHZ:
			I2C_Update_SCLL(60);
			I2C_Update_SCLH(60);	
			break;
	}
	I2C_Enable();
}


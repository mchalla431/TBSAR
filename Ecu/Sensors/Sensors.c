#include "Sensors.h"
#include "Gpt_Config.h"
#include "Monitor.h"


int Sensor_Vpot_Get(void)
{
	int a2d, mvolts =0;

	// Select the Adc input channel
	Adc_Input_Select(0);
	
	// Start the Adc
	Adc_Start();
	
	// Wait for the conversion
	Adc_Conversion_Wait(0);
	
	// Stop the Adc
	Adc_Stop();
	
	// Read a2d count
	a2d = Adc_Count_Get(0);
	
	// Measure the voltage in milli-volts (Adc step size = 3.22mv)
	mvolts = (a2d * 3226)/1000;
	
	return mvolts;
}

int Sensor_Lm35_Get(void)
{
	int a2d, temp =0;
	
	// Select the Adc input channel
	Adc_Input_Select(1);
	
	// Start the Adc
	Adc_Start();
	
	// Wait for the conversion
	Adc_Conversion_Wait(1);
	
	// Stop the Adc
	Adc_Stop();
	
	// Read a2d count
	a2d = Adc_Count_Get(1);
	
	// Measure the temperature in Celsius (Adc step size = 3.22mv)
	temp = a2d/3;

	return temp;
}

void Sensor_Monitor(void)
{
	int vpot_mv, temp_c;
	
	// Read sensor values
	vpot_mv = Sensor_Vpot_Get();
	temp_c = Sensor_Lm35_Get();
	
	// Convert voltage to decimal format (e.g., 1650mv = 1.65V)
	int voltage_int = vpot_mv / 1000;
	int voltage_dec = (vpot_mv % 1000) / 100;  // One decimal place
	
	// Display sensors in single row with steady display and emojis
	uart_printf("\r\x1b[2K[SENSORS] 🔋:%d.%dV 🌡️:%d°C   ", 
	           voltage_int, voltage_dec, temp_c);
}


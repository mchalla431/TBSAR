#include "Sensors.h"
#include "Monitor.h"

/* Global sensor variables */
int vpot_mv = 0;      /* Potentiometer voltage in mV */
int temp_c = 0;       /* LM35 temperature in Celsius */

void Sensor_Vpot(void)
{
	int a2d;
	
	// Read ADC channel 0 (Vpot on PIO0_11)
	a2d = Adc_Read_Count_Channel(0);
	
	// Convert to millivolts (3.226mV per count)
	vpot_mv = (a2d * 3226) / 1000;
}

void Sensor_Lm35(void)
{
	static int count = 0;
	static int sum = 0;
	int a2d;
	
	// Read ADC sample from channel 1 (LM35 on PIO1_0)
	a2d = Adc_Read_Count_Channel(1);
	
	// Accumulate 5 samples
	sum += a2d;
	count++;
	
	// Calculate average and convert to Celsius every 5 samples (50ms)
	if (count >= 5) 
	{
		count = 0;
		a2d = sum / 5;
		
		// Convert: LM35 outputs 10mV/°C, ADC is 3.226mV/count
		temp_c = a2d/3;
		
		sum = 0;
	}
}



void Sensor_Monitor(void)
{
	// Display Vpot (0.1V resolution) and LM35 (1°C resolution) on single line
	int vpot_volt = vpot_mv / 1000;
	int vpot_frac = (vpot_mv % 1000) / 100;
	
	uart_printf("\rVpot:");
	uart_printf("%d", vpot_volt);
	uart_printf(".");
	uart_printf("%d", vpot_frac);
	uart_printf("V | LM35:");
	uart_printf("%d", temp_c);
	uart_printf("C    ");
}

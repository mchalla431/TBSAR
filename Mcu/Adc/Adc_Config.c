#include "Adc_Config.h"


void Adc_Clock_Set(int clk)
{
	uint8_t val =0;
	
	switch(clk)
	{
		case ADC_CLOCK_1MHZ:	
			val = 47;	
			break;	
		
		case ADC_CLOCK_2MHZ:	
			val = 23;	
			break;	
		
		case ADC_CLOCK_4MHZ:	
			val = 11;	
			break;	
	}
	
	ADC_CR = ( ADC_CR & ~(0xff <<8) ) | (val<<8); 
}


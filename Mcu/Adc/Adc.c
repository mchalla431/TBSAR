#include "Adc.h"
#include "../Sys/lpc11xx.h"

/* ADC Driver macros */

#define A2D_Start()				ADC_CR |= (1<<24)
#define A2D_Stop()				ADC_CR &= ~(1<<24)

#define A2D_Wait(ch)			while(!(LPC_ADC->DR[ch] & (1u<<31)))

#define MASK_10BIT  0x3FF  // 0000 0011 1111 1111
#define A2D_Count(ch)			((LPC_ADC->DR[ch] >> 6) & MASK_10BIT)

/* ADC Driver Functions */

void Adc_Input_Select(int ch)
{
	ADC_CR = (ADC_CR & ~(0xff)) | (1<<ch);
}

int Adc_Input_Get(void)
{
	int ch=0;

	ch = (ADC_GDR >> 24) & 0x07;
	
	return ch;
}

void Adc_Start(void)
{
	A2D_Start();
}


void  Adc_Conversion_Wait(int ch)
{
	A2D_Wait(ch);
}


void Adc_Stop(void)
{
	A2D_Stop();
}

uint16_t Adc_Count_Get(int ch)
{
	uint16_t a2d;
	
	a2d = A2D_Count(ch);
	
	return a2d;
	
}


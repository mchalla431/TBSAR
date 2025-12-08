#include "Adc.h"

/* ADC Driver macros */

#define A2D_Start()				ADC_CR |= (1<<24)
#define A2D_Stop()				ADC_CR &= ~(1<<24)

#define A2D_Wait(ch)			while(!(LPC_ADC->DR[ch] & (1u<<31)))

#define MASK_10BIT  0x3FF  // 0000 0011 1111 1111
#define A2D_Count(ch)			((LPC_ADC->DR[ch] >> 6) & MASK_10BIT)

/* ADC Driver inline functions */

static inline void Adc_Input_Select(int ch)
{
	ADC_CR = (ADC_CR & ~(0xff)) | (1<<ch);
}


static inline void Adc_Start(void)
{
	A2D_Start();
}

static inline void Adc_Conversion_Wait(int ch)
{
	A2D_Wait(ch);
}

static inline void Adc_Stop(void)
{
	A2D_Stop();
}

static inline uint16_t Adc_Count_Get(int ch)
{
	uint16_t a2d;
	
	a2d = A2D_Count(ch);
	
	return a2d;
}

uint16_t Adc_Read_Count_Channel(int ch)
{
	uint16_t count;
	
	Adc_Input_Select(ch);
	Adc_Start();
	Adc_Conversion_Wait(ch);
	count = Adc_Count_Get(ch);
	Adc_Stop();
	
	return count;
}


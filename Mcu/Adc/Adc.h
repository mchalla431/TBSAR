#ifndef __ADC_H__
#define __ADC_H__

#include <stdint.h>
#include "lpc11xx.h"

/* ADC Driver Function Prototype Declarations */
void Adc_Input_Select(int ch);  // 0 to 7
int Adc_Input_Get(void);
void Adc_Start(void);
void Adc_Conversion_Wait(int ch);
void Adc_Stop(void);
uint16_t Adc_Count_Get(int ch); // returns 10-bit count

#endif

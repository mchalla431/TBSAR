#ifndef __DAC_H__
#define __DAC_H__

#include "Dio.h"
#include "Spi.h"
#include "Syscon.h"
#include "Adc.h"

/* Serial Dac prototype functions */  
		
void Dac_Set_Input(uint16_t val);     // Complete DAC operation: select, update, deselect
uint16_t Dac_Get_Output(void);        // Get DAC output voltage in mV (0-3300mV)
void Dac_Monitor(void);               // Display DAC A2D count and voltage

#endif


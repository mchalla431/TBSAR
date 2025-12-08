#ifndef __DAC_H__
#define __DAC_H__

#include "Dio.h"
#include "Spi.h"
#include "Adc.h"

/* Global Variables */
extern uint16_t dac_in;
extern uint16_t dac_a2d;

/* Serial Dac prototype functions */  
void Dac_Set_Input(void);
void Dac_Get_A2d(void);
void Dac_Monitor(void);

#endif


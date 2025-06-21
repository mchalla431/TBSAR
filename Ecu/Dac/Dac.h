#ifndef __DAC_H__
#define __DAC_H__

#include "../../Mcu/Dio/Dio.h"
#include "../../Mcu/Spi/Spi.h"
#include "../../Mcu/Sys/Syscon.h"
#include "../../Mcu/Gpt/Gpt.h"

/* Serial Dac prototype functions */  

void Dac_Chip_Select(void); 	// Select the DAC Chip (GPIO0_2 pin set to LOW)
void Dac_Chip_Deselect(void);   // Deselect the DAC chip (GPIO0_2 set to HIGH)
		
uint16_t Dac_Value_Update(uint16_t val);

#endif


#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>
#include "../Sys/lpc11xx.h"

/* SPI Driver Function Prototype Declarations */

int Spi_Transfer_Status_Get(void);
void Spi_Shift_Register_Set(uint16_t dat);
uint16_t Spi_Shift_Register_Get(void);


#endif

#include "Spi.h"

#define SPI_Data_Write(dat)		SPI_DR = dat
#define SPI_Data_Read()			SPI_DR

#define SPI_Get_Status()		( (SPI_SR & (1<<4))?1:0 )		


int Spi_Transfer_Status_Get(void)
{
	return (SPI_Get_Status());
}



void Spi_Shift_Register_Set(uint16_t dat)
{
	SPI_Data_Write(dat);
}

uint16_t Spi_Shift_Register_Get(void)
{
	return (SPI_Data_Read());
}


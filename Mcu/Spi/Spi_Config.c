/**
 * @file Spi_Config.c
 * @brief SPI configuration - clock mode, prescaler, data size
 */
#include "Spi_Config.h"

#define SPI_Master_MCU()		SPI_CR1 &= ~(1<<2)
#define SPI_Slave_MCU()			SPI_CR1 |=  (1<<2)

#define SPI_Enable()			SPI_CR1 |= (1<<1)	
#define SPI_Disable()			SPI_CR1 &= ~(1<<1)

#define SPI_Update_CPSR(val)	SPI_CPSR = val

/* Set data frame size: 8-bit (val=7) or 16-bit (val=15) in CR0[3:0] */
void Spi_Data_Size_Set(int dsize) 
{
	int val =0;
	
	switch(dsize)
	{
		case SPI_DATA_8BIT:  val = 7;   break;
		case SPI_DATA_16BIT: val = 0xf; break;
	}
	
	SPI_CR0 = ( SPI_CR0 & ~(0xf<<0) ) | (val <<0);
}

/* Configure clock phase (CPHA) and polarity (CPOL) bits in CR0 */
void Spi_Mode_Set(int mode)
{
	SPI_Master_MCU();
	
	switch(mode)
	{
		case SPI_MODE0:	 SPI_CR0 &= ~(1<<6); SPI_CR0 &= ~(1<<7); break;  /* CPOL=0, CPHA=0 */
		case SPI_MODE1:	 SPI_CR0 &= ~(1<<6); SPI_CR0 |=  (1<<7); break;  /* CPOL=0, CPHA=1 */
		case SPI_MODE2:	 SPI_CR0 |=  (1<<6); SPI_CR0 &= ~(1<<7); break;  /* CPOL=1, CPHA=0 */
		case SPI_MODE3:	 SPI_CR0 |=  (1<<6); SPI_CR0 |=  (1<<7); break;  /* CPOL=1, CPHA=1 */
	}
}

/* Set SPI clock via prescaler and enable peripheral */
void Spi_Clock_Set(int clk)
{
	int val =0;
	switch(clk)
	{
		case SPI_CLOCK_1MHZ:  val =48; break;  /* ~1MHz @ 48MHz sysclock */
		case SPI_CLOCK_10MHZ: val =5;  break;  /* ~9.6MHz @ 48MHz sysclock */
	}	
	
	SPI_Update_CPSR(val);
	SPI_Enable();
}



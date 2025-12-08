/**
 * @file Spi.c
 * @brief SPI (Serial Peripheral Interface) driver for LPC11xx
 * 
 * Provides low-level SPI communication primitives including data transfer
 * with blocking wait for transmission completion.
 */

#include "Spi.h"

/** @brief Write data to SPI data register */
#define SPI_Data_Write(dat)		SPI_DR = dat

/** @brief Read data from SPI data register */
#define SPI_Data_Read()			SPI_DR

/** @brief Check if SPI transmission complete (bit 4 = SPIF flag) */
#define SPI_Get_Status()		( (SPI_SR & (1<<4))?1:0 )


/**
 * @brief Transfer 16-bit data over SPI with blocking wait
 * 
 * Writes data to SPI output register and waits for transmission complete
 * (SPIF flag set in status register). Returns received data from input
 * register after transmission completes.
 * 
 * @param dat 16-bit data to transmit
 * @return uint16_t Data received from slave device
 */
uint16_t Spi_Transfer(uint16_t dat)
{
	/* Load data into SPI output register (triggers transmission) */
	SPI_Data_Write(dat);
	
	/* Wait for SPIF (Spi Transfer In Progress Flag) to complete */
	while(SPI_Get_Status());
	
	/* Read and return received data */
	return SPI_Data_Read();
}
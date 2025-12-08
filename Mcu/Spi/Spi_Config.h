/**
 * @file Spi_Config.h
 * @brief SPI hardware configuration interface
 */
#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

#include "Spi.h"

#define SPI_DATA_8BIT  1
#define SPI_DATA_16BIT 2
void Spi_Data_Size_Set(int dsize);

#define SPI_MODE0	1
#define SPI_MODE1	2
#define SPI_MODE2	3
#define SPI_MODE3	4
void Spi_Mode_Set(int mode);

#define SPI_CLOCK_1MHZ  1
#define SPI_CLOCK_10MHZ 2
void Spi_Clock_Set(int clk);

#endif
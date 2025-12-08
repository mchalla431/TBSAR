/**
 * @file Spi.h
 * @brief SPI (Serial Peripheral Interface) driver header for LPC11xx
 * 
 * Defines SPI communication interface and function prototypes.
 */

#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>
#include "Spi.h"
#include "lpc11xx.h"

/**
 * @brief Transfer data over SPI in full-duplex mode
 * 
 * Transmits 16-bit data and receives 16-bit response in blocking fashion.
 * Waits for transmission to complete before returning.
 * 
 * @param dat Data to transmit to SPI slave
 * @return Received data from SPI slave
 */
uint16_t Spi_Transfer(uint16_t dat);

#endif

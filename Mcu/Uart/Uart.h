#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include "lpc11xx.h"
#include "Uart.h"



void uart_printf(const char *format, ...);

#endif
#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include "Uart.h"
#include "lpc11xx.h"

/* UART communication functions */
void Uart_Byte_Send(uint8_t dat);
void Uart_String_Send(const char *str);
uint8_t Uart_Byte_Receive(void);

void uart_printf(const char *format, ...);

#endif
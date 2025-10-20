#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include "../Sys/lpc11xx.h"

/* UART communication functions */
void Uart_Byte_Send(uint8_t dat);
void Uart_String_Send(char *str);
uint8_t Uart_Byte_Receive(void);

#endif
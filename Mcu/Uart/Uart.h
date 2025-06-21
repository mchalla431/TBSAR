#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include "../Sys/lpc11xx.h"

int Uart_Transmit_Buffer_Check(void);
void Uart_Transmit_Buffer_Write(uint8_t byte);
int Uart_Receive_Buffer_Check(void);
uint8_t Uart_Receive_Buffer_Read(void);

#endif
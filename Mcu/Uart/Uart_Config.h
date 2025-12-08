#ifndef __UART_CONFIG_H__
#define __UART_CONFIG_H__

#include "Uart.h"

#define UART_DATA_5BIT 0
#define UART_DATA_6BIT 1
#define UART_DATA_7BIT 2
#define UART_DATA_8BIT 3
void Uart_Data_Size_Set(int option);

/* UART Baudrate Definitions */
#define UART_BAUD_9600  	1
#define UART_BAUD_19200 	2
#define UART_BAUD_38400 	3
#define UART_BAUD_57600 	4
#define UART_BAUD_115200	5
void Uart_Baudrate_Set(int baud);



#endif



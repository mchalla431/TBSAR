#ifndef __PC_COM_H__
#define __PC_COM_H__

#include "../../Mcu/Sys/Syscon.h"
#include "../../Mcu/Uart/Uart.h"
#include "../../Mcu/Gpt/Gpt.h"
#include <stdio.h>

// PC Communication functions
void Pc_Com_Byte_Send(uint8_t dat);
void Pc_Com_String_Send(char *str);
uint8_t Pc_Com_Byte_Receive(void);

// Printf support - automatically redirected to UART
// Usage: printf("Hello World!\n");
//        printf("Value: %d\n", 42);




#endif

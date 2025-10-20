#ifndef __MONITOR_H__
#define __MONITOR_H__

#include "../../Mcu/Sys/Syscon.h"
#include "../../Mcu/Uart/Uart.h"
#include "../../Mcu/Gpt/Gpt.h"
#include <stdio.h>

// High-level UART printf functionality
void uart_printf(const char* format, ...);

#endif

#ifndef __MONITOR_H__
#define __MONITOR_H__

#include "Monitor.h"
#include "Syscon.h"
#include "Uart.h"
#include "Gpt.h"
#include <stdio.h>

// High-level UART printf functionality
void uart_printf(const char* format, ...);

#endif

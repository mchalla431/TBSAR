#ifndef APP_HOOKS_H
#define APP_HOOKS_H

#include "FreeRTOS.h"
#include "task.h"


void vApplicationMallocFailedHook(void);
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName);
void vApplicationIdleHook(void);
void vApplicationTickHook(void);

#endif // APP_HOOKS_H

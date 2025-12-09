#include "AppHooks.h"

#include "FreeRTOS.h"
#include "task.h"

void vApplicationMallocFailedHook(void)
{
    /* Handle memory allocation failure (optional: add logging or reset) */
    taskDISABLE_INTERRUPTS();
    for(;;);
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    /* Handle stack overflow (optional: add logging or reset) */
    (void)xTask;
    (void)pcTaskName;
    taskDISABLE_INTERRUPTS();
    for(;;);
}

void vApplicationIdleHook(void)
{
    /* Idle task hook (optional: add low-power or background code) */
}

void vApplicationTickHook(void)
{
    /* Tick ISR hook (optional: add periodic code) */
}


/**
 * @file main.c
 * @brief TBSAR Main Application
 * @author Murali Challa
 * @date 2025-12-07
 */

#include <stdint.h>
#include <stddef.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Buz_Config.h"



/* Example FreeRTOS task */
void vMainTask(void *pvParameters)
{
    for(;;)
    {
        // Main application loop
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}


/* =============================================================================
 * Main Function
 * ===========================================================================*/

int main(void)
{
    /* Initialize hardware */
    Buz_Config();      /* on-board buzzer calm at startup */

    /* Create main FreeRTOS task */
    xTaskCreate(vMainTask, "MainTask", 128, NULL, 1, NULL);

    /* Start FreeRTOS scheduler */
    vTaskStartScheduler();

    /* Should never reach here */
    for(;;);
}

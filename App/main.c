/**
 * @file main.c
 * @brief TBSAR Main Application -
 * @author Murali Challa
 * @date 2025-10-20
 * 
 */

#include "Monitor.h"
#include "Monitor_Config.h"

/**
 * @brief Simple software delay function
 * @param count Number of loops to delay
 */
void Software_Delay(volatile uint32_t count)
{
    while (count--) {
        // Simple busy wait loop
        __asm("nop");
    }
}

/**
 * @brief Main function 
 */
int main(void) 
{
    
    // Initialize Monitor Communication (UART for printf)
    Monitor_Config();
    
    
    while (1) 
    {

    }
    
    return 0;
}
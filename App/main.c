/**
 * @file main.c
 * @brief TBSAR Main Application
 * @author Murali Challa
 * @date 2025-12-07
 */

#include <stdint.h>
#include "Scheduler.h"
#include "Buz_Config.h"

/* =============================================================================
 * Scheduler Task: Every 10ms
 * ===========================================================================*/
void Scheduler_10ms(void)
{

}

/* =============================================================================
 * Scheduler Task: Every 20ms
 * ===========================================================================*/
void Scheduler_20ms(void)
{

}

/* =============================================================================
 * Scheduler Task: Every 50ms
 * ===========================================================================*/
void Scheduler_50ms(void)
{

}

/* =============================================================================
 * Scheduler Task: Every 100ms
 * ===========================================================================*/
void Scheduler_100ms(void)
{

}


/* =============================================================================
 * Main Function
 * ===========================================================================*/
int main(void) 
{
    /* Initialize hardware */
    Buz_Config();      /* on-board buzzer calm at startup */
    
   
    /* Start scheduler (10ms base tick) */
    Scheduler_Init();
    
    while(1) 
    {
        __asm volatile("wfi");  
    }   

    return 0;
}

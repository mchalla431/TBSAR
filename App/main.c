/**
 * @file main.c
 * @brief TBSAR Main Application
 * @author Murali Challa
 * @date 2025-12-07
 */

#include <stdint.h>
#include "Scheduler.h"
#include "Buz_Config.h"
#include "Buz.h"
#include "Monitor_Config.h"

#include "Pwm_Config.h"
#include "Pwm.h"

#include "Ukeys_Config.h"
#include "Ukeys.h"

#include "Lcd_Config.h"
#include "Lcd.h"


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
    Monitor_Config(); /* UART monitor initialization */
    Ukeys_Config();     /* Ukeys hardware initialization */
    Lcd_Config();     /* LCD hardware initialization */
    
    
    /* Start scheduler (10ms base tick) */
    Scheduler_Init();

   
    while(1) 
    {
        __asm volatile("wfi");  
    }   

    return 0;
}

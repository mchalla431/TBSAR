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
    static uint8_t sec_counter = 0;
    static uint8_t duty = 10;
    sec_counter++;
    if (sec_counter >= 10) 
    { // 10 x 100ms = 1s
        sec_counter = 0;
        duty += 10;
        if (duty > 90) duty = 10;
        pwm_duty = duty;
        Pwm_Set();
        Pwm_Monitor();

        Lcd_Set_Cursor(1,1);
        lcd_printf("PWM:%4luHz %3lu%%  ", pwm_freq, pwm_duty);
        Lcd_Set_Cursor(2,1);
        lcd_printf("Volt:%4lumV     ", pwm_volt);
    }
}


/* =============================================================================
 * Main Function
 * ===========================================================================*/
int main(void) 
{
    /* Initialize hardware */
    Buz_Config();      /* on-board buzzer calm at startup */
    Monitor_Config(); /* UART monitor initialization */
    Pwm_Config();     /* PWM hardware initialization */
    Lcd_Config();     /* LCD hardware initialization */
    pwm_freq = 1000; // 1kHz
    Pwm_Set();
    
    
    /* Start scheduler (10ms base tick) */
    Scheduler_Init();

   
    while(1) 
    {
        __asm volatile("wfi");  
    }   

    return 0;
}

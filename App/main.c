/**
 * @file main.c
 * @brief TBSAR Main Application - RGB Green Blink
 * @author Murali Challa
 * @date 2025-10-23
 * 
 */

#include <stdint.h>
#include "Syscon.h"
#include "Iocon.h"

/**
 * @brief Software delay function in milliseconds
 * @param ms Delay time in milliseconds  
 * @note Calibrated for LPC11C24 at 48MHz with -O2 optimization
 */
void Software_Delay_Ms(volatile uint32_t ms)
{
    // Further reduced for more accurate timing on LPC11C24
    // With -O2 optimization, roughly 4000 loops per millisecond
    volatile uint32_t cycles_per_ms = 4000;
    
    while (ms--) {
        volatile uint32_t count = cycles_per_ms;
        while (count--) {
            __asm volatile("nop");
        }
    }
}


void Buz_Config(void)
{
    Syscon_Pclk_Iocon_Enable();
    Iocon_Pio0_8_Set(0, 1, 0, 0, 0, 0);
}

/**
 * @brief Main function - DAC Test Application
 */
int main(void) 
{
    
    // Initialize Buzzer Configuration
    Buz_Config();

   
    while (1) 
    {
        
        
    }
    
    return 0;
}
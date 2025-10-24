/**
 * @file main.c
 * @brief TBSAR Main Application - RGB Green Blink
 * @author Murali Challa
 * @date 2025-10-23
 * 
 * Simple RGB green LED blinking application.
 */

#include "Monitor.h"
#include "Monitor_Config.h"
#include "Rgb.h"
#include "Rgb_Config.h"

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
 * @brief Main function - RGB Green Blink Application
 */
int main(void) 
{
    // Initialize Monitor Communication (UART for printf)
    Monitor_Config();

   Buz_Config();

    // Initialize RGB LED
    Rgb_Config();
    
    uart_printf("\r\n🚀 TBSAR RGB Green Blink Application Started!\r\n");
    
    // Main RGB green blinking loop
    while (1) 
    {
        // Turn on green LED
        Rgb_Set(RGB_GREEN);
        Rgb_Monitor(RGB_GREEN);
        Software_Delay_Ms(500);  // 500ms delay
        
        // Turn off green LED
        Rgb_Set(RGB_NONE);
        Rgb_Monitor(RGB_NONE);
        Software_Delay_Ms(500);  // 500ms delay
    }
    
    return 0;
}
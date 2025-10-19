#include "../Ecu/Rgb/Rgb.h"
#include "../Ecu/Rgb/Rgb_Config.h"

/**
 * @brief Software delay function - longer delays for debugging
 * @param delay_count Number of delay loops
 */
void Software_Delay(uint32_t delay_count)
{
    volatile uint32_t i;
    for (i = 0; i < delay_count; i++)
    {
        __asm("nop"); // No operation - prevents optimization
    }
}

int main(void)
{
    // Initialize RGB LED configuration
    Rgb_Config();
    
    // Green LED test - blink every 500ms
    while (1)
    {
        // Turn GREEN LED ON
        Rgb_Set(RGB_GREEN);
        Software_Delay(500000);  // 500ms ON
        
        // Turn GREEN LED OFF
        Rgb_Set(RGB_NONE);
        Software_Delay(500000);  // 500ms OFF
    }
    
    return 0;
}
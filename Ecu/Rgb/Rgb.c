#include "Rgb.h"
#include "Monitor.h"  // For uart_printf


void Rgb_Set(int option)
{
	switch(option)
	{
		case RGB_NONE:
			Gpio2_Pin_Set(10, HIGH);	// Red LED is Off 
			Gpio1_Pin_Set(2, HIGH);    	// Green LED is Off
			Gpio2_Pin_Set(2, HIGH);   	// Blue LED is Off
			break;
			
		case RGB_RED:
			Gpio2_Pin_Set(10, LOW);		// Red LED is On 
			Gpio1_Pin_Set(2, HIGH);    	// Green LED is Off
			Gpio2_Pin_Set(2, HIGH);   	// Blue LED is Off
			break;
		
		case RGB_GREEN:
			Gpio2_Pin_Set(10, HIGH);	// Red LED is Off 
			Gpio1_Pin_Set(2, LOW);    	// Green LED is On
			Gpio2_Pin_Set(2, HIGH);   	// Blue LED is Off
			break;
		
		case RGB_BLUE:
			Gpio2_Pin_Set(10, HIGH);	// Red LED is Off 
			Gpio1_Pin_Set(2, HIGH);    	// Green LED is Off
			Gpio2_Pin_Set(2, LOW);   	// Blue LED is On
			break;
		
		case RGB_YELLOW:
			Gpio2_Pin_Set(10, LOW);		// Red LED is On 
			Gpio1_Pin_Set(2, LOW);    	// Green LED is On
			Gpio2_Pin_Set(2, HIGH);   	// Blue LED is Off
			break;
		
		case RGB_MAGENTA:
			Gpio2_Pin_Set(10, LOW);		// Red LED is On 
			Gpio1_Pin_Set(2, HIGH);    	// Green LED is Off
			Gpio2_Pin_Set(2, LOW);   	// Blue LED is On
			break;
		
		case RGB_CYAN:
			Gpio2_Pin_Set(10, HIGH);	// Red LED is Off 
			Gpio1_Pin_Set(2, LOW);    	// Green LED is On
			Gpio2_Pin_Set(2, LOW);   	// Blue LED is On
			break;
		
		case RGB_WHITE:
			Gpio2_Pin_Set(10, LOW);		// Red LED is On 
			Gpio1_Pin_Set(2, LOW);    	// Green LED is On
			Gpio2_Pin_Set(2, LOW);   	// Blue LED is On
			break;
	}	
}

void Rgb_Monitor(int rgb_state)
{
    uart_printf("\r\x1b[2K\x1b[37m[RGB Status] ");
    
    switch(rgb_state)
    {
        case RGB_NONE:
            uart_printf("\x1b[90m⚫ OFF     \x1b[0m");
            break;
        case RGB_RED:
            uart_printf("\x1b[91m🔴 RED     \x1b[0m");
            break;
        case RGB_GREEN:
            uart_printf("\x1b[92m🟢 GREEN   \x1b[0m");
            break;
        case RGB_BLUE:
            uart_printf("\x1b[94m🔵 BLUE    \x1b[0m");
            break;
        case RGB_YELLOW:
            uart_printf("\x1b[93m🟡 YELLOW  \x1b[0m");
            break;
        case RGB_MAGENTA:
            uart_printf("\x1b[95m🟣 MAGENTA \x1b[0m");
            break;
        case RGB_CYAN:
            uart_printf("\x1b[96m🔵 CYAN    \x1b[0m");
            break;
        case RGB_WHITE:
            uart_printf("\x1b[97m⚪ WHITE   \x1b[0m");
            break;
        default:
            uart_printf("\x1b[91m❌ ERROR   \x1b[0m");
            break;
    }
}

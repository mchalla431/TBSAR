#include "Rgb.h"
#include "../../Mcu/Gpt/Gpt_Config.h"


void Rgb_Set(int option)
{
	switch(option)
	{
		case RGB_NONE:
			Gpio2_Pin_Set(10, HIGH);	// Red LED is Off 
			Gpio1_Pin_Set(2, HIGH);    	// Green LED is Off
			Gpio1_Pin_Set(10, HIGH);   	// Blue LED is Off
			break;
			
		case RGB_RED:
			Gpio2_Pin_Set(10, LOW);		// Red LED is On 
			Gpio1_Pin_Set(2, HIGH);    	// Green LED is Off
			Gpio1_Pin_Set(10, HIGH);   	// Blue LED is Off
			break;
		
		case RGB_GREEN:
			Gpio2_Pin_Set(10, HIGH);	// Red LED is Off 
			Gpio1_Pin_Set(2, LOW);    	// Green LED is On
			Gpio1_Pin_Set(10, HIGH);   	// Blue LED is Off
			break;
		
		case RGB_BLUE:
			Gpio2_Pin_Set(10, HIGH);	// Red LED is Off 
			Gpio1_Pin_Set(2, HIGH);    	// Green LED is Off
			Gpio1_Pin_Set(10, LOW);   	// Blue LED is On
			break;
		
		case RGB_YELLOW:
			Gpio2_Pin_Set(10, LOW);		// Red LED is On 
			Gpio1_Pin_Set(2, LOW);    	// Green LED is On
			Gpio1_Pin_Set(10, HIGH);   	// Blue LED is Off
			break;
		
		case RGB_MAGENTA:
			Gpio2_Pin_Set(10, LOW);		// Red LED is On 
			Gpio1_Pin_Set(2, HIGH);    	// Green LED is Off
			Gpio1_Pin_Set(10, LOW);   	// Blue LED is On
			break;
		
		case RGB_CYAN:
			Gpio2_Pin_Set(10, HIGH);	// Red LED is Off 
			Gpio1_Pin_Set(2, LOW);    	// Green LED is On
			Gpio1_Pin_Set(10, LOW);   	// Blue LED is On
			break;
		
		case RGB_WHITE:
			Gpio2_Pin_Set(10, LOW);		// Red LED is On 
			Gpio1_Pin_Set(2, LOW);    	// Green LED is On
			Gpio1_Pin_Set(10, LOW);   	// Blue LED is On
			break;

		case RGB_RED_BLINK:
			Gpio2_Pin_Set(10, TOGGLE);	// Red LED Blink 
			Gpio1_Pin_Set(2, HIGH);    	// Green LED is Off
			Gpio1_Pin_Set(10, HIGH);   	// Blue LED is Off
			break;

		case RGB_GREEN_BLINK:
			Gpio2_Pin_Set(10, HIGH);	// Red LED is Off 
			Gpio1_Pin_Set(2, TOGGLE);  	// Green LED Blink
			Gpio1_Pin_Set(10, HIGH);   	// Blue LED is Off
			break;

		case RGB_BLUE_BLINK:
			Gpio2_Pin_Set(10, HIGH);	// Red LED is Off 
			Gpio1_Pin_Set(2, HIGH);  	// Green LED is Off
			Gpio1_Pin_Set(10, TOGGLE);  // Blue LED Blink
			break;
	}	
}

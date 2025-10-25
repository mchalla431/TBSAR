#include "Ukeys.h"
#include "Gpt_Config.h"
#include "Monitor.h"


uint8_t Ukey_Up_State_Get(void)
{
	uint8_t uk = UNTOUCH, pn = HIGH;
	
	pn = Gpio0_Pin_Get(3);
	
	if(LOW == pn)
	{
		uk = TOUCH;
	}	
	return uk;
}

uint8_t Ukey_Down_State_Get(void)
{
	uint8_t uk = UNTOUCH, pn = HIGH;
	
	pn = Gpio2_Pin_Get(6);
	
	if(LOW == pn)
	{
		uk = TOUCH;
	}	
	return uk;
}

uint8_t Ukey_Center_State_Get(void)
{
	uint8_t uk = UNTOUCH, pn = HIGH;
	
	pn = Gpio2_Pin_Get(8);
	
	if(LOW == pn)
	{
		uk = TOUCH;
	}	
	return uk;
}

uint8_t Ukey_Left_State_Get(void)
{
	uint8_t uk = UNTOUCH, pn = HIGH;
	
	pn = Gpio2_Pin_Get(7);
	
	if(LOW == pn)
	{
		uk = TOUCH;
	}	
	return uk;
}

uint8_t Ukey_Right_State_Get(void)
{
	uint8_t uk = UNTOUCH, pn = HIGH;
	
	pn = Gpio1_Pin_Get(4);
	
	if(LOW == pn)
	{
		uk = TOUCH;
	}	
	return uk;
}

void Ukey_Up_Clicks_Get(uint8_t *clicks)
{
	uint8_t state_current  = UNTOUCH;
	static uint8_t state_previous = UNTOUCH;
	
	state_current = Ukey_Up_State_Get();
	
	if(state_current == UNTOUCH)
	{
		if(state_previous == TOUCH)
		{
			(*clicks)++;
		}	
	}	
	state_previous = state_current;
}  

void Ukey_Down_Clicks_Get(uint8_t *clicks)
{
	uint8_t state_current  = UNTOUCH;
	static uint8_t state_previous = UNTOUCH;
	
	state_current = Ukey_Down_State_Get();
	
	if(state_current == UNTOUCH)
	{
		if(state_previous == TOUCH)
		{
			(*clicks)++;
		}	
	}	
	state_previous = state_current;
}  

void Ukey_Center_Clicks_Get(uint8_t *clicks)
{
	uint8_t state_current  = UNTOUCH;
	static uint8_t state_previous = UNTOUCH;
	
	state_current = Ukey_Center_State_Get();
	
	if(state_current == UNTOUCH)
	{
		if(state_previous == TOUCH)
		{
			(*clicks)++;
		}	
	}	
	state_previous = state_current;
}

void Ukey_Left_Clicks_Get(uint8_t *clicks) 
{
	uint8_t state_current  = UNTOUCH;
	static uint8_t state_previous = UNTOUCH;
	
	state_current = Ukey_Left_State_Get();
	
	if(state_current == UNTOUCH)
	{
		if(state_previous == TOUCH)
		{
			(*clicks)++;
		}	
	}	
	state_previous = state_current;
}

void Ukey_Right_Clicks_Get(uint8_t *clicks)
{
	uint8_t state_current  = UNTOUCH;
	static uint8_t state_previous = UNTOUCH;
	
	state_current = Ukey_Right_State_Get();
	
	if(state_current == UNTOUCH)
	{
		if(state_previous == TOUCH)
		{
			(*clicks)++;
		}	
	}	
	state_previous = state_current;
}

void Ukeys_Status_Monitor(uint8_t up, uint8_t down, uint8_t left, uint8_t center, uint8_t right)
{
    // Enhanced status display with dark green arrows using improved uart_printf
    uart_printf("\r\x1b[2K[UKEYS] \x1b[32m⬆️\x1b[0m:%s \x1b[32m⬇️\x1b[0m:%s 🎯:%s \x1b[32m⬅️\x1b[0m:%s \x1b[32m➡️\x1b[0m:%s   ",
               (up == TOUCH) ? "ON" : "__",
               (down == TOUCH) ? "ON" : "__",
               (center == TOUCH) ? "ON" : "__",
               (left == TOUCH) ? "ON" : "__",
               (right == TOUCH) ? "ON" : "__");
}

void Ukeys_Clicks_Monitor(uint8_t up_clicks, uint8_t down_clicks, uint8_t left_clicks, uint8_t center_clicks, uint8_t right_clicks)
{
    // Enhanced clicks display with proper spacing and same order as status monitor
    uart_printf("\r\x1b[2K\x1b[35m[CLICKS] \x1b[32m⬆️\x1b[97m:%u \x1b[32m⬇️\x1b[97m:%u \x1b[35m🎯\x1b[97m:%u \x1b[32m⬅️\x1b[97m:%u \x1b[32m➡️\x1b[97m:%u\x1b[0m   ",
        up_clicks, down_clicks, center_clicks, left_clicks, right_clicks
    );
}
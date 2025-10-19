#include "Rotary.h"
#include "../../Mcu/Gpt/Gpt_Config.h"

/* Rotary Encoder IO Map
Rotary Terminal A is interfaced to GPIO1_5 of MCU
Rotary Terminal B is interfaced to GPIO1_8 of MCU
Rotary Switch is interfaced to GPIO0_7 of MCU */


static volatile  uint8_t rotary_dir, rotary_count; 

void PIOINT1_IRQHandler(void)  // CPU jumps here whenever there is a Falling Edge on PIO1_5
{
	uint8_t state;
	
	state = Gpio1_Pin_Get(8);  // Check the ENC_B current state
	
	if(HIGH == state)
	{ 
		rotary_dir = ROTARY_DIR_CLK;   // Clockwise Movement	
		rotary_count++;
	}
	else
	{
		rotary_dir = ROTARY_DIR_CCLK;   // Counter Clockwise Movement	
		rotary_count--;
	}		

  // Before returning from ISR, Clear the interrupt and give 2 NOPs delay
  Eint1_Reset(5);

  __NOP();
  __NOP();
}	


void Rotary_Rotation_Reset(void)
{
	rotary_count =0;
}

void Rotary_Rotation_Set(uint8_t cnt)
{
	rotary_count =cnt;
}

// Rotary feature function definitions
uint8_t Rotary_Rotation_Get(uint8_t *cnt)
{
	*cnt = rotary_count;

	return rotary_dir;
}

uint8_t Rotary_Switch_Get(void)
{
	int rs = ROTARY_SW_DPRESS, pn = HIGH;
	
	pn = Gpio0_Pin_Get(7);
	
	if(LOW == pn)
	{
		rs = ROTARY_SW_PRESS;
	}	
	
	return rs;
}

void Rotary_Switch_Clicks_Get(uint8_t *clicks)
{
	uint8_t state_current  = ROTARY_SW_DPRESS;
	static uint8_t state_previous = ROTARY_SW_DPRESS;
	
	state_current = Rotary_Switch_Get();
	
	if(state_current == ROTARY_SW_DPRESS)
	{
		if(state_previous == ROTARY_SW_PRESS)
		{
			(*clicks)++;
		}	
	}	
	state_previous = state_current;
}
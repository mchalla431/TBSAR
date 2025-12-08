#include "Gpt.h"
#include "lpc11xx.h"

/* GPT1 Base Operation */
#define GPT1_Init_Count(val)			GPT1_TC = val

/* GPT1 Timer Match Internal Options for MR0 and MR3*/
#define GPT1_MR0_iOP_TC_Reset()			GPT1_MCR |= (1<<1)
#define GPT1_MR0_iOP_TC_Stop()			GPT1_MCR |= (1<<2)

#define GPT1_MR3_iOP_TC_Reset()			GPT1_MCR |= (1<<10)
#define GPT1_MR3_iOP_TC_Stop()			GPT1_MCR |= (1<<11)

/* GPT1 Timer Match External Options for MR0*/
#define GPT1_MR0_eOP_Toggle()			GPT1_EMR = (3<<4)		
#define GPT1_MR0_eOP_PWM()				GPT1_PWMC |= (1<<0)
#define GPT1_MR0_Disable_PWM()			GPT1_PWMC &= ~(1<<0)

/* GPT1 Match Registers */
#define GPT1_Set_MR0(val)				GPT1_MR0 = val
#define GPT1_Set_MR3(val)				GPT1_MR3 = val


/* GPT2 Base Operation */
#define GPT2_Init_Count(val)			GPT2_TC = val

/* GPT1 Timer Match Internal Options for MR0 and MR3*/
#define GPT2_MR0_iOP_TC_Reset()			GPT2_MCR |= (1<<1)
#define GPT2_MR0_iOP_TC_Stop()			GPT2_MCR |= (1<<2)
										   
#define GPT2_MR3_iOP_TC_Reset()			GPT2_MCR |= (1<<10)
#define GPT2_MR3_iOP_TC_Stop()			GPT2_MCR |= (1<<11)
		   
/* GPT1 Timer Match External Options for MR0*/
#define GPT2_MR0_eOP_Toggle()			GPT2_EMR = (3<<4)		
#define GPT2_MR0_eOP_PWM()				GPT2_PWMC |= (1<<0)
#define GPT2_MR0_Disable_PWM()			GPT2_PWMC &= ~(1<<0)
		   
/* GPT1 Match Registers */
#define GPT2_Set_MR0(val)				GPT2_MR0 = val
#define GPT2_Set_MR3(val)				GPT2_MR3 = val



void Gpt1_Base_Mode_Set(int option)
{
	GPT1_CTCR = option;
}

void Gpt2_Base_Mode_Set(int option)
{
	GPT2_CTCR = option;
}

unsigned int Gpt1_Count_Get(void)
{
	return (GPT1_TC);
}	

unsigned int Gpt2_Count_Get(void)
{
	return (GPT2_TC);
}	


void Gpt1_Count_Set(int cnt)
{
	GPT1_Init_Count(cnt);
} 

void Gpt2_Count_Set(int cnt)
{
	GPT2_Init_Count(cnt);
} 


void Gpt1_Match0_Count_Set(int cnt)
{
	GPT1_Set_MR0(cnt);
}

void Gpt2_Match0_Count_Set(int cnt)
{
	GPT2_Set_MR0(cnt);
}


void Gpt1_Match1_Count_Set(int cnt)
{
	GPT1_Set_MR3(cnt);
}

void Gpt2_Match1_Count_Set(int cnt)
{
	GPT2_Set_MR3(cnt);
}


void Gpt1_Match0_iOption_Set(int option)
{
	switch(option)
	{
		case COUNTER_CONTINUE:
			break;

		case COUNTER_RESET:
			GPT1_MR0_iOP_TC_Reset();
			break;
			
		case COUNTER_STOP:
			GPT1_MR0_iOP_TC_Stop();
			break;
	}
}

void Gpt2_Match0_iOption_Set(int option)
{
	switch(option)
	{
		case COUNTER_CONTINUE:
			break;

		case COUNTER_RESET:
			GPT2_MR0_iOP_TC_Reset();
			break;
			
		case COUNTER_STOP:
			GPT2_MR0_iOP_TC_Stop();
			break;
	}
}


void Gpt1_Match1_iOption_Set(int option)
{
	switch(option)
	{
		case COUNTER_CONTINUE:
			break;

		case COUNTER_RESET:
			GPT1_MR3_iOP_TC_Reset();
			break;
			
		case COUNTER_STOP:
			GPT1_MR3_iOP_TC_Stop();
			break;
	}
}

void Gpt2_Match1_iOption_Set(int option)
{
	switch(option)
	{
		case COUNTER_CONTINUE:
			break;

		case COUNTER_RESET:
			GPT2_MR3_iOP_TC_Reset();
			break;
			
		case COUNTER_STOP:
			GPT2_MR3_iOP_TC_Stop();
			break;
	}
}


void Gpt1_Match0_eOption_Set(int option)
{
	switch(option)
	{
		case MAT_PIN_TOGGLE:
			GPT1_MR0_eOP_Toggle();
			break;
			
		case MAT_PIN_PWM:
			GPT1_MR0_eOP_PWM();
			break;
	}
}

void Gpt2_Match0_eOption_Set(int option)
{
	switch(option)
	{
		case MAT_PIN_TOGGLE:
			GPT2_MR0_eOP_Toggle();
			break;
			
		case MAT_PIN_PWM:
			GPT2_MR0_eOP_PWM();
			break;
	}
}

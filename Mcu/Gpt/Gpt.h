#ifndef __GPT_H__	
#define __GPT_H__

#include "lpc11xx.h"

#define INTERNAL_TIMER		0
#define EVENT_COUNTER_V1	1 
#define EVENT_COUNTER_V2	2
#define EVENT_COUNTER_V3	3
void Gpt1_Base_Mode_Set(int option);
void Gpt2_Base_Mode_Set(int option);

// GPT Match internal options
#define COUNTER_CONTINUE	1
#define COUNTER_RESET		2
#define COUNTER_STOP		3
void Gpt1_Match0_iOption_Set(int option);
void Gpt1_Match1_iOption_Set(int option);
void Gpt2_Match0_iOption_Set(int option);
void Gpt2_Match1_iOption_Set(int option);

// GPT Match external options
#define MAT_PIN_TOGGLE		1
#define MAT_PIN_PWM			2
void Gpt1_Match0_eOption_Set(int option);
void Gpt2_Match0_eOption_Set(int option);

unsigned int Gpt1_Count_Get(void);
void Gpt1_Count_Set(int cnt);
void Gpt1_Match0_Count_Set(int cnt);
void Gpt1_Match1_Count_Set(int cnt);

unsigned int Gpt2_Count_Get(void);
void Gpt2_Count_Set(int cnt);
void Gpt2_Match0_Count_Set(int cnt);
void Gpt2_Match1_Count_Set(int cnt);


#endif


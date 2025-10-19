#ifndef __GPT_CONFIG_H__
#define __GPT_CONFIG_H__

#include "Gpt.h"

#define GPT_CLOCK_100KHZ  1
#define GPT_CLOCK_500KHZ  2
#define GPT_CLOCK_1MHZ    3
void Gpt1_Clock_Set(int clk);
void Gpt2_Clock_Set(int clk);




#endif
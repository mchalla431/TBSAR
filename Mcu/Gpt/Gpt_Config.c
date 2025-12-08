#include "Gpt_Config.h"

#define GPT1_Update_PR(val)				GPT1_PR = val
#define GPT2_Update_PR(val)				GPT2_PR = val
#define GPT1_Enable_Counters()			GPT1_TCR |= (1<<0)
#define GPT2_Enable_Counters()			GPT2_TCR |= (1<<0)


void Gpt1_Clock_Set(int clk)
{
	uint32_t gpt_pr =0;
	
	switch(clk)
	{
		case GPT_CLOCK_100KHZ: gpt_pr = 479; break;
		case GPT_CLOCK_500KHZ: gpt_pr = 95; break;
		case GPT_CLOCK_1MHZ:   gpt_pr = 47; break;
	}
	GPT1_Update_PR(gpt_pr);	
	GPT1_Enable_Counters();
}

void Gpt2_Clock_Set(int clk)
{
	uint32_t gpt_pr =0;
	
	switch(clk)
	{
		case GPT_CLOCK_100KHZ: gpt_pr = 479; break;
		case GPT_CLOCK_500KHZ: gpt_pr = 95; break;
		case GPT_CLOCK_1MHZ:   gpt_pr = 47; break;
	}
	GPT2_Update_PR(gpt_pr);
	GPT2_Enable_Counters();	
}




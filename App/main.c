#include "../Mcu/Sys/Syscon.h"
#include "../Mcu/Sys/Iocon.h"
#include <stdint.h>

void Task_10ms(void)		// This task function is called every 10ms
{

}	

void Task_20ms(void)  // This task function is called every 20ms
{

}

void Task_50ms(void) // This task function is called every 50ms
{

}

void Task_100ms(void)	// This task function is called every 100ms
{

}



volatile uint8_t 	flag_10ms, flag_20ms, flag_50ms, flag_100ms;

int main(void)
{

	SysTick_Config(480000); // 480000/48MHZ = 10ms
	                        // SysTick interrupts the processor every 10ms   
	
	while(1) // Real time loop
	{
		if(flag_10ms)
		{
			flag_10ms =0;
			Task_10ms();
		}	
		if(flag_20ms)
		{
			flag_20ms =0;
			Task_20ms();
		}	
		if(flag_50ms)
		{
			flag_50ms =0;
			Task_50ms();
		}	
		if(flag_100ms)
		{
			flag_100ms =0;
			Task_100ms();
		}	
	}
}

void SysTick_Handler(void)
{
	static volatile uint8_t ctr_1=0, ctr_2=0, ctr_3=0, ctr_4=0;
	// Processor jumps here every 10ms
	
	ctr_1++;
	ctr_2++;
	ctr_3++;
	ctr_4++;
	
	if(1 == ctr_1)
	{
		flag_10ms = 1;
		ctr_1  = 0;
	}	

	if(2 == ctr_2)
	{
		flag_20ms = 1;
		ctr_2  = 0;
	}	

	if(5 == ctr_3)
	{
		flag_50ms = 1;
		ctr_3  = 0;
	}	

	if(10 == ctr_4)
	{
		flag_100ms = 1;
		ctr_4  = 0;
	}	
}	





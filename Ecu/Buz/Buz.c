#include "Buz.h"

void Buz_On(void)
{
	Gpio0_Pin_Set(8, 1);
}

void Buz_Off(void)
{
	Gpio0_Pin_Set(8, 0);
}



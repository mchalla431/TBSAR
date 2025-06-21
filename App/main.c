#include "../Mcu/Sys/Syscon.h"
#include "../Mcu/Sys/Iocon.h"
#include "../Ecu/Rgb/Rgb_Config.h"
#include "../Ecu/Rgb/Rgb.h"
#include "../Ecu/Buz/Buz_Config.h"
#include "../Ecu/Buz/Buz.h"

int main(void)
{
	Rgb_Config();
	Buz_Config();

	Buz_Set_Freq(1000);      

	while (1)
	{
	}

	return 0;
}


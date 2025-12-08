#include "Can_Config.h"
#include "Can.h"
#include "Syscon.h"


void Can_Baudrate_Set(int baud)
{
  LPC_CAN->BT   = 0x2301;        /* 500kBit/s @ 8MHz CAN clk */
  LPC_CAN->BRPE = 0x0000;
}

void Can_Loop_Back_Set(void)
{
	Can_Test_Mode();
}

void Can_Config(void)
{
	// Base Configuration : Syscon
	Syscon_Pclk_Iocon_Enable();
	Syscon_Pclk_Can_Enable();
	
	// Base Configuration: Iocon
		// No need

	// Baudrate set to 500KHz
	Can_Baudrate_Set(CAN_BAUD_500KHZ);
	
	// Loopback Mode
	//Can_Loop_Back_Set();
}


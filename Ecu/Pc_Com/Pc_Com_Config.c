#include "Pc_Com_Config.h"


void Pc_Com_Config(void)
{
	// Base Configuration : Syscon
	Syscon_Pclk_Iocon_Enable();
	Syscon_Pclk_Uart_Enable();
	Syscon_Uart_Clkdiv_Set(1);
	
	// Base Configuration: Iocon
	Iocon_Pio1_6_Set(1,2,0,0,0,0);
	Iocon_Pio1_7_Set(1,2,0,0,0,0);
	
	// Core Configuration: Uart
	Uart_Data_Size_Set(UART_DATA_8BIT);
	Uart_Baudrate_Set(UART_BAUD_57600);
}



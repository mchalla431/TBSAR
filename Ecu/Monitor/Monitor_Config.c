#include "Monitor_Config.h"


void Monitor_Config(void)
{
	// Base Configuration : Syscon
	Syscon_Pclk_Iocon_Enable();
	Syscon_Pclk_Uart_Enable();
	Syscon_Uart_Clkdiv_Set(1);
	Syscon_Uart_Preset_Deassert();
	
	// Base Configuration: Iocon - Standard UART pins
	Iocon_Pio1_6_Set(1,2,0,0,0,0);  // RXD on PIO1_6 (function 1 = UART)
	Iocon_Pio1_7_Set(1,2,0,0,0,0);  // TXD on PIO1_7 (function 1 = UART)
	
	// Core Configuration: Uart
	Uart_Data_Size_Set(UART_DATA_8BIT);
	Uart_Baudrate_Set(UART_BAUD_57600);
}



#include "Uart_Config.h"

#define UART_Set_Data_Size(val)		UART_LCR = val
#define UART_Enable_DLAB()			UART_LCR |= (1<<7)
#define UART_Disable_DLAB()   		UART_LCR &= ~(1<<7)
#define UART_Update_DLL(val)		UART_DLL = val
#define UART_Update_DLM(val)		UART_DLM = val
#define UART_Update_FDR(val)		UART_FDR = val
#define UART_ACR              		LPC_UART->ACR
#define UART_Update_ACR(val)		UART_ACR = val

/* UART ACR (Auto-baud Control Register) bit definitions */
#define Uart_Baud_Double()		LPC_UART->ACR = (1<<1)
#define Uart_Baud_Normal()		LPC_UART->ACR = 0


void Uart_Data_Size_Set(int opt)
{
	UART_Set_Data_Size(opt);
}

void Uart_Baudrate_Set(int baud)
{
	switch(baud)
	{
		case UART_BAUD_9600:
			// Unlock Baud Registers
			UART_Enable_DLAB();
			// Setup the Baudrate: 9600
			UART_Update_DLL(0xfa);
			UART_Update_DLM(0x00);
			UART_Update_FDR(0x41);
			// Lock Baud Registers
			UART_Disable_DLAB();
			// Disable baudrate doubler
			Uart_Baud_Normal();
			break;

		case UART_BAUD_19200:
			// Unlock Baud Registers
			UART_Enable_DLAB();
			// Setup the Baudrate: 19200
			UART_Update_DLL(0x7d);
			UART_Update_DLM(0x00);
			UART_Update_FDR(0x41);
			// Lock Baud Registers
			UART_Disable_DLAB();
			// Disable baudrate doubler
			Uart_Baud_Normal();
			break;

		case UART_BAUD_38400:
			// Unlock Baud Registers
			UART_Enable_DLAB();
			// Setup the Baudrate: 38400
			UART_Update_DLL(0x25);
			UART_Update_DLM(0x00);
			UART_Update_FDR(0x9a);
			// Lock Baud Registers
			UART_Disable_DLAB();
			// Disable baudrate doubler
			Uart_Baud_Normal();
			break;

		case UART_BAUD_57600:
			// Unlock Baud Registers
			UART_Enable_DLAB();
			// Setup the Baudrate: 57600
			UART_Update_DLL(0x19);
			UART_Update_DLM(0x00);
			UART_Update_FDR(0xcd);
			// Lock Baud Registers
			UART_Disable_DLAB();
			// Disable baudrate doubler
			Uart_Baud_Normal();
			break;
		
		case UART_BAUD_115200:
			break;
	}	
}


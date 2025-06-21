#include "Pc_Com.h"

void Pc_Com_Byte_Send(uint8_t dat)
{

	// Check the status of transmit buffer (Wait until it becomes empty)
	while(!(Uart_Transmit_Buffer_Check()));
	// Uart_Transmit_Buffer_Check() returns 1 if the transmit buffer is empty
	// Uart_Transmit_Buffer_Check() returns 0 if the transmit buffer is not empty
	
	// Load the data in the buffer
	Uart_Transmit_Buffer_Write(dat);
}

void Pc_Com_String_Send(char *str)
{
	while(*str != 0)
	{
		Pc_Com_Byte_Send(*str);
		str++;
	}	
}

uint8_t Pc_Com_Byte_Receive(void)
{
	uint8_t rx_byte =0;


	//	Check the status of receive buffer
	if(1 == Uart_Receive_Buffer_Check())
	{
		// read the data from the buffer
		rx_byte = Uart_Receive_Buffer_Read();
	}	

	return rx_byte;
}

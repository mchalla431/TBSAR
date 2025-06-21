#include "Uart.h"


#define UART_Get_TBuf_Status()		((UART_LSR & (1<<5))?1:0)
#define UART_Get_RBuf_Status()		((UART_LSR & (1<<0))?1:0)
#define UART_Update_TBuf(data)		UART_THR = data
#define UART_Get_RBuf()				UART_RBR



int Uart_Transmit_Buffer_Check(void)
{
	return UART_Get_TBuf_Status();
}

void Uart_Transmit_Buffer_Write(uint8_t byte)
{
	UART_Update_TBuf(byte);
}

int Uart_Receive_Buffer_Check(void)
{
	return UART_Get_RBuf_Status();
}

uint8_t Uart_Receive_Buffer_Read(void)
{
	return UART_Get_RBuf();
}



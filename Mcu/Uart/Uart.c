#include "Uart.h"

/* UART Register Access Macros */
#define UART_Get_TBuf_Status()		((UART_LSR & (1<<5))?1:0)
#define UART_Get_RBuf_Status()		((UART_LSR & (1<<0))?1:0)
#define UART_Update_TBuf(data)		UART_THR = data
#define UART_Get_RBuf()				UART_RBR

/* Inline UART register access functions for performance */
static inline int Uart_Transmit_Buffer_Check(void)
{
	return UART_Get_TBuf_Status();
}

static inline void Uart_Transmit_Buffer_Write(uint8_t byte)
{
	UART_Update_TBuf(byte);
}

static inline int Uart_Receive_Buffer_Check(void)
{
	return UART_Get_RBuf_Status();
}

static inline uint8_t Uart_Receive_Buffer_Read(void)
{
	return UART_Get_RBuf();
}

/* UART communication functions */
void Uart_Byte_Send(uint8_t dat)
{
	// Check the status of transmit buffer (Wait until it becomes empty)
	while(!(Uart_Transmit_Buffer_Check()));
	// Uart_Transmit_Buffer_Check() returns 1 if the transmit buffer is empty
	// Uart_Transmit_Buffer_Check() returns 0 if the transmit buffer is not empty

	// Load the data in the buffer
	Uart_Transmit_Buffer_Write(dat);
}

void Uart_String_Send(char *str)
{
	// Add null pointer check for robustness
	if (!str) return;
	
	while(*str != '\0')
	{
		Uart_Byte_Send(*str);
		str++;
	}
}

uint8_t Uart_Byte_Receive(void)
{
	uint8_t rx_byte = 0;

	// Check the status of receive buffer
	if(1 == Uart_Receive_Buffer_Check())
	{
		// read the data from the buffer
		rx_byte = Uart_Receive_Buffer_Read();
	}

	return rx_byte;
}



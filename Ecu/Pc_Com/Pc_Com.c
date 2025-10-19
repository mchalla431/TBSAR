#include "Pc_Com.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>

// Retarget printf to use Pc_Com_Byte_Send
int _write(int file, char *ptr, int len)
{
	int i;
	
	// Only redirect stdout (file descriptor 1) and stderr (file descriptor 2)
	if (file == 1 || file == 2)
	{
		for (i = 0; i < len; i++)
		{
			Pc_Com_Byte_Send((uint8_t)ptr[i]);
		}
		return len;
	}
	
	// For other file descriptors, return error
	errno = EBADF;
	return -1;
}

// Additional stubs for newlib (optional but prevents linker warnings)
int _close(int file)
{
	(void)file;
	return -1;
}

int _fstat(int file, struct stat *st)
{
	(void)file;
	st->st_mode = S_IFCHR;
	return 0;
}

int _isatty(int file)
{
	(void)file;
	return 1;
}

int _lseek(int file, int ptr, int dir)
{
	(void)file;
	(void)ptr;
	(void)dir;
	return 0;
}

int _read(int file, char *ptr, int len)
{
	(void)file;
	(void)ptr;
	(void)len;
	return 0;
}

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

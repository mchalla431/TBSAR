#include "I2c.h"

#define I2C_Set_Start()				I2C_CONSET = (1<<5)		 
#define I2C_Clear_Start()			I2C_CONCLR = (1<<5)		 
#define I2C_Set_Stop()				I2C_CONSET = (1<<4)
#define I2C_Get_Status_Flag()		( (I2C_CONSET & (1<<3))?1:0 )
#define I2C_Clear_Status_Flag()		I2C_CONCLR = (1<<3)
#define I2C_Update_DAT(byte)		I2C_DAT = byte
#define I2C_Get_DAT()				I2C_DAT
#define I2C_Get_Status_Code()		I2C_STAT
#define I2C_Set_Master_Ack()		I2C_CONSET = (1<<2)
#define I2C_Set_Master_Nack()		I2C_CONCLR = (1<<2)

void I2c_Start_Set(void)
{
	I2C_Clear_Status_Flag();
	I2C_Set_Start();
}

void I2c_Start_Clr(void)
{
	I2C_Clear_Start();
}

#define MASTER_WRITE 0
#define MASTER_READ  1
void I2c_Slave_Select(uint8_t slaveID, int dir)
{
	I2C_Update_DAT(slaveID | dir);
}

void I2c_Byte_Write(uint8_t byte)
{
	I2C_Update_DAT(byte);
}

uint8_t I2c_Byte_Read(void)
{
	uint8_t dat;
	
	dat = I2C_Get_DAT();
	
	return dat;
}

void I2c_Stop_Set(void)
{
	I2C_Set_Stop();
}

#define MASTER_ACK 	0
#define MASTER_NACK 1
void I2c_Master_Acknowledge_Set(int option)
{
	switch(option)
	{
		case MASTER_ACK: I2C_Set_Master_Ack();   break;
		case MASTER_NACK: I2C_Set_Master_Nack(); break;
	}
}

void I2c_Status_Wait(void)
{
	while(!(I2C_Get_Status_Flag()));
	I2C_Clear_Status_Flag();
}




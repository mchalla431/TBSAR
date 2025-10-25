#ifndef __I2C_H__	
#define __I2C_H__

#include <stdint.h>
#include "lpc11xx.h"


// I2C Driver function prototypes


void I2c_Start_Set(void);
void I2c_Start_Clr(void);

#define MASTER_WRITE 0
#define MASTER_READ  1
void I2c_Slave_Select(uint8_t slaveID, int dir);

void I2c_Byte_Write(uint8_t byte);
uint8_t I2c_Byte_Read(void);

void I2c_Stop_Set(void);

#define MASTER_ACK 	0
#define MASTER_NACK 1
void I2c_Master_Acknowledge_Set(int option);

void I2c_Status_Wait(void);


#endif


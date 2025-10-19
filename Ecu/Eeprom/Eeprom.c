#include "Eeprom.h"


void Eeprom_Bytes_Write(uint8_t adr, uint8_t *buf, int size)
{
	int index;
	
// I2c Start
	I2c_Start_Set();
	I2c_Status_Wait(); // Wait for Bus ready
	I2c_Start_Clr();

// Enable (Select) Eeprom for writing (Slave Id : A0 Direction LSB: 0)
	I2c_Slave_Select(0xA0, MASTER_WRITE);
	I2c_Status_Wait(); // Wait for Slave Ack

// Select Eeprom internal memory location (00 to FF)
	I2c_Byte_Write(adr);
	I2c_Status_Wait(); // Wait for Slave Ack

// Write Byte(s)
	for(index=0; index<size; index++)
	{
		I2c_Byte_Write(buf[index]);
		I2c_Status_Wait(); // Wait for Slave Ack
	}	

// I2c Stop
	I2c_Stop_Set();

//Note: Check I2c status (Bus condition and slave acknowledgement) in each phase of transaction

}

void Eeprom_Bytes_Read(uint8_t adr, uint8_t *buf, int size)
{
	int index;

// I2c Start
	I2c_Start_Set();
	I2c_Status_Wait(); // Wait for Bus ready
	I2c_Start_Clr();

// Enable (Select) Eeprom for writing (Slave Id : A0 Direction LSB: 0)
	I2c_Slave_Select(0xA0, MASTER_WRITE);
	I2c_Status_Wait(); // Wait for Slave Ack

// Select Eeprom internal memory location (00 to FF)
	I2c_Byte_Write(adr);
	I2c_Status_Wait(); // Wait for Slave Ack

// I2c reStart
	I2c_Start_Set();
	I2c_Status_Wait(); // Wait for Bus ready
	I2c_Start_Clr();
	
// Enable (Select) Eeprom for reading (Slave Id : A0 Direction LSB: 1)
	I2c_Slave_Select(0xA0, MASTER_READ);
	I2c_Status_Wait(); // Wait for Slave Ack

// Read Byte(s) (Master ACK to continue reading. Master NACK to stop reading)
	for(index=0; index<(size-1); index++)
	{
		I2c_Master_Acknowledge_Set(MASTER_ACK);
		I2c_Status_Wait();; // Wait for Slave Response
		buf[index] = I2c_Byte_Read();
	}	
	I2c_Master_Acknowledge_Set(MASTER_NACK);
	I2c_Status_Wait(); // Wait for Slave Response
	buf[index] = I2c_Byte_Read();

// I2c Stop
	I2c_Stop_Set();

//Note: Check I2c status (slave response) in each phase of transaction

}
#include "Eeprom.h"
#include "../Monitor/Monitor.h"

// EEPROM test data
static uint8_t test_write_data[8] = {0xAA, 0x55, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};
static uint8_t test_read_data[8] = {0};
static uint8_t eeprom_status = 0; // 0: Not tested, 1: OK, 2: Failed


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

/**
 * @brief Test EEPROM write functionality
 */
void Eeprom_Test_Write(void)
{
	// Write test pattern to EEPROM address 0x10
	Eeprom_Bytes_Write(0x10, test_write_data, sizeof(test_write_data));
	
	// Small delay for EEPROM write cycle completion
	for(volatile int i = 0; i < 10000; i++);
}

/**
 * @brief Test EEPROM read functionality and verify data
 */
void Eeprom_Test_Read(void)
{
	int i;
	uint8_t match = 1;
	
	// Read back data from EEPROM address 0x10
	Eeprom_Bytes_Read(0x10, test_read_data, sizeof(test_read_data));
	
	// Compare read data with written data
	for(i = 0; i < sizeof(test_write_data); i++)
	{
		if(test_read_data[i] != test_write_data[i])
		{
			match = 0;
			break;
		}
	}
	
	// Update status
	eeprom_status = match ? 1 : 2; // 1: OK, 2: Failed
}

/**
 * @brief Monitor EEPROM status and display information
 */
void Eeprom_Monitor(void)
{
	// Perform EEPROM test if not done yet
	if(eeprom_status == 0)
	{
		Eeprom_Test_Write();
		Eeprom_Test_Read();
	}
	
	// Display EEPROM status with emojis and color coding
	if(eeprom_status == 1)
	{
		uart_printf("\r\x1b[2K[EEPROM] 💾✅ I2C OK - Test Pattern Verified   ");
	}
	else if(eeprom_status == 2)
	{
		uart_printf("\r\x1b[2K[EEPROM] 💾❌ I2C FAIL - Data Mismatch   ");
	}
	else
	{
		uart_printf("\r\x1b[2K[EEPROM] 💾⏳ Testing...   ");
	}
}
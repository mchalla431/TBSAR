#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "../../Mcu/Sys/Syscon.h"
#include "../../Mcu/I2c/I2c.h"

// Eeprom drive function prototypes
void Eeprom_Bytes_Write(uint8_t adr, uint8_t *buf, int size); 
void Eeprom_Bytes_Read(uint8_t adr, uint8_t *buf, int size); 

// Eeprom monitoring functions
void Eeprom_Test_Write(void);
void Eeprom_Test_Read(void);
void Eeprom_Monitor(void);

#endif
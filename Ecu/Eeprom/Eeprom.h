#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "Eeprom.h"
#include "Syscon.h"
#include "I2c.h"

// Eeprom drive function prototypes
void Eeprom_Bytes_Write(uint8_t adr, uint8_t *buf, int size); 
void Eeprom_Bytes_Read(uint8_t adr, uint8_t *buf, int size);
void Eeprom_Monitor(uint8_t *buf, int size); 


#endif
#ifndef __LCD_CONFIG_H__
#define __LCD_CONFIG_H__

#include <stdint.h>
#include "Syscon.h"
#include "Iocon.h"
#include "Dio_Config.h"
#include "Dio.h"

/* LCD IO Map 
LCD 4-bit Bus : PIO3_0 to PIO3_3
LCD RS: PIO2_0
LCD EN:	PIO2_1
LCD RW: GND
Backlight: PIO1_10
*/

// LCD hardware control macros
#define LCD_RS_Command() 	Gpio2_Pin_Set(0, LOW)
#define LCD_RS_Data()		Gpio2_Pin_Set(0, HIGH)
#define LCD_EN_HIGH()		Gpio2_Pin_Set(1, HIGH)
#define LCD_EN_LOW()		Gpio2_Pin_Set(1, LOW)
#define LCD_Write_4Bit(dat)	Gpio3_Nibble_Set(0, dat)

void Lcd_Config(void);
void Lcd_Delay(volatile uint32_t microseconds);  // Delay in microseconds
void Lcd_Cmd_Set(uint8_t cmd);                   // Send command to LCD controller
void Lcd_Clear(void);                            // Clear LCD display

// LCD Backlight Control
void Lcd_Backlight_On(void);
void Lcd_Backlight_Off(void);


#endif


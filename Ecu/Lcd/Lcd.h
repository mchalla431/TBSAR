#ifndef __LCD_H__
#define __LCD_H__

#include <stdint.h>
#include "Lcd_Config.h"


// LCD Global Application Functions  
void Lcd_Set_Cursor(int row, int col);     // Set cursor at row (1-2), column (1-16)
void lcd_printf(const char *format, ...);  // Printf-style formatted output

#endif

#include "Lcd.h"
#include "Lcd_Config.h"
#include <stdarg.h>
#include <stdio.h>


// Set cursor at specific row and column (1-based indexing)
void Lcd_Set_Cursor(int row, int col)
{
	uint8_t address;
	
	// Convert to 0-based and calculate DDRAM address
	// Row: 1 or 2, Column: 1 to 16
	if (row == 1)
		address = 0x80 + (col - 1);  // Row 1: 0x80 to 0x8F
	else
		address = 0xC0 + (col - 1);  // Row 2: 0xC0 to 0xCF
	
	Lcd_Cmd_Set(address);
}

// Internal function: Write single character to LCD
static char Lcd_Put_Char(char dat)
{
   	char dat_h, dat_l;
	
	dat_l = (dat >>0) & 0xF;
	dat_h = (dat >>4) & 0xF;
		
	LCD_RS_Data();
	Lcd_Delay(1);  // Setup time for RS
	
	// Send high nibble
	LCD_EN_HIGH();
	Lcd_Delay(1);  // Enable pulse width minimum 450ns
	LCD_Write_4Bit(dat_h);
	Lcd_Delay(1);  // Data setup time minimum 195ns
	LCD_EN_LOW();
	Lcd_Delay(1);  // Enable cycle time
	
	// Send low nibble
	LCD_EN_HIGH();
	Lcd_Delay(1);  // Enable pulse width minimum 450ns
	LCD_Write_4Bit(dat_l);
	Lcd_Delay(1);  // Data setup time minimum 195ns
	LCD_EN_LOW();
	
	Lcd_Delay(50);  // Character write time (43µs typical)
	
	return dat;
}

// Internal helper: Print string at current cursor position
static void Lcd_Print_String(const char *str)
{
	while (*str != '\0')
	{
		Lcd_Put_Char(*str);
		str++;
	}
}

// Printf-style formatted output to LCD at current position
void lcd_printf(const char *format, ...)
{
	char buffer[32];  // Buffer for formatted string (16x2 LCD max 32 chars)
	va_list args;
	
	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);
	
	Lcd_Print_String(buffer);
}



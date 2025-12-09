#include "Lcd_Config.h"

void Lcd_Delay(volatile uint32_t microseconds)
{
	// Using system clock: Assume 48MHz system clock
	// Each loop iteration takes ~4-5 cycles
	// For better accuracy: cycles = (microseconds * 48) / 5
	volatile uint32_t cycles = (microseconds * 10);
	
	while (cycles--)
	{
		__asm volatile("nop");  // Precise no-operation
	}
}

void Lcd_Cmd_Set(uint8_t cmd)   
{
	uint8_t cmd_h, cmd_l;
	
	cmd_l = (cmd >>0) & 0xF;
	cmd_h = (cmd >>4) & 0xF;
		
	LCD_RS_Command();
	Lcd_Delay(1);  // Setup time for RS
	
	// Send high nibble
	LCD_EN_HIGH();
	Lcd_Delay(1);  // Enable pulse width minimum 450ns
	LCD_Write_4Bit(cmd_h);
	Lcd_Delay(1);  // Data setup time minimum 195ns
	LCD_EN_LOW();
	Lcd_Delay(1);  // Enable cycle time
	
	// Send low nibble
	LCD_EN_HIGH();
	Lcd_Delay(1);  // Enable pulse width minimum 450ns
	LCD_Write_4Bit(cmd_l);
	Lcd_Delay(1);  // Data setup time minimum 195ns
	LCD_EN_LOW();
	
	Lcd_Delay(50);  // Command execution time (most commands need 37µs)
}

// Clear LCD display
void Lcd_Clear(void)
{
	Lcd_Cmd_Set(0x01);  // Clear display command
	Lcd_Delay(2000);    // Clear/Home commands need 1.52ms minimum
}

void Lcd_Config(void)
{
	//Base Configuration
	Syscon_Pclk_Iocon_Enable();
	Syscon_Pclk_Gpio_Enable();	

	Iocon_Pio2_0_Set(0,2,0,0,0,0);
	Iocon_Pio2_1_Set(0,2,0,1,0,0);
	Iocon_Pio3_0_Set(0,2,0,0,0,0);
	Iocon_Pio3_1_Set(0,2,0,0,0,0);
	Iocon_Pio3_2_Set(0,2,0,0,0,0);
	Iocon_Pio3_3_Set(0,2,0,0,0,0);
	Iocon_Pio1_10_Set(0,1,0,0,0,0);
	
	//Core Configuration
	Gpio2_Direction_Set(0, OUTPUT);
	Gpio2_Direction_Set(1, OUTPUT);
	Gpio3_Direction_Set(0, OUTPUT);
	Gpio3_Direction_Set(1, OUTPUT);
	Gpio3_Direction_Set(2, OUTPUT);
	Gpio3_Direction_Set(3, OUTPUT);
	Gpio1_Direction_Set(10, OUTPUT);
	

	// LCD high level configuration (HD44780 4-bit initialization sequence)
	
	// Power-on delay: Wait for LCD controller to stabilize
	Lcd_Delay(15000);         // Wait >15ms after VDD rises to 4.5V
	
	// Special 4-bit initialization sequence (see HD44780 datasheet)
	Lcd_Cmd_Set(0x02);        // Function set: 4-bit mode
	Lcd_Delay(100);           // Wait >100µs
	
	Lcd_Cmd_Set(0x28);        // Function set: 4-bit, 2-line, 5x8 dots
	Lcd_Delay(100);
	
	Lcd_Cmd_Set(0x0C);        // Display ON, Cursor OFF, Blink OFF
	Lcd_Delay(100);
	
	Lcd_Cmd_Set(0x06);        // Entry mode: Increment cursor, No display shift
	Lcd_Delay(100);
	
	Lcd_Cmd_Set(0x01);        // Clear display
	Lcd_Delay(2000);          // Clear command needs 1.52ms minimum
	
	Lcd_Cmd_Set(0x80);        // Set cursor to home position (line 0, column 0)
	Lcd_Delay(100);
	
	Lcd_Clear();
	Lcd_Delay(100);

	// Turn on backlight by default
	Lcd_Backlight_Off();
}

// Turn LCD backlight ON
void Lcd_Backlight_On(void)
{
	Gpio1_Pin_Set(10, HIGH);  // PIO1_10 controls backlight
}

// Turn LCD backlight OFF
void Lcd_Backlight_Off(void)
{
	Gpio1_Pin_Set(10, LOW);   // PIO1_10 controls backlight
}

#include "lcd.h"

/* Function: lcd_init
 * ------------------------
 * Init LCD
 */
void lcd_init()
{
	LCD_RS_DISABLE;
	LCD_E_DISABLE;
	
	_delay_ms(15);
	
	/* to init the lcd you have to write 3 times (03)h within a specific time
	 * first delay longer 5ms, second longer 100us, third longer 150 us
	 */
	lcd_out(0x03);
	_delay_ms(5);
	
	lcd_out(0x03);
	_delay_us(110);
	
	lcd_out(0x03);
	_delay_us(200);
	
	/* (02)h: 4 Byte mode 
	 * (XX)h: 8 Byte mode
	 */
	lcd_out(0x02);
	_delay_ms(2);
	
	lcd_command(0x28);
	_delay_ms(2);
	
	lcd_command(0xC);
	_delay_ms(2);
	
	lcd_command(LCD_COM_CLEARDISPLAY);
	_delay_ms(2);
}

/* Function: lcd_wait_busy_flag
 * ------------------------
 * Wait until busy flag cleared
 * 
 * return: 
 */
void lcd_wait_busy_flag()
{
	LCD_RS_DISABLE;
	LCD_RW_ENABLE;
	LCD_DDR &= ~( (1<<LCD_DB4_DDR) | (1<<LCD_DB5_DDR) | (1<<LCD_DB6_DDR) | (1<<LCD_DB7_DDR) );
	LCD_PORT |= (1<<LCD_DB4) | (1<<LCD_DB5) | (1<<LCD_DB6) | (1<<LCD_DB7);
	
	_delay_us(11);
    LCD_WAIT_BUSY_FLAG;
	
    LCD_DDR |= (1<<LCD_DB4_DDR) | (1<<LCD_DB5_DDR) | (1<<LCD_DB6_DDR) | (1<<LCD_DB7_DDR);
    LCD_RW_DISABLE;
}

/* Function: lcd_command
 * ------------------------
 * Write a lcd commando to the LCD.
 * RS=LOW: command
 * RS=HIGH: data
 * 
 * lcd_command: lcd commando byte see lcd.h or datasheet for possible commands
 */
void lcd_command(uint8_t lcd_command)
{
	LCD_RS_DISABLE;
	lcd_out(lcd_command>>4);
	lcd_out(lcd_command);
	_delay_us(50);
}

/* Function: lcd_print_decimal
 * ------------------------
 * Recursive Function to write a decimal value on lcd
 * 
 * number: value to write on lcd
 */
void lcd_print_decimal(uint16_t number)
{	
	if(number != 0)
		lcd_print_decimal(number/10);
	else
		return;
	
	fifo_buffer_in( (number%10) + 48 , &lcd_line1_buff);
	
	return;
}

/* Function: lcd_putchar
 * ------------------------
 * Put a single character value on lcd
 * RS=LOW: command
 * RS=HIGH: data
 * 
 * lcd_command: character ASCII Code
 */
void lcd_putchar(uint8_t lcd_command)
{
	LCD_RS_ENABLE;
	lcd_out(lcd_command>>4);
	lcd_out(lcd_command);
	_delay_us(50);
}

/* Function: lcd_out
 * ------------------------
 * Writes physically an value to the lcd without to bother if its a command or data
 * Data read on falling edge (ENABLE PIN)
 * 
 * lcd_output: byte to write to lcd
 */
void lcd_out(uint8_t lcd_output)
{
	/* Set PORT to output and read data into register */
	LCD_PORT &= ~((1 << PB0) | (1 << PB1) | (1<<PB2) | (1<<PB3) );
	LCD_PORT |= lcd_output;
	
	/* Data read on falling edge (ENABLE PIN)*/
	LCD_E_ENABLE;
	asm("nop;nop;nop;");	//wait 3 instruction because avr needs time to set enable on high and low
	LCD_E_DISABLE;
}

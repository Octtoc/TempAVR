/* LCD Functions
 * LCD functions to write and read on a LCD type HD447180
 * LCD Anschluss an AVR ATMEGA8
 * PB0 = DB4, PB1 = DB5, PB2 = DB6, PB3 = DB7
 * PB4 = E, PB5 = RS
 */
 
#ifndef LCD_H
#define LCD_H
 
#include "main.h"
#include "fifo_buffer.h"
#include <avr/io.h>
#include <util/delay.h>

struct FIFO_BUFFER lcd_line1_buff;

/* LCD Port Definitions */
#define LCD_PORT	PORTB
#define LCD_PIN		PINB
#define LCD_DDR 	DDRB

#define LCD_DB4		PB0
#define LCD_DB5		PB1
#define LCD_DB6		PB2
#define LCD_DB7		PB3
#define LCD_PIN_E	PB4
#define LCD_PIN_RS	PB5
#define LCD_PIN_RW  PC0

#define LCD_DB4_DDR		DDB0
#define LCD_DB5_DDR		DDB1
#define LCD_DB6_DDR		DDB2
#define LCD_DB7_DDR		DDB3
#define LCD_PIN_E_DDR	PB4
#define LCD_PIN_RS_DDR	PB5
#define LCD_PIN_RW_DDR	PB6

#define LCD_RS_ENABLE	LCD_PORT |= (1<<LCD_PIN_RS)
#define LCD_RS_DISABLE	LCD_PORT &= ~(1 << LCD_PIN_RS)
#define LCD_E_ENABLE	LCD_PORT |= (1<<LCD_PIN_E)
#define LCD_E_DISABLE	LCD_PORT &= ~(1 << LCD_PIN_E)
#define LCD_RW_ENABLE	PORTC |= (1<<LCD_PIN_RW)
#define LCD_RW_DISABLE	PORTC &= ~(1 << LCD_PIN_RW)

#define LCD_WAIT_BUSY_FLAG	while( !(LCD_PIN & (1<<LCD_DB7)) ) ;
/* LCD Commands */
#define LCD_COM_CLEARDISPLAY	0x01
#define LCD_COM_CURSORHOME		0x02

/* LCD Functions */
void lcd_init();
void lcd_out(uint8_t lcd_output);
void lcd_command(uint8_t lcd_command);
void lcd_putchar(uint8_t lcd_command);
void lcd_print_decimal(uint16_t number);
void lcd_wait_busy_flag();

#endif /* LCD_H */
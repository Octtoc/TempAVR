/* TempAVR.c
 * Created: 19.01.2018 21:36:11
 * Author : Michael
 */ 
 
#include "main.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
 
#include "lcd.h"
#include "dht22.h"
#include "fifo_buffer.h"

//TWI Funktionen
void init_twi();

//Timer Funktionen
void timer0_init();

/*
 * global variables
 */
volatile uint16_t dht_read_counter;
volatile uint8_t lcd_delay_counter;

/*
 * main
 */
int main(void)
{
	uint16_t temperature;
	uint8_t temp_changed = 0;
	
	dht_read_counter = 0;
	
	LCD_DDR |= (1<<LCD_DB4_DDR) | (1<<LCD_DB5_DDR) | (1<<LCD_DB6_DDR) | (1<<LCD_DB7_DDR) | (1<<LCD_PIN_E_DDR) | (1<<LCD_PIN_RS_DDR);
	DDRC |= (1<<DDC0);
	
	timer0_init();
	dht22_init();
	lcd_init();
	
	sei();
	
	while (1)
	{
		if(dht_read_counter >= 1000)	//every second measure temperature
		{
			dht22_read(&temperature);
			
			lcd_command(LCD_COM_CURSORHOME);
			lcd_print_decimal(temperature);
			fifo_buffer_in('C', &lcd_line1_buff);
			
			dht_read_counter = 0;
			temp_changed = 1;
		}
		
		/*uint8_t SLA_W = 0x00,
				START = 0x08,
				MT_SLA_ACK = 0x18,
				MT_DATA_ACK = 0x28,
				DATA = 0x10;
		
		TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
		while (!(TWCR & (1<<TWINT))) fifo_buffer_in('B', &lcd_line1_buff);
		fifo_buffer_in('C', &lcd_line1_buff);
		if ((TWSR & 0xF8) != START)
		{
			
		}
		
		TWDR = SLA_W;
		TWCR = (1<<TWINT) | (1<<TWEN);
		while (!(TWCR & (1<<TWINT)));
		
		if ((TWSR & 0xF8) != MT_SLA_ACK)
		{
			
		}
		
		TWDR = DATA;
		TWCR = (1<<TWINT) | (1<<TWEN);
		while (!(TWCR & (1<<TWINT)));
		
		if ((TWSR & 0xF8) != MT_DATA_ACK)
		{
			
		}
		
		TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);*/
	}
}

void init_twi()
{
	DDRD |= (1<<DDD4) | (1<<DDD5);
	
	TWBR = 110;
}

/*
 * Interrupt Routines
 */

/* 1ms Interrupt 
 * Frequency 16 Mhz, Prescaler 64, Init Value 5
 * Formula (Frequency/Prescaler) / Counter Overflow-TCNT0
 * 16.000.000/64=250.000, 250.000/255-5=1000
 */
ISR(TIMER0_OVF_vect)
{
	uint8_t write_lcd;
	if(fifo_buffer_out(&write_lcd, &lcd_line1_buff) == BUFFER_SUCCESS)
	{
		lcd_putchar(write_lcd);
	}
	
	dht_read_counter++;
	TCNT0 = 5;		//set timer to 5 for 1ms interrupt
}

ISR(TWI_vect)
{
	fifo_buffer_in('T', &lcd_line1_buff);
}

/* 1ms Interrupt 
 * Frequency 16 Mhz, Prescaler 64, Init Value 5
 * Formula (Frequency/Prescaler) / Counter Overflow-TCNT0
 * 16.000.000/64=250.000, 250.000/255-5=1000
 */
void timer0_init()
{
	TCCR0 |= (1<<CS01) | (1<<CS00);		//Prescaler 64
	TIMSK |= (1<<TOIE0);				//Activate Timer0
}

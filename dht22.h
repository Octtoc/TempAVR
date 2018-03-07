/* DHT22
 * Functions to read the temperature and humidity
 * for the 1 Wire DHT22 sensor
 */

#ifndef DHT22_H
#define DHT22_H

#include "main.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
 
#define DHT22_PORT			PORTD
#define DHT22_PIN			PIND
#define DHT22_DDR			DDRD
#define DHT22_DATA			PD2
#define DHT22_DATA_DDR		DDB2

#define DHT22_LOW(del_ay)	while( !(DHT22_PIN & (1<<DHT22_DATA)) ) _delay_us(del_ay)
#define DHT22_HI			DHT22_PIN & (1<<DHT22_DATA)
#define DHT22_ACT_PULLUP	DHT22_PORT |= (1<<DHT22_DATA)
#define DHT22_READ_MODE	    DHT22_DDR &= ~(1 << DHT22_DATA_DDR)
#define DHT22_WRITE_MODE	DHT22_DDR |= (1<<DHT22_DATA_DDR)
#define DHT22_PIN_HIGH		DHT22_PORT |= (1<<DHT22_DATA)
#define DHT22_PIN_LOW		DHT22_PORT &= ~(1 << DHT22_DATA)

//DHT22 Funktionen
void dht22_init();
void dht22_read(uint16_t *temp_u);

#endif /* DHT22_H */
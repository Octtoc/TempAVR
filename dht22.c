#include "dht22.h"

/* Function: dht22_init
 * ------------------------
 * Init dht22 sensor
 */
void dht22_init()
{
	DHT22_WRITE_MODE;
	DHT22_PIN_HIGH;
	_delay_ms(10);
}

/* Function: dht22_read
 * ------------------------
 * Reads temperature and humidity from a dht22 sensor
 * 
 * *temp_u: pointer to hold temperature data
 */
void dht22_read(uint16_t *temp_u)
{
	uint8_t bit_data[40];
	uint8_t sensor_data[5];
	uint8_t i, count;
	
	sensor_data[0] = sensor_data[1] = sensor_data[2] = sensor_data[3] = sensor_data[4] = 0;
	
	//Send Signal to Sensor to start read
	DHT22_PIN_LOW;
	_delay_ms(2);		//5ms wait for sensor
	
	cli();	//time sensitive stuff now
	
	DHT22_PIN_HIGH;	//Sensor should send data now
	_delay_us(20);		//wait for sensor to start transmission
	
	DHT22_READ_MODE;
	DHT22_ACT_PULLUP;
	_delay_us(10);
	
	//Sensor should be 80us in LOW in 80us in HIGH
	DHT22_LOW(1);
	while( DHT22_HI )	_delay_us(1) ;
	
	for(i=0; i < 40; i++)	//5*8 Bit
	{
		count = 0;
		DHT22_LOW(1);	//wait to start BIT 50us
		while( DHT22_HI )					//26-28us=LOW 70us=HIGH
		{
			count++;
			_delay_us(1);
		}
		bit_data[i] = count;
	}
	
	sei();		//time sensitive stuff over
	
	for(i=0; i < 40; i++)
	{
		sensor_data[i/8] <<= 1;
		if (bit_data[i] > 40)			//time over 26-28us 1
		{
			sensor_data[i/8] |= 1;
		}
	}
	
	if ( ((sensor_data[0] + sensor_data[1] + sensor_data[2] + sensor_data[3]) & 0xff ) != sensor_data[4])
	{
		*temp_u = 1;
	}
	
	DHT22_WRITE_MODE;
	DHT22_PIN_HIGH;
	
	*temp_u = (sensor_data[2] << 8) + sensor_data[3];
}
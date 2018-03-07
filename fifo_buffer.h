/* FIFO Buffer
 * simple fifo buffer
 */

#ifndef FIFO_BUFFER_H
#define FIFO_BUFFER_H

#include "main.h"
#include <avr/io.h>

#define BUFFER_FAIL 0
#define BUFFER_SUCCESS 1
#define BUFFER_SIZE 8

struct FIFO_BUFFER {
	uint8_t data[BUFFER_SIZE];
	uint8_t read;
	uint8_t write;
};

uint8_t fifo_buffer_out(uint8_t *pByte, struct FIFO_BUFFER *fifo_buff);
uint8_t fifo_buffer_in(uint8_t byte, struct FIFO_BUFFER *fifo_buff);

#endif /* fifo_buffer.h */
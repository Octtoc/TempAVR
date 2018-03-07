#include "fifo_buffer.h"

/* Function: fifo_buffer_out
 * ---------------
 * Write a value into fifo buffer
 * 
 * *pByte: byte to read from fifo buffer
 * *fifo_buff: pointer to the buffer
 * 
 * return: BUFFER STATUS CODE
 */
uint8_t fifo_buffer_out(uint8_t *pByte, struct FIFO_BUFFER *fifo_buff)
{
	if (fifo_buff->read == fifo_buff->write)
		return BUFFER_FAIL;

	*pByte = fifo_buff->data[fifo_buff->read];

	fifo_buff->read++;
	if (fifo_buff->read >= BUFFER_SIZE)
		fifo_buff->read = 0;

	return BUFFER_SUCCESS;
}

/* Function: fifo_buffer_in
 * ------------------------
 * Read a value into fifo buffer
 * 
 * byte: byte to write in fifo buffer
 * *fifo_buff: pointer to the buffer
 * 
 * return: BUFFER STATUS CODE
 */
uint8_t fifo_buffer_in(uint8_t byte, struct FIFO_BUFFER *fifo_buff)
{
	if ( ( fifo_buff->write + 1 == fifo_buff->read ) ||
		( fifo_buff->read == 0 && fifo_buff->write + 1 == BUFFER_SIZE ) )
		return BUFFER_FAIL; // voll
	
	fifo_buff->data[fifo_buff->write] = byte;
	
	fifo_buff->write++;
	if(fifo_buff->write >= BUFFER_SIZE)
	{
		fifo_buff->write = 0;
	}
	
	return BUFFER_SUCCESS;
}
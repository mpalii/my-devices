#include "uart.h"
#include <avr/io.h>

#define END_OF_STRING '\0'

char* output_buffer;

void init_frame_format(void)
{
    /************************************************************************/
    /* Default frame format:                                                */
    /* 1 start bit, 8 data bits, no parity bit, 1 stop bit                  */
    /************************************************************************/
}

void init_uart(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled)
{
    // Baud rate calculation ratio
    uint32_t baud_rate_divider = 16;
	
    // Check double speed (U2X) mode
    if (double_speed_enabled)
    {
        UCSR0A = _BV(U2X0);
        baud_rate_divider /= 2;
    }
	
    // Set baud rate
    UBRR0 = f_cpu / (baud_rate_divider * baud_rate) - 1;
	
    // Enable transmission only
    UCSR0B = _BV(TXEN0);
	
    init_frame_format();
	
    // NO interrupts on receive/transmit
	
    // reset outbut buffer pointer
    output_buffer = NULL;
}

void uart_transmit(void) 
{
    if (output_buffer != NULL && bit_is_set(UCSR0A, UDRE0))
    {
        char data = *output_buffer;
				
        if (data == END_OF_STRING)
        {
            output_buffer = NULL;
            return;
        }
		
        UDR0 = data;
		
        output_buffer++;
    }
}

void uart_transmit_data(char* data)
{
    output_buffer = data;
}
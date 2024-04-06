#include "serial_transmission_task.h"
#include "../drivers/uart.h"

// External variables
volatile uint8_t serial_transmission_task_time;

void init_serial_transmission_task(void)
{
    serial_transmission_task_time = SERIAL_TRANSMISSION_TASK_TIME;
}

void serial_transmission_task(void)
{
    serial_transmission_task_time = SERIAL_TRANSMISSION_TASK_TIME;
	
    uart_transmit();
}
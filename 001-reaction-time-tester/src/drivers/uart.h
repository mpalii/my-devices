#ifndef UART_H_
#define UART_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint-gcc.h>

void init_uart(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled);
void uart_transmit(void);
void uart_transmit_data(char* data);

#endif /* UART_H_ */
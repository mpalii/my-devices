#include <stdbool.h>
#include "gpio.h"
#include "uart.h"

void init_reset(void)
{
    _gpio_set_input(SCORE_RESET);
    _gpio_high(SCORE_RESET);     // Enable internal pull-up resistor

    uart_transmit("- RESET ready\r\n");
}

bool reset_probe(void)
{
    return (_gpio_get_input(SCORE_RESET) == 0);
}

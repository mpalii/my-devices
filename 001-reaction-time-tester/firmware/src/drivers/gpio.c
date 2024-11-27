/*
 * General purpose IO pins assignment and handling
 * ATmega328P has 22 general purpose IO lines
 * Two 8bit ports (B, and D), and 7bit port C
 */

#include <util/delay.h>
#include "gpio.h"

void init_gpio(void)
{
    _gpio_set_output(CHECK);
    _gpio_high(CHECK);
    _delay_ms(500);
    _gpio_low(CHECK);
}
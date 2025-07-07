/**
 * @author Maksym Palii
 * @brief GPIO driver for ATmega328P
*/

#include "gpio.h"
#include <util/delay.h>

void init_gpio(void)
{
    _gpio_set_output(POWER_CONTROL);
    _gpio_high(POWER_CONTROL);
    _delay_ms(200);

    _gpio_set_input(POWER_BUTTON);
    _gpio_high(POWER_BUTTON);

    _gpio_set_input(IR_SENSOR_TOP_LEFT);
    _gpio_set_input(IR_SENSOR_TOP_RIGHT);
    _gpio_set_input(IR_SENSOR_BOTTOM_LEFT);
    _gpio_set_input(IR_SENSOR_BOTTOM_RIGHT);
}
/**
 * @author Maksym Palii
 * @brief GPIO driver for ATmega328P
*/

#include "gpio.h"

void init_gpio(void)
{
    _gpio_set_input(IR_SENSOR_TOP_LEFT);
    _gpio_set_input(IR_SENSOR_TOP_RIGHT);
    _gpio_set_input(IR_SENSOR_BOTTOM_LEFT);
    _gpio_set_input(IR_SENSOR_BOTTOM_RIGHT);
}
#include "led.h"
#include "gpio.h"

void init_led(void)
{
    // NOP
}

void led_on(void)
{
    GPIO_HIGH(LED);
}

void led_off(void)
{
    GPIO_LOW(LED);
}

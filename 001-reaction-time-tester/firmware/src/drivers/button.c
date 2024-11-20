#include <stdbool.h>
#include "button.h"
#include "gpio.h"
#include "uart.h"

static enum button_state state = RELEASED;

void init_button(void)
{
    _gpio_set_input(BUTTON);
    _gpio_high(BUTTON);     // Enable internal pull-up resistor

    uart_transmit("- BUTTON ready\r\n");
}

enum button_state button_state_get(void)
{
    bool push_probe = (_gpio_get_input(BUTTON) == 0);

    switch (state)
    {
        case RELEASED:
            state = push_probe ? PRE_PUSHED : RELEASED;
            break;

        case PRE_PUSHED:
            state = push_probe ? PUSHED : RELEASED;
            break;

        case PUSHED:
            state = push_probe ? PUSHED : PRE_RELEASED;
            break;

        case PRE_RELEASED:
            state = push_probe ? PUSHED : RELEASED;
            break;
    }

    return state;
}